// Copyright (c) Martin Schweiger
// Licensed under the MIT License

#include "Keymap.h"
#include "Config.h"
#include <fstream>

#define NKEY 95

using namespace std;

struct {
	BYTE id;
	const char *name;
} keyname[NKEY] = {
	{OAPI_KEY_ESCAPE,     "ESC"},         // 0x01: Escape
	{OAPI_KEY_1,          "1"},           // 0x02: 1
	{OAPI_KEY_2,          "2"},           // 0x03: 2
	{OAPI_KEY_3,          "3"},           // 0x04:
	{OAPI_KEY_4,          "4"},           // 0x05
	{OAPI_KEY_5,          "5"},           // 0x06
	{OAPI_KEY_6,          "6"},           // 0x07
	{OAPI_KEY_7,          "7"},           // 0x08
	{OAPI_KEY_8,          "8"},           // 0x09
	{OAPI_KEY_9,          "9"},           // 0x0A
	{OAPI_KEY_0,          "0"},           // 0x0B
	{OAPI_KEY_MINUS,      "MINUS"},       // 0x0C
	{OAPI_KEY_EQUALS,     "EQUALS"},      // 0x0D
	{OAPI_KEY_BACK,       "BACK"},        // 0x0E
	{OAPI_KEY_TAB,        "TAB"},         // 0x0F
	{OAPI_KEY_Q,          "Q"},           // 0x10
	{OAPI_KEY_W,          "W"},           // 0x11
	{OAPI_KEY_E,          "E"},           // 0x12
	{OAPI_KEY_R,          "R"},           // 0x13
	{OAPI_KEY_T,          "T"},           // 0x14
	{OAPI_KEY_Y,          "Y"},           // 0x15
	{OAPI_KEY_U,          "U"},           // 0x16
	{OAPI_KEY_I,          "I"},           // 0x17
	{OAPI_KEY_O,          "O"},           // 0x18
	{OAPI_KEY_P,          "P"},           // 0x19
	{OAPI_KEY_LBRACKET,   "LBRACKET"},    // 0x1A
	{OAPI_KEY_RBRACKET,   "RBRACKET"},    // 0x1B
	{OAPI_KEY_RETURN,     "RETURN"},      // 0x1C
	{OAPI_KEY_A,          "A"},           // 0x1E
	{OAPI_KEY_S,          "S"},           // 0x1F
	{OAPI_KEY_D,          "D"},           // 0x20
	{OAPI_KEY_F,          "F"},           // 0x21
	{OAPI_KEY_G,          "G"},           // 0x22
	{OAPI_KEY_H,          "H"},           // 0x23
	{OAPI_KEY_J,          "J"},           // 0x24
	{OAPI_KEY_K,          "K"},           // 0x25
	{OAPI_KEY_L,          "L"},           // 0x26
	{OAPI_KEY_SEMICOLON,  "SEMICOLON"},   // 0x27
	{OAPI_KEY_APOSTROPHE, "APOSTROPHE"},  // 0x28
	{OAPI_KEY_GRAVE,      "GRAVE"},       // 0x29
	{OAPI_KEY_BACKSLASH,  "BACKSLASH"},   // 0x2B
	{OAPI_KEY_Z,          "Z"},           // 0x2C
	{OAPI_KEY_X,          "X"},           // 0x2D
	{OAPI_KEY_C,          "C"},           // 0x2E
	{OAPI_KEY_V,          "V"},           // 0x2F
	{OAPI_KEY_B,          "B"},           // 0x30
	{OAPI_KEY_N,          "N"},           // 0x31
	{OAPI_KEY_M,          "M"},           // 0x32
	{OAPI_KEY_COMMA,      "COMMA"},       // 0x33
	{OAPI_KEY_PERIOD,     "PERIOD"},      // 0x34
	{OAPI_KEY_SLASH,      "SLASH"},       // 0x35
	{OAPI_KEY_MULTIPLY,   "MULTIPLY"},    // 0x37
	{OAPI_KEY_SPACE,      "SPACE"},       // 0x39
	{OAPI_KEY_CAPITAL,    "CAPITAL"},     // 0x3A
	{OAPI_KEY_F1,         "F1"},          // 0x3B
	{OAPI_KEY_F2,         "F2"},          // 0x3C
	{OAPI_KEY_F3,         "F3"},          // 0x3D
	{OAPI_KEY_F4,         "F4"},          // 0x3E
	{OAPI_KEY_F5,         "F5"},          // 0x3F
	{OAPI_KEY_F6,         "F6"},          // 0x40
	{OAPI_KEY_F7,         "F7"},          // 0x41
	{OAPI_KEY_F8,         "F8"},          // 0x42
	{OAPI_KEY_F9,         "F9"},          // 0x43
	{OAPI_KEY_F10,        "F10"},         // 0x44
	{OAPI_KEY_NUMLOCK,    "NUMLOCK"},     // 0x45
	{OAPI_KEY_SCROLL,     "SCROLL"},      // 0x46
	{OAPI_KEY_NUMPAD7,    "NUMPAD7"},     // 0x47
	{OAPI_KEY_NUMPAD8,    "NUMPAD8"},     // 0x48
	{OAPI_KEY_NUMPAD9,    "NUMPAD9"},     // 0x49
	{OAPI_KEY_SUBTRACT,   "SUBTRACT"},    // 0x4A
	{OAPI_KEY_NUMPAD4,    "NUMPAD4"},     // 0x4B
	{OAPI_KEY_NUMPAD5,    "NUMPAD5"},     // 0x4C
	{OAPI_KEY_NUMPAD6,    "NUMPAD6"},     // 0x4D
	{OAPI_KEY_ADD,        "ADD"},         // 0x4E
	{OAPI_KEY_NUMPAD1,    "NUMPAD1"},     // 0x4F
	{OAPI_KEY_NUMPAD2,    "NUMPAD2"},     // 0x50
	{OAPI_KEY_NUMPAD3,    "NUMPAD3"},     // 0x51
	{OAPI_KEY_NUMPAD0,    "NUMPAD0"},     // 0x52
	{OAPI_KEY_DECIMAL,    "DECIMAL"},     // 0x53
	{OAPI_KEY_OEM_102,    "OEM_102"},     // 0x56
	{OAPI_KEY_F11,        "F11"},         // 0x57
	{OAPI_KEY_F12,        "F12"},         // 0x58
	{OAPI_KEY_NUMPADENTER,"NUMPADENTER"}, // 0x9C
	{OAPI_KEY_DIVIDE,     "DIVIDE"},      // 0xB5
	{OAPI_KEY_SYSRQ,      "SYSRQ"},       // 0xB7
	{OAPI_KEY_HOME,       "HOME"},        // 0xC7
	{OAPI_KEY_UP,         "UP"},          // 0xC8
	{OAPI_KEY_PRIOR,      "PGUP"},        // 0xC9
	{OAPI_KEY_LEFT,       "LEFT"},        // 0xCB
	{OAPI_KEY_RIGHT,      "RIGHT"},       // 0xCD
	{OAPI_KEY_END,        "END"},         // 0xCF
	{OAPI_KEY_DOWN,       "DOWN"},        // 0xD0
	{OAPI_KEY_NEXT,       "PGDOWN"},      // 0xD1
	{OAPI_KEY_INSERT,     "INSERT"},      // 0xD2
	{OAPI_KEY_DELETE,     "DELETE"}       // 0xD3
};

