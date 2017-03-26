#ifndef SIGNALREGIONSLEP_H
#define SIGNALREGIONSLEP_H

#include <string>
#include "TTree.h"
#include "SR.h"

namespace mt2
{

  std::vector<SR> getSignalRegionsLep();
  std::vector<SR> getSignalRegionsLep2();
  std::vector<SR> getSignalRegionsLep3();
  std::vector<SR> getSignalRegionsLep4();

  //2017
  std::vector<SR> getSignalRegionsLep4withLepPt();
  std::vector<SR> getSignalRegionsLep5withLepPt();

} // namespace mt2

#endif // SIGNALREGIONSLEP_H
