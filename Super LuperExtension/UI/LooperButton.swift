//
//  LooperButton.swift
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-20.
//

import SwiftUI

struct LooperButton: View {
    @ObservedObject var writeLoop: ObservableAUParameter
    @ObservedObject var playLoop: ObservableAUParameter
    
    @State var monitor: Any?;
    
    
    var body: some View {
                    Button(action: {
                        if writeLoop.value != 0.0 {
                            if playLoop.value != 0.0 {
                                writeLoop.value = 0.0;
                            } else {
                                playLoop.value = 1.0;
                            }
                        } else {
                            if playLoop.value != 0.0 {
                                playLoop.value = 0.0;
                            } else {
                                writeLoop.value = 1.0;
                            }
                        }
                    }) {
                        Text(writeLoop.value != 0.0 ? (playLoop.value != 0.0 ? "Stop Recording (L)" : "Start Overdub (L)") : (playLoop.value != 0.0 ? "Stop Loop (L)" : "Start Recording (L)"));
                    }
                    .focusSection() 
            .keyboardShortcut("l", modifiers: .command)
            .padding()
            .onAppear {
                    monitor = NSEvent.addLocalMonitorForEvents(matching: .keyDown, handler: {(event) -> NSEvent? in
                        NSLog("Key pressed: %d", event.keyCode);
                        if (event.keyCode == 37) {
                            NSLog("L pressed");
                            if writeLoop.value != 0.0 {
                                if playLoop.value != 0.0 {
                                    writeLoop.value = 0.0;
                                } else {
                                    playLoop.value = 1.0;
                                }
                            } else {
                                if playLoop.value != 0.0 {
                                    playLoop.value = 0.0;
                                } else {
                                    writeLoop.value = 1.0;
                                }
                            }
                            return nil;
                        }
                        return event;
                    });
            }
            .onDisappear {
                if let monitorNotNull = monitor {
                    NSEvent.removeMonitor(monitorNotNull);
                }
            };
    }
}
