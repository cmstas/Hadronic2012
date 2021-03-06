#include "ShortTrackLooper.h"

using namespace std;
using namespace duplicate_removal;

class mt2tree;

const bool recalculate = true; // to use a non standard (ie not in babies) Fshort, change the iso and qual cuts and provide a new Fshort input file below
const int applyRecoVeto = 2; // 0: None, 1: use MT2 ID leptons for the reco veto, 2: use any Reco ID (Default: 2)
const bool increment17 = false;
const float isoSTC = 6, qualSTC = 3;
bool adjL = true; // use fshort'(M) = fshort(M) * fshort(L)_mc / fshort(M)_mc instead of raw fshort(M) in place of fshort(L)
const bool EventWise = false; // Count events with Nst == 1 and Nst == 2, or just counts STs?
const bool skipHighEventWeights = true;
const bool prioritize = true; // only count the longest, then highest pt, track

const bool merge17and18 = true;

// turn on to apply json file to data
const bool applyJSON = true;
const bool blind = false;

const bool applyISRWeights = true; // evt_id is messed up in current babies, and we don't have isr weights implemented for 2017 MC anyway

const bool doNTrueIntReweight = true; // evt_id is messed up in current babies

bool doHEMveto = true;
int HEM_startRun = 319077; // affects 38.58 out of 58.83 fb-1 in 2018
uint HEM_fracNum = 1286, HEM_fracDen = 1961; // 38.58/58.82 ~= 1286/1961. Used for figuring out if we should veto MC events
float HEM_ptCut = 30.0;  // veto on jets above this threshold
float HEM_region[4] = {-4.7, -1.4, -1.6, -0.8}; // etalow, etahigh, philow, phihigh

// turn on to apply L1prefire inefficiency weights to MC (2016/17 only)
bool applyL1PrefireWeights = true;



TFile VetoFile("veto_etaphi.root");
TH2F* veto_etaphi_16 = (TH2F*) VetoFile.Get("etaphi_veto_16");
TH2F* veto_etaphi_17 = (TH2F*) VetoFile.Get("etaphi_veto_17");
TH2F* veto_etaphi_18 = (TH2F*) VetoFile.Get("etaphi_veto_18");

int ShortTrackLooper::InEtaPhiVetoRegion(float eta, float phi, int year) {
  if (fabs(eta) > 2.4) return -1;
  TH2F* veto_hist = veto_etaphi_16;
  if (year == 2017) veto_hist = veto_etaphi_17;
  if (year == 2018) veto_hist = veto_etaphi_18;
  return (int) veto_hist->GetBinContent(veto_hist->FindBin(eta,phi));
}

