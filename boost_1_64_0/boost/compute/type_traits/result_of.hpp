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
ROr2NltP9SY83osy2q/eYZm5jN5oq111OfPGwc8M0R8UN5h0XNw2fQ2gEkOBBXs10gm8JWzLg3GeisPzWk1cXLdmvY6TuLJZaQaaEdD3JRuy7el0aH1KxA20S/HXyvpc4rVI/GJqL5N+quutSuqRlJT1rCKmsyUJdCz01Xkow0ybB/9pI+gcsiyQONMzMnh65jpVYraQKhJEH42rrNyITpwLGfZZON+aGPHbKCzA3969mehIKan6AVTEuxAT/urQaLSHTdiiXLDZ404qlemuszc1CQSx7BrPJsmPVMFy5PHSObAWyn5fsTwrLXVeQgqDWwIQZIeIHOW8KKJApjQemqLuUCMmUIZgbsjDpDbFFYRLpdhx7LusTcLnJ5h23T6KCOlzG3XJ7Hcz+qHWTDesxQY0pZZ4UZycixOwng+AdD1IqHc7fGyRP9Cce7QORgKS6Vi0888tIZvnnuTXSw3Dg7PuXfuO4OtAIi9u3uyy9cfjYafg1+g5dwyGKepGu4HID7TKD7OdrplehmEeJc7axIbyffq9FoZlgKF8YbupBCdKn9v6dp6W2zciQw==
*/