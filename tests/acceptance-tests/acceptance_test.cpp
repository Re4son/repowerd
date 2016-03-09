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

#include "acceptance_test.h"

#include "daemon_config.h"
#include "mock_display_power_control.h"
#include "mock_power_button_event_sink.h"
#include "fake_power_button.h"
#include "fake_timer.h"

#include "src/daemon.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

namespace rt = repowerd::test;

rt::AcceptanceTest::AcceptanceTest()
{
    daemon_thread = std::thread{ [this] { daemon.run(); }};
    daemon.flush();
}

rt::AcceptanceTest::~AcceptanceTest()
{
    daemon.flush();
    daemon.stop();
    daemon_thread.join();
}

void rt::AcceptanceTest::expect_display_turns_off()
{
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_off());
}

void rt::AcceptanceTest::expect_display_turns_on()
{
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_on());
}

void rt::AcceptanceTest::expect_long_press_notification()
{
    EXPECT_CALL(*config.the_mock_power_button_event_sink(), notify_long_press());
}

void rt::AcceptanceTest::expect_no_display_power_change()
{
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_on()).Times(0);
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_off()).Times(0);
}

void rt::AcceptanceTest::verify_expectations()
{
    daemon.flush();
    testing::Mock::VerifyAndClearExpectations(config.the_mock_display_power_control().get());
    testing::Mock::VerifyAndClearExpectations(config.the_mock_power_button_event_sink().get());
}

void rt::AcceptanceTest::advance_time_by(std::chrono::milliseconds advance)
{
    daemon.flush();
    config.the_fake_timer()->advance_by(advance);
    daemon.flush();
}

void rt::AcceptanceTest::press_power_button()
{
    config.the_fake_power_button()->press();
}

void rt::AcceptanceTest::release_power_button()
{
    config.the_fake_power_button()->release();
}

void rt::AcceptanceTest::turn_off_display()
{
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_off());
    press_power_button();
    release_power_button();
    daemon.flush();
    testing::Mock::VerifyAndClearExpectations(config.the_mock_display_power_control().get());
}

void rt::AcceptanceTest::turn_on_display()
{
    EXPECT_CALL(*config.the_mock_display_power_control(), turn_on());
    press_power_button();
    release_power_button();
    daemon.flush();
    testing::Mock::VerifyAndClearExpectations(config.the_mock_display_power_control().get());
}
