// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SHELL_PATH_HPP
#define BOOST_PROCESS_POSIX_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path shell_path()
{
    return "/bin/sh";
}

inline boost::filesystem::path shell_path(std::error_code &ec)
{
    ec.clear();
    return "/bin/sh";
}

}}}}

#endif

/* shell_path.hpp
jixX/1dz9nx/C+i7lL25YeOoAa0Sj3nno0Hxmd7KOXt/1TE+f7U5e7Imp/meJH91bcZ4ZJ7efMdRMVaHLWBd2Ao2h61ha9gGZsC2sBtsB3vA9rAfzICZsAOcCDvBQtgZngW7wMWwK5SxSF79BtNvwzKYieTrN3R7HQvUHY6HJ8Ii2AMuhKfClXAAvB4OgrfDwfBOOAQ+CIfCR+DpcBscDl+GI+HbcDT8EY6FPp1f1xhOgC3gRJgBJ8F+cDIcB6fCfDgNzoCFcC6cAefBYngWLIXnwplwKZwD74InwkfgPPgYnA+fgefA1+AS+AU8F1rkyXkwGvaG8TAbNoI5sCnsDzvDk+EJ8AI4WMf+jIQXw2x4CSyGl8Gl8HK4Eq6At+gYoDVwFXwQroRl8Gr4NLwWboE3wZfhLfAreCvcD2+HHh3bEw3vhsk6tqcxvA8eBx+A3eFDsC9cD0+BG+Bo+AicAmUsGVwDL4S94Y2wDK6BT8B74JPwQfgU3Ag3w83wafgGfAZ+ALfoWDTLo+9t+p5bBush3HPy+xa76vAnmAZ/hq3hQdgONqUcd4IW7A98cBSMgpNhFTgNxsKz4dFwifo7D8bBZTAe3ggT4BqYCNfDJLgRpsAyWBtuhXXhczAVvg7T4ZuwPnxfw/8QNoL7YWN4CDaBxEXiwTmxM/mg7xPyvhSeD7oniAf+A1aDL8J6cDtsAL+GjeErsBN8FXaDr8FB8HU4TO2GwzfhOPgWzIM74XT4jt7XX8Hz1H4pfB9eBT+A18KP4Br4CbwPfgofgLvhJvX3KPyn3u974A74BXwXfgk/1fOgE/sDhzHmrMUsGXPGWDN0/J2DzENWzPJVjj37Px579r8y5/WvNt7s1tu9lWPOjnDM2X9ivNk66qsXkN1I1OzKcWeVv8pf5a/y91f+/dnz/3P+oPn/8136/tFF9v2jc/b92zqvc60/1flc5vSjd1srQPTRznUBVBfj0p+P3rU/P9+xjuDYGEt+23UdQSh92LtqhPqwcyqaZ27aYu+OD9jOpO10MDboOBpYE53pD9HwCP1ur8/ZpozetT/b9AffL2GX0k95uoQVW0FYqndbg1DCSoI/iPsKb2NPlOmbXi7tMw3KrQGYqH3VbeX8Z3vHcq5q2MyP6K/uqGmvzoyqcnPgtT+6odhc4s0nDLf+5kTtk/aL3Y3eedi5zCk3/co1xG6BN94TzTnRhaXDfU75h+JnracTPQjz+ZK8wFPNuol8SNH54OpO730b3E93zMcO7pm/N6IfOlH74j3i717vMq9Pzn25uFNmHH3cVcTmXG+ipwo26Oz4ajrVj/SLlJjxCY2kDE3ytMDqGM/R1umeGmZdxfclzEJK2DSrwnnimrZksb3Wu8rztvVr88Td5m3vR38NfQFHW9p/7dpv7T5XW/ukzZqBSYl2P/JmR5/2k8j0ZOzMXO7wedwFuN1SK/h3oc7hLoKhOdkNDqM/WvI71FccX75feC66yH7hbHSR/cIjja6LHA8wx53leLs57iTHlCvtJ24nYa6P/339xPHo9pq500W/Ond6///B3OnWf5P2720jnjl6y01DVtQrHja20WldK+dO/7/3q/w3505v8OgzVN8D1sAMhLZ8+bXR/opu8DR4PJwAT4DTYX84C54M58BT4UKYCRfBgfAqOAheDU+Dq+AQeDMcBh/VcJ+Bo+A2OBq+DM+Ab8Ce8Et4EtwL+2i/xjJY9V/snQmATtUewO+3zT6YYcY+WbKkFFIq5ZGErEV2jTEzGMbMmMUuayLJniWVNiEVkXhNTEgqvShJK1FRryLJkuT9vv93vnPvfO6U6dV7vdd36/jN/Z/lnnPuued+9/7//3PhdFgS3gc=
*/