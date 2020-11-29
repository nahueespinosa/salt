#include "safety.h"
#include "mock_relay.h"
#include "mock_panel.h"

#define LSB     1

uint16_t relay_status;

static void relayWrite_Callback(relay_t relay, bool value) {
    if (value) {
        relay_status |= LSB << relay;
    } else {
        relay_status &= ~(LSB << relay);
    }
}

static bool relayRead_Callback(relay_t relay) {
    return relay_status & (LSB << relay) ? true : false;
}

void setUp() {
    relay_status = 0;

    relayWrite_Stub((CMOCK_relayWrite_CALLBACK)relayWrite_Callback);
    relayRead_Stub((CMOCK_relayRead_CALLBACK)relayRead_Callback);
}

void tearDown() {

}

void test_whenIsolated_thenTurnOnStateLeds() {
    panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_GREEN);
    panelLedWrite_Expect(PANEL_LED_AL, PANEL_LED_GREEN);
    panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_GREEN);

    safetyIsolatedModeEnable();
}

void test_whenNotIsolated_thenTurnOffStateLeds() {
    panelLedWrite_Expect(PANEL_LED_AL, PANEL_LED_OFF);
    panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_OFF);
    panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_OFF);
    panelLedWrite_Expect(PANEL_LED_REMOTE, PANEL_LED_OFF);
    panelLedWrite_Expect(PANEL_LED_GPS, PANEL_LED_OFF);

    safetyIsolatedModeDisable();
}

void test_whenIsolated_thenEnableCTControl() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(true , relayRead_Callback(RELAY_CT_1));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_2));
    TEST_ASSERT_EQUAL(true , relayRead_Callback(RELAY_CT_3));
}

void test_whenIsolated_thenEnableFEControl() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(true , relayRead_Callback(RELAY_FE_1));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_2));
    TEST_ASSERT_EQUAL(true , relayRead_Callback(RELAY_FE_3));
}

void test_whenIsolated_thenRegisterEvent() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(true , relayRead_Callback(RELAY_REG_4));
}

void test_whenNotIsolated_thenDisableCTControl() {
    panelLedWrite_Ignore();
    safetyIsolatedModeDisable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_1));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_3));
}

void test_whenNotIsolated_thenDisableFEControl() {
    panelLedWrite_Ignore();
    safetyIsolatedModeDisable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_1));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_3));
}

void test_whenNotIsolated_thenRegisterEvent() {
    panelLedWrite_Ignore();
    safetyIsolatedModeDisable();
    panelLedWrite_StopIgnore();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_REG_4));
}

void test_whenActivatingCT_ifIsolated_thenAllow() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_RED);

    safetySignalActivateCT();

    TEST_ASSERT_EQUAL(true, relayRead_Callback(RELAY_CT_2));
    TEST_ASSERT_EQUAL(true, relayRead_Callback(RELAY_REG_2));
}

void test_whenActivatingCT_ifNotIsolated_thenDeny() {
    panelLedWrite_Ignore();
    safetyIsolatedModeDisable();
    panelLedWrite_StopIgnore();

    safetySignalActivateCT();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_REG_2));
}

void test_whenDeactivatingCT_ifIsolated_thenAllow() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    panelLedWrite_Expect(PANEL_LED_CT, PANEL_LED_GREEN);

    safetySignalDeactivateCT();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_CT_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_REG_2));
}

void test_whenActivatingFE_ifIsolated_thenAllow() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_RED);

    safetySignalActivateFE();

    TEST_ASSERT_EQUAL(true, relayRead_Callback(RELAY_FE_2));
    TEST_ASSERT_EQUAL(true, relayRead_Callback(RELAY_REG_3));
}

void test_whenActivatingFE_ifNotIsolated_thenDeny() {
    panelLedWrite_Ignore();
    safetyIsolatedModeDisable();
    panelLedWrite_StopIgnore();

    safetySignalActivateFE();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_REG_3));
}

void test_whenDeactivatingFE_ifIsolated_thenAllow() {
    panelLedWrite_Ignore();
    safetyIsolatedModeEnable();
    panelLedWrite_StopIgnore();

    panelLedWrite_Expect(PANEL_LED_FE, PANEL_LED_GREEN);

    safetySignalDeactivateFE();

    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_FE_2));
    TEST_ASSERT_EQUAL(false, relayRead_Callback(RELAY_REG_3));
}
