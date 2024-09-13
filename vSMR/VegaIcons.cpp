#include "stdafx.h"
#include "VegaIcons.h"

using namespace std;

VegaIcons::VegaIcons(string iconsPath) {
	icons_path = iconsPath;
	loadIcons();
}

void VegaIcons::loadIcons() {
	stringstream ss;
	ifstream ifs;
	ifs.open(icons_path.c_str(), std::ios::binary);
	ss << ifs.rdbuf();
	ifs.close();

	if (document.Parse<0>(ss.str().c_str()).HasParseError()) {
		AfxMessageBox("An error parsing vSMR configuration occurred.\nOnce fixed, reload the config by typing '.smr reload'", MB_OK);

		ASSERT(AfxGetMainWnd() != NULL);
		AfxGetMainWnd()->SendMessage(WM_CLOSE);
	}
}

bool VegaIcons::hasIcon(string icon) {
    return document["types"].HasMember(icon.c_str()) || document["alias"].HasMember(icon.c_str());
}

const Value &VegaIcons::getIcon(string icon) {
    if (document["types"].HasMember(icon.c_str())) {
        return document["types"][icon.c_str()];
	} else if (document["alias"].HasMember(icon.c_str())) {
        return document["types"][document["alias"][icon.c_str()].GetString()];
	} else {
        throw exception("Icon not found");
	}
}

int VegaIcons::getIconPointSize(string icon) {
    if (icon == "1P") return 36;
    if (icon == "1J") return 46;
    if (icon == "2P") return 58;
    if (icon == "2J") return 66;
    if (icon == "2JT") return 46;
    if (icon == "T154") return 56;
    if (icon == "4P") return 96;
    if (icon == "4J") return 72;
    if (icon == "CONC") return 48;
    if (icon == "Heli") return 40;
    if (icon == "Fight") return 54;
    if (icon == "A225") return 86;
    if (icon == "B737") return 62;
    if (icon == "B777") return 56;
    if (icon == "YK40") return 44;
    if (icon == "IL76") return 64;
    return 0;
}

