#ifndef BU353S4_I_IMPL_H
#define BU353S4_I_IMPL_H

#include "BU353S4_base.h"

#include "nmea/nmea.h"

#include <boost/circular_buffer.hpp>
using namespace boost;


class BU353S4_i : public BU353S4_base
{
    ENABLE_LOGGING
    public:
        BU353S4_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl);
        BU353S4_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, char *compDev);
        BU353S4_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities);
        BU353S4_i(char *devMgr_ior, char *id, char *lbl, char *sftwrPrfl, CF::Properties capacities, char *compDev);
        ~BU353S4_i();

        void constructor();

        int serviceFunction();

		void start() throw(CF::Resource::StartError, CORBA::SystemException);
		void stop() throw(CF::Resource::StopError, CORBA::SystemException);

    protected:
        void updateUsageState();

    protected:
        frontend::GPSInfo get_gps_info(const std::string& port_name);
        void set_gps_info(const std::string& port_name, const frontend::GPSInfo &gps_info);
        frontend::GpsTimePos get_gps_time_pos(const std::string& port_name);
        void set_gps_time_pos(const std::string& port_name, const frontend::GpsTimePos &gps_time_pos);

    private:
        frontend::GPSInfo _gps_info;
        frontend::GpsTimePos _gps_time_pos;

        // File descriptor for serial stream from GPS
		// Circular buffer for NMEA messages
		// Mutex for reading the buffer
		// Worker thread instance to avoid blocking service_function
		int _gps_fd;
		circular_buffer<unsigned char> _buffer;
		mutex _bufferMutex;
		thread *_worker;

		// For NMEA
		nmeaPARSER _parser;
		nmeaINFO _bufferInfo;

		void _connect_serial_port();
		void _worker_function();
		void _configure_serial_port(const char* oldValue, const char* newValue);
};

#endif // BU353S4_I_IMPL_H
