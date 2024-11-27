#include "Globals.hpp"

// Initialisation des rails
Rail rail1("rail1", {100.0, 300}, {300, 300});
Rail rail2("rail2", {300, 300}, {500, 200});
Rail rail3("rail3", {300, 300}, {500, 400});
Rail rail4("rail4", {500, 200}, {700, 200});
Rail rail5("rail5", {500, 400}, {700, 400});
Rail rail6("rail6", {700, 200}, {700, 400});
Rail rail7("rail7", {700, 200}, {700, 100});
Rail rail8("rail8", {700, 400}, {700, 500});
Rail rail9("rail9", {700, 100}, {300, 100});
Rail rail10("rail10", {300, 100}, {100, 300});

// Initialisation des switches
Switch railSwitch1("railSwitch1", {300, 300});
Switch railSwitch2("railSwitch2", {700, 200});
Switch railSwitch3("railSwitch3", {700, 400});
