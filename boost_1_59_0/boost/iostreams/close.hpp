// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED
#define BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/flush.hpp>
#include <boost/iostreams/detail/adapter/non_blocking_adapter.hpp>
#include <boost/iostreams/detail/ios.hpp> // BOOST_IOS
#include <boost/iostreams/detail/select.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/remove_cv.hpp>
#include <boost/type_traits/remove_reference.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

template<typename T>
void close(T& t);

template<typename T>
void close(T& t, BOOST_IOS::openmode which);

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which);
    
namespace detail {

template<typename T>
void close_all(T& t)
{ 
    try {
        boost::iostreams::close(t, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, BOOST_IOS::out);
}

template<typename T, typename Sink>
void close_all(T& t, Sink& snk)
{ 
    try {
        boost::iostreams::close(t, snk, BOOST_IOS::in);
    } catch (...) {
        try {
            boost::iostreams::close(t, snk, BOOST_IOS::out);
        } catch (...) { }
        throw;
    }
    boost::iostreams::close(t, snk, BOOST_IOS::out);
}

} // End namespace detail. 

} } // End namespaces iostreams, boost.

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct close_impl;

} // End namespace detail.

template<typename T>
void close(T& t) { detail::close_all(t); }

template<typename T>
void close(T& t, BOOST_IOS::openmode which)
{ 
#ifdef BOOST_IOSTREAMS_STRICT
    BOOST_ASSERT(which == BOOST_IOS::in || which == BOOST_IOS::out);
#else
    if (which == (BOOST_IOS::in | BOOST_IOS::out)) {
        detail::close_all(t);
        return;
    }
#endif
    detail::close_impl<T>::close(detail::unwrap(t), which); 
}

template<typename T, typename Sink>
void close(T& t, Sink& snk, BOOST_IOS::openmode which)
{ 
#ifdef BOOST_IOSTREAMS_STRICT
    BOOST_ASSERT(which == BOOST_IOS::in || which == BOOST_IOS::out);
#else
    if (which == (BOOST_IOS::in | BOOST_IOS::out)) {
        detail::close_all(t, snk);
        return;
    }
#endif
    detail::close_impl<T>::close(detail::unwrap(t), snk, which); 
}

namespace detail {

//------------------Definition of close_impl----------------------------------//

struct close_boost_stream { };
struct close_filtering_stream { };

template<typename T>
struct close_tag {
    typedef typename category_of<T>::type             category;
    typedef typename detail::unwrapped_type<T>::type  unwrapped;
    typedef typename
            iostreams::select<
                mpl::not_< is_convertible<category, closable_tag> >,
                any_tag,
                mpl::or_<
                    is_boost_stream<unwrapped>,
                    is_boost_stream_buffer<unwrapped>
                >,
                close_boost_stream,
                mpl::or_<
                    is_filtering_stream<unwrapped>,
                    is_filtering_streambuf<unwrapped>
                >,
                close_filtering_stream,
                mpl::or_<
                    is_convertible<category, two_sequence>,
                    is_convertible<category, dual_use>
                >,
                two_sequence,
                else_,
                closable_tag
            >::type type;
};

template<typename T>
struct close_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          close_impl<BOOST_DEDUCED_TYPENAME close_tag<T>::type>
      >::type
    { };

template<>
struct close_impl<any_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out)
            iostreams::flush(t);
    }

    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out) {
            non_blocking_adapter<Sink> nb(snk);
            iostreams::flush(t, nb);
        }
    }
};

template<>
struct close_impl<close_boost_stream> {
    template<typename T>
    static void close(T& t)
    {
        t.close();
    }
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        if (which == BOOST_IOS::out)
            t.close();
    }
};

template<>
struct close_impl<close_filtering_stream> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in) && t.is_complete())
            t.pop();
    }
};

template<>
struct close_impl<closable_tag> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in))
            t.close();
    }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        typedef typename category_of<T>::type category;
        const bool in =  is_convertible<category, input>::value &&
                        !is_convertible<category, output>::value;
        if (in == (which == BOOST_IOS::in)) {
            non_blocking_adapter<Sink> nb(snk);
            t.close(nb);
        }
    }
};

template<>
struct close_impl<two_sequence> {
    template<typename T>
    static void close(T& t, BOOST_IOS::openmode which) { t.close(which); }
    template<typename T, typename Sink>
    static void close(T& t, Sink& snk, BOOST_IOS::openmode which)
    {
        non_blocking_adapter<Sink> nb(snk);
        t.close(nb, which);
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_CLOSE_HPP_INCLUDED

/* close.hpp
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
*/