struct {
	WORD defkey;
	const char *itemstr;
	const char *label;
} lkeyspec[LKEY_COUNT] = {
	{OAPI_KEY_LEFT     | KMOD_ALT,                 "CockpitCamRotateLeft", "Look left"},
	{OAPI_KEY_RIGHT    | KMOD_ALT,                 "CockpitCamRotateRight", "Look right"},
	{OAPI_KEY_UP       | KMOD_ALT,                 "CockpitCamRotateUp", "Look up"},
	{OAPI_KEY_DOWN     | KMOD_ALT,                 "CockpitCamRotateDown", "Look down"},
	{OAPI_KEY_DOWN     | KMOD_CTRL | KMOD_ALT,     "CockpitCamDontLean", "Lean back to centre"},
	{OAPI_KEY_UP       | KMOD_CTRL | KMOD_ALT,     "CockpitCamLeanForward", "Lean forward"},
	{OAPI_KEY_LEFT     | KMOD_CTRL | KMOD_ALT,     "CockpitCamLeanLeft", "Lean left"},
	{OAPI_KEY_RIGHT    | KMOD_CTRL | KMOD_ALT,     "CockpitCamLeanRight", "Lean right"},
	{OAPI_KEY_HOME,                                "CockpitResetCam", "Reset cockpit view"},
	{OAPI_KEY_LEFT,                                "PanelShiftLeft", "Scroll panel left"},
	{OAPI_KEY_RIGHT,                               "PanelShiftRight", "Scroll panel right"},
	{OAPI_KEY_UP,                                  "PanelShiftUp", "Scroll panel up"},
	{OAPI_KEY_DOWN,                                "PanelShiftDown", "Scroll panel down"},
	{OAPI_KEY_LEFT     | KMOD_CTRL,                "PanelSwitchLeft", "Switch to left panel"},
	{OAPI_KEY_RIGHT    | KMOD_CTRL,                "PanelSwitchRight", "Switch to right panel"},
	{OAPI_KEY_UP       | KMOD_CTRL,                "PanelSwitchUp", "Switch to upper panel"},
	{OAPI_KEY_DOWN     | KMOD_CTRL,                "PanelSwitchDown", "Switch to lower panel"},
	{OAPI_KEY_LEFT     | KMOD_CTRL,                "TrackCamRotateLeft", "Orbit camera left"},
	{OAPI_KEY_RIGHT    | KMOD_CTRL,                "TrackCamRotateRight", "Orbit camera right"},
	{OAPI_KEY_UP       | KMOD_CTRL,                "TrackCamRotateUp", "Orbit camera up"},
	{OAPI_KEY_DOWN     | KMOD_CTRL,                "TrackCamRotateDown", "Orbit camera down"},
	{OAPI_KEY_NEXT,                                "TrackCamAdvance", "Move camera closer"},
	{OAPI_KEY_PRIOR,                               "TrackCamRetreat", "Move camera away"},
	{OAPI_KEY_LEFT,                                "GroundCamTiltLeft", "Ground camera tilt left"},
	{OAPI_KEY_RIGHT,                               "GroundCamTiltRight", "Ground camera tilt right"},
	{OAPI_KEY_UP,                                  "GroundCamTiltUp", "Ground camera tilt up"},
	{OAPI_KEY_DOWN,                                "GroundCamTiltDown", "Ground camera tilt down"},
	{OAPI_KEY_ADD      | KMOD_CTRL,                "IncMainThrust", "Throttle up"},
	{OAPI_KEY_SUBTRACT | KMOD_CTRL,                "DecMainThrust", "Throttle down"},
	{OAPI_KEY_MULTIPLY,                            "KillMainRetroThrust", "Cut throttle"},
	{OAPI_KEY_ADD,                                 "OverrideFullMainThrust", "Full throttle (hold)"},
	{OAPI_KEY_SUBTRACT,                            "OverrideFullRetroThrust", "Full retro (hold)"},
	{OAPI_KEY_NUMPAD0,                             "IncHoverThrust", "Hover up"},
	{OAPI_KEY_DECIMAL,                             "DecHoverThrust", "Hover down"},
	{OAPI_KEY_DIVIDE   | KMOD_CTRL,                "RCSEnable", "Toggle RCS"},
	{OAPI_KEY_DIVIDE,                              "RCSMode", "Switch RCS rotation/translation"},
	{OAPI_KEY_NUMPAD2,                             "RCSPitchUp", "Pitch up"},
	{OAPI_KEY_NUMPAD8,                             "RCSPitchDown", "Pitch down"},
	{OAPI_KEY_NUMPAD1,                             "RCSYawLeft", "Yaw left"},
	{OAPI_KEY_NUMPAD3,                             "RCSYawRight", "Yaw right"},
	{OAPI_KEY_NUMPAD4,                             "RCSBankLeft", "Roll left"},
	{OAPI_KEY_NUMPAD6,                             "RCSBankRight", "Roll right"},
	{OAPI_KEY_NUMPAD2,                             "RCSUp", "Translate up"},
	{OAPI_KEY_NUMPAD8,                             "RCSDown", "Translate down"},
	{OAPI_KEY_NUMPAD1,                             "RCSLeft", "Translate left"},
	{OAPI_KEY_NUMPAD3,                             "RCSRight", "Translate right"},
	{OAPI_KEY_NUMPAD6,                             "RCSForward", "Translate forward"},
	{OAPI_KEY_NUMPAD9,                             "RCSBack", "Translate back"},
	{OAPI_KEY_NUMPAD2 | KMOD_CTRL,                 "LPRCSPitchUp", "Fine pitch up"},
	{OAPI_KEY_NUMPAD8 | KMOD_CTRL,                 "LPRCSPitchDown", "Fine pitch down"},
	{OAPI_KEY_NUMPAD1 | KMOD_CTRL,                 "LPRCSYawLeft", "Fine yaw left"},
	{OAPI_KEY_NUMPAD3 | KMOD_CTRL,                 "LPRCSYawRight", "Fine yaw right"},
	{OAPI_KEY_NUMPAD4 | KMOD_CTRL,                 "LPRCSBankLeft", "Fine roll left"},
	{OAPI_KEY_NUMPAD6 | KMOD_CTRL,                 "LPRCSBankRight", "Fine roll right"},
	{OAPI_KEY_NUMPAD2 | KMOD_CTRL,                 "LPRCSUp", "Fine translate up"},
	{OAPI_KEY_NUMPAD8 | KMOD_CTRL,                 "LPRCSDown", "Fine translate down"},
	{OAPI_KEY_NUMPAD1 | KMOD_CTRL,                 "LPRCSLeft", "Fine translate left"},
	{OAPI_KEY_NUMPAD3 | KMOD_CTRL,                 "LPRCSRight", "Fine translate right"},
	{OAPI_KEY_NUMPAD6 | KMOD_CTRL,                 "LPRCSForward", "Fine translate forward"},
	{OAPI_KEY_NUMPAD9 | KMOD_CTRL,                 "LPRCSBack", "Fine translate back"},
	{OAPI_KEY_A,                                   "NMHoldAltitude", "Hold altitude"},
	{OAPI_KEY_L,                                   "NMHLevel", "Level horizon"},
	{OAPI_KEY_LBRACKET,                            "NMPrograde", "Hold prograde"},
	{OAPI_KEY_RBRACKET,                            "NMRetrograde", "Hold retrograde"},
	{OAPI_KEY_SEMICOLON,                           "NMNormal", "Hold normal"},
	{OAPI_KEY_APOSTROPHE,                          "NMAntinormal", "Hold antinormal"},
	{OAPI_KEY_NUMPAD5,                             "NMKillrot", "Kill rotation"},
	{OAPI_KEY_D       | KMOD_CTRL,                 "Undock", "Undock"},
	{OAPI_KEY_DELETE,                              "IncElevatorTrim", "Trim nose up"},
	{OAPI_KEY_INSERT,                              "DecElevatorTrim", "Trim nose down"},
	{OAPI_KEY_COMMA,                               "WheelbrakeLeft", "Left wheel brake"},
	{OAPI_KEY_PERIOD,                              "WheelbrakeRight", "Right wheel brake"},
	{OAPI_KEY_H       | KMOD_CTRL,                 "HUD", "Toggle HUD"},
	{OAPI_KEY_H,                                   "HUDMode", "Cycle HUD mode"},
	{OAPI_KEY_R       | KMOD_CTRL,                 "HUDReference", "HUD reference"},
	{OAPI_KEY_R       | KMOD_CTRL | KMOD_ALT,      "HUDTarget", "HUD docking target"},
	{OAPI_KEY_H       | KMOD_ALT,                  "HUDColour", "HUD colour"},
	{OAPI_KEY_T,                                   "IncSimSpeed", "Time warp up"},
	{OAPI_KEY_R,                                   "DecSimSpeed", "Time warp down"},
	{OAPI_KEY_X,                                   "IncFOV", "Zoom out"},
	{OAPI_KEY_Z,                                   "DecFOV", "Zoom in"},
	{OAPI_KEY_X       | KMOD_CTRL,                 "StepIncFOV", "Zoom out a step"},
	{OAPI_KEY_Z       | KMOD_CTRL,                 "StepDecFOV", "Zoom in a step"},
	{OAPI_KEY_F4,                                  "MainMenu", "Main menu"},
	{OAPI_KEY_F1      | KMOD_ALT,                  "DlgHelp", "Help"},
	{OAPI_KEY_F1      | KMOD_CTRL,                 "DlgCamera", "Camera dialog"},
	{OAPI_KEY_F2      | KMOD_CTRL,                 "DlgSimspeed", "Time warp dialog"},
	{OAPI_KEY_F4      | KMOD_CTRL,                 "DlgCustomCmd", "Custom functions"},
	{OAPI_KEY_F9      | KMOD_CTRL,                 "DlgVisualHelpers", "Visual helpers"},
	{OAPI_KEY_F5      | KMOD_CTRL,                 "DlgRecorder", "Flight recorder"},
	{OAPI_KEY_I       | KMOD_CTRL,                 "DlgInfo", "Object info"},
	{OAPI_KEY_M       | KMOD_CTRL,                 "DlgMap", "Map"},
	{OAPI_KEY_F1,                                  "ToggleCamInternal", "Cockpit / external view"},
	{OAPI_KEY_F2,                                  "ToggleTrackMode", "Cycle camera mode"},
	{OAPI_KEY_F8,                                  "TogglePanelMode", "Cycle panel mode"},
	{OAPI_KEY_F9,                                  "TogglePlanetarium", "Planetarium"},
	{OAPI_KEY_F9      | KMOD_ALT,                  "ToggleSurfaceLabels", "Surface labels"},
	{OAPI_KEY_C       | KMOD_CTRL,                 "ToggleRecPlay", "Record / stop playback"},
	{OAPI_KEY_P       | KMOD_CTRL,                 "Pause", "Pause"},
	{OAPI_KEY_S       | KMOD_CTRL,                 "Quicksave", "Quicksave"},
	{OAPI_KEY_Q       | KMOD_CTRL,                 "Quit", "Quit"},
	{OAPI_KEY_F3,                                  "DlgSelectVessel", "Select vessel"},
	{OAPI_KEY_F3      | KMOD_CTRL,                 "SelectPrevVessel", "Previous vessel"},
	{OAPI_KEY_SYSRQ   | KMOD_CTRL,                 "DlgCapture", "Screenshot"},
	{OAPI_KEY_F6,                                  "DlgOptions", "Options"}
};

