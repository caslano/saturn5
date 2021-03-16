// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    

#define BOOST_IOSTREAMS_PUSH_PARAMS() \
    , std::streamsize buffer_size = -1 , std::streamsize pback_size = -1 \
    /**/

#define BOOST_IOSTREAMS_PUSH_ARGS() , buffer_size, pback_size     

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED

/* push_params.hpp
bvr/YBnQS3kLjWST3EOZXqumYvz4SdMmlhvXRl1tjLluSFT9BicTKi81J/K8f6GmDciTDmEgkPq/w4ElwEF54vdzMHAS8AggOZY6Mk82fY8C0iZ+MfB1YAmQhqej88TQ6Jg8ORJ/LJDq5zjtu+zfEfMh/Zsb/rOWtsnSWvflwbVn7V6hzVXH8hcRo5nDilbbPIvebv7CS4MxelbM4UYyrWlalvHoUGO3LyNWWiLgbYk57Jp27MbiXtQOmqnH3Uo=
*/