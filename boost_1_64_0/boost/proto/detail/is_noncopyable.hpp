///////////////////////////////////////////////////////////////////////////////
/// \file is_noncopyable.hpp
/// Utility for detecting when types are non-copyable
//
//  Copyright 2008 Eric Niebler. Distributed under the Boost
//  Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012
#define BOOST_PROTO_DETAIL_IS_NONCOPYABLE_HPP_EAN_19_07_2012

#include <boost/noncopyable.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/type_traits/is_base_of.hpp>
#include <boost/type_traits/is_abstract.hpp>
#include <boost/type_traits/is_function.hpp>
#include <boost/proto/proto_fwd.hpp>

namespace boost { namespace proto { namespace detail
{
    // All classes derived from std::ios_base have these public nested types,
    // and are non-copyable. This is an imperfect test, but it's the best we
    // we can do.
    template<typename T>
    yes_type check_is_iostream(
        typename T::failure *
      , typename T::Init *
      , typename T::fmtflags *
      , typename T::iostate *
      , typename T::openmode *
      , typename T::seekdir *
    );

    template<typename T>
    no_type check_is_iostream(...);

    template<typename T>
    struct is_iostream
    {
        static bool const value = sizeof(yes_type) == sizeof(check_is_iostream<T>(0,0,0,0,0,0));
        typedef mpl::bool_<value> type;
    };

    /// INTERNAL ONLY
    // This should be a customization point. And it serves the same purpose
    // as the is_noncopyable trait in Boost.Foreach. 
    template<typename T>
    struct is_noncopyable
        : mpl::or_<
            is_function<T>
          , is_abstract<T>
          , is_iostream<T>
          , is_base_of<noncopyable, T>
        >
    {};

    template<typename T, std::size_t N>
    struct is_noncopyable<T[N]>
      : mpl::true_
    {};

}}}

#endif

/* is_noncopyable.hpp
SHrPZXSQd3vWTDCu5ik9igwen/LIwsMPW58WrPY5/tG56JG4+i6F0WHBIHHvAkQwJfRHNaK1bqQWSlPsGsbINfmY1TpptUqU+pi6PxdVGHpXdzpV3lIN0rsUlxvrPhYQ5ISezo/U5MsM5lOhn/igpYZoDzPyo5iJYwGDR9TZA7+2glFhJMFE0f97bxQaVIrMkih9m7YgDdqfRF0VZN9sjbFpv7cleX6hi4rmLqDQ2bqH7Zj+gq5esMLTsJi05tXL3CJgg0YDRSaESyHVrS7IrO8L36DP0coqjlKGuSFDNObwI1wEAQQZutuRL3EeI7rEToZB1D57LX/wZ/+S8CXf3AKgncDaxmNXksicTyAEoRCXDRbGQ42p8J0QYenMnklMeOtWzEe7ElC2dqYMSZp1Auwqt0JUIgaLBSGtHMzCiolcKllLSfUp+8RXPk4s3O5YWU1BNkvZ5DkaCP64Ovy9X2BAZ6lC89/K4ekt7ac4OWsd5NeYpcZi4I4lkDUJAoSpPxWEz5jS12kdc7jxCbRasAFe/EdiMc7B3eSRz1IYm15puvjHWD68F4cxaA==
*/