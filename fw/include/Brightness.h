#include "BH1750FVI.h"

/* calculates an 8-bit luma value based on current light intensity
   and configuration:
   luma = base + scale*intensity

   base is 8-bit
   scale is 8-bit
   intensity is 16-bit

   when scale is at max we want to reach max luma at 1/16 of max intensity
   therefore we need another scaling by 1/4096
*/
class Brightness {
    public:
    Brightness() {}
    ~Brightness() {}

    void setup(uint8_t _base, uint8_t _scale) {
        setScaleParams(_base, _scale);
        lightSensor.begin();
    }

    void setScaleParams(uint8_t _base, uint8_t _scale) {
        base = _base;
        scale = _scale;
    }

    uint8_t getLuma() {
        uint32_t intensity = lightSensor.GetLightIntensity();
        uint32_t luma32 = base + intensity * uint32_t(scale);
        luma32 >>= 12;
        return (luma32 > 255) ? 255 : luma32;
    }

    private:
    BH1750FVI lightSensor = BH1750FVI(BH1750FVI::k_DevModeContHighRes);
    uint8_t base;
    uint8_t scale;
};