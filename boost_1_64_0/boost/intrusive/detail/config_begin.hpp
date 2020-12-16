/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2006-2013
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#ifdef BOOST_MSVC

   #pragma warning (push)
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4996) // "function": was declared deprecated
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4521) ////Disable "multiple copy constructors specified"
   #pragma warning (disable : 4127) //conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4267) //conversion from 'X' to 'Y', possible loss of data
   #pragma warning (disable : 4541) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4512) //'typeid' used on polymorphic type 'boost::exception' with /GR-
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4706) //assignment within conditional expression
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4714) // "function": marked as __forceinline not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
#endif

//#define BOOST_INTRUSIVE_USE_ITERATOR_FACADE
//#define BOOST_INTRUSIVE_USE_ITERATOR_ENABLE_IF_CONVERTIBLE

/* config_begin.hpp
hvTIs3ceKRgH0+S6bAKTYVOYAtO1+ZOKJL3xkp5pHf6zYIzMP1MLngNtvbNhKmwn9tVernOk6DzYEQ6Q8OEwA46U+KNgJzjO3pb8tHK+tcm7JxKlyiNjqKR8KaKfLt+6RJ9nHP95RHjecfTiw9RLD1Ovg6ZXEOWvd5GWv8ww9bLD1MsJU68gTL2iSvS6hzkPy5Yi9gfMwTJ0tTvseViqOgfLItKuaB6Wu1a7w56L5T8xD8vR1e7/+Fws4czD4rnDrc3FUvEcLBnoZiPeuVjCn4dF5mCpaP4VmXvFPO9K4R3usOdeCWfelZWkV8HcK868KyXo6XOvHGHbNP/KccKXQ+/8K1Wbe6X+ne6A+Vf+P+ZeyaLcgfOvTLDrgr8P3azPvVK1eVeyzvFY+chdyB6kDKl/rsfqh+Qjq5BS5AgSfZ7H6oCMRZYg65A9yFEkqQvztiBjkUXIWmQPchSp39VjdUemdI3MtxL5RX6n8vMgl/3I4/8LJ9qwR/+f+tj/rGQraA30S6J4NocD4dOkXbyljjNuJHfBInsF0Nm+sSKz4pV/wQLdJ/J5pd8pyjhWfkvQWslqzbj1rC2zR+3rGuVbC+dptX2OMyZ95FNqHWTvNn/9RW0bx75ynEAfBhbOy1PZdtZV/kzpPOPqzRv7UWt0sM9CcDr8WNpgxhTbcVLpryPf4nPKLzd/Ru58x19hvMpfA2eNhcvVtkelVSvF67cow24sX5nfe1L5d6g6WUvaX6nj14jSfN0cX5B0pbvXNYc3qiauSyUc33sVnuVqaxXybfF2dby/1LPjzpkxZb7qplF53yh5L1DpTp0xb34hur3VOYtWaZznusFqLmG+dP/Ce80K8ucrQ+G8BRIvia33VX5Lefe6wSlTBxVvhOgEpEM5i8nHBypeapTUpa+enXWZrlN1N0X5fmxhe4WbMZRUcpxncVx09TjX4BBrSyaKfgn6m239mkXrg8YIis6HTppLz1SJjqhgfV6JE+3xpbt0bGC649m27WgQ/wxGhiBPsm8X+kP5GyIqLGT4MIkzXGjLCzLeeUqYazv5+rLsazVZXatB6zgH+Kvo10qCsnEVrtk+4cp+sCvCxa4CfIkPylr3a13e9/9l8HzKUby1vD2ZM3l+wYwp0qT4tSmTCvT153erODNdvVyJ5jk4tga1K46/0w61b4FrkCve2FYQ17nGPcqmR2X17li+7tZHcp20UqWyV8Mpb+v+pOLmOP6gSdvt7YaqHOnqcWpK3jzNd/ZZpV/oynLVMa652nub17d2pHVuUJqJepp4puq+USdUujEqv0fIr3ctWbmOJqmT4+T5dnUMY/rkR9LnLOvpf0T6aKrr9UPS/1pt92es6XiuBa9dbkW+Q3mN8JfIjWLHaxGbf6zrDX8WeUbbLzrKrtPDtGt7HBl518ZV6naO/ZjtXJ1PTwrb2nkmXNUb9Uu41K+z3ov4mUYHzY2j7Llku2PPwfdGyYfBZokXZLPB9qnrSfvydBhrTYdTF+JD6zemuSnPAJ1hY3guGTgYWLaJeYuCrlPNtuo8rdaN9Rh9/g3lddbEU/FmeYLKr8WT9f35a/YsWTRIxa8L31c6E61Uih/ni0NpJrkfsNI9c60DnmT9vu6kWdtJc7KdpHO/+Ujtr1YtjfTitfSauPqxXsb5QWmKjmnNcmdN3K/V/m89dvkT1f58Zwx4gSr/Muomhe+RWYFtg9KfssPWGc532DrYJGFs/VaFdXTXwRrP58vyKr7Ot3f15UPoA1bPqLlWaVSi9feoZCveXaP8+qb+pIV32sgodfzfeV6nN07dt9l67Tlpy8j/cfJ/ttJ5wVNbxu+QTt40rY3op/IS7+S3ltpOwc6qOWs=
*/