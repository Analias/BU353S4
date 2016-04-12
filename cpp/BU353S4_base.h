#ifndef BU353S4_BASE_IMPL_BASE_H
#define BU353S4_BASE_IMPL_BASE_H

#include <boost/thread.hpp>
#include <ossie/Device_impl.h>
#include <ossie/ThreadedComponent.h>

#include <frontend/frontend.h>

#define BOOL_VALUE_HERE 0

class BU353S4_base : public Device_impl, public virtual frontend::gps_delegation, protected ThreadedComponent
{
    public:
        BU353S4_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        BU353S4_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        BU353S4_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        BU353S4_base(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
        ~BU353S4_base();

        void start() throw (CF::Resource::StartError, CORBA::SystemException);

        void stop() throw (CF::Resource::StopError, CORBA::SystemException);

        void releaseObject() throw (CF::LifeCycle::ReleaseError, CORBA::SystemException);

        void loadProperties();
        void removeAllocationIdRouting(const size_t tuner_id);

    protected:
        // Member variables exposed as properties
        /// Property: device_kind
        std::string device_kind;
        /// Property: device_model
        std::string device_model;
        /// Property: serial_port
        std::string serial_port;

        // Ports
        /// Port: GPS_in
        frontend::InGPSPort *GPS_in;



    private:
        void construct();
};
#endif // BU353S4_BASE_IMPL_BASE_H
