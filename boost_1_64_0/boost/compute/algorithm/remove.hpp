//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element equal to \p value in the range [\p first,
/// \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove_if()
template<class Iterator, class T>
inline Iterator remove(Iterator first,
                       Iterator last,
                       const T &value,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::remove_if(first,
                                           last,
                                           _1 == value,
                                           queue);
    }
    else {
        return ::boost::compute::remove_if(first,
                                           last,
                                           all(_1 == value),
                                           queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

/* remove.hpp
m0uDGRpTcTWNE8+0sS5KLgy+2BRA4m8dDIRRjA60v/Am6Pr69UOuAa8mlM6TrYsKS6e/HZsbIx6MMoF2ed7ZsLJQN6tlGSa/L8965di7TlVXryAyfmJkmk6Z6IyKCfyDckrIN2Gi6A/3idHzUE2vQR9rKODSbrqTGUZbCEHoZonaooAPG0BZdM8oT2sBP9FBu219Ue6saosXrmdDt9YRXgaQuOJ/Jhd1aG9WEqPrhMYu89DAJKFlT0+MB4JH9TBWJSUKIfHa9tnIi6ixdWWXDSWzCf2CbJWRWBAOw+D8+QNDbWRPTU5bRJBQnEwsrLJ03Qj6A0yWT+8mNmC+LJOveMGczPxz2jaSNabwTBq0gf0rconytMkETvwL0asqIvgRw+bUtFlAwnbDKnPfPPZ41JIjqux7siOLbSB8Z2j8eOt73C61LjVqktVU9VCs7EGRjcd6SANla6K1fD0kAcxghuRlZxipO2x1xVlykl0kwNVESVWcT2kH5ReaTYBCXW6ZlYFMU5m0yVjmHiO/wydqWbGH/z9KkdU+P673aUgmGmWZjho1RkloTfwUFg==
*/