// -*- mode: c++ -*-
// Copyright 2016 Keyboardio, inc. <jesse@keyboard.io>
// See "LICENSE" for license details

#ifndef BUILD_INFORMATION
#define BUILD_INFORMATION "locally built"
#endif
/**
These #include directives pull in the Kaleidoscope firmware core,
as well as the Kaleidoscope plugins we use in the Model 01's firmware
*/

// The Kaleidoscope core
#include "Kaleidoscope.h"

// Support for storing the keymap in EEPROM
#include "Kaleidoscope-EEPROM-Settings.h"
#include "Kaleidoscope-EEPROM-Keymap.h"

// Support for communicating with the host via a simple Serial protocol
#include "Kaleidoscope-FocusSerial.h"

// Support for keys that move the mouse
// #include "Kaleidoscope-MouseKeys.h"

// Support for macros
#include "Kaleidoscope-Macros.h"

// Support for controlling the keyboard's LEDs
#include "Kaleidoscope-LEDControl.h"

// Support for "Numpad" mode, which is mostly just the Numpad specific LED mode
#include "Kaleidoscope-NumPad.h"

// Support for the "Boot greeting" effect, which pulses the 'LED' button for 10s
// when the keyboard is connected to a computer (or that computer is powered on)
#include "Kaleidoscope-LEDEffect-BootGreeting.h"

// Support for LED modes that set all LEDs to a single color
// #include "Kaleidoscope-LEDEffect-SolidColor.h"

// Support for an LED mode that makes all the LEDs 'breathe'
#include "Kaleidoscope-LEDEffect-Breathe.h"

// Support for an LED mode that makes a red pixel chase a blue pixel across the keyboard
#include "Kaleidoscope-LEDEffect-Chase.h"

// Support for LED modes that pulse the keyboard's LED in a rainbow pattern
#include "Kaleidoscope-LEDEffect-Rainbow.h"

// Support for an LED mode that lights up the keys as you press them
#include "Kaleidoscope-LED-Stalker.h"

// Support for an LED mode that prints the keys you press in letters 4px high
//#include "Kaleidoscope-LED-AlphaSquare.h"

// Support for shared palettes for other plugins, like Colormap below
#include "Kaleidoscope-LED-Palette-Theme.h"

// Support for an LED mode that lets one configure per-layer color maps
#include "Kaleidoscope-Colormap.h"

// Support for Keyboardio's internal keyboard testing mode
#include "Kaleidoscope-HardwareTestMode.h"

// Support for host power management (suspend & wakeup)
#include "Kaleidoscope-HostPowerManagement.h"

// Support for magic combos (key chrods that trigger an action)
#include "Kaleidoscope-MagicCombo.h"

// Support for USB quirks, like changing the key state report protocol
#include "Kaleidoscope-USB-Quirks.h"

// my plugins imports start here
#include <Kaleidoscope-Qukeys.h>

#include <Kaleidoscope-Heatmap.h>
// #include <Kaleidoscope-LEDEffect-DigitalRain.h>

/** This 'enum' is a list of all the macros used by the Model 01's firmware
The names aren't particularly important. What is important is that each
is unique.

These are the names of your macros. They'll be used in two places.
The first is in your keymap definitions. There, you'll use the syntax
`M(MACRO_NAME)` to mark a specific keymap position as triggering `MACRO_NAME`

The second usage is in the 'switch' statement in the `macroAction` function.
That switch statement actually runs the code associated with a macro when
a macro key is pressed.
*/

enum {
  MACRO_VERSION_INFO,

  E_AIGU,
  E_GRAVE,
  E_CIRCONFLEXE,

  A_GRAVE,
  A_TREMA,
  A_CIRCONFLEXE,

  O_CIRCONFLEXE,
  O_TREMA,

  I_TREMA,

  U_GRAVE,
  U_TREMA,

  C_CEDILLE,

  E_DANS_A,
  E_DANS_O,

  EURO_POUND,

  DEAD_AIGU,
  DEAD_GRAVE,
  DEAD_CIRCONFLEXE,
  DEAD_TREMA,
  DEAD_TILDE,

  M_WIN,
  M_MAC,
  M_LNX
};



