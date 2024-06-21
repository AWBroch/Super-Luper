//
//  Super_LuperApp.swift
//  Super Luper
//
//  Created by Asher White on 2024-06-19.
//

import CoreMIDI
import SwiftUI

@main
struct Super_LuperApp: App {
    @ObservedObject private var hostModel = AudioUnitHostModel()

    var body: some Scene {
        WindowGroup {
            ContentView(hostModel: hostModel)
        }
    }
}
