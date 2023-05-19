#include <stdio.h>
#include <iostream>
#include <string.h>
#include <Actuator.hpp>
#include <Sensor.hpp>
#include "openel_common.hpp"
#include "openel_impl.hpp"

static Actuator* hako_motor_l;
static Actuator* hako_motor_r;
static Sensor* hako_sensor;
static float scan_ranges[360];
static float motor_velocity;
static float motor_angle;

static void hako_motor_init()
{
    HALId halid;
    halid.deviceKindId = 0x0001;
    halid.productId = 0x00000001;
    halid.vendorId = 0x0000000E;
    
    halid.instanceId = MOTOR_LEFT;
    hako_motor_l = new Actuator(halid);
    ReturnCode ret = hako_motor_l->Init();
    if (ret != HAL_OK) {
        std::cout << "ERROR: motor left init()" << std::endl;
        exit(1);
    }
    std::cout << "OpenEL Motor L init OK" << std::endl;

    halid.instanceId = MOTOR_RIGHT;
    hako_motor_r = new Actuator(halid);
    ret = hako_motor_r->Init();
    if (ret != HAL_OK) {
        std::cout << "ERROR: motor right init()" << std::endl;
        exit(1);
    }
    std::cout << "OpenEL Motor R init OK" << std::endl;
}
static void hako_sensor_init()
{
    HALId halid;
    halid.deviceKindId = 0x0002;
    halid.productId = 0x00000001;
    halid.vendorId = 0x0000000E;
    
    halid.instanceId = 0x1;
    hako_sensor = new Sensor(halid);
    ReturnCode ret = hako_sensor->Init();
    if (ret != HAL_OK) {
        std::cout << "ERROR: sensor init()" << std::endl;
        exit(1);
    }
    std::cout << "OpenEL Sensor init OK" << std::endl;
}
static void do_control(void);

int main(int argc, char **argv) 
{
    openel_init(argc, argv[1]);
    
    hako_motor_init();
    hako_sensor_init();
    while (true) {
        int num;
        hako_sensor->GetValueList(scan_ranges, &num);
        do_control();
        hako_motor_l->SetValue(Request::HAL_REQUEST_VELOCITY_CONTROL, motor_velocity);
        hako_motor_r->SetValue(Request::HAL_REQUEST_VELOCITY_CONTROL, motor_angle);

        openel_sync();
    }
    hako_sensor->Finalize();
    hako_motor_l->Finalize();
    hako_motor_r->Finalize();
    delete hako_motor_l;
    delete hako_motor_r;
    delete hako_sensor;

    std::cout << "EXIT" << std::endl;
    return 0;
}

/* control */
static float get_forward_distance(void) {
  int i;
  float min = 100.0f;
  for (i = 0; i < 15; i++) {
    if (scan_ranges[i] < min) {
      min = scan_ranges[i];
    }
  }
  for (i = (360 - 15); i < 360; i++) {
    if (scan_ranges[i] < min) {
      min = scan_ranges[i];
    }
  }
  // printf("forward: %lf\n", min);
  return min;
}

static float get_right_distance(void) {
  int i;
  float min = 100.0f;
  for (i = (90 - 30); i < (90 + 30); i++) {
    if (scan_ranges[i] < min) {
      min = scan_ranges[i];
    }
  }
  // printf("right: %lf\n", min);
  return min;
}

static bool do_forward(void) {
  bool is_stop = false;
  motor_velocity = 0;
  if (get_forward_distance() < 0.2f) {
    motor_velocity = 0;
    is_stop = true;
  } else {
    motor_velocity = 0.5f;
  }

  return is_stop;
}

static bool turn_right(void) {
  bool is_stop = false;
  motor_angle = 0;
  if (get_right_distance() < 0.05f) {
    motor_angle = -0.01;
    is_stop = true;
  } else {
    motor_angle = 0;
  }

  return is_stop;
}

static void do_control(void) 
{
  (void)do_forward();
  (void)turn_right();

  if (motor_velocity == 0 && motor_angle == 0) {
    motor_angle = -1.0f;
  }
  return;
}

