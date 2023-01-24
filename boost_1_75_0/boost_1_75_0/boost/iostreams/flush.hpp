// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_FLUSH_HPP_INCLUDED
#define BOOST_IOSTREAMS_FLUSH_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct flush_device_impl;

template<typename T>
struct flush_filter_impl;

} // End namespace detail.

template<typename T>
bool flush(T& t)
{ return detail::flush_device_impl<T>::flush(detail::unwrap(t)); }

template<typename T, typename Sink>
bool flush(T& t, Sink& snk)
{ return detail::flush_filter_impl<T>::flush(detail::unwrap(t), snk); }

namespace detail {

//------------------Definition of flush_device_impl---------------------------//

template<typename T>
struct flush_device_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          flush_device_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, ostream_tag, streambuf_tag, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_device_impl<ostream_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.rdbuf()->BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<streambuf_tag> {
    template<typename T>
    static bool flush(T& t)
    { return t.BOOST_IOSTREAMS_PUBSYNC() == 0; }
};

template<>
struct flush_device_impl<flushable_tag> {
    template<typename T>
    static bool flush(T& t) { return t.flush(); }
};

template<>
struct flush_device_impl<any_tag> {
    template<typename T>
    static bool flush(T&) { return true; }
};

//------------------Definition of flush_filter_impl---------------------------//

template<typename T>
struct flush_filter_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          flush_filter_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, flushable_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct flush_filter_impl<flushable_tag> {
    template<typename T, typename Sink>
    static bool flush(T& t, Sink& snk) { return t.flush(snk); }
};

template<>
struct flush_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static bool flush(T&, Sink&) { return false; }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_FLUSH_HPP_INCLUDED

/* flush.hpp
RNBTYZmKR+1DZUdYTLfcIe+llBAUWbeSSkkeTLOIjrQNVdKkdZuRFYUPf1ji/Zo0v9jwAZ7JAWnAk9FQgNtgQvA8UZDcczBRNJbz7OP4SZJxu46tRns6o5kPq4qdI8T/Q+Gvr4j5Au52m/ZHkItzVGY/BOHI2RuwpBA3Vy1L+pC8HouipPOGZIbTHcQnW6SK/IeBPBzhguSDQpnvKI1B24FqjxBpeHGCfMqBD1M0VmECQoR2cntY1Eba4ucpj9XCOe9oqIaUT3qxizyd50lVpbBA6c3dX9x0o/lLSyFNBGEIOWQBH0WKzfUHEovPvg2s53H2f8GlV2b5gKFiqkFBxK7z86Zlk2gX2WNfOav4Rv9j0zd17tAtH5ZgIPKsgSe58iIDVp+C9STP4lplPU/b9G7boZGnSahcvzDxJhnmhVLrSGJUwHJmDOOUUDEkrUpeWq2wkJ9jkljh7VNIUvE781TKm7Lvisl/vsngy3bY4YggUXAr/pm91ZAsKAAjKVZIPjY4mNaimiz/NX+lZkXCKl7NH+cMsMN4jtRA0m8RMeevIW750LKO/A1ivNlamlF0tonWVJ3UlMEyF61Om5y6bN3WgDrLJBXT9/6kB+3qrjN597fNazRxufujSmrZXwXdth807O3arv/6mTXEWGE7Rv0xbO7BzxronOyNxcBUODLjesKSKPSRiID/Oc06ejmnrHJkIfEqy7XVcI/Y
*/