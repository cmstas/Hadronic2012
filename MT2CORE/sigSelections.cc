#include "sigSelections.h"

namespace mt2 {

std::vector<SR> getSignalRegions2012(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 3);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 3);
  sr.SetVar("nbjets", 1, 3);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 3, 6);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("mt2", 200, 400);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 3, 6);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 3, 6);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 6, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 6, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("mt2", 200, 400);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("8");
  sr.SetVar("njets", 6, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("mt2", 200, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("9");
  sr.SetVar("njets", 3, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("mt2", 200, 400);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 750);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 750, 1200);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1200, -1);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  //baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMht", 0, 70);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  return SRVec;

}

std::vector<SR> getSignalRegions2015LowLumi(){//used for AN-15-009

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 4, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("8");
  sr.SetVar("njets", 4, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("9");
  sr.SetVar("njets", 2, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 2, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 575, 1000);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1000, -1);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  return SRVec;

}


std::vector<SR> getSignalRegions2015ExtendedNJets(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("8");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("9");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("11");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("12");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("13");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("14");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("15");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("16");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("17");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("18");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("19");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("20");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();


  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 575, 1000);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1000, -1);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  return SRVec;

}

std::vector<SR> getSignalRegions2015ExtendedNJets_UltraHighHT(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("8");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("9");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("11");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("12");
  sr.SetVar("njets", 7, 9);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("13");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("14");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("15");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("16");
  sr.SetVar("njets", 9, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("17");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("18");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("19");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("20");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();


  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 575, 1000);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1000, 1500);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "UH");
    fullSR.SetVar("ht", 1500, -1);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  return SRVec;

}


std::vector<SR> getSignalRegions2015SevenJets_UltraHighHT(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("8");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("9");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVar("lowMT", 0, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("11");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("12");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("13");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("14");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("15");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("16");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVar("lowMT", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();


  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 575, 1000);
    fullSR.SetVar("met", 200, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1000, 1500);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "UH");
    fullSR.SetVar("ht", 1500, -1);
    fullSR.SetVar("met", 30, -1);
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  return SRVec;

}

