// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED
#define BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams { 

namespace detail {

// Implementation templates for simulated tag dispatch.
template<typename T> 
struct imbue_impl;

} // End namespace detail.

template<typename T, typename Locale>
void imbue(T& t, const Locale& loc)
{ detail::imbue_impl<T>::imbue(detail::unwrap(t), loc); }

namespace detail {

//------------------Definition of imbue_impl----------------------------------//

template<typename T>
struct imbue_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          imbue_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, streambuf_tag, localizable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct imbue_impl<any_tag> {
    template<typename T, typename Locale>
    static void imbue(T&, const Locale&) { }
};

template<>
struct imbue_impl<streambuf_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.pubimbue(loc); }
};

template<>
struct imbue_impl<localizable_tag> {
    template<typename T, typename Locale>
    static void imbue(T& t, const Locale& loc) { t.imbue(loc); }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_IMBUE_HPP_INCLUDED

/* imbue.hpp
cnwzpopOU3gIdV7TsEgH47UbsyTE6bvBjhDQjhBmXhPsCNgRsCMmKDxlR4htAmDOlhg2APfZwp+wdXYA1g99lJ0Q52x+ZRzA0yyzHfCB7gRO9RU6FNDpl1rw0e2H3Keh2w+5h9xD7qd7/RNyj765LFI97p/nHxnNqmqjgu75Fug1hvtXu0aBqe9tpabUb9UOa0TBBbV0VazVyvDNi+ebjxHmMe1OLsX4fCY66XIoP/rp0P009NOh+9B9aXRfbMlGb10MzZ50rKO/vmW6jeH0D1ielUDM4VRPv24L1F1Hl1p+eUanGuKchk41xBniLIs4o98ri7DOWEXGz2jpqupVAd3fLVBYDFcnnj42/SMN77qPhSiuRBmddNFZcEyDsHZ4clW8GZ50rnhZwfctjkwvMzEty6uR/sEu8gVmpQdVIa72Y1U87JmU2DPwF8CaSYO/ANYMrBlYM2tdaj/XmsHafFgi77VEZi7Vg29l66wRTC0QxFpJsLJvromCIZD0WiNiLQB8vd5/Ed8KPhEAu2MJuwM+EFgdafCBwOqA1QGrY62fHVjEB4IvFUhnMQw3KxT4G4LYBybd+8Cu+Su9k7u+4KO92Mvwo+i+ZgaL00sDgUXbiQtsBpvB5o2xWeBxPLBaYmt57fN14oGN6Ttg
*/