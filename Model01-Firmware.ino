// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif

/**
 * These #include directives pull in the Kaleidoscope firmware core,
 * as well as the Kaleidoscope plugins we use in the Model 01's firmware
 */

#define KALEIDOSCOPE_HOSTOS_GUESSER 1

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for keys that move the mouse
#include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include <Kaleidoscope-Macros.h>

// Support for controlling the keyboard's LEDs
//#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
//#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-Model01-TestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

#include <Kaleidoscope-HostOS.h>
#include <Kaleidoscope-Unicode.h>
#include <Kaleidoscope-OneShot.h>
#include <kaleidoscope/hid.h>
//#include <Kaleidoscope-LED-ActiveModColor.h>
//#include <Kaleidoscope-LEDEffect-FunctionalColor.h>

//kaleidoscope::LEDFunctionalColor::FCPlugin FunColor;

/** This 'enum' is a list of all the macros used by the Model 01's firmware
  * The names aren't particularly important. What is important is that each
  * is unique.
  *
  * These are the names of your macros. They'll be used in two places.
  * The first is in your keymap definitions. There, you'll use the syntax
  * `M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`
  *
  * The second usage is in the 'switch' statement in the `macroAction` function.
  * That switch statement actually runs the code associated with a macro when
  * a macro key is pressed.
  */

enum { MACRO_VERSION_INFO,
       MACRO_POUND,
       MACRO_LAMBDA,
       MACRO_ANY,
     };



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
  * keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
  * keymap.
  *
  * Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
  * of first the left hand's layout, followed by the right hand's layout.
  *
  * Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
  * defined as part of the USB HID Keyboard specification. You can find the names
  * (if not yet the explanations) for all the standard `Key_` defintions offered by
  * Kaleidoscope in these files:
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
  *    https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h
  *
  * Additional things that should be documented here include
  *   using ___ to let keypresses fall through to the previously active layer
  *   using XXX to mark a keyswitch as 'blocked' on this layer
  *   using ShiftToLayer() and LockLayer() keys to change the active keymap.
  *   the special nature of the PROG key
  *   keeping NUM and FN consistent and accessible on all layers
  *
  *
  * The "keymaps" data structure is a list of the keymaps compiled into the firmware.
  * The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
  * macros switch to key layers based on this list.
  *
  *

  * A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
  * Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
  */

/**
  * Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
  * The third one is layer 2.
  * This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
  * the numbers 0, 1 and 2.
  *
  */

