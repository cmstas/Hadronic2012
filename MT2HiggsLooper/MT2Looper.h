#ifndef MT2LOOPER_h
#define MT2LOOPER_h

// C++ includes
//#include <string>
//#include <vector>

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "Math/LorentzVector.h"

#include "RooDataSet.h"

//MT2
#include "../MT2CORE/mt2tree.h"
#include "../MT2CORE/sigSelections.h"
#include "../MT2CORE/sigSelectionsMT2Higgs.h"
#include "../MT2CORE/SR.h"

typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
using namespace mt2;
class MT2Looper {

 public:

  struct lepcand {
    float pt;
    float eta;
    float phi;
    int pdgId;
    float mt;
    bool isPFCand;
  };

  MT2Looper();
  ~MT2Looper();

  void SetSignalRegions();
  void loop(TChain* chain, std::string sample, std::string output_dir);
  void fillHistosSRBase();
  void fillHistosInclusive();
  void fillHistosSignalRegion(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosSRMT2Higgs(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosCRSL(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosCRGJ(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosCRDY(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosCRRL(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistosCRQCD(const std::string& prefix = "", const std::string& suffix = "");
  void fillHistos(std::map<std::string, TH1*>& h_1d, int n_mt2bins, float* mt2bins,
		  const std::string& dir = "", const std::string& suffix = ""); 
  void fillHistosMT2Higgs(std::map<std::string, TH1*>& h_1d, int n_mt2bins,
                          float* mt2bins, const std::string& dirname, const std::string& s);
  void fillHistosSingleLepton(std::map<std::string, TH1*>& h_1d, int n_mt2bins, float* mt2bins,
			      const std::string& dir = "", const std::string& suffix = ""); 
  void fillHistosGammaJets(std::map<std::string, TH1*>& h_1d, std::map<std::string, RooDataSet*>& datasets, int n_mt2bins, float* mt2bins, 
			      const std::string& dir = "", const std::string& suffix = ""); 
  void fillHistosRemovedLepton(std::map<std::string, TH1*>& h_1d, int n_mt2bins, float* mt2bins, 
			      const std::string& dir = "", const std::string& suffix = ""); 
  void fillHistosDY(std::map<std::string, TH1*>& h_1d, int n_mt2bins, float* mt2bins, 
			      const std::string& dir = "", const std::string& suffix = ""); 
  void fillHistosQCD(std::map<std::string, TH1*>& h_1d, int n_mt2bins, float* mt2bins,
			      const std::string& dir = "", const std::string& suffix = "");
  void fillLepUncSR();
  void fillLepCorSRfastsim();
  
 private:

  TFile * outfile_;
  mt2tree t;
  float evtweight_;
  int nlepveto_;
  float leppt_;
  float mt_;
  int nJet30Eta3_;
  bool isSignal_;
  bool passMonojetId_;
  std::map<std::string, TH1*> h_1d_global;
  std::vector<SR> SRVec;
  std::vector<SR> SRVecHcand;
  std::vector<SR> SRVecMonojet;
  std::vector<SR> InclusiveRegions;
  std::vector<SR> InclusiveRegionsMonojet;
  SR SRBase;
  SR SRBaseHcand;
  SR SRBaseIncl;
  SR SRBaseMonojet;
  SR SRBaseMonojet0B;
  SR SRBaseMonojet1B;
  SR SRNoCut;
  SR CRSL_WJets;
  SR CRSL_TTbar;
  TH1D* h_nvtx_weights_;
  TH2D* h_sig_nevents_;
  TH2D* h_sig_avgweight_btagsf_;
  TH2D* h_sig_avgweight_btagsf_heavy_UP_;
  TH2D* h_sig_avgweight_btagsf_light_UP_;
  TH2D* h_sig_avgweight_btagsf_heavy_DN_;
  TH2D* h_sig_avgweight_btagsf_light_DN_;
  TH2D* h_sig_avgweight_isr_;
  float cor_lepeff_sr_;
  float unc_lepeff_sr_UP_;
  float unc_lepeff_sr_DN_;
  
};

#endif

