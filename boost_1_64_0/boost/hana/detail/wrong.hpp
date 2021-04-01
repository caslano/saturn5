/*!
@file
Defines `boost::hana::detail::wrong`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_WRONG_HPP
#define BOOST_HANA_DETAIL_WRONG_HPP

#include <boost/hana/config.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    //! @ingroup group-detail
    //! Equivalent to a type-dependent `std::false_type`.
    //!
    //! This is useful for making a static assertion that would otherwise
    //! always fire up dependent on some template parameters.
    //!
    //!
    //! Example
    //! -------
    //! @include example/detail/wrong.cpp
    template <typename ...>
    struct wrong : std::false_type { };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_WRONG_HPP

/* wrong.hpp
0RVcMHhJtSw8KVStAFICuODnBtzdvhR2q6Ieoi562exWxj+ve+k058Kf2oxhJmaQ40SPYpmTET9W9+wGm4b1P2C0hj3pIs8W9l9IPVmGrIQWpKKX8PLO8oHuBnPbZV7L3sjPxDYOaF23B2XWhvRF/H/LyZNJS00kdrw3nuvbLdCuE/Wl89iwrs3A0cOG6Tch5sVsEY0HeM+IXHEQokds1UYfgW2CoPnadkk6KUpA+JV8pOvKdL0sgNulW3eQCDX9X5X/2U/Dg0K9cTrc4lPqKI7GN/BkYGdZqI9D72kyefrL+yTLsh31adKtUAmsNrJZr0+C+wbHDzGcAAAd2i7fGjt2wW2CAkEx1xKVgi0FBFABWEl+fMSipxy1R6bHIsB5ftXE1gjrErCec+sQsW3GE/6tTeDShPhIuokOguzN0nB2FradlXGQLyaTEl+GK4Zuuos/22X7Q2x6Se3Ip+tBU+ZnrS0yXQlYe0j1nMYzQvyLqmwjJXvaHM8dd78paLKkU8jxboj2kxUrdOGW4CF2Zca6MqLhQausvdlibcsC6BnN42ZJHWibPpUfYw==
*/