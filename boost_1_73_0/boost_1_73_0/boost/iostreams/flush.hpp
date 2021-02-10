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
74LAdzel3+4+fZ6ImcX6JYilYnnE6RPd0DwyFtenz/Ug7i93NKOCgBP3h6UWvkfbJfX764vSWW4/OC+2qteGZfSNP4lbavpWy+iTqtF1NOel7WoP9L57zXRJGOmj5mg9+gYq8aL4WD6E2cYOeAbclBoOOWeJKj8Ry2O/BoH3YkKXfNez+8ENc8P+97qqaJ52SSxCU2c7c2+4JV2VOE9Gj9Cq+PyS/MbrilIdBqL1mAwcu0dc13YUck/zLKgHZ7mOUj5vX4aBrn/SvKbZV7L7A5r1XZNG5Dl+mH2ZluY8EK9sPRmObfVpxtDGyH+hJcRzPXz6qEQ/feYtKKgFec8MCzhzRTSdOKx2hne8ncFV9kY07CjVmfrAY8Ue1JCoNmSKuh6kSzMrVs/09WEtM4g7WWeN8PeT8WtR7ZuXWSfn7UpVqdQuO9XKeandrJ4El4OrPCNZndTMJgmaxngmnmuu0aMVlb48KT2S3k8a62H4E7/KM3J4+VZzLIq6Knki5lnuKLwYtM+KxRp+kAMXwUF0T2yV0CzaJvQmcW3f6ZFXmRp3X+wNyapVyTc936ExHewfvv2CNLqqYf1M1uxYyPF3GRW+QgbE0qlIBMX+yy10Dgt5WrrZX6auDcJjXosCrrFqGF9p9bxu8kewR9Ka
*/