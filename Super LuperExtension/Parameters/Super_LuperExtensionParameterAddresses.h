//
//  Super_LuperExtensionParameterAddresses.h
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-19.
//

#pragma once

#include <AudioToolbox/AUParameters.h>

#ifdef __cplusplus
namespace Super_LuperExtensionParameterAddress {
#endif

typedef NS_ENUM(AUParameterAddress, Super_LuperExtensionParameterAddress) {
    gain = 0,
    level,
    playLoop,
    writeLoop
};

#ifdef __cplusplus
}
#endif