int ShortTrackLooper::loop(TChain* ch, char * outtag, std::string config_tag, char * runtag, double ctau_in = -1, double ctau_out = -1) {
  string tag(outtag);

  cout << "Input  ctau: " << ctau_in << endl;
  cout << "Output ctau: " << ctau_out << endl;

  double tau_in = ctau_in / TMath::C() / 100;
  double tau_out = ctau_out / TMath::C() / 100;

  config_ = GetMT2Config(config_tag);
  const int year = config_.year;  
  const float max_weight = year == 2016 ? 5.0 : 1.0;

  string signame = tag.substr(tag.rfind("/") + 1);
  bool isT2bt = signame.find("bt") != std::string::npos;

  unsigned int genmet_idx = signame.find("_GENMET");
  unsigned int isr_idx = signame.find("_ISR");
  if (genmet_idx != std::string::npos) signame = signame.substr(0,genmet_idx);
  if (isr_idx    != std::string::npos) signame = signame.substr(0,   isr_idx);

  mt2tree t;
  t.Init(ch);
  t.GetEntry(0); // Need to load first event for evt_id branch

  //  bool isSignal = tag.find("sim") != std::string::npos;
  bool isSignal = t.evt_id >= 1000;
  if (!isSignal) {
    cout << "This looper can only be used for signal scans. Doesn't like like signal (t.evt_id = " << t.evt_id << " < 1000). Aborting..." << endl;
    return -1;
  }

  bool useGENMET = tag.find("GENMET") != std::string::npos;
  bool noISR = tag.find("ISR") != std::string::npos; // the ISR file does NOT apply ISR correction, used to calaculate ISR error
  bool useMC = tag.find("MC") != std::string::npos;

  TH1F* h_xsec = 0;
  TFile * f_xsec = TFile::Open("xsec_susy_13tev_run2.root");
  TString xsec_name = "h_xsec_gluino";
  if (tag.find("T2") != std::string::npos) {
    if (tag.find("T2qq") != std::string::npos) {
      xsec_name = "h_xsec_squark";
    }
    else {
      xsec_name = "h_xsec_stop";
    }
  }

  cout << "Pulling xsec from " << xsec_name << endl;

  TH1F* h_xsec_orig = (TH1F*) f_xsec->Get( xsec_name );
  h_xsec = (TH1F*) h_xsec_orig->Clone("h_xsec");
  h_xsec->SetDirectory(0);
  f_xsec->Close();

  TH2D* h_sig_nevents_ = 0;
  TH2D* h_sig_avgweight_isr_ = 0;
  TH2D* h_sig_avgweight_isr_UP_ = 0;
  TH2D* h_sig_avgweight_isr_DN_ = 0;
  string weights_dir = "short_track";
  string weights_name = signame;
  if (ctau_in != ctau_out) {
    string sample_name = weights_name.substr(0,weights_name.find("_"));
    weights_name = sample_name + "_" + to_string( (int) ctau_in);
  }
  TFile* f_nsig_weights = new TFile(Form("%s/%d/nsig_weights_%s.root", weights_dir.c_str(), year, weights_name.c_str()));
  TH2D* h_sig_nevents_temp = (TH2D*) f_nsig_weights->Get("h_nsig");
  TH2D* h_sig_avgweight_isr_temp = (TH2D*) f_nsig_weights->Get("h_avg_weight_isr");
  TH2D* h_sig_avgweight_isr_UP_temp = (TH2D*) f_nsig_weights->Get("h_avg_weight_isr_UP");
  TH2D* h_sig_avgweight_isr_DN_temp = (TH2D*) f_nsig_weights->Get("h_avg_weight_isr_DN");
  h_sig_nevents_ = (TH2D*) h_sig_nevents_temp->Clone("h_sig_nevents");
  h_sig_avgweight_isr_ = (TH2D*) h_sig_avgweight_isr_temp->Clone("h_sig_avgweight_isr");
  h_sig_avgweight_isr_UP_ = (TH2D*) h_sig_avgweight_isr_UP_temp->Clone("h_sig_avgweight_isr_UP");
  h_sig_avgweight_isr_DN_ = (TH2D*) h_sig_avgweight_isr_DN_temp->Clone("h_sig_avgweight_isr_DN");
  h_sig_nevents_->SetDirectory(0);
  h_sig_avgweight_isr_->SetDirectory(0);
  h_sig_avgweight_isr_UP_->SetDirectory(0);
  h_sig_avgweight_isr_DN_->SetDirectory(0);
  f_nsig_weights->Close();
  delete f_nsig_weights;
  
  cout << "Using runtag: " << runtag << endl;

  cout << (merge17and18 ? "" : "not ") << "merging 2017 and 2018" << endl;

  const TString FshortName16Data = Form("Fshort_data_2016_%s.root",runtag);
  const TString FshortName16MC = Form("Fshort_mc_2016_%s.root",runtag);
  const TString FshortName17Data = Form("Fshort_data_%s_%s.root",(merge17and18 ? "2017and2018" : "2017"), runtag);
  const TString FshortName17MC = Form("Fshort_mc_%s_%s.root",(merge17and18 ? "2017and2018" : "2017"),runtag);
  const TString FshortName18Data = Form("Fshort_data_%s_%s.root",(merge17and18 ? "2017and2018" : "2018"),runtag);
  const TString FshortName18MC = Form("Fshort_mc_%s_%s.root",(merge17and18 ? "2017and2018" : "2018"), runtag);

  cout << "Will load observed MR ST counts from: " 
       << FshortName16Data.Data()
       << FshortName16MC.Data()
       << FshortName17Data.Data()
       << FshortName17MC.Data()
       << FshortName18Data.Data()
       << FshortName18MC.Data() << endl;

  // Book histograms
  TH1::SetDefaultSumw2(true); // Makes histograms do proper error calculation automatically

  const int Pidx = 1;
  const int P3idx = 2;
  const int P4idx = 3;
  const int Midx = 4;
  const int Lidx = 5;
  //  const int LREJidx = 6;

  const int n_track_bins = 5;
  const float track_bins[6] = {0.,1.,2.,3.,4.,5.};

  const int n_DLbins = 100;
  float *DLbins = new float[n_DLbins+1];
  for (int i = 0; i <= n_DLbins; i++) DLbins[i] = i*5;

  const int n_factorbins = 12;
  float *Factorbins = new float[n_factorbins+1];
  for (int i = 0; i <= n_factorbins; i++) Factorbins[i] = i*0.5;

  const int n_betabins = 10;
  float *Betabins = new float[n_betabins+1];
  for (int i = 0; i <= n_betabins; i++) Betabins[i] = i*0.1;

  // 0 to 2825 in steps of 25 for non T2bt, else 0 to 2500 in steps of 17-ish: 0, 17, 33, 50, 67, 83
  int n_m1bins = isT2bt ? 151 : 113;
  float* m1bins = new float[n_m1bins+1];
  int n_m2bins = isT2bt ? 151 : 113;
  float* m2bins = new float[n_m2bins+1];
  float stepsize = isT2bt ? 16.6667 : 25.0;
  for (int i = 0; i <= n_m1bins; i++) {
    m1bins[i] = i*stepsize;
  }
  for (int i = 0; i <= n_m2bins; i++) {
    m2bins[i] = i*stepsize;
  }

  TH3D* h_decay_factor = new TH3D("h_decay_factor","t/#tau_{in} for Charginos with DecayXY > 10 cm",n_factorbins,Factorbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_decay_factor_P3 = new TH3D("h_decay_factor_P3","t/#tau_{in} for P3 ST Charginos",n_factorbins,Factorbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_decay_factor_P4 = new TH3D("h_decay_factor_P4","t/#tau_{in} for P4 ST Charginos",n_factorbins,Factorbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_decay_factor_M = new TH3D("h_decay_factor_M","t/#tau_{in} for M ST Charginos",n_factorbins,Factorbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_decay_factor_L = new TH3D("h_decay_factor_L","t/#tau_{in} for L ST Charginos",n_factorbins,Factorbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_beta = new TH3D("h_beta","Chargino #beta Distribution",n_betabins,Betabins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_DL_raw = new TH3D("h_DL_raw","Decay Length Distribution Before Reweighting",n_DLbins,DLbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_DL = new TH3D("h_DL","Decay Length Distribution after Reweighting",n_DLbins,DLbins,n_m1bins,m1bins,n_m2bins,m2bins);

  int n_wbins = 6;
  const float wbins [n_wbins] = {-3, -2, -1, 0, 1, 2, 3};

  TH2D* h_weight_raw = new TH2D("h_weight_raw","Total Weight before Reweight",n_m1bins,m1bins,n_m2bins,m2bins);
  TH2D* h_eff_den = new TH2D("h_eff_den","Total Weight after Reweight",n_m1bins,m1bins,n_m2bins,m2bins);
  TH2D* h_weight_nospikes = new TH2D("h_weight_nospikes","Total Weight after Reweight, Spike Events Removed",n_m1bins,m1bins,n_m2bins,m2bins);
  TH2D* h_nevents = new TH2D("h_nevents","Number of Events without Spike Removal",n_m1bins,m1bins,n_m2bins,m2bins);
  TH2D* h_nospikes = new TH2D("h_nospikes","Number of Events after Reweight, Spike Events Removed",n_m1bins,m1bins,n_m2bins,m2bins);
  TH2D* h_eff_num = new TH2D("h_eff_num","Weight of Passing Events",n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_weight_all = new TH3D("h_weight_all","Initial Log(Reweight) Dist",n_wbins,wbins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_weight_acc = new TH3D("h_weight_acc","Selected Log(Reweight) Dist",n_wbins,wbins,n_m1bins,m1bins,n_m2bins,m2bins);

  TH3D h_counts_STC ("h_counts_STC","STC Counts by Length;",n_track_bins,track_bins,n_m1bins,m1bins,n_m2bins,m2bins);
  h_counts_STC.GetXaxis()->SetBinLabel(Pidx,"P");
  h_counts_STC.GetXaxis()->SetBinLabel(P3idx,"P3");
  h_counts_STC.GetXaxis()->SetBinLabel(P4idx,"P4");
  h_counts_STC.GetXaxis()->SetBinLabel(Midx,"M");
  h_counts_STC.GetXaxis()->SetBinLabel(Lidx,"L (acc)");

  TH3D h_counts_ST ("h_counts_ST","ST Counts by Length;",n_track_bins,track_bins,n_m1bins,m1bins,n_m2bins,m2bins);
  h_counts_ST.GetXaxis()->SetBinLabel(Pidx,"P");
  h_counts_ST.GetXaxis()->SetBinLabel(P3idx,"P3");
  h_counts_ST.GetXaxis()->SetBinLabel(P4idx,"P4");
  h_counts_ST.GetXaxis()->SetBinLabel(Midx,"M");
  h_counts_ST.GetXaxis()->SetBinLabel(Lidx,"L (acc)");

  /////////////
  // STC hists
  /////////////

  // NjHt
  TH3D* h_1L_MR_STC = (TH3D*)h_counts_STC.Clone("h_1L_MR_STC");
  TH3D* h_1M_MR_STC = (TH3D*)h_counts_STC.Clone("h_1M_MR_STC");
  TH3D* h_1H_MR_STC = (TH3D*)h_counts_STC.Clone("h_1H_MR_STC");
  TH3D* h_LL_MR_STC = (TH3D*)h_counts_STC.Clone("h_LL_MR_STC");
  TH3D* h_LM_MR_STC = (TH3D*)h_counts_STC.Clone("h_LM_MR_STC");
  TH3D* h_LH_MR_STC = (TH3D*)h_counts_STC.Clone("h_LH_MR_STC");
  TH3D* h_HL_MR_STC = (TH3D*)h_counts_STC.Clone("h_HL_MR_STC");
  TH3D* h_HM_MR_STC = (TH3D*)h_counts_STC.Clone("h_HM_MR_STC");
  TH3D* h_HH_MR_STC = (TH3D*)h_counts_STC.Clone("h_HH_MR_STC");

  TH3D* h_1L_VR_STC = (TH3D*)h_counts_STC.Clone("h_1L_VR_STC");
  TH3D* h_1M_VR_STC = (TH3D*)h_counts_STC.Clone("h_1M_VR_STC");
  TH3D* h_1H_VR_STC = (TH3D*)h_counts_STC.Clone("h_1H_VR_STC");
  TH3D* h_LL_VR_STC = (TH3D*)h_counts_STC.Clone("h_LL_VR_STC");
  TH3D* h_LM_VR_STC = (TH3D*)h_counts_STC.Clone("h_LM_VR_STC");
  TH3D* h_LH_VR_STC = (TH3D*)h_counts_STC.Clone("h_LH_VR_STC");
  TH3D* h_HL_VR_STC = (TH3D*)h_counts_STC.Clone("h_HL_VR_STC");
  TH3D* h_HM_VR_STC = (TH3D*)h_counts_STC.Clone("h_HM_VR_STC");
  TH3D* h_HH_VR_STC = (TH3D*)h_counts_STC.Clone("h_HH_VR_STC");

  TH3D* h_1L_SR_STC = (TH3D*)h_counts_STC.Clone("h_1L_SR_STC");
  TH3D* h_1M_SR_STC = (TH3D*)h_counts_STC.Clone("h_1M_SR_STC");
  TH3D* h_1H_SR_STC = (TH3D*)h_counts_STC.Clone("h_1H_SR_STC");
  TH3D* h_LL_SR_STC = (TH3D*)h_counts_STC.Clone("h_LL_SR_STC");
  TH3D* h_LM_SR_STC = (TH3D*)h_counts_STC.Clone("h_LM_SR_STC");
  TH3D* h_LH_SR_STC = (TH3D*)h_counts_STC.Clone("h_LH_SR_STC");
  TH3D* h_HL_SR_STC = (TH3D*)h_counts_STC.Clone("h_HL_SR_STC");
  TH3D* h_HM_SR_STC = (TH3D*)h_counts_STC.Clone("h_HM_SR_STC");
  TH3D* h_HH_SR_STC = (TH3D*)h_counts_STC.Clone("h_HH_SR_STC");

  // Hi pt

  // NjHt
  TH3D* h_1L_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1L_MR_hi_STC");
  TH3D* h_1M_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1M_MR_hi_STC");
  TH3D* h_1H_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1H_MR_hi_STC");
  TH3D* h_LL_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LL_MR_hi_STC");
  TH3D* h_LM_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LM_MR_hi_STC");
  TH3D* h_LH_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LH_MR_hi_STC");
  TH3D* h_HL_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HL_MR_hi_STC");
  TH3D* h_HM_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HM_MR_hi_STC");
  TH3D* h_HH_MR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HH_MR_hi_STC");

  TH3D* h_1L_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1L_VR_hi_STC");
  TH3D* h_1M_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1M_VR_hi_STC");
  TH3D* h_1H_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1H_VR_hi_STC");
  TH3D* h_LL_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LL_VR_hi_STC");
  TH3D* h_LM_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LM_VR_hi_STC");
  TH3D* h_LH_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LH_VR_hi_STC");
  TH3D* h_HL_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HL_VR_hi_STC");
  TH3D* h_HM_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HM_VR_hi_STC");
  TH3D* h_HH_VR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HH_VR_hi_STC");

  TH3D* h_1L_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1L_SR_hi_STC");
  TH3D* h_1M_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1M_SR_hi_STC");
  TH3D* h_1H_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_1H_SR_hi_STC");
  TH3D* h_LL_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LL_SR_hi_STC");
  TH3D* h_LM_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LM_SR_hi_STC");
  TH3D* h_LH_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_LH_SR_hi_STC");
  TH3D* h_HL_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HL_SR_hi_STC");
  TH3D* h_HM_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HM_SR_hi_STC");
  TH3D* h_HH_SR_hi_STC = (TH3D*)h_counts_STC.Clone("h_HH_SR_hi_STC");

  // Lo pt
  // NjHt
  TH3D* h_1L_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1L_MR_lo_STC");
  TH3D* h_1M_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1M_MR_lo_STC");
  TH3D* h_1H_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1H_MR_lo_STC");
  TH3D* h_LL_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LL_MR_lo_STC");
  TH3D* h_LM_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LM_MR_lo_STC");
  TH3D* h_LH_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LH_MR_lo_STC");
  TH3D* h_HL_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HL_MR_lo_STC");
  TH3D* h_HM_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HM_MR_lo_STC");
  TH3D* h_HH_MR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HH_MR_lo_STC");

  TH3D* h_1L_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1L_VR_lo_STC");
  TH3D* h_1M_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1M_VR_lo_STC");
  TH3D* h_1H_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1H_VR_lo_STC");
  TH3D* h_LL_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LL_VR_lo_STC");
  TH3D* h_LM_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LM_VR_lo_STC");
  TH3D* h_LH_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LH_VR_lo_STC");
  TH3D* h_HL_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HL_VR_lo_STC");
  TH3D* h_HM_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HM_VR_lo_STC");
  TH3D* h_HH_VR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HH_VR_lo_STC");

  TH3D* h_1L_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1L_SR_lo_STC");
  TH3D* h_1M_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1M_SR_lo_STC");
  TH3D* h_1H_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_1H_SR_lo_STC");
  TH3D* h_LL_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LL_SR_lo_STC");
  TH3D* h_LM_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LM_SR_lo_STC");
  TH3D* h_LH_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_LH_SR_lo_STC");
  TH3D* h_HL_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HL_SR_lo_STC");
  TH3D* h_HM_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HM_SR_lo_STC");
  TH3D* h_HH_SR_lo_STC = (TH3D*)h_counts_STC.Clone("h_HH_SR_lo_STC");

  /////////////
  // ST hists
  /////////////

  // NjHt
  TH3D* h_1L_MR_ST = (TH3D*)h_counts_ST.Clone("h_1L_MR_ST");
  TH3D* h_1M_MR_ST = (TH3D*)h_counts_ST.Clone("h_1M_MR_ST");
  TH3D* h_1H_MR_ST = (TH3D*)h_counts_ST.Clone("h_1H_MR_ST");
  TH3D* h_LL_MR_ST = (TH3D*)h_counts_ST.Clone("h_LL_MR_ST");
  TH3D* h_LM_MR_ST = (TH3D*)h_counts_ST.Clone("h_LM_MR_ST");
  TH3D* h_LH_MR_ST = (TH3D*)h_counts_ST.Clone("h_LH_MR_ST");
  TH3D* h_HL_MR_ST = (TH3D*)h_counts_ST.Clone("h_HL_MR_ST");
  TH3D* h_HM_MR_ST = (TH3D*)h_counts_ST.Clone("h_HM_MR_ST");
  TH3D* h_HH_MR_ST = (TH3D*)h_counts_ST.Clone("h_HH_MR_ST");

  TH3D* h_1L_VR_ST = (TH3D*)h_counts_ST.Clone("h_1L_VR_ST");
  TH3D* h_1M_VR_ST = (TH3D*)h_counts_ST.Clone("h_1M_VR_ST");
  TH3D* h_1H_VR_ST = (TH3D*)h_counts_ST.Clone("h_1H_VR_ST");
  TH3D* h_LL_VR_ST = (TH3D*)h_counts_ST.Clone("h_LL_VR_ST");
  TH3D* h_LM_VR_ST = (TH3D*)h_counts_ST.Clone("h_LM_VR_ST");
  TH3D* h_LH_VR_ST = (TH3D*)h_counts_ST.Clone("h_LH_VR_ST");
  TH3D* h_HL_VR_ST = (TH3D*)h_counts_ST.Clone("h_HL_VR_ST");
  TH3D* h_HM_VR_ST = (TH3D*)h_counts_ST.Clone("h_HM_VR_ST");
  TH3D* h_HH_VR_ST = (TH3D*)h_counts_ST.Clone("h_HH_VR_ST");

  TH3D* h_1L_SR_ST = (TH3D*)h_counts_ST.Clone("h_1L_SR_ST");
  TH3D* h_1M_SR_ST = (TH3D*)h_counts_ST.Clone("h_1M_SR_ST");
  TH3D* h_1H_SR_ST = (TH3D*)h_counts_ST.Clone("h_1H_SR_ST");
  TH3D* h_LL_SR_ST = (TH3D*)h_counts_ST.Clone("h_LL_SR_ST");
  TH3D* h_LM_SR_ST = (TH3D*)h_counts_ST.Clone("h_LM_SR_ST");
  TH3D* h_LH_SR_ST = (TH3D*)h_counts_ST.Clone("h_LH_SR_ST");
  TH3D* h_HL_SR_ST = (TH3D*)h_counts_ST.Clone("h_HL_SR_ST");
  TH3D* h_HM_SR_ST = (TH3D*)h_counts_ST.Clone("h_HM_SR_ST");
  TH3D* h_HH_SR_ST = (TH3D*)h_counts_ST.Clone("h_HH_SR_ST");

  // Hi pt

  // NjHt
  TH3D* h_1L_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1L_MR_hi_ST");
  TH3D* h_1M_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1M_MR_hi_ST");
  TH3D* h_1H_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1H_MR_hi_ST");
  TH3D* h_LL_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LL_MR_hi_ST");
  TH3D* h_LM_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LM_MR_hi_ST");
  TH3D* h_LH_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LH_MR_hi_ST");
  TH3D* h_HL_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HL_MR_hi_ST");
  TH3D* h_HM_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HM_MR_hi_ST");
  TH3D* h_HH_MR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HH_MR_hi_ST");

  TH3D* h_1L_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1L_VR_hi_ST");
  TH3D* h_1M_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1M_VR_hi_ST");
  TH3D* h_1H_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1H_VR_hi_ST");
  TH3D* h_LL_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LL_VR_hi_ST");
  TH3D* h_LM_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LM_VR_hi_ST");
  TH3D* h_LH_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LH_VR_hi_ST");
  TH3D* h_HL_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HL_VR_hi_ST");
  TH3D* h_HM_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HM_VR_hi_ST");
  TH3D* h_HH_VR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HH_VR_hi_ST");

  TH3D* h_1L_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1L_SR_hi_ST");
  TH3D* h_1M_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1M_SR_hi_ST");
  TH3D* h_1H_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_1H_SR_hi_ST");
  TH3D* h_LL_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LL_SR_hi_ST");
  TH3D* h_LM_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LM_SR_hi_ST");
  TH3D* h_LH_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_LH_SR_hi_ST");
  TH3D* h_HL_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HL_SR_hi_ST");
  TH3D* h_HM_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HM_SR_hi_ST");
  TH3D* h_HH_SR_hi_ST = (TH3D*)h_counts_ST.Clone("h_HH_SR_hi_ST");

  // Lo pt
  // NjHt
  TH3D* h_1L_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1L_MR_lo_ST");
  TH3D* h_1M_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1M_MR_lo_ST");
  TH3D* h_1H_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1H_MR_lo_ST");
  TH3D* h_LL_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LL_MR_lo_ST");
  TH3D* h_LM_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LM_MR_lo_ST");
  TH3D* h_LH_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LH_MR_lo_ST");
  TH3D* h_HL_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HL_MR_lo_ST");
  TH3D* h_HM_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HM_MR_lo_ST");
  TH3D* h_HH_MR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HH_MR_lo_ST");

  TH3D* h_1L_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1L_VR_lo_ST");
  TH3D* h_1M_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1M_VR_lo_ST");
  TH3D* h_1H_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1H_VR_lo_ST");
  TH3D* h_LL_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LL_VR_lo_ST");
  TH3D* h_LM_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LM_VR_lo_ST");
  TH3D* h_LH_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LH_VR_lo_ST");
  TH3D* h_HL_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HL_VR_lo_ST");
  TH3D* h_HM_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HM_VR_lo_ST");
  TH3D* h_HH_VR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HH_VR_lo_ST");

  TH3D* h_1L_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1L_SR_lo_ST");
  TH3D* h_1M_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1M_SR_lo_ST");
  TH3D* h_1H_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_1H_SR_lo_ST");
  TH3D* h_LL_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LL_SR_lo_ST");
  TH3D* h_LM_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LM_SR_lo_ST");
  TH3D* h_LH_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_LH_SR_lo_ST");
  TH3D* h_HL_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HL_SR_lo_ST");
  TH3D* h_HM_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HM_SR_lo_ST");
  TH3D* h_HH_SR_lo_ST = (TH3D*)h_counts_ST.Clone("h_HH_SR_lo_ST");

  // Save fractional change in fshort, for signal contamination calculation
  TH3D* h_fracFS = new TH3D("h_fracFS","N_{ST}^{Sig#;MR}/N_{ST}^{Obs#;MR};Mass 1 (GeV);Mass 2 (GeV)",n_track_bins,track_bins,n_m1bins,m1bins,n_m2bins,m2bins);
  TH3D* h_fracFS_1 = (TH3D*) h_fracFS->Clone("h_fracFS_1");
  TH3D* h_fracFS_23 = (TH3D*) h_fracFS->Clone("h_fracFS_23");
  TH3D* h_fracFS_4 = (TH3D*) h_fracFS->Clone("h_fracFS_4");
  TH3D* h_fracFS_1_hi = (TH3D*) h_fracFS->Clone("h_fracFS_1_hi");
  TH3D* h_fracFS_23_hi = (TH3D*) h_fracFS->Clone("h_fracFS_23_hi");
  TH3D* h_fracFS_4_hi = (TH3D*) h_fracFS->Clone("h_fracFS_4_hi");
  TH3D* h_fracFS_1_lo = (TH3D*) h_fracFS->Clone("h_fracFS_1_lo");
  TH3D* h_fracFS_23_lo = (TH3D*) h_fracFS->Clone("h_fracFS_23_lo");
  TH3D* h_fracFS_4_lo = (TH3D*) h_fracFS->Clone("h_fracFS_4_lo");

  unordered_map<TH3D*,TH3D*> low_hists;
  low_hists[h_1L_MR_STC] = h_1L_MR_lo_STC;
  low_hists[h_1M_MR_STC] = h_1M_MR_lo_STC;
  low_hists[h_1H_MR_STC] = h_1H_MR_lo_STC;
  low_hists[h_LL_MR_STC] = h_LL_MR_lo_STC;
  low_hists[h_LM_MR_STC] = h_LM_MR_lo_STC;
  low_hists[h_LH_MR_STC] = h_LH_MR_lo_STC;
  low_hists[h_HL_MR_STC] = h_HL_MR_lo_STC;
  low_hists[h_HM_MR_STC] = h_HM_MR_lo_STC;
  low_hists[h_HH_MR_STC] = h_HH_MR_lo_STC;
  low_hists[h_1L_VR_STC] = h_1L_VR_lo_STC;
  low_hists[h_1M_VR_STC] = h_1M_VR_lo_STC;
  low_hists[h_1H_VR_STC] = h_1H_VR_lo_STC;
  low_hists[h_LL_VR_STC] = h_LL_VR_lo_STC;
  low_hists[h_LM_VR_STC] = h_LM_VR_lo_STC;
  low_hists[h_LH_VR_STC] = h_LH_VR_lo_STC;
  low_hists[h_HL_VR_STC] = h_HL_VR_lo_STC;
  low_hists[h_HM_VR_STC] = h_HM_VR_lo_STC;
  low_hists[h_HH_VR_STC] = h_HH_VR_lo_STC;
  low_hists[h_1L_SR_STC] = h_1L_SR_lo_STC;
  low_hists[h_1M_SR_STC] = h_1M_SR_lo_STC;
  low_hists[h_1H_SR_STC] = h_1H_SR_lo_STC;
  low_hists[h_LL_SR_STC] = h_LL_SR_lo_STC;
  low_hists[h_LM_SR_STC] = h_LM_SR_lo_STC;
  low_hists[h_LH_SR_STC] = h_LH_SR_lo_STC;
  low_hists[h_HL_SR_STC] = h_HL_SR_lo_STC;
  low_hists[h_HM_SR_STC] = h_HM_SR_lo_STC;
  low_hists[h_HH_SR_STC] = h_HH_SR_lo_STC;

  low_hists[h_fracFS_1] = h_fracFS_1_lo;
  low_hists[h_fracFS_23] = h_fracFS_23_lo;
  low_hists[h_fracFS_4] = h_fracFS_4_lo;

  low_hists[h_1L_MR_ST] = h_1L_MR_lo_ST;
  low_hists[h_1M_MR_ST] = h_1M_MR_lo_ST;
  low_hists[h_1H_MR_ST] = h_1H_MR_lo_ST;
  low_hists[h_LL_MR_ST] = h_LL_MR_lo_ST;
  low_hists[h_LM_MR_ST] = h_LM_MR_lo_ST;
  low_hists[h_LH_MR_ST] = h_LH_MR_lo_ST;
  low_hists[h_HL_MR_ST] = h_HL_MR_lo_ST;
  low_hists[h_HM_MR_ST] = h_HM_MR_lo_ST;
  low_hists[h_HH_MR_ST] = h_HH_MR_lo_ST;
  low_hists[h_1L_VR_ST] = h_1L_VR_lo_ST;
  low_hists[h_1M_VR_ST] = h_1M_VR_lo_ST;
  low_hists[h_1H_VR_ST] = h_1H_VR_lo_ST;
  low_hists[h_LL_VR_ST] = h_LL_VR_lo_ST;
  low_hists[h_LM_VR_ST] = h_LM_VR_lo_ST;
  low_hists[h_LH_VR_ST] = h_LH_VR_lo_ST;
  low_hists[h_HL_VR_ST] = h_HL_VR_lo_ST;
  low_hists[h_HM_VR_ST] = h_HM_VR_lo_ST;
  low_hists[h_HH_VR_ST] = h_HH_VR_lo_ST;
  low_hists[h_1L_SR_ST] = h_1L_SR_lo_ST;
  low_hists[h_1M_SR_ST] = h_1M_SR_lo_ST;
  low_hists[h_1H_SR_ST] = h_1H_SR_lo_ST;
  low_hists[h_LL_SR_ST] = h_LL_SR_lo_ST;
  low_hists[h_LM_SR_ST] = h_LM_SR_lo_ST;
  low_hists[h_LH_SR_ST] = h_LH_SR_lo_ST;
  low_hists[h_HL_SR_ST] = h_HL_SR_lo_ST;
  low_hists[h_HM_SR_ST] = h_HM_SR_lo_ST;
  low_hists[h_HH_SR_ST] = h_HH_SR_lo_ST;

  unordered_map<TH3D*,TH3D*> hi_hists;
  hi_hists[h_1L_MR_STC] = h_1L_MR_hi_STC;
  hi_hists[h_1M_MR_STC] = h_1M_MR_hi_STC;
  hi_hists[h_1H_MR_STC] = h_1H_MR_hi_STC;
  hi_hists[h_LL_MR_STC] = h_LL_MR_hi_STC;
  hi_hists[h_LM_MR_STC] = h_LM_MR_hi_STC;
  hi_hists[h_LH_MR_STC] = h_LH_MR_hi_STC;
  hi_hists[h_HL_MR_STC] = h_HL_MR_hi_STC;
  hi_hists[h_HM_MR_STC] = h_HM_MR_hi_STC;
  hi_hists[h_HH_MR_STC] = h_HH_MR_hi_STC;
  hi_hists[h_1L_VR_STC] = h_1L_VR_hi_STC;
  hi_hists[h_1M_VR_STC] = h_1M_VR_hi_STC;
  hi_hists[h_1H_VR_STC] = h_1H_VR_hi_STC;
  hi_hists[h_LL_VR_STC] = h_LL_VR_hi_STC;
  hi_hists[h_LM_VR_STC] = h_LM_VR_hi_STC;
  hi_hists[h_LH_VR_STC] = h_LH_VR_hi_STC;
  hi_hists[h_HL_VR_STC] = h_HL_VR_hi_STC;
  hi_hists[h_HM_VR_STC] = h_HM_VR_hi_STC;
  hi_hists[h_HH_VR_STC] = h_HH_VR_hi_STC;
  hi_hists[h_1L_SR_STC] = h_1L_SR_hi_STC;
  hi_hists[h_1M_SR_STC] = h_1M_SR_hi_STC;
  hi_hists[h_1H_SR_STC] = h_1H_SR_hi_STC;
  hi_hists[h_LL_SR_STC] = h_LL_SR_hi_STC;
  hi_hists[h_LM_SR_STC] = h_LM_SR_hi_STC;
  hi_hists[h_LH_SR_STC] = h_LH_SR_hi_STC;
  hi_hists[h_HL_SR_STC] = h_HL_SR_hi_STC;
  hi_hists[h_HM_SR_STC] = h_HM_SR_hi_STC;
  hi_hists[h_HH_SR_STC] = h_HH_SR_hi_STC;

  hi_hists[h_1L_MR_ST] = h_1L_MR_hi_ST;
  hi_hists[h_1M_MR_ST] = h_1M_MR_hi_ST;
  hi_hists[h_1H_MR_ST] = h_1H_MR_hi_ST;
  hi_hists[h_LL_MR_ST] = h_LL_MR_hi_ST;
  hi_hists[h_LM_MR_ST] = h_LM_MR_hi_ST;
  hi_hists[h_LH_MR_ST] = h_LH_MR_hi_ST;
  hi_hists[h_HL_MR_ST] = h_HL_MR_hi_ST;
  hi_hists[h_HM_MR_ST] = h_HM_MR_hi_ST;
  hi_hists[h_HH_MR_ST] = h_HH_MR_hi_ST;
  hi_hists[h_1L_VR_ST] = h_1L_VR_hi_ST;
  hi_hists[h_1M_VR_ST] = h_1M_VR_hi_ST;
  hi_hists[h_1H_VR_ST] = h_1H_VR_hi_ST;
  hi_hists[h_LL_VR_ST] = h_LL_VR_hi_ST;
  hi_hists[h_LM_VR_ST] = h_LM_VR_hi_ST;
  hi_hists[h_LH_VR_ST] = h_LH_VR_hi_ST;
  hi_hists[h_HL_VR_ST] = h_HL_VR_hi_ST;
  hi_hists[h_HM_VR_ST] = h_HM_VR_hi_ST;
  hi_hists[h_HH_VR_ST] = h_HH_VR_hi_ST;
  hi_hists[h_1L_SR_ST] = h_1L_SR_hi_ST;
  hi_hists[h_1M_SR_ST] = h_1M_SR_hi_ST;
  hi_hists[h_1H_SR_ST] = h_1H_SR_hi_ST;
  hi_hists[h_LL_SR_ST] = h_LL_SR_hi_ST;
  hi_hists[h_LM_SR_ST] = h_LM_SR_hi_ST;
  hi_hists[h_LH_SR_ST] = h_LH_SR_hi_ST;
  hi_hists[h_HL_SR_ST] = h_HL_SR_hi_ST;
  hi_hists[h_HM_SR_ST] = h_HM_SR_hi_ST;
  hi_hists[h_HH_SR_ST] = h_HH_SR_hi_ST;

  hi_hists[h_fracFS_1] = h_fracFS_1_hi;
  hi_hists[h_fracFS_23] = h_fracFS_23_hi;
  hi_hists[h_fracFS_4] = h_fracFS_4_hi;

  // Load the configuration and output to screen
  cout << "[ShortTrackLooper::loop] using configuration tag: " << config_tag << endl;
  cout << "                  JSON: " << config_.json << endl;
  cout << "                  lumi: " << config_.lumi << " fb-1" << endl;

  vector<const Int_t*> trigs_SR_;
  vector<const Int_t*> trigs_prescaled_;
  vector<const Int_t*> trigs_singleLep_;

  // load the triggers we want
  if(config_.triggers.size() > 0){
    if( config_.triggers.find("SR")       == config_.triggers.end() || 
	config_.triggers.find("prescaledHT")       == config_.triggers.end() || 
	config_.triggers.find("SingleMu") == config_.triggers.end() || 
	config_.triggers.find("SingleEl") == config_.triggers.end() ){
      cout << "[ShortTrackLooper::loop] ERROR: invalid trigger map in configuration '" << config_tag << "'!" << endl;
      cout << "                         Make sure you have trigger vectors for 'SR', 'SingleMu', 'SingleEl', 'prescaledHT" << endl;
      return -1;
    }
    cout << "                  Triggers:" << endl;
    for(map<string,vector<string> >::iterator it=config_.triggers.begin(); it!=config_.triggers.end(); it++){
      cout << "                    " << it->first << ":" << endl;
      for(uint i=0; i<it->second.size(); i++){
	if(i==0)
	  cout << "                      " << it->second.at(i);
	else
	  cout << " || " << it->second.at(i);
      }
      cout << endl;
    }
    fillTriggerVector(t, trigs_SR_,        config_.triggers["SR"]);
    fillTriggerVector(t, trigs_prescaled_, config_.triggers["prescaledHT"]);
    fillTriggerVector(t, trigs_singleLep_, config_.triggers["SingleMu"]);
    fillTriggerVector(t, trigs_singleLep_, config_.triggers["SingleEl"]);
  }else if (config_tag.find("mc") == std::string::npos) {
    cout << "                  No triggers provided and no \"mc\" in config name. Weight calculation may be inaccurate." << endl;
    if(config_tag.find("data") != string::npos){
      cout << "[ShortTrackLooper::loop] WARNING! it looks like you are using data and didn't supply any triggers in the configuration." <<
	"\n                  Every event is going to fail the trigger selection!" << endl;
    }
  }

  TH1D* h_nTrueInt_weights_ = 0;
  if (doNTrueIntReweight && config_.pu_weights_file != "") {
    TFile* f_weights = new TFile((config_.pu_weights_file).c_str());
    TH1D* h_nTrueInt_weights_temp = (TH1D*) f_weights->Get("pileupWeight");
    //	outfile_->cd();
    h_nTrueInt_weights_ = (TH1D*) h_nTrueInt_weights_temp->Clone("h_pileupWeight");
    h_nTrueInt_weights_->SetDirectory(0);
    f_weights->Close();
    delete f_weights;
  }

  if (applyJSON && config_.json != "") {
    cout << "[ShortTrackLooper::loop] Loading json file: " << config_.json << endl;
    set_goodrun_file((config_.json).c_str());
  }

  cout << "Getting transfer factors" << endl;

  TString FshortName = "", FshortNameMC = "";
  if (year == 2016) {
    if (useMC) {
      FshortName = FshortName16MC;
    } else {
      FshortName = FshortName16Data;
    }
    FshortNameMC = FshortName16MC;
  }
  else if (year == 2017) {
    if (useMC) {
      FshortName = FshortName17MC;
    } else {
      FshortName = FshortName17Data;
    }
    FshortNameMC = FshortName17MC;
  }
  else if (year == 2018) {
    if (useMC) {
      FshortName = FshortName18MC;
    } else {
      FshortName = FshortName18Data;
    }
    FshortNameMC = FshortName18MC;
  }
  else {
    cout << "Check configuration" << endl;
    return -1;
  }

  TFile* FshortFile = TFile::Open(FshortName,"READ");

  TH1D* h_fs_Nj1;
  TH1D* h_fs_Nj23;
  TH1D* h_fs_Nj4;
  // Monojet turned on
  h_fs_Nj1 = ((TH2D*) FshortFile->Get("h_fs_1_MR_Baseline"))->ProjectionX("h_fs_1",2,2);
  h_fs_Nj23 = ((TH2D*) FshortFile->Get("h_fsMR_23_Baseline"))->ProjectionX("h_fs_23",2,2);
  h_fs_Nj4 = ((TH2D*) FshortFile->Get("h_fsMR_4_Baseline"))->ProjectionX("h_fs_4",2,2);
  h_fs_Nj1->SetDirectory(0);
  h_fs_Nj23->SetDirectory(0);
  h_fs_Nj4->SetDirectory(0);

  const double st_Nj1_P = h_fs_Nj1->GetBinContent(Pidx);
  const double st_Nj1_P3 = h_fs_Nj1->GetBinContent(P3idx);
  const double st_Nj1_P4 = h_fs_Nj1->GetBinContent(P4idx);
  const double st_Nj1_M = h_fs_Nj1->GetBinContent(Midx);

  const double st_Nj23_P = h_fs_Nj23->GetBinContent(Pidx);
  const double st_Nj23_P3 = h_fs_Nj23->GetBinContent(P3idx);
  const double st_Nj23_P4 = h_fs_Nj23->GetBinContent(P4idx);
  const double st_Nj23_M = h_fs_Nj23->GetBinContent(Midx);

  const double st_Nj4_P = h_fs_Nj4->GetBinContent(Pidx);
  const double st_Nj4_P3 = h_fs_Nj4->GetBinContent(P3idx);
  const double st_Nj4_P4 = h_fs_Nj4->GetBinContent(P4idx);
  const double st_Nj4_M = h_fs_Nj4->GetBinContent(Midx);

  TH1D* h_fs_Nj1_hi;
  TH1D* h_fs_Nj23_hi;
  TH1D* h_fs_Nj4_hi;
  // Monojet turned on
  h_fs_Nj1_hi = ((TH2D*) FshortFile->Get("h_fs_1_MR_Baseline_hipt"))->ProjectionX("h_fs_1_hi",2,2);
  h_fs_Nj23_hi = ((TH2D*) FshortFile->Get("h_fsMR_23_Baseline_hipt"))->ProjectionX("h_fs_23_hi",2,2);
  h_fs_Nj4_hi = ((TH2D*) FshortFile->Get("h_fsMR_4_Baseline_hipt"))->ProjectionX("h_fs_4_hi",2,2);
  h_fs_Nj1_hi->SetDirectory(0);
  h_fs_Nj23_hi->SetDirectory(0);
  h_fs_Nj4_hi->SetDirectory(0);

  const double st_Nj1_P_hi = h_fs_Nj1_hi->GetBinContent(Pidx);
  const double st_Nj1_P3_hi = h_fs_Nj1_hi->GetBinContent(P3idx);
  const double st_Nj1_P4_hi = h_fs_Nj1_hi->GetBinContent(P4idx);
  const double st_Nj1_M_hi = h_fs_Nj1_hi->GetBinContent(Midx);

  const double st_Nj23_P_hi = h_fs_Nj23_hi->GetBinContent(Pidx);
  const double st_Nj23_P3_hi = h_fs_Nj23_hi->GetBinContent(P3idx);
  const double st_Nj23_P4_hi = h_fs_Nj23_hi->GetBinContent(P4idx);
  const double st_Nj23_M_hi = h_fs_Nj23_hi->GetBinContent(Midx);

  const double st_Nj4_P_hi = h_fs_Nj4_hi->GetBinContent(Pidx);
  const double st_Nj4_P3_hi = h_fs_Nj4_hi->GetBinContent(P3idx);
  const double st_Nj4_P4_hi = h_fs_Nj4_hi->GetBinContent(P4idx);
  const double st_Nj4_M_hi = h_fs_Nj4_hi->GetBinContent(Midx);

  TH1D* h_fs_Nj1_lo;
  TH1D* h_fs_Nj23_lo;
  TH1D* h_fs_Nj4_lo;
  // Monojet turned on
  h_fs_Nj1_lo = ((TH2D*) FshortFile->Get("h_fs_1_MR_Baseline_lowpt"))->ProjectionX("h_fs_1_lo",2,2);
  h_fs_Nj23_lo = ((TH2D*) FshortFile->Get("h_fsMR_23_Baseline_lowpt"))->ProjectionX("h_fs_23_lo",2,2);
  h_fs_Nj4_lo = ((TH2D*) FshortFile->Get("h_fsMR_4_Baseline_lowpt"))->ProjectionX("h_fs_4_lo",2,2);
  h_fs_Nj1_lo->SetDirectory(0);
  h_fs_Nj23_lo->SetDirectory(0);
  h_fs_Nj4_lo->SetDirectory(0);

  const double st_Nj1_P_lo = h_fs_Nj1_lo->GetBinContent(Pidx);
  const double st_Nj1_P3_lo = h_fs_Nj1_lo->GetBinContent(P3idx);
  const double st_Nj1_P4_lo = h_fs_Nj1_lo->GetBinContent(P4idx);
  const double st_Nj1_M_lo = h_fs_Nj1_lo->GetBinContent(Midx);

  const double st_Nj23_P_lo = h_fs_Nj23_lo->GetBinContent(Pidx);
  const double st_Nj23_P3_lo = h_fs_Nj23_lo->GetBinContent(P3idx);
  const double st_Nj23_P4_lo = h_fs_Nj23_lo->GetBinContent(P4idx);
  const double st_Nj23_M_lo = h_fs_Nj23_lo->GetBinContent(Midx);

  const double st_Nj4_P_lo = h_fs_Nj4_lo->GetBinContent(Pidx);
  const double st_Nj4_P3_lo = h_fs_Nj4_lo->GetBinContent(P3idx);
  const double st_Nj4_P4_lo = h_fs_Nj4_lo->GetBinContent(P4idx);
  const double st_Nj4_M_lo = h_fs_Nj4_lo->GetBinContent(Midx);

  cout << "Loaded observed MR ST counts" << endl;

  cout << "st_Nj1_P         : " << st_Nj1_P << endl;
  cout << "st_Nj1_P3        : " << st_Nj1_P3 << endl;
  cout << "st_Nj1_P4        : " << st_Nj1_P4 << endl;
  cout << "st_Nj1_M         : " << st_Nj1_M << endl;
  cout << "st_Nj23_P        : " << st_Nj23_P << endl;
  cout << "st_Nj23_P3       : " << st_Nj23_P3 << endl;
  cout << "st_Nj23_P4       : " << st_Nj23_P4 << endl;
  cout << "st_Nj23_M        : " << st_Nj23_M << endl;
  cout << "st_Nj4_P         : " << st_Nj4_P << endl;
  cout << "st_Nj4_P3        : " << st_Nj4_P3 << endl;
  cout << "st_Nj4_P4        : " << st_Nj4_P4 << endl;
  cout << "st_Nj4_M         : " << st_Nj4_M << endl;

  cout << "/nHi Pt/n" << endl;

  cout << "st_Nj1_P         : " << st_Nj1_P_hi << endl;
  cout << "st_Nj1_P3        : " << st_Nj1_P3_hi << endl;
  cout << "st_Nj1_P4        : " << st_Nj1_P4_hi << endl;
  cout << "st_Nj1_M         : " << st_Nj1_M_hi << endl;
  cout << "st_Nj23_P        : " << st_Nj23_P_hi << endl;
  cout << "st_Nj23_P3       : " << st_Nj23_P3_hi << endl;
  cout << "st_Nj23_P4       : " << st_Nj23_P4_hi << endl;
  cout << "st_Nj23_M        : " << st_Nj23_M_hi << endl;
  cout << "st_Nj4_P         : " << st_Nj4_P_hi << endl;
  cout << "st_Nj4_P3        : " << st_Nj4_P3_hi << endl;
  cout << "st_Nj4_P4        : " << st_Nj4_P4_hi << endl;
  cout << "st_Nj4_M         : " << st_Nj4_M_hi << endl;

  cout << "/nLow Pt/n" << endl;

  cout << "st_Nj1_P         : " << st_Nj1_P_lo << endl;
  cout << "st_Nj1_P3        : " << st_Nj1_P3_lo << endl;
  cout << "st_Nj1_P4        : " << st_Nj1_P4_lo << endl;
  cout << "st_Nj1_M         : " << st_Nj1_M_lo << endl;
  cout << "st_Nj23_P        : " << st_Nj23_P_lo << endl;
  cout << "st_Nj23_P3       : " << st_Nj23_P3_lo << endl;
  cout << "st_Nj23_P4       : " << st_Nj23_P4_lo << endl;
  cout << "st_Nj23_M        : " << st_Nj23_M_lo << endl;
  cout << "st_Nj4_P         : " << st_Nj4_P_lo << endl;
  cout << "st_Nj4_P3        : " << st_Nj4_P3_lo << endl;
  cout << "st_Nj4_P4        : " << st_Nj4_P4_lo << endl;
  cout << "st_Nj4_M         : " << st_Nj4_M_lo << endl;

  unordered_map<TH3D*,TH1D*> obs_mr_st;
  obs_mr_st[h_fracFS_1] = h_fs_Nj1;
  obs_mr_st[h_fracFS_23] = h_fs_Nj23;
  obs_mr_st[h_fracFS_4] = h_fs_Nj4;
  obs_mr_st[h_fracFS_1_lo] = h_fs_Nj1_lo;
  obs_mr_st[h_fracFS_23_lo] = h_fs_Nj23_lo;
  obs_mr_st[h_fracFS_4_lo] = h_fs_Nj4_lo;
  obs_mr_st[h_fracFS_1_hi] = h_fs_Nj1_hi;
  obs_mr_st[h_fracFS_23_hi] = h_fs_Nj23_hi;
  obs_mr_st[h_fracFS_4_hi] = h_fs_Nj4_hi;

  FshortFile->Close();

  const unsigned int nEventsTree = ch->GetEntries();
  cout << nEventsTree << " events in chain" << endl;
  int nDuplicates = 0; int numberOfAllSTs = 0; int numberOfAllSTCs = 0; int numberOfUnmatchedSTs = 0; int numberOfUnmatchedSTCs = 0;
  int GoodEventCounter = 0;
  for( unsigned int event = 0; event < nEventsTree; ++event) {    
  //  for( unsigned int event = 0; event < 10000; ++event) {    
    //    if (event % 1000 == 0) cout << 100.0 * event / nEventsTree  << "%" << endl;

    t.GetEntry(event); 

    const float lumi = config_.lumi; 
    int bin_xsec = h_xsec->GetXaxis()->FindBin(t.GenSusyMScan1);      
    const float xs = h_xsec->GetBinContent(bin_xsec);
    int binx = h_sig_nevents_->GetXaxis()->FindBin(t.GenSusyMScan1);
    int biny = h_sig_nevents_->GetYaxis()->FindBin(t.GenSusyMScan2);
    double nevents = h_sig_nevents_->GetBinContent(binx,biny);

    float weight = lumi * xs * 1000 / nevents;
    
    if(applyL1PrefireWeights && (config_.year==2016 || config_.year==2017) && config_.cmssw_ver!=80) {
      weight *= t.weight_L1prefire;
    }
    
    if (doNTrueIntReweight) {
      if(h_nTrueInt_weights_==0){
	cout << "[ShortTrackLooper::loop] WARNING! You requested to do nTrueInt reweighting but didn't supply a PU weights file. Turning off." << endl;
      }else{
	int nTrueInt_input = t.nTrueInt;
	float puWeight = h_nTrueInt_weights_->GetBinContent(h_nTrueInt_weights_->FindBin(nTrueInt_input));
	weight *= puWeight;
      }
    }

    if (applyISRWeights && !noISR) {
      int binx = h_sig_avgweight_isr_->GetXaxis()->FindBin(t.GenSusyMScan1);
      int biny = h_sig_avgweight_isr_->GetYaxis()->FindBin(t.GenSusyMScan2);
      float avgweight_isr = h_sig_avgweight_isr_->GetBinContent(binx,biny);
      float weight_isr = t.weight_isr / avgweight_isr;
      weight *= weight_isr;
    }

    double weight_adj = 1;
    double ch_1_decay_factor = -999.0;
    double ch_2_decay_factor = -999.0;
    if (ctau_in != ctau_out) {
      for (int ic = 0; ic < t.nCharginos; ic++) {
	double ch_decayXY = t.chargino_decayXY[ic];
	double ch_decayZ = t.chargino_decayZ[ic];
	// double ch_theta = Theta(t.chargino_eta[ic]);       
	// double boosted_ch_decay_length = ch_decayXY/TMath::Sin(ch_theta);	
	double boosted_ch_decay_length = TMath::Sqrt(ch_decayXY*ch_decayXY + ch_decayZ*ch_decayZ);
	//	double p = t.chargino_pt[ic] / ch_theta;
	double p = t.chargino_pt[ic] / ch_decayXY * boosted_ch_decay_length;
	double gamma = TMath::Sqrt(p*p/(t.GenSusyMScan2 * t.GenSusyMScan2) + 1);
	double betaC = TMath::Sqrt(1-1/gamma/gamma) * TMath::C() * 100; // *100 to convert to cm/s
	h_beta->Fill(TMath::Sqrt(1-1/gamma/gamma),t.GenSusyMScan1,t.GenSusyMScan2);
	double boosted_ch_lifetime = boosted_ch_decay_length / betaC;
	double ch_lifetime = boosted_ch_lifetime / gamma;	
	if (ch_decayXY > 10) {
	  h_decay_factor->Fill(ch_lifetime/tau_in,t.GenSusyMScan1,t.GenSusyMScan2);
	}
	if (ic == 0) ch_1_decay_factor = ch_lifetime/tau_in;
	else ch_2_decay_factor = ch_lifetime/tau_in;
	double new_prob = 1/tau_out * TMath::Exp(-ch_lifetime / tau_out);
	double old_prob = 1/tau_in * TMath::Exp(-ch_lifetime / tau_in);
	double weight_adjustment = new_prob / old_prob;
	weight *= weight_adjustment;
	weight_adj *= weight_adjustment;
	/*
	if (ch_decayXY > 0) {
	  cout << "ch_decayXY = " << ch_decayXY << endl;
	  cout << "ch_theta = " << ch_theta << endl;
	  cout << "boosted_ch_DL = " << boosted_ch_decay_length << endl;
	  cout << "p = " << p << endl;
	  cout << "gamma = " << gamma << endl;
	  cout << "betaC = " << betaC << endl;
	  cout << "ch_tau = " << ch_lifetime << endl;
	  cout << "tau_in = " << tau_in << endl;
	  cout << "tau_out = " << tau_out << endl;
	  cout << "new prob = " << new_prob << endl;
	  cout << "old prob = " << old_prob << endl;
	  cout << "weight adjustment = " << weight_adjustment << endl;
	  return 0;
	}
	*/
	h_DL_raw->Fill(ch_lifetime*betaC*gamma,t.GenSusyMScan1,t.GenSusyMScan2,1);
	h_DL->Fill(ch_lifetime*betaC*gamma,t.GenSusyMScan1,t.GenSusyMScan2,weight_adjustment);	
      }
    }

    h_weight_raw->Fill(t.GenSusyMScan1,t.GenSusyMScan2,weight/weight_adj);
    h_eff_den->Fill(t.GenSusyMScan1,t.GenSusyMScan2,weight);
    h_weight_all->Fill(TMath::Log10(weight_adj),t.GenSusyMScan1,t.GenSusyMScan2);
    h_nevents->Fill(t.GenSusyMScan1,t.GenSusyMScan2,1);    
    if (weight_adj > 10) {
      cout << "Track length reweight factor > 10: evt = " << t.evt << " (" << t.GenSusyMScan1 << ", " << t.GenSusyMScan2 << ") GeV, produces weight "
	   << weight << " from weight " << weight/weight_adj;
      if (weight > max_weight) {
	cout << ". Skipping since weight > " << max_weight << endl;
	continue;
      }
      else {
	cout << ". Allowing since weight < " << max_weight << endl;
      }
    }
    h_weight_nospikes->Fill(t.GenSusyMScan1,t.GenSusyMScan2,weight);
    h_nospikes->Fill(t.GenSusyMScan1,t.GenSusyMScan2,1);

    // skim
    if ((t.nshorttrackcandidates == 0 && t.nshorttracks == 0)  || (t.ht < 200)) continue;

    //---------------------
    // skip duplicates -- needed when running on mutiple streams in data
    //---------------------
    if( t.isData ) {
      DorkyEventIdentifier id(t.run, t.evt, t.lumi);
      if (is_duplicate(id) ){
	++nDuplicates;
	continue;
      }
    }

    //---------------------
    // basic event selection and cleaning
    //---------------------
    
    if( applyJSON && t.isData && !goodrun(t.run, t.lumi) ) continue;

    // Not a duplicate, and a good event. Counts towards our unblinded luminosity
    GoodEventCounter++;
    // 10/fb in 2016 = 10/35.9 = about 1 event in 3.6, call it 1 event in 4
    // 10/fb in 2017 = 10/42 = about 1 event in 4 
    // 10/fb in 2018 = 10/58.83 = about 1 event in 6
    bool partial_unblind = false;
    if (year == 2016 && GoodEventCounter % 4 == 0) partial_unblind = true; // about 9/fb
    else if (year == 2017 && GoodEventCounter % 4 == 0) partial_unblind = true; // about 10.5/fb
    else if (year == 2018 && GoodEventCounter % 6 == 0) partial_unblind = true; // about 9.8/fb
    /*
    if (year == 2016 && GoodEventCounter % 7 == 0) partial_unblind = true;
    else if (year == 2017 && GoodEventCounter % 8 == 0) partial_unblind = true;
    */

    if (unlikely(t.nVert == 0)) {
      continue;
    }

    if (config_.filters["eeBadScFilter"] && !t.Flag_eeBadScFilter) continue; 
    if (config_.filters["globalSuperTightHalo2016Filter"] && !t.Flag_globalSuperTightHalo2016Filter) continue; 
    if (config_.filters["globalTightHalo2016Filter"] && !t.Flag_globalTightHalo2016Filter) continue; 
    if (config_.filters["goodVertices"] && !t.Flag_goodVertices) continue;
    if (config_.filters["HBHENoiseFilter"] && !t.Flag_HBHENoiseFilter) continue;
    if (config_.filters["HBHENoiseIsoFilter"] && !t.Flag_HBHENoiseIsoFilter) continue;
    if (config_.filters["EcalDeadCellTriggerPrimitiveFilter"] && !t.Flag_EcalDeadCellTriggerPrimitiveFilter) continue;
    if (config_.filters["ecalBadCalibFilter"] && !t.Flag_ecalBadCalibFilter) continue;
    if (config_.filters["badMuonFilter"] && !t.Flag_badMuonFilter) continue;
    //    if (config_.filters["badChargedCandidateFilter"] && !t.Flag_badChargedCandidateFilter) continue; 
    if (config_.filters["badMuonFilterV2"] && !t.Flag_badMuonFilterV2) continue;
    if (config_.filters["badChargedHadronFilterV2"] && !t.Flag_badChargedHadronFilterV2) continue; 
    
    // random events with ht or met=="inf" or "nan" that don't get caught by the filters...
    if(isinf(t.met_pt) || isnan(t.met_pt) || isinf(t.ht) || isnan(t.ht)){
      cout << "WARNING: bad event with infinite MET/HT! " << t.run << ":" << t.lumi << ":" << t.evt
	   << ", met=" << t.met_pt << ", ht=" << t.ht << endl;
      continue;
    }

    // catch events with unphysical jet pt
    if(t.jet_pt[0] > 13000.){
      cout << endl << "WARNING: bad event with unphysical jet pt! " << t.run << ":" << t.lumi << ":" << t.evt
	   << ", met=" << t.met_pt << ", ht=" << t.ht << ", jet_pt=" << t.jet_pt[0] << endl;
      continue;
    }

    // apply HEM veto, and simulate effects in MC
    if(doHEMveto && config_.year == 2018){
      bool hasHEMjet = false;
      float lostHEMtrackPt = 0;
      // monojet, VL, and L HT are handled specially (lower pt threshold, and apply lostTrack veto)
      bool isLowHT = (t.nJet30==1 || (t.nlep != 2 && t.ht < 575) || (t.nlep == 2 && t.zll_ht < 575));
      float actual_HEM_ptCut = isLowHT ? 20.0 : HEM_ptCut;
      if((t.isData && t.run >= HEM_startRun) || (!t.isData && t.evt % HEM_fracDen < HEM_fracNum)){ 
	for(int i=0; i<t.njet; i++){
	  if(t.jet_pt[i] < actual_HEM_ptCut)
	    break;
	  if(t.jet_eta[i] > HEM_region[0] && t.jet_eta[i] < HEM_region[1] && 
	     t.jet_phi[i] > HEM_region[2] && t.jet_phi[i] < HEM_region[3])
	    hasHEMjet = true;
	}
	for (int i=0; i<t.ntracks; i++){
	  // Is the track in the HEM region?
	  if ( !(t.track_eta[i] > HEM_region[0] && t.track_eta[i] < HEM_region[1] &&
		 t.track_phi[i] > HEM_region[2] && t.track_phi[i] < HEM_region[3]))
	    continue;
	  // Found a track in the HEM region. Is is high enough quality to veto the event?
	  // if (!t.track_isHighPurity[i]) continue;
	  if (fabs(t.track_dz[i]) > 0.20 || fabs(t.track_dxy[i]) > 0.10) continue;
	  // if (t.track_nPixelLayersWithMeasurement[i] < 3) continue;
	  // if (t.track_nLostInnerPixelHits[i] > 0) continue;
	  // if (t.track_nLostOuterHits[i] > 2) continue;
	  // May wish to add this guy
	  //if (t.track_ptErr[i_trk] / (t.track_pt[i_trk]*t.track_pt[i_trk]) > 0.02) continue;
	  lostHEMtrackPt += t.track_pt[i];
	}
      }
      // May wish to set lostHEMtrackPt threshold to some higher value; this is equivalent to "any lost track" (saving only pT > 15 GeV tracks in babies for now)
      if(hasHEMjet || (isLowHT && lostHEMtrackPt > 0)){// cout << endl << "SKIPPED HEM EVT: " << t.run << ":" << t.lumi << ":" << t.evt << endl;
	continue;
      }
    }

    const float deltaPhiMin = useGENMET ? t.deltaPhiMin_genmet : t.deltaPhiMin;
    const float diffMetMht = useGENMET ? t.diffMetMht_genmet/t.met_genPt : t.diffMetMht/t.met_pt;
    const float mt2 = useGENMET ? t.mt2_genmet : t.mt2;
    const float met_pt = useGENMET ? t.met_genPt : t.met_pt;

    if (unlikely(t.nJet30FailId != 0)) {
      continue;
    }
      
    if (diffMetMht > 0.5) {
      continue;
    }

    if (unlikely(t.met_miniaodPt / t.met_caloPt >= 5.0)) {
      continue;
    }
    if (unlikely(t.nJet200MuFrac50DphiMet > 0)) {
      continue;
    }
    
    const bool lepveto = t.nMuons10 + t.nElectrons10 + t.nPFLep5LowMT + t.nPFHad10LowMT > 0;

    int nLongCharginos = 0;
    for (int i_ch = 0; i_ch < t.nCharginos; i_ch++) {
      if (t.chargino_decayXY[i_ch] >= 490 || fabs(t.chargino_decayZ[i_ch]) >= 820) nLongCharginos++;
    }

    if (lepveto || (nLongCharginos > 0 && config_.year != 2016)) {
      continue;
    }

    if (deltaPhiMin < 0.3) {
      continue;
    }

    if (t.ht < 250) {
      continue;
    }

    if (t.nJet30 < 1) {
      continue;
    }
    else if (t.nJet30 < 2) {
      if (met_pt < 250) {
	continue;
      }
    }
    else {
      if (mt2 < 60) {
	continue;
      }
      // Let low met events through regardless of Ht if they're in MR
      if (met_pt < 30 || (t.ht < 1200 && met_pt < 250 && mt2 > 100)) {
	continue;
      }
    }

    //    const bool passPrescaleTrigger = passTrigger(t, trigs_prescaled_);
    const bool passSRTrigger = passTrigger(t, trigs_SR_);

    //    if (! (passPrescaleTrigger || passSRTrigger)) continue;
    if (!passSRTrigger) continue;

    if (weight > 1.0 && !t.isData && !isSignal && skipHighEventWeights) continue;
    
    TH3D* hist_STC;    
    TH3D* hist_ST;
    TH3D* hist_fracFS;
    
    // Monojet FIXME
    /*
    if (t.nJet30 == 1) {
      if (t.jet1_pt >= 1200) {
	hist_STC = h_1H_SR_STC;
	hist_ST = h_1H_SR_ST;
      }
      else if (t.jet1_pt >= 450) {
	hist_STC = h_1M_SR_STC;
	hist_ST = h_1M_SR_ST;
      }
      else if (t.jet1_pt >= 350) { // low Ht
	hist_STC = h_1L_SR_STC;
	hist_ST = h_1L_SR_ST;
      }
      else if (t.jet1_pt >= 250) {
      }
    }
    */
    // Just call everything the 1L region for now
    if (t.nJet30 == 1) {
      if (t.jet1_pt >= 350 && met_pt > 250 && t.ht > 250) {
	hist_STC = h_1L_SR_STC;
	hist_ST = h_1L_SR_ST;
      }
      else if (t.jet1_pt >= 275 && met_pt > 250 && t.ht > 250) {
	hist_STC = h_1L_VR_STC;
	hist_ST = h_1L_VR_ST;
      }
      else if (t.jet1_pt >= 200 && met_pt > 200 && t.ht > 200) { // low Ht
	hist_STC = h_1L_MR_STC;
	hist_ST = h_1L_MR_ST;
      }
      else {
	continue; // probably some pathological monojet event with high jet1_pt but low met and ht
      }
    }
    else if (t.nJet30 < 4) {
      // LH
      if (t.ht >= 1200) {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_LH_MR_STC;
	  hist_ST = h_LH_MR_ST;
	  hist_fracFS = h_fracFS_23;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_LH_VR_STC;
	  hist_ST = h_LH_VR_ST;
	}
	// SR 
	else { 
	  hist_STC = h_LH_SR_STC;
	  hist_ST = h_LH_SR_ST;
	}
      }
      // LM
      else if (t.ht >= 450) {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_LM_MR_STC;
	  hist_ST = h_LM_MR_ST;
	  hist_fracFS = h_fracFS_23;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_LM_VR_STC;
	  hist_ST = h_LM_VR_ST;
	}
	// SR 
	else { 
	  hist_STC = h_LM_SR_STC;
	  hist_ST = h_LM_SR_ST;
	}
      }
      // LL
      else {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_LL_MR_STC;
	  hist_ST = h_LL_MR_ST;
	  hist_fracFS = h_fracFS_23;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_LL_VR_STC;
	  hist_ST = h_LL_VR_ST;
	}
	// SR 
	else { 
	  hist_STC = h_LL_SR_STC;
	  hist_ST = h_LL_SR_ST;
	}
      }
    } 
    // H*
    else {
      // HH
      if (t.ht >= 1200) {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_HH_MR_STC;
	  hist_ST = h_HH_MR_ST;
	  hist_fracFS = h_fracFS_4;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_HH_VR_STC;
	  hist_ST = h_HH_VR_ST;
	}
	// SR 
	else {
	  hist_STC = h_HH_SR_STC;
	  hist_ST = h_HH_SR_ST;
	}
      }
      // HM
      else if (t.ht >= 450) {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_HM_MR_STC;
	  hist_ST = h_HM_MR_ST;
	  hist_fracFS = h_fracFS_4;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_HM_VR_STC;
	  hist_ST = h_HM_VR_ST;
	}
	// SR 
	else {
	  hist_STC = h_HM_SR_STC;
	  hist_ST = h_HM_SR_ST;
	}
      }
      // HL
      else {
	// MR
	if (mt2 < 100) {
	  hist_STC = h_HL_MR_STC;
	  hist_ST = h_HL_MR_ST;
	  hist_fracFS = h_fracFS_4;
	}
	// VR
	else if (mt2 < 200) {
	  hist_STC = h_HL_VR_STC;
	  hist_ST = h_HL_VR_ST;
	}
	// SR 
	else { //if (! (blind && t.isData) ){
	  hist_STC = h_HL_SR_STC;
	  hist_ST = h_HL_SR_ST;
	}
      }
    }

    bool doContam = mt2 < 100 && t.nJet30 > 1;

    // Analysis code

    int nSTCp = t.nshorttrackcandidates_P;
    // TODO: add these guys to babies
    int nSTCp3 = 0;
    int nSTCp4 = 0;
    int nSTCm = t.nshorttrackcandidates_M;
    int nSTCl_acc = 0; // L STCs, accepted by mtpt
    int nSTCl_rej = 0; // L STCs, rejected by mtpt
    int nSTp = t.nshorttracks_P;
    int nSTp3 = 0;
    int nSTp4 = 0;
    int nSTm = t.nshorttracks_M;
    int nSTl_acc = 0; // L STs, accepted by mtpt
    int nSTl_rej = 0; // L STs, rejected by mtpt
    // hi pt
    int nSTCp_hi = 0;
    int nSTCp3_hi = 0;
    int nSTCp4_hi = 0;
    int nSTCm_hi = 0;
    int nSTp_hi = 0;
    int nSTp3_hi = 0;
    int nSTp4_hi = 0;
    int nSTm_hi = 0;
    // lo pt
    int nSTCp_lo = 0;
    int nSTCp3_lo = 0;
    int nSTCp4_lo = 0;
    int nSTCm_lo = 0;
    int nSTp_lo = 0;
    int nSTp3_lo = 0;
    int nSTp4_lo = 0;
    int nSTm_lo = 0;


    // Need to do a little loop for L ST(C)s even if not recalculating, to see who passed and didn't pass mtpt veto
    if (!recalculate) {
      for (int i_trk = 0; i_trk < t.ntracks; i_trk++) {
	// L ST
	if (t.track_islong[i_trk]) {
	  MT( t.track_pt[i_trk], t.track_phi[i_trk], met_pt, t.met_phi ) < 100 && t.track_pt[i_trk] < 150 ? nSTl_rej++ : nSTl_acc++;
	} 
	else if (t.track_islongcandidate[i_trk]) {
	  MT( t.track_pt[i_trk], t.track_phi[i_trk], met_pt, t.met_phi ) < 100 && t.track_pt[i_trk] < 150 ? nSTCl_rej++ : nSTCl_acc++;
	}
      }
    }
    else {
      // Manual calculation for testing new ST/STC definitions not coded in babymaker
      nSTCp = 0;
      nSTCp3 = 0;
      nSTCp4 = 0;
      nSTCm = 0;
      nSTCl_rej = 0;
      nSTCl_acc = 0;
      nSTp = 0;
      nSTp3 = 0;
      nSTp4 = 0;
      nSTm = 0;      
      nSTl_rej = 0;
      nSTl_acc = 0;

      bool overlapping_track[t.ntracks];
      for (int i_trk = 0; i_trk < t.ntracks; i_trk++) {
	overlapping_track[i_trk] = false;
      }
      for (int i_trk = 0; i_trk < t.ntracks; i_trk++) {
	for (int j_trk = i_trk + 1; j_trk < t.ntracks; j_trk++) {
	  if (DeltaR(t.track_eta[i_trk],t.track_eta[j_trk],t.track_phi[i_trk],t.track_phi[j_trk]) < 0.1) {
	    overlapping_track[i_trk] = true;
	    overlapping_track[j_trk] = true;
	  }
	}
      }
      
      for (int i_trk = 0; i_trk < t.ntracks; i_trk++) {   

	if (overlapping_track[i_trk]) continue; // veto any tracks closely overlapping other lost tracks (pt > 15 GeV, with iso cut for 15-20 GeV)

	int charginoMatch = t.track_matchedCharginoIdx[i_trk];
	bool isChargino = isSignal && charginoMatch >= 0;
	if (isSignal && !isChargino) {
	  for (int i_chargino = 0; i_chargino < t.nCharginos; i_chargino++) {
	    if (DeltaR(t.track_eta[i_trk],t.chargino_eta[i_chargino],t.track_phi[i_trk],t.chargino_phi[i_chargino]) < 0.1) {
	      isChargino = true;
	      charginoMatch = i_chargino;
	      break;
	    }
	  }
	}

	int lenIndex = -1;
	bool isST = false, isSTC = false;
	
	// Apply basic selections
	const bool CaloSel = !(t.track_DeadECAL[i_trk] || t.track_DeadHCAL[i_trk]) && InEtaPhiVetoRegion(t.track_eta[i_trk],t.track_phi[i_trk],year) == 0;
	const float pt = t.track_pt[i_trk];
	const bool ptSel = pt >= 15.0;
	const bool etaSel = fabs(t.track_eta[i_trk]) <= 2.4;
	const bool BaseSel = CaloSel && ptSel && etaSel;
	
	if (!BaseSel) {
	  continue;
	}
	
	// Length and category
	// Length and categorization
	const bool lostOuterHitsSel = t.track_nLostOuterHits[i_trk] >= 2;
	const int nLayers = t.track_nLayersWithMeasurement[i_trk];
	const bool isP = nLayers == t.track_nPixelLayersWithMeasurement[i_trk] && lostOuterHitsSel && nLayers >= (increment17 ? (year == 2016 ? 3 : 4) : 3);
	const bool isLong = nLayers >= 7;
	const bool isM = nLayers != t.track_nPixelLayersWithMeasurement[i_trk] && !isLong && lostOuterHitsSel;
	const bool isL = isLong && lostOuterHitsSel;
	const bool isShort = isP || isM || isL;
	if (!isShort) {
	  continue;
	}
	
	lenIndex = isP ? 1 : (isM ? 2 : 3);
	
	if (applyRecoVeto == 1) {	
	  const float nearestPF_DR = t.track_nearestPF_DR[i_trk];
	  const int nearestPF_id = abs(t.track_nearestPF_id[i_trk]);
	  const bool nearestPFSel = !(nearestPF_DR < 0.1 && (nearestPF_id == 11 || nearestPF_id == 13));
	  float mindr = 100;
	  for (int iL = 0; iL < t.nlep; iL++) {
	    float dr = DeltaR(t.lep_eta[iL],t.track_eta[i_trk],t.lep_phi[iL],t.track_phi[i_trk]);
	    if (mindr < dr) mindr = dr;
	  }
	  const float minrecodr = mindr;
	  const bool recoVeto = minrecodr < 0.1;
	  const bool PassesRecoVeto = !recoVeto && nearestPFSel && !t.track_isLepOverlap[i_trk];
	  if (!PassesRecoVeto) {
	    continue;
	  }	  
	}
	else if (applyRecoVeto == 2) {
	  const bool PassesRecoVeto = t.track_recoveto[i_trk] == 0;
	  if (!PassesRecoVeto) {
	    continue;
	  }
	} else {
	  // do nothing
	}
	
	// Isolation
	const float niso = t.track_neuIso0p05[i_trk];
	const bool NeuIso0p05Sel = niso < 10;
	const bool NeuIso0p05SelSTC = niso < 10*isoSTC;
	const float nreliso = t.track_neuRelIso0p05[i_trk];
	const bool NeuRelIso0p05Sel =  nreliso < 0.1;
	const bool NeuRelIso0p05SelSTC = nreliso < 0.1*isoSTC;
	const float iso = t.track_iso[i_trk];
	const bool isoSel = iso < 10;
	const bool isoSelSTC = iso < 10 * isoSTC;
	const float reliso = t.track_reliso[i_trk];
	const bool relisoSel = reliso < 0.2;
	const bool relisoSelSTC = reliso < 0.2 * isoSTC;
	const bool PassesFullIsoSel = NeuIso0p05Sel && NeuRelIso0p05Sel && isoSel && relisoSel;
	const bool PassesFullIsoSelSTC = NeuIso0p05SelSTC && NeuRelIso0p05SelSTC && isoSelSTC && relisoSelSTC;
	
	if (!PassesFullIsoSelSTC) {
	  continue;
	}
	
	// Quality
	const bool pixLayersSelLoose = t.track_nPixelLayersWithMeasurement[i_trk] >= 2;
	const bool pixLayersSelTight = t.track_nPixelLayersWithMeasurement[i_trk] >= 3;
	const bool pixLayersSel4 = nLayers > 4 ? pixLayersSelLoose : pixLayersSelTight; // Apply 2 layer selection to tracks with 5 or more layers
	
	const int lostInnerHits = t.track_nLostInnerPixelHits[i_trk];
	const bool lostInnerHitsSel = lostInnerHits == 0;
	const float pterr = t.track_ptErr[i_trk];
	const float pterrOverPt2 = pterr / (pt*pt);
	const bool pterrSelLoose = pterrOverPt2 <= 0.2;
	const bool pterrSelMedium = pterrOverPt2 <= 0.02;
	const bool pterrSelTight = pterrOverPt2 <= 0.005;
	const bool pterrSelLooseSTC = pterrOverPt2 <= 0.2 * qualSTC;
	const bool pterrSelMediumSTC = pterrOverPt2 <= 0.02 * qualSTC;
	const bool pterrSelTightSTC = pterrOverPt2 <= 0.005 * qualSTC;
	bool pterrSel = pterrSelTight;
	bool pterrSelSTC = pterrSelTightSTC;
	if (isP) {pterrSel = pterrSelLoose; pterrSelSTC = pterrSelLooseSTC;}
	else if (nLayers < 7) {pterrSel = pterrSelMedium; pterrSelSTC = pterrSelMediumSTC;}
	const float dxy = fabs(t.track_dxy[i_trk]);
	const bool dxySelLoose = dxy < 0.02;
	const bool dxySelLooseSTC = dxy < 0.02 * qualSTC;
	const bool dxySelTight = dxy < 0.01;
	const bool dxySelTightSTC = dxy < 0.01 * qualSTC;
	const bool dxySel = isP ? dxySelLoose : dxySelTight;
	const bool dxySelSTC = isP ? dxySelLooseSTC : dxySelTightSTC;
	const float dz = fabs(t.track_dz[i_trk]);
	const bool dzSel = dz < 0.05;
	const bool dzSelSTC = dz < 0.05*qualSTC;
	const bool isHighPurity = t.track_isHighPurity[i_trk] == 1;
	const bool QualityTrackBase = lostInnerHitsSel && pterrSel && isHighPurity && dxySel && dzSel;
	const bool QualityTrackSTCBase =  lostInnerHitsSel && pterrSelSTC && isHighPurity && dxySelSTC && dzSelSTC;
	const bool isQualityTrack = pixLayersSel4 && QualityTrackBase;
	const bool isQualityTrackSTC = pixLayersSel4 && QualityTrackSTCBase;
	
	if (!isQualityTrackSTC) {
	  continue;
	}
	
	// Full Short Track
	isST = PassesFullIsoSel && isQualityTrack;
	
	// Candidate (loosened isolation, quality)...already checked for Iso and Quality above
	isSTC = !isST;
	//	isSTC = !isST && (isP || iso > 30 || reliso > 0.4);
	if (! (isST || isSTC)) continue;       

	if ( isST && (blind && t.isData && mt2 >= 200 && !partial_unblind)) {
	  continue;
	}

	const float mt = MT( t.track_pt[i_trk], t.track_phi[i_trk], met_pt, t.met_phi );	
	const bool vetoMtPt = mt < 100 && t.track_pt[i_trk] < 150;

	if (!isChargino && !(lenIndex == 3 && vetoMtPt)) {
	  isST ? numberOfUnmatchedSTs++ : numberOfUnmatchedSTCs++;
	  float fraction = isST ? (float) numberOfUnmatchedSTs / numberOfAllSTs : (float) numberOfUnmatchedSTCs / numberOfAllSTCs;
	  int nMatches = (t.chargino_matchedTrackIdx[0] >= 0 ? 1 : 0) + (t.chargino_matchedTrackIdx[1] >= 0 ? 1 : 0);
	  int nDisappearing = (t.chargino_isDisappearing[0] ? 1 : 0) + (t.chargino_isDisappearing[1] ? 1 : 0);
	  bool missingMatch = nMatches < nDisappearing;
	  float DR1 = DeltaR(t.track_eta[i_trk], t.chargino_eta[0], t.track_phi[i_trk], t.chargino_phi[0]);
	  float DR2 = DeltaR(t.track_eta[i_trk], t.chargino_eta[1], t.track_phi[i_trk], t.chargino_phi[1]);
	  cout << "Unmatched " << (isST ? "ST" : "STC") << " (" << fraction*100 << "%), " << (missingMatch  ? "Not enough chargino matches" : "Enough chargino matches") << " in this event." << endl;
	  cout << "Track: " << t.track_eta[i_trk] << ", " << t.track_phi[i_trk] << "\n"
	       << "Chargino 0 eta, phi, DR | " << t.chargino_eta[0] << ", " << t.chargino_phi[0] << " | " << DR1 << "\n"
	       << "Chargino 1 eta, phi, DR | " << t.chargino_eta[1] << ", " << t.chargino_phi[1] << " | " << DR2 << endl;
	  continue;
	}

	if (lenIndex == 3) {
	  if (vetoMtPt) {
	    if (isST) {
	      nSTl_rej++;
	    }
	    else {
	      nSTCl_rej++;
	    }
	  }
	  else {
	    if (isST) {
	      nSTl_acc++;
	      numberOfAllSTs++;
	      if (mt2 > 200) h_decay_factor_L->Fill(charginoMatch == 0 ? ch_1_decay_factor : ch_2_decay_factor,t.GenSusyMScan1,t.GenSusyMScan2);
	    }
	    else {
	      nSTCl_acc++;
	      numberOfAllSTCs++;
	    }
	  }
	}	
	else if (isSTC) {
	  numberOfAllSTCs++;
	  if (lenIndex == 1) {
	    nSTCp++; 
	    t.track_pt[i_trk] < 50 ? nSTCp_lo++ : nSTCp_hi++;
	    if (t.track_nLayersWithMeasurement[i_trk] == 3) {
	      nSTCp3++;
	      t.track_pt[i_trk] < 50 ? nSTCp3_lo++ : nSTCp3_hi++;
	    }
	    else {
	      nSTCp4++;
	      t.track_pt[i_trk] < 50 ? nSTCp4_lo++ : nSTCp4_hi++;
	    }
	  }
	  else if (lenIndex == 2) {
	    nSTCm++;
	    t.track_pt[i_trk] < 50 ? nSTCm_lo++ : nSTCm_hi++;	    
	  }
	}
	else if (isST) {
	  numberOfAllSTs++;
	  if (lenIndex == 1) {
	    nSTp++; 
	    t.track_pt[i_trk] < 50 ? nSTp_lo++ : nSTp_hi++;
	    if (t.track_nLayersWithMeasurement[i_trk] == 3) {
	      nSTp3++;
	      if (mt2 > 200) h_decay_factor_P3->Fill(charginoMatch == 0 ? ch_1_decay_factor : ch_2_decay_factor,t.GenSusyMScan1,t.GenSusyMScan2);
	      t.track_pt[i_trk] < 50 ? nSTp3_lo++ : nSTp3_hi++;
 	    }
	    else {
	      nSTp4++;
	      if (mt2 > 200) h_decay_factor_P4->Fill(charginoMatch == 0 ? ch_1_decay_factor : ch_2_decay_factor,t.GenSusyMScan1,t.GenSusyMScan2);
	      t.track_pt[i_trk] < 50 ? nSTp4_lo++ : nSTp4_hi++;
	    }
	  }
	  else if (lenIndex == 2) {
	    nSTm++;
	    if (mt2 > 200) h_decay_factor_M->Fill(charginoMatch == 0 ? ch_1_decay_factor : ch_2_decay_factor,t.GenSusyMScan1,t.GenSusyMScan2);
	    t.track_pt[i_trk] < 50 ? nSTm_lo++ : nSTm_hi++;
	  }
	}
      } // Track loop
    } // recalculate
    
    if (nSTl_acc + nSTm + nSTp > 1) {
      h_eff_num->Fill(t.GenSusyMScan1,t.GenSusyMScan2,weight);
      h_weight_acc->Fill(TMath::Log10(weight_adj),t.GenSusyMScan1,t.GenSusyMScan2);
    }

    if (prioritize) {
      if (nSTl_acc + nSTm + nSTp > 1) {
	// if has ST, don't count STCs
	nSTCl_acc = 0;
	nSTCm = 0; nSTCm_hi = 0; nSTCm_lo = 0;
	nSTCp = 0; nSTCp_hi = 0; nSTCp_lo = 0;
	nSTCp3 = 0; nSTCp3_hi = 0; nSTCp3_lo = 0;
	nSTCp4 = 0; nSTCp4_hi = 0; nSTCp4_lo = 0;
	if (nSTl_acc > 0) {
	  nSTl_acc = 1;
	  nSTm = 0; nSTm_hi = 0; nSTm_lo = 0;
	  nSTp = 0; nSTp_hi = 0; nSTp_lo = 0;
	  nSTp3 = 0; nSTp3_hi = 0; nSTp3_lo = 0;
	  nSTp4 = 0; nSTp4_hi = 0; nSTp4_lo = 0;
	}
	if (nSTm > 0) {
	  nSTm = 1; nSTm_hi = 0; nSTm_lo = 0;
	  if (nSTm_hi > 0) {nSTm_hi = 1; nSTm_lo = 0;} else {nSTm_lo = 1;}
	  nSTp = 0; nSTp_hi = 0; nSTp_lo = 0;
	  nSTp3 = 0; nSTp3_hi = 0; nSTp3_lo = 0;
	  nSTp4 = 0; nSTp4_hi = 0; nSTp4_lo = 0;
	}
	if (nSTp > 0) {
	  nSTp = 1; 
	  if (nSTp_hi > 0) {nSTp_hi = 1; nSTp_lo = 0;} else {nSTp_lo = 1;}
	  if (nSTp4 > 0) {
	    nSTp4 = 1; 
	    if (nSTp4_hi > 0) {nSTp4_hi = 1; nSTp4_lo = 0;} else {nSTp4_lo = 1;}
	    nSTp3 = 0; nSTp3_hi = 0; nSTp3_lo = 0;
	  }
	  else {
	    nSTp3 = 1; 
	    if (nSTp3_hi > 0) {nSTp3_hi = 1; nSTp3_lo = 0;} else {nSTp3_lo = 1;} 
	  }
	}
      }
      else if (nSTCl_acc + nSTCm + nSTCp > 1) {
	if (nSTCl_acc > 0) {
	  nSTCl_acc = 1;
	  nSTCm = 0; nSTCm_hi = 0; nSTCm_lo = 0;
	  nSTCp = 0; nSTCp_hi = 0; nSTCp_lo = 0;
	  nSTCp3 = 0; nSTCp3_hi = 0; nSTCp3_lo = 0;
	  nSTCp4 = 0; nSTCp4_hi = 0; nSTCp4_lo = 0;
	}
	if (nSTCm > 0) {
	  nSTCm = 1; nSTCm_hi = 0; nSTCm_lo = 0;
	  if (nSTCm_hi > 0) {nSTCm_hi = 1; nSTCm_lo = 0;} else {nSTCm_lo = 1;}
	  nSTCp = 0; nSTCp_hi = 0; nSTCp_lo = 0;
	  nSTCp3 = 0; nSTCp3_hi = 0; nSTCp3_lo = 0;
	  nSTCp4 = 0; nSTCp4_hi = 0; nSTCp4_lo = 0;
	}
	if (nSTCp > 0) {
	  nSTCp = 1; 
	  if (nSTCp_hi > 0) {nSTCp_hi = 1; nSTCp_lo = 0;} else {nSTCp_lo = 1;}
	  if (nSTCp4 > 0) {
	    nSTCp4 = 1; 
	    if (nSTCp4_hi > 0) {nSTCp4_hi = 1; nSTCp4_lo = 0;} else {nSTCp4_lo = 1;}
	    nSTCp3 = 0; nSTCp3_hi = 0; nSTCp3_lo = 0;
	  }
	  else {
	    nSTCp3 = 1; 
	    if (nSTCp3_hi > 0) {nSTCp3_hi = 1; nSTCp3_lo = 0;} else {nSTCp3_lo = 1;} 
	  }
	}
      }
    }

    if (nSTCl_acc + nSTCm + nSTCp == 2 && EventWise) {
      cout << "2 STC, P3: " << nSTCp3 << " P4: " << nSTCp4 << " M: " << nSTCm << " L: " << nSTCl_acc << " in " << t.run << ":" << t.lumi << ":" << t.evt;
      /*
      float pred_weight = weight;
      pred_weight *= pow(fs_L,nSTCl_acc);
      pred_weight *= pow(fs_M,nSTCm);
      if (year == 2016) {
	pred_weight *= pow(fs_P,nSTCp);
      }
      else {
	pred_weight *= pow(fs_P3,nSTCp3);
	pred_weight *= pow(fs_P4,nSTCp4);
      }

      if (mt2 < 100) {
	cout << ", MR" << endl;
       	h_2STC_MR->Fill(0.0,2.0,weight);
	h_2STC_MR->Fill(0.0,1.0,pred_weight);
      }
      else if (mt2 < 200) {
	cout << ", VR" << endl;
	h_2STC_VR->Fill(0.0,2.0,weight);
	h_2STC_VR->Fill(0.0,1.0,pred_weight);
      }
      else {
	cout << ", SR" << endl;
	h_2STC_SR->Fill(0.0,2.0,weight);
	h_2STC_SR->Fill(0.0,1.0,pred_weight);
      }
      */
    }
    else if (nSTCl_acc + nSTCm + nSTCp >= 1) { // we fill here if track count == 1 if filling EventWise, and for any track count if filling TrackWise. Can safely multiply by Nstc.
      if (nSTCl_acc > 0) {
	// For L tracks, we fill separately based on MtPt veto region, and extrapolate from STCs to STs based on M fshort
	hist_STC->Fill(4.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCl_acc);
      }
      if (nSTCm > 0) {
	hist_STC->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCm);
      }
      if (nSTCp > 0) {
	hist_STC->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp);
      }
      if (nSTCp3 > 0) {
	hist_STC->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp3);
      }
      if (nSTCp4 > 0) {
	hist_STC->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp4);
      }
    }
    else if (nSTCl_acc + nSTCm + nSTCp > 2) {
      cout << "More than 2 STCs!" << endl;
    }
    
    if (nSTl_acc + nSTm + nSTp > 1 && EventWise) {
      cout << "2 ST, P3: " << nSTp3 << " P4: " << nSTp4 << " M: " << nSTm << " L: " << nSTl_acc << " in " << t.run << ":" << t.lumi << ":" << t.evt;
      /*
      if (mt2 < 100) {
	cout << ", MR" << endl;
	h_2STC_MR->Fill(0.0,0.0,weight);
      }
      else if (mt2 < 200) {
	cout << ", VR" << endl;
	h_2STC_VR->Fill(0.0,0.0,weight);
      }
      else {
	cout << ", SR" << endl;
	h_2STC_SR->Fill(0.0,0.0,weight);
      }
      */
    }
    else { // If nST > 1, we only fill here if filling trackwise; can safely multiply by Nst.
      if (nSTl_acc > 0) {
	hist_ST->Fill(4.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTl_acc);
      }
      if (nSTm > 0) {
	hist_ST->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm);
	if (doContam) {
	  // Fill both M and L here, since L fshort is based on data M STs, not L
	  double n_obs_ST = obs_mr_st[hist_fracFS]->GetBinContent(Midx);
	  hist_fracFS->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm/n_obs_ST);
	  hist_fracFS->Fill(4.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm/n_obs_ST);
	}
      }
      if (nSTp > 0) {
	hist_ST->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp);
	if (doContam) {
	  double n_obs_ST = obs_mr_st[hist_fracFS]->GetBinContent(Pidx);
	  hist_fracFS->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp/n_obs_ST);
	}
      }
      if (nSTp3 > 0) {
	hist_ST->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3);
	if (doContam) {
	  double n_obs_ST = obs_mr_st[hist_fracFS]->GetBinContent(P3idx);
	  hist_fracFS->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3/n_obs_ST);
	}
      }
      if (nSTp4 > 0) {
	hist_ST->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4);
	if (doContam) {
	  double n_obs_ST = obs_mr_st[hist_fracFS]->GetBinContent(P4idx);
	  hist_fracFS->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4/n_obs_ST);
	}
      }
    }

    // Low pt
    TH3D* hist_STC_lo = low_hists[hist_STC];
    TH3D* hist_ST_lo = low_hists[hist_ST];
    TH3D* hist_fracFS_lo;
    if (doContam) hist_fracFS_lo = low_hists[hist_fracFS];
    // STC fills
    if (nSTCm_lo > 0) {
      hist_STC_lo->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCm_lo);
    }
    if (nSTCp_lo > 0) {
      hist_STC_lo->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp_lo);
    }
    if (nSTCp3_lo > 0) {
      hist_STC_lo->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp3_lo);
    }
    if (nSTCp4_lo > 0) {
      hist_STC_lo->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp4_lo);
    }
    
    // ST fills
    if (nSTm_lo > 0) {
      hist_ST_lo->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_lo);
      // Fill both M and L here, since L fshort is based on data M STs, not L
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_lo]->GetBinContent(Midx);
	hist_fracFS_lo->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_lo/n_obs_ST);
	hist_fracFS_lo->Fill(4.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_lo/n_obs_ST);
      }
    }
    if (nSTp_lo > 0) {
      hist_ST_lo->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp_lo);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_lo]->GetBinContent(Pidx);
	hist_fracFS_lo->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp_lo/n_obs_ST);
      }
    }
    if (nSTp3_lo > 0) {
      hist_ST_lo->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3_lo);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_lo]->GetBinContent(P3idx);
	hist_fracFS_lo->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3_lo/n_obs_ST);
      }
    }
    if (nSTp4_lo > 0) {
      hist_ST_lo->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4_lo);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_lo]->GetBinContent(P4idx);
	hist_fracFS_lo->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4_lo/n_obs_ST);
      }
    }

    // High pt
    TH3D* hist_STC_hi = hi_hists[hist_STC];
    TH3D* hist_ST_hi = hi_hists[hist_ST];
    TH3D* hist_fracFS_hi;
    if (doContam) hist_fracFS_hi = hi_hists[hist_fracFS];
    // STC fills
    if (nSTCm_hi > 0) {
      hist_STC_hi->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCm_hi);
    }
    if (nSTCp_hi > 0) {
      hist_STC_hi->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp_hi);
    }
    if (nSTCp3_hi > 0) {
      hist_STC_hi->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp3_hi);
    }
    if (nSTCp4_hi > 0) {
      hist_STC_hi->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTCp4_hi);
    }
    
    // ST fills
    if (nSTm_hi > 0) {
      hist_ST_hi->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_hi);
      // Fill both M and L here, since L fshort is based on data M STs, not L
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_hi]->GetBinContent(Midx);
	hist_fracFS_hi->Fill(3.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_hi/n_obs_ST);
	hist_fracFS_hi->Fill(4.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTm_hi/n_obs_ST);
      }
    }
    if (nSTp_hi > 0) {
      hist_ST_hi->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp_hi);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_hi]->GetBinContent(Pidx);
	hist_fracFS_hi->Fill(0.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp_hi/n_obs_ST);
      }
    }
    if (nSTp3_hi > 0) {
      hist_ST_hi->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3_hi);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_hi]->GetBinContent(P3idx);
	hist_fracFS_hi->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp3_hi/n_obs_ST);
      }
    }
    if (nSTp4_hi > 0) {
      hist_ST_hi->Fill(2.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4_hi);
      if (doContam) {
	double n_obs_ST = obs_mr_st[hist_fracFS_hi]->GetBinContent(P4idx);
	hist_fracFS_hi->Fill(1.5,t.GenSusyMScan1,t.GenSusyMScan2,weight*nSTp4_hi/n_obs_ST);
      }
    }

  }//end loop on events in a file

  // Post-process

  // STCs
  TH3D* h_1LM_SR_STC = (TH3D*) h_1L_SR_STC->Clone("h_1LM_SR_STC");
  h_1LM_SR_STC->Add(h_1M_SR_STC);
  TH3D* h_1LM_VR_STC = (TH3D*) h_1L_VR_STC->Clone("h_1LM_VR_STC");
  h_1LM_VR_STC->Add(h_LM_VR_STC);
  TH3D* h_1LM_MR_STC = (TH3D*) h_1L_MR_STC->Clone("h_1LM_MR_STC");
  h_1LM_MR_STC->Add(h_1M_MR_STC);
  TH3D* h_LLM_SR_STC = (TH3D*) h_LL_SR_STC->Clone("h_LLM_SR_STC");
  h_LLM_SR_STC->Add(h_LM_SR_STC);
  TH3D* h_LLM_VR_STC = (TH3D*) h_LL_VR_STC->Clone("h_LLM_VR_STC");
  h_LLM_VR_STC->Add(h_LM_VR_STC);
  TH3D* h_LLM_MR_STC = (TH3D*) h_LL_MR_STC->Clone("h_LLM_MR_STC");
  h_LLM_MR_STC->Add(h_LM_MR_STC);
  TH3D* h_HLM_SR_STC = (TH3D*) h_HL_SR_STC->Clone("h_HLM_SR_STC");
  h_HLM_SR_STC->Add(h_HM_SR_STC);
  TH3D* h_HLM_VR_STC = (TH3D*) h_HL_VR_STC->Clone("h_HLM_VR_STC");
  h_HLM_VR_STC->Add(h_HM_VR_STC);
  TH3D* h_HLM_MR_STC = (TH3D*) h_HL_MR_STC->Clone("h_HLM_MR_STC");
  h_HLM_MR_STC->Add(h_HM_MR_STC);

  TH3D* h_1LM_SR_hi_STC = (TH3D*) h_1L_SR_hi_STC->Clone("h_1LM_SR_hi_STC");
  h_1LM_SR_hi_STC->Add(h_1M_SR_hi_STC);
  hi_hists[h_1LM_SR_STC] = h_1LM_SR_hi_STC;
  TH3D* h_1LM_VR_hi_STC = (TH3D*) h_LL_VR_hi_STC->Clone("h_1LM_VR_hi_STC");
  h_1LM_VR_hi_STC->Add(h_LM_VR_hi_STC);
  hi_hists[h_1LM_VR_STC] = h_1LM_VR_hi_STC;
  TH3D* h_1LM_MR_hi_STC = (TH3D*) h_LL_MR_hi_STC->Clone("h_1LM_MR_hi_STC");
  h_1LM_MR_hi_STC->Add(h_LM_MR_hi_STC);
  hi_hists[h_1LM_MR_STC] = h_1LM_MR_hi_STC;
  TH3D* h_LLM_SR_hi_STC = (TH3D*) h_LL_SR_hi_STC->Clone("h_LLM_SR_hi_STC");
  h_LLM_SR_hi_STC->Add(h_LM_SR_hi_STC);
  hi_hists[h_LLM_SR_STC] = h_LLM_SR_hi_STC;
  TH3D* h_LLM_VR_hi_STC = (TH3D*) h_LL_VR_hi_STC->Clone("h_LLM_VR_hi_STC");
  h_LLM_VR_hi_STC->Add(h_LM_VR_hi_STC);
  hi_hists[h_LLM_VR_STC] = h_LLM_VR_hi_STC;
  TH3D* h_LLM_MR_hi_STC = (TH3D*) h_LL_MR_hi_STC->Clone("h_LLM_MR_hi_STC");
  h_LLM_MR_hi_STC->Add(h_LM_MR_hi_STC);
  hi_hists[h_LLM_MR_STC] = h_LLM_MR_hi_STC;
  TH3D* h_HLM_SR_hi_STC = (TH3D*) h_HL_SR_hi_STC->Clone("h_HLM_SR_hi_STC");
  h_HLM_SR_hi_STC->Add(h_HM_SR_hi_STC);
  hi_hists[h_HLM_SR_STC] = h_HLM_SR_hi_STC;
  TH3D* h_HLM_VR_hi_STC = (TH3D*) h_HL_VR_hi_STC->Clone("h_HLM_VR_hi_STC");
  h_HLM_VR_hi_STC->Add(h_HM_VR_hi_STC);
  hi_hists[h_HLM_VR_STC] = h_HLM_VR_hi_STC;
  TH3D* h_HLM_MR_hi_STC = (TH3D*) h_HL_MR_hi_STC->Clone("h_HLM_MR_hi_STC");
  h_HLM_MR_hi_STC->Add(h_HM_MR_hi_STC);
  hi_hists[h_HLM_MR_STC] = h_HLM_MR_hi_STC;

  TH3D* h_1LM_SR_lo_STC = (TH3D*) h_1L_SR_lo_STC->Clone("h_1LM_SR_lo_STC");
  h_1LM_SR_lo_STC->Add(h_1M_SR_lo_STC);
  low_hists[h_1LM_SR_STC] = h_1LM_SR_lo_STC;
  TH3D* h_1LM_VR_lo_STC = (TH3D*) h_1L_VR_lo_STC->Clone("h_1LM_VR_lo_STC");
  h_1LM_VR_lo_STC->Add(h_1M_VR_lo_STC);
  low_hists[h_1LM_VR_STC] = h_1LM_VR_lo_STC;
  TH3D* h_1LM_MR_lo_STC = (TH3D*) h_1L_MR_lo_STC->Clone("h_1LM_MR_lo_STC");
  h_1LM_MR_lo_STC->Add(h_1M_MR_lo_STC);
  low_hists[h_1LM_MR_STC] = h_1LM_MR_lo_STC;
  TH3D* h_LLM_SR_lo_STC = (TH3D*) h_LL_SR_lo_STC->Clone("h_LLM_SR_lo_STC");
  h_LLM_SR_lo_STC->Add(h_LM_SR_lo_STC);
  low_hists[h_LLM_SR_STC] = h_LLM_SR_lo_STC;
  TH3D* h_LLM_VR_lo_STC = (TH3D*) h_LL_VR_lo_STC->Clone("h_LLM_VR_lo_STC");
  h_LLM_VR_lo_STC->Add(h_LM_VR_lo_STC);
  low_hists[h_LLM_VR_STC] = h_LLM_VR_lo_STC;
  TH3D* h_LLM_MR_lo_STC = (TH3D*) h_LL_MR_lo_STC->Clone("h_LLM_MR_lo_STC");
  h_LLM_MR_lo_STC->Add(h_LM_MR_lo_STC);
  low_hists[h_LLM_MR_STC] = h_LLM_MR_lo_STC;
  TH3D* h_HLM_SR_lo_STC = (TH3D*) h_HL_SR_lo_STC->Clone("h_HLM_SR_lo_STC");
  h_HLM_SR_lo_STC->Add(h_HM_SR_lo_STC);
  low_hists[h_HLM_SR_STC] = h_HLM_SR_lo_STC;
  TH3D* h_HLM_VR_lo_STC = (TH3D*) h_HL_VR_lo_STC->Clone("h_HLM_VR_lo_STC");
  h_HLM_VR_lo_STC->Add(h_HM_VR_lo_STC);
  low_hists[h_HLM_VR_STC] = h_HLM_VR_lo_STC;
  TH3D* h_HLM_MR_lo_STC = (TH3D*) h_HL_MR_lo_STC->Clone("h_HLM_MR_lo_STC");
  h_HLM_MR_lo_STC->Add(h_HM_MR_lo_STC);
  low_hists[h_HLM_MR_STC] = h_HLM_MR_lo_STC;

  // STs
  TH3D* h_1LM_SR_ST = (TH3D*) h_1L_SR_ST->Clone("h_1LM_SR_ST");
  h_1LM_SR_ST->Add(h_1M_SR_ST);
  TH3D* h_1LM_VR_ST = (TH3D*) h_1L_VR_ST->Clone("h_1LM_VR_ST");
  h_1LM_VR_ST->Add(h_1M_VR_ST);
  TH3D* h_1LM_MR_ST = (TH3D*) h_1L_MR_ST->Clone("h_1LM_MR_ST");
  h_1LM_MR_ST->Add(h_1M_MR_ST);
  TH3D* h_LLM_SR_ST = (TH3D*) h_LL_SR_ST->Clone("h_LLM_SR_ST");
  h_LLM_SR_ST->Add(h_LM_SR_ST);
  TH3D* h_LLM_VR_ST = (TH3D*) h_LL_VR_ST->Clone("h_LLM_VR_ST");
  h_LLM_VR_ST->Add(h_LM_VR_ST);
  TH3D* h_LLM_MR_ST = (TH3D*) h_LL_MR_ST->Clone("h_LLM_MR_ST");
  h_LLM_MR_ST->Add(h_LM_MR_ST);
  TH3D* h_HLM_SR_ST = (TH3D*) h_HL_SR_ST->Clone("h_HLM_SR_ST");
  h_HLM_SR_ST->Add(h_HM_SR_ST);
  TH3D* h_HLM_VR_ST = (TH3D*) h_HL_VR_ST->Clone("h_HLM_VR_ST");
  h_HLM_VR_ST->Add(h_HM_VR_ST);
  TH3D* h_HLM_MR_ST = (TH3D*) h_HL_MR_ST->Clone("h_HLM_MR_ST");
  h_HLM_MR_ST->Add(h_HM_MR_ST);

  TH3D* h_1LM_SR_hi_ST = (TH3D*) h_1L_SR_hi_ST->Clone("h_1LM_SR_hi_ST");
  h_1LM_SR_hi_ST->Add(h_1M_SR_hi_ST);
  hi_hists[h_1LM_SR_ST] = h_1LM_SR_hi_ST;
  TH3D* h_1LM_VR_hi_ST = (TH3D*) h_1L_VR_hi_ST->Clone("h_1LM_VR_hi_ST");
  h_1LM_VR_hi_ST->Add(h_1M_VR_hi_ST);
  hi_hists[h_1LM_VR_ST] = h_1LM_VR_hi_ST;
  TH3D* h_1LM_MR_hi_ST = (TH3D*) h_1L_MR_hi_ST->Clone("h_1LM_MR_hi_ST");
  h_1LM_MR_hi_ST->Add(h_1M_MR_hi_ST);
  hi_hists[h_1LM_MR_ST] = h_1LM_MR_hi_ST;
  TH3D* h_LLM_SR_hi_ST = (TH3D*) h_LL_SR_hi_ST->Clone("h_LLM_SR_hi_ST");
  h_LLM_SR_hi_ST->Add(h_LM_SR_hi_ST);
  hi_hists[h_LLM_SR_ST] = h_LLM_SR_hi_ST;
  TH3D* h_LLM_VR_hi_ST = (TH3D*) h_LL_VR_hi_ST->Clone("h_LLM_VR_hi_ST");
  h_LLM_VR_hi_ST->Add(h_LM_VR_hi_ST);
  hi_hists[h_LLM_VR_ST] = h_LLM_VR_hi_ST;
  TH3D* h_LLM_MR_hi_ST = (TH3D*) h_LL_MR_hi_ST->Clone("h_LLM_MR_hi_ST");
  h_LLM_MR_hi_ST->Add(h_LM_MR_hi_ST);
  hi_hists[h_LLM_MR_ST] = h_LLM_MR_hi_ST;
  TH3D* h_HLM_SR_hi_ST = (TH3D*) h_HL_SR_hi_ST->Clone("h_HLM_SR_hi_ST");
  h_HLM_SR_hi_ST->Add(h_HM_SR_hi_ST);
  hi_hists[h_HLM_SR_ST] = h_HLM_SR_hi_ST;
  TH3D* h_HLM_VR_hi_ST = (TH3D*) h_HL_VR_hi_ST->Clone("h_HLM_VR_hi_ST");
  h_HLM_VR_hi_ST->Add(h_HM_VR_hi_ST);
  hi_hists[h_HLM_VR_ST] = h_HLM_VR_hi_ST;
  TH3D* h_HLM_MR_hi_ST = (TH3D*) h_HL_MR_hi_ST->Clone("h_HLM_MR_hi_ST");
  h_HLM_MR_hi_ST->Add(h_HM_MR_hi_ST);
  hi_hists[h_HLM_MR_ST] = h_HLM_MR_hi_ST;

  TH3D* h_1LM_SR_lo_ST = (TH3D*) h_1L_SR_lo_ST->Clone("h_1LM_SR_lo_ST");
  h_1LM_SR_lo_ST->Add(h_1M_SR_lo_ST);
  low_hists[h_1LM_SR_ST] = h_1LM_SR_lo_ST;
  TH3D* h_1LM_VR_lo_ST = (TH3D*) h_1L_VR_lo_ST->Clone("h_1LM_VR_lo_ST");
  h_1LM_VR_lo_ST->Add(h_1M_VR_lo_ST);
  low_hists[h_1LM_VR_ST] = h_1LM_VR_lo_ST;
  TH3D* h_1LM_MR_lo_ST = (TH3D*) h_1L_MR_lo_ST->Clone("h_1LM_MR_lo_ST");
  h_1LM_MR_lo_ST->Add(h_1M_MR_lo_ST);
  low_hists[h_1LM_MR_ST] = h_1LM_MR_lo_ST;
  TH3D* h_LLM_SR_lo_ST = (TH3D*) h_LL_SR_lo_ST->Clone("h_LLM_SR_lo_ST");
  h_LLM_SR_lo_ST->Add(h_LM_SR_lo_ST);
  low_hists[h_LLM_SR_ST] = h_LLM_SR_lo_ST;
  TH3D* h_LLM_VR_lo_ST = (TH3D*) h_LL_VR_lo_ST->Clone("h_LLM_VR_lo_ST");
  h_LLM_VR_lo_ST->Add(h_LM_VR_lo_ST);
  low_hists[h_LLM_VR_ST] = h_LLM_VR_lo_ST;
  TH3D* h_LLM_MR_lo_ST = (TH3D*) h_LL_MR_lo_ST->Clone("h_LLM_MR_lo_ST");
  h_LLM_MR_lo_ST->Add(h_LM_MR_lo_ST);
  low_hists[h_LLM_MR_ST] = h_LLM_MR_lo_ST;
  TH3D* h_HLM_SR_lo_ST = (TH3D*) h_HL_SR_lo_ST->Clone("h_HLM_SR_lo_ST");
  h_HLM_SR_lo_ST->Add(h_HM_SR_lo_ST);
  low_hists[h_HLM_SR_ST] = h_HLM_SR_lo_ST;
  TH3D* h_HLM_VR_lo_ST = (TH3D*) h_HL_VR_lo_ST->Clone("h_HLM_VR_lo_ST");
  h_HLM_VR_lo_ST->Add(h_HM_VR_lo_ST);
  low_hists[h_HLM_VR_ST] = h_HLM_VR_lo_ST;
  TH3D* h_HLM_MR_lo_ST = (TH3D*) h_HL_MR_lo_ST->Clone("h_HLM_MR_lo_ST");
  h_HLM_MR_lo_ST->Add(h_HM_MR_lo_ST);
  low_hists[h_HLM_MR_ST] = h_HLM_MR_lo_ST;

  vector<TH3D*> hists = {
    h_1L_MR_STC,  h_1M_MR_STC,  h_1LM_MR_STC, h_1H_MR_STC, h_LL_MR_STC,  h_LM_MR_STC,  h_LLM_MR_STC, h_LH_MR_STC, h_HL_MR_STC,  h_HM_MR_STC,  h_HLM_MR_STC, h_HH_MR_STC,  
    h_1L_VR_STC,  h_1M_VR_STC,  h_1LM_VR_STC, h_1H_VR_STC, h_LL_VR_STC,  h_LM_VR_STC,  h_LLM_VR_STC, h_LH_VR_STC, h_HL_VR_STC,  h_HM_VR_STC,  h_HLM_VR_STC, h_HH_VR_STC, 
    h_1L_SR_STC,  h_1M_SR_STC,  h_1LM_SR_STC, h_1H_SR_STC, h_LL_SR_STC,  h_LM_SR_STC,  h_LLM_SR_STC, h_LH_SR_STC, h_HL_SR_STC,  h_HM_SR_STC,  h_HLM_SR_STC, h_HH_SR_STC,

    h_1L_MR_ST,  h_1M_MR_ST,  h_1LM_MR_ST, h_1H_MR_ST, h_LL_MR_ST,  h_LM_MR_ST,  h_LLM_MR_ST, h_LH_MR_ST, h_HL_MR_ST,  h_HM_MR_ST,  h_HLM_MR_ST, h_HH_MR_ST,  
    h_1L_VR_ST,  h_1M_VR_ST,  h_1LM_VR_ST, h_1H_VR_ST, h_LL_VR_ST,  h_LM_VR_ST,  h_LLM_VR_ST, h_LH_VR_ST, h_HL_VR_ST,  h_HM_VR_ST,  h_HLM_VR_ST, h_HH_VR_ST, 
    h_1L_SR_ST,  h_1M_SR_ST,  h_1LM_SR_ST, h_1H_SR_ST, h_LL_SR_ST,  h_LM_SR_ST,  h_LLM_SR_ST, h_LH_SR_ST, h_HL_SR_ST,  h_HM_SR_ST,  h_HLM_SR_ST, h_HH_SR_ST,

    h_fracFS_1, h_fracFS_23, h_fracFS_4};

  cout << "About to write" << endl;
  
  TH2D* h_rescale = (TH2D*) h_weight_raw->Clone("h_reweight_rescale");
  h_rescale->Divide(h_eff_den);
  h_rescale->SetTitle("Post-reweight / Pre-reweight Total Integral");

  TFile outfile_(Form("%s.root",outtag),"RECREATE"); 
  outfile_.cd();
  for (vector<TH3D*>::iterator hist = hists.begin(); hist != hists.end(); hist++) {
  if (ctau_in != ctau_out) {
      cout << "Rescaling counts to adjust for reweighting, see h_reweight_rescale" << endl;    
      cout << "Integral: " << (*hist)->Integral();
      for (int x = 1; x <= h_rescale->GetNbinsX(); x++) {
	for (int y = 1; y <= h_rescale->GetNbinsY(); y++) {
	  double factor = h_rescale->GetBinContent(x,y);
	  for (int z = 1; z <= (*hist)->GetNbinsZ(); z++) {
	    (*hist)->SetBinContent(z,x,y,(*hist)->GetBinContent(z,x,y)*factor);
	    low_hists[(*hist)]->SetBinContent(z,x,y,low_hists[(*hist)]->GetBinContent(z,x,y)*factor);
	    hi_hists[(*hist)]->SetBinContent(z,x,y,hi_hists[(*hist)]->GetBinContent(z,x,y)*factor);
	  }
	}
      }
      cout << " -> " << (*hist)->Integral() << endl;;
    }
    (*hist)->Write();
    low_hists[(*hist)]->Write();
    hi_hists[(*hist)]->Write();
  }

  /*
  h_2STC_MR->Write();
  h_2STC_VR->Write();
  h_2STC_SR->Write();
  */

  h_decay_factor->Write();
  h_decay_factor_P3->Write();
  h_decay_factor_P4->Write();
  h_decay_factor_M->Write();
  h_decay_factor_L->Write();
  h_beta->Write();
  h_DL_raw->Write();
  h_DL->Write();

  h_rescale->Write();
  h_weight_raw->Write();
  h_weight_nospikes->Write();
  h_eff_den->Write();
  h_eff_num->Write();

  h_weight_all->Write();
  h_weight_acc->Write();

  h_nospikes->Write();
  h_nevents->Write();
  
  outfile_.Close();
  cout << "Wrote everything" << endl;

  cout << "Total short track count: " << numberOfAllSTs << endl;
  cout << "Total short track candidate count: " << numberOfAllSTCs << endl;


  return 0;
}

