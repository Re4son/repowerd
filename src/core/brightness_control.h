/*
 * Copyright © 2016 Canonical Ltd.
 *
 * This program is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 3,
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authored by: Alexandros Frantzis <alexandros.frantzis@canonical.com>
 */

#pragma once

#include "handler_registration.h"

namespace repowerd
{

class BrightnessControl
{
public:
    virtual ~BrightnessControl() = default;

    virtual void disable_autobrightness() = 0;
    virtual void enable_autobrightness() = 0;
    virtual void set_dim_brightness() = 0;
    virtual void set_normal_brightness() = 0;
    virtual void set_normal_brightness_value(double) = 0;
    virtual void set_off_brightness() = 0;
    virtual double get_normal_brightness_value() = 0;

protected:
    BrightnessControl() = default;
    BrightnessControl (BrightnessControl const&) = default;
    BrightnessControl& operator=(BrightnessControl const&) = default;
};

}
