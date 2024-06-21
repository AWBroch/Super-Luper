//
//  Super_LuperExtensionDSPKernel.hpp
//  Super LuperExtension
//
//  Created by Asher White on 2024-06-19.
//

#pragma once

#import <AudioToolbox/AudioToolbox.h>
#import <algorithm>
#import <vector>
#import <span>

#import "Super_LuperExtension-Swift.h"
#import "Super_LuperExtensionParameterAddresses.h"

/*
 Super_LuperExtensionDSPKernel
 As a non-ObjC class, this is safe to use from render thread.
 */
class Super_LuperExtensionDSPKernel {
public:
    void initialize(int inputChannelCount, int outputChannelCount, double inSampleRate) {
        mSampleRate = inSampleRate;
        mChannelSamples.resize(inputChannelCount); // 10 minutes of samples
        for (int ch = 0; ch < inputChannelCount; ++ch) {
          mChannelSamples[ch] =
              std::vector<float>(inSampleRate * 60 * 10, 0.0);
        }
    }
    
    void deInitialize() {
    }
    
    // MARK: - Bypass
    bool isBypassed() {
        return mBypassed;
    }
    
    void setBypass(bool shouldBypass) {
        mBypassed = shouldBypass;
    }
    
    // MARK: - Parameter Getter / Setter
    void setParameter(AUParameterAddress address, AUValue value) {
        switch (address) {
            case Super_LuperExtensionParameterAddress::gain:
                mGain = value;
                break;
            case Super_LuperExtensionParameterAddress::level:
                mLevel = value;
                break;
            case Super_LuperExtensionParameterAddress::playLoop:
                if (mPlaying & !value) {
                  // ie, the loop is ending, clear it
                    mLoopIndex = 0;
                    mLoopLen = 0;
                } else if (!mPlaying && !!value) {
                    // ie, starting the loop
                    mLoopLen = mLoopIndex;
                    mLoopIndex = 0;
                }
                mPlaying = !!value;
                break;
            case Super_LuperExtensionParameterAddress::writeLoop:
                mWriting = !!value;
                break;
                // Add a case for each parameter in Super_LuperExtensionParameterAddresses.h
        }
    }
    
    AUValue getParameter(AUParameterAddress address) {
        // Return the goal. It is not thread safe to return the ramping value.
        
        switch (address) {
            case Super_LuperExtensionParameterAddress::gain:
                return (AUValue)mGain;
            case Super_LuperExtensionParameterAddress::level:
                return (AUValue)mLevel;
            case Super_LuperExtensionParameterAddress::playLoop:
                return (AUValue)(mPlaying ? 1.0 : 0.0);
            case Super_LuperExtensionParameterAddress::writeLoop:
                return (AUValue)(mWriting ? 1.0 : 0.0);
                
            default: return 0.f;
        }
    }
    
    // MARK: - Max Frames
    AUAudioFrameCount maximumFramesToRender() const {
        return mMaxFramesToRender;
    }
    
    void setMaximumFramesToRender(const AUAudioFrameCount &maxFrames) {
        mMaxFramesToRender = maxFrames;
    }
    
    // MARK: - Musical Context
    void setMusicalContextBlock(AUHostMusicalContextBlock contextBlock) {
        mMusicalContextBlock = contextBlock;
    }
    
    /**
     MARK: - Internal Process
     
     This function does the core siginal processing.
     Do your custom DSP here.
     */
    void process(std::span<float const*> inputBuffers, std::span<float *> outputBuffers, AUEventSampleTime bufferStartTime, AUAudioFrameCount frameCount) {
        /*
         Note: For an Audio Unit with 'n' input channels to 'n' output channels, remove the assert below and
         modify the check in [Super_LuperExtensionAudioUnit allocateRenderResourcesAndReturnError]
         */
        assert(inputBuffers.size() == outputBuffers.size());
        
        if (mBypassed) {
            // Pass the samples through
            for (UInt32 channel = 0; channel < inputBuffers.size(); ++channel) {
                std::copy_n(inputBuffers[channel], frameCount, outputBuffers[channel]);
            }
            return;
        }
        
        // Use this to get Musical context info from the Plugin Host,
        // Replace nullptr with &memberVariable according to the AUHostMusicalContextBlock function signature
        /*
         if (mMusicalContextBlock) {
         mMusicalContextBlock(nullptr, 	// currentTempo
         nullptr, 	// timeSignatureNumerator
         nullptr, 	// timeSignatureDenominator
         nullptr, 	// currentBeatPosition
         nullptr, 	// sampleOffsetToNextBeat
         nullptr);	// currentMeasureDownbeatPosition
         }
         */
        
        // Perform per sample dsp on the incoming float in before assigning it to out
        for (UInt32 channel = 0; channel < inputBuffers.size(); ++channel) {
            auto& loop = mChannelSamples[channel];
          for (UInt32 frameIndex = 0; frameIndex < frameCount; ++frameIndex) {

            // Do your sample by sample dsp here...
            float sample = inputBuffers[channel][frameIndex];
            if (mPlaying) {
              outputBuffers[channel][frameIndex] =
                  sample +
                      (loop[mLoopIndex % mLoopLen]) * mLevel;
            } else {
              outputBuffers[channel][frameIndex] =
                  sample;
            }
            if (mWriting) {
              loop[mLoopIndex] =
                  outputBuffers[channel][frameIndex];
              if (!mPlaying) { // Size determined on recording pass, not secondary ones
                mLoopIndex = (mLoopIndex + 1) % loop.size();
                mLoopLen = mLoopIndex;
              }
            }
            if (mPlaying) {
              mLoopIndex = (mLoopIndex + 1) % mLoopLen;
            }
          }
        }
    }
    
    void handleOneEvent(AUEventSampleTime now, AURenderEvent const *event) {
        switch (event->head.eventType) {
            case AURenderEventParameter: {
                handleParameterEvent(now, event->parameter);
                break;
            }
                
            default:
                break;
        }
    }
    
    void handleParameterEvent(AUEventSampleTime now, AUParameterEvent const& parameterEvent) {
        // Implement handling incoming Parameter events as needed
    }
    
    // MARK: Member Variables
    AUHostMusicalContextBlock mMusicalContextBlock;
    
    double mSampleRate = 44100.0;
    double mGain = 1.0;
    double mLevel = 1.0;
    bool mPlaying = false;
    bool mWriting = false;
    uint32_t mLoopIndex = 0;
    uint32_t mLoopLen = 0;
    std::vector<std::vector<float>> mChannelSamples;
    bool mBypassed = false;
    AUAudioFrameCount mMaxFramesToRender = 1024;
};
