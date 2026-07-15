#include "../scripting/include/compiler.h"

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

TEST(ScriptCompilerTests, CompilesDefaultAssetScript) {
    es_script::Compiler compiler;
    compiler.initialize();

    const bool compiled = compiler.compile("assets/main.mr");
    if (!compiled) {
        std::ifstream errorLog("error_log.log");
        std::stringstream errorText;
        errorText << errorLog.rdbuf();
        ADD_FAILURE() << errorText.str();
    }

    compiler.destroy();
}

TEST(ScriptCompilerTests, CompilesFlexVehicleTransmission) {
    // Verifies the backported 1.14 vehicle/transmission flex + brake inputs
    // parse and resolve on the vehicle() / transmission() nodes.
    es_script::Compiler compiler;
    compiler.initialize();

    const bool compiled = compiler.compile("assets/test_flex_engine.mr");
    if (!compiled) {
        std::ifstream errorLog("error_log.log");
        std::stringstream errorText;
        errorText << errorLog.rdbuf();
        ADD_FAILURE() << errorText.str();
    }

    compiler.destroy();
}
