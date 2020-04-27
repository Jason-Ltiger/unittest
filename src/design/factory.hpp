


#include <memory>
#include <iostream>

class ProtocolLink;

class DataHandlerFactory
{
public:
    static DataHandlerFactory& getInstance() { return _instance; };

public:
    std::shared_ptr<ProtocolLink> CreateDefaultLink();
    std::shared_ptr<ProtocolLink> UdpDectect();
private:
    DataHandlerFactory() {};
    DataHandlerFactory(const DataHandlerFactory& cls) = delete;
    DataHandlerFactory& operator=(const DataHandlerFactory& cls) = delete;
    DataHandlerFactory(DataHandlerFactory&& cls) = delete;
    DataHandlerFactory& operator=(DataHandlerFactory&& cls) = delete;

private:
    static DataHandlerFactory _instance;
};