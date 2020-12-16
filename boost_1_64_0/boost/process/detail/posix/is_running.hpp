// Copyright (c) 2106 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_DETAIL_POSIX_IS_RUNNING_HPP
#define BOOST_PROCESS_DETAIL_POSIX_IS_RUNNING_HPP

#include <boost/process/detail/config.hpp>
#include <boost/process/detail/posix/child_handle.hpp>
#include <system_error>
#include <sys/wait.h>

namespace boost { namespace process { namespace detail { namespace posix {

// Use the "stopped" state (WIFSTOPPED) to indicate "not terminated".
// This bit arrangement of status codes is not guaranteed by POSIX, but (according to comments in
// the glibc <bits/waitstatus.h> header) is the same across systems in practice.
constexpr int still_active = 0x017f;
static_assert(WIFSTOPPED(still_active), "Expected still_active to indicate WIFSTOPPED");
static_assert(!WIFEXITED(still_active), "Expected still_active to not indicate WIFEXITED");
static_assert(!WIFSIGNALED(still_active), "Expected still_active to not indicate WIFSIGNALED");
static_assert(!WIFCONTINUED(still_active), "Expected still_active to not indicate WIFCONTINUED");

inline bool is_running(int code)
{
    return !WIFEXITED(code) && !WIFSIGNALED(code);
}

inline bool is_running(const child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    int status;
    auto ret = ::waitpid(p.pid, &status, WNOHANG);

    if (ret == -1)
    {
        if (errno != ECHILD) //because it no child is running, than this one isn't either, obviously.
            ec = ::boost::process::detail::get_last_error();
        return false;
    }
    else if (ret == 0)
        return true;
    else
    {
        ec.clear();

        if (!is_running(status))
            exit_code = status;

        return false;
    }
}

inline bool is_running(const child_handle &p, int & exit_code)
{
    std::error_code ec;
    bool b = is_running(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "waitpid(2) failed in is_running");
    return b;
}

inline int eval_exit_status(int code)
{
    if (WIFEXITED(code))
    {
        return WEXITSTATUS(code);
    }
    else if (WIFSIGNALED(code))
    {
        return WTERMSIG(code);
    }
    else
    {
        return code;
    }
}

}}}}

#endif

/* is_running.hpp
+rrqnSXMHoS5QMKsk9hV8/dl885ht3NuEL9Z+OHYXMu5tE01l3BWEs7FEk61xBZh94vcVXJvZJj593r9SgtnZk/JNe8rS3GfImW6jX8IeRP5nZ2ucbmqtZSbaD81bi9PBvt4JHmnR02yGpWrk+7yxPnO9kbWS4M5T5LEdXHi7cTV/R3Kzst/SNrPoCX91OA3g6QjlPeB4jo+7BvhOty1PGtdJ3kp5+6P22Vy7pjEZpzbWf9oFWHece4Vu8/81cPKNOU5YKh2a7DbJnbP+78gz5zv5Kmh/UDbS13Cfd/COo2ZGQc99l7MH0i9c420SIu9yb8XqrC/cEzrGEatV9mq9iG3VbH9Pe2qOOvoGYEqWtM4hzgtk+sY52+ldTn5G7q3yd1gPr2g+bQrScMI3F0lwTCG4faqhLE54ZOazvRTz2v6zX63bQN2Rb57rUu94XXUFyxv8b7cd0WE10jCm+VfGfZ8KSgM5Tx28k7QQeyy/Uuws6+jqZbEbjl2V0u+H/I39DvD03cTtSvDrlDCO9Z/qobXKJhn8gIUsmuA3fNity3hq5rOsh+sv1I1rV3lvptSdREzps71Do7qXmUi5T6yvsnx3s+k6z3eWOYP3ksuvOsNnKMO52ghcc5PvJg4a58JP9rZNR7NsJksNm0Th5arS/V9RctVTylXiXqf2OevaW2KCYQ1j7A+kLAe9u9IcNYJpVIpmG+IZroOQPhzSeIzgTBaSb5M9S8jDFN/UCdk5xaV6reZCattBrba1r3Y1DemjOZNzyU/Na3bcb9dwt6XkETYdvsfLwna/heqc2ZKvvep2t8aH7Ulqq4nKYYRLjHveo8pV+eMY/+Ry7zdo072OOudyHbxRvqMbCX5077mcVa32KmxJ1h3xF7i6VGtuefa6pf7pA38F+4R+xqE3iRMetPahL9H9JHjFEnfhkA9J+lb7L+d9Lm0pUsYb7ZTP/qd1kjycBdjYy42z7oYSd+WmL6eKZ6nvOO8GdFDrWox64LfocQx4lvchP2PDlJGTPzmdZT4Bt9Fid8wSX/vxEnO51lEm8vWQ3YeaB0Slgf3yfOgidVKzzFV8mBgVBL19XW82T5k+Zif8QxzxXzMw2vEnJzmVnNvLbkn7iLsAxKHVf4nw+qFmayMwngwjcOr+u3oTw3dC+STtl3UFv9ja/axRle/rXoT764a7ay68b2tifHfid8o9ftuktQjpYXFuab+jZL8yfK8a2W717HEcQX+b5Vz7PenhN+TpjKM1+tUJnmxlhwOrwcj6gTJ/3WH+Em4V/s3JjjDNVls8vjYtsH57Omax5/K8UveRpZPdoI+G7d7rGCe5hPsUVLu5vNdTrkze1fTHplttymkaF2oz9Cw+rAU96ckjNcSvjf1v/0Obznacga0CLY5dWJ2WsS7pr7DmXOUu3+mtw2/f65sa98/m4hDjMThMv+DzvdwR7vd5rA6prQ4Ky+fdg95xJl1VZpIHmdXe4uWnRXRWYxvetS6OzaGOfeTPClh71NbqsZYtXmrKq7irHdnBKssU2bekvJ9kieN2T8pYWWme1TwnaeVJxD/FsTtEzn3/f5Xw8p2YChBQWFBdq55xzldzt+RWzhJrmEcfgdJ2k/2Twurd8lGCvB4eh/0Wsl38CyxbeTvLecJXe/pWXOyJudGtldxzc23kV51CecA9cgWCeelhG+45vqOZWz1LUvCWkVY9vNE9/DXtAyX8nCppx6zCo2N9o2Ytf9aY6PtQgkalsnvvAJjFxf8JvWE8t6SfLrKO5MZtqIz3+WbPGM94yQdUwjvbfH3qP+98OeefDyGwo6X516s+BmJn2Mk7cX+FeF+iLjtJ8XhZyx+jhM/Bf7lke80+jU=
*/