//
//  Parameters.swift
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-19.
//

import Foundation
import AudioToolbox

let Super_LuperExtensionParameterSpecs = ParameterTreeSpec {
    ParameterGroupSpec(identifier: "global", name: "Global") {
        ParameterSpec(
            address: .level,
            identifier: "level",
            name: "Level",
            units: .linearGain,
            valueRange: 0.0...1.5,
            defaultValue: 1.0
        );
        ParameterSpec(
            address: .gain,
            identifier: "gain",
            name: "Gain",
            units: .linearGain,
            valueRange: 0.0...1.5,
            defaultValue: 1.0
        );
        ParameterSpec(address: .playLoop, identifier: "playLoop", name: "Play Loop", units: .customUnit, valueRange: 0.0...1.0, defaultValue: 0.0);
        ParameterSpec(address: .writeLoop, identifier: "writeLoop", name: "Write Loop", units: .customUnit, valueRange: 0.0...1.0, defaultValue: 0.0);
    }
}

extension ParameterSpec {
    init(
        address: Super_LuperExtensionParameterAddress,
        identifier: String,
        name: String,
        units: AudioUnitParameterUnit,
        valueRange: ClosedRange<AUValue>,
        defaultValue: AUValue,
        unitName: String? = nil,
        flags: AudioUnitParameterOptions = [AudioUnitParameterOptions.flag_IsWritable, AudioUnitParameterOptions.flag_IsReadable],
        valueStrings: [String]? = nil,
        dependentParameters: [NSNumber]? = nil
    ) {
        self.init(address: address.rawValue,
                  identifier: identifier,
                  name: name,
                  units: units,
                  valueRange: valueRange,
                  defaultValue: defaultValue,
                  unitName: unitName,
                  flags: flags,
                  valueStrings: valueStrings,
                  dependentParameters: dependentParameters)
    }
}
