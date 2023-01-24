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
hIme53kHnPJKIZnx/EleKaTXNCfqpJUyaxqulDPqOfNKefoZWin2KY1yxqHyjkySbZ8T/nlOObNBK5/iXMz+eSvVMIt2Lf4l9M/Lv1kKLJxNy6u7YcJV7FOBnkvJ3ezPb+bWJwBfn95s8t3HevFTNDrfjWpomkWnBBadUrJ10QnDvsghahgmZvuDfZ+M7NKvyez7ZC7liS2cwkXKcdqtuQl1CeAn+tcQneY1EjFwFzv35KKa1b0rktP38oeRRazUormmcHxyOhWT7t8or+Qa4TijByrHCkZ6sYypujfXzhSuPhUWw22lqb2uyJyWoUQYjZYLoxHbgnY93dRqpxkOsYW5rNUTomiS5l+0mHqIlNlqVG4xO/WUW1owFY7ElwL0Ky0mPx0tIWm5Dhf5vHhQl39eVQsrsKSuuFAdY7HUlpHbRV5cPBWDH8aOIfnKildZIo0nbVRBkJ1gMGvZnkBaKN8RJfw78BKGVLnkH10pR+wFqbR3apNK3u5Uw7dKGRXQpeAkSXOKNzomDd3MJ9MeVrIHFkx/7MJI38OEJ4/6meJp3vqYQzs9e6A/L+eCJ+VQXj8iSW5qpHhJI4UtD2qBcFf6hZJtZFwS3ab20dSefLeIzl37ZxhJbk8a+Hmi2EZTVWPRLazqw4ADBQ2qz64PY7Ed9r5jKPJv9XzsszDumLD60P2KszTuA/ULI+y8ncYteF0/43XTijFAbIsw
*/