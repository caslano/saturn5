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
Y5YG18CxyX2ARvhIBwuL7y7w1IEOWhfLyYhs+LYZBpjaz1qW/7YZpWt6fVEKeyo/0fRDkMjjbBk20iJohx7f5l56kWQPQptCF/SX9zjxQvvcnzjWUmRB+umggN8H2MUe9s46aZfDLy/d4/o3isMYANE/LLaYH9qMgb6QxYpYywD9baVha2zzJJQni1UZyHnO72v3lGRXIQLkdWeAn8dmD1jIbhuUzVvo6+H74/7u8aoBLzrzhW3P807leivnsSwt7KljmjX5RTo87Kkrw5fQLs+2M8z1j6mh1y22FnDxhncaegRa3OJrQo6wE2+hXIamW3uFFZX9+TolFz67lKXGpD+mxfr8F43shXEW03oTihpWbHpu297yBf64hsQi7frGw2+b3go8z4oQHYLTFacEwYJgXW0VuhpTihIWGt/3Hl/5i83l932EvgfOET9Jf05KjUmi4JX0Ic6kWBxCEAjySFYllB0RZK/bxVIQJI+QTiYyA2xjznKGyjhu1YN4aiLIYirRLO0vGBUuuwm1uONumhofzy8zvjrOb88zEsZ49GgRMMj0il3rCioKCHNmHS4ksCr+GhEfQeKVWxPZgJpMp5LGWA+RcQxFCKR9zZ7uc2uBjRmivm0PuXXZFFazh52CfKW8e+4edsp570YGAs2D2UNfOp+RRD0j+W+fyNN9uqomildukkBRiJuuGKg8dgo4Zx+MVnaNbDequMuS
*/