enum { WORKMAN, NUMPAD, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
 *   so we can make the keymaps actually resemble the physical key layout better
 */
// *INDENT-OFF*

const Key keymaps[][ROWS][COLS] PROGMEM = {

  [WORKMAN] = KEYMAP_STACKED
  (___,          LSHIFT(Key_1),         LSHIFT(Key_2),     M(MACRO_POUND),      LSHIFT(Key_4), LSHIFT(Key_5), Key_LEDEffectNext,
   Key_Backtick, Key_Q, Key_D, Key_R, Key_W, Key_B, Key_Tab,
   Key_PageUp,   Key_A, Key_S, Key_H, Key_T, Key_G,
   Key_PageDown, Key_Z, Key_X, Key_M, Key_C, Key_V, Key_Escape,
   Key_LeftControl, Key_Backspace, ShiftToLayer(NUMPAD), Key_LeftShift,
   ShiftToLayer(FUNCTION),

   M(MACRO_ANY),  LSHIFT(Key_6), LSHIFT(Key_7), LSHIFT(Key_8), LSHIFT(Key_3), M(MACRO_LAMBDA), LockLayer(NUMPAD),
   Key_Enter,     Key_J, Key_F, Key_U,     Key_P,         Key_Semicolon, LSHIFT(Key_5),
                  Key_Y, Key_N, Key_E,     Key_O,         Key_I,         Key_Quote,
   Key_RightAlt,  Key_K, Key_L, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
   ShiftToLayer(FUNCTION)),


  [NUMPAD] =  KEYMAP_STACKED
  (___, ___, ___, ___, ___, ___, Key_Enter,
   ___, ___, LSHIFT(Key_LeftBracket), LSHIFT(Key_RightBracket), Key_Equals, ___, Key_Spacebar,
   ___, ___, LSHIFT(Key_9), LSHIFT(Key_0), Key_Semicolon, ___,
   ___, ___, Key_LeftBracket, Key_RightBracket, ___, ___, ___,
   ___, ___, ___, ___,
   ___,

   M(MACRO_VERSION_INFO),  ___, Key_7, Key_8,   Key_9,        Key_KeypadSubtract, ___,
   ___,                    ___, Key_4, Key_5,   Key_6,        Key_KeypadAdd,      ___,
                           ___, Key_1, Key_2,   Key_3,        Key_Equals,         Key_Quote,
   ___,                    ___, Key_0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
   ___, ___, ___, ___,
   ___),

  [FUNCTION] =  KEYMAP_STACKED
  (___,      Key_F1,           Key_F2,      Key_F3,     Key_F4,        Key_F5,           XXX,
   Key_Tab,  ___,              Key_mouseUp, Key_mouseScrollUp,        Key_mouseBtnR, Key_mouseWarpEnd, Key_mouseWarpNE,
   Key_Home, Key_mouseL,       Key_mouseDn, Key_mouseR, Key_mouseBtnL, Key_mouseWarpNW,
   Key_End,  Key_PrintScreen,  Key_Insert,  Key_mouseScrollDn,        Key_mouseBtnM, Key_mouseWarpSW,  Key_mouseWarpSE,
   ___, Key_Delete, OSM(LeftGui), ___,
   ___,

   Consumer_ScanPreviousTrack, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
   Consumer_PlaySlashPause,    Consumer_ScanNextTrack, Key_LeftCurlyBracket,     Key_RightCurlyBracket,    Key_LeftBracket, Key_RightBracket, Key_F12,
                               Key_LeftArrow,          Key_DownArrow,            Key_UpArrow,              Key_RightArrow,  ___,              ___,
   Key_PcApplication,          Consumer_Mute,          Consumer_VolumeDecrement, Consumer_VolumeIncrement, ___,             Key_Backslash,    Key_Pipe,
   ___, ___, Key_Enter, ___,
   ___)

};

/* Re-enable astyle's indent enforcement */
// *INDENT-ON*

/** versionInfoMacro handles the 'firmware version info' macro
 *  When a key bound to the macro is pressed, this macro
 *  prints out the firmware build information as virtual keystrokes
 */

static void versionInfoMacro(uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
    Macros.type(PSTR(BUILD_INFORMATION));
  }
}

/** anyKeyMacro is used to provide the functionality of the 'Any' key.
 *
 * When the 'any key' macro is toggled on, a random alphanumeric key is
 * selected. While the key is held, the function generates a synthetic
 * keypress event repeating that randomly selected key.
 *
 */

static void anyKeyMacro(uint8_t keyState) {
  static Key lastKey;
  if (keyToggledOn(keyState))
    lastKey.keyCode = Key_A.keyCode + (uint8_t)(millis() % 36);

  if (keyIsPressed(keyState))
    kaleidoscope::hid::pressKey(lastKey);
}


/** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

 */

static void unicode(uint32_t character, uint8_t keyState) {
  if (keyToggledOn(keyState)) {
    Unicode.type(character);
  }
}

const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
  switch (macroIndex) {

  case MACRO_VERSION_INFO:
    versionInfoMacro(keyState);
    break;
    
  case MACRO_ANY:
    anyKeyMacro(keyState);
    break;

  case MACRO_POUND:
    unicode(0x00A3, keyState);
    break;

  case MACRO_LAMBDA:
    unicode(0x03BB, keyState);
    break;
  }
  return MACRO_NONE;
}

/** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
 * and turns them back on when it wakes up.
 */
//void toggleLedsOnSuspendResume(kaleidoscope::HostPowerManagement::Event event) {
//  switch (event) {
//  case kaleidoscope::HostPowerManagement::Suspend:
//    LEDControl.paused = true;
//    LEDControl.set_all_leds_to({0, 0, 0});
//    LEDControl.syncLeds();
//    break;
//  case kaleidoscope::HostPowerManagement::Resume:
//    LEDControl.paused = false;
//    LEDControl.refreshAll();
//    break;
//  case kaleidoscope::HostPowerManagement::Sleep:
//    break;
//  }
//}

/** hostPowerManagementEventHandler dispatches power management events (suspend,
 * resume, and sleep) to other functions that perform action based on these
 * events.
 */
//void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
//  toggleLedsOnSuspendResume(event);
//}



