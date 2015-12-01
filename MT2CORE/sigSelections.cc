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
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("8");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("9");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 2, 7);
  sr.SetVarCRSL("nbjets", 3, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("11");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
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
  }

  return SRVec;

}

std::vector<SR> getSignalRegionsJamboree(){

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
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("2");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("3");
  sr.SetVar("njets", 2, 4);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 2, 4);
  sr.SetVarCRSL("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("4");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("5");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 1, 2);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("6");
  sr.SetVar("njets", 4, 7);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 4, 7);
  sr.SetVarCRSL("nbjets", 2, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("7");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 0, 1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 0, 1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("8");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 1, 2);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("9");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 2, 3);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  sr.SetName("10");
  sr.SetVar("njets", 2, 7);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 2, 7);
  sr.SetVarCRSL("nbjets", 3, -1);
  temp_SR_vec.push_back(sr);
  sr.Clear();

  // shared CR: 7j1-2b
  sr.SetName("11");
  sr.SetVar("njets", 7, -1);
  sr.SetVar("nbjets", 3, -1);
  sr.SetVarCRSL("njets", 7, -1);
  sr.SetVarCRSL("nbjets", 1, 3);
  temp_SR_vec.push_back(sr);
  sr.Clear();


  //add HT and MET requirements
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "VL");
    fullSR.SetVar("ht", 200, 450);
    fullSR.SetVar("met", 200, -1);
    fullSR.SetVarCRSL("ht", 200, 450);
    fullSR.SetVarCRSL("met", 200, -1);
    fullSR.SetVarCRQCD("ht", 200, 450);
    fullSR.SetVarCRQCD("met", 200, -1);
    int njets_lo = fullSR.GetLowerBound("njets");
    int nbjets_lo = fullSR.GetLowerBound("nbjets");
    if     (njets_lo == 2 && nbjets_lo == 0){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 1){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 2){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 0){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 1){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 4 && nbjets_lo == 2){float mt2bins[4] = {200, 300, 400, 1500}; fullSR.SetMT2Bins(3, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 0){float mt2bins[2] = {200, 1500};           fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 1){float mt2bins[2] = {200, 1500};           fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 2){float mt2bins[2] = {200, 1500};           fullSR.SetMT2Bins(1, mt2bins);}
    else if(njets_lo == 2 && nbjets_lo == 3){float mt2bins[3] = {200, 300, 1500};      fullSR.SetMT2Bins(2, mt2bins);}
    else if(njets_lo == 7 && nbjets_lo == 3){float mt2bins[2] = {200, 1500};           fullSR.SetMT2Bins(1, mt2bins);}
    SRVec.push_back(fullSR);
  }
  for(unsigned int iSR = 0; iSR < temp_SR_vec.size(); iSR++){
    SR fullSR = temp_SR_vec.at(iSR);  
    fullSR.SetName(fullSR.GetName() + "L");
    fullSR.SetVar("ht", 450, 575);
    fullSR.SetVar("met", 200, -1);
    fullSR.SetVarCRSL("ht", 450, 575);
    fullSR.SetVarCRSL("met", 200, -1);
    fullSR.SetVarCRQCD("ht", 450, 575);
    fullSR.SetVarCRQCD("met", 200, -1);
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
    fullSR.SetVarCRQCD("ht", 575, 1000);
    fullSR.SetVarCRQCD("met", 200, -1);
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
    fullSR.SetVarCRQCD("ht", 1000, 1500);
    fullSR.SetVarCRQCD("met", 30, -1);
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
    fullSR.SetVarCRQCD("ht", 1500, -1);
    fullSR.SetVarCRQCD("met", 30, -1);
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
  baseSR.SetVar("j1pt", 30, -1);
  baseSR.SetVar("j2pt", 30, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVar("nlep", 0, 1);
  //baseSR.SetVar("passesHtMet", 1, 1);

  // common selections for CRSL
  baseSR.SetVarCRSL("mt2", 200, -1);
  baseSR.SetVarCRSL("j1pt", 30, -1);
  baseSR.SetVarCRSL("j2pt", 30, -1);
  baseSR.SetVarCRSL("deltaPhiMin", 0.3, -1);
  baseSR.SetVarCRSL("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRSL("nlep", 1, 2);

  // common selections for QCD
  baseSR.SetVarCRQCD("mt2", 200, -1);
  baseSR.SetVarCRQCD("j1pt", 30, -1);
  baseSR.SetVarCRQCD("j2pt", 30, -1);
  baseSR.SetVarCRQCD("deltaPhiMin", 0., 0.3);
  baseSR.SetVarCRQCD("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRQCD("nlep", 0, 1);

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

  //add baseline selections to all QCD regions 
  std::vector<std::string> varsCRQCD = baseSR.GetListOfVariablesCRQCD();
  for(unsigned int i = 0; i < SRVec.size(); i++){
    for(unsigned int j = 0; j < varsCRQCD.size(); j++){
      SRVec.at(i).SetVarCRQCD(varsCRQCD.at(j), baseSR.GetLowerBoundCRQCD(varsCRQCD.at(j)), baseSR.GetUpperBoundCRQCD(varsCRQCD.at(j)));
    }
  }

  return SRVec;

}
  

std::vector<SR> getSignalRegionsMonojet(){

  std::vector<SR> temp_SR_vec;
  std::vector<SR> SRVec;
  SR baseSR;

  // define baseline selections commmon to all monojet regions
  float mt2bins_monojet[2] = {0, 1500};
  baseSR.SetVar("j1pt", 200, -1);
  baseSR.SetVar("nlep", 0, 1);
  baseSR.SetVar("njets", 1, 2);
  baseSR.SetVar("met", 200, -1);
  baseSR.SetVar("deltaPhiMin", 0.3, -1);
  baseSR.SetVar("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetVarCRSL("j1pt", 200, -1);
  baseSR.SetVarCRSL("nlep", 1, 2);
  baseSR.SetVarCRSL("njets", 1, 2);
  baseSR.SetVarCRSL("met", 200, -1);
  baseSR.SetVarCRSL("deltaPhiMin", 0.3, -1);
  baseSR.SetVarCRSL("diffMetMhtOverMet", 0, 0.5);
  // QCD region: 2 jets, low deltaPhiMin, pt subleading between 30 and 60 GeV
  baseSR.SetVarCRQCD("j1pt", 200, -1);
  baseSR.SetVarCRQCD("j2pt", 30, 60);
  baseSR.SetVarCRQCD("nlep", 0, 1);
  baseSR.SetVarCRQCD("njets", 2, 3);
  baseSR.SetVarCRQCD("met", 200, -1);
  baseSR.SetVarCRQCD("deltaPhiMin", 0., 0.3);
  baseSR.SetVarCRQCD("diffMetMhtOverMet", 0, 0.5);
  baseSR.SetMT2Bins(1, mt2bins_monojet);

  // fine binning in HT
  const int nbins_monojet_0b = 7;
  float htbins_0b[nbins_monojet_0b+1] = {200, 250, 350, 450, 575, 700, 1000, -1};
  const int nbins_monojet_1b = 5;
  float htbins_1b[nbins_monojet_1b+1] = {200, 250, 350, 450, 575, -1};

  temp_SR_vec.clear();
  for(unsigned int iSR = 0; iSR < nbins_monojet_0b; iSR++){
    SR fullSR0b = baseSR;  
    fullSR0b.SetName(std::to_string(iSR+1) + "J");
    fullSR0b.SetVar("ht", htbins_0b[iSR], htbins_0b[iSR+1]);
    fullSR0b.SetVar("nbjets", 0, 1);
    fullSR0b.SetVarCRSL("ht", htbins_0b[iSR], htbins_0b[iSR+1]);
    fullSR0b.SetVarCRSL("nbjets", 0, 1);
    fullSR0b.SetVarCRQCD("ht", htbins_0b[iSR], htbins_0b[iSR+1]);
    fullSR0b.SetVarCRQCD("nbjets", 0, 1);
    SRVec.push_back(fullSR0b);
  }
  for(unsigned int iSR = 0; iSR < nbins_monojet_1b; iSR++){
    SR fullSR1b = baseSR;  
    fullSR1b.SetName(std::to_string(iSR+11) + "J");
    fullSR1b.SetVar("ht", htbins_1b[iSR], htbins_1b[iSR+1]);
    fullSR1b.SetVar("nbjets", 1, -1);
    fullSR1b.SetVarCRSL("ht", htbins_1b[iSR], htbins_1b[iSR+1]);
    fullSR1b.SetVarCRSL("nbjets", 1, -1);
    fullSR1b.SetVarCRQCD("ht", htbins_1b[iSR], htbins_1b[iSR+1]);
    fullSR1b.SetVarCRQCD("nbjets", 1, -1);
    SRVec.push_back(fullSR1b);
  }


  // Also put in some inclusive regions: 0b, 1b
  SR fullSR0b = baseSR;  
  fullSR0b.SetName("baseJ0B");
  fullSR0b.SetVar("nbjets", 0, 1);
  fullSR0b.SetVarCRSL("nbjets", 0, 1);
  fullSR0b.SetVarCRQCD("nbjets", 0, 1);
  fullSR0b.SetVar("ht", 200, -1);
  fullSR0b.SetVarCRSL("ht", 200, -1);
  fullSR0b.SetVarCRQCD("ht", 200, -1);
  fullSR0b.SetMT2Bins(nbins_monojet_0b, htbins_0b);
  SRVec.push_back(fullSR0b);

  SR fullSR1b = baseSR;  
  fullSR1b.SetName("baseJ1B");
  fullSR1b.SetVar("nbjets", 1, -1);
  fullSR1b.SetVarCRSL("nbjets", 1, -1);
  fullSR1b.SetVarCRQCD("nbjets", 1, -1);
  fullSR1b.SetVar("ht", 200, -1);
  fullSR1b.SetVarCRSL("ht", 200, -1);
  fullSR1b.SetVarCRQCD("ht", 200, -1);
  fullSR1b.SetMT2Bins(nbins_monojet_1b, htbins_1b);
  SRVec.push_back(fullSR1b);

  return SRVec;

}


  
} // namespace mt2
