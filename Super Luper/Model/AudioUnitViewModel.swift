//
//  AudioUnitViewModel.swift
//  Super Luper
//
//  Created by Asher White on 2024-06-19.
//

import SwiftUI
import AudioToolbox
import CoreAudioKit

struct AudioUnitViewModel {
    var showAudioControls: Bool = false
    var showMIDIContols: Bool = false
    var title: String = "-"
    var message: String = "No Audio Unit loaded.."
    var viewController: ViewController?
}
