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
6TQbKvtSmm0LHaXJEqtx2tL8rtWav2ddDteI78AicGptOmedI4DuLPY0GxpEOLeOMflAI0+JftBc1+AI8Hdpr2cmQTUnI7Ay0FbS/B7V2U+8LVuhbTdX7LIkdc9LxCRNF8/fsJ7RheUF//rKDQc8aI0kX66Q55oMLFvvB3HcUj78FRgMYFqbQHcfag7buBYRowMmKFPt+r11EeV8pjskGC8+kPOR3yXe54Q3OHj3s/KaZsF69155hBVg3UdP7yHfU4ymYwa3b0WvH3/Q0w1gmhSI5DZ3r47m6h5tC6sjR67KgxBjezut1dbeyRlseOIpMT8znsP2h+H4X18wvEgD0naq9y2noeKfCJ+5gdEvoVDltdzOwk4JBWahUbKFq1EG1lxm9SbnyeZ1Z5Y2+bUiUMHZuMiEyFQnnhRndQ9dZc3QW/gKIsA5aDq252ratNMdb8HpIQs85QZu2AvcEwfkG01zeosyzKU3YrsMEv9iMOy937Q2YstRyzXaFohRYaikAuelMS4F/yiSu8nzdFMpOh6Z3uFjEj9zIL1y4yOkoopJPJzkQPbxucFOj6ob85AHFkWMiac/eQvluJVM/XQHlNcX7V3pfe1IghFQtXQkNeJeduunjzkAMLKxs233NB3CwHvC+T8VlaRn946j8k/uVXehVzf3QnkKUTnDxWcKS7aW1Z8VxFeP01bH2KXHf8oAwnTPcQZCa97n4ppP
*/