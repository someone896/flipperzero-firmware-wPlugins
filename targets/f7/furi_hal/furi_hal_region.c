#include <furi_hal_region.h>
#include <furi_hal_version.h>
#include <furi_hal_subghz.h>
#include <furi.h>

const FuriHalRegion furi_hal_region_no_limits = {
    .country_code = "ALL",  // Use a generic country code to signify no limits
    .bands_count = 1,  // Single band with no restrictions
    .bands = {
        {
            .start = 0,  // Start frequency set to 0 (no frequency restriction)
            .end = 9999999999,  // End frequency set to a very high value (no upper limit)
            .power_limit = 100,  // No power limit
            .duty_cycle = 100,  // No duty cycle limit
        },
    }
};

// Set the region to one with no restrictions
static const FuriHalRegion* furi_hal_region = NULL;

void furi_hal_region_init(void) {
    // Always initialize to the region with no limits
    furi_hal_region = &furi_hal_region_no_limits;
}

const FuriHalRegion* furi_hal_region_get(void) {
    return furi_hal_region;
}

void furi_hal_region_set(FuriHalRegion* region) {
    furi_check(region);

    // Set the region to the new one, though we might always use no-limit region
    furi_hal_region = region;
}

bool furi_hal_region_is_provisioned(void) {
    return furi_hal_region != NULL;
}

const char* furi_hal_region_get_name(void) {
    if(furi_hal_region) {
        return furi_hal_region->country_code;  // Always return "ALL" (indicating no restrictions)
    } else {
        return "--";
    }
}

// Frequency check always returns true (bypasses any restriction)
bool furi_hal_region_is_frequency_allowed(uint32_t frequency) {
    return true;  // Always allow any frequency
}

// No region limit, always return the first band (which has no limits)
const FuriHalRegionBand* furi_hal_region_get_band(uint32_t frequency) {
    if(!furi_hal_region) {
        return NULL;
    }

    // Always return the first band (it has no limits)
    return &furi_hal_region->bands[0];
}

// No limits on frequency, always return true for any frequency
bool _furi_hal_region_is_frequency_allowed(uint32_t frequency) {
    if(!furi_hal_region) {
        return false;
    }

    const FuriHalRegionBand* band = furi_hal_region_get_band(frequency);
    if(!band) {
        return false;
    }

    return true;
}