struct KeyOverride {
	int lfunc;
	WORD key;
};

static const KeyOverride macPreset[] = {
	{OAPI_LKEY_RCSPitchUp,         OAPI_KEY_S},
	{OAPI_LKEY_RCSPitchDown,       OAPI_KEY_W},
	{OAPI_LKEY_RCSYawLeft,         OAPI_KEY_A},
	{OAPI_LKEY_RCSYawRight,        OAPI_KEY_D},
	{OAPI_LKEY_RCSBankLeft,        OAPI_KEY_Q},
	{OAPI_LKEY_RCSBankRight,       OAPI_KEY_E},
	{OAPI_LKEY_RCSUp,              OAPI_KEY_K},
	{OAPI_LKEY_RCSDown,            OAPI_KEY_I},
	{OAPI_LKEY_RCSLeft,            OAPI_KEY_J},
	{OAPI_LKEY_RCSRight,           OAPI_KEY_L},
	{OAPI_LKEY_RCSForward,         OAPI_KEY_H},
	{OAPI_LKEY_RCSBack,            OAPI_KEY_N},
	{OAPI_LKEY_LPRCSPitchUp,       OAPI_KEY_S | KMOD_CAPS},
	{OAPI_LKEY_LPRCSPitchDown,     OAPI_KEY_W | KMOD_CAPS},
	{OAPI_LKEY_LPRCSYawLeft,       OAPI_KEY_A | KMOD_CAPS},
	{OAPI_LKEY_LPRCSYawRight,      OAPI_KEY_D | KMOD_CAPS},
	{OAPI_LKEY_LPRCSBankLeft,      OAPI_KEY_Q | KMOD_CAPS},
	{OAPI_LKEY_LPRCSBankRight,     OAPI_KEY_E | KMOD_CAPS},
	{OAPI_LKEY_LPRCSUp,            OAPI_KEY_K | KMOD_CAPS},
	{OAPI_LKEY_LPRCSDown,          OAPI_KEY_I | KMOD_CAPS},
	{OAPI_LKEY_LPRCSLeft,          OAPI_KEY_J | KMOD_CAPS},
	{OAPI_LKEY_LPRCSRight,         OAPI_KEY_L | KMOD_CAPS},
	{OAPI_LKEY_LPRCSForward,       OAPI_KEY_H | KMOD_CAPS},
	{OAPI_LKEY_LPRCSBack,          OAPI_KEY_N | KMOD_CAPS},
	{OAPI_LKEY_IncMainThrust,      OAPI_KEY_Z},
	{OAPI_LKEY_DecMainThrust,      OAPI_KEY_X},
	{OAPI_LKEY_KillMainRetro,      OAPI_KEY_X | KMOD_CTRL},
	{OAPI_LKEY_FullMainThrust,     OAPI_KEY_Z | KMOD_ALT},
	{OAPI_LKEY_FullRetroThrust,    OAPI_KEY_X | KMOD_ALT},
	{OAPI_LKEY_IncHoverThrust,     OAPI_KEY_R | KMOD_ALT},
	{OAPI_LKEY_DecHoverThrust,     OAPI_KEY_F | KMOD_ALT},
	{OAPI_LKEY_RCSEnable,          OAPI_KEY_R},
	{OAPI_LKEY_RCSMode,            OAPI_KEY_SLASH},
	{OAPI_LKEY_NMKillrot,          OAPI_KEY_T},
	{OAPI_LKEY_NMHoldAltitude,     OAPI_KEY_A | KMOD_CTRL},
	{OAPI_LKEY_NMHLevel,           OAPI_KEY_L | KMOD_CTRL},
	{OAPI_LKEY_IncElevatorTrim,    OAPI_KEY_S | KMOD_ALT},
	{OAPI_LKEY_DecElevatorTrim,    OAPI_KEY_W | KMOD_ALT},
	{OAPI_LKEY_WheelbrakeLeft,     OAPI_KEY_B},
	{OAPI_LKEY_WheelbrakeRight,    OAPI_KEY_B},
	{OAPI_LKEY_HUDMode,            OAPI_KEY_Y},
	{OAPI_LKEY_IncSimSpeed,        OAPI_KEY_PERIOD},
	{OAPI_LKEY_DecSimSpeed,        OAPI_KEY_COMMA},
	{OAPI_LKEY_IncFOV,             OAPI_KEY_MINUS},
	{OAPI_LKEY_DecFOV,             OAPI_KEY_EQUALS},
	{OAPI_LKEY_StepIncFOV,         OAPI_KEY_MINUS | KMOD_CTRL},
	{OAPI_LKEY_StepDecFOV,         OAPI_KEY_EQUALS | KMOD_CTRL},
	{OAPI_LKEY_TrackAdvance,       OAPI_KEY_EQUALS | KMOD_ALT},
	{OAPI_LKEY_TrackRetreat,       OAPI_KEY_MINUS | KMOD_ALT},
	{OAPI_LKEY_MainMenu,           OAPI_KEY_ESCAPE},
	{OAPI_LKEY_ToggleCamInternal,  OAPI_KEY_C},
	{OAPI_LKEY_ToggleTrackMode,    OAPI_KEY_V},
	{OAPI_LKEY_TogglePanelMode,    OAPI_KEY_P},
	{OAPI_LKEY_DlgMap,             OAPI_KEY_M},
	{OAPI_LKEY_CockpitResetCam,    OAPI_KEY_BACKSLASH},
};

