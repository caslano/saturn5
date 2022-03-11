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