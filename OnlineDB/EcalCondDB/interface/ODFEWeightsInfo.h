#ifndef ODFEWEIGHTSINFO_H
#define ODFEWEIGHTSINFO_H

#include <map>
#include <string>

#include "OnlineDB/EcalCondDB/interface/IODConfig.h"

class ODFEWeightsInfo : public IODConfig {
 public:
  friend class EcalCondDBInterface;
  ODFEWeightsInfo();
  ~ODFEWeightsInfo();

  // User data methods
  inline std::string getTable() { return "DCC_WEIGHTS_INFO"; }

  inline void setId(int id) { m_ID = id; }
  inline int getId() const { return m_ID; }

  // the tag is already in IODConfig 

  inline void setVersion(int id) { m_version = id; }
  inline int getVersion() const { return m_version; }

  int fetchNextId() throw(std::runtime_error);
  void setParameters(std::map<std::string,std::string> my_keys_map);
  int fetchID()  throw(std::runtime_error);
  
 private:
  void prepareWrite()  throw(std::runtime_error);

  void writeDB()       throw(std::runtime_error);

  void clear();

  void fetchData(ODFEWeightsInfo * result)     throw(std::runtime_error);



  // User data
  int m_ID;
  int m_version;

  
};

#endif
