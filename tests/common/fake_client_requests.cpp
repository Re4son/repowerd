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

#include "fake_client_requests.h"

namespace rt = repowerd::test;

rt::FakeClientRequests::FakeClientRequests()
    : enable_inactivity_timeout_handler{[]{}},
      disable_inactivity_timeout_handler{[]{}},
      set_normal_brightness_value_handler{[](float){}}
{
}

repowerd::HandlerRegistration rt::FakeClientRequests::register_enable_inactivity_timeout_handler(
    EnableInactivityTimeoutHandler const& handler)
{
    mock.register_enable_inactivity_timeout_handler(handler);
    enable_inactivity_timeout_handler = handler;
    return HandlerRegistration{
        [this]
        {
            mock.unregister_enable_inactivity_timeout_handler();
            enable_inactivity_timeout_handler = []{};
        }};
}

repowerd::HandlerRegistration rt::FakeClientRequests::register_disable_inactivity_timeout_handler(
    DisableInactivityTimeoutHandler const& handler)
{
    mock.register_disable_inactivity_timeout_handler(handler);
    disable_inactivity_timeout_handler = handler;
    return HandlerRegistration{
        [this]
        {
            mock.unregister_disable_inactivity_timeout_handler();
            disable_inactivity_timeout_handler = []{};
        }};
}

repowerd::HandlerRegistration rt::FakeClientRequests::register_set_normal_brightness_value_handler(
    SetNormalBrightnessValueHandler const& handler)
{
    mock.register_set_normal_brightness_value_handler(handler);
    set_normal_brightness_value_handler = handler;
    return HandlerRegistration{
        [this]
        {
            mock.unregister_set_normal_brightness_value_handler();
            set_normal_brightness_value_handler = [](float){};
        }};
}


void rt::FakeClientRequests::emit_enable_inactivity_timeout()
{
    enable_inactivity_timeout_handler();
}

void rt::FakeClientRequests::emit_disable_inactivity_timeout()
{
    disable_inactivity_timeout_handler();
}

void rt::FakeClientRequests::emit_set_normal_brightness_value(float f)
{
    set_normal_brightness_value_handler(f);
}
