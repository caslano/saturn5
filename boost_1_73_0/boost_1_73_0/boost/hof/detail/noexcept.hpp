/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    noexcept.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP
#define BOOST_HOF_GUARD_DETAIL_NOEXCEPT_HPP

#include <boost/hof/config.hpp>

#if BOOST_HOF_HAS_NOEXCEPT_DEDUCTION
#define BOOST_HOF_NOEXCEPT(...) noexcept(__VA_ARGS__)
#else
#define BOOST_HOF_NOEXCEPT(...)
#endif

#endif

/* noexcept.hpp
xby9JLUuH2GW45CEXrQEKZdwheEJ/TmgciBNie8l9BLPwxM66OmIhI4WPzKhNzo5CsjYyKMT+guKo40bdqSTjJH6jTveFsfLEcW7IqjD6ZbOvNSa6NZ+kZja+QwcGRHuw59qtrZEU75by1KhN++ckral2orJuDfV3+waWGYm4XFN8bblVBh6B0K3c3wkPzt2lxxGU5GuddhRv1bypbS2vGTaNf3TrvGyXJN2gR+9AALXmQgfm5op14uhLKVZzSA=
*/