int main (int argc, char ** argv) {

  if (argc < 5 && argc != 7) {
    cout << "Usage: ./ShortTrackLooper.exe <outtag> <infile> <config> <runtag> [<ctau in> <ctau out>]" << endl;
    return 1;
  }

  TChain *ch = new TChain("mt2");
  //  ch->AddFile(Form("%s.root",argv[2]));
  //ch->AddFile(Form("%s_ext1.root",argv[2]));
  ch->Add(Form("%s*.root",argv[2]));
  ShortTrackLooper * stl = new ShortTrackLooper();
  if (argc == 5) {
    stl->loop(ch,argv[1],string(argv[3]),argv[4]);
  }
  else {
    stl->loop(ch,argv[1],string(argv[3]),argv[4],atof(argv[5]),atof(argv[6]));
  }
  return 0;
}

float ShortTrackLooper::getAverageISRWeight(const string sample, const string config_tag) {
  // 2016 94x ttsl 0.908781126143
  // 2016 94x ttdl 0.895473127249
  if (config_tag == "mc_94x_Summer16") {
    if (sample.compare("ttsl") == 0) {
      return 0.909;
    }
    else {
      return 0.895;
    }
  }
  // 2017 94x ttsl 0.915829735522
  // 2017 94x ttdl 0.903101272148
  else if (config_tag == "mc_94x_Fall17") {
    if (sample == "ttsl") {
      return 0.916;
    }
    else {
      return 0.903;
    }
  }
  else {
    cout << "Didn't recognize config " << config_tag << endl;
    return 1.0;
  }
}

double ShortTrackLooper::Theta(float eta) {
  double exp_eta = 2*TMath::Exp(-eta);
  return TMath::ATan(exp_eta);
}


ShortTrackLooper::ShortTrackLooper() {}

ShortTrackLooper::~ShortTrackLooper() {};
