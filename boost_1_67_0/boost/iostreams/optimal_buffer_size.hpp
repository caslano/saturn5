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
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
*/