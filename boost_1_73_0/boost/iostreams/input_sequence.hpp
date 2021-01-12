// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED
#define BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <utility>           // pair.
#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>  // is_custom 
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct input_sequence_impl;

} // End namespace detail.

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*,
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*
>
input_sequence(T& t)
{ return detail::input_sequence_impl<T>::input_sequence(t); }

namespace detail {

//------------------Definition of direct_impl-------------------------------//

template<typename T>
struct input_sequence_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          input_sequence_impl<direct_tag>
      >::type
    { };

template<>
struct input_sequence_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*,
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*
    >
    input_sequence(U& u) { return u.input_sequence(); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_INPUT_SEQUENCE_HPP_INCLUDED

/* input_sequence.hpp
KlgxGyu33AolYeUSK9cIOWPLiJInKHkZQDlko+SVW9OSUPKIkico04mSLyjLBeUNGyW/3PIloeQTJV9QxNkFQSZEAhMQjg3i7Ylnzuaugm3Ld/+Yvu1n6F/3/d3rFndlsPjZ4fYiuQ24XhnsIaA2AdfTYG+dwVgE1DM46+pLD+4sPoB0j1ih8lLuN3nc75ffTvn9IH7HrfL5LMba8Iq1mb5PP5wuxV7bk9+wvdsje/R8JwOc
*/