//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2006-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP
#define BOOST_INTERPROCESS_PTIME_WRK_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

//workaround to avoid winsock redefines when using date-time

#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#define BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifndef WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#include <boost/date_time/posix_time/ptime.hpp>

#ifdef _WIN32
#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#undef WIN32_LEAN_AND_MEAN
#undef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef BOOST_INTERPROCESS_WIN32_LEAN_AND_MEAN
#endif   //#ifdef _WIN32

#endif   //#ifndef BOOST_INTERPROCESS_PTIME_WRK_HPP


/* ptime_wrk.hpp
YnX3OcXrVh8uoIahzRdx4E7f2Ua0QGBQ3SOXdAJuA8Jsvc5EsVYjknJn9PF7SU13/Hov6PAY3NbWXjafSC2WZUzOb9TH6Cgnk9GLJFs3/PWg2e16/0I3rjxcbo6AMWysteC7GwkAMz2P7sn6FtjaQG9I9eM5x1WciUs8+6azqmAVHeimm14atlitOnfcASvoNgW7/UJZ8e1vR987tTIRyJnXfNa+RtJukZ8rIZ8dv3OBNGC+L7YEWNaFe5uFQazPURDGRZz4gD6l1JWOemV+Z/nA/vkjrPJjZEAVGZ0PZ+4B5+tUnbvrr1cEqp4smkrqJZTR9Cd/LqM468Ey5++lAMqNF/hTdVGM9+WfKCr0kDT/ycE73nHSXqgX5pt5Qv6tCsJebe0hxXdEB5/D5It5yIRW8bL/jl4QOOCplkpBn/cnjoubAg1qkGBeI8HzRe7R+7MC/I11R1evytoJUHPsFNPiBkBRRoF/9YuHti6NQX2vh/xcsxuV/B+cv6J/901tb1tI/DrjX8rUZMtBTWn5+/pPztVFHh5kmj1+2vWJWc/HAEfJoIOYfCkdlADFAq0n3H/QQ21c6TXaLUN8nlIWdRCthZwVxSTjN3jZe3xeOS+XhizFaDfkn5MXO1UBmANZZ2nEED1I29HkKcjvNfsnj8qBqgduIr6RCU11zv68UBTXhnIDinXRJPGJpPOP51+/CjcaWwxV81qxK+pm
*/