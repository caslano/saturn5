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
OLyI+rTXRSUHrXjEWsXie79mnDhxoV9tFnfxWO5X+PK7ksXBDmj3fctgV+lCR2F9x+dXRFs3Wmoz2usXLLdAZvLzTz7k5++U5OcfsGLrLyhBzbSCaLu+l4roz13Qu8JXQuhukX4I16CZL+ebaV1emjdhH+9N2woidC+OcsrRtGaqke0m0+Cq6BMwyF5GudDY4Ytl0ZCLlR8f3bEJYOhQC7fSPamjF2RmV0tkPiXSBy26fMu6/OIuuWEkYuQ3IWzg15cg92d6LK3Z8agshh8M3UytrA0Dze2MTyFTkU7kzDc5tUeXqIkvj+DJmxJhU2q1EaQiTBnCOVmHF4rTEWFpBtwlVfbWsr17kl+1Lh+jxMbt1nreZ3lRcXrOV7VRLMKufKzCIEzX19sNzpjq1w2gqCP4wx9O60qAWW5OzwQQ7yMgkJGZIpDoY/M+d+Ywrvgdz/2c9iZ7/MP5/ejmI14omHjKVF98c+7GT+Tj/ZU20kW2eNzvebC/be5GJOtj5VX58FWcZcKCR88ofqrCiTQRPKVVQHtoawaQzfOJN+nsW9KZ0J1Yj+PQZMObur28TmuZ4uyMJjs+y8iZ4XOxNZ3MTu2hbXCT92S6YXO07dVXb3gUSKr89E6UnE2ufk0NVftShV/Vx822Q1lgCLvpr3mJ/AI73qe+LkDj4IN6KeSGr3m65ADXEi1gZ4nze1XzSn/yYOlDDtJ23Anzogb9
*/