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
alX+m5hD3aWj/sO+lqibhze0EE9Eoajy3XCoVm0O3j1lXWxggHfJAZ6A+CYfEDK+2dd9I1xvfbsMkNvAulWU2QE9yeTidRLThBqh64vzZbl7XIKv1YBKLiESaFGJaHHOLgrj63VfzfgTwQmvlVDK4djcsb92ayw0avdPjO5vnVxI444Ckvjzqm54IgB5R3/WiWgKUknwLVcphIvZ8HWvBX9CMmTRYhpTT3wEnB8vjb2hQ38bfua43Idy1ueqgsqMfWlntd2dZ55nv4PX93SCDxFV+DfxbsjQVDrz+VRMNXW9hgw9EkRZUQ6JQidju8Kckjf+votBSWGmSYFNRYkUzB9AaBK40VuX3mBfgaZPxcCb3SJXX6d28/+/3r1ecxFy4Bx0zH9aDs5apfRt8tS1UmHbQhGkwx8oN/D0ae28YiIa3+CyXELEwyaDDOHFSy7eTwOdRWsSCDOJgSFgbHFjULSsLw2mqJbcsNMr+TbK/6nuWdTH4QqolVNW5GEIWtAEI3dirjTc9wYP4EeIEqGVm3k9zX48Jed/gjCZUsXxCkpAA+avprhHrqJs7A==
*/