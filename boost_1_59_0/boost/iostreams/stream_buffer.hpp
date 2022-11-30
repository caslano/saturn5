// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED
#define BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <memory>            // allocator.
#include <boost/config.hpp>  // BOOST_DEDUCED_TYPENAME.
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/config/overload_resolution.hpp>
#include <boost/iostreams/detail/forward.hpp>
#include <boost/iostreams/detail/ios.hpp>  // failure, streamsize.
#include <boost/iostreams/detail/streambuf/direct_streambuf.hpp>
#include <boost/iostreams/detail/streambuf/indirect_streambuf.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/throw_exception.hpp>
#include <boost/type_traits/is_convertible.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams { namespace detail {

template<typename T, typename Tr, typename Alloc, typename Mode>
struct stream_buffer_traits {
    typedef typename
            mpl::if_<
                is_convertible<
                    BOOST_DEDUCED_TYPENAME category_of<T>::type,
                    direct_tag
                >,
                direct_streambuf<T, Tr>,
                indirect_streambuf<T, Tr, Alloc, Mode>
            >::type type;
};

} } } // End namespaces detail, iostreams, boost

#ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION
# include <boost/iostreams/detail/broken_overload_resolution/stream_buffer.hpp>
#else

namespace boost { namespace iostreams {

template< typename T,
          typename Tr =
              BOOST_IOSTREAMS_CHAR_TRAITS(
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type
              ),
          typename Alloc =
              std::allocator<
                  BOOST_DEDUCED_TYPENAME char_type_of<T>::type
              >,
          typename Mode = BOOST_DEDUCED_TYPENAME mode_of<T>::type >
class stream_buffer
    : public detail::stream_buffer_traits<T, Tr, Alloc, Mode>::type
{
private:
    BOOST_STATIC_ASSERT((
        is_convertible<
            BOOST_DEDUCED_TYPENAME iostreams::category_of<T>::type, Mode
        >::value
    ));
    typedef typename
            detail::stream_buffer_traits<
                T, Tr, Alloc, Mode
            >::type                           base_type;
public:
    typedef typename char_type_of<T>::type    char_type;
    struct category 
        : Mode,
          closable_tag,
          streambuf_tag
        { };
    BOOST_IOSTREAMS_STREAMBUF_TYPEDEFS(Tr)
public:
    stream_buffer() { }
    ~stream_buffer()
    { 
        try { 
            if (this->is_open() && this->auto_close()) 
                this->close(); 
        } catch (...) { } 
    }
    BOOST_IOSTREAMS_FORWARD( stream_buffer, open_impl, T,
                             BOOST_IOSTREAMS_PUSH_PARAMS,
                             BOOST_IOSTREAMS_PUSH_ARGS )
    T& operator*() { return *this->component(); }
    T* operator->() { return this->component(); }
private:
    void open_impl(const T& t BOOST_IOSTREAMS_PUSH_PARAMS())
        {   // Used for forwarding.
            if (this->is_open())
                boost::throw_exception(
                    BOOST_IOSTREAMS_FAILURE("already open")
                );
            base_type::open(t BOOST_IOSTREAMS_PUSH_ARGS());
        }
};

} } // End namespaces iostreams, boost.

#endif // #ifdef BOOST_IOSTREAMS_BROKEN_OVERLOAD_RESOLUTION

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_STREAM_BUFFER_HPP_INCLUDED

/* stream_buffer.hpp
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
*/