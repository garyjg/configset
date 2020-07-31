// -*- mode: C++; c-basic-offset: 4; -*-

#include <iostream>
#include <string>
#include <sstream>

#include "ConfigItem.h"

class TestConfigSet : public ConfigSet
{
public:
    TestConfigSet() :
        number(this, "number", 1),
        wavelength(this, "wavelength", 3.14),
        callsign(this, "callsign", "kbco"),
	enabled(this, "enabled", true)
    {}

    ConfigItemT<int> number;
    ConfigItemT<float> wavelength;
    ConfigItemT<std::string> callsign;
    ConfigItemT<bool> enabled;
};

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

TEST_CASE("ConfigSet stores defaults", "[ConfigSet]")
{
    TestConfigSet cs;

    REQUIRE(cs.number == 1);
    REQUIRE(cs.wavelength == 3.14f);
    REQUIRE(cs.callsign == std::string("kbco"));
    REQUIRE(cs.enabled == true);
}

TEST_CASE("equality tests work both ways", "[ConfigSet]")
{
    TestConfigSet cs;

    REQUIRE(1 == cs.number);
    REQUIRE(3.14f == cs.wavelength);
    REQUIRE(std::string("kbco") == cs.callsign);
    REQUIRE(true == cs.enabled);
}

TEST_CASE("ConfigSet values can change", "[ConfigSet]")
{
    TestConfigSet cs;
    cs.number = 2;
    int three = 3;
    cs.wavelength = three;
    REQUIRE(cs.wavelength == three);
    cs.wavelength = 2.7;
    cs.callsign = "red5";
    REQUIRE(cs.number == 2);
    REQUIRE(cs.wavelength == Approx(2.7));
    REQUIRE(cs.callsign == "red5");

    std::string lv = cs.callsign;
    REQUIRE(lv == "red5");

    cs.enabled = false;
    REQUIRE(cs.enabled == false);
}

TEST_CASE("Config items can be converted to and from string", "[ConfigItem]")
{
    TestConfigSet cs;
    cs.number.setString("2");
    cs.wavelength.setString("2.7");
    cs.callsign.setString("red5");
    REQUIRE(cs.number == 2);
    REQUIRE(cs.wavelength == 2.7f);
    REQUIRE(cs.callsign == "red5");
    REQUIRE(cs.number.getString() == "2");
    REQUIRE(cs.wavelength.getString() == "2.7");
    REQUIRE(cs.callsign.getString() == "red5");
    REQUIRE(cs.enabled.getString() == "true");
    cs.enabled = false;
    REQUIRE(cs.enabled.getString() == "false");
    cs.enabled.setString("true");
    REQUIRE(cs.enabled.getString() == "true");
    cs.enabled.setString("false");
    REQUIRE(cs.enabled.getString() == "false");
    REQUIRE(cs.enabled == false);
}

TEST_CASE("Configs work through base pointer.", "[ConfigItem]")
{
    TestConfigSet cs;
    ConfigItem* cfg;

    cfg = &cs.number;
    cfg->setString("2");
    REQUIRE(cs.number == 2);
    REQUIRE(cfg->getString() == "2");

    cfg = &cs.wavelength;
    cfg->setString("2.7");
    REQUIRE(cs.wavelength == 2.7f);
    REQUIRE(cfg->getString() == "2.7");

    cfg = &cs.callsign;
    cfg->setString("red5");
    REQUIRE(cs.callsign == "red5");
    REQUIRE(cfg->getString() == "red5");

    cfg = &cs.enabled;
    REQUIRE(cfg->getString() == "true");
    cs.enabled = false;
    REQUIRE(cfg->getString() == "false");
    cfg->setString("true");
    REQUIRE(cs.enabled == true);
    REQUIRE(cfg->getString() == "true");
    cfg->setString("false");
    REQUIRE(cfg->getString() == "false");
    REQUIRE(cs.enabled == false);
}


TEST_CASE("Config items can be tested easily", "[ConfigItem]")
{
    TestConfigSet cs;
    REQUIRE(cs.number < 2);
    REQUIRE(bool(cs.number));
    cs.number = 0;
    REQUIRE(!cs.number);
    REQUIRE(cs.wavelength*2 == 6.28f);
    REQUIRE(cs.wavelength > 1);
    REQUIRE(cs.wavelength);
    cs.wavelength = 0;
    REQUIRE(!cs.wavelength);

    REQUIRE(cs.enabled);
    cs.enabled = false;
    REQUIRE(!cs.enabled);

    std::ostringstream out;
    out << static_cast<const ConfigItemT<int> >(cs.number);
    REQUIRE(out.str() == "0");
}


