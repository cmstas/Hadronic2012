#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TLegend.h"
#include "TString.h"
#include "TCanvas.h"
#include "TCut.h"
#include "TEfficiency.h"

void plot_trigeff_PFHT350_PFMET100 (const TString& indir = "/nfs-6/userdata/mt2/V00-01-05_25ns_json_246908-258159_v3_Summer15_25nsV5/") {

  TH1::SetDefaultSumw2();
  
  TChain* t_jetht = new TChain("mt2");
  TChain* t_met = new TChain("mt2");
  TChain* t_ele = new TChain("mt2");

  t_jetht->Add(Form("%s/*Run2015*JetHT*.root", indir.Data()));
  t_met->Add(Form("%s/*Run2015*MET*.root", indir.Data()));
  t_ele->Add(Form("%s/*Run2015*SingleElectron*.root", indir.Data()));

  TFile* f_out = new TFile("trigeff_PFHT350_PFMET100.root","RECREATE");
  
  TH1D* h_ht_denom_met170 = new TH1D("h_ht_denom_met170",";H_{T} [GeV]",32,200,1000);
  TH1D* h_ht_num_met170 = (TH1D*) h_ht_denom_met170->Clone("h_ht_num_met170");
  TH1D* h_ht_denom_ele23 = (TH1D*) h_ht_denom_met170->Clone("h_ht_denom_ele23");
  TH1D* h_ht_num_ele23 = (TH1D*) h_ht_denom_met170->Clone("h_ht_num_ele23");

  TH1D* h_met_denom_ht475 = new TH1D("h_met_denom_ht475",";E_{T}^{miss} [GeV]",20,0,500);
  TH1D* h_met_num_ht475 = (TH1D*) h_met_denom_ht475->Clone("h_met_num_ht475");
  TH1D* h_met_denom_ele23 = (TH1D*) h_met_denom_ht475->Clone("h_met_denom_ele23");
  TH1D* h_met_num_ele23 = (TH1D*) h_met_denom_ht475->Clone("h_met_num_ele23");

  TCut base = "nVert > 0 && nJet30 > 1 && Flag_CSCTightHaloFilter && Flag_eeBadScFilter && Flag_HBHENoiseFilter && Flag_HBHEIsoNoiseFilter";
  TCut had = base + "nElectrons10+nMuons10==0 && deltaPhiMin > 0.3";
  TCut ele = base + "nElectrons10 > 0 && abs(lep_pdgId[0]) == 11 && lep_pt[0] > 25.";

  t_jetht->Draw("met_pt>>h_met_denom_ht475",had+"ht > 500. && HLT_PFHT475_Prescale");
  t_jetht->Draw("met_pt>>h_met_num_ht475",had+"ht > 500. && HLT_PFHT475_Prescale && HLT_PFHT350_PFMET100");

  t_ele->Draw("met_pt>>h_met_denom_ele23",ele+"ht > 450. && HLT_SingleEl");
  t_ele->Draw("met_pt>>h_met_num_ele23",ele+"ht > 450. && HLT_SingleEl && HLT_PFHT350_PFMET100");

  t_met->Draw("ht>>h_ht_denom_met170",had+"met_pt > 250. && HLT_PFMET170");
  t_met->Draw("ht>>h_ht_num_met170",had+"met_pt > 250. && HLT_PFMET170 && HLT_PFHT350_PFMET100");

  t_ele->Draw("ht>>h_ht_denom_ele23",ele+"met_pt > 250. && HLT_SingleEl");
  t_ele->Draw("ht>>h_ht_num_ele23",ele+"met_pt > 250. && HLT_SingleEl && HLT_PFHT350_PFMET100");

  TH2F* h_met_axis = new TH2F("h_met_axis",";E_{T}^{miss} [GeV];Efficiency of PFMET100 leg",20,0,500,20,0,1);
  
  TEfficiency* h_met_eff_ht475 = new TEfficiency(*h_met_num_ht475, *h_met_denom_ht475);
  h_met_eff_ht475->SetLineColor(kRed);
  h_met_eff_ht475->SetMarkerColor(kRed);
  
  TEfficiency* h_met_eff_ele23 = new TEfficiency(*h_met_num_ele23, *h_met_denom_ele23);
  h_met_eff_ele23->SetLineColor(kGreen+2);
  h_met_eff_ele23->SetMarkerColor(kGreen+2);

  TH2F* h_ht_axis = new TH2F("h_ht_axis",";H_{T} [GeV];Efficiency of PFHT350 leg",16,200,1000,20,0,1);

  TEfficiency* h_ht_eff_met170 = new TEfficiency(*h_ht_num_met170, *h_ht_denom_met170);
  h_ht_eff_met170->SetLineColor(kBlue);
  h_ht_eff_met170->SetMarkerColor(kBlue);

  TEfficiency* h_ht_eff_ele23 = new TEfficiency(*h_ht_num_ele23, *h_ht_denom_ele23);
  h_ht_eff_ele23->SetLineColor(kGreen+2);
  h_ht_eff_ele23->SetMarkerColor(kGreen+2);

  TCanvas* c_met = new TCanvas("c_met","c_met");
  c_met->SetGrid(1,1);
  c_met->cd();

  h_met_axis->Draw();
  h_met_eff_ht475->Draw("pe same");
  h_met_eff_ele23->Draw("pe same");

  TLegend* leg_met = new TLegend(0.6,0.2,0.95,0.5);
  leg_met->AddEntry(h_met_eff_ht475,"HLT_PFHT475","pe");
  leg_met->AddEntry(h_met_eff_ele23,"HLT_Ele23_WPLoose_Gsf","pe");
  leg_met->Draw("same");

  c_met->SaveAs("trigeff_PFMET100_leg.pdf");
  c_met->SaveAs("trigeff_PFMET100_leg.eps");

  TCanvas* c_ht = new TCanvas("c_ht","c_ht");
  c_ht->SetGrid(1,1);
  c_ht->cd();

  h_ht_axis->Draw();
  h_ht_eff_ele23->Draw("pe same");
  h_ht_eff_met170->Draw("pe same");

  TLegend* leg_ht = new TLegend(0.6,0.2,0.95,0.5);
  leg_ht->AddEntry(h_ht_eff_ele23,"HLT_Ele23_WPLoose_Gsf","pe");
  leg_ht->AddEntry(h_ht_eff_met170,"HLT_PFMET170","pe");
  leg_ht->Draw("same");

  c_ht->SaveAs("trigeff_PFHT350_leg.pdf");
  c_ht->SaveAs("trigeff_PFHT350_leg.eps");

  f_out->Write();
  f_out->Close();
  
  return;
}