/** The Model 01's key layouts are defined as 'keymaps'. By default, there are three
keymaps: The standard QWERTY keymap, the "Function layer" keymap and the "Numpad"
keymap.

Each keymap is defined as a list using the 'KEYMAP_STACKED' macro, built
of first the left hand's layout, followed by the right hand's layout.

Keymaps typically consist mostly of `Key_` definitions. There are many, many keys
defined as part of the USB HID Keyboard specification. You can find the names
(if not yet the explanations) for all the standard `Key_` defintions offered by
Kaleidoscope in these files:
https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keyboard.h
https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_consumerctl.h
https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_sysctl.h
https://github.com/keyboardio/Kaleidoscope/blob/master/src/key_defs_keymaps.h

Additional things that should be documented here include
using ___ to let keypresses fall through to the previously active layer
using XXX to mark a keyswitch as 'blocked' on this layer
using ShiftToLayer() and LockLayer() keys to change the active keymap.
the special nature of the PROG key
keeping NUM and FN consistent and accessible on all layers


The "keymaps" data structure is a list of the keymaps compiled into the firmware.
The order of keymaps in the list is important, as the ShiftToLayer(#) and LockLayer(#)
macros switch to key layers based on this list.



A key defined as 'ShiftToLayer(FUNCTION)' will switch to FUNCTION while held.
Similarly, a key defined as 'LockLayer(NUMPAD)' will switch to NUMPAD when tapped.
*/

/**
Layers are "0-indexed" -- That is the first one is layer 0. The second one is layer 1.
The third one is layer 2.
This 'enum' lets us use names like QWERTY, FUNCTION, and NUMPAD in place of
the numbers 0, 1 and 2.
*/

enum { COLEMAK, FUNCTION }; // layers

/* This comment temporarily turns off astyle's indent enforcement
so we can make the keymaps actually resemble the physical key layout better
*/
// *INDENT-OFF*

