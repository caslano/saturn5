// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif              

#include <boost/config.hpp>                // BOOST_NO_SFINAE.
#include <boost/utility/enable_if.hpp>                  
#include <boost/iostreams/traits_fwd.hpp>  // is_std_io.

#if !defined(BOOST_NO_SFINAE) && \
    !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x592))
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T) \
    , typename boost::enable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T) \
    , typename boost::disable_if< boost::iostreams::is_std_io<T> >::type* = 0 \
    /**/
#else 
# define BOOST_IOSTREAMS_ENABLE_IF_STREAM(T)
# define BOOST_IOSTREAMS_DISABLE_IF_STREAM(T)
#endif

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_ENABLE_IF_STREAM_HPP_INCLUDED

/* enable_if_stream.hpp
jWNsHmxFrgIfzg+RajX3JfMaDy7CyXvNXE5gmT1F6t/ICYJaTA1ZmUVNFIFxkspmCTZljrQmKRSJoSJo8oMGBoE4mFpfL7TY67TkBcUgdNL+hQ38XVQn9rgYS24ESdZadzC4HfS6991eNHd/0C1Hev1UTuNbz9dlJuGTPU3CcWL4phNwtjE1yxZHMC+p1A3fkuGr9HvELTF9pe9W4bsSDSKBVqfIwwlq8K0waFecP93XtO2V7qXnkUbePMLxy0VL9Ow45byyghXFYqEPl6wp/2p3Viryb+7QYh3jLXn2mFGHgjGoKV/kQ+mOuxbJ204W+KERyPRSKhays8ZalxTifIin7/RuiUVZQqi8V5FbIKPe9VuxVs+8ccb7MORoiXAnjZo5mY1e5vdSqgEpjZl0IkeMHP2RtOa9k+aFR9KjDBOl5sxo3798K4YhaReFzcKTatjWpOaZk7V80uBKbWThOb4FNS0sTXJNDNrHvNLal0kRuUN02ettHiJMJ9lRUjoWjpLst91ARZ3KsNpxrCJ9VodrldUehivXDFuvA9QYXq3ZvnEUD3KWORknWYnhuE+hf2znGCXhd/SJgtjNctmDO+wxcksMCzjfStxuHhnotXXUlmSye8wWxOs3GKIV9beI1mw5dVK0LN/jkjZn
*/