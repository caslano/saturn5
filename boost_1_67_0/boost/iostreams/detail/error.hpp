// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              
                 
#include <boost/iostreams/detail/ios.hpp>  // failure.

namespace boost { namespace iostreams { namespace detail {

inline BOOST_IOSTREAMS_FAILURE cant_read() 
{ return BOOST_IOSTREAMS_FAILURE("no read access"); }

inline BOOST_IOSTREAMS_FAILURE cant_write() 
{ return BOOST_IOSTREAMS_FAILURE("no write access"); }

inline BOOST_IOSTREAMS_FAILURE cant_seek() 
{ return BOOST_IOSTREAMS_FAILURE("no random access"); }

inline BOOST_IOSTREAMS_FAILURE bad_read() 
{ return BOOST_IOSTREAMS_FAILURE("bad read"); }

inline BOOST_IOSTREAMS_FAILURE bad_putback() 
{ return BOOST_IOSTREAMS_FAILURE("putback buffer full"); }

inline BOOST_IOSTREAMS_FAILURE bad_write() 
{ return BOOST_IOSTREAMS_FAILURE("bad write"); }

inline BOOST_IOSTREAMS_FAILURE write_area_exhausted() 
{ return BOOST_IOSTREAMS_FAILURE("write area exhausted"); }

inline BOOST_IOSTREAMS_FAILURE bad_seek() 
{ return BOOST_IOSTREAMS_FAILURE("bad seek"); }

} } } // End namespaces detail, iostreams, boost.

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ERROR_HPP_INCLUDED

/* error.hpp
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
*/