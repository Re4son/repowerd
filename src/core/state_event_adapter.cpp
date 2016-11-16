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

#include "state_event_adapter.h"

repowerd::StateEventAdapter::StateEventAdapter(StateMachine& state_machine)
    : state_machine(state_machine)
{
}

void repowerd::StateEventAdapter::handle_enable_inactivity_timeout(
    std::string const& request_id)
{
    inactivity_timeout_disallowances.erase(request_id);

    if (inactivity_timeout_disallowances.empty())
        state_machine.handle_enable_inactivity_timeout();
}

void repowerd::StateEventAdapter::handle_disable_inactivity_timeout(
    std::string const& request_id)
{
    inactivity_timeout_disallowances.insert(request_id);

    state_machine.handle_disable_inactivity_timeout();
}
