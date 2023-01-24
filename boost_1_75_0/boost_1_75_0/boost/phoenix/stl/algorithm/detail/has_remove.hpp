// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove.hpp
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove.hpp
czONAb3oiMzc06kUWZXCerlNgLP20LaY8MyIQrcZ8Py+WIF8AphPTyaMVuT+6zC4Vm5a2ULEyuBTheRkWQOQwqoTU4uoTzkw6sxZU0HooBKW97FxEVFTSMsAo/t0GTVon9Bb5F0pig76eXBdCBWWGFH4UiZYu6w6cqulTKams6bUzShCLBtjsh+wGqCXP8xecFizVnhFv6yBsKmK5KNcN8eEx9U7V1n91Mcw9IPTIsBxS0wF+4n72PSI6IiUCW+pMMNu2X+vwaD/nqwcZlZQfbePlp/+C/aosE8ROuTYeNf76I6V0zzl234/bmTLJZuWrHxhcERx6P1L7I0U8kf53azSfjAoOzRS3bsSZaaOqEBZqyOK0IwlKHJ1iJDXzI0B5lV54ZjufSXKVR2xpnwMfgdngsrrHRdGeE8gXmOSnCOqLhuunvlTK+FVS7+vldj2+3Rl8/IuxeAe8uvmig5WU4PmqwiMfDwriz0pWz9G3dCvooVnZQdNIDqJlfVr4Oy1wj2Bgo7QyAzrSStyo6pb21rPizulWJ/WWfFQ9u7IpnH2wdJBKCsqZJNXK1YAgBQb/G2E/V4AVofaVN4sn5Rd6kBz2O70CC/uKWhtSHWxBqExUyYc98fpa2YlkE88bvRXlxpMFYGLNgowTmk4LD3i69WtVIbkYFn/Oo23frcsMp+tQ0298N9CA2lftMuBBRiL3O6VgjKnIBzh3Uqy
*/