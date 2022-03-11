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