#ifndef ZLLLOOPER_h
#define ZLLLOOPER_h

// C++ includes
//#include <string>
//#include <vector>

// ROOT includes
#include "TROOT.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TH1F.h"
#include "Math/LorentzVector.h"

//MT2
#include "../MT2CORE/mt2tree.h"
#include "../MT2CORE/sigSelections.h"


typedef ROOT::Math::LorentzVector<ROOT::Math::PxPyPzE4D<float> > LorentzVector;
using namespace mt2;
class ZllLooper {

 public:

  ZllLooper();
  ~ZllLooper();

  void loop(TChain* chain, std::string output_name = "test.root");
  void fillHistosSignalRegion(std::map<std::string, TH1F*>& h_1d, 
			      const SignalRegionJets::value_type& signal_region = SignalRegionJets::nocut, 
			      const SignalRegionHtMet::value_type& signal_region_type = SignalRegionHtMet::nocut,
			      const std::string& dir = "", const std::string& suffix = "");
  void fillHistos(std::map<std::string, TH1F*>& h_1d, 
		  const std::string& dir = "", const std::string& suffix = ""); 
  
 private:

  TFile * outfile_;
  mt2tree t;
  float evtweight_;
  int nlepveto_;
  std::map<std::string, TH1F*> h_1d_global;
  float Zinv_pt_;
  float mt2_Zinv_;
  float nJet40_Zinv_;
  float nBJet40_Zinv_;
  float ht_Zinv_;
  float deltaPhiMin_Zinv_;
  float diffMetMht_Zinv_;
  float mht_pt_Zinv_;
  float mht_phi_Zinv_;
  float met_pt_Zinv_;
  float met_phi_Zinv_;
  int   jetIdx0_;
  int   jetIdx1_;
};

#endif

