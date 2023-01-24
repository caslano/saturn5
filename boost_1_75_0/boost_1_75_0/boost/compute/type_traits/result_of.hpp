//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP
#define BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

#include <boost/utility/result_of.hpp>

namespace boost {
namespace compute {

/// Returns the result of \c Function when called with \c Args.
///
/// For example,
/// \code
/// // int + int = int
/// result_of<plus(int, int)>::type == int
/// \endcode
template<class Signature>
struct result_of
{
    // the default implementation uses the TR1-style result_of protocol. note
    // that we explicitly do *not* use the C++11 decltype operator as we want
    // the result type as it would be on an OpenCL device, not the actual C++
    // type resulting from "invoking" the function on the host.
    typedef typename ::boost::tr1_result_of<Signature>::type type;
};

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_TYPE_TRAITS_RESULT_OF_HPP

/* result_of.hpp
SyVuxi5O7R0NEx9E/6ddij3H8O2JBPV3Pl3aEsI77bYe0T9SM4zdQILH7gyqWFm92tBZV5efJFpy0gm+LtsSUfi6fIkqt1EJR/y+Lh4mBXMwVX+O1rutVeFnQk7GzlgtOqHWhFt1LOy239gyiO/IzDK6V7c9U27bf0KXabftBvaYdbU+3/TX6PHA87i/fd/9bXVdVJ1MxYms/Rdaotma3WG1ZL57SdHFGtLOAdNvsy+SM+6LYXr9b925OYcqt1K5j0rSCRd/KWv+SuEgsMnd+jG91LjubEaXXQaCiSn7x9RaWiXq99WV53P6UmpQbW1nt9ZN1m+cZ8OdkVuju2KXxf9VJxL1dyTuiuRoVrLWSp1TIzrmpCOxaCxu6PocdfJ4e9XJmdOqTq5qqfJWFvs/1NO+dlz/B6p8jsoVVJqwto6axuZDprHHTWNB7I+hsTxNLJa6vdiAvi7AK1V6Eq4TVSRzJBs/X1/uzgK94KawWtg48Ly12n7I2RW+IrLViQ7Evqzr70jubXyiPpHIxdfEtkS3R661iZrojBq36mn/uyzdcKyl3rgjxRojRg40NtsDrKOq0Ne+VM86vtepYp/E+g+vJQP/hRpyrz5oeOwlc1TTtm/Q+r2H1u/dxAsdVLC0YKwy9Pq8ahqrPFW2ULnqJCMn+gRy8D8Gk+8PmbG4MmTG6ljoJiMqbjvJm9P36NPV0fr5dvgnOvJQdGfk
*/