//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP
#define BOOST_BEAST_UNIT_TEST_GLOBAL_SUITES_HPP

#include <boost/beast/_experimental/unit_test/suite_list.hpp>

namespace boost {
namespace beast {
namespace unit_test {

namespace detail {

/// Holds test suites registered during static initialization.
inline
suite_list&
global_suites()
{
    static suite_list s;
    return s;
}

template<class Suite>
struct insert_suite
{
    insert_suite(char const* name, char const* module,
        char const* library, bool manual)
    {
        global_suites().insert<Suite>(
            name, module, library, manual);
    }
};

} // detail

/// Holds test suites registered during static initialization.
inline
suite_list const&
global_suites()
{
    return detail::global_suites();
}

} // unit_test
} // beast
} // boost

#endif

/* global_suites.hpp
OOB+4PHAMXi+EL+S/HaeyNk/4K9Rz0rgs8BZ/PIC+bZDwEouB44D3ggcD1wJnAC8DziR9wl4P9L/DPhA1Iy1aZ5gxtoM9dNz74arE65ZuGuFu1u4+4XrEO4F4TYK95pw24X7QLh+juUGOJYbK9wE4c4V7gLh5gk3X7jrhfOFu1+4VcJtEO4V4f4o3J+E2yPcAeEmuJb7qmu5SuHOEm6hcFcIt0y4NuFWC/eEcB3CvSDcu8L1CPftkOUuCVnuSuE=
*/