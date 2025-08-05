#pragma once

#ifndef _MT_DFROBOTLUXSENSOR_H
#define _MT_DFROBOTLUXSENSOR_H
#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<hp_BH1750.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <hp_BH1750.h>
#include <string>

class DFRobotLuxSensor : public TelemetrySensor
{
  private:
    hp_BH1750 BH1750;

  protected:
    virtual void setup() override;

  public:
    DFRobotLuxSensor();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};

#endif
#endif