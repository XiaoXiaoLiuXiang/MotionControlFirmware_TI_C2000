/******************************************************************************
 * Copyright (C) 2017 by Yifan Jiang                                          *
 * jiangyi@student.ethz.com                                                   *
 *                                                                            *
 * This program is distributed in the hope that it will be useful,            *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                       *
 ******************************************************************************/

/*
* current loop sweep sine class
*
* Control the execution of current loop sweep sine, to obtain the frequency
* domain response of the current loop. This is the sweep sine process
* controller and setpoint generator only, current loop is executed by CLA.
*/

#ifndef _CURRENT_LOOP_SWEEPSINE_H
#define _CURRENT_LOOP_SWEEPSINE_H

#include "ControlProcessData.h"
#include "CurrentLoopController.h"
#include "ObjectDictionaryEntryBase.h"

class CurrentLoopSweepSine : public ControlProcessBase, public ObjectDictionaryEntryBase{

  public:
    CurrentLoopSweepSine(CurrentLoopController * CurrentLoopControllerPtr,
                          ControlProcessData * ControlProcessDataPtr):
      _State(STATE_WAIT_SYNC)
    {
      _CurrentLoopController = CurrentLoopControllerPtr;
      _ControlProcessData = ControlProcessDataPtr;

      _ActivePhase = 'A';

      _ExcitationAmplitude = 100;
      _StartFreq = 600;
      _EndFreq = 7600;
      _RampRate = 7000;
      _HalfRampRate = 0;

      _NumberOfPkg = 0xFFFFFFFF;
      _TimeMax = 0;
      _TimeStamp = 0;
    }

    ~CurrentLoopSweepSine(){}

    enum CurrentLoopSweepSine_STATE{
      STATE_WAIT_SYNC,
      STATE_RUNNING,
      STATE_END
    };

    virtual void Execute(void);
    virtual void Reset(void);

    void GetCurrentHistory(float32_t * buffer);

    void AccessExcitationAmplitude(ObdAccessHandle * handle);
    void AccessDataLength(ObdAccessHandle * handle);
    void AccessStartFrequency(ObdAccessHandle * handle);
    void AccessEndFrequency(ObdAccessHandle * handle);
    void AccessRampRate(ObdAccessHandle * handle);

    void AccessActivePhase(ObdAccessHandle * handle);

  private:

    void CalculateSweepSineParameters(void);
    float32_t GenerateSweepSine(void);

    CurrentLoopController * _CurrentLoopController;
    ControlProcessData * _ControlProcessData;

    char _ActivePhase;

    enum CurrentLoopSweepSine_STATE _State;
    float32_t _ExcitationAmplitude;
    float32_t _StartFreq;              // unit: rad/s
    float32_t _EndFreq;
    float32_t _RampRate;               // unit: rad/(s^2)
    float32_t _HalfRampRate;

    uint32_t _NumberOfPkg;
    uint32_t _TimeMax;
    uint32_t _TimeStamp;

    char _OldPdoID;
};

#endif
