/*=============================================================================
 * Author: Nahuel Espinosa <nahue.espinosa@gmail.com>
 * Date: 2020/08/17
 *===========================================================================*/

/*=====[Inclusions of function dependencies]=================================*/

#include "safety.h"
#include "panel.h"
#include "relay.h"

/*=====[Implementation of public functions]==================================*/

void safetyIsolatedModeEnable(void) {
   relayWrite(RELAY_CT_1, RELAY_ON);
   relayWrite(RELAY_CT_2, RELAY_OFF);
   relayWrite(RELAY_CT_3, RELAY_ON);

   relayWrite(RELAY_FE_1, RELAY_ON);
   relayWrite(RELAY_FE_2, RELAY_OFF);
   relayWrite(RELAY_FE_3, RELAY_ON);

   relayWrite(RELAY_REG_4, RELAY_ON);

   panelLedWrite(PANEL_LED_CT, PANEL_LED_GREEN);
   panelLedWrite(PANEL_LED_AL, PANEL_LED_GREEN);
   panelLedWrite(PANEL_LED_FE, PANEL_LED_GREEN);
}

void safetyIsolatedModeDisable(void) {
   relayWrite(RELAY_CT_1, RELAY_OFF);
   relayWrite(RELAY_CT_2, RELAY_OFF);
   relayWrite(RELAY_CT_3, RELAY_OFF);

   relayWrite(RELAY_FE_1, RELAY_OFF);
   relayWrite(RELAY_FE_2, RELAY_OFF);
   relayWrite(RELAY_FE_3, RELAY_OFF);

   relayWrite(RELAY_REG_2, RELAY_OFF);
   relayWrite(RELAY_REG_3, RELAY_OFF);
   relayWrite(RELAY_REG_4, RELAY_OFF);

   panelLedWrite(PANEL_LED_AL, PANEL_LED_OFF);
   panelLedWrite(PANEL_LED_CT, PANEL_LED_OFF);
   panelLedWrite(PANEL_LED_FE, PANEL_LED_OFF);
   panelLedWrite(PANEL_LED_REMOTE, PANEL_LED_OFF);
   panelLedWrite(PANEL_LED_GPS, PANEL_LED_OFF);
}

void safetySignalActivateCT(void) {
   if( relayRead(RELAY_CT_1) && relayRead(RELAY_CT_3) ) {
      relayWrite(RELAY_CT_2, RELAY_ON);
      relayWrite(RELAY_REG_2, RELAY_ON);

      panelLedWrite(PANEL_LED_CT, PANEL_LED_RED);
   }
}

void safetySignalDeactivateCT(void) {
   if( relayRead(RELAY_CT_1) && relayRead(RELAY_CT_3) ) {
      relayWrite(RELAY_CT_2, RELAY_OFF);
      relayWrite(RELAY_REG_2, RELAY_OFF);

      panelLedWrite(PANEL_LED_CT, PANEL_LED_GREEN);
   }
}

void safetySignalActivateFE(void) {
   if( relayRead(RELAY_FE_1) && relayRead(RELAY_FE_3) ) {
      relayWrite(RELAY_FE_2, RELAY_ON);
      relayWrite(RELAY_REG_3, RELAY_ON);

      panelLedWrite(PANEL_LED_FE, PANEL_LED_RED);
   }
}

void safetySignalDeactivateFE(void) {
   if( relayRead(RELAY_FE_1) && relayRead(RELAY_FE_3) ) {
      relayWrite(RELAY_FE_2, RELAY_OFF);
      relayWrite(RELAY_REG_3, RELAY_OFF);

      panelLedWrite(PANEL_LED_FE, PANEL_LED_GREEN);
   }
}
