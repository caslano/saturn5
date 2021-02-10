// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED
#define BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

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
struct output_sequence_impl;

} // End namespace detail.

template<typename T>
inline std::pair<
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*,
    BOOST_DEDUCED_TYPENAME char_type_of<T>::type*
>
output_sequence(T& t)
{ return detail::output_sequence_impl<T>::output_sequence(t); }

namespace detail {

//------------------Definition of output_sequence_impl------------------------//

template<typename T>
struct output_sequence_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          output_sequence_impl<direct_tag>
      >::type
    { };

template<>
struct output_sequence_impl<direct_tag> {
    template<typename U>
    static std::pair<
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*,
        BOOST_DEDUCED_TYPENAME char_type_of<U>::type*
    >
    output_sequence(U& u) { return u.output_sequence(); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OUTPUT_SEQUENCE_HPP_INCLUDED

/* output_sequence.hpp
ff2our2/vlutnqwf7dX31/fY0b16VVW/bKv/sVxNzwuiYmjPMIdlfVspHV45RtDx/C5lO8M9tp3+LLuYnSpLW9qckuB5f3dw+nBztLTDa89zTmyHxDubY3uK53bs+9A3AnahyU+PHRoWr2pauUkcYlDyb1aX0mUY9MJAtX3WFJ7fr1U2Nu6yf+3Qdqy7OPHdrXJwt7o2VnZU7qe4lIYbEL9LLNsIyEhZq2uXcdmf7qhvxgnH8id3bDs+cUPJZef8RKlVtuL9o2vt3Hbtrv2bUKUZutd2l2h22zf8/g017lm+juFQkhT6YPiGyWqgk6BWSa4raomk4aKNtAlulSufHEcXVX8kbhCdjRNvTkmthDTwunGG3LQ/zzXVCIxT4hJ2dZ6fm+EHaevEf7RNwnric794xvOGqmWJSlEjpg2TJFhduzb8exK3+2A7vlMbgdNO8pwRwyJ+1IeSLK83gqZ43R5LO6xZ6bIXRLcmvouDFmedwLFdchK6ZnS4/twz3PSpTs4fWZYdnTGchms6oZX1FJvQ8X5nJ+e/jh5z7LTy7Bb2fM8klHq+Sjqsk8Rdv1a5UOvHN6dfW8rlhX6p1ZPUeuCzoeSK1TweUQI/TPpMifWpYNinsouou0bbyS5CI4/E0Wz314vMPwzfZYfi
*/