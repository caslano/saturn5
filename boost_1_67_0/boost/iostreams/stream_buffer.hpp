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