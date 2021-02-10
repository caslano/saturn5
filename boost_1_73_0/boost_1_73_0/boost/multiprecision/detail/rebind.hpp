///////////////////////////////////////////////////////////////////////////////
//  Copyright 2012 John Maddock.
//  Copyright Christopher Kormanyos 2013. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef BOOST_MP_DETAIL_REBIND_HPP
#define BOOST_MP_DETAIL_REBIND_HPP

namespace boost { namespace multiprecision { namespace backends { namespace detail {
template <class value_type, class my_allocator>
struct rebind
{
#ifndef BOOST_NO_CXX11_ALLOCATOR
   typedef typename std::allocator_traits<my_allocator>::template rebind_alloc<value_type> type;
#else
   typedef typename my_allocator::template rebind<value_type>::other type;
#endif
};
}}}} // namespace boost::multiprecision::backends::detail

#endif // BOOST_MP_DETAIL_REBIND_HPP

/* rebind.hpp
w8Lc2Jm5TcZokDuVgml4XEYwHOL3xK1qsjHvXRxeuV44CObOtYso9Mp8nT5fqI3iuaap4iK7x1x2weaONsmAnznTiEamLSIy3+lHApPK4K84oR9aKJ03tf6JmsCgWGpk5RD5QV5SbwEEX/9QSHfxLgYUGqj/bQfmr8zvCziKll5v5HmNuu0jq9doSw+/Wfxihn+WI/8sR/6q0x95con7PMy+woC/9sbApufJ34e6lljk6o8Fr/0wL/agBA8j3XTgp5OjvvxN136w1L0fuzMu/Vjkwg9sxEvxVwq0l735Q1s/rWYVu7fUTR8SkPWCj5Sqp4s9lIJILvawXTmxYhrIjL1udzf0XP5Z1S8GgO6myN5LoV07wMmaf0uG9aqOOdd0ZER03i0PK/qFDmY/iG2aKZyMaxcWinpf5EaHPLBkjOIVDLgIy6LunCFU1wlH13PB3ai5IXsfhHEXhBi+RW+D0Lbx5CUQ6kEyNRMxxavs1RBGk9rlEDNJYG70qCJLbfYsZBTkTNud7eO3aeegE55X6dbcypZ2IgVPNF8iAyRPzjx/QJer4603yTSC192UajX5tsQ2WKmk0s588EChT0L30gumUcYyI2n2RrBQuIChckaeOG1mmgPh1KfDJKVrNzLsAQQuQbhhVC5OMJIf
*/