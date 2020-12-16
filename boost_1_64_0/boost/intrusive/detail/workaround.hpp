//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2013. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP
#define BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#ifndef BOOST_CONFIG_HPP
#include <boost/config.hpp>
#endif

// MSVC-12 ICEs when variadic templates are enabled.
#if    !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES) && (!defined(BOOST_MSVC) || BOOST_MSVC >= 1900)
   #define BOOST_INTRUSIVE_VARIADIC_TEMPLATES
#endif

#if    !defined(BOOST_NO_CXX11_RVALUE_REFERENCES) && !defined(BOOST_NO_CXX11_VARIADIC_TEMPLATES)
   #define BOOST_INTRUSIVE_PERFECT_FORWARDING
#endif

//Macros for documentation purposes. For code, expands to the argument
#define BOOST_INTRUSIVE_IMPDEF(TYPE) TYPE
#define BOOST_INTRUSIVE_SEEDOC(TYPE) TYPE
#define BOOST_INTRUSIVE_DOC1ST(TYPE1, TYPE2) TYPE2
#define BOOST_INTRUSIVE_I ,
#define BOOST_INTRUSIVE_DOCIGN(T1) T1

//#define BOOST_INTRUSIVE_DISABLE_FORCEINLINE

#if defined(BOOST_INTRUSIVE_DISABLE_FORCEINLINE)
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(BOOST_INTRUSIVE_FORCEINLINE_IS_BOOST_FORCELINE)
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#elif defined(BOOST_MSVC) && defined(_DEBUG)
   //"__forceinline" and MSVC seems to have some bugs in debug mode
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#elif defined(__GNUC__) && ((__GNUC__ < 4) || (__GNUC__ == 4 && (__GNUC_MINOR__ < 5)))
   //Older GCCs have problems with forceinline
   #define BOOST_INTRUSIVE_FORCEINLINE inline
#else
   #define BOOST_INTRUSIVE_FORCEINLINE BOOST_FORCEINLINE
#endif

#endif   //#ifndef BOOST_INTRUSIVE_DETAIL_WORKAROUND_HPP

/* workaround.hpp
uwZ4PnALMAt4N3AR8JfAbOCDwBzgw8BcU3+uswBepND/Qup/CfW/FDgGmAdMB+YDzwUWAHOBy4BLgIXMv9FYP8C1D9XAvqADzH99FOKNAzcAzwZeBVwEvBp4FdAH3AS8BlgL3ATcDdwMfB34beB7wO8AjwO/CxyNwrYAxwOvBU4Gfg9YArwOWA7cCkRZIt9bgDcC9wJvBT4OrAEeAt4GbAReD9Qg/w3Ao0Jvzm8G5tFu3UG51OsP9MeXWb+vMv74n4ATgU3AOcA3gQuAbwMvBv6F9fwO7bfSnF8L2VlOD9BSlnM75OkB3AkcC7wHeAbwJ8BpwN3ALOCvgIuB9wEvBO4Cfhd4L/BaII5TL87zBK5Q6PUD6rWN7exmxpO5FTgWWEP5bwfmA+8AFvD3cv424qNXs5wjLEeOj94f8uh4CrAPcBBwGPBU4EhgKvAC4BhgHvB0YBFwLLAYmAZcBxwKvJt8u8l3L/nuAw4HPsnzz/P8SzzP9su5c+jnFO33LraPHwMnA+8BZgAfBM4A7mK/8DPgRuDPgdXA3cAdwL3AOuADwL1M9wDwPuCzwPuBfyLfO+RrJt9R4EFjLhnnx1UDPaB9lG8R29di4BjghcB04BLgpcCLgMuAlwAvAy4F3gG8lO0tD/grYCFwP7AIeAhYDHwRuBL4JrAU+BH5vgSWA7tDngpgErASmMLfpwC9wFOBJcAFwG/S3unGHB3gQNq7M2go9XmOfvE8cADwsJSuziHd40z3BNMdZLo6UBPTDaL9+oB2Mt0Z4IsFnkn7TWK7mgwsBZ4NLAdOYT/1deANwKnA24DTgT8DZgLrgXOAj5D/EHA+7bgA+AbwPODb/P0ecCGwGTgDOBDyzTTbKd9nAwsV7fRqttONwGTgNcB+wE3AecDvsd++jv3Pd4CX8vgyHkc5yITvUIG3sZxeIC/LeZjl/I793H5gGvBR9ncHgBcCf8/+oJHXr+eAxcCDvH49BbyOfNvIV0M+yIFy+S4OeD9/9wZtphydWL9dgPHArsAhwG7A04AxwBxgMvs/D3AJsCewABjLfqMX8Eby3UK+W4HxwF/yeB2P0z58V4M+TmGfZtrnb7RPC+3zEe1zlPZppX2+oH3+Qft8AqwCfgq8gXw15NtOPvo/3x+o/f9p2ucQ/f8Zyp8KKme6LiDc04nvSUyH+zvy4YtLvmqXfLUSX2MQX6vEV+eSr8ElX6MDX4HE1+SSr8UFX7kx/gG4i/XTE1REvgdYPw8CPcBfA/sDfwOcD3wIeDFwP693jwLzgfuA1wMfZr/9CLCW5419URpZbjrLlfdFKaN/rgGmAMuB44CXAZmez9jq9CuZvoTpv8n0q4ATumht7i0yFL/lWHPeMOLNfRX2FonOcheX7j+1v8iUCZ3/6/YYeSu7Y/YZMWLeLYCOB3GMse+w18hXf5+RLd+Jjuw1EuZeI7vOjTb3G5n0m2gtH+QD7QQdAL0LinkoWpsCKgJtBdWDXgPFYDOlMaAskBe0HXQA1AyKfzhaSwctAW0AbQc1gN4CRT8SrQ0FZYDyQb5HIjH/Ip/IJ/KJfCKfyCfy+f/+/Fvi/xVUlp3RAfH/hiDizSC83KjZH41XBUHbyFcWX5bn9Yo9Agb3wzpAgyc7cxHPifTDU/AM/ijPTZ85c3H29JkXkQHiCZ59AzBuZvDk5uSKGVYyD/PZfYA8ObnTcxfnCDZZjhGQI/oxU46crLyCtVVIP4h6DJTPSfmfxvP54nxmDnLOyVmcmZ2Xk5k9b/oCg9O0x06Tb2ZmNqSdpcjrXZMnZ96chfMWzhG8ZOT+CD/3aIxNBt0YFzDRD+Ldwf36OspmsTZcLqxobbkm1rqliPkpVep5dkg=
*/