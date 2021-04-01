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
doRw+3xBbxju4K+e9q8g/jNnnJDSUb8+lAI4XzCdquHvnzcAsawHHHBotGnAXU2ykGZnpyNYvKfelSB1PEhHraCrcd02wTwpYGfnMZ6nlt2MsfVIV+uw75wXqPdE3UXbZAj/QdmY9wwAGVd1fCRvF8dN0rq+G4TJLz1OFqi/0EDxttSaJwdt1baapxnjysbqZ5wNHoBP6QOiHThUP0LF6F6bylUQeO4OWbrk33unIG/sisulcwo60foDf0hZUggvxnoiLrawA2FeGWWWr8xEofNNZLjhhwfi+K/f5NkBOIldGH5+VFBEeerirvu5V8EKm59vH5peqahyBCB5qe7kJt70Epc7L0EKj/lRZ7NuCeadGyuBZDx34zv/L9dnZKwDEunbdX1W2yao0L1jhI9QKvWGDW4OKIGijZs9lJqUb/JLneNvhYGtLsulu+Jj2zdtZhkYoIXDfjiPfVMd28WRWLABqDPIVJ8WxsQdIlQ9mbhkBHe0MWWokyg4xeP3pmTudAN527E0/MspRvbdH4ldMUX8bBGRSwYDtkJKdRupYNtLZdiRG9mXBzQm5w==
*/