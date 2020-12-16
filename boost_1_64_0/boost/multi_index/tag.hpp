/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_TAG_HPP
#define BOOST_MULTI_INDEX_TAG_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <boost/multi_index/detail/no_duplicate_tags.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/transform.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/preprocessor/facilities/intercept.hpp> 
#include <boost/preprocessor/repetition/enum_binary_params.hpp> 
#include <boost/preprocessor/repetition/enum_params.hpp> 
#include <boost/static_assert.hpp>
#include <boost/type_traits/is_base_and_derived.hpp>

/* A wrapper of mpl::vector used to hide MPL from the user.
 * tag contains types used as tag names for indices in get() functions.
 */

/* This user_definable macro limits the number of elements of a tag;
 * useful for shortening resulting symbol names (MSVC++ 6.0, for instance,
 * has problems coping with very long symbol names.)
 */

#if !defined(BOOST_MULTI_INDEX_LIMIT_TAG_SIZE)
#define BOOST_MULTI_INDEX_LIMIT_TAG_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

#if BOOST_MULTI_INDEX_LIMIT_TAG_SIZE<BOOST_MPL_LIMIT_VECTOR_SIZE
#define BOOST_MULTI_INDEX_TAG_SIZE BOOST_MULTI_INDEX_LIMIT_TAG_SIZE
#else
#define BOOST_MULTI_INDEX_TAG_SIZE BOOST_MPL_LIMIT_VECTOR_SIZE
#endif

namespace boost{

namespace multi_index{

namespace detail{

struct tag_marker{};

template<typename T>
struct is_tag
{
  BOOST_STATIC_CONSTANT(bool,value=(is_base_and_derived<tag_marker,T>::value));
};

} /* namespace multi_index::detail */

template<
  BOOST_PP_ENUM_BINARY_PARAMS(
    BOOST_MULTI_INDEX_TAG_SIZE,
    typename T,
    =mpl::na BOOST_PP_INTERCEPT) 
>
struct tag:private detail::tag_marker
{
  /* The mpl::transform pass produces shorter symbols (without
   * trailing mpl::na's.)
   */

  typedef typename mpl::transform<
    mpl::vector<BOOST_PP_ENUM_PARAMS(BOOST_MULTI_INDEX_TAG_SIZE,T)>,
    mpl::identity<mpl::_1>
  >::type type;

  BOOST_STATIC_ASSERT(detail::no_duplicate_tags<type>::value);
};

} /* namespace multi_index */

} /* namespace boost */

#undef BOOST_MULTI_INDEX_TAG_SIZE

#endif

/* tag.hpp
LfQ5OCbj/v/ciRp3Eq6ercgrmafWZPT+x1M9ctf2dozqAlQX3qFwaFshUGyHd7J2iIQfZ27hJf/1fp3aV39apwljj47JYx1Om3vMZm/h0UPeS4Su7XW4fm9r0PbTejs+3qTX8hFzsYmpIPTMZIJgYE4htJdtJzTDJjqzg9DkmKTl/oFBqxPFMXR6Z01fXZWIoS303Md527hR6sV5+F/btvSad/HjfM2zbct38+L/bMkb66CtifTd/YUoQ9cJg2rFm6dLimOPWFLqN5Y/0u/mqDxwyxQUEGPbErWYCHO9htlahJ8eZr3HqZiDoPq//1XQoeG/99eyYvwbSVBS/Te8hYP91Ab07YfDuaxcM5Z7K72NygagaYevy2jK0eYta9pnmnyw7CFdNHiBDOOuon+hya+XXJThNmUABGV8pUUGTGdURtiUoSA3JXcjfoY2imoBuCXaKBhN+bvrnyL3Jzmd359kNJjYyboybtLm1pYXh/SjEzV9/sRA2jb0FI5zw1dquizxKrXzvW67/r46LUmYl33/oe7KY+z+pvibpdOWoihqr7326ejUFOF+933RmR+1xPNm5k1ndJZn3htKxBYRS1HUvi9/kIjUvlMiQgiNiJAIldjXoqRived+v/e8c+57U60tVH5Pez+fc/d7v/eee+65Eyy80yJpvYdgq22FsrQev7PGwVRgk6xlWDjUfR87vothUKcY3zcQq3xMo13xbh2+sS51OLBb7D611enn48aIwye8H76nDl/c6rA60uGQOp2Tb1KHQ2surbbAvgDPfyimXi3qInaHmxLMODd/nsZWulARqrHxHOVmiMkOcqLVgxUbyedpgm8sLmL4ZRq+3sa0Hr8Xw3U2EPsGwZ7e3tyg2MNuXmPQyNBrCLbvFjW21uqeVMOI2PpqDHo3kdl7Sx2+tVaLYJlfYGA6p3hWuK/Gu7CGbUPUKNtjmHSFUkWOsvtvhbga8TRP5xHDtsV4Z25NMGwIYjeE+GDbP/42iGHbY39GDHprP72v7K/DextsxYZr5NvW+JYaCJjW5O3qcHXmrZoesY9qTKoBl6sCIpbevsag4UH9SXSHH1QYDv7+nuYOED6oBsB5444EryCU/RZi7MgW01y+k8LxLADtLXn4FLWbPn1nhsnVtnw0DG3PK857DtQcGNfN/njZd5cqHJbo7JxRhz+1zgjBzkF+oM5Obsp6lqtumN+0juVneIbe1oVDW82fagwmo0FdQ8lkuz3Z1xZqFsZ/gXH4GfwTf64xMKHeWGpWhk8o++wfary1udl6WrO92ghy7bfqcw12Xz0KkzSOnes+K6f2dD8coUnx/ZPCwOEXXAB6am75dG08ijhWE9oojdUYzKeLa61TRO4sYlj1iP2ZYGafXBwHrKpSMKVTY4HufSjOmwXjP7UDOQNpX0JsMO3nTWiMNRmu27/zWb63dTwvc/PAvt52uXWtYz+j4pt95LFmr7ofQ84Sf6TWFv7UGmyoSHs9e4Rhm5tTnY3Vp4Es7mcJvrZBZc+bGMgTvDFu4HCwz+t+EDfi+PwOgwMTAYnj3MQQ3Ijj3E6Ts7JO87H3RkNwI44fcA5u+vDu442H4BAH2duXNzE53Y3Vp7TlNg/WV8Sn9k2356koafvdzODi+QauDQZxLBuuAwY5xKZ9/y2G4SoSjOMnjAN9aApwPPP66C0Bn19XuKqbQ6cOkTOxH+wz8alTU2T+bHxYzW9wvixJVRtpm9lc+//8rLEPzpPISbLi+sdT/1vwY7W+W2D6iTeO1OE8G6h3efzoIC51e815aVSxsNz/bolx4LW3FlZXmG7nJyp8aFGxrAeNucNNfcdPw+suK44RSFfmWQ+hqWpLhOldOc8=
*/