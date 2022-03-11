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