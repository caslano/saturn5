//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/copy.hpp>
#include <boost/compute/iterator/function_input_iterator.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p last).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Generator>
inline void generate(OutputIterator first,
                     OutputIterator last,
                     Generator generator,
                     command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    ::boost::compute::copy(
        ::boost::compute::make_function_input_iterator(generator,
                                                       first.get_index()),
        ::boost::compute::make_function_input_iterator(generator,
                                                       last.get_index()),
        first,
        queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_HPP

/* generate.hpp
7e6WHSnFNFi6thJF9Wp53P0A8FPKObWZwkDXKMv5yiNYKUwQeeCjWADOYmIcInVaX1Vm1+QBlnx8Z4KOGxuP6NAt56VwiNIonNZ6vYgLR+tvqrvruAKGuA85ThWYMKYhCbRkgbOn7sxuT9y1dDG/QVtN66JCHYhDPlbdw7LdFWZOu2ywOs7VLZdaLAg1ctAaHkJZuOD+tjvNUgUQqqSLJxR7BTn8nT0wjiujbWCCCz1JenK3X3KCzUYdmBEpBe58w/vplcVvSg4tHZS2/j9CQLaU61ViO0xzk7UPNXcUAJc6Be231tF04jfynC6RcAnx4IyKTpHRJbQ1az0oWMcPI6+8hPEKeT+jkyWJ2O4c2H6Ozkh3DpIrfSM1s5GUOh/gIDoaLe9yn7+AJgWKdIN9+CvYvmsylF99XKzkZqid8r2zQITLBwNa+5mpTHaJa6iiMMC2qWJfO4pnCgNm/JT1Ey6MgZEztNY+V7V+jotn/g/S3kkcKcBGldXwpbSF4aTDc9QPsrzHqPB2a3tyslu7Gdeuh0+MNA4aqPDGym5NWQH1QJTKAOOC2nmjaw==
*/