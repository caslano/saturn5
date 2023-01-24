/* Copyright 2003-2017 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP
#define BOOST_MULTI_INDEX_DETAIL_PROMOTES_ARG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/detail/workaround.hpp>

/* Metafunctions to check if f(arg1,arg2) promotes either arg1 to the type of
 * arg2 or viceversa. By default, (i.e. if it cannot be determined), no
 * promotion is assumed.
 */

#if BOOST_WORKAROUND(BOOST_MSVC,<1400)

namespace boost{

namespace multi_index{

namespace detail{

template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:mpl::false_{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:mpl::false_{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#else

#include <boost/mpl/and.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/not.hpp>
#include <boost/multi_index/detail/is_transparent.hpp>
#include <boost/type_traits/is_convertible.hpp>

namespace boost{

namespace multi_index{

namespace detail{
  
template<typename F,typename Arg1,typename Arg2>
struct promotes_1st_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg1,Arg2>,
    is_transparent<F,Arg2,Arg2>
  >
{};

template<typename F,typename Arg1,typename Arg2>
struct promotes_2nd_arg:
  mpl::and_<
    mpl::not_<is_transparent<F,Arg1,Arg2> >,
    is_convertible<const Arg2,Arg1>,
    is_transparent<F,Arg1,Arg1>
  >
{};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
#endif

/* promotes_arg.hpp
zaxSYNWCGQM0UIgCjhs7i54KE3nS+Bi9F2xz9biiFEyg9070mhE2Gujlx5FhWdtXSTwivMTwe7k53EDFrr1niK+SKciyG761mFjt09B3whDPRZ8izpKhrq87dk5VVUfuFma0aLsFd1i0wAXlu02m8AgvoX2n8SMY/E+LFGGIEjiHA9ij/1t/EbSTLG7vBD52crrOywJ3ctNqYrfSV5tEpOTzX1NBn9WobaFAKL9yiYNrtuOfXV+jVm+Toq6i2+5r2M716Cpmdpg+v3HFf5lnvfqjhvg6nGd9Z3sTPKs8ND8UYjqT2L0BOu6evr017OpraY1xN4zWQqNtKv/HohbPlfPbGp0rcjSH+/MdtpD8Il7v4e5trTldzlzVxOnSZN+Ofdhi3+5uvm+zlYZ9u6FVfRvbdN+MZ58Wqu9PRDTy4Hyxr36uIXYn38gWbatpzBZ9XdMMG120RWeL2HZFBB5jt45fPtAPQMB5Js2lTeTzTg8PIequaSwlk/xjYP9ZXzofRZg0jyOg9NmLp1Nc7H0YaqbDVjpF1IIIcYrkKbuQeChV4XiqDLYhf4HftuAxVKVVWLKHjqGlBdjAti3UwAeGBl7ao51vleJ8W7TFcL7lKd49jOzTG59Tefo5NesDPqf6RzKeT0ddXCduIOs7k4l2Yt1JOIRXo2UVUwUD84gyoOiGhsMDoOPYvdjbi0WjP0Xob4wiXw4hhTG+MfvZ
*/