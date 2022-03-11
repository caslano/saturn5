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