Keymap::Keymap ()
{
	SetDefault ();
}

void Keymap::SetPreset (int preset)
{
	SetDefault ();
	if (preset == KEYPRESET_MAC)
		for (const KeyOverride &o : macPreset)
			func[o.lfunc] = o.key;
}

void Keymap::Load (int preset, const char *fname)
{
	if (preset == KEYPRESET_CUSTOM) {
		SetDefault ();
		if (!Read (fname)) Write (fname);
	} else {
		SetPreset (preset);
		Write (fname);
	}
}

const char *Keymap::PresetName (int preset)
{
	switch (preset) {
	case KEYPRESET_ORBITER: return "Orbiter default";
	case KEYPRESET_MAC:     return "Mac-optimized";
	case KEYPRESET_CUSTOM:  return "Custom (keymap.cfg)";
	}
	return "";
}

std::string Keymap::FuncLabel (int lfunc)
{
	return lkeyspec[lfunc].label;
}

std::string Keymap::KeyLabel (int lfunc) const
{
	WORD key = func[lfunc];
	WORD kbase = key & 0x00ff;
	int i;
	for (i = 0; i < NKEY; i++)
		if (keyname[i].id == kbase) break;
	if (i == NKEY || !kbase) return "";
	std::string s;
	if (key & KMOD_CAPS)  s += "Caps Lock + ";
	if (key & KMOD_CTRL)  s += "Ctrl + ";
	if (key & KMOD_ALT)   s += "Option + ";
	if (key & KMOD_SHIFT) s += "Shift + ";
	static const char *pretty[][2] = {
		{"ESC", "Esc"}, {"MINUS", "-"}, {"EQUALS", "="}, {"BACK", "Delete"}, {"TAB", "Tab"},
		{"LBRACKET", "["}, {"RBRACKET", "]"}, {"RETURN", "Return"}, {"SEMICOLON", ";"},
		{"APOSTROPHE", "'"}, {"GRAVE", "`"}, {"BACKSLASH", "\\"}, {"COMMA", ","}, {"PERIOD", "."},
		{"SLASH", "/"}, {"SPACE", "Space"}, {"CAPITAL", "Caps Lock"}, {"MULTIPLY", "Num *"},
		{"SUBTRACT", "Num -"}, {"ADD", "Num +"}, {"DECIMAL", "Num ."}, {"DIVIDE", "Num /"},
		{"NUMPADENTER", "Num Enter"}, {"SYSRQ", "Print"}, {"HOME", "Home"}, {"END", "End"},
		{"PGUP", "Page Up"}, {"PGDOWN", "Page Down"}, {"INSERT", "Insert"}, {"DELETE", "Fwd Delete"},
		{"UP", "Up"}, {"DOWN", "Down"}, {"LEFT", "Left"}, {"RIGHT", "Right"}
	};
	std::string name = keyname[i].name;
	for (auto &p : pretty)
		if (name == p[0]) { name = p[1]; break; }
	if (name.compare (0, 6, "NUMPAD") == 0) name = "Num " + name.substr (6);
	return s + name;
}