Gdiplus::Point *VegaIcons::getIconPoints(string icon) {
    if (icon == "1P") {
        return new Gdiplus::Point[36] {
            Gdiplus::Point(-113, 0),
            Gdiplus::Point(-104, -2),
            Gdiplus::Point(-104, -33),
            Gdiplus::Point(-87, -33),
            Gdiplus::Point(-84, -31),
            Gdiplus::Point(-80, -4),
            Gdiplus::Point(-37, -10),
            Gdiplus::Point(-30, -11),
            Gdiplus::Point(-25, -12),
            Gdiplus::Point(-14, -100),
            Gdiplus::Point(10, -100),
            Gdiplus::Point(13, -97),
            Gdiplus::Point(15, -13),
            Gdiplus::Point(30, -13),
            Gdiplus::Point(40, -12),
            Gdiplus::Point(49, -10),
            Gdiplus::Point(55, -7),
            Gdiplus::Point(55, -5),
            Gdiplus::Point(63, 0),
            Gdiplus::Point(55, 5),
            Gdiplus::Point(55, 7),
            Gdiplus::Point(49, 10),
            Gdiplus::Point(40, 12),
            Gdiplus::Point(30, 13),
            Gdiplus::Point(15, 13),
            Gdiplus::Point(13, 97),
            Gdiplus::Point(10, 100),
            Gdiplus::Point(-14, 100),
            Gdiplus::Point(-25, 12),
            Gdiplus::Point(-30, 11),
            Gdiplus::Point(-37, 10),
            Gdiplus::Point(-80, 4),
            Gdiplus::Point(-84, 31),
            Gdiplus::Point(-87, 33),
            Gdiplus::Point(-104, 33),
            Gdiplus::Point(-104, 2)
        };
    } 
    if (icon == "1J") {
        return new Gdiplus::Point[46] {
            Gdiplus::Point(-101, 0),
            Gdiplus::Point(-97, -2),
            Gdiplus::Point(-100, -7),
            Gdiplus::Point(-101, -37),
            Gdiplus::Point(-93, -37),
            Gdiplus::Point(-77, -5),
            Gdiplus::Point(-64, -5),
            Gdiplus::Point(-53, -9),
            Gdiplus::Point(-39, -12),
            Gdiplus::Point(-25, -14),
            Gdiplus::Point(-12, -14),
            Gdiplus::Point(-12, -34),
            Gdiplus::Point(-10, -65),
            Gdiplus::Point(-5, -99),
            Gdiplus::Point(4, -99),
            Gdiplus::Point(6, -98),
            Gdiplus::Point(8, -95),
            Gdiplus::Point(20, -14),
            Gdiplus::Point(63, -14),
            Gdiplus::Point(77, -12),
            Gdiplus::Point(90, -9),
            Gdiplus::Point(100, -5),
            Gdiplus::Point(104, -3),
            Gdiplus::Point(106, 0),
            Gdiplus::Point(104, 3),
            Gdiplus::Point(100, 5),
            Gdiplus::Point(90, 9),
            Gdiplus::Point(77, 12),
            Gdiplus::Point(63, 14),
            Gdiplus::Point(20, 14),
            Gdiplus::Point(8, 95),
            Gdiplus::Point(6, 98),
            Gdiplus::Point(4, 99),
            Gdiplus::Point(-5, 99),
            Gdiplus::Point(-10, 65),
            Gdiplus::Point(-12, 34),
            Gdiplus::Point(-12, 14),
            Gdiplus::Point(-25, 14),
            Gdiplus::Point(-39, 12),
            Gdiplus::Point(-53, 9),
            Gdiplus::Point(-64, 5),
            Gdiplus::Point(-77, 5),
            Gdiplus::Point(-93, 37),
            Gdiplus::Point(-101, 37),
            Gdiplus::Point(-100, 7),
            Gdiplus::Point(-97, 2)
        };
    } 
    if (icon == "2P") {
        return new Gdiplus::Point[58] {
            Gdiplus::Point(-98, 0),
            Gdiplus::Point(-94, -2),
            Gdiplus::Point(-94, -24),
            Gdiplus::Point(-86, -24),
            Gdiplus::Point(-81, -4),
            Gdiplus::Point(-66, -7),
            Gdiplus::Point(-51, -9),
            Gdiplus::Point(-29, -9),
            Gdiplus::Point(-17, -10),
            Gdiplus::Point(-9, -12),
            Gdiplus::Point(-9, -33),
            Gdiplus::Point(-6, -90),
            Gdiplus::Point(1, -90),
            Gdiplus::Point(3, -89),
            Gdiplus::Point(4, -87),
            Gdiplus::Point(8, -30),
            Gdiplus::Point(18, -30),
            Gdiplus::Point(22, -29),
            Gdiplus::Point(24, -27),
            Gdiplus::Point(22, -25),
            Gdiplus::Point(18, -24),
            Gdiplus::Point(8, -24),
            Gdiplus::Point(8, -12),
            Gdiplus::Point(14, -10),
            Gdiplus::Point(63, -10),
            Gdiplus::Point(70, -9),
            Gdiplus::Point(77, -6),
            Gdiplus::Point(80, -4),
            Gdiplus::Point(81, -2),
            Gdiplus::Point(82, 0),
            Gdiplus::Point(81, 2),
            Gdiplus::Point(80, 4),
            Gdiplus::Point(77, 6),
            Gdiplus::Point(70, 9),
            Gdiplus::Point(63, 10),
            Gdiplus::Point(14, 10),
            Gdiplus::Point(8, 12),
            Gdiplus::Point(8, 24),
            Gdiplus::Point(18, 24),
            Gdiplus::Point(22, 25),
            Gdiplus::Point(24, 27),
            Gdiplus::Point(22, 29),
            Gdiplus::Point(18, 30),
            Gdiplus::Point(8, 30),
            Gdiplus::Point(4, 87),
            Gdiplus::Point(3, 89),
            Gdiplus::Point(1, 90),
            Gdiplus::Point(-6, 90),
            Gdiplus::Point(-9, 33),
            Gdiplus::Point(-9, 12),
            Gdiplus::Point(-17, 10),
            Gdiplus::Point(-29, 9),
            Gdiplus::Point(-51, 9),
            Gdiplus::Point(-66, 7),
            Gdiplus::Point(-81, 4),
            Gdiplus::Point(-86, 24),
            Gdiplus::Point(-94, 24),
            Gdiplus::Point(-94, 2)
        };
    }
    if (icon == "2J") {
        return new Gdiplus::Point[66] {
            Gdiplus::Point(-154, 0),
            Gdiplus::Point(-154, -2),
            Gdiplus::Point(-147, -5),
            Gdiplus::Point(-139, -6),
            Gdiplus::Point(-149, -47),
            Gdiplus::Point(-138, -47),
            Gdiplus::Point(-113, -10),
            Gdiplus::Point(-101, -13),
            Gdiplus::Point(-90, -14),
            Gdiplus::Point(-20, -14),
            Gdiplus::Point(-20, -47),
            Gdiplus::Point(-45, -120),
            Gdiplus::Point(-35, -120),
            Gdiplus::Point(-32, -119),
            Gdiplus::Point(-30, -117),
            Gdiplus::Point(8, -49),
            Gdiplus::Point(12, -50),
            Gdiplus::Point(19, -51),
            Gdiplus::Point(28, -51),
            Gdiplus::Point(35, -50),
            Gdiplus::Point(38, -49),
            Gdiplus::Point(38, -36),
            Gdiplus::Point(35, -34),
            Gdiplus::Point(30, -33),
            Gdiplus::Point(21, -33),
            Gdiplus::Point(15, -34),
            Gdiplus::Point(27, -14),
            Gdiplus::Point(91, -14),
            Gdiplus::Point(100, -13),
            Gdiplus::Point(106, -11),
            Gdiplus::Point(111, -8),
            Gdiplus::Point(115, -5),
            Gdiplus::Point(117, -2),
            Gdiplus::Point(118, 0),
            Gdiplus::Point(117, 2),
            Gdiplus::Point(115, 5),
            Gdiplus::Point(111, 8),
            Gdiplus::Point(106, 11),
            Gdiplus::Point(100, 13),
            Gdiplus::Point(91, 14),
            Gdiplus::Point(27, 14),
            Gdiplus::Point(15, 34),
            Gdiplus::Point(21, 33),
            Gdiplus::Point(30, 33),
            Gdiplus::Point(35, 34),
            Gdiplus::Point(38, 36),
            Gdiplus::Point(38, 49),
            Gdiplus::Point(35, 50),
            Gdiplus::Point(28, 51),
            Gdiplus::Point(19, 51),
            Gdiplus::Point(12, 50),
            Gdiplus::Point(8, 49),
            Gdiplus::Point(-30, 117),
            Gdiplus::Point(-32, 119),
            Gdiplus::Point(-35, 120),
            Gdiplus::Point(-45, 120),
            Gdiplus::Point(-20, 47),
            Gdiplus::Point(-20, 14),
            Gdiplus::Point(-90, 14),
            Gdiplus::Point(-101, 13),
            Gdiplus::Point(-113, 10),
            Gdiplus::Point(-138, 47),
            Gdiplus::Point(-149, 47),
            Gdiplus::Point(-139, 6),
            Gdiplus::Point(-147, 5),
            Gdiplus::Point(-154, 2)
        };
    }
    if (icon == "2JT") {
        return new Gdiplus::Point[46] {
            Gdiplus::Point(-84, 0),
            Gdiplus::Point(-96, -29),
            Gdiplus::Point(-87, -29),
            Gdiplus::Point(-68, -3),
            Gdiplus::Point(-64, -4),
            Gdiplus::Point(-59, -9),
            Gdiplus::Point(-59, -15),
            Gdiplus::Point(-51, -16),
            Gdiplus::Point(-49, -17),
            Gdiplus::Point(-42, -18),
            Gdiplus::Point(-35, -18),
            Gdiplus::Point(-31, -16),
            Gdiplus::Point(-31, -7),
            Gdiplus::Point(-22, -7),
            Gdiplus::Point(-22, -13),
            Gdiplus::Point(-47, -76),
            Gdiplus::Point(-39, -76),
            Gdiplus::Point(-36, -75),
            Gdiplus::Point(19, -7),
            Gdiplus::Point(52, -7),
            Gdiplus::Point(59, -6),
            Gdiplus::Point(65, -4),
            Gdiplus::Point(69, -2),
            Gdiplus::Point(70, 0),
            Gdiplus::Point(69, 2),
            Gdiplus::Point(65, 4),
            Gdiplus::Point(59, 6),
            Gdiplus::Point(52, 7),
            Gdiplus::Point(19, 7),
            Gdiplus::Point(-36, 75),
            Gdiplus::Point(-39, 76),
            Gdiplus::Point(-47, 76),
            Gdiplus::Point(-22, 13),
            Gdiplus::Point(-22, 7),
            Gdiplus::Point(-31, 7),
            Gdiplus::Point(-31, 16),
            Gdiplus::Point(-35, 18),
            Gdiplus::Point(-42, 18),
            Gdiplus::Point(-49, 17),
            Gdiplus::Point(-51, 16),
            Gdiplus::Point(-59, 15),
            Gdiplus::Point(-59, 9),
            Gdiplus::Point(-64, 4),
            Gdiplus::Point(-68, 3),
            Gdiplus::Point(-87, 29),
            Gdiplus::Point(-96, 29)
        };
    }
    if (icon == "T154") {
        return new Gdiplus::Point[56] {
            Gdiplus::Point(-81, 0),
            Gdiplus::Point(-76, -1),
            Gdiplus::Point(-89, -22),
            Gdiplus::Point(-82, -22),
            Gdiplus::Point(-66, -4),
            Gdiplus::Point(-58, -4),
            Gdiplus::Point(-55, -7),
            Gdiplus::Point(-52, -8),
            Gdiplus::Point(-52, -11),
            Gdiplus::Point(-45, -13),
            Gdiplus::Point(-38, -14),
            Gdiplus::Point(-31, -14),
            Gdiplus::Point(-30, -13),
            Gdiplus::Point(-30, -9),
            Gdiplus::Point(-32, -8),
            Gdiplus::Point(-32, -6),
            Gdiplus::Point(-19, -7),
            Gdiplus::Point(-19, -21),
            Gdiplus::Point(-41, -64),
            Gdiplus::Point(-34, -64),
            Gdiplus::Point(12, -7),
            Gdiplus::Point(46, -7),
            Gdiplus::Point(57, -6),
            Gdiplus::Point(64, -5),
            Gdiplus::Point(68, -4),
            Gdiplus::Point(71, -3),
            Gdiplus::Point(73, -2),
            Gdiplus::Point(74, -1),
            Gdiplus::Point(75, 0),
            Gdiplus::Point(74, 1),
            Gdiplus::Point(73, 2),
            Gdiplus::Point(71, 3),
            Gdiplus::Point(68, 4),
            Gdiplus::Point(64, 5),
            Gdiplus::Point(57, 6),
            Gdiplus::Point(46, 7),
            Gdiplus::Point(12, 7),
            Gdiplus::Point(-34, 64),
            Gdiplus::Point(-41, 64),
            Gdiplus::Point(-19, 21),
            Gdiplus::Point(-19, 7),
            Gdiplus::Point(-32, 6),
            Gdiplus::Point(-32, 8),
            Gdiplus::Point(-30, 9),
            Gdiplus::Point(-30, 13),
            Gdiplus::Point(-31, 14),
            Gdiplus::Point(-38, 14),
            Gdiplus::Point(-45, 13),
            Gdiplus::Point(-52, 11),
            Gdiplus::Point(-52, 8),
            Gdiplus::Point(-55, 7),
            Gdiplus::Point(-58, 4),
            Gdiplus::Point(-66, 4),
            Gdiplus::Point(-82, 22),
            Gdiplus::Point(-89, 22),
            Gdiplus::Point(-76, 1)
        };
    }
    if (icon == "4P") {
        return new Gdiplus::Point[96] {
            Gdiplus::Point(-121, 0),
            Gdiplus::Point(-121, -4),
            Gdiplus::Point(-119, -6),
            Gdiplus::Point(-114, -7),
            Gdiplus::Point(-111, -33),
            Gdiplus::Point(-109, -35),
            Gdiplus::Point(-100, -35),
            Gdiplus::Point(-98, -33),
            Gdiplus::Point(-93, -9),
            Gdiplus::Point(-81, -11),
            Gdiplus::Point(-45, -11),
            Gdiplus::Point(-37, -15),
            Gdiplus::Point(-27, -16),
            Gdiplus::Point(-14, -16),
            Gdiplus::Point(-8, -124),
            Gdiplus::Point(-7, -126),
            Gdiplus::Point(-4, -127),
            Gdiplus::Point(3, -127),
            Gdiplus::Point(5, -124),
            Gdiplus::Point(11, -56),
            Gdiplus::Point(26, -56),
            Gdiplus::Point(27, -55),
            Gdiplus::Point(31, -55),
            Gdiplus::Point(33, -53),
            Gdiplus::Point(31, -51),
            Gdiplus::Point(27, -51),
            Gdiplus::Point(26, -50),
            Gdiplus::Point(12, -50),
            Gdiplus::Point(14, -29),
            Gdiplus::Point(27, -29),
            Gdiplus::Point(28, -28),
            Gdiplus::Point(32, -28),
            Gdiplus::Point(34, -26),
            Gdiplus::Point(32, -24),
            Gdiplus::Point(28, -24),
            Gdiplus::Point(27, -23),
            Gdiplus::Point(15, -23),
            Gdiplus::Point(16, -16),
            Gdiplus::Point(30, -16),
            Gdiplus::Point(35, -15),
            Gdiplus::Point(39, -13),
            Gdiplus::Point(41, -11),
            Gdiplus::Point(66, -11),
            Gdiplus::Point(75, -10),
            Gdiplus::Point(83, -8),
            Gdiplus::Point(89, -6),
            Gdiplus::Point(93, -4),
            Gdiplus::Point(96, -2),
            Gdiplus::Point(98, 0),
            Gdiplus::Point(96, 2),
            Gdiplus::Point(93, 4),
            Gdiplus::Point(89, 6),
            Gdiplus::Point(83, 8),
            Gdiplus::Point(75, 10),
            Gdiplus::Point(66, 11),
            Gdiplus::Point(41, 11),
            Gdiplus::Point(39, 13),
            Gdiplus::Point(35, 15),
            Gdiplus::Point(30, 16),
            Gdiplus::Point(16, 16),
            Gdiplus::Point(15, 23),
            Gdiplus::Point(27, 23),
            Gdiplus::Point(28, 24),
            Gdiplus::Point(32, 24),
            Gdiplus::Point(34, 26),
            Gdiplus::Point(32, 28),
            Gdiplus::Point(28, 28),
            Gdiplus::Point(27, 29),
            Gdiplus::Point(14, 29),
            Gdiplus::Point(12, 50),
            Gdiplus::Point(26, 50),
            Gdiplus::Point(27, 51),
            Gdiplus::Point(31, 51),
            Gdiplus::Point(33, 53),
            Gdiplus::Point(31, 55),
            Gdiplus::Point(27, 55),
            Gdiplus::Point(26, 56),
            Gdiplus::Point(11, 56),
            Gdiplus::Point(5, 124),
            Gdiplus::Point(3, 127),
            Gdiplus::Point(-4, 127),
            Gdiplus::Point(-7, 126),
            Gdiplus::Point(-8, 124),
            Gdiplus::Point(-14, 16),
            Gdiplus::Point(-27, 16),
            Gdiplus::Point(-37, 15),
            Gdiplus::Point(-45, 11),
            Gdiplus::Point(-81, 11),
            Gdiplus::Point(-93, 9),
            Gdiplus::Point(-98, 33),
            Gdiplus::Point(-100, 35),
            Gdiplus::Point(-109, 35),
            Gdiplus::Point(-111, 33),
            Gdiplus::Point(-114, 7),
            Gdiplus::Point(-119, 6),
            Gdiplus::Point(-121, 4),
        };
    }
    if (icon == "4J") {
        return new Gdiplus::Point[72] {
            Gdiplus::Point(-88, 0),
            Gdiplus::Point(-85, -1),
            Gdiplus::Point(-80, -2),
            Gdiplus::Point(-78, -3),
            Gdiplus::Point(-90, -33),
            Gdiplus::Point(-85, -33),
            Gdiplus::Point(-67, -7),
            Gdiplus::Point(-60, -7),
            Gdiplus::Point(-53, -8),
            Gdiplus::Point(-38, -9),
            Gdiplus::Point(-14, -9),
            Gdiplus::Point(-14, -14),
            Gdiplus::Point(-15, -19),
            Gdiplus::Point(-39, -72),
            Gdiplus::Point(-33, -72),
            Gdiplus::Point(-31, -71),
            Gdiplus::Point(-13, -49),
            Gdiplus::Point(0, -49),
            Gdiplus::Point(1, -48),
            Gdiplus::Point(1, -44),
            Gdiplus::Point(0, -43),
            Gdiplus::Point(-8, -43),
            Gdiplus::Point(1, -31),
            Gdiplus::Point(14, -31),
            Gdiplus::Point(15, -30),
            Gdiplus::Point(15, -26),
            Gdiplus::Point(14, -25),
            Gdiplus::Point(6, -25),
            Gdiplus::Point(18, -9),
            Gdiplus::Point(38, -9),
            Gdiplus::Point(54, -8),
            Gdiplus::Point(60, -7),
            Gdiplus::Point(63, -6),
            Gdiplus::Point(65, -5),
            Gdiplus::Point(67, -3),
            Gdiplus::Point(69, -1),
            Gdiplus::Point(70, 0),
            Gdiplus::Point(69, 1),
            Gdiplus::Point(67, 3),
            Gdiplus::Point(65, 5),
            Gdiplus::Point(63, 6),
            Gdiplus::Point(60, 7),
            Gdiplus::Point(54, 8),
            Gdiplus::Point(38, 9),
            Gdiplus::Point(18, 9),
            Gdiplus::Point(6, 25),
            Gdiplus::Point(14, 25),
            Gdiplus::Point(15, 26),
            Gdiplus::Point(15, 30),
            Gdiplus::Point(14, 31),
            Gdiplus::Point(1, 31),
            Gdiplus::Point(-8, 43),
            Gdiplus::Point(0, 43),
            Gdiplus::Point(1, 44),
            Gdiplus::Point(1, 48),
            Gdiplus::Point(0, 49),
            Gdiplus::Point(-13, 49),
            Gdiplus::Point(-31, 71),
            Gdiplus::Point(-33, 72),
            Gdiplus::Point(-39, 72),
            Gdiplus::Point(-15, 19),
            Gdiplus::Point(-14, 14),
            Gdiplus::Point(-14, 9),
            Gdiplus::Point(-38, 9),
            Gdiplus::Point(-53, 8),
            Gdiplus::Point(-60, 7),
            Gdiplus::Point(-67, 7),
            Gdiplus::Point(-85, 33),
            Gdiplus::Point(-90, 33),
            Gdiplus::Point(-78, 3),
            Gdiplus::Point(-80, 2),
            Gdiplus::Point(-85, 1)
        };
    }
    if (icon == "CONC") {
        return new Gdiplus::Point[48] {
            Gdiplus::Point(-187, 0),
            Gdiplus::Point(-180, -3),
            Gdiplus::Point(-166, -6),
            Gdiplus::Point(-147, -8),
            Gdiplus::Point(-129, -9),
            Gdiplus::Point(-128, -26),
            Gdiplus::Point(-125, -45),
            Gdiplus::Point(-123, -62),
            Gdiplus::Point(-121, -73),
            Gdiplus::Point(-119, -78),
            Gdiplus::Point(-109, -77),
            Gdiplus::Point(-97, -74),
            Gdiplus::Point(-88, -70),
            Gdiplus::Point(-74, -61),
            Gdiplus::Point(-56, -49),
            Gdiplus::Point(-39, -39),
            Gdiplus::Point(-23, -31),
            Gdiplus::Point(-6, -25),
            Gdiplus::Point(24, -16),
            Gdiplus::Point(46, -10),
            Gdiplus::Point(86, -10),
            Gdiplus::Point(109, -9),
            Gdiplus::Point(132, -6),
            Gdiplus::Point(151, -3),
            Gdiplus::Point(167, 0),
            Gdiplus::Point(151, 3),
            Gdiplus::Point(132, 6),
            Gdiplus::Point(109, 9),
            Gdiplus::Point(86, 10),
            Gdiplus::Point(46, 10),
            Gdiplus::Point(24, 16),
            Gdiplus::Point(-6, 25),
            Gdiplus::Point(-23, 31),
            Gdiplus::Point(-39, 39),
            Gdiplus::Point(-56, 49),
            Gdiplus::Point(-74, 61),
            Gdiplus::Point(-88, 70),
            Gdiplus::Point(-97, 74),
            Gdiplus::Point(-109, 77),
            Gdiplus::Point(-119, 78),
            Gdiplus::Point(-121, 73),
            Gdiplus::Point(-123, 62),
            Gdiplus::Point(-125, 45),
            Gdiplus::Point(-128, 26),
            Gdiplus::Point(-129, 9),
            Gdiplus::Point(-147, 8),
            Gdiplus::Point(-166, 6),
            Gdiplus::Point(-180, 3)
        };
    }
    if (icon == "Heli") {
        return new Gdiplus::Point[40] {
            Gdiplus::Point(-88, 0),
            Gdiplus::Point(-81, -2),
            Gdiplus::Point(-79, -18),
            Gdiplus::Point(-75, -18),
            Gdiplus::Point(-74, -2),
            Gdiplus::Point(-33, -4),
            Gdiplus::Point(-24, -9),
            Gdiplus::Point(-18, -11),
            Gdiplus::Point(-8, -11),
            Gdiplus::Point(-35, -47),
            Gdiplus::Point(-32, -49),
            Gdiplus::Point(-3, -11),
            Gdiplus::Point(7, -11),
            Gdiplus::Point(34, -48),
            Gdiplus::Point(37, -46),
            Gdiplus::Point(12, -11),
            Gdiplus::Point(20, -11),
            Gdiplus::Point(29, -9),
            Gdiplus::Point(34, -6),
            Gdiplus::Point(36, -3),
            Gdiplus::Point(37, 0),
            Gdiplus::Point(36, 3),
            Gdiplus::Point(34, 6),
            Gdiplus::Point(29, 9),
            Gdiplus::Point(20, 11),
            Gdiplus::Point(12, 11),
            Gdiplus::Point(37, 46),
            Gdiplus::Point(34, 48),
            Gdiplus::Point(7, 11),
            Gdiplus::Point(-3, 11),
            Gdiplus::Point(-32, 49),
            Gdiplus::Point(-35, 47),
            Gdiplus::Point(-8, 11),
            Gdiplus::Point(-18, 11),
            Gdiplus::Point(-24, 9),
            Gdiplus::Point(-33, 4),
            Gdiplus::Point(-74, 2),
            Gdiplus::Point(-75, 18),
            Gdiplus::Point(-79, 18),
            Gdiplus::Point(-81, 2)
        };
    }
    if (icon == "Fight") {
        return new Gdiplus::Point[54] {
            Gdiplus::Point(-131, 0),
            Gdiplus::Point(-129, -4),
            Gdiplus::Point(-116, -7),
            Gdiplus::Point(-95, -8),
            Gdiplus::Point(-107, -11),
            Gdiplus::Point(-107, -21),
            Gdiplus::Point(-95, -24),
            Gdiplus::Point(-107, -26),
            Gdiplus::Point(-111, -53),
            Gdiplus::Point(-99, -61),
            Gdiplus::Point(-64, -28),
            Gdiplus::Point(-54, -28),
            Gdiplus::Point(-70, -93),
            Gdiplus::Point(-31, -93),
            Gdiplus::Point(-30, -92),
            Gdiplus::Point(-31, -91),
            Gdiplus::Point(-46, -91),
            Gdiplus::Point(14, -25),
            Gdiplus::Point(19, -25),
            Gdiplus::Point(46, -16),
            Gdiplus::Point(69, -12),
            Gdiplus::Point(87, -9),
            Gdiplus::Point(97, -8),
            Gdiplus::Point(112, -8),
            Gdiplus::Point(122, -7),
            Gdiplus::Point(131, -5),
            Gdiplus::Point(137, -3),
            Gdiplus::Point(144, 0),
            Gdiplus::Point(137, 3),
            Gdiplus::Point(131, 5),
            Gdiplus::Point(122, 7),
            Gdiplus::Point(112, 8),
            Gdiplus::Point(97, 8),
            Gdiplus::Point(87, 9),
            Gdiplus::Point(69, 12),
            Gdiplus::Point(46, 16),
            Gdiplus::Point(19, 25),
            Gdiplus::Point(14, 25),
            Gdiplus::Point(-46, 91),
            Gdiplus::Point(-31, 91),
            Gdiplus::Point(-30, 92),
            Gdiplus::Point(-31, 93),
            Gdiplus::Point(-70, 93),
            Gdiplus::Point(-54, 28),
            Gdiplus::Point(-64, 28),
            Gdiplus::Point(-99, 61),
            Gdiplus::Point(-111, 53),
            Gdiplus::Point(-107, 26),
            Gdiplus::Point(-95, 24),
            Gdiplus::Point(-107, 21),
            Gdiplus::Point(-107, 11),
            Gdiplus::Point(-95, 8),
            Gdiplus::Point(-116, 7),
            Gdiplus::Point(-129, 4)
        };
    }
    if (icon == "A225") {
        return new Gdiplus::Point[86] {
            Gdiplus::Point(-113, 0),
            Gdiplus::Point(-112, -2),
            Gdiplus::Point(-107, -3),
            Gdiplus::Point(-129, -42),
            Gdiplus::Point(-119, -44),
            Gdiplus::Point(-108, -44),
            Gdiplus::Point(-99, -42),
            Gdiplus::Point(-107, -40),
            Gdiplus::Point(-82, -8),
            Gdiplus::Point(-70, -10),
            Gdiplus::Point(-21, -10),
            Gdiplus::Point(-21, -29),
            Gdiplus::Point(-46, -116),
            Gdiplus::Point(-41, -116),
            Gdiplus::Point(-37, -114),
            Gdiplus::Point(-9, -69),
            Gdiplus::Point(-4, -70),
            Gdiplus::Point(3, -70),
            Gdiplus::Point(5, -69),
            Gdiplus::Point(5, -63),
            Gdiplus::Point(3, -62),
            Gdiplus::Point(-5, -62),
            Gdiplus::Point(3, -49),
            Gdiplus::Point(8, -50),
            Gdiplus::Point(15, -50),
            Gdiplus::Point(17, -49),
            Gdiplus::Point(17, -43),
            Gdiplus::Point(15, -42),
            Gdiplus::Point(7, -42),
            Gdiplus::Point(16, -29),
            Gdiplus::Point(20, -30),
            Gdiplus::Point(27, -30),
            Gdiplus::Point(29, -29),
            Gdiplus::Point(29, -23),
            Gdiplus::Point(27, -22),
            Gdiplus::Point(20, -22),
            Gdiplus::Point(27, -10),
            Gdiplus::Point(55, -10),
            Gdiplus::Point(66, -9),
            Gdiplus::Point(74, -8),
            Gdiplus::Point(81, -6),
            Gdiplus::Point(86, -3),
            Gdiplus::Point(89, -1),
            Gdiplus::Point(90, 0),
            Gdiplus::Point(89, 1),
            Gdiplus::Point(86, 3),
            Gdiplus::Point(81, 6),
            Gdiplus::Point(74, 8),
            Gdiplus::Point(66, 9),
            Gdiplus::Point(55, 10),
            Gdiplus::Point(27, 10),
            Gdiplus::Point(20, 22),
            Gdiplus::Point(27, 22),
            Gdiplus::Point(29, 23),
            Gdiplus::Point(29, 29),
            Gdiplus::Point(27, 30),
            Gdiplus::Point(20, 30),
            Gdiplus::Point(16, 29),
            Gdiplus::Point(7, 42),
            Gdiplus::Point(15, 42),
            Gdiplus::Point(17, 43),
            Gdiplus::Point(17, 49),
            Gdiplus::Point(15, 50),
            Gdiplus::Point(8, 50),
            Gdiplus::Point(3, 49),
            Gdiplus::Point(-5, 62),
            Gdiplus::Point(3, 62),
            Gdiplus::Point(5, 63),
            Gdiplus::Point(5, 69),
            Gdiplus::Point(3, 70),
            Gdiplus::Point(-4, 70),
            Gdiplus::Point(-9, 69),
            Gdiplus::Point(-37, 114),
            Gdiplus::Point(-41, 116),
            Gdiplus::Point(-46, 116),
            Gdiplus::Point(-21, 29),
            Gdiplus::Point(-21, 10),
            Gdiplus::Point(-70, 10),
            Gdiplus::Point(-82, 8),
            Gdiplus::Point(-107, 40),
            Gdiplus::Point(-99, 42),
            Gdiplus::Point(-108, 44),
            Gdiplus::Point(-119, 44),
            Gdiplus::Point(-129, 42),
            Gdiplus::Point(-107, 3),
            Gdiplus::Point(-112, 2)
        };
    }
    if (icon == "B737") {
        return new Gdiplus::Point[62]{
            Gdiplus::Point(-134, 0),
            Gdiplus::Point(-125, -3),
            Gdiplus::Point(-137, -46),
            Gdiplus::Point(-132, -46),
            Gdiplus::Point(-105, -8),
            Gdiplus::Point(-95, -10),
            Gdiplus::Point(-77, -12),
            Gdiplus::Point(-20, -12),
            Gdiplus::Point(-20, -33),
            Gdiplus::Point(-44, -110),
            Gdiplus::Point(-36, -109),
            Gdiplus::Point(-32, -107),
            Gdiplus::Point(6, -37),
            Gdiplus::Point(10, -38),
            Gdiplus::Point(16, -39),
            Gdiplus::Point(26, -39),
            Gdiplus::Point(29, -38),
            Gdiplus::Point(30, -37),
            Gdiplus::Point(30, -26),
            Gdiplus::Point(27, -25),
            Gdiplus::Point(23, -24),
            Gdiplus::Point(18, -24),
            Gdiplus::Point(12, -25),
            Gdiplus::Point(21, -14),
            Gdiplus::Point(25, -12),
            Gdiplus::Point(79, -12),
            Gdiplus::Point(87, -11),
            Gdiplus::Point(95, -9),
            Gdiplus::Point(106, -6),
            Gdiplus::Point(111, -4),
            Gdiplus::Point(114, -2),
            Gdiplus::Point(115, 0),
            Gdiplus::Point(114, 2),
            Gdiplus::Point(111, 4),
            Gdiplus::Point(106, 6),
            Gdiplus::Point(95, 9),
            Gdiplus::Point(87, 11),
            Gdiplus::Point(79, 12),
            Gdiplus::Point(25, 12),
            Gdiplus::Point(21, 14),
            Gdiplus::Point(12, 25),
            Gdiplus::Point(18, 24),
            Gdiplus::Point(23, 24),
            Gdiplus::Point(27, 25),
            Gdiplus::Point(30, 26),
            Gdiplus::Point(30, 37),
            Gdiplus::Point(29, 38),
            Gdiplus::Point(26, 39),
            Gdiplus::Point(16, 39),
            Gdiplus::Point(10, 38),
            Gdiplus::Point(6, 37),
            Gdiplus::Point(-32, 107),
            Gdiplus::Point(-36, 109),
            Gdiplus::Point(-44, 110),
            Gdiplus::Point(-20, 33),
            Gdiplus::Point(-20, 12),
            Gdiplus::Point(-77, 12),
            Gdiplus::Point(-95, 10),
            Gdiplus::Point(-105, 8),
            Gdiplus::Point(-132, 46),
            Gdiplus::Point(-137, 46),
            Gdiplus::Point(-125, 3)
        };
    }
    if (icon == "B777") {
        return new Gdiplus::Point[56]{
            Gdiplus::Point(-133, 0),
            Gdiplus::Point(-123, -4),
            Gdiplus::Point(-136, -36),
            Gdiplus::Point(-127, -36),
            Gdiplus::Point(-105, -9),
            Gdiplus::Point(-102, -8),
            Gdiplus::Point(-95, -9),
            Gdiplus::Point(-77, -11),
            Gdiplus::Point(-22, -11),
            Gdiplus::Point(-22, -31),
            Gdiplus::Point(-50, -106),
            Gdiplus::Point(-43, -106),
            Gdiplus::Point(5, -37),
            Gdiplus::Point(8, -38),
            Gdiplus::Point(15, -40),
            Gdiplus::Point(25, -40),
            Gdiplus::Point(28, -39),
            Gdiplus::Point(28, -28),
            Gdiplus::Point(25, -26),
            Gdiplus::Point(17, -26),
            Gdiplus::Point(12, -27),
            Gdiplus::Point(21, -13),
            Gdiplus::Point(25, -11),
            Gdiplus::Point(84, -11),
            Gdiplus::Point(92, -10),
            Gdiplus::Point(100, -8),
            Gdiplus::Point(107, -5),
            Gdiplus::Point(111, -2),
            Gdiplus::Point(113, 0),
            Gdiplus::Point(111, 2),
            Gdiplus::Point(107, 5),
            Gdiplus::Point(100, 8),
            Gdiplus::Point(92, 10),
            Gdiplus::Point(84, 11),
            Gdiplus::Point(25, 11),
            Gdiplus::Point(21, 13),
            Gdiplus::Point(12, 27),
            Gdiplus::Point(17, 26),
            Gdiplus::Point(25, 26),
            Gdiplus::Point(28, 28),
            Gdiplus::Point(28, 39),
            Gdiplus::Point(25, 40),
            Gdiplus::Point(15, 40),
            Gdiplus::Point(8, 38),
            Gdiplus::Point(5, 37),
            Gdiplus::Point(-43, 106),
            Gdiplus::Point(-50, 106),
            Gdiplus::Point(-22, 31),
            Gdiplus::Point(-22, 11),
            Gdiplus::Point(-77, 11),
            Gdiplus::Point(-95, 9),
            Gdiplus::Point(-102, 8),
            Gdiplus::Point(-105, 9),
            Gdiplus::Point(-127, 36),
            Gdiplus::Point(-136, 36),
            Gdiplus::Point(-123, 4)
        };
    }
    if (icon == "YK40") {
        return new Gdiplus::Point[44]{
            Gdiplus::Point(-103, 0),
            Gdiplus::Point(-101, -40),
            Gdiplus::Point(-99, -42),
            Gdiplus::Point(-90, -42),
            Gdiplus::Point(-88, -40),
            Gdiplus::Point(-78, -5),
            Gdiplus::Point(-67, -7),
            Gdiplus::Point(-55, -9),
            Gdiplus::Point(-46, -17),
            Gdiplus::Point(-46, -21),
            Gdiplus::Point(-40, -22),
            Gdiplus::Point(-38, -23),
            Gdiplus::Point(-23, -24),
            Gdiplus::Point(-10, -129),
            Gdiplus::Point(-7, -131),
            Gdiplus::Point(5, -131),
            Gdiplus::Point(7, -129),
            Gdiplus::Point(15, -12),
            Gdiplus::Point(74, -12),
            Gdiplus::Point(86, -10),
            Gdiplus::Point(95, -7),
            Gdiplus::Point(102, -3),
            Gdiplus::Point(104, 0),
            Gdiplus::Point(102, 3),
            Gdiplus::Point(95, 7),
            Gdiplus::Point(86, 10),
            Gdiplus::Point(74, 12),
            Gdiplus::Point(15, 12),
            Gdiplus::Point(7, 129),
            Gdiplus::Point(5, 131),
            Gdiplus::Point(-7, 131),
            Gdiplus::Point(-10, 129),
            Gdiplus::Point(-23, 24),
            Gdiplus::Point(-38, 23),
            Gdiplus::Point(-40, 22),
            Gdiplus::Point(-46, 21),
            Gdiplus::Point(-46, 17),
            Gdiplus::Point(-55, 9),
            Gdiplus::Point(-67, 7),
            Gdiplus::Point(-78, 5),
            Gdiplus::Point(-88, 40),
            Gdiplus::Point(-90, 42),
            Gdiplus::Point(-99, 42),
            Gdiplus::Point(-101, 40)
        };
    }
    if (icon == "IL76") {
        return new Gdiplus::Point[64]{
            Gdiplus::Point(-86, 0),
            Gdiplus::Point(-79, -2),
            Gdiplus::Point(-88, -29),
            Gdiplus::Point(-81, -29),
            Gdiplus::Point(-64, -5),
            Gdiplus::Point(-55, -7),
            Gdiplus::Point(-42, -8),
            Gdiplus::Point(-29, -9),
            Gdiplus::Point(-26, -10),
            Gdiplus::Point(-18, -11),
            Gdiplus::Point(-11, -11),
            Gdiplus::Point(-14, -39),
            Gdiplus::Point(-29, -85),
            Gdiplus::Point(-18, -85),
            Gdiplus::Point(8, -39),
            Gdiplus::Point(23, -39),
            Gdiplus::Point(24, -38),
            Gdiplus::Point(24, -33),
            Gdiplus::Point(23, -32),
            Gdiplus::Point(11, -32),
            Gdiplus::Point(15, -25),
            Gdiplus::Point(24, -25),
            Gdiplus::Point(25, -24),
            Gdiplus::Point(25, -19),
            Gdiplus::Point(24, -18),
            Gdiplus::Point(19, -18),
            Gdiplus::Point(24, -9),
            Gdiplus::Point(45, -9),
            Gdiplus::Point(52, -8),
            Gdiplus::Point(61, -6),
            Gdiplus::Point(66, -4),
            Gdiplus::Point(70, -2),
            Gdiplus::Point(71, 0),
            Gdiplus::Point(70, 2),
            Gdiplus::Point(66, 4),
            Gdiplus::Point(61, 6),
            Gdiplus::Point(52, 8),
            Gdiplus::Point(45, 9),
            Gdiplus::Point(24, 9),
            Gdiplus::Point(19, 18),
            Gdiplus::Point(24, 18),
            Gdiplus::Point(25, 19),
            Gdiplus::Point(25, 24),
            Gdiplus::Point(24, 25),
            Gdiplus::Point(15, 25),
            Gdiplus::Point(11, 32),
            Gdiplus::Point(23, 32),
            Gdiplus::Point(24, 33),
            Gdiplus::Point(24, 38),
            Gdiplus::Point(23, 39),
            Gdiplus::Point(8, 39),
            Gdiplus::Point(-18, 85),
            Gdiplus::Point(-29, 85),
            Gdiplus::Point(-14, 39),
            Gdiplus::Point(-11, 11),
            Gdiplus::Point(-18, 11),
            Gdiplus::Point(-26, 10),
            Gdiplus::Point(-29, 9),
            Gdiplus::Point(-42, 8),
            Gdiplus::Point(-55, 7),
            Gdiplus::Point(-64, 5),
            Gdiplus::Point(-81, 29),
            Gdiplus::Point(-88, 29),
            Gdiplus::Point(-79, 2),
        };
    }
    return nullptr;
}
