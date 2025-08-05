#include "configuration.h"

#if !MESHTASTIC_EXCLUDE_ENVIRONMENTAL_SENSOR && __has_include(<TinySensor.h>)

#include "../mesh/generated/meshtastic/telemetry.pb.h"
#include "TelemetrySensor.h"
#include <TinySensor.h>

class MyTinySensor : public TelemetrySensor
{
  private:
    TinySensor tinySensor;

  protected:
    virtual void setup() override;

  public:
    MyTinySensor();
    virtual int32_t runOnce() override;
    virtual bool getMetrics(meshtastic_Telemetry *measurement) override;
};

#endif