/*=============================================================================
  Copyright (c) 2001-2008 Joel de Guzman
  Copyright (c) 2001-2008 Hartmut Kaiser
  http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT
#define BOOST_SPIRIT_DEPRECATED_INCLUDE_SPIRIT

#include <boost/version.hpp>

#if BOOST_VERSION >= 103800
#if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__)
#  pragma message ("Warning: This header is deprecated. Please use: boost/spirit/include/classic.hpp")
#elif defined(__GNUC__) || defined(__HP_aCC) || defined(__SUNPRO_CC) || defined(__IBMCPP__)
#  warning "This header is deprecated. Please use: boost/spirit/include/classic.hpp"
#endif
#endif

#if !defined(BOOST_SPIRIT_USE_OLD_NAMESPACE)
#define BOOST_SPIRIT_USE_OLD_NAMESPACE
#endif
#include <boost/spirit/include/classic.hpp>

#endif

/* spirit.hpp
EeIfr6hdCvKh1c2VQs+/l8Yu6bI4csnVJEIae/gVwMTVooA3Y4m9pa1hyTrJNZC8btYu+JHmHNf/Y/pf2cWXGH9IW3+knumv8k/ajz/rLtlcjovz+KMLbcjkKbLPId13HItWr4Gyzt2hNkFYVG0zweagAhjTUynXC2iTznDaz+sCEwWiV5WIcJI0zzCZmDGR87wNEgoJT654/SyuPv6p9Xoh5KU//ExViJi3FJyqHgtu0erLGexgznvnGm6SBsoGMVnDTiy2qBV3hTgOGy8LXyP90zEw+vupGTAoHs8A7+kF4x5xH04Q99EPnhgyBdQzvp6lzwrgNJyq0R1LDX20y3+sOvvbKluBqzTeuhmPRhHWNSOFYnGqSe91goEW4/Dy+j+kQ+H3Vv8Y6ueF39ArVTTgyvJEcrn3XL1o9PgxlvvgTWLhUS1/AvYaUKJog+lr4VmC0/ks0FbbRah58EKkEarkkmmq9P3cBZfNmcmlbzapqWmo8niwVft1UqGyhEpiARAYkjwtDDO4QVtRjCTjzP06s97SAwOKYkPRSbcbjTOP1phcLYSBuUiKvg==
*/