bool Keymap::IsFlightFunc (int lfunc) const
{
	return (lfunc >= OAPI_LKEY_IncMainThrust && lfunc <= OAPI_LKEY_DecHoverThrust) ||
		(lfunc >= OAPI_LKEY_RCSPitchUp && lfunc <= OAPI_LKEY_LPRCSBack);
}

bool Keymap::IsFlightKey (DWORD key, char *kstate) const
{
	for (int i = 0; i < LKEY_COUNT; i++) {
		if (!IsFlightFunc (i)) continue;
		DWORD k = key;
		if (IsLogicalKey (k, kstate, i, false)) return true;
	}
	return false;
}

bool Keymap::SplitRCS () const
{
	for (int r = OAPI_LKEY_RCSPitchUp; r <= OAPI_LKEY_RCSBankRight; r++)
		for (int t = OAPI_LKEY_RCSUp; t <= OAPI_LKEY_RCSBack; t++)
			if (func[r] == func[t]) return false;
	return true;
}

void Keymap::SetDefault ()
{
	for (WORD i = 0; i < LKEY_COUNT; i++)
		func[i] = lkeyspec[i].defkey;
}

void Keymap::Write (const char *fname)
{
	char cbuf[256];
	ofstream ofs (fname);
	for (int i = 0; i < LKEY_COUNT; i++)
		ofs << lkeyspec[i].itemstr << " = " << PrintStr (cbuf, func[i]) << endl;
}

bool Keymap::Read (const char *fname)
{
	char cbuf[256];
	ifstream ifs (fname, ios::in);
	if (!ifs) return false;
	for (int i = 0; i < LKEY_COUNT; i++) {
		//func[i] = 0;
		if (GetItemString (ifs, lkeyspec[i].itemstr, cbuf, sizeof(cbuf))) {
			if (!ScanStr (cbuf, func[i])) func[i] = 0;
		}
	}
	return true;
}

bool Keymap::IsLogicalKey (char *kstate, int lfunc) const
{
	// check key
	if (!KEYDOWN (kstate, func[lfunc] & 0x00FF)) return false;
	// check modifiers, if any
	return IsMatchingModifier (kstate, func[lfunc]);
}

bool Keymap::IsLogicalKey (DWORD &key, char *kstate, int lfunc, bool clearkey) const
{
	// check key
	if ((func[lfunc] & 0x00FFu) != key) return false;
	// check modifiers, if any
	if (IsMatchingModifier (kstate, func[lfunc])) {
		if (clearkey) key = 0;
		return true;
	} else {
		return false;
	}
}

bool Keymap::IsMatchingModifier (char *kstate, WORD key) const
{
	WORD kmod;
	if ((key & KMOD_CAPS) && !KEYDOWN (kstate, OAPI_KEY_CAPITAL)) return false;
	if (kmod = (key & KMOD_CTRL)) {
		if (kmod == KMOD_CTRL) {
			if (!KEYMOD_CONTROL(kstate))  return false;
		} else if (kmod == KMOD_LCTRL) {
			if (!KEYMOD_LCONTROL(kstate)) return false;
		} else {
			if (!KEYMOD_RCONTROL(kstate)) return false;
		}
	} else {
		if (KEYMOD_CONTROL(kstate))       return false;
	}

	if (kmod = (key & KMOD_SHIFT)) {
		if (kmod == KMOD_SHIFT) {
			if (!KEYMOD_SHIFT(kstate))    return false;
		} else if (kmod == KMOD_LSHIFT) {
			if (!KEYMOD_LSHIFT(kstate))   return false;
		} else {
			if (!KEYMOD_RSHIFT(kstate))   return false;
		}
	} else {
		if (KEYMOD_SHIFT(kstate))         return false;
	}

	if (kmod = (key & KMOD_ALT)) {
		if (kmod == KMOD_ALT) {
			if (!KEYMOD_ALT(kstate))      return false;
		} else if (kmod == KMOD_LALT) {
			if (!KEYMOD_LALT(kstate))     return false;
		} else {
			if (!KEYMOD_RALT(kstate))     return false;
		}
	} else {
		if (KEYMOD_ALT(kstate))           return false;
	}

	return true;
}

