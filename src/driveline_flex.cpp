#include "../include/driveline_flex.h"

DrivelineFlex::DrivelineFlex() {
    m_ks = 0.0;
    m_kd = 0.0;
    m_maxFlex = 0.0;
    m_limitFlex = true;
    m_maxTorque = 0.0; // no coupling until Transmission::update() sets capacity
    m_flexAngle = 0.0;
    m_body1 = nullptr;
    m_body2 = nullptr;
}

DrivelineFlex::~DrivelineFlex() {
    /* void */
}

void DrivelineFlex::apply(atg_scs::SystemState *state) {
    if (m_body1 == nullptr || m_body2 == nullptr) return;

    // A disengaged clutch (capacity 0, e.g. neutral) transmits nothing and
    // holds no wind-up.
    if (m_maxTorque <= 0.0) {
        m_flexAngle = 0.0;
        return;
    }

    const int i1 = m_body1->index;
    const int i2 = m_body2->index;

    const double v1 = (i1 == -1) ? 0.0 : state->v_theta[i1];
    const double v2 = (i2 == -1) ? 0.0 : state->v_theta[i2];
    const double rel_v = v1 - v2;

    // Integrate elastic wind-up. Single-stage solver -> exactly one call per
    // physics step with the full timestep.
    m_flexAngle += rel_v * state->dt;
    if (m_limitFlex && m_maxFlex > 0.0) {
        if (m_flexAngle > m_maxFlex) m_flexAngle = m_maxFlex;
        else if (m_flexAngle < -m_maxFlex) m_flexAngle = -m_maxFlex;
    }

    double torque = m_ks * m_flexAngle + m_kd * rel_v;

    // Saturate at clutch capacity (slip). Anti-windup: keep the stored angle
    // consistent with the torque actually applied so it can't run away.
    if (torque > m_maxTorque) {
        torque = m_maxTorque;
        if (m_ks > 0.0) m_flexAngle = (torque - m_kd * rel_v) / m_ks;
    }
    else if (torque < -m_maxTorque) {
        torque = -m_maxTorque;
        if (m_ks > 0.0) m_flexAngle = (torque - m_kd * rel_v) / m_ks;
    }

    if (i1 != -1) state->t[i1] -= torque;
    if (i2 != -1) state->t[i2] += torque;
}
