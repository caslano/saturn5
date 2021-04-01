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
UAJ+NnfNB5s8gELDm47vmlELG9nvmvscnJvy0vQqmBYHBUqAefLszJ5dnRLHDHgdFkubawrOQPEhm0dJ4UdjQviXvLQ3q7qCgGerXuR5Rfr0v1nS4SuOHaJdsHFiKBzA+zsV6mRUZNf9K6HrxUlBe19nUiP+S+iB5fF+is9Yg372eOC9wj0CyIsVTffevHXfe81YZq83IsQQZ6/db9srAkBSA/1icW+DWoA2nQgUqHT0Ce3P8yu/jGcuQeRKeTf2jgRUfo4bsf1mEQmdY8EZuzxjIkZweCQyhvAMc/0BujqnWf2uShD7l5KIPGC/NAgCuQbX7o3vfGL38jy2uGLz4D+Xs/QsAX3zb703nI0gF3pvb8YEAmk9rTb4dsbtxAc4aYUy7nvkNfYPJMTZW12vNWzS+LvptUzWhHO1B5SApj5T5cW543W54BTADq75G7vKZC57Vr8WnzPVxx4NCqjAWMzRtmzK2B7ucSuHo60lO+SFRk053VjRmTDV8tFWhfwyClo5B2vPvEDaGMjM8u8Dv07w2grADNP0Av8FVPUkgiimoFGTsTGPHxWmHQ==
*/