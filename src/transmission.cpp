#include "../include/transmission.h"

#include "../include/units.h"

#include <cmath>

Transmission::Transmission() {
    m_gear = -1;
    m_newGear = -1;
    m_gearCount = 0;
    m_gearRatios = nullptr;
    m_maxClutchTorque = units::torque(1000.0, units::ft_lb);
    m_rotatingMass = nullptr;
    m_vehicle = nullptr;
    m_clutchPressure = 0.0;
    m_flexActive = false;
    m_simulateFlex = false;
    m_clutchStiffness = 0.0;
    m_clutchDamping = 0.0;
    m_maxClutchFlex = 0.0;
    m_limitClutchFlex = true;
}

Transmission::~Transmission() {
    if (m_gearRatios != nullptr) {
        delete[] m_gearRatios;
    }

    m_gearRatios = nullptr;
}

void Transmission::initialize(const Parameters &params) {
    m_gearCount = params.GearCount;
    m_maxClutchTorque = params.MaxClutchTorque;
    m_gearRatios = new double[params.GearCount];
    memcpy(m_gearRatios, params.GearRatios, sizeof(double) * m_gearCount);

    m_simulateFlex = params.SimulateFlex;
    m_clutchStiffness = params.ClutchStiffness;
    m_clutchDamping = params.ClutchDamping;
    m_maxClutchFlex = params.MaxClutchFlex;
    m_limitClutchFlex = params.LimitClutchFlex;
}

void Transmission::update(double dt) {
    const double capacity = (m_gear == -1)
        ? 0.0
        : m_maxClutchTorque * m_clutchPressure;

    if (m_flexActive) {
        m_flex.m_maxTorque = capacity;
    }
    else {
        m_clutchConstraint.m_minTorque = -capacity;
        m_clutchConstraint.m_maxTorque = capacity;
    }
}

void Transmission::addToSystem(
    atg_scs::RigidBodySystem *system,
    atg_scs::RigidBody *rotatingMass,
    Vehicle *vehicle,
    Engine *engine)
{
    m_rotatingMass = rotatingMass;
    m_vehicle = vehicle;

    atg_scs::RigidBody *crankshaft = &engine->getOutputCrankshaft()->m_body;

    // Combine clutch flex (transmission) and driveline flex (vehicle) as two
    // torsional springs in series; a disabled or unspecified side is rigid and
    // simply skipped. If neither is active, fall back to the rigid clutch lock.
    double invK = 0.0, invC = 0.0, maxFlex = 0.0;
    bool limit = true, active = false;

    if (m_simulateFlex && m_clutchStiffness > 0.0 && m_clutchDamping > 0.0) {
        invK += 1.0 / m_clutchStiffness;
        invC += 1.0 / m_clutchDamping;
        maxFlex += m_maxClutchFlex;
        limit = limit && m_limitClutchFlex;
        active = true;
    }

    if (vehicle->getSimulateFlex()
            && vehicle->getStiffness() > 0.0
            && vehicle->getDamping() > 0.0) {
        invK += 1.0 / vehicle->getStiffness();
        invC += 1.0 / vehicle->getDamping();
        maxFlex += vehicle->getMaxFlex();
        limit = limit && vehicle->getLimitFlex();
        active = true;
    }

    if (active) {
        m_flex.m_ks = 1.0 / invK;
        m_flex.m_kd = 1.0 / invC;
        m_flex.m_maxFlex = maxFlex;
        m_flex.m_limitFlex = limit;
        m_flex.setBody1(crankshaft);
        m_flex.setBody2(m_rotatingMass);
        m_flex.reset();
        system->addForceGenerator(&m_flex);
        m_flexActive = true;
    }
    else {
        m_clutchConstraint.setBody1(crankshaft);
        m_clutchConstraint.setBody2(m_rotatingMass);
        system->addConstraint(&m_clutchConstraint);
        m_flexActive = false;
    }
}

void Transmission::changeGear(int newGear) {
    if (newGear < -1 || newGear >= m_gearCount) return;
    else if (newGear != -1) {
        const double m_car = m_vehicle->getMass();
        const double gear_ratio = m_gearRatios[newGear];
        const double diff_ratio = m_vehicle->getDiffRatio();
        const double tire_radius = m_vehicle->getTireRadius();
        const double f = tire_radius / (diff_ratio * gear_ratio);

        const double new_I = m_car * f * f;
        const double E_r =
            0.5 * m_rotatingMass->I * m_rotatingMass->v_theta * m_rotatingMass->v_theta;
        const double new_v_theta = m_rotatingMass->v_theta < 0
            ? -std::sqrt(E_r * 2 / new_I)
            : std::sqrt(E_r * 2 / new_I);

        m_rotatingMass->I = new_I;
        m_rotatingMass->p_x = m_rotatingMass->p_y = 0;
        m_rotatingMass->m = m_car;
        m_rotatingMass->v_theta = new_v_theta;
    }

    m_flex.reset();
    m_gear = newGear;
}
