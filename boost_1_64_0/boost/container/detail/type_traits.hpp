//////////////////////////////////////////////////////////////////////////////
// (C) Copyright John Maddock 2000.
// (C) Copyright Ion Gaztanaga 2005-2015.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
// The alignment and Type traits implementation comes from
// John Maddock's TypeTraits library.
//
// Some other tricks come from Howard Hinnant's papers and StackOverflow replies
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_TYPE_TRAITS_HPP
#define BOOST_CONTAINER_CONTAINER_DETAIL_TYPE_TRAITS_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/move/detail/type_traits.hpp>

namespace boost {
namespace container {
namespace dtl {

using ::boost::move_detail::enable_if;
using ::boost::move_detail::enable_if_and;
using ::boost::move_detail::is_same;
using ::boost::move_detail::is_different;
using ::boost::move_detail::is_pointer;
using ::boost::move_detail::add_reference;
using ::boost::move_detail::add_const;
using ::boost::move_detail::add_const_reference;
using ::boost::move_detail::remove_const;
using ::boost::move_detail::remove_reference;
using ::boost::move_detail::make_unsigned;
using ::boost::move_detail::is_floating_point;
using ::boost::move_detail::is_integral;
using ::boost::move_detail::is_enum;
using ::boost::move_detail::is_pod;
using ::boost::move_detail::is_empty;
using ::boost::move_detail::is_trivially_destructible;
using ::boost::move_detail::is_trivially_default_constructible;
using ::boost::move_detail::is_trivially_copy_constructible;
using ::boost::move_detail::is_trivially_move_constructible;
using ::boost::move_detail::is_trivially_copy_assignable;
using ::boost::move_detail::is_trivially_move_assignable;
using ::boost::move_detail::is_nothrow_default_constructible;
using ::boost::move_detail::is_nothrow_copy_constructible;
using ::boost::move_detail::is_nothrow_move_constructible;
using ::boost::move_detail::is_nothrow_copy_assignable;
using ::boost::move_detail::is_nothrow_move_assignable;
using ::boost::move_detail::is_nothrow_swappable;
using ::boost::move_detail::alignment_of;
using ::boost::move_detail::aligned_storage;
using ::boost::move_detail::nat;
using ::boost::move_detail::nat2;
using ::boost::move_detail::nat3;
using ::boost::move_detail::max_align_t;

}  //namespace dtl {
}  //namespace container {
}  //namespace boost {

#endif   //#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_TYPE_TRAITS_HPP

/* type_traits.hpp
OZmZnLAKEcffB1HFLF28K6KGzIKJv481knlh4jqglcxmdvExuW5Yt7B/bRm0ExZTFF3vwG9twzk+MvR5tXvFQWbssACZl5npBRYUcQfGtzA7xOxa98gzTU5YksnJzOSEpYo49u6+cDqzDP4OPrJMk5OZyQnLFnE8Zx6ZzezTJ+ZshpUIe3nABRthVWQWM3fcmyWweqXPRsWalTG0K2PoVHJ2K9ar1Iu5S9Rj69bLbIb45olN5mf22esNg2AJZDaz13bffBlsEpnF7M8jaz6HZYo47/Wvj4TlKb0UkAWY9Wy+byqsUuTEN0/++zsWlvM68WxEI5mXGd8XtIq4qPflMZsp35dncjLjOXuVuH7FYlaznOK9frZisYolKJZMxnvhy2ySYmmOtuKgDDLMpUy6p/rv0499G5ZPZjM7NCeYBSsV9sVdkyfAqsksZle8+Mo+WIOwKRMWz4a1kvmYXT0lJxHW4xg3Khiz5kAv17tnzzTv04H5yfzM+jtvmApLFHF3xE4cAksT9pn/9stgWWQWs0u+fWwWrECY+W41rFTkLFj7khdWLeyhh+deBGsUOXf0tB8FaxPjm/XAkERYn8i59Ills2BWcbRdfJInCRZHxuu99PIPe2GJwkYtHT9uv2UsTGU5Z9E7Bg9c+y68OcJstntu1gEbl1FAhvkZdi+aa7YxWJFiJcLMvIaVKVahWJViNYrVkXmZmf0LrEnEmf0nrEWJ61DiukTcpW83PwfrU3J61jrntMiccgaYyZxBJWdIxJ1z70+bYClKznQlZ6aIq6reXAnLFnHmGXdYHjO5/gqEme+ZwopEPbNPhpUpOSsUq1LGXqdYk2JtinUpvfQo1qeYa52zeZjJ7dYis5mZ8wJYHJnFzJyzwxId6xUOSCbDfnCOu3CA+ZYILGzimJk5ActicTeQvXph5D1YsYmDibhSFncj2b9rFsyF1TKLCGtlOeeKnO1kNjOzj4T1KnH9wsy2AotZ7xznJXOqF6vExStxyUrcJCUurMRlkXmZme0Plk9mMTPPjMBKWL15ZOa8AFZF5oGJejVkXpio16DENSlxbSKOz90OEWe2W1gPi/srWcaNyzfB+kwcTMR5SqLjbih7cSnMEma2TZiPm+gzoFicMPOdA1iQzGa2c/jMq2ApwhbeVnwcLFPkNO+hg0W4iTmfLXJeNLzrR1gRmcWs+ZTxb8LKeU6xbiuVsVeLnGafBWtQ4poUa1GsTbEOxbqUZdYjltngkhOOh3nuPjC+LLIT/3biFTA/mc1s15PNP8ESyHzM/hz44mOwVBE3bEqMDxYR1tk39UtYgeiltH3pp7BSYSMLUo+FVZHFMUtMW9UKaxX1tl9+65WwbhF342V9bTDfhuh65n2VsHhh7512czssiSzA7K2yob2wsIgz726A5ZFh/c0X67ZAsSLFShQrU6xCsSoym5n5uz2sQdjrg0edD2sjs5iZ7+DAurmJbcx1D80zZl9u/f5VmJ/Mz2x+SoYflkjGe3l+9iVjYGlkvF5XfdkbsIgwc18Kli96ue6r9mJYmaj3ZKh4C6yGLMBszda2R2Gtot7eMXWLYV3CzHMTsH7RyyMP1DXDfKXR9TbNicyAJZLxnOY+JixV2Jj+D8fCwmQ2s0+GbJwByxd2S84lJ8BKybwwcRyrLHWeZ9WK1SpWr1ijYs2KtZY6z88uJa5HsT5u4njkutc5zsNsgTi+W2RemFjWATKbmXmnEyxEZsGixrdywCSWc6F75X9zwjIUyxJmvvEAyyezmZ0eeW8NrFTYytBB78KqyTzMzNhhtUovjYq1klnMXn7zsrdgXaKeOabCeoSZdQTrY5YtzHUfMzEGD5nFjK8Hv4gz50s=
*/