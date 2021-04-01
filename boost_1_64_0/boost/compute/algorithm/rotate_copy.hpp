//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP
#define BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/copy.hpp>

namespace boost {
namespace compute {

/// Performs left rotation such that element at n_first comes to the
/// beginning and the output is stored in range starting at result.
///
/// Space complexity: \Omega(1)
///
/// \see rotate()
template<class InputIterator, class OutputIterator>
inline void rotate_copy(InputIterator first,
                        InputIterator n_first,
                        InputIterator last,
                        OutputIterator result,
                        command_queue &queue = system::default_queue())
{
    size_t count = detail::iterator_range_size(first, n_first);
    size_t count2 = detail::iterator_range_size(n_first, last);

    ::boost::compute::copy(first+count, last, result, queue);
    ::boost::compute::copy(first, first+count, result+count2, queue);
}

} //end compute namespace
} //end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_ROTATE_COPY_HPP

/* rotate_copy.hpp
NWF9a9s9/aQTzBnGMCyOsva/BCIH7owzJNDgxWN9vDiaCjmrPnMC2nJSzoCVm//pBjgd3cIGjF6af6zhpcr8GVR4dVhufTEtAobuLoYH/zwfE9qjaz8wgMARHPp3N+dUMXmCoc9pHKCsSX5pS3gFnBjgeCjJceaiR/14vNAIvyuPi+KYrACvxdk19lMTC3W/B2Rv+kESgLRuZTM/Zx2AzJH3q0pwCEWlqC+kQcivtf+OXYzen7sLXcg+Ygt/xF/lUvUw8R3LKt2cOcTq++V+NT1JHUiGBkbUsSnww/EFkX4z2xtO4qVhEFMyrLy7gQ4Ll+O18d4132fk9ZYsUiO7oeaO/Zsirf0fjUjhBpfyCW3Fvo5lTAfQs9D6Ad6c4wS4KksEEFdqcn/CZaUMjXBbctrDyslv7G0dbKJNK5umvFbj5j+Hph2O6daeta6I6cJCCsrIt0l1ZiHWfQrhkRRqn9CYn1CBSBjl/COZ9JbkJq4RgbBhIO5rr+MHxk6/o4ojcjkvZWHDAtrTLWWW3QlSyiQLeqNjPyvvJsFaenPWoecFxX5L6ranDxUz/w==
*/