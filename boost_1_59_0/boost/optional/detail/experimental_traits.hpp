// Copyright (C) 2017 Andrzej Krzemienski.
//
// Use, modification, and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/optional for documentation.
//
// You are welcome to contact the author at:
//  akrzemi1@gmail.com

#ifndef BOOST_OPTIONAL_DETAIL_EXPERIMENTAL_TRAITS_04NOV2017_HPP
#define BOOST_OPTIONAL_DETAIL_EXPERIMENTAL_TRAITS_04NOV2017_HPP

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/predef.h>
#include <boost/type_traits.hpp>
  
// The condition to use POD implementation

#ifdef BOOST_OPTIONAL_CONFIG_NO_POD_SPEC
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif defined BOOST_OPTIONAL_CONFIG_NO_SPEC_FOR_TRIVIAL_TYPES
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_CONSTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_MOVE_ASSIGN
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_MOVE_CONSTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_COPY
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_ASSIGN
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif !defined BOOST_HAS_TRIVIAL_DESTRUCTOR
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#elif BOOST_WORKAROUND(BOOST_GCC, < 50000)
# define BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
#endif

// GCC 5 or higher, or clang with libc++ or clang with libstdc++ 5 or higher
#if __cplusplus >= 201103L
#  if BOOST_WORKAROUND(BOOST_GCC, >= 50000)
#    define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#  elif (defined BOOST_CLANG)
#    if BOOST_LIB_STD_CXX > 0
#      define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#    elif BOOST_LIB_STD_GNU >= 441200023 && BOOST_LIB_STD_GNU != 450600023 && BOOST_LIB_STD_GNU != 450600026 && BOOST_LIB_STD_GNU != 460800003 && BOOST_LIB_STD_GNU != 450400026 && BOOST_LIB_STD_GNU != 460700026
#      define BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#    endif
#  endif
#endif  


#ifndef BOOST_OPTIONAL_DETAIL_USE_STD_TYPE_TRAITS
#  define BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T) BOOST_HAS_TRIVIAL_CONSTRUCTOR(T)
#else
#  include <type_traits>
#  define BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T) std::is_trivially_default_constructible<T>::value
#endif
  
  
namespace boost { namespace optional_detail {
  
#ifndef BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES
template <typename T>
struct is_type_trivially_copyable
  : boost::conditional<(boost::has_trivial_copy_constructor<T>::value &&
                        boost::has_trivial_move_constructor<T>::value &&
                        boost::has_trivial_destructor<T>::value &&
                        boost::has_trivial_move_assign<T>::value &&
                        boost::has_trivial_assign<T>::value),
                        boost::true_type, boost::false_type>::type
{};
#else
template <typename T>
struct is_type_trivially_copyable
: boost::conditional<(boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value),
                     boost::true_type, boost::false_type>::type
{};
#endif



#ifndef BOOST_OPTIONAL_DETAIL_NO_SPEC_FOR_TRIVIAL_TYPES  
template <typename T>
struct optional_uses_direct_storage_for_
  : boost::conditional< (is_type_trivially_copyable<T>::value && BOOST_OPTIONAL_DETAIL_HAS_TRIVIAL_CTOR(T)) ||
                        (boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value)
                      , boost::true_type, boost::false_type>::type
{};
#else
template <typename T>
struct optional_uses_direct_storage_for_
  : boost::conditional<(boost::is_scalar<T>::value && !boost::is_const<T>::value && !boost::is_volatile<T>::value)
                      , boost::true_type, boost::false_type>::type
{};
#endif


}} // boost::optional_detail

#endif

/* experimental_traits.hpp
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
*/