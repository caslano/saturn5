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
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
*/