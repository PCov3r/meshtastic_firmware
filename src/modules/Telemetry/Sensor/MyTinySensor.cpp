#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<TinySensor.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "MyTinySensor.h"
#include "TelemetrySensor.h"
#include <TinySensor.h>
#include <string>

MyTinySensor::MyTinySensor() : TelemetrySensor(meshtastic_TelemetrySensorType_CUSTOM_SENSOR, "ATTINY_HELPER") {}

int32_t MyTinySensor::runOnce()
{
    LOG_INFO("Init sensor: %s", sensorName);
    if (!hasSensor()) {
        return DEFAULT_SENSOR_MINIMUM_WAIT_TIME_BETWEEN_READS;
    }
    status = tinySensor.begin(nodeTelemetrySensorsMap[sensorType].first);

    return initI2CSensor();
}

void MyTinySensor::setup() {}

bool MyTinySensor::getMetrics(meshtastic_Telemetry *measurement)
{
    measurement->variant.environment_metrics.has_distance = true;
    measurement->variant.environment_metrics.has_rainfall_1h = true;
    measurement->variant.environment_metrics.has_rainfall_24h = true;
    measurement->variant.environment_metrics.has_wind_direction = true;
    measurement->variant.environment_metrics.has_wind_speed = true;
    measurement->variant.environment_metrics.has_wind_gust = true;
    
    LOG_DEBUG("TinySensor getMetrics");
    measurement->variant.environment_metrics.distance = tinySensor.getInstantRain();
    measurement->variant.environment_metrics.wind_gust = tinySensor.getAverageWind();
    tinySensor.requestAll(1);
    measurement->variant.environment_metrics.rainfall_1h = tinySensor.getAverageRainResult();
    measurement->variant.environment_metrics.wind_direction = tinySensor.getInstantDirResult();
    measurement->variant.environment_metrics.wind_speed = tinySensor.getInstantWindResult();
    tinySensor.requestAverageRain(24);
    measurement->variant.environment_metrics.rainfall_24h = tinySensor.getAverageRainResult();

    return true;
}
#endif