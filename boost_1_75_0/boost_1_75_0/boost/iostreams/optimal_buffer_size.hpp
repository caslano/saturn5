// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/constants.hpp>  // constants.
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct optimal_buffer_size_impl;

} // End namespace detail.

template<typename T>
std::streamsize optimal_buffer_size(const T& t)
{
    typedef detail::optimal_buffer_size_impl<T> impl;
    return impl::optimal_buffer_size(detail::unwrap(t));
}

namespace detail {

//------------------Definition of optimal_buffer_size_impl--------------------//

template<typename T>
struct optimal_buffer_size_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          optimal_buffer_size_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, optimally_buffered_tag, device_tag, filter_tag
              >::type
          >
      >::type
    { };

template<>
struct optimal_buffer_size_impl<optimally_buffered_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T& t)
    { return t.optimal_buffer_size(); }
};

template<>
struct optimal_buffer_size_impl<device_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_device_buffer_size; }
};

template<>
struct optimal_buffer_size_impl<filter_tag> {
    template<typename T>
    static std::streamsize optimal_buffer_size(const T&)
    { return default_filter_buffer_size; }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OPTIMAL_BUFFER_SIZE_HPP_INCLUDED

/* optimal_buffer_size.hpp
wiIDTQRHDdQZdYaOhvAAd/s26le0a4RT2i8XDH9yqlAY9htjbiz6iKG0uLYUSE6SzNmib9dFxbBmVjiWz7a46tQfcMrUmyqHkbnh16U/VbeVFUSFZwtrzzfOeRJLoc332MtnzXMr8l+tzNbei8d8hwx64GdG9ci12yzvuH1pb/fxRl3Tq/sxgB8zbF/43XGpmBp+46Fjw5DTaySsz6c5lD1w647v6rW8UG/deXS40eefCRFrEd8/6TaujYDpMRv2GI3tVe7WIwV6Ijmdoc4/0RpSZp6918oSPmttjdwF8HquylyBM3lv873ddgGPE4bWdRi13m7GXi5jy9Zg7283nNseJ6Nc/i0C7Szb6Pzb/enufNGvfFO/t1fdvgXwCFRveLV8pj5SamEwripfUPB2Mh5HHLOrYh1gNAZYpx5g4rQl0TbJt8z3o5VO2+wJtkcZaxi0hQ0UIKQuO6+dVgqFKHfGbIiVO5wY8vgoxPC4LMxbBqQou84pjry2SfNWTpiSvM1P/tiOSjb+PLVv7UPTOmIiBwNA/bxHA9v3QLt1VhsrY+wtDS2KlgRiV7hpoJW+EerBKwumvTj+3oEAOOJxY98Z+6dgV5O7UE4KjldIUMbqU6qfST0MZGzwdIVESDjL1rEttJIuMgpUBaRTrygrQZ5BhfuteEb+g+RymFC5BcS0V/5oEFhl59MlaVNceKLvHM/3Ywm7p/MMeNHF
*/