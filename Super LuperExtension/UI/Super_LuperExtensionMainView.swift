//
//  Super_LuperExtensionMainView.swift
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-19.
//

import SwiftUI

struct Super_LuperExtensionMainView: View {
    var parameterTree: ObservableAUParameterGroup
    
    
//    var body: some View {
//        VStack {
//            ParameterSlider(param: parameterTree.global.gain);
//        }
//    }
    
    var body: some View {
        VStack {
            ParameterSlider(param: parameterTree.global.level);
            LooperButton(writeLoop: parameterTree.global.writeLoop, playLoop: parameterTree.global.playLoop);
        }
    }
}
