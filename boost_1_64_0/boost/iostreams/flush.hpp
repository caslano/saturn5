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
XHY0EuOd3UWEq5P1PtcDrPvOavpYMc17Ho8fepmWUn0pW24s5SjYxR3n+bWzt5QWOWSj7kcPy3veVaURdH6ccd5eZwrrr3YZu8KnyaEiTHlMrmSvhnbK52xqcUGMtbbyKbQngXKQKC+XVj6yhYpH7fWlcH4nDBqk+XvT9iR682bS54refz81lNqvovc7OwfSb1v+/rwzx28yPS/S3QpxPAY7UfIToThj8C3ZKbriVKCzOHdtnmoX1W0lxX6bXWThbNCqjmCc/xiIky+ni4FOPxHmcqG/Lme8r1I4D/Q4HKbfe6T8fV9Zzt/TaRQHW1ns+N9TipeWyLHSYSVKCuE8fZTiWBn10mP0H00pzLrGOYVjhmu/VSkQvvL3gSHcf/xAz3EIBX70sj1MbstRtvWlNijbGXJD6QOlvnRdbS61sJcRI3GGpv4ObUx+29o94nPpW6mPGslxCRisuT9imy2cKItPpOpKRyNen2j5D1dcM87IXT+A8sOu9bFzxFYxHCdyRSvZchV7qNE+niM/Nnf+PrYCx7sdxyUIpxqkSFHSIjlKOog8i7BVNvLNj+peMEpCNs71TaJwf4GL2yivTykvXxEF+l0O5xVud21FJ/j6k+girUS7S0f/NkIMVEYIuzpCjFUXiUDbavG6bTnaXWfsh95dLHWsRrtri3bXk/op5036qXBzP8X9h1kHG36jfyrSPu3F3Re9uPu6F7Yf+2DS1T5xaOlrI79s0L1Mrx92fHl04Pji7/deXB3uRToPheVnHufOBUvC7uCMrih7z9+pCoaANcA28FwTDEZ+1QKPgLXBhQrOuwD7Ix7xYBk8tw54GqwLrkK864EjkT/1warIjwbgJbAhuMGF8wHAiW60G7CeB2pdUBusJoCHwDaaf7AtGIiItdPCAduDHcFEkNPF41vrdF3mc4Wu8bk5Ave1hmcJDJLxE/wSVMAFSJcK9kO6bGAU0mMHT4EO8HmkywmOQLpcYBWkxw3+BHrA9UiXHzgB6fIHNbkiALwOBnK6IjldpTldUZyuMpyuspyuJInfPfx+nQve5T0PicxbfG7Su5y+HWAA/y4FbuPzgXLA3nx9MbgTDEUYH4ANwV3gWvCv4HHwI7AL8mMPmA1+DJ4GPwGjkT9/A58E94I54KdgFeTXZ2BfcB/4N3A/KJBvn4ODwQPgSvALMBD5eBBsBh4CN4CHwVzwS7Aj8vcIOBr8CrwMfg1WRj4fBeuDueBn4Ddgc+T7t+BQ8Bh4GDwOqsigE+BU8Ec+FyX2tHrjbIHfsZbAvI6gGcK62VqCrrieATvHt6bAZ3zGZ3zGZ3zGZ3zGZ3zm325u8/r/MZn9NJs6vlGduEG3Yg2Apu+vavr+P8UuyKyQvWvhl4JVMBfS7G6af+3cpXlqCp4Nnf8YLDJPTR8vvN//dwsTuI6o4bc+F9WJ7pklp2F+L4TmmTgchN4VUr55LpbceU7UTmFlxAmrbwSs/cZb7hFo6Xd0nOU3AtZ+Ea71NwJmv5PIbwoibPWNgLXfeMv9Aaz96nGINvmNtvY7Wo9DJZPfSoX41eNQxeS3SiF+9TjEmvzGmvy6Db/phh7mFbrmJ58VLtYjSeLtezQ3mcKqbQqrdr7nlqH5+AH99efWNfmtm8/vQ2F03mMW6qJxJmUyXZ8q95Ed/B2HZsakawzn+KWQn2lyF3FRai2X5XInfzRfrM9xryR/98im63F0ncNZ0JT1VXnTaOivZtP93cz3U73S517n0fX2cp60wIc+h9qFrs+UB8g2cxxrm+PwGcXho4Jx4DnxbAojVZ4helI9ykXA1dBIq+ez38P9z0Eo25J5+TPca+DvmrBMcqsF1obVwotjv7VN1NziYY8=
*/