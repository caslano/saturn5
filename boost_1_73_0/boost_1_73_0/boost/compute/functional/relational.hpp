//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP
#define BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnotequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isgreaterequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isless, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessequal, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(islessgreater, int (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isfinite, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isinf, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnan, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isnormal, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(isunordered, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION_UNDERSCORE(signbit, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(any, int (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(all, int (T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_RELATIONAL_HPP

/* relational.hpp
1h7juPDgxkR67cZVvToSXq2qKqMoROpB9kORq6qNCIvdq3ci5XxDUYa8734r5D7ojvqvQyYG/TdKNalDAi88FgcCsrHsRU5rDAxpMzQX7E6Y+/isoM9IeavCPvc7rE7sIkG8EA7tsLPKRuILVlgRfw3FslwjDAcLLKG23V+bhRaehtmQ/u3pszuyC7siDFC7JDML1VvV+Ypppai3JwXciIukj0VZnm39M0QEeQE7MxkUORtDlBKHG1q63pUlVJUElDILyQjniORVninP6SMK6RsKSSUcjV06B1Mj0Td0RACEcsVL04OrOqFoKG5aD2j4gHq0sf0AYWDlDV6BByBFTmE/jFPAEVAPDn0c/azv8aMgyQCOqODG5AfqdGA+/of8JCqkHmVNC+15yaOlSxp2Y5CVukcICMyoVmR2v+7y9I54AWLJ01cbUpuUjZseWdbu153w6j6nI+Ps9F8vOs80kxk0SV4CM3lPnimDMZu0cFBS96nhQzFxJMQuELKNkomWlj1CSi7YD0Wg0YEIVxnfVLV4wITcPT2b5RSU6Jd7ORQ9d3k+I5iEiJNB6K1LK0X86jINYYvAaVGaIW0u6tiRG45Bgaoo7BJ8WNfVbrUW4sJajlW0yTeQ2r4qHeuoeg1s8QdjzomWnufgD13J
*/