#include "openel_impl.hpp"
#include "openel_impl_private.hpp"
#include <hako.hpp>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include "geometry_msgs/pdu_ctype_Twist.h"

#define HAKO_CONFIG_DELTA_TIME_USEC  100000
#define HAKO_CONFIG_ASSET_NAME  "OpenEL"
#define HAKO_CONFIG_ROBO_NAME  "TB3RoboModel"

static void reset_callback();
static void start_callback();
static void stop_callback();
static void hako_asset_signal_handler(int sig);

static std::string *hako_asset_name = nullptr;
static std::string *hako_robo_name = nullptr;
static bool hako_asset_is_end = false;
static HakoTimeType hako_asset_time_usec = 0LL;
static std::shared_ptr<hako::IHakoSimulationEventController> hako_sim_ctrl = nullptr;
static std::shared_ptr<hako::IHakoAssetController> hako_asset = nullptr;
static HakoTimeType hako_delta_usec = 1000;

void openel_init(int argc, const char* argv)
{
    hako_delta_usec = HAKO_CONFIG_DELTA_TIME_USEC;

    signal(SIGINT, hako_asset_signal_handler);
    signal(SIGTERM, hako_asset_signal_handler);

    hako_asset_name = new std::string(HAKO_CONFIG_ASSET_NAME);
    hako_robo_name = new std::string(HAKO_CONFIG_ROBO_NAME);

    hako::logger::init("core");
    hako_asset = hako::create_asset_controller();
    if (hako_asset == nullptr) {
        std::cout << "ERROR: Not found hako-master on this PC" << std::endl;
        return;
    }
    AssetCallbackType callback;
    callback.reset = reset_callback;
    callback.start = start_callback;
    callback.stop = stop_callback;
    bool ret = hako_asset->asset_register(*hako_asset_name, callback);
    if (ret == false) {
        std::cout << "ERROR: Can not register asset" << std::endl;
        return;
    }
    ret = hako_pdu_write_init(HAKO_PDU_CHANNEL_CMDVEL, sizeof(Hako_Twist));
    if (ret == false) {
        std::cout << "ERROR: hako_pdu_write_init() return error" << std::endl;
        return;
    }
    std::cout << "hako_pdu_write_init("<< HAKO_PDU_CHANNEL_CMDVEL << ", "<< sizeof(Hako_Twist) << ") ret=" << ret << std::endl;
    return;
}

void openel_sync()
{
    if (hako_asset->is_pdu_created() == false) {
        //std::cout << "not pdu created...yet" << std::endl;
    }
    else if (hako_asset->is_simulation_mode()) {
        hako_asset->notify_simtime(*hako_asset_name, hako_asset_time_usec);
        while (true) {
            HakoTimeType world_time = hako_asset->get_worldtime();
            if (world_time >= hako_asset_time_usec) {
                hako_asset_time_usec += hako_delta_usec;
                //std::cout << "TIME: " << hako_asset_time_usec << std::endl;
                break;
            }
            else {
                usleep(hako_delta_usec);
            }
        }
    }
    else if (hako_asset->is_pdu_sync_mode(*hako_asset_name)) {
        hako_asset->notify_write_pdu_done(*hako_asset_name);
    }
    return;
}

void hako_fin()
{
    hako_asset->asset_unregister(*hako_asset_name);
    return;
}
static void reset_callback()
{
    hako_asset_time_usec = 0;
    hako_asset->reset_feedback(*hako_asset_name, true);
}
static void start_callback()
{
    hako_asset->start_feedback(*hako_asset_name, true);
}
static void stop_callback()
{
    hako_asset->stop_feedback(*hako_asset_name, true);
}

static void hako_asset_signal_handler(int sig)
{
    if (hako_asset_name != nullptr) {
        printf("SIGNAL RECV: %d\n", sig);
    }
    hako_asset_is_end = true;
}

bool hako_pdu_read_data(HakoPduChannelIdType pdu_channel, char* pdu_msg, int buflen)
{
    if (hako_asset->is_pdu_created() == false) {
        return false;
    }
    else if (hako_asset->is_simulation_mode()) {
       if (hako_asset->is_pdu_dirty(*hako_asset_name, *hako_robo_name, pdu_channel)) {
           bool ret = hako_asset->read_pdu(*hako_asset_name, *hako_robo_name, pdu_channel, pdu_msg, buflen);
           hako_asset->notify_read_pdu_done(*hako_asset_name);
           return ret;
       }
    }
    return false;
}
bool hako_pdu_write_init(HakoPduChannelIdType pdu_channel, int buflen)
{
    return hako_asset->create_pdu_lchannel(*hako_robo_name, pdu_channel, buflen);
}
bool hako_pdu_write_data(HakoPduChannelIdType pdu_channel, char* pdu_msg, int buflen)
{
    if (hako_asset->is_pdu_created() == false) {
        return false;
    }
    else if (hako_asset->is_simulation_mode())
    {
        //printf("write_pdu\n");
        return hako_asset->write_pdu(*hako_asset_name, *hako_robo_name, pdu_channel, pdu_msg, buflen);
    }
    return false;
}

