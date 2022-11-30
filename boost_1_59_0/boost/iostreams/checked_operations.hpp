// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

// Contains implementations of get, read, put, write and seek which
// check a device's mode at runtime instead of compile time.

#ifndef BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED

#include <boost/iostreams/categories.hpp>
#include <boost/iostreams/detail/dispatch.hpp>
#include <boost/iostreams/detail/error.hpp>
#include <boost/iostreams/detail/config/unreachable_return.hpp>
#include <boost/iostreams/get.hpp>
#include <boost/iostreams/put.hpp>
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/traits.hpp>
#include <boost/iostreams/write.hpp>
#include <boost/throw_exception.hpp>

// Must come last.
#include <boost/iostreams/detail/config/disable_warnings.hpp>  // MSVC.

namespace boost { namespace iostreams {

namespace detail {

template<typename T> 
struct read_write_if_impl;

template<typename T> 
struct seek_if_impl;

} // End namespace detail.

template<typename T>
typename int_type_of<T>::type get_if(T& t)
{ 
    typedef typename detail::dispatch<T, input, output>::type tag;
    return detail::read_write_if_impl<tag>::get(t);
}

template<typename T>
inline std::streamsize
read_if(T& t, typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, input, output>::type tag;
    return detail::read_write_if_impl<tag>::read(t, s, n);
}

template<typename T>
bool put_if(T& t, typename char_type_of<T>::type c)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::put(t, c);
}

template<typename T>
inline std::streamsize write_if
    (T& t, const typename char_type_of<T>::type* s, std::streamsize n)
{ 
    typedef typename detail::dispatch<T, output, input>::type tag;
    return detail::read_write_if_impl<tag>::write(t, s, n);
}

template<typename T>
inline std::streampos
seek_if( T& t, stream_offset off, BOOST_IOS::seekdir way, 
         BOOST_IOS::openmode which = BOOST_IOS::in | BOOST_IOS::out )
{ 
    using namespace detail;
    typedef typename dispatch<T, random_access, any_tag>::type tag;
    return seek_if_impl<tag>::seek(t, off, way, which);
}

namespace detail {

//------------------Specializations of read_write_if_impl---------------------//

template<>
struct read_write_if_impl<input> {
    template<typename T>
    static typename int_type_of<T>::type get(T& t)
    { return iostreams::get(t); }

    template<typename T>
    static std::streamsize
    read(T& t, typename char_type_of<T>::type* s, std::streamsize n)
    { return iostreams::read(t, s, n); }

    template<typename T>
    static bool put(T&, typename char_type_of<T>::type)
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(false) }

    template<typename T>
    static std::streamsize 
    write(T&, const typename char_type_of<T>::type*, std::streamsize)
    { boost::throw_exception(cant_write());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }
};

template<>
struct read_write_if_impl<output> {
    template<typename T>
    static typename int_type_of<T>::type get(T&)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename T>
    static std::streamsize
    read(T&, typename char_type_of<T>::type*, std::streamsize)
    { boost::throw_exception(cant_read());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(0) }

    template<typename T>
    static bool put(T& t, typename char_type_of<T>::type c)
    { return iostreams::put(t, c); }

    template<typename T>
    static std::streamsize 
    write( T& t, const typename char_type_of<T>::type* s, 
           std::streamsize n )
    { return iostreams::write(t, s, n); }
};

//------------------Specializations of seek_if_impl---------------------------//

template<>
struct seek_if_impl<random_access> {
    template<typename T>
    static std::streampos 
    seek( T& t, stream_offset off, BOOST_IOS::seekdir way, 
          BOOST_IOS::openmode which )
    { return iostreams::seek(t, off, way, which); }
};

template<>
struct seek_if_impl<any_tag> {
    template<typename T>
    static std::streampos 
    seek(T&, stream_offset, BOOST_IOS::seekdir, BOOST_IOS::openmode)
    { boost::throw_exception(cant_seek());
      BOOST_IOSTREAMS_UNREACHABLE_RETURN(std::streampos()) }
};

} // End namespace detail.

} } // End namespaces iostreams, boost.

#include <boost/iostreams/detail/config/enable_warnings.hpp>  // MSVC.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_CHECKED_OPERATIONS_HPP_INCLUDED

/* checked_operations.hpp
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
*/