#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<TinyRain.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "AttinyRainSensor.h"
#include "TelemetrySensor.h"
#include <TinyRain.h>
#include <string>

TinyRainSensor::TinyRainSensor() : TelemetrySensor(meshtastic_TelemetrySensorType_CUSTOM_SENSOR, "ATTINY_RAIN") {}

int32_t TinyRainSensor::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    if (!hasSensor()) {
        return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
    }
    status = rainSensor.begin();

    return initI2CSensor();
}

void TinyRainSensor::setup() {}

bool TinyRainSensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_distance = true;
    
    LOG_DEBUG("TinyRain getMetrics");
    measurement->variant.environment_metrics.distance = rainSensor.read();
    LOG_DEBUG("measurement %f", measurement->variant.environment_metrics.distance);

    return true;
}
#endif