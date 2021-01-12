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
SQXk0ddQZ0jJGY8i4Om/TWqzsW4zQTezRM6Li7uWOWNzwj8j1WAO7SHy4tY9PJekrUyDIJRFVUYomHrI4ryvckkLeNcGAVAoY0kdWJ03YD1Nkqo61BLdPx5L9HNRxqT3ryxZo891cI3e2Gmv0fl8Vw7Am0BnMsLlCEutSKVdIfEIj0G4EOF7b74bb2Dh6NhYunRhIrxkfqr/1aqAOWaEz2+1vsK63pU2B9KXmIfz3kHrKPGI
*/