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
87xhRf/0mpqaJZ+0uoT+noA4hepXTqH+xvLEzH3Acn2hUV/ZDyflhfjo+LLYojPANqoUt5sRwQqN8mHfgjPofwnHNvKA97EcVeKp7WgG6gL+qZpv8OtBjI6viLHW41r9RWlRcerq3Es/92zsvIPyap5NsfvqhPBNKE9k8bscu0oMbkI+9Qn6gYmq7pYQtwGvPsVS9rPZRnWz7U9jduGzMMfMWpgpDLDKENhB/bSfb7daRZCD
*/