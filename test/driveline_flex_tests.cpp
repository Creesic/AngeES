#include "../include/driveline_flex.h"

#include "../include/scs.h"

#include <gtest/gtest.h>

#include <cmath>

// Drives the torsional flex generator in a real 2-body solver system: a fast
// "crankshaft" coupled to a heavier "wheels" body at rest. Verifies the flex
// stays finite/bounded over 5 s of stepping (stable by construction: torque is
// capacity-limited) and actually transmits torque (the wheels spin up).
TEST(DrivelineFlexTests, CouplesStablyAndStaysFinite) {
    atg_scs::GenericRigidBodySystem system;
    system.initialize(
        new atg_scs::GaussianEliminationSleSolver,
        new atg_scs::NsvOdeSolver);

    atg_scs::RigidBody crank, wheels;
    crank.reset();
    wheels.reset();
    crank.m = 1.0;  crank.I = 0.2;   crank.v_theta = 300.0; // spinning fast
    wheels.m = 1.0; wheels.I = 2.0;  wheels.v_theta = 0.0;   // at rest

    system.addRigidBody(&crank);
    system.addRigidBody(&wheels);

    DrivelineFlex flex;
    flex.m_ks = 5000.0;
    flex.m_kd = 25.0;
    flex.m_maxFlex = 0.25;
    flex.m_limitFlex = true;
    flex.m_maxTorque = 400.0; // finite clutch capacity -> cannot inject runaway energy
    flex.setBody1(&crank);
    flex.setBody2(&wheels);
    system.addForceGenerator(&flex);

    for (int i = 0; i < 50000; ++i) { // 5 s at 1e-4 s steps
        system.process(1e-4, 1);
        ASSERT_TRUE(std::isfinite(crank.v_theta)) << "step " << i;
        ASSERT_TRUE(std::isfinite(wheels.v_theta)) << "step " << i;
        ASSERT_LT(std::fabs(crank.v_theta), 1e4) << "step " << i;
        ASSERT_LT(std::fabs(wheels.v_theta), 1e4) << "step " << i;
    }

    // The spring must actually transmit torque: the wheels spin up from rest.
    EXPECT_GT(wheels.v_theta, 1.0);
}

// With zero capacity (disengaged clutch / neutral) the flex transmits nothing
// and the bodies stay independent.
TEST(DrivelineFlexTests, DisengagedTransmitsNoTorque) {
    atg_scs::GenericRigidBodySystem system;
    system.initialize(
        new atg_scs::GaussianEliminationSleSolver,
        new atg_scs::NsvOdeSolver);

    atg_scs::RigidBody crank, wheels;
    crank.reset();
    wheels.reset();
    crank.m = 1.0;  crank.I = 0.2;   crank.v_theta = 300.0;
    wheels.m = 1.0; wheels.I = 2.0;  wheels.v_theta = 0.0;

    system.addRigidBody(&crank);
    system.addRigidBody(&wheels);

    DrivelineFlex flex;
    flex.m_ks = 5000.0;
    flex.m_kd = 25.0;
    flex.m_maxFlex = 0.25;
    flex.m_limitFlex = true;
    flex.m_maxTorque = 0.0; // disengaged
    flex.setBody1(&crank);
    flex.setBody2(&wheels);
    system.addForceGenerator(&flex);

    for (int i = 0; i < 10000; ++i) {
        system.process(1e-4, 1);
    }

    EXPECT_NEAR(wheels.v_theta, 0.0, 1e-6);
    EXPECT_NEAR(crank.v_theta, 300.0, 1e-6);
}
