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
95BXUErtFj0fs0e158ak8ITSIXP+alNVsPgCzLefovnwPout9Ay9ZPSyBv+WwlrpjocXXtboV1qie+ngzbND0dSbtUPJ6a+UHYqxCuywGtdPMOPW3TdNzlsH5x6m0jVenZ+O8/y6VHIs7dlFaKV9Ox/gyd5dzh6lJ4vSHr6lPcrPXaW9fK1B97L3m6RwdXu1IInDvKZInUxtWy7mz5NbHPwkvMU8WxcLVbzzwemjw0z83sJHps/ouZjCqvKwLfn9tSFP5P/+hvzqyV2r38ivhrr4h+/xZAif5eUQ+FSR10TwYXSxAh/Hlyx+W5UjugJwvtr0YLTkWFRB3Ozp9ZZC92oNHV5CVklr9bWk/L6yQn+6BhpIf1RIz9aTniqk9eN1pOJKb0RaX0vaUEkba0lVterNtaQ/pkiFyQpIX6VJG2tIz1bHONoZzRl+3CqNhIyqKD16dxzvYgrSVjOHVJ6zSZGqjqe4dA57cRwgiymeprlHW2FpyuhpAftb3M/KYxvvH1XJUF5TYTyObyFIh8MeYW7oGzRdj6YxZETGCCIPGCEL3AXeuoruQGSugzD1ykQgdtwI7qhF9SoHT3747ctK5/zodV9cabnCFcKbo4L7gr/Kex6/5UBduT6htVktFh1gR7rnsdGH+2G9WcnR
*/