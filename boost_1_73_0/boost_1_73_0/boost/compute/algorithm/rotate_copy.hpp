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
ufKwWNCgTNsFvabAkPyGKuZas6IZCcv2XyxyCJ2ZjRaXswl8GI4vR+QMJd0eERQjVKe2+/WdFzu/27tApjqGrPIY2cbq2twes9uLCsiNyeV4DCIFnLvTpnZi+Rvi2VUzwt4DpoPKqsD/iohVaiosRjNNyKCF2OI4iaba4LHNxIun8+ejEQzH8wvsMKczF3PgH706DrD9mN467a3rO2vwvf8AUEsDBAoAAAAIAC1nSlJms/2XXQUAAKAMAAAwAAkAY3VybC1tYXN0ZXIvZG9jcy9saWJjdXJsL2N1cmxfbXVsdGlfYWRkX2hhbmRsZS4zVVQFAAG2SCRgrVZtb9s2EP7OX3HwPiwpFLlNO2ztimKu4zbGEjuwnBUBAgi0REVcZFIgqbgG+uN3R0qx7GRoP9RBYpu6l+eee+6Y+HYAL37ai8UUDr77Sv1vii9875yujP5XZO55hzT9BuEHHW/x/QdSDWHn9S09hh/y+gZH3ittc72nz2n6A+luCST9GZLzbUof8SR4tv5jXW+NvCsdHI2P4dXbt3/ACZy+PH0ZwRlXUlSQOKFWwtxF8D73J3+V/OvX2IoPEQgHvIr3Ai5LacHqwm24EYCfK5kJZUUO3EIubGbkCr9IBa4UUMhKwHh+dTOdfY5gU8qsbONs
*/