std::vector<SR> getSignalRegionsZurich(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR sr;
  SR baseSR;

  //first set binning in njet-nbjet plane
  sr.SetName("1");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 0, 1);
  sr.SetVarCRRSInvertDPhi("njets", 2, 4);
  sr.SetVarCRRSInvertDPhi("nbjets", 0, 1);
  sr.SetVarCRRSMT2SideBand("njets", 2, 4);
  sr.SetVarCRRSMT2SideBand("nbjets", 0, 1);
  sr.SetVarCRRSDPhiMT2("njets", 2, 4);
  sr.SetVarCRRSDPhiMT2("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 1, 2);
  sr.SetVarCRRSInvertDPhi("njets", 2, 4);
  sr.SetVarCRRSInvertDPhi("nbjets", 1, 2);
  sr.SetVarCRRSMT2SideBand("njets", 2, 4);
  sr.SetVarCRRSMT2SideBand("nbjets", 1, 2);
  sr.SetVarCRRSDPhiMT2("njets", 2, 4);
  sr.SetVarCRRSDPhiMT2("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 2, 3);
  sr.SetVarCRRSInvertDPhi("njets", 2, 4);
  sr.SetVarCRRSInvertDPhi("nbjets", 2, 3);
  sr.SetVarCRRSMT2SideBand("njets", 2, 4);
  sr.SetVarCRRSMT2SideBand("nbjets", 2, 3);
  sr.SetVarCRRSDPhiMT2("njets", 2, 4);
  sr.SetVarCRRSDPhiMT2("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 0, 1);
  sr.SetVarCRRSInvertDPhi("njets", 4, 7);
  sr.SetVarCRRSInvertDPhi("nbjets", 0, 1);
  sr.SetVarCRRSMT2SideBand("njets", 4, 7);
  sr.SetVarCRRSMT2SideBand("nbjets", 0, 1);
  sr.SetVarCRRSDPhiMT2("njets", 4, 7);
  sr.SetVarCRRSDPhiMT2("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 1, 2);
  sr.SetVarCRRSInvertDPhi("njets", 4, 7);
  sr.SetVarCRRSInvertDPhi("nbjets", 1, 2);
  sr.SetVarCRRSMT2SideBand("njets", 4, 7);
  sr.SetVarCRRSMT2SideBand("nbjets", 1, 2);
  sr.SetVarCRRSDPhiMT2("njets", 4, 7);
  sr.SetVarCRRSDPhiMT2("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 2, 3);
  sr.SetVarCRRSInvertDPhi("njets", 4, 7);
  sr.SetVarCRRSInvertDPhi("nbjets", 2, 3);
  sr.SetVarCRRSMT2SideBand("njets", 4, 7);
  sr.SetVarCRRSMT2SideBand("nbjets", 2, 3);
  sr.SetVarCRRSDPhiMT2("njets", 4, 7);
  sr.SetVarCRRSDPhiMT2("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 0, 1);
  sr.SetVarCRRSInvertDPhi("njets", 7, -1);
  sr.SetVarCRRSInvertDPhi("nbjets", 0, 1);
  sr.SetVarCRRSMT2SideBand("njets", 7, -1);
  sr.SetVarCRRSMT2SideBand("nbjets", 0, 1);
  sr.SetVarCRRSDPhiMT2("njets", 7, -1);
  sr.SetVarCRRSDPhiMT2("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("8");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  sr.SetVarCRRSInvertDPhi("njets", 7, -1);
  sr.SetVarCRRSInvertDPhi("nbjets", 1, 2);
  sr.SetVarCRRSMT2SideBand("njets", 7, -1);
  sr.SetVarCRRSMT2SideBand("nbjets", 1, 2);
  sr.SetVarCRRSDPhiMT2("njets", 7, -1);
  sr.SetVarCRRSDPhiMT2("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("9");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  sr.SetVarCRRSInvertDPhi("njets", 7, -1);
  sr.SetVarCRRSInvertDPhi("nbjets", 2, 3);
  sr.SetVarCRRSMT2SideBand("njets", 7, -1);
  sr.SetVarCRRSMT2SideBand("nbjets", 2, 3);
  sr.SetVarCRRSDPhiMT2("njets", 7, -1);
  sr.SetVarCRRSDPhiMT2("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 2, 7);
  sr.SetVarCRSL("nbjets", 3, -1);
  sr.SetVarCRRSInvertDPhi("njets", 2, 7);
  sr.SetVarCRRSInvertDPhi("nbjets", 3, -1);
  sr.SetVarCRRSMT2SideBand("njets", 2, 7);
  sr.SetVarCRRSMT2SideBand("nbjets", 3, -1);
  sr.SetVarCRRSDPhiMT2("njets", 2, 7);
  sr.SetVarCRRSDPhiMT2("nbjets", 3, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("11");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  sr.SetVarCRRSInvertDPhi("njets", 7, -1);
  sr.SetVarCRRSInvertDPhi("nbjets", 3, -1);
  sr.SetVarCRRSMT2SideBand("njets", 7, -1);
  sr.SetVarCRRSMT2SideBand("nbjets", 3, -1);
  sr.SetVarCRRSDPhiMT2("njets", 7, -1);
  sr.SetVarCRRSDPhiMT2("nbjets", 3, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();


  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    fullSR.SetVarCRSL("ht", 450, 575);
    fullSR.SetVarCRSL("met", 200, -1);
    fullSR.SetVarCRRSInvertDPhi("ht", 450, 575);
    fullSR.SetVarCRRSInvertDPhi("met", 200, -1);
    fullSR.SetVarCRRSMT2SideBand("ht", 450, 575);
    fullSR.SetVarCRRSMT2SideBand("met", 200, -1);
    fullSR.SetVarCRRSDPhiMT2("ht", 450, 575);
    fullSR.SetVarCRRSDPhiMT2("met", 200, -1);
    int njets_lo = fullSR.GetLowerBound("njets");
    int nbjets_lo = fullSR.GetLowerBound("nbjets");
    if     (njets_lo == 2 && nbjets_lo == 0){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 1){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 2){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 0){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 1){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 2){float mt2bins[5] = {200, 300, 400, 500, 1500}; fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 0){float mt2bins[2] = {200, 1500};                fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 1){float mt2bins[3] = {200, 300, 1500};           fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 2){float mt2bins[2] = {200, 1500};                fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 3){float mt2bins[3] = {200, 300, 1500};           fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 3){float mt2bins[2] = {200, 1500};                fullSR.SetMT2Bins(1, mt2bins);}
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "M");
    fullSR.SetVar("ht", 575, 1000);
    fullSR.SetVar("met", 200, -1);
    fullSR.SetVarCRSL("ht", 575, 1000);
    fullSR.SetVarCRSL("met", 200, -1);
    fullSR.SetVarCRRSInvertDPhi("ht", 575, 1000);
    fullSR.SetVarCRRSInvertDPhi("met", 200, -1);
    fullSR.SetVarCRRSMT2SideBand("ht", 575, 1000);
    fullSR.SetVarCRRSMT2SideBand("met", 200, -1);
    fullSR.SetVarCRRSDPhiMT2("ht", 575, 1000);
    fullSR.SetVarCRRSDPhiMT2("met", 200, -1);
    int njets_lo = fullSR.GetLowerBound("njets");
    int nbjets_lo = fullSR.GetLowerBound("nbjets");
    if     (njets_lo == 2 && nbjets_lo == 0){float mt2bins[6] = {200, 300, 400, 600, 800, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 1){float mt2bins[6] = {200, 300, 400, 600, 800, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 2){float mt2bins[5] = {200, 300, 400, 600, 1500};      fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 0){float mt2bins[6] = {200, 300, 400, 600, 800, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 1){float mt2bins[5] = {200, 300, 400, 600, 1500};      fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 2){float mt2bins[5] = {200, 300, 400, 600, 1500};      fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 0){float mt2bins[4] = {200, 300, 400, 1500};           fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 1){float mt2bins[4] = {200, 300, 400, 1500};           fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 2){float mt2bins[4] = {200, 300, 400, 1500};           fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 3){float mt2bins[4] = {200, 300, 400, 1500};           fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 3){float mt2bins[4] = {200, 300, 400, 1500};           fullSR.SetMT2Bins(3, mt2bins);}
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "H");
    fullSR.SetVar("ht", 1000, 1500);
    fullSR.SetVar("met", 30, -1);
    fullSR.SetVarCRSL("ht", 1000, 1500);
    fullSR.SetVarCRSL("met", 30, -1);
    fullSR.SetVarCRRSInvertDPhi("ht", 1000, 1500);
    fullSR.SetVarCRRSInvertDPhi("met", 30, -1);
    fullSR.SetVarCRRSMT2SideBand("ht", 1000, 1500);
    fullSR.SetVarCRRSMT2SideBand("met", 30, -1);
    fullSR.SetVarCRRSDPhiMT2("ht", 1000, 1500);
    fullSR.SetVarCRRSDPhiMT2("met", 30, -1);
    int njets_lo = fullSR.GetLowerBound("njets");
    int nbjets_lo = fullSR.GetLowerBound("nbjets");
    if     (njets_lo == 2 && nbjets_lo == 0){float mt2bins[6] = {200, 400, 600, 800, 1000, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 1){float mt2bins[5] = {200, 400, 600, 800, 1500};       fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 2){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 0){float mt2bins[6] = {200, 400, 600, 800, 1000, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 1){float mt2bins[5] = {200, 400, 600, 800, 1500};       fullSR.SetMT2Bins(4, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 2){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 0){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 1){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 2){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 3){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 3){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "UH");
    fullSR.SetVar("ht", 1500, -1);
    fullSR.SetVar("met", 30, -1);
    fullSR.SetVarCRSL("ht", 1500, -1);
    fullSR.SetVarCRSL("met", 30, -1);
    fullSR.SetVarCRRSInvertDPhi("ht", 1500, -1);
    fullSR.SetVarCRRSInvertDPhi("met", 30, -1);
    fullSR.SetVarCRRSMT2SideBand("ht", 1500, -1);
    fullSR.SetVarCRRSMT2SideBand("met", 30, -1);
    fullSR.SetVarCRRSDPhiMT2("ht", 1500, -1);
    fullSR.SetVarCRRSDPhiMT2("met", 30, -1);
    int njets_lo = fullSR.GetLowerBound("njets");
    int nbjets_lo = fullSR.GetLowerBound("nbjets");
    if     (njets_lo == 2 && nbjets_lo == 0){float mt2bins[6] = {200, 400, 600, 800, 1000, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 1){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 2){float mt2bins[2] = {200, 1500};                      fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 0){float mt2bins[6] = {200, 400, 600, 800, 1000, 1500}; fullSR.SetMT2Bins(5, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 1){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 2){float mt2bins[4] = {200, 400, 600, 1500};            fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 0){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 1){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 2){float mt2bins[3] = {200, 400, 1500};                 fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 3){float mt2bins[2] = {200, 1500};                      fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 3){float mt2bins[2] = {200, 1500};                      fullSR.SetMT2Bins(1, mt2bins);}
    SRVec.push_back(fullSR);
  }

  //define baseline selections commmon to all signal regions 
  baseSR.SetVar("mt2", 200, -1);
  baseSR.SetVar("j1pt", 100, -1);
  baseSR.SetVar("j2pt", 100, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  // common selections for CRSL
  baseSR.SetVarCRSL("mt2", 200, -1);
  baseSR.SetVarCRSL("j1pt", 100, -1);
  baseSR.SetVarCRSL("j2pt", 100, -1);
  baseSR.SetVarCRSL("deltaPhiMin", 0.3, -1);
  baseSR.SetVarCRSL("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRSL("nlep", 1, 2);

  baseSR.SetVarCRRSInvertDPhi("mt2", 200, -1);
  baseSR.SetVarCRRSInvertDPhi("j1pt", 100, -1);
  baseSR.SetVarCRRSInvertDPhi("j2pt", 100, -1);
  baseSR.SetVarCRRSInvertDPhi("deltaPhiMin", 0.0, 0.3);
  baseSR.SetVarCRRSInvertDPhi("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRRSInvertDPhi("nlep", 0, 1);

  baseSR.SetVarCRRSMT2SideBand("mt2", 100, 200);
  baseSR.SetVarCRRSMT2SideBand("j1pt", 100, -1);
  baseSR.SetVarCRRSMT2SideBand("j2pt", 100, -1);
  baseSR.SetVarCRRSMT2SideBand("deltaPhiMin", 0.3, -1);
  baseSR.SetVarCRRSMT2SideBand("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRRSMT2SideBand("nlep", 0, 1);

  baseSR.SetVarCRRSDPhiMT2("mt2", 100, 200);
  baseSR.SetVarCRRSDPhiMT2("j1pt", 100, -1);
  baseSR.SetVarCRRSDPhiMT2("j2pt", 100, -1);
  baseSR.SetVarCRRSDPhiMT2("deltaPhiMin", 0.0, 0.3);
  baseSR.SetVarCRRSDPhiMT2("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRRSDPhiMT2("nlep", 0, 1);

  //add baseline selections to all signal regions 
  std::vector<std::string> vars = baseSR.GetListOfVariables();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < vars.size(); j++){
      SRVec.at(i).SetVar(vars.at(j), baseSR.GetLowerBound(vars.at(j)), baseSR.GetUpperBound(vars.at(j)));
    }
  }

  //add baseline selections to all CRSL regions 
  std::vector<std::string> varsCRSL = baseSR.GetListOfVariablesCRSL();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < varsCRSL.size(); j++){
      SRVec.at(i).SetVarCRSL(varsCRSL.at(j), baseSR.GetLowerBoundCRSL(varsCRSL.at(j)), baseSR.GetUpperBoundCRSL(varsCRSL.at(j)));
    }
  }

  std::vector<std::string> varsCRRSInvertDPhi = baseSR.GetListOfVariablesCRRSInvertDPhi();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < varsCRRSInvertDPhi.size(); j++){
      SRVec.at(i).SetVarCRRSInvertDPhi(varsCRRSInvertDPhi.at(j), baseSR.GetLowerBoundCRRSInvertDPhi(varsCRSL.at(j)), baseSR.GetUpperBoundCRRSInvertDPhi(varsCRSL.at(j)));
    }
  }

  std::vector<std::string> varsCRRSMT2SideBand = baseSR.GetListOfVariablesCRRSMT2SideBand();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < varsCRRSMT2SideBand.size(); j++){
      SRVec.at(i).SetVarCRRSMT2SideBand(varsCRRSMT2SideBand.at(j), baseSR.GetLowerBoundCRRSMT2SideBand(varsCRSL.at(j)), baseSR.GetUpperBoundCRRSMT2SideBand(varsCRSL.at(j)));
    }
  }

  std::vector<std::string> varsCRRSDPhiMT2 = baseSR.GetListOfVariablesCRRSDPhiMT2();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < varsCRRSDPhiMT2.size(); j++){
      SRVec.at(i).SetVarCRRSDPhiMT2(varsCRRSDPhiMT2.at(j), baseSR.GetLowerBoundCRRSDPhiMT2(varsCRSL.at(j)), baseSR.GetUpperBoundCRRSDPhiMT2(varsCRSL.at(j)));
    }
  }

  return SRVec;

}

std::vector<SR> getSignalRegionsZurich_jetpt40(){

  std::vector<SR> SRVec = getSignalRegionsZurich();

  //change j1pt and j2pt cuts to 40 GeV
  for(unsigned int i = 0; i < SRVec.size(); i++){
    SRVec.at(i).RemoveVar("j1pt");
    SRVec.at(i).RemoveVar("j2pt");
    SRVec.at(i).SetVar("j1pt", 40, -1);
    SRVec.at(i).SetVar("j2pt", 40, -1);

    SRVec.at(i).RemoveVarCRSL("j1pt");
    SRVec.at(i).RemoveVarCRSL("j2pt");
    SRVec.at(i).SetVarCRSL("j1pt", 40, -1);
    SRVec.at(i).SetVarCRSL("j2pt", 40, -1);
  }

  return SRVec;

}

std::vector<SR> getSignalRegionsZurich_jetpt30(){

  std::vector<SR> SRVec = getSignalRegionsZurich();

  //change j1pt and j2pt cuts to 30 GeV
  for(unsigned int i = 0; i < SRVec.size(); i++){
    SRVec.at(i).RemoveVar("j1pt");
    SRVec.at(i).RemoveVar("j2pt");
    SRVec.at(i).SetVar("j1pt", 30, -1);
    SRVec.at(i).SetVar("j2pt", 30, -1);

    SRVec.at(i).RemoveVarCRSL("j1pt");
    SRVec.at(i).RemoveVarCRSL("j2pt");
    SRVec.at(i).SetVarCRSL("j1pt", 30, -1);
    SRVec.at(i).SetVarCRSL("j2pt", 30, -1);

    SRVec.at(i).RemoveVarCRRSInvertDPhi("j1pt");
    SRVec.at(i).RemoveVarCRRSInvertDPhi("j2pt");
    SRVec.at(i).SetVarCRRSInvertDPhi("j1pt", 30, -1);
    SRVec.at(i).SetVarCRRSInvertDPhi("j2pt", 30, -1);

    SRVec.at(i).RemoveVarCRRSMT2SideBand("j1pt");
    SRVec.at(i).RemoveVarCRRSMT2SideBand("j2pt");
    SRVec.at(i).SetVarCRRSMT2SideBand("j1pt", 30, -1);
    SRVec.at(i).SetVarCRRSMT2SideBand("j2pt", 30, -1);

    SRVec.at(i).RemoveVarCRRSDPhiMT2("j1pt");
    SRVec.at(i).RemoveVarCRRSDPhiMT2("j2pt");
    SRVec.at(i).SetVarCRRSDPhiMT2("j1pt", 30, -1);
    SRVec.at(i).SetVarCRRSDPhiMT2("j2pt", 30, -1);
  }

  return SRVec;

}

} // namespace mt2
