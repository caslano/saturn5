/*!
@file
Documents the `BOOST_HANA_ADAPT_ADT` macro.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_ADAPT_ADT_HPP
#define BOOST_HANA_FWD_ADAPT_ADT_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    // Note:
    // The weird definition as a variable seems to exploit a glitch in Doxygen
    // which makes the macro appear in the related objects of Struct (as we
    // want it to).

    //! Defines a model of `Struct` with the given accessors.
    //! @ingroup group-Struct
    //!
    //! Using this macro at _global scope_ will define a model of the `Struct`
    //! concept for the given type. This can be used to easily adapt existing
    //! user-defined types in a ad-hoc manner. Unlike `BOOST_HANA_ADAPT_STRUCT`,
    //! this macro requires specifying the way to retrieve each member by
    //! providing a function that does the extraction.
    //!
    //! @note
    //! This macro only works if the tag of the user-defined type `T` is `T`
    //! itself. This is the case unless you specifically asked for something
    //! different; see `tag_of`'s documentation.
    //!
    //!
    //! Example
    //! -------
    //! @include example/adapt_adt.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    auto BOOST_HANA_ADAPT_ADT(...) = ;
    #define BOOST_HANA_ADAPT_ADT(Name, ...) see documentation
#else
    // defined in <boost/hana/adapt_adt.hpp>
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_ADAPT_ADT_HPP

/* adapt_adt.hpp
HsxHQ7xC6O2Hk4V4myLw9aiyzxi/dLaL/1CVdcZp3ACS2p8stf4YnOloFFmz+D6qqRCH7FTm3dpa8tXg/csiYd/uUHZNBP4Dtnivmowf36dUJex0rQr6c0ulQr5ac17xHp191NWd+BvibhhEvJtL7vA367/YW19XCXTCf//HGti/RYS4wPOp34NZz/j6Ipmy6Uv43rSJQNPDojPidv5xX4N4mxozD2J/oH115/VYIk87Tw1gPSNp52D0ofnopw0tNH7bVJbjhLJDXuCPYEvOKC7gzUxf3M17hkviYrdLZbsIbT17wP3WDnurjKrlAjEthPf80cKWXCv2hkECXoTA8hzB3o8X59YEvfNOtuV7CPxr2FbdU1XWyVTYwj74Sy6wnr2UutYJf8RQpTJH8D3YcTX0eo2wXXl2+aQk3yMyl91slOrXRm3s78V8EGszoY36hYVI3Yy9FYN+3xd+t+15L69s+3lCFHiiduci/ZNUgR+0tvOZUk6LeB/rzHppJNApXX1bslOICWymmxBXrKYmT+zn/W4fvo83UXZ9lC3vwwTewz4ok/gvQZAVb8RgIy6G+SiQOWljagmBu2+FiHPDf2ApVj3vqcwMMOKzRqgOqT8sIv5GP05Wt+S9Ld9/XOY9UgWVfcUyPJ+C/xR9Y8ErjdUqB74ndpFAtVFhcydYiQH+g1ZzlI2ZomxRuvDAGP9fHeL7YwU2BolBzdaq5tuQeDIvEcr4Y19O4/uPCjbil1+p1ae5L92MJF+6UjGR6ONv1W7rd8RrG2B/MFaF8N00r6xqVUqJ6XD8SAt6C/S/JOwBLr7aY4Q9wt7yYC5bUS0Pi/8JgZsNvFCzeIL/oLGyPug0EXZa2aMy1JD9IdGtHc33sKOE+M3tvM4KBaO2ujoC+3IvFpB5hMqWL1CNuqvQNw7hDyuCfVlWZak4wBKP8X6ch2278c1dmIu//b4auueDv+4xNqyn6BYxodWH8T6xGJqlDe8xC7P+puKP+MB7uFCBxj/FuVeawF1cB+FnbP/yPfvgQ9iXqNOGggJZZcV0LIu1b1neJ9YQ9st2c60/1tDPK5bYRwLPagkM57V1D7ZuZ0yFdn9QqhWeJ7P9vGdAB5l03lHdN+N7iGaS7w3RkWDOWHfku2rNfZ6P9WIi0Jax6jGD9+hM47XfvBfdIVaZKMePWbFZfJxqTo+eLOV7HAz8nbyr77hPZYvb8/10GJHgKnxPUoL3k/RyFaKdzoO/c74Qq8ei33OlDrHmvQXZ6/WUiuPGvjhG2aelmY9WfG96HfujvLK/uO1buKpaLj6SrxiuJq0n8P0WJI/hMqmtGBx9qWpPjqBv8DrQlTP78C/87VbEuwtacf+KJJ027m5hPvg0ZSl6zsK8wr7AjJzOm/xWjKTfEUsJVMNJ48ekuFYWeJpkKvk2qNogzpeVf3BQNUgWMCQXOgjRAI//Ce7kkviuHzuoxiRi+TvuqgsdBig1lF12e7hk6cdA+MzHXu2ssjAu614biB9txf9yD/00A/sIN8sAU+7zUmotsjr30SNhZ3RgvdS1xL+BvtuO+5zPoGpu5vvBjY68J2R+H5prfuFcsTb6c1Pst/G8B+ZFY+RazlMaP7tXqbq/s/1Xau0GXKJyKjWfpZLYlfcqEN8FMbth9ns9J8mXyPcaB4nXbsFeXSP2R+egD+HCLNiG/jJ554gatUH5bD6MeN5ysfqFVN8IsY9Ga24QgT+RLyJv9VJ2M1/9tuK4OVpG4h76gP+ZXTFvlcTtd5vvk7kNLrVn/HLSX6623duJB8SrrAgLOC3VnN+TwV5gKb+ezfnnJnB9umQ+iXzB3tir4Zz3o5Sqac77pp8ChelqmXzsfVTOTfw=
*/