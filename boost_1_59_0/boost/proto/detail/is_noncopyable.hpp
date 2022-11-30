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
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
*/