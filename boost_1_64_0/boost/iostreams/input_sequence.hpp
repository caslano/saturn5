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
S21MDROXam57EbjOwj5LsLWzisWwnCiXzsBuc9d27GZfm7DFR6pZznsoaA/QINU4lw2nSaripbkJxwKotiii0q8yvB8zm4u2OP2aP1hXyhW5GGGlZlHr8aDf4jEtGamV2dOW1a91pfBUlvqo70nOPkzmp97uqPdndWLy7ns+cjJvEfetsG3g8Ze8mOWoRVclQwk0c4Hxl2zy9jkVetM/PY+lBwHP8dr1RI63ceBztmkX9xAPXaRHTR0rKcHq5OPFvaY2TPU3ipT/FS//NJzjktCGXz/Nqsrgp1Iri+DmlGr6Eeg3ZDJAsbi4xvlfVBHLGbfdfHFDszXCz9EGPbqxm4sjmeFHk8ayaFN02OjbMrKfPPp9bNWnDHoe4+8NTSHKYdl8xuRAvXtJfrpEfX05UR2nLKvC4Ano8SDJjtUHCs6bQmi5AesA7Puk2KcORLKRDORIePKG0RbZmLr4xhhHPZU4Qa1E5zx7XeVLnx89y/A5r7Uqc6rpu/ic39K8UYmb7VvdFL55qE1z0pPeD1ACeueP283BlpwxG1eqoGitLinPYK8nTUHHA9xhjQ==
*/