KEYMAPS(

  [COLEMAK] = KEYMAP_STACKED
  (Key_Backtick, Key_1, Key_2, Key_3, Key_4, Key_5, Key_Escape,
    Key_Tab, Key_Q, Key_W, Key_F, Key_P, Key_G, Key_Tab,
    Key_LeftGui,   Key_A, Key_R, Key_S, Key_T, Key_D,
    Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, LCTRL(Key_LeftShift),
    Key_LeftAlt, Key_Backspace, Key_Enter, Key_Tab,
    ShiftToLayer(FUNCTION),

    Key_Backspace,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         Key_KeypadNumLock,
    Key_F2,     Key_J, Key_L, Key_U,     Key_Y,         Key_Semicolon, Key_Equals,
    Key_H, Key_N, Key_E,     Key_I,         Key_O,         Key_Quote,
    LCTRL(Key_LeftShift),  Key_K, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
    Key_Tab, Key_Enter, Key_Spacebar, Key_Delete,
    ShiftToLayer(FUNCTION)),

    [FUNCTION] =  KEYMAP_STACKED
    (M(DEAD_TILDE),      Key_F1,  Key_F2,  Key_F3, Key_F4, Key_F5, Key_LEDEffectNext,
    Key_PageUp,  M(A_TREMA), M(A_CIRCONFLEXE), M(DEAD_TILDE), M(DEAD_AIGU), M(EURO_POUND), Key_F12,
    ___, M(A_GRAVE),  M(DEAD_GRAVE), Key_Home, Key_End, M(DEAD_TREMA),
    ___, M(E_DANS_A), M(DEAD_CIRCONFLEXE),  M(C_CEDILLE), M(E_DANS_O), ___,  ___,
    ___, Key_Delete, ___, ___,
    ___,

    Consumer_VolumeIncrement, Key_F6,                 Key_F7,                   Key_F8,                   Key_F9,          Key_F10,          Key_F11,
    Consumer_PlaySlashPause,    Key_LeftCurlyBracket, Key_RightCurlyBracket,     M(U_GRAVE),    M(U_TREMA), M(O_TREMA), Key_Pipe,
    Key_LeftBracket, M(E_GRAVE), M(E_AIGU), M(I_TREMA), M(O_CIRCONFLEXE), M(E_CIRCONFLEXE),
    Consumer_VolumeDecrement,   Key_RightBracket, Key_LeftArrow, Key_UpArrow, Key_DownArrow,  Key_RightArrow,    Key_Backslash,
    LCTRL(Key_LeftArrow), ___, ___, LCTRL(Key_RightArrow),
    ___),


    // [NUMPAD] =  KEYMAP_STACKED
    // (___, M(M_LNX), M(M_WIN), M(M_MAC), ___, ___, ___,
    // ___, ___, ___, ___, ___, ___, ___,
    // ___, ___, ___, ___, ___, ___,
    // ___, ___, ___, ___, ___, ___, ___,
    // ___, ___, ___, ___,
    // ___,

    // M(MACRO_VERSION_INFO),  ___, Key_Keypad7, Key_Keypad8,   Key_Keypad9,        Key_KeypadSubtract, ___,
    // ___,                    ___, Key_Keypad4, Key_Keypad5,   Key_Keypad6,        Key_KeypadAdd,      ___,
    // ___, Key_Keypad1, Key_Keypad2,   Key_Keypad3,        Key_Equals,         Key_Quote,
    // ___,                    ___, Key_Keypad0, Key_KeypadDot, Key_KeypadMultiply, Key_KeypadDivide,   Key_Enter,
    // ___, ___, ___, ___,
    // ___),


    // [QWERTY] = KEYMAP_STACKED
    // (___,          Key_1, Key_2, Key_3, Key_4, Key_5, Key_LEDEffectNext,
    //   Key_Backtick, Key_Q, Key_W, Key_E, Key_R, Key_T, Key_Tab,
    //   Key_PageUp,   Key_A, Key_S, Key_D, Key_F, Key_G,
    //   Key_PageDown, Key_Z, Key_X, Key_C, Key_V, Key_B, Key_Escape,
    //   Key_LeftControl, Key_Backspace, Key_LeftGui, Key_LeftShift,
    //   ShiftToLayer(FUNCTION),

    //   ___,  Key_6, Key_7, Key_8,     Key_9,         Key_0,         Key_KeypadNumLock,
    //   Key_Enter,     Key_Y, Key_U, Key_I,     Key_O,         Key_P,         Key_Equals,
    //   Key_H, Key_J, Key_K,     Key_L,         Key_Semicolon, Key_Quote,
    //   Key_RightAlt,  Key_N, Key_M, Key_Comma, Key_Period,    Key_Slash,     Key_Minus,
    //   Key_RightShift, Key_LeftAlt, Key_Spacebar, Key_RightControl,
    //   ShiftToLayer(FUNCTION))
   ) // KEYMAPS(

    /* Re-enable astyle's indent enforcement */
    // *INDENT-ON*

    /** versionInfoMacro handles the 'firmware version info' macro
    When a key bound to the macro is pressed, this macro
    prints out the firmware build information as virtual keystrokes
    */

    static void versionInfoMacro(uint8_t keyState) {
      if (keyToggledOn(keyState)) {
        Macros.type(PSTR("Keyboardio Model 01 - Kaleidoscope "));
        Macros.type(PSTR(BUILD_INFORMATION));
      }
    }

    /** macroAction dispatches keymap events that are tied to a macro
    to that macro. It takes two uint8_t parameters.

    The first is the macro being called (the entry in the 'enum' earlier in this file).
    The second is the state of the keyswitch. You can use the keyswitch state to figure out
    if the key has just been toggled on, is currently pressed or if it's just been released.

    The 'switch' statement should have a 'case' for each entry of the macro enum.
    Each 'case' statement should call out to a function to handle the macro in question.

    */
    const macro_t *macroAction(uint8_t macroIndex, uint8_t keyState) {
      switch (macroIndex) {
        case MACRO_VERSION_INFO:
        versionInfoMacro(keyState);
        break;
        case E_AIGU:
        return MACRODOWN(I(25), D(RightAlt),  T(E), U(RightAlt));
        break;
        case E_GRAVE:
        return MACRODOWN(I(25), D(RightAlt),  T(N), U(RightAlt));
        break;
        case E_CIRCONFLEXE:
        return MACRODOWN(I(25), D(RightAlt),  T(Quote), U(RightAlt));
        break;
        case A_GRAVE:
        return MACRODOWN(I(25), D(RightAlt),  T(A), U(RightAlt));
        break;
        case A_TREMA:
        return MACRODOWN(I(25), D(RightAlt),  T(Q), U(RightAlt));
        break;
        case A_CIRCONFLEXE:
        return MACRODOWN(I(25), D(RightAlt),  T(W), U(RightAlt));
        break;
        case O_CIRCONFLEXE:
        return MACRODOWN(I(25), D(RightAlt),  T(O), U(RightAlt));
        break;
        case O_TREMA:
        return MACRODOWN(I(25), D(RightAlt),  T(Semicolon), U(RightAlt));
        break;
        case I_TREMA:
        return MACRODOWN(I(25), D(RightAlt),  T(I), U(RightAlt));
        break;
        case U_GRAVE:
        return MACRODOWN(I(25), D(RightAlt),  T(U), U(RightAlt));
        break;
        case U_TREMA:
        return MACRODOWN(I(25), D(RightAlt),  T(Y), U(RightAlt));
        break;
        case C_CEDILLE:
        return MACRODOWN(I(25), D(RightAlt),  T(C), U(RightAlt));
        break;
        case E_DANS_A:
        return MACRODOWN(I(25), D(RightAlt),  T(Z), U(RightAlt));
        break;
        case E_DANS_O:
        return MACRODOWN(I(25), D(RightAlt),  T(V), U(RightAlt));
        break;
        case EURO_POUND:
        return MACRODOWN(I(25), D(RightAlt),  T(G), U(RightAlt));
        break;
        case DEAD_AIGU:
        return MACRODOWN(I(25), D(RightAlt),  T(P), U(RightAlt));
        break;
        case DEAD_GRAVE:
        return MACRODOWN(I(25), D(RightAlt),  T(R), U(RightAlt));
        break;
        case DEAD_CIRCONFLEXE:
        return MACRODOWN(I(25), D(RightAlt),  T(X), U(RightAlt));
        break;
        case DEAD_TREMA:
        return MACRODOWN(I(25), D(RightAlt),  T(D), U(RightAlt));
        break;
        case DEAD_TILDE:
        return MACRODOWN(I(25), D(RightAlt),  T(F), U(RightAlt));
        break;
        case M_LNX:
        //HostOS.os(kaleidoscope::hostos::LINUX);
        break;
        case M_MAC:
        //HostOS.os(kaleidoscope::hostos::OSX);
        break;
        case M_WIN:
        //HostOS.os(kaleidoscope::hostos::WINDOWS);
        break;
      }
      return MACRO_NONE;
    }

    // These 'solid' color effect definitions define a rainbow of
    // LED color modes calibrated to draw 500mA or less on the
    // Keyboardio Model 01.


    //static kaleidoscope::LEDSolidColor solidRed(160, 0, 0);
    //static kaleidoscope::LEDSolidColor solidOrange(140, 70, 0);
    //static kaleidoscope::LEDSolidColor solidYellow(130, 100, 0);
    //static kaleidoscope::LEDSolidColor solidGreen(0, 160, 0);
    //static kaleidoscope::LEDSolidColor solidBlue(0, 70, 130);
    //static kaleidoscope::LEDSolidColor solidIndigo(0, 0, 170);
    //static kaleidoscope::LEDSolidColor solidViolet(130, 0, 120);

    /** toggleLedsOnSuspendResume toggles the LEDs off when the host goes to sleep,
    * and turns them back on when it wakes up.
    */
    void toggleLedsOnSuspendResume(kaleidoscope::plugin::HostPowerManagement::Event event) {
      switch (event) {
      case kaleidoscope::plugin::HostPowerManagement::Suspend:
        LEDControl.disable();
        break;
      case kaleidoscope::plugin::HostPowerManagement::Resume:
        LEDControl.enable();
        break;
      case kaleidoscope::plugin::HostPowerManagement::Sleep:
        break;
      }
    }


    /** hostPowerManagementEventHandler dispatches power management events (suspend,
    * resume, and sleep) to other functions that perform action based on these
    * events.
    */
    void hostPowerManagementEventHandler(kaleidoscope::HostPowerManagement::Event event) {
      toggleLedsOnSuspendResume(event);
    }

    /** This 'enum' is a list of all the magic combos used by the Model 01's
    * firmware The names aren't particularly important. What is important is that
    * each is unique.
    *
    * These are the names of your magic combos. They will be used by the
    * `USE_MAGIC_COMBOS` call below.
    */
    enum {
      // Toggle between Boot (6-key rollover; for BIOSes and early boot) and NKRO
      // mode.
      COMBO_TOGGLE_NKRO_MODE
    };

    /** A tiny wrapper, to be used by MagicCombo.
    * This simply toggles the keyboard protocol via USBQuirks, and wraps it within
    * a function with an unused argument, to match what MagicCombo expects.
    */
    static void toggleKeyboardProtocol(uint8_t combo_index) {
      USBQuirks.toggleKeyboardProtocol();
    }

    /** Magic combo list, a list of key combo and action pairs the firmware should
    * recognise.
    */
    USE_MAGIC_COMBOS({.action = toggleKeyboardProtocol,
      // Left Fn + Esc + Shift
      .keys = { R3C6, R2C6, R3C7 }
    });



    // First, tell Kaleidoscope which plugins you want to use.
    // The order can be important. For example, LED effects are
    // added in the order they're listed here.
    KALEIDOSCOPE_INIT_PLUGINS(

      Qukeys,

      // The EEPROMSettings & EEPROMKeymap plugins make it possible to have an
      // editable keymap in EEPROM.
      EEPROMSettings,
      EEPROMKeymap,

      // Focus allows bi-directional communication with the host, and is the
      // interface through which the keymap in EEPROM can be edited.
      Focus,

      // FocusSettingsCommand adds a few Focus commands, intended to aid in
      // changing some settings of the keyboard, such as the default layer (via the
      // `settings.defaultLayer` command)
      FocusSettingsCommand,

      // FocusEEPROMCommand adds a set of Focus commands, which are very helpful in
      // both debugging, and in backing up one's EEPROM contents.
      FocusEEPROMCommand,

      // The boot greeting effect pulses the LED button for 10 seconds after the keyboard is first connected
      BootGreetingEffect,

      // The hardware test mode, which can be invoked by tapping Prog, LED and the
      // left Fn button at the same time.
      // HardwareTestMode,

      // LEDControl provides support for other LED modes
      LEDControl,

      // We start with the LED effect that turns off all the LEDs.
      LEDOff,

      // LEDDigitalRainEffect,
      HeatmapEffect,

      // The rainbow effect changes the color of all of the keyboard's keys at the same time
      // running through all the colors of the rainbow.
      LEDRainbowEffect,

      // The rainbow wave effect lights up your keyboard with all the colors of a rainbow
      // and slowly moves the rainbow across your keyboard
      LEDRainbowWaveEffect,

      // The chase effect follows the adventure of a blue pixel which chases a red pixel across
      // your keyboard. Spoiler: the blue pixel never catches the red pixel
      LEDChaseEffect,

      // These static effects turn your keyboard's LEDs a variety of colors
      // solidRed, solidOrange, solidYellow, solidGreen, solidBlue, solidIndigo, solidViolet,

      // The breathe effect slowly pulses all of the LEDs on your keyboard
      LEDBreatheEffect,

      // The AlphaSquare effect prints each character you type, using your
      // keyboard's LEDs as a display
      // AlphaSquareEffect,

      // The stalker effect lights up the keys you've pressed recently
      StalkerEffect,

      // The LED Palette Theme plugin provides a shared palette for other plugins,
      // like Colormap below
      LEDPaletteTheme,

      // The Colormap effect makes it possible to set up per-layer colormaps
      ColormapEffect,

      // We end with the LED effect that turns off all the LEDs.
      LEDOff,

      // The numpad plugin is responsible for lighting up the 'numpad' mode
      // with a custom LED effect
      NumPad,

      // The macros plugin adds support for macros
      Macros,

      // The MouseKeys plugin lets you add keys to your keymap which move the mouse.
      // MouseKeys,

      // The HostPowerManagement plugin allows us to turn LEDs off when then host
      // goes to sleep, and resume them when it wakes up.
      HostPowerManagement,

      // The MagicCombo plugin lets you use key combinations to trigger custom
      // actions - a bit like Macros, but triggered by pressing multiple keys at the
      // same time.
      MagicCombo,

      // The USBQuirks plugin lets you do some things with USB that we aren't
      // comfortable - or able - to do automatically, but can be useful
      // nevertheless. Such as toggling the key report protocol between Boot (used
      // by BIOSes) and Report (NKRO).
      USBQuirks
    );

    /** The 'setup' function is one of the two standard Arduino sketch functions.
    It's called when your keyboard first powers up. This is where you set up
    Kaleidoscope and any plugins.
    */

    void setup() {
      // First, call Kaleidoscope's internal setup function
      Kaleidoscope.setup();

      QUKEYS(
        kaleidoscope::plugin::Qukey(0, KeyAddr(3, 0), Key_LeftShift),    // PgDown/shift
        kaleidoscope::plugin::Qukey(0, KeyAddr(2, 7), Key_LeftShift),    // Enter/shift (Left hand)
        kaleidoscope::plugin::Qukey(0, KeyAddr(3, 7), Key_LeftControl),  // Tab/ctrl (Left hand)
        kaleidoscope::plugin::Qukey(0, KeyAddr(3, 8), Key_LeftControl),  // Tab/ctrl (Right hand)
        kaleidoscope::plugin::Qukey(0, KeyAddr(2, 8), Key_LeftShift),    // Enter/shift (Right hand)

        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 1), Key_LeftGui),      // A
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 2), Key_LeftAlt),      // R
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 3), Key_LeftShift),    // S
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 4), Key_LeftControl),  // T

        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 11), Key_LeftControl), // N
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 12), Key_LeftShift),   // E
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 13), Key_LeftAlt),     // I
        // kaleidoscope::plugin::Qukey(0, KeyAddr(2, 14), Key_LeftGui),     // O

      )

      Qukeys.setHoldTimeout(200);
      // Qukeys.setOverlapThreshold(30);

      // LEDDigitalRainEffect.DROP_TICKS = 35; // Make the rain fall slower/faster
      // LEDDigitalRainEffect.ENABLE_CHRISTMAS_LIGHTS = true;

      // While we hope to improve this in the future, the NumPad plugin
      // needs to be explicitly told which keymap layer is your numpad layer
      // NumPad.numPadLayer = NUMPAD;

      // We configure the AlphaSquare effect to use RED letters
      // AlphaSquare.color = CRGB(255, 0, 0);

      // We set the brightness of the rainbow effects to 150 (on a scale of 0-255)
      // This draws more than 500mA, but looks much nicer than a dimmer effect
      LEDRainbowEffect.brightness(150);
      LEDRainbowWaveEffect.brightness(150);

      // The LED Stalker mode has a few effects. The one we like is
      // called 'BlazingTrail'. For details on other options,
      // see https://github.com/keyboardio/Kaleidoscope-LED-Stalker
      //StalkerEffect.variant = STALKER(BlazingTrail);
      StalkerEffect.variant = STALKER(Haunt, (CRGB(0, 128, 0)));

      // We want to make sure that the firmware starts with LED effects off
      // This avoids over-taxing devices that don't have a lot of power to share
      // with USB devices
       LEDOff.activate();

      // To make the keymap editable without flashing new firmware, we store
      // additional layers in EEPROM. For now, we reserve space for five layers. If
      // one wants to use these layers, just set the default layer to one in EEPROM,
      // by using the `settings.defaultLayer` Focus command, or by using the
      // `keymap.onlyCustom` command to use EEPROM layers only.
      EEPROMKeymap.setup(5);

      // We need to tell the Colormap plugin how many layers we want to have custom
      // maps for. To make things simple, we set it to five layers, which is how
      // many editable layers we have (see above).
      ColormapEffect.max_layers(5);
    }

    /** loop is the second of the standard Arduino sketch functions.
    As you might expect, it runs in a loop, never exiting.

    For Kaleidoscope-based keyboard firmware, you usually just want to
    call Kaleidoscope.loop(); and not do anything custom here.
    */

    void loop() {
      Kaleidoscope.loop();
    }