// Next, tell Kaleidoscope which plugins you want to use.
// The order can be important. For example, LED effects are
// added in the order they're listed here.
KALEIDOSCOPE_INIT_PLUGINS(
  // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
  //BootGreetingEffect,

  // LEDControl provides support for other LED modes
  //LEDControl,

  // The macros plugin adds support for macros
  Macros,

  // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
  MouseKeys,

  // The HostPowerManagement plugin enables waking up the host from suspend,
  // and allows us to turn LEDs off when it goes to sleep.
  HostPowerManagement,

  Unicode,
  //FunColor,
  HostOS,
  OneShot
  //ActiveModColorEffect
);

/** The 'setup' function is one of the two standard Arduino sketch functions.
  * It's called when your keyboard first powers up. This is where you set up
  * Kaleidoscope and any plugins.
  */

void setup() {
  // First, call Kaleidoscope's internal setup function
  Kaleidoscope.setup();
  
//  MouseKeys.speed = 2;
//  MouseKeys.speedDelay = 5;
//  MouseKeys.accelDelay = 100;

  // We want the keyboard to be able to wake the host up from suspend.
  HostPowerManagement.enableWakeup();

  HostOS.os(kaleidoscope::hostos::WINDOWS);

//  cRGB antiquewhite = CRGB(250, 235, 215);
//  cRGB blue = CRGB(0, 0, 255);
//  cRGB cyan = CRGB(0, 255, 255);
//  cRGB green = CRGB(0, 128, 0);
//  cRGB lightskyblue = CRGB(135, 206, 250);
//  cRGB lime = CRGB(0, 255, 0);
//  cRGB mintcream = CRGB(245, 255, 250);
//  cRGB orange = CRGB(255, 165, 0);
//  cRGB orangered = CRGB(255, 100, 0);
//  cRGB palegreen = CRGB(152, 251, 152);
//  cRGB pink = CRGB(255, 192, 203);
//  cRGB red = CRGB(255, 0, 0);
//  cRGB skyblue = CRGB(135, 206, 235);
//  cRGB slateblue = CRGB(106, 90, 205);
//  cRGB violet = CRGB(238, 130, 238);
//  cRGB white = CRGB(255, 255, 255);
//  cRGB yellow = CRGB(255, 255, 0);
//  cRGB yellowgreen = CRGB(154, 205, 50);
//
//  FunColor.all(CRGB(0, 0, 0));
//  FunColor.allModifiers(yellow, 100);
//  FunColor.allMouse(CRGB(0, 200, 200));
//  FunColor.escape(red, 170);
//  FunColor.numbers(yellowgreen, 160);
//  FunColor.symbols(blue, 160);
//  FunColor.letters(antiquewhite, 100);
//  FunColor.punctuation(blue, 170);
//  FunColor.brackets(blue, 200);
//  FunColor.backslash(blue, 170);
//  FunColor.pipe(blue, 170);
//  FunColor.tab(white, 170);
//  FunColor.backspace(red, 170);
//  FunColor.del(red, 255);
//  FunColor.enter(green, 255);
//  FunColor.space(slateblue, 200);
//  FunColor.arrows(orange, 170);
//  FunColor.nav(yellow, 170);
//  FunColor.insert(yellow, 170);
//  FunColor.cmd(lime, 180);
//  FunColor.app(lime, 180);
//  FunColor.printscreen(lime, 255);
//  FunColor.pause(lime, 180);
//  FunColor.scrolllock(red, 255);
//  FunColor.capslock(red, 255);
//  FunColor.fkeys(red, 170);
//  FunColor.media(lime, 180);
//  FunColor.led(blue, 190);
//  FunColor.mousemove(cyan, 170);
//  FunColor.mousebuttons(lightskyblue, 170);
//  FunColor.mousewarp(cyan, 100);
//  FunColor.mousescroll(lightskyblue, 100);
//  FunColor.macros(violet, 255);
//  FunColor.layer(lime, 100);
//  FunColor.oneshot(skyblue, 150);
}

/** loop is the second of the standard Arduino sketch functions.
  * As you might expect, it runs in a loop, never exiting.
  *
  * For Kaleidoscope-based keyboard firmware, you usually just want to
  * call Kaleidoscope.loop(); and not do anything custom here.
  */

void loop() {
  Kaleidoscope.loop();
}
