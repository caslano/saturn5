//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED
#define BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED
#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

#endif   //BOOST_CONTAINER_CONTAINER_DETAIL_CONFIG_INCLUDED

#ifdef BOOST_MSVC
   #pragma warning (push)
   #pragma warning (disable : 4127) // conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4197) // top-level volatile in cast is ignored
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4267) // conversion from "X" to "Y", possible loss of data
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4290) // C++ exception specification ignored except to indicate a function is not __declspec(nothrow)
   #pragma warning (disable : 4324) // structure was padded due to __declspec(align(
   #pragma warning (disable : 4345) // behavior change: an object of POD type constructed with an initializer of the form () will be default-initialized
   #pragma warning (disable : 4355) // "this" : used in base member initializer list
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4510) //  default constructor could not be generated
   #pragma warning (disable : 4511) // copy constructor could not be generated
   #pragma warning (disable : 4512) // assignment operator could not be generated
   #pragma warning (disable : 4514) // unreferenced inline removed
   #pragma warning (disable : 4521) // Disable "multiple copy constructors specified"
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4541) // 'typeid' used on polymorphic type '' with /GR-; unpredictable behavior may result
   #pragma warning (disable : 4584) //  X is already a base-class of Y
   #pragma warning (disable : 4610) //  struct can never be instantiated - user defined constructor required
   #pragma warning (disable : 4671) //  the copy constructor is inaccessible
   #pragma warning (disable : 4673) //  throwing '' the following types will not be considered at the catch site
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4702) // unreachable code
   #pragma warning (disable : 4706) // assignment within conditional expression
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4714) // "function": marked as __forceinline not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
 
#endif   //BOOST_MSVC

/* config_begin.hpp
6wzMIKz5OStkKSxLyL3Y3tYDliPsi+v9FsdhecKapS83tcDMZC48d6vJbli+kJsZXbcxrIjMnvVy8WONcjDJJNvcoo1rW8KkZM7MurlqJ8LkQq5M482rYQoyXu9X2mlYhJDzmREwH6Yic2L2qldKFZhGyC3xLtsOpiUrzexw317PYClkPsz6dfinPyydjH/WvNZ9lD/MIOTGuL5YCcsh82SW/ulGB1iekLPYTXKEWSYJ74u3ZI6ESSbb5lZrhm2ByciCmWXUnmeCKcnKMvM91/w2LI7MhVnz3b1bwXRk/PF32Pl/PrAUIbeqc9sDsDQhN+BCl3awdCHX+n/GQ7BMMn7vlpo7y7pmFpkzfz7zCm4LM04W3sMqmkyE5QnWdUu9tTCzsObutqedYflC7rw22ANWJOTu9sg/BnOaYptTvfW5CpOR8Zxf+xH1YaFkbszKbr1WFxYh5J6fVD2CqYTccvfkvTCNkKt+9ZoPTEtWhlmvI0v/gKUJuc7jVmXBDELuv22542FGIbd4cIm+sDwhlyTN/AzLF2zEkrmnYE5Tbe28/ccmsFCy0symP5+3BBYh5G498+gO05DxM0o8k3MMphVyv3/qthiWJtS7MX9kV5iBzIVZ0LRZbWBZQu7j/pjRMCMZ37OJDd5Ew/LIPJj17fqoGcwizJBez1UOKyCTMgt0DFfAnKbZvo6NqhfVAiYj47kd4zLrwBSCRWpGyGAqMj7DwqR2VtMIucKQjwEwndDLg4LsnTC9kAtp1esCzEDmyczXYYoDLEfILY64kQfLI3Ni1qHLy+ows5A7qk6+BisQch+P3/OFSVJtc27VvppgMjKe+0sd6w0LFXI3JAlpMKWQ63x6aChMLeT6j8+fDdMKuSt/flXAUoScfN7+n8/JQq5/r0susEwht+BdwyiYUcgNSg4bC8sTcukdF+2GWYTc3Sd+zWEFQq5CuGw/zGG67etKla0JQTApGX/8ra/80pqTk3kye/b6ZDosQsh1WXKvPUwl5GquqSqBxZFVYNZYefMuLI3Mn9ks6fVCWBZZCLNdw/csh10T5nsyrMYYmEXIjXz+2Rnmmmb7unl+Q/ZYmIyM5x69f9IYpiLjs0+M3H4YphFyvaVzs2FpZEHMVvXeoIflkFVhdtB7pgpmEep9Ltz1FFZAFsZssNnDARY6w7bejusNtsLUZDy3VRm5CJZG5srso8/+mTCDkGscG7sOZiJzY1bDPeAmzCLkJh+qWxsmm2l77U6d1e8CTEHGZ9/0wLMjTEnmxcxn0NspMI2w5oocty0wHRnvU789tj1MTyZjlnRktbWXTDJ3ZuMbTmsByxFy0yqNz4GZyJyZrYzPUsMsQu6i5eUImGSW7WPFv/aBJFgoGc9VHufuBFOR8XrTO/m+hmmEXMKgSgpYilBv2pWr12CZQm7Om9MxsFyh3vCQvoNgJjJ+DnFVF/WA5ZMFMqsZOXApTDrb9t47fUL5VrBqZPxx22VN+QmwCDJ+TWSkvdoBU5MFMSt4l/8JlkLmx2zglvpfYQah3rDLnVvCMoV6hwyfj8CMZHLei7HMUJhFqNf8YKVXMMkc23qfru79F+ZExq/de9sXG2AyMr6fx5vr6sOUZD7MujVsUg6mISvNLK9V5V4wLZk7s70jpzjDUsjKMavdu+8qmIGMz7da0kUOM5I5M2vytfV9WB6ZB7PfjNnJMAtZWWaBqxIfwyRzbff6aY+JPx8rZHzNG1cG1YIpyfh8YweWmwNTk0mZTRyr1sO0ZDJm0c3b3oOlkTkx63hemgkzkLky8z3b8iMsi8yb2Zb3p8ywXCG3uLOqEsxE5slsqW/BH7B8ITfjyIOesCJhhupBh17CZPNsc84=
*/