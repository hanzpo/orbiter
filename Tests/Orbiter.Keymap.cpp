#include <catch2/catch_test_macros.hpp>
#include "Keymap.h"
#include <cstdio>
#include <cstring>

namespace {

struct KeyState {
	char k[256];
	KeyState() { memset(k, 0, sizeof(k)); }
	KeyState &down(int key) { k[key] = (char)0x80; return *this; }
};

}

TEST_CASE("Orbiter preset keeps the stock bindings", "[keymap]")
{
	Keymap km;
	km.SetPreset(KEYPRESET_ORBITER);
	KeyState s;
	s.down(OAPI_KEY_NUMPAD2);
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_RCSPitchUp));
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_RCSUp));
	CHECK_FALSE(km.SplitRCS());
	CHECK(km.KeyLabel(OAPI_LKEY_IncMainThrust) == "Ctrl + Num +");
}

TEST_CASE("Mac preset flies with WASD and HNJLIK", "[keymap]")
{
	Keymap km;
	km.SetPreset(KEYPRESET_MAC);
	CHECK(km.SplitRCS());

	KeyState s;
	s.down(OAPI_KEY_W).down(OAPI_KEY_Z).down(OAPI_KEY_H);
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_RCSPitchDown));
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_IncMainThrust));
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_RCSForward));
	CHECK_FALSE(km.IsLogicalKey(s.k, OAPI_LKEY_LPRCSPitchDown));

	s.down(OAPI_KEY_CAPITAL);
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_LPRCSPitchDown));
	CHECK(km.IsLogicalKey(s.k, OAPI_LKEY_IncMainThrust));

	KeyState alt;
	alt.down(OAPI_KEY_S).down(OAPI_KEY_LALT);
	CHECK(km.IsLogicalKey(alt.k, OAPI_LKEY_IncElevatorTrim));
	CHECK_FALSE(km.IsLogicalKey(alt.k, OAPI_LKEY_RCSPitchUp));
}

TEST_CASE("Flight keys win over vessel shortcuts, chords do not", "[keymap]")
{
	Keymap km;
	km.SetPreset(KEYPRESET_MAC);
	KeyState none, shift, ctrl;
	shift.down(OAPI_KEY_LSHIFT);
	ctrl.down(OAPI_KEY_LCONTROL);
	CHECK(km.IsFlightKey(OAPI_KEY_D, none.k));
	CHECK(km.IsFlightKey(OAPI_KEY_K, none.k));
	CHECK_FALSE(km.IsFlightKey(OAPI_KEY_G, none.k));
	CHECK_FALSE(km.IsFlightKey(OAPI_KEY_D, shift.k));
	CHECK(km.IsFlightKey(OAPI_KEY_X, ctrl.k));
	CHECK_FALSE(km.IsFlightKey(OAPI_KEY_D, ctrl.k));
}

TEST_CASE("Custom preset round-trips through keymap.cfg", "[keymap]")
{
	const char *path = "keymap.test.cfg";
	Keymap a;
	a.Load(KEYPRESET_MAC, path);
	Keymap b;
	b.Load(KEYPRESET_CUSTOM, path);
	for (int i = 0; i < Keymap::Count(); i++)
		CHECK(a.KeyLabel(i) == b.KeyLabel(i));
	CHECK(b.KeyLabel(OAPI_LKEY_LPRCSPitchUp) == "Caps Lock + S");
	remove(path);
}

TEST_CASE("Every function has a label", "[keymap]")
{
	for (int i = 0; i < Keymap::Count(); i++)
		CHECK_FALSE(Keymap::FuncLabel(i).empty());
}
