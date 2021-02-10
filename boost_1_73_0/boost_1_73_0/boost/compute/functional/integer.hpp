//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP
#define BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

#include <boost/compute/functional/detail/macros.hpp>

namespace boost {
namespace compute {

BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs, T (T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(abs_diff, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(add_sat, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(hadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(rhadd, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(max, T (T, T), class T)
BOOST_COMPUTE_DECLARE_BUILTIN_FUNCTION(min, T (T, T), class T)

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_INTEGER_HPP

/* integer.hpp
mNlsw14KfhgXJFHF07vUZeq8ammiPdKM3KqJvOgcUAYlRJ5bjaMGiq3LvZJvD1r10Y6NWWVN4Ttl+tTs0eXpSRUlGK5MGUjkMdmqo24jbZm5gNNLw1xUIMcLPiEqn9BbaeqqdV45orFweCNrpbwCctut3DEWevPeLqHxwYcwZ6fTxEMxY3SxTqW3RMiKKeHLCpduFYWT1YcqtQvpoE8/2YpT6Y2jM98itA98A60SyhuD8pRzUXzrqUsH05PDXfny7fvZHNfHtogo0NwZjP582GIr4ImQBEuCxyBlChHge8jwDY2oNFGahs8bpmVshzX3j8acEUSPsCz9E5Iv4edxCGCA6ueho3OBCKU0+j2Kb8IKdpf0KlHgzzo8ZCXVEniLmb/CD7DDO7SRhBAJovSffO1sbk7jIQcfcCxmN5e/X81HR2mSGXUhpzgxot2JYzw3y1hm8GFPrxIIkooYz9Vk3oOzRGVkHS7MJUgUydSCxnoJDiPgUlPrVt60KH8iJbVGOz6LHSmjWYUVRidcNtm94eJf1XRSSulKo26cFYfGKRmLwMKr1M2YDw9OzA6Og74hLgdHM/2w+0W1HkssDblYAm4JPijTx7PmI1j9QSDqZw2DkCM8j86XmahrWZbiS/RBZxy9ou8WgLWX72/f
*/