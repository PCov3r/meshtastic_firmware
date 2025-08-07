#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<hp_BH1750.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "DFRobotLuxSensor.h"
#include "TelemetrySensor.h"
#include <hp_BH1750.h>
#include <string>

DFRobotLuxSensor::DFRobotLuxSensor() : TelemetrySensor(meshtastic_TelemetrySensorType_DFROBOT_LUX, "DFROBOT_LUX") {}

int32_t DFRobotLuxSensor::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    if (!hasSensor()) {
        return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
    }
    status = BH1750.begin(nodeTelemetrySensorsMap[sensorType].first);

    BH1750.calibrateTiming();

    return initI2CSensor();
}

void DFRobotLuxSensor::setup()
{
    LOG_DEBUG("%s Conversion time: %dms\n, Quality: %x, Mtreg: %d", sensorName, BH1750.getMtregTime(), BH1750.getQuality(), BH1750.getMtreg());
}

bool DFRobotLuxSensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_lux = true;

    LOG_DEBUG("DFRobot LUX BH1750 getMetrics");
    BH1750.start();   
    measurement->variant.environment_metrics.lux = BH1750.getLux();;

    LOG_INFO("Lux: %f ", measurement->variant.environment_metrics.lux);
    return true;
}

#endif