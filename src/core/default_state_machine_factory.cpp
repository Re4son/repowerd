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

#include "default_state_machine_factory.h"
#include "default_state_machine.h"

#include "src/core/log.h"

char const* const log_tag = "DefaultStateMachineFactory";

repowerd::DefaultStateMachineFactory::DefaultStateMachineFactory(
    DaemonConfig& daemon_config)
    : daemon_config(daemon_config)
{
}

std::shared_ptr<repowerd::StateMachine>
repowerd::DefaultStateMachineFactory::create_state_machine(std::string const& name)
{
    daemon_config.the_log()->log(log_tag, "create_state_machine - DefaultStateMachine - %s", name.c_str());

    return std::make_shared<DefaultStateMachine>(daemon_config, name);
}
