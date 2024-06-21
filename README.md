# Super Luper Extension

This is a looper AudioUnit extension, tested with GarageBand. Press ‘L’ to loop!

Licensed under the Apache 2.0 License.

## Installation

Clone this repository and build it, then run the Super Luper.app that’s built. This should auto-register the AU plugin for use in GarageBand, other you can use `pluginkit -a` and `auval` to add the plugin (`/path/to/Super Luper.app/Contents/PlugIns/Super LuperExtension.app`) and check it.

## Project Layout

* /Common - Contains common code split by functionality
  
   * `Audio Unit/Super_LuperExtensionAudioUnit.mm/h` - A subclass of AUAudioUnit, this is the actual Audio Unit implementation.

* /Parameters
  
   * `Super_LuperExtensionParameterAddresses.h` - A pure `C` enum containing parameter addresses used by Swift and C++ to reference parameters.
  
   * `Parameters.swift` - Contains a ParameterTreeSpec object made up of ParameterGroupSpec's and ParameterSpec's which allow describe the plug-in's parameters and the layout of those parameters.

* /DSP
  
   * `Super_LuperExtensionDSPKernel.hpp` - A pure C++ class to handle the real-time aspects of the Audio Unit Extension. DSP and processing are done here.

* /UI
  
   * `Super_LuperExtensionMainView.swift` - SwiftUI based main view

## 

## Catalyst / iPhone and iPad apps on Mac with Apple silicon

To build this template in a Catalyst or iPhone/iPad App on Mac with Apple silicon, perform the following steps:  

1. Select your Xcode project in the left hand side file browser
2. Select your app target under the 'TARGETS' menu
3. Under 'Deployment Info' select 'Mac Catalyst' (Note: Skip this step for iPhone and iPad apps on Mac with Apple silicon)
4. Select the 'General' tab in the top menu bar
5. Under 'Frameworks, Libraries, and Embedded Content' click the button next to the  iOS filter
6. In the pop-up menu select 'Allow any platforms'

## More Information

[Apple Audio Developer Documentation](https://developer.apple.com/audio/)
