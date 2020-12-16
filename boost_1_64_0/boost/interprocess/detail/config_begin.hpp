//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_CONFIG_INCLUDED
#define BOOST_INTERPROCESS_CONFIG_INCLUDED
#include <boost/config.hpp>
#endif

#ifdef BOOST_MSVC
   #pragma warning (push)
   #pragma warning (disable : 4702) // unreachable code
   #pragma warning (disable : 4706) // assignment within conditional expression
   #pragma warning (disable : 4127) // conditional expression is constant
   #pragma warning (disable : 4146) // unary minus operator applied to unsigned type, result still unsigned
   #pragma warning (disable : 4284) // odd return type for operator->
   #pragma warning (disable : 4244) // possible loss of data
   #pragma warning (disable : 4251) // "identifier" : class "type" needs to have dll-interface to be used by clients of class "type2"
   #pragma warning (disable : 4267) // conversion from "X" to "Y", possible loss of data
   #pragma warning (disable : 4275) // non DLL-interface classkey "identifier" used as base for DLL-interface classkey "identifier"
   #pragma warning (disable : 4355) // "this" : used in base member initializer list
   #pragma warning (disable : 4345) // behavior change: an object of POD type constructed with an initializer of the form () will  be default-initialized
   #pragma warning (disable : 4503) // "identifier" : decorated name length exceeded, name was truncated
   #pragma warning (disable : 4511) // copy constructor could not be generated
   #pragma warning (disable : 4512) // assignment operator could not be generated
   #pragma warning (disable : 4514) // unreferenced inline removed
   #pragma warning (disable : 4521) // Disable "multiple copy constructors specified"
   #pragma warning (disable : 4522) // "class" : multiple assignment operators specified
   #pragma warning (disable : 4675) // "method" should be declared "static" and have exactly one parameter
   #pragma warning (disable : 4710) // function not inlined
   #pragma warning (disable : 4711) // function selected for automatic inline expansion
   #pragma warning (disable : 4786) // identifier truncated in debug info
   #pragma warning (disable : 4996) // "function": was declared deprecated
   #pragma warning (disable : 4197) // top-level volatile in cast is ignored
   #pragma warning (disable : 4541) // 'typeid' used on polymorphic type 'boost::exception'
                                    //    with /GR-; unpredictable behavior may result
   #pragma warning (disable : 4673) //  throwing '' the following types will not be considered at the catch site
   #pragma warning (disable : 4671) //  the copy constructor is inaccessible
   #pragma warning (disable : 4250) //  inherits 'x' via dominance
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40600)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

/* config_begin.hpp
2rDUjevTTc66KbRuqgYyYBvwqRi/Hca0yaFcc2O8wUJxc8gDaCQ2TgxyN2o3s+WcDTNxvebGkJtHjK+xvFO1k4WWnWsVqo2YxCeC+diptexmvp7brjpar+QLoxVbx5tM2STa1elB3eWc7e1sOdsQiRUqa9qFkt2MKX6aWGLzQhMWBeAxt+UURdzVY+NPPyFkdZqpYipMF7O4Z6ehEayZikPtC9+vG4RXWw1sLMF+mAdjr+c0W+1CJV4qwcLEhfrQZcb8wfoC0hwH0pzOSHMiThO7m5VMD0MnzA5vKJMNMpCyqJdxjXqZwVevM05F9ToP1+tMXK8zo05w404v6lXwE8Rin5m/4b+frcflmhrju65VLlSdynZYV7Pi2U3LArRRKPUgNq0oB2GwkBqrybLPBtqplLY3Bj7HeXZ2o/y7xtx6ccsCOM1yW/VmYcy2tm1g6UPw1VZDGxBrnJgZ/qSNRdT6bDARh06eziQG1k1SH+5iLLUBYatAPx2H++lcU0GMdQfyaVQMZpM0qlL3DCEgKfTtnFORb3cF327haTNjZQsbfblQ5LYutBMJfKxZbze4DQO2r8DK1XrJ6BMHCqzWrrrNIvUj0B0qMLcC7Tz22bKx8XFdN6/h76m60LBVdiqQLjrJBES79rSHKSDPi3j6u1sw28P8oj0IrFRoFUSf4Da+gJmmqh+zUiitq9l2C5WtquXaRdl+cD0msKpTM7GJBLZ5vd2MaWwy1JUK2xnYVIjVPXGnE9h2dsGMO5PAtvHGnQ11XmwugTluSfh2HijnxFDOhYxyzgc8lrBVFWXTY+ae1P8WUf2vaxrRgBedCv64rwr7wpOLcV9dnLWrhLR3XqEPpOKZdYesNYaz6w5hsgF0tdXQ1pJsa3X29VxUj9ZoT+wz+btL/O7Vv8cRv5fSv8cVv5eGNsV9uEeWG+topXatVqjapcVbhbFVMC8eBPIxj7cNWdtA2mq+EL97wTa3naX+pO1V2HYvxstZ7Zo1Kut8aY1to8dkwrBFfiHa7ARiNJhgmalC08v705uG01tW2YY+Annvgrwv58m7U7NUs+f///0xzKktC+7Y0m30YLwQnOt1ea7X3lB7a6Yz4nohkbIstGP85vgrcvxFwuKH5x3njpV5PIN28Nnu7AvARJyqW7aqf/X6f5rYhDN0gf56+H0QGBgX+pDAxmXswCGNjc/Y44tpbELGPjewiRk7L6mxaRlbYmWNTc9Yw8DmAKwLKjXbpbH5xBwAv5PjamxB1n0Q09jCgJ0A2IwG1gfYh4DNbGCrsb03xtHYBpyXW4zybsK6q424DuuuW0ljWwLWB7YeMXTbAlYF7HsD25Hj7mCUd2fAbgTdfYZuV8A+AWxBA9uL435gxD0IsOXG9ZbtGMD2BGwhAzuZ83eXgZ0N2J2gW9rAzuG8PGxg54bYu1CsMcYD/xl1dDVgGwM2i6G7LiTdG0PSuCfEf/eyD+YysIc53fc53eHY+DOIdpxcYaTesGsuzE5Fm/7XrSw+2nYqpcV7luhZoru8+NZub3fPcorbtm/ZxV1Yn8L40rQrdsG1WRHr1zZL9tYjHG+9xEi+DgvgkcEc/G/P0kv0dC/Ru4xgRp3ayJp1t7VB37Ij28JfsbJEagO41liC7SyxxAj8w+lybkaKze0arfpIqVKpFpzaEkUoy+g/X5aROtCwCivA8nuJRmk0NkkXpbF4+h9MZa5/1Jp0jVMrVtol+x82zlbF/CN90SkFtv079B/NLqm1LJkdSmVyuQFxQ1NcFw+kM2sDmsxlrfXTmaV64f8zeB/EkObXHIbLoJyBZLJWckO4tE0nLLj5kM6kDG4onYBfBOfgQmblkXkga2beVOZi47A=
*/