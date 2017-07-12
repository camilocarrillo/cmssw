#include "DataFormats/CPPFDigi/interface/CPPFDigi.h"
#include "DataFormats/CPPFDigi/interface/CPPFDigiCollection.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <vector>

namespace DataFormats_CPPFDigi {
  struct dictionary {  
       
    CPPFDigi drf;
    std::vector<CPPFDigi> vrf;
    CPPFDigiCollection tt;
    edm::Wrapper<CPPFDigiCollection> jjo;
  };
}

