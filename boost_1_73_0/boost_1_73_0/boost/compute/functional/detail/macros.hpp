//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP
#define BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/stringize.hpp>

#include <boost/compute/function.hpp>

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(name, signature, template_args) \
    template<template_args> \
    class name : public function<signature> \
    { \
    public: \
        (name)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#define BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(name, signature, template_args) \
    template<template_args> \
    class BOOST_PP_CAT(name, _) : public function<signature> \
    { \
    public: \
        BOOST_PP_CAT(name, _)() : function<signature>(BOOST_PP_STRINGIZE(name)) { } \
    };

#endif // BOOST_COMPUTE_FUNCTIONAL_MACROS_HPP

/* macros.hpp
6hebbmTFUEUM12GKWN4YLkPdoxThjIxQhBOSp4j13VGSFTuJFTu5FO8krJSwZYStJOwRwtYS9gxhvyesq6JiyYqKcS/UFTjkIw1sRzvSbxdGpEJGZPD5kT+yUGWQLlOM6taHp0PQ+YzEhOTmtbKV5CwsxetbPfxbXsXC9qBYsbzqUz4gtfQaqZUfZGJF4zEmAh0PMbGS8TATq1cwK9b2lsdRvBtJvBsVddALrJCwxYQtJex+wtYQ9k/CThMm/cw=
*/