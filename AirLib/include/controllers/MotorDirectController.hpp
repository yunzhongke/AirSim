// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License.

#ifndef msr_airlib_MotorDirectController_hpp
#define msr_airlib_MotorDirectController_hpp

#include <exception>
#include "controllers/ControllerBase.hpp"
#include "common/common_utils/Utils.hpp"
#include "MotorDirectControllerParams.hpp"

namespace msr { namespace airlib {

class MotorDirectController : public ControllerBase {
private:
    vector<real_T> motor_control_signals_;
    MotorDirectControllerParams params_;

public:
    MotorDirectController(const MotorDirectControllerParams& params = MotorDirectControllerParams())
    {
        initialize(params);
    }
    void initialize(const MotorDirectControllerParams& params)
    {
        params_ = params;
        motor_control_signals_.resize(params_.rotor_count);
    }


    //*** Start ControllerBase implementation ****//
    virtual void reset() override
    {
        ControllerBase::reset();

        motor_control_signals_.assign(params_.rotor_count, 0);
    }

    virtual void update() override
    {
        ControllerBase::update();

        //nothing to update in direct motor control
    }

    virtual real_T getVertexControlSignal(unsigned int rotor_index) override
    {
        return motor_control_signals_.at(rotor_index);
    }
    virtual size_t getVertexCount() override
    {
        return 4;
    }
    //*** End ControllerBase implementation ****//

    void setRotorControlSignal(unsigned int rotor_index, real_T value)
    {
        motor_control_signals_[rotor_index] = value;
    }

    virtual ~MotorDirectController() = default;

};

}} //namespace
#endif