bool Keymap::ScanStr (char *cbuf, WORD &key) const
{
	int i;
	char *tok = strtok (cbuf, " ");
	if (!tok) return false;
	for (i = 0; i < NKEY; i++)
		if (!_stricmp (tok, keyname[i].name)) break;
	if (i == NKEY) return false; // key not found
	key = keyname[i].id;
	for (;;) {
		tok = strtok (NULL, " ");
		if (!tok) break;
		if      (!_stricmp (tok, "LSHIFT")) key |= KMOD_LSHIFT;
		else if (!_stricmp (tok, "RSHIFT")) key |= KMOD_RSHIFT;
		else if (!_stricmp (tok, "SHIFT"))  key |= KMOD_SHIFT;
		else if (!_stricmp (tok, "LCTRL"))  key |= KMOD_LCTRL;
		else if (!_stricmp (tok, "RCTRL"))  key |= KMOD_RCTRL;
		else if (!_stricmp (tok, "CTRL"))   key |= KMOD_CTRL;
		else if (!_stricmp (tok, "LALT"))   key |= KMOD_LALT;
		else if (!_stricmp (tok, "RALT"))   key |= KMOD_RALT;
		else if (!_stricmp (tok, "ALT"))    key |= KMOD_ALT;
		else if (!_stricmp (tok, "CAPS"))   key |= KMOD_CAPS;
	}
	return true;
}

