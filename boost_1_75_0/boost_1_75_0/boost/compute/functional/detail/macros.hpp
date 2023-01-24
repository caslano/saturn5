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
SrzPNxd9RmLlb8aty93AfR6elvUh/IqcFOu92dzcVC9zs22e8jSKTHsH1GmWiE3RfveFkJ4G/cipaerssPXTbS+f8H8w0qNRfue3+W9Kq0rk/SX/8kTxBltoFKC5+mLTDSWp/Bbc+oquN9J5B7OEyoeszbzgJqjrQEbN4Y5NquaroCLxZshuxly7xEnMeb7iaZZ1UxaXGdbj9HmlxuVD10iezgYwcLTKGeXh/WZZg6BAh87Q+YyQqMx8b96FacHaTw3pkO78qIjByCcGiI9D2ovFmy27pbRskmkW7JLg6xPE1/RfjVanJgzhll+RkqcnEmCWPv67tDUR8sv4Z9oIZ/BdDaHlrX95l+PYJmyPC22S4zkJbMtAr/B0Kl7NpeOSSuHVW16/c94EcXstYDvLyUkOORGOUZ90N4cj5JKFRrB8v0aWGx5FMc88939ptvuwBn/cJ081qTOMzizW3HnwQTBY/Z1s2eBK5Ur88ShE/4/xwVmPuKqeUVhpdGFq/VDN4kVHk6RzW+oeCox68x1GjvYI8PzL8F/iXSp3PEazpbU9FW0tCu8sQp7Nx3Ijb00oTfc5EAZVejwH6U+BgKW9xsCzLp5bozcpoftuC/T/lQX+cak7qlhThP03UUbW8rlNCc3uiYRO/65V1/UpfYG+rP5XnTP4et1oXjhDlcmUu/ImUjvn4eFezR5E5Mp4Vli9wjQWn97YEA7bzlNW
*/