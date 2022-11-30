// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_WRITE_HPP_INCLUDED
#define BOOST_IOSTREAMS_WRITE_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/config.hpp>  // DEDUCED_TYPENAME, MSVC.
#include <boost/detail/workaround.hpp>
#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/char_traits.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/ios.hpp>  // streamsize.
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
struct write_device_impl;

template<typename T> 
struct write_filter_impl;

} // End namespace detail.

template<typename T>
bool put(T& t, typename char_type_of<T>::type c)
{ return detail::write_device_impl<T>::put(detail::unwrap(t), c); }

template<typename T>
inline std::streamsize write
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ return detail::write_device_impl<T>::write(detail::unwrap(t), s, n); }

template<typename T, typename Sink>
inline std::streamsize
write( T& t, Sink& snk, const typename char_type_of<T>::type* s, 
       std::streamsize n )
{ return detail::write_filter_impl<T>::write(detail::unwrap(t), snk, s, n); }

namespace detail {

//------------------Definition of write_device_impl---------------------------//

template<typename T>
struct write_device_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          write_device_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, ostream_tag, streambuf_tag, output
              >::type
          >
      >::type
    { };

template<>
struct write_device_impl<ostream_tag> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type( t.rdbuf()->sputc(c),
                                          traits_type::eof() );
    }

    template<typename T>
    static std::streamsize write
        (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.rdbuf()->sputn(s, n); }
};

template<>
struct write_device_impl<streambuf_tag> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    {
        typedef typename char_type_of<T>::type          char_type;
        typedef BOOST_IOSTREAMS_CHAR_TRAITS(char_type)  traits_type;
        return !traits_type::eq_int_type(t.sputc(c), traits_type::eof());
    }

    template<typename T>
    static std::streamsize write
        (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.sputn(s, n); }
};

template<>
struct write_device_impl<output> {
    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    { return t.write(&c, 1) == 1; }

    template<typename T>
    static std::streamsize
    write(T& t, const typename char_type_of<T>::type* s, std::streamsize n)
    { return t.write(s, n); }
};

//------------------Definition of write_filter_impl---------------------------//

template<typename T>
struct write_filter_impl
    : mpl::if_<
          is_custom<T>,
          operations<T>,
          write_filter_impl<
              BOOST_DEDUCED_TYPENAME
              dispatch<
                  T, multichar_tag, any_tag
              >::type
          >
      >::type
    { };

template<>
struct write_filter_impl<multichar_tag> {
    template<typename T, typename Sink>
    static std::streamsize
    write( T& t, Sink& snk, const typename char_type_of<T>::type* s,
           std::streamsize n )
    { return t.write(snk, s, n); }
};

template<>
struct write_filter_impl<any_tag> {
    template<typename T, typename Sink>
    static std::streamsize
    write( T& t, Sink& snk, const typename char_type_of<T>::type* s,
           std::streamsize n )
    {
        for (std::streamsize off = 0; off < n; ++off)
            if (!t.put(snk, s[off]))
                return off;
        return n;
    }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>

#endif // #ifndef BOOST_IOSTREAMS_WRITE_HPP_INCLUDED

/* write.hpp
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
*/