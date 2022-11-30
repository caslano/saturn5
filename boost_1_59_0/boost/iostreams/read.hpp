// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_READ_HPP_INCLUDED
#define BOOST_IOSTREAMS_READ_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/char_traits.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>  // streamsize.
#include <boost/iostreams/detail/streambuf.hpp>
#include <boost/iostreams/detail/wrap_unwrap.hpp>
#include <boost/iostreams/operations_fwd.hpp>
#include <boost/mpl/if.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>

namespace boost { namespace iostreams {

namespace detail {

template<typename T>
struct read_device_impl;

template<typename T>
struct read_filter_impl;

} // End namespace detail.

template<typename T>
typename int_type_of<T>::type get(T& t)
{ return detail::read_device_impl<T>::get(detail::unwrap(t)); }

template<typename T>
inline std::streamsize
read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::read_device_impl<T>::read(detail::unwrap(t), s, n); }

template<typename T, typename Source>
std::streamsize
read(T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::read_filter_impl<T>::read(detail::unwrap(t), src, s, n); }

template<typename T>
bool putback(T& t, typename char_type_of<T>::type c)
{ return detail::read_device_impl<T>::putback(detail::unwrap(t), c); }

//----------------------------------------------------------------------------//

namespace detail {

// Helper function for adding -1 as EOF indicator.
inline std::streamsize check_eof(std::streamsize n) { return n != 0 ? n : -1; }

// Helper templates for reading from streambufs.
template<bool IsLinked>
struct true_eof_impl;

template<>
struct true_eof_impl<true> {
    template<typename T>
    static bool true_eof(T& t) { return t.true_eof(); }
};

template<>
struct true_eof_impl<false> {
    template<typename T>
    static bool true_eof(T&) { return true; }
};

template<typename T>
inline bool true_eof(T& t)
{
    const bool linked = is_linked<T>::value;
    return true_eof_impl<linked>::true_eof(t);
}

//------------------Definition of read_device_impl----------------------------//

template<typename T>
struct read_device_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_device_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, istream_tag, streambuf_tag, input
              >::type
          >
      >::type
    { };

template<>
struct read_device_impl<istream_tag> {
    template<typename T>
    static typename int_type_of<T>::type get(T& t)
    { return t.get(); }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return check_eof(t.rdbuf()->sgetn(s, n)); }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type( t.rdbuf()->sputbackc(c),
                                          traits_type::eof() );
    }
};

template<>
struct read_device_impl<streambuf_tag> {
    template<typename T>
    static typename int_type_of<T>::type
    get(T& t)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        typename int_type_of<T>::type c;
        return !traits_type::is_eof(c = t.sbumpc()) ||
                detail::true_eof(t)
                    ?
                c : traits_type::would_block();
    }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    {
        std::streamsize amt;
        return (amt = t.sgetn(s, n)) != 0 ?
            amt :
            detail::true_eof(t) ?
                -1 :
                0;
    }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        return !traits_type::is_eof(t.sputbackc(c));
    }
};

template<>
struct read_device_impl<input> {
    template<typename T>
    static typename int_type_of<T>::type
    get(T& t)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        char_type c;
        std::streamsize amt;
        return (amt = t.read(&c, 1)) == 1 ?
            traits_type::to_int_type(c) :
            amt == -1 ?
                traits_type::eof() :
                traits_type::would_block();
    }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return t.read(s, n); }

    template<typename T>
    static bool putback(T& t, typename char_type_of<T>::type c)
    {   // T must be Peekable.
        return t.putback(c);
    }
};

//------------------Definition of read_filter_impl----------------------------//

template<typename T>
struct read_filter_impl
    : mpl::if_<
          detail::is_custom<T>,
          operations<T>,
          read_filter_impl<
              BOOST_DEDUCED_TYPENAME
              detail::dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct read_filter_impl<multichar_tag> {
    template<typename T, typename Source>
    static std::streamsize read
       (T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
    { return t.read(src, s, n); }
};

template<>
struct read_filter_impl<any_tag> {
    template<typename T, typename Source>
    static std::streamsize read
       (T& t, Source& src, typename char_type_of<T>::type* s, std::streamsize n)
    {   // gcc 2.95 needs namespace qualification for char_traits.
        typedef typename char_type_of<T>::type     char_type;
        typedef iostreams::char_traits<char_type>  traits_type;
        for (std::streamsize off = 0; off < n; ++off) {
            typename traits_type::int_type c = t.get(src);
            if (traits_type::is_eof(c))
                return check_eof(off);
            if (traits_type::would_block(c))
                return off;
            s[off] = traits_type::to_char_type(c);
        }
        return n;
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_READ_HPP_INCLUDED

/* read.hpp
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
*/