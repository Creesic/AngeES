#ifndef ATG_ENGINE_SIM_DRIVELINE_FLEX_H
#define ATG_ENGINE_SIM_DRIVELINE_FLEX_H

#include "scs.h"

// Torsional spring-damper coupling between two rotating bodies, used to model
// driveline / clutch "flex" (elastic wind-up) as found in the 1.14 engines.
//
// When flex is enabled this replaces the rigid clutch velocity-lock: the two
// bodies are joined by a torsional spring (stiffness m_ks, damping m_kd) whose
// transmitted torque saturates at the clutch capacity m_maxTorque -- so the
// driveline winds up elastically and then slips once capacity is exceeded.
//
// It is a ForceGenerator, so apply() is called once per physics step (the
// engine uses the single-stage symplectic NsvOdeSolver, dt == full timestep),
// which makes the wind-up integration below correct and stable.
class DrivelineFlex : public atg_scs::ForceGenerator {
    public:
        DrivelineFlex();
        virtual ~DrivelineFlex();

        void setBody1(atg_scs::RigidBody *body) { m_body1 = body; }
        void setBody2(atg_scs::RigidBody *body) { m_body2 = body; }
        void reset() { m_flexAngle = 0.0; }

        virtual void apply(atg_scs::SystemState *state);

        double m_ks;         // torsional stiffness [Nm/rad]
        double m_kd;         // torsional damping   [Nm/(rad/s)]
        double m_maxFlex;    // wind-up angle limit [rad]
        bool m_limitFlex;
        double m_maxTorque;  // clutch capacity [Nm]; updated per frame

    protected:
        double m_flexAngle;  // integrated wind-up state [rad]
        atg_scs::RigidBody *m_body1;
        atg_scs::RigidBody *m_body2;
};

#endif /* ATG_ENGINE_SIM_DRIVELINE_FLEX_H */
