#ifndef SR_h
#define SR_h

#include <string>
#include <map>
#include <vector>

#include "TH1.h"
#include "RooDataSet.h"


class SR {

  public:

    SR();
    ~SR();

    void SetName(std::string sr_name);
    void SetVar(std::string var_name, float lower_bound, float upper_bound);
    void SetVarCRSL(std::string var_name, float lower_bound, float upper_bound);
    void SetVarCRRSInvertDPhi(std::string var_name, float lower_bound, float upper_bound);
    void SetVarCRRSMT2SideBand(std::string var_name, float lower_bound, float upper_bound);
    void SetVarCRRSDPhiMT2(std::string var_name, float lower_bound, float upper_bound);
    void SetMT2Bins(int nbins, float* bins);

    std::string GetName();

    float GetLowerBound(std::string var_name);
    float GetUpperBound(std::string var_name);
    unsigned int GetNumberOfVariables();
    std::vector<std::string> GetListOfVariables();

    float GetLowerBoundCRSL(std::string var_name);
    float GetUpperBoundCRSL(std::string var_name);
    unsigned int GetNumberOfVariablesCRSL();
    std::vector<std::string> GetListOfVariablesCRSL();

    float GetLowerBoundCRRSInvertDPhi(std::string var_name);
    float GetUpperBoundCRRSInvertDPhi(std::string var_name);
    unsigned int GetNumberOfVariablesCRRSInvertDPhi();
    std::vector<std::string> GetListOfVariablesCRRSInvertDPhi();

    float GetLowerBoundCRRSMT2SideBand(std::string var_name);
    float GetUpperBoundCRRSMT2SideBand(std::string var_name);
    unsigned int GetNumberOfVariablesCRRSMT2SideBand();
    std::vector<std::string> GetListOfVariablesCRRSMT2SideBand();

    float GetLowerBoundCRRSDPhiMT2(std::string var_name);
    float GetUpperBoundCRRSDPhiMT2(std::string var_name);
    unsigned int GetNumberOfVariablesCRRSDPhiMT2();
    std::vector<std::string> GetListOfVariablesCRRSDPhiMT2();

    float* GetMT2Bins();
    int GetNumberOfMT2Bins();

    bool PassesSelection(std::map<std::string, float> values);
    bool PassesSelectionCRSL(std::map<std::string, float> values);
    bool PassesSelectionCRRSInvertDPhi(std::map<std::string, float> values);
    bool PassesSelectionCRRSMT2SideBand(std::map<std::string, float> values);
    bool PassesSelectionCRRSDPhiMT2(std::map<std::string, float> values);
    void RemoveVar(std::string var_name);
    void RemoveVarCRSL(std::string var_name);
    void RemoveVarCRRSInvertDPhi(std::string var_name);
    void RemoveVarCRRSMT2SideBand(std::string var_name);
    void RemoveVarCRRSDPhiMT2(std::string var_name);
    void Clear();

    //used for plotting
    std::map<std::string, TH1*> srHistMap;
    std::map<std::string, TH1*> crslHistMap;
    std::map<std::string, TH1*> crslmuHistMap;
    std::map<std::string, TH1*> crslelHistMap;
    std::map<std::string, TH1*> crslhadHistMap;
    std::map<std::string, TH1*> crgjHistMap;
    std::map<std::string, RooDataSet*> crgjRooDataSetMap;
    std::map<std::string, TH1*> crdyHistMap;
    std::map<std::string, TH1*> crrlHistMap;
    std::map<std::string, TH1*> crrlmuHistMap;
    std::map<std::string, TH1*> crrlelHistMap;
    std::map<std::string, TH1*> crRSInvertDPhiHistMap;
    std::map<std::string, TH1*> crRSMT2SideBandHistMap;
    std::map<std::string, TH1*> crRSDPhiMT2HistMap;

  private:

    std::string srName_;
    std::map<std::string, std::pair<float, float> > bins_;
    std::map<std::string, std::pair<float, float> > binsCRSL_;
    std::map<std::string, std::pair<float, float> > binsCRRSInvertDPhi_;
    std::map<std::string, std::pair<float, float> > binsCRRSMT2SideBand_;
    std::map<std::string, std::pair<float, float> > binsCRRSDPhiMT2_;
    int n_mt2bins_;
    float *mt2bins_;

};

#endif
