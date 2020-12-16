// Copyright (c) 2106 Klemens D. Morgenstern
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_WINDOWS_IS_RUNNING_HPP
#define BOOST_PROCESS_WINDOWS_IS_RUNNING_HPP

#include <boost/process/detail/config.hpp>
#include <system_error>
#include <cstdlib>
#include <boost/winapi/process.hpp>

namespace boost { namespace process { namespace detail { namespace windows {

constexpr static ::boost::winapi::DWORD_ still_active = 259;


struct child_handle;

inline bool is_running(const child_handle &p, int & exit_code, std::error_code &ec) noexcept
{
    ::boost::winapi::DWORD_ code;
    //single value, not needed in the winapi.
    if (!::boost::winapi::GetExitCodeProcess(p.process_handle(), &code))
        ec = ::boost::process::detail::get_last_error();
    else
        ec.clear();

    if (code == still_active)
        return true;
    else
    {
        exit_code = code;
        return false;
    }
}

inline bool is_running(const child_handle &p, int & exit_code)
{
    std::error_code ec;
    bool b = is_running(p, exit_code, ec);
    boost::process::detail::throw_error(ec, "GetExitCodeProcess() failed in is_running");
    return b;
}

inline bool is_running(int code)
{
    return code == still_active;
}

inline int eval_exit_status(int in ) {return in;}

}}}}

#endif

/* is_running.hpp
L+p2QZrJ8gfL+M4wvo8kX7xXORlf4brUq1mXW/OO0k6I/p7LMRnPG9bBlm608B5P6/P+ug37HCnTdnyHgTRdD2kkgeYSzG23NJF8pfT6TJC6yRYj/Wm9VspjJfWgq2emZ2WmTT5dP6yeNfn13y7bRt657ivLs4/lWSfLM9yrKstjaqNKT3OEzHcF3S7/OeluZN1oqenMQ9cOSQtkPmR6ar3cslfhbfg3mJbLN0tlvAFSPo8wDrZ33b4LDScOy04yt7dSVZZ5nbNbL2MlhnF+7/OazH81r5OqDheESF3k46+6bRVdLrMtATZ/ezfLIrX8KxjeV/oFeX3u6VI/nM366fm9KGX9PlN+US+3uW7sYFxbZF4GeoWZ65r5m5KqLePtku9xryDyGdtqwojUDGeeveT5RvK09rrpnC+mp+oZRWQxfR+1QOahgzWDlhh/UG3aLTC163S/qn+zZXxtvOpaPfntww+WJp7VLUM9K1me9+zGu4YteG/P+ObrUWd9lHlZy7x8IMMmelUsslzpyQmyYMa8rJR85dmGFvG7oqn6O1jVpYyvenrwK7DRtur8Jue61by9J9CylpSP+mbsARlPZy8PpmfkSx86NCsx27zNLu9IPpY6hHb55lla6+OGsR3M8GSc0nb3ORlnfa+fKE+9b5X2wo3v9BrLlpQYL22UuGsbLi2dzVLm9TzpR2S87b1uM17jGDK4Me+U631mGVlHVZhvU3lQCqo8ZFwHGddyGdcIr3pFypkZcZaz3gbXS751HhkcAypKmnEMMG/jVs8Nun7J92VN3xYZLmU31BLKF9PM+1epg4VtLEmes+yxOpKHNL1t28nTPTDGyr19H2lPgt8p5MwqbOv2DeMbEJJnM3nyHHlKTqpRmGcx3UZb3xn6WBiIc+VcwFfGEabGcYZxvOUYh+/k/v4c4Vy/b1tR5Qv3Vfmsk0f7e9v4fO3r/t4ebr9bq+evBcOscgxTYnKubq/XJU+ckWd5cXkmk+cdRx6fiW0K86xVeS7R3dyx7lS7Sp+b4jlimbStZ8Ryujfge8T7Du8iHPnziS3ENoLfQzJ+/q1ihenbDyvDWB6idQjzzc7lBuHo7hXo9C2CfJJ/dZhzftao4d/W4zHMDzL+fT4YVTtvMXfRZiX7G91m5eZ2hW1RNmhqUWnrjLQmhWnLjLSHCtNeMtIaF6ZNMNIaFaZlGWkNC9MGGWm6rcz2RlqDwrSmRlr9wrQ6RlpUYVolnVZfL0ewkaaXw9NI08txuq1O0/N8wcin5/k7Z1p6Bq2tpkh7jsxLW9d2FlX7SnK+bbSddzNApY1kf6raSOSclTTjnJW8ci4aaS/azt5q/d1cOVeU4TfrNhaN8zfyyn41Q4aXfa3kva7T9H5W2uLqKcvDOWZ5Z3eC6t4a6ux+xqXbu6PRbW6juJWqaLsJb/XbpqUcEyM7F7bBzvE9MVNa7NJt3upzQmMf2VbyP8pXASq6a8eL8bl8N9LlvCEEq0me6bToVkZfi8hw8m2t3np8RrpVH8Otpu+Sh+Em6V/PXbtfelhffU6aoafXWPqtZ2p2876eA4LRvmMdybPJ8pilhP4OJdcvelnK4P2SZ7PlcebAOK5wQmI6X3tb8jTT52uZ0h1macD+z4/+OwOMdpa5gpT9Cr/rlX+vde6TkPS7avPWM1DGLx/dN9qXk7ql16dr28x6Hen25Shr0lVZq7zOOp9haovsn29zzH2bUcW3/eW+baji29Ry3+ZVcW2FFd9G2WvzHOlXvq7jtbNLfpM3H6ra9WBez1vFtQn272uzy33ba8W3aea+Tbbi285y35Za8W2RuW/brfi2vNy3IVZ8m2Pu214rrm26f77tNfdtvhU=
*/