//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

#include <iterator>

#include <boost/compute/lambda.hpp>
#include <boost/compute/algorithm/transform.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class InputIterator, class OutputIterator>
inline OutputIterator
clamp_range(InputIterator first,
            InputIterator last,
            OutputIterator result,
            typename std::iterator_traits<InputIterator>::value_type lo,
            typename std::iterator_traits<InputIterator>::value_type hi,
            command_queue &queue)
{
    using ::boost::compute::lambda::_1;
    using ::boost::compute::lambda::_2;
    using ::boost::compute::lambda::clamp;

    return ::boost::compute::transform(
        first,
        last,
        result,
        clamp(_1, lo, hi),
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_CLAMP_RANGE_HPP

/* clamp_range.hpp
xFshvT/4jEc/aoMeiXgY5JMCeWQgfxHSaaMeB9AzEM9FPxmgHMkt+MORrgT3/beJ/JkZ8GcCGWBKLD2H5h5HMXQFRZOVFB3iKWqsohgOOcSjfe7bRfUcQz1ABmgwBfmnUryO/kqGHFLF53eUnAcq86b5o32AkykGQT6a4Cc6RVSekvNPEg+a/+IkirHodzP+3M9WUTlZKAfIAKO9aH5r8FeK/mEgp2z0B/OUpm/1DP5kjB9D/vkC5MCfQyqHfoQifzn40nek9WQBQ5woajpTNB1J0XU8+m8CRYOJFHX58xj8+Ed/HO6HfOA/AXqVAznk9ICcMH/mQh9yeH3mzyF1QH2dKOYCSztTNO8KPTOiKDERIp+vAHHxPBsLuQSBL2vU6wF5R4OfWPCXDbkmI30q5B4bDb1fVjlqLadYvlwY5+/z5YiRv58GfSyB3Ashb/1pkMNsioWhFNMXUTyM+UwL/eGL9pj3wnME4FtTig97UxwIOZggXxbqCzGh97V6UAyCnHz5eQh8StrS+yb6eL7RjmJqe5yfhN4kQa7haNdbA3rfsDPFjC44/9YV9RpR1OyGc5nGNQT6btZdGA9CXAI5hIG/fLSroHUNgV6kQV+Tke4i+tkhFf2wG/PdXorZB4T00kPCuNERiqmZ6B/IXxPyaoV6NDAP50G/TCCXt8BSHcqnaVOKOZivCqG3A8XnNU9gngEyQKPrlI+8CuhH
*/