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