#ifndef ATG_ENGINE_SIM_VEHICLE_H
#define ATG_ENGINE_SIM_VEHICLE_H

#include "scs.h"

class Vehicle {
    public:
        struct Parameters {
            double mass;
            double dragCoefficient;
            double crossSectionArea;
            double diffRatio;
            double tireRadius;
            double rollingResistance;

            // Driveline flex (1.14) + brake capacity.
            bool simulateFlex = false;
            double stiffness = 0.0;
            double damping = 0.0;
            double maxFlex = 0.0;
            bool limitFlex = true;
            double maxBrakeForce = 0.0;
        };

    public:
        Vehicle();
        ~Vehicle();

        void initialize(const Parameters &params);
        void update(double dt);
        void addToSystem(atg_scs::RigidBodySystem *system, atg_scs::RigidBody *rotatingMass);
        inline double getMass() const { return m_mass; }
        inline double getRollingResistance() const { return m_rollingResistance; }
        inline double getDragCoefficient() const { return m_dragCoefficient; }
        inline double getCrossSectionArea() const { return m_crossSectionArea; }
        inline double getDiffRatio() const { return m_diffRatio; }
        inline double getTireRadius() const { return m_tireRadius; }
        inline bool getSimulateFlex() const { return m_simulateFlex; }
        inline double getStiffness() const { return m_stiffness; }
        inline double getDamping() const { return m_damping; }
        inline double getMaxFlex() const { return m_maxFlex; }
        inline bool getLimitFlex() const { return m_limitFlex; }
        inline double getMaxBrakeForce() const { return m_maxBrakeForce; }
        double getSpeed() const;
        inline double getTravelledDistance() const { return m_travelledDistance; }
        inline void resetTravelledDistance() { m_travelledDistance = 0; }
        double linearForceToVirtualTorque(double force) const;

    protected:
        atg_scs::RigidBody *m_rotatingMass;

        double m_mass;
        double m_dragCoefficient;
        double m_crossSectionArea;
        double m_diffRatio;
        double m_tireRadius;
        double m_travelledDistance;
        double m_rollingResistance;

        bool m_simulateFlex;
        double m_stiffness;
        double m_damping;
        double m_maxFlex;
        bool m_limitFlex;
        double m_maxBrakeForce;
};

#endif /* ATG_ENGINE_SIM_VEHICLE_H */
