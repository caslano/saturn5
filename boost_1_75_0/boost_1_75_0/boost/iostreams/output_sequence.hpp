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
Zsz7cnvIKVOvyQGrBUb/Hj9B7X2/69eDo2iDltZqJquDwHKO2uzH/kCSZZdEvuEjjFXLK6TzDx+BZvNnzpcUul3Y6IMaX4i9Bds7um/IRkcWkMCkOsKlRfDjFidvXr9cNqNu/Y0h/Brtrvwx4DGazVkJicEkTf1fBMgzOyvW/cZCizf1Byd8y64+9ptU7cnx+uGt1IyesVDOWWPDeqNHX82IfIUjY8RT2b/uuC74tQSCq+w7XyhHGlUqZ6fo2de/Gt2vbiunwX/2NSQ1Xdg/HLcJC9/8qFPxOlFJklv2WZzaZFRscdj5LIF72HtB4Zan9dcA024H1KpXXW5TdUk2kk/6Y7tt3QNVZdSJhaZ13lAIg894VGYJyx6adPlFI8KVyH2hqTjK2r4Cun34h28/HWHdXzxnUdwAFmgd2hzWGLk5wvPlwQ7NCxXNG/5EoGALh2HPU4ts1xnPv+xHOhcbj8xkqENy1XE785f3zUDMz0jXGfMmr40+K7mdq7tedWt1RG9aWU3DahHmfcMb4zX7E3uvA61J7aek1ZvegE0NebuLPL3JjMEOk2n3N18EiIkEd3tcPK0lynVqB8zMZdbMTi0fH+exzUbZPnUXs+AQKRSZw2+Q9xL5u0ZqTTwYHl+cRetFVQKERM+CnFCEkR8ANu/3xcZFRG85B+QesnNlxG4DyUxjsP1/Z4lEtvWmALDcUX4gZWA8kF0tCDqe
*/