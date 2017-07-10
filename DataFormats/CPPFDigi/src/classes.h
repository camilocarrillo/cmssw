#include "DataFormats/CPPFDigi/interface/CPPFDigi.h"
#include "DataFormats/CPPFDigi/interface/CPPFDigiCollection.h"
#include "DataFormats/Common/interface/Wrapper.h"

#include <vector>
#include <map>

namespace DataFormats_CPPFDigi {
  struct dictionary {

    typedef edm::RangeMap <RPCDetId, edm::OwnVector<CPPFDigi>> CPPFDigiCollection;

    CPPFDigi rrh;
    std::vector<CPPFDigi> vrh;
    CPPFDigiCollection cc;
    edm::Wrapper<CPPFDigiCollection> ww;
  };
}

