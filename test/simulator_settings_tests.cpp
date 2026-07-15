#include "../include/engine.h"
#include "../include/piston_engine_simulator.h"
#include "../include/simulator.h"

#include <gtest/gtest.h>

#include <memory>

TEST(SimulatorSettingsTests, EngineCreateSimulatorCopiesPhysicsPerformanceSettings) {
    Engine::Parameters params;
    params.name = "settings-test";
    params.cylinderBanks = 0;
    params.cylinderCount = 0;
    params.crankshaftCount = 0;
    params.exhaustSystemCount = 0;
    params.intakeCount = 0;
    params.throttle = nullptr;
    params.initialSimulationFrequency = 10000;
    params.initialHighFrequencyGain = 0.01;
    params.initialNoise = 1.0;
    params.initialJitter = 0.5;
    params.initialMaxSleSolverSteps = 4;
    params.initialFluidSimulationSteps = 6;

    Engine engine;
    engine.initialize(params);

    std::unique_ptr<Simulator> simulator(engine.createSimulator(nullptr, nullptr));

    ASSERT_NE(simulator, nullptr);
    EXPECT_EQ(simulator->getMaxSleSolverSteps(), 4);

    auto *pistonSimulator = dynamic_cast<PistonEngineSimulator *>(simulator.get());
    ASSERT_NE(pistonSimulator, nullptr);
    EXPECT_EQ(pistonSimulator->getFluidSimulationSteps(), 6);

    simulator->releaseSimulation();
    engine.destroy();
}

TEST(SimulatorSettingsTests, EngineStoresInitialAudioAndThermalSettings) {
    Engine::Parameters params;
    params.name = "audio-thermal-test";
    params.cylinderBanks = 0;
    params.cylinderCount = 0;
    params.crankshaftCount = 0;
    params.exhaustSystemCount = 0;
    params.intakeCount = 0;
    params.throttle = nullptr;
    params.initialSimulationFrequency = 10000;
    params.initialHighFrequencyGain = 0.01;
    params.initialNoise = 1.0;
    params.initialJitter = 0.5;
    params.initialConvolution = 0.25;
    params.initialHeatTransferCoefficient = 250.0;
    params.initialBlockTemperature = units::celcius(80.0);

    Engine engine;
    engine.initialize(params);

    EXPECT_DOUBLE_EQ(engine.getInitialConvolution(), 0.25);
    EXPECT_DOUBLE_EQ(engine.getInitialHeatTransferCoefficient(), 250.0);
    EXPECT_DOUBLE_EQ(engine.getInitialBlockTemperature(), units::celcius(80.0));

    engine.destroy();
}