char *Keymap::PrintStr (char *cbuf, WORD &key) const
{
	WORD i, kmod, kbase = key & 0x00ff;

	for (i = 0; i < NKEY; i++)
		if (keyname[i].id == kbase) break;
	if (i == NKEY) {
		cbuf[0] = '\0'; 
	} else {
		strcpy (cbuf, keyname[i].name);
		if (kmod = (key & KMOD_SHIFT)) {
			switch (kmod) {
			case KMOD_SHIFT:  strcat (cbuf, " SHIFT");  break;
			case KMOD_LSHIFT: strcat (cbuf, " LSHIFT"); break;
			case KMOD_RSHIFT: strcat (cbuf, " RSHIFT"); break;
			}
		}
		if (kmod = (key & KMOD_CTRL)) {
			switch (kmod) {
			case KMOD_CTRL:  strcat (cbuf, " CTRL");  break;
			case KMOD_LCTRL: strcat (cbuf, " LCTRL"); break;
			case KMOD_RCTRL: strcat (cbuf, " RCTRL"); break;
			}
		}
		if (kmod = (key & KMOD_ALT)) {
			switch (kmod) {
			case KMOD_ALT:  strcat (cbuf, " ALT");  break;
			case KMOD_LALT: strcat (cbuf, " LALT"); break;
			case KMOD_RALT: strcat (cbuf, " RALT"); break;
			}
		}
		if (key & KMOD_CAPS) strcat (cbuf, " CAPS");
	}
	return cbuf;
}

