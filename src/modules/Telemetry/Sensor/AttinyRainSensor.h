#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<TinyRain.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <TinyRain.h>

class TinyRainSensor : public TelemetrySensor
{
  private:
    TinyRain rainSensor;

  protected:
    virtual void setup() override;

  public:
    TinyRainSensor();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};

#endif