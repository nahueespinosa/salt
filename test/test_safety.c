#include "safety.h"
#include "mock_relay.h"
#include "mock_panel.h"

void setUp() {

}

void tearDown() {

}

void test_safetyIsolatedModeEnable() {
   relayWrite_Expect(RELAY_CT_1, RELAY_ON);
   relayWrite_Expect(RELAY_CT_2, RELAY_OFF);
   relayWrite_Expect(RELAY_CT_3, RELAY_ON);

   relayWrite_Expect(RELAY_FE_1, RELAY_ON);
   relayWrite_Expect(RELAY_FE_2, RELAY_OFF);
   relayWrite_Expect(RELAY_FE_3, RELAY_ON);

   relayWrite_Expect(RELAY_REG_4, RELAY_ON);

   panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_GREEN);
   panelLedWrite_Expect(PANEL_LED_AL, PANEL_LED_GREEN);
   panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_GREEN);

   safetyIsolatedModeEnable();
}

void test_safetyIsolatedModeDisable() {
   relayWrite_Expect(RELAY_CT_1, RELAY_OFF);
   relayWrite_Expect(RELAY_CT_2, RELAY_OFF);
   relayWrite_Expect(RELAY_CT_3, RELAY_OFF);

   relayWrite_Expect(RELAY_FE_1, RELAY_OFF);
   relayWrite_Expect(RELAY_FE_2, RELAY_OFF);
   relayWrite_Expect(RELAY_FE_3, RELAY_OFF);

   relayWrite_Expect(RELAY_REG_2, RELAY_OFF);
   relayWrite_Expect(RELAY_REG_3, RELAY_OFF);
   relayWrite_Expect(RELAY_REG_4, RELAY_OFF);

   panelLedWrite_Expect(PANEL_LED_AL, PANEL_LED_OFF);
   panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_OFF);
   panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_OFF);
   panelLedWrite_Expect(PANEL_LED_REMOTE, PANEL_LED_OFF);
   panelLedWrite_Expect(PANEL_LED_GPS, PANEL_LED_OFF);

   safetyIsolatedModeDisable();
}

void test_whenIsolated_thenActivateCT() {
    relayRead_ExpectAndReturn(RELAY_CT_1, RELAY_ON);
    relayRead_ExpectAndReturn(RELAY_CT_3, RELAY_ON);

    relayWrite_Expect(RELAY_CT_2, RELAY_ON);
    relayWrite_Expect(RELAY_REG_2, RELAY_ON);

    panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_RED);

    safetySignalActivateCT();
}

void test_whenNotIsolated_thenDontActivateCT() {
    relayRead_IgnoreAndReturn(RELAY_OFF);

    safetySignalActivateCT();
}

void test_whenIsolated_thenActivateFE() {
    relayRead_ExpectAndReturn(RELAY_FE_1, RELAY_ON);
    relayRead_ExpectAndReturn(RELAY_FE_3, RELAY_ON);

    relayWrite_Expect(RELAY_FE_2, RELAY_ON);
    relayWrite_Expect(RELAY_REG_3, RELAY_ON);

    panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_RED);

    safetySignalActivateFE();
}

void test_whenNotIsolated_thenDontActivateFE() {
    relayRead_IgnoreAndReturn(RELAY_OFF);

    safetySignalActivateFE();
}