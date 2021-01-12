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
JC/HB4ym+OtynwcGdyJve1bAIhsk51rmPw6/eS504jUspuokameN4BtN8rdzjZBtEG52TW9oCoKV6Ab5JdtADJhy7auhzpKMrUdBBHsGCqFhg0RGZjY0RVkcObRiwArMdxgBsx7EqsY0NDQhqsx67g1B1dQb6iQyMn1DkyIlm1sq8DP5O+g+uT5gycJ9HYiYk09PvT7wrdff7rG3nGp3SDnUZWgp7K66LVq0sFfZgDCLwkCU
*/