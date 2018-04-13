/*
 * Copyright © 2018 Gemian
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
 * Authored by: Adam Boardman <adamboardman@gmail.com>
 */

#pragma once

#include "src/core/exec.h"

#include <string>
#include <vector>
#include <mutex>

namespace repowerd
{
    namespace test
    {

        class FakeExec : public Exec
        {
        public:
            FakeExec();

            int exec(char const* string) override;

            bool contains_line(std::vector<std::string> const& words);

        private:
            bool const log_to_console;
            std::mutex contents_mutex;
            std::vector<std::string> contents;
        };

    }
}
