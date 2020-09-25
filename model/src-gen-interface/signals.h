/**
 *  \file       signals.h
 *  \brief      Event signal definitions.
 */

/* -------------------------- Development history -------------------------- */
/*
 */

/* -------------------------------- Authors -------------------------------- */
/*
 */

/* --------------------------------- Notes --------------------------------- */
/* --------------------------------- Module -------------------------------- */
#ifndef __SIGNALS_H__
#define __SIGNALS_H__

/* ----------------------------- Include files ----------------------------- */
#include "priorities.h"
#include "rkhfwk_pubsub.h"

/* ---------------------- External C language linkage ---------------------- */
#ifdef __cplusplus
extern "C" {
#endif

/* --------------------------------- Macros -------------------------------- */
/* -------------------------------- Constants ------------------------------ */
/* ................................ Signals ................................ */
typedef enum Signals
{
   evSwitchOn,
   evSwitchOff,
   evRemoteStop,
   evRemoteIsolate,
   evRemoteDrift,
   evRemoteExit,
   evSpeedAvailable,
   evSpeedLost,
   evHaslerSpeedValid,
   evPulseGenSpeedValid,
   evGPSSpeedValid,
   evTout0,
   evTout1,
   evTout2,
   evTout3,
   evTout4,
   evTout5,
   evTout6,
   evTout7,
   evTout8,
   evOpen,
   evClose,
   evCmd,
   evResponse,
   evNoResponse,
   evURC,
   evTimeout,
   evRegStatusTout,
   evToutWaitResponse,
   evOk,
   evError,
   evToutDelay,
   evSimReady,
   evSimPin,
   evSimError,
   evNoReg,
   evOper,
   evReg,
   evIP,
   evIPInitial,
   evIPStart,
   evIPStatus,
   evIPGprsAct,
   evConnecting,
   evClosed,
   evConnected,
   evSend,
   evSendFail,
   evSent,
   evRecv,
   evRecvFail,
   evReceived,
   evNetConnected,
   evNetDisconnected,
   evDisconnected,
   evNetClockSync,
   evLocalTime,
   evUnlocked,
   evImei,
   evSigLevel,
   evRMC,
   evGeo,
   evGeoInvalid,
   evTurn,
   evDigInChanged,
   evRestart,
   evEndOfCycle,
   evSensorData,
   evTerminate,     /* press the key escape on the keyboard */
   evDevData,
   evNoDev,
   evGStatus,
   evSyncTout,
   evDigOutChanged,
   evMapping,
   evNoMapping,
   evToutSyncStopped,
   evToutSyncRunning,
   evDiskConnected,
   evDiskDisconnected,
   evGsmError,
   evGsmReady,
   evDataModeReady,
   evNoSMS,
   evNewSMS,
   evSendSMS,
   evSendSMSOk,
   evSendSMSFail,
   evDoneSMS,
   evBatChrStatus,
   evTrace,
   evUsbMounted,
   evUsbUnmounted,
   evFlowmeter,
   TERMINATE
} Signals;

/* ------------------------------- Data types ------------------------------ */
/* -------------------------- External variables --------------------------- */
/* -------------------------- Function prototypes -------------------------- */
void signalsPublishSymbols(void);

/* -------------------- External C language linkage end -------------------- */
#ifdef __cplusplus
}
#endif

/* ------------------------------ Module end ------------------------------- */
#endif

/* ------------------------------ End of file ------------------------------ */
