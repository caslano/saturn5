// Copyright Daniel Wallin 2006.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FUNCTION_DISPATCH_TUPLE_HPP

#include <boost/preprocessor/tuple/elem.hpp>

// Accessor macros for the input tuple to the dispatch macros.
#define BOOST_PARAMETER_FUNCTION_DISPATCH_BASE_NAME(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 0, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_SPLIT_ARGS(x)                      \
    BOOST_PP_TUPLE_ELEM(5, 1, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_MEMBER(x)                       \
    BOOST_PP_TUPLE_ELEM(5, 2, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_IS_CONST(x)                        \
    BOOST_PP_TUPLE_ELEM(5, 3, x)
/**/

#define BOOST_PARAMETER_FUNCTION_DISPATCH_TAG_NAMESPACE(x)                   \
    BOOST_PP_TUPLE_ELEM(5, 4, x)
/**/

#endif  // include guard


/* function_dispatch_tuple.hpp
anWp0BOojLh/8LaM/Ero9fDElDWEjwLcjqGjxoKZZbmkIMIVjouPLqHj8HtgvG0i6sZuYLVbM/oXm+rPlzYnkaFZXr5JoGmrJwr3sS/sqdzqx6K9aCYYKxSgo+fIwibBnVWkI4pz94Xkg1TPjQZqweowJ7BM7+5CU/VleEExvoMawfTXhZe41rISiCnkQPx8yoDsiQTywO9g4Qktyie81L9b2dgo/bXF9XyEobOAhmf0HUJWtI+sUblG/2TLnIjeT1609fJq+ZGpT7KL3uHw8wDstdzYYtEaTw3bqkcfNerkfCYeasHpv+sKuYt6Y8Ft3KLPgEU0BmU+n3crJikxZtVBhd0ME1MCe4iXZiOq2NeMeyG4p0/UoUuyp4RCUMqMluNwZeqAw91+J010cLeeWuKlbo7XY+hnBv7PRTNdVEvu7m8AdKxymZKtyn0q81CQjNB1EbUulMeuPc7c5hWgl5Z2dgG7c5zgQTWOwGVElLlM1OEEgCq/u9jAfVSkbphDnIxuxIwJGBefgqNK6d9vKw/lpJtNryvxzZF81oZpyqIeFWz4rMPH2miCiw==
*/