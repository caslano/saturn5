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
/WkBNPJ2vDWLLhDGF7/sJNSesHDg6eDyAE0Amx7oMlM/ISdttXRu2fdL7UiOmsquW89d0VmLenbPv8nfSBVCdNyBMnlkDvM/c6bQ0HvDxEJJC58feCIYNWHX2XoLOptbj7raKuo5M51M151yuMwp4Vzn2D3/LouJHCdmp4ih4VanRYO385QA5FKmrsZI37MWQqRqy9vz6APCuR5Caei9YWKhpIXPDzwRjJqw62y9BZ2119O7l6d3Oody1dW4kKMPyk6jH5zvvyUfp8kyTNdRKPsr5uto9rJ9m8xCMWLYGQUDqcDLnmrlH1BLAwQKAAAACAAtZ0pSvR3bk0QJAAAobQEALgAJAGN1cmwtbWFzdGVyL3Byb2plY3RzL1dpbmRvd3MvVkM4L3NyYy9jdXJsLnRtcGxVVAUAAbZIJGDtnWtP2zocxl+XT1FVvGCauJXLOBrdBEmBSuGiBtheIFVp4kLO0qSKE6A753z341yatqwlKSrYdR9pk3KxXcdx/PPz/J1w+P2565QfiU9tz61Vtje2KmXimp5lu/e1yg/btbwnur5d3atWvn9bOby1aWg4ehBatnfle38TM1gppRvX/R6pVZIUZeXz58pK6XZQ7sHG1hbbvzC6LIkZ+k4ly3Z601BrlX/2qtWD+l9K
*/