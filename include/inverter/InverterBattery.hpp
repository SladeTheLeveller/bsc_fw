// Copyright (c) 2024 Tobias Himmler
//
// This software is released under the MIT License.
// https://opensource.org/licenses/MIT

#pragma once

#include <cstdint>
#include "inverter/Inverter.hpp"


namespace nsInverterBattery
{
    class InverterBattery
    {
    public:
        InverterBattery();
        ~InverterBattery();

        void getBatteryVoltage(Inverter &inverter, Inverter::inverterData_s &inverterData);
        void getBatteryCurrent(Inverter &inverter, Inverter::inverterData_s &inverterData);
        int16_t getBatteryTemp(Inverter::inverterData_s &inverterData);

    private:

    };
}