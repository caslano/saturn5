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
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
*/