//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP
#define BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

#include <iterator>

#include <boost/compute/algorithm/transform.hpp>
#include <boost/compute/iterator/counting_iterator.hpp>

namespace boost {
namespace compute {
namespace experimental {

template<class Iterator, class UnaryFunction>
inline void tabulate(Iterator first,
                     Iterator last,
                     UnaryFunction function,
                     command_queue &queue)
{
    size_t n = detail::iterator_range_size(first, last);

    ::boost::compute::transform(
        ::boost::compute::make_counting_iterator<int>(0),
        ::boost::compute::make_counting_iterator<int>(n),
        first,
        function,
        queue
    );
}

} // end experimental namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_EXPERIMENTAL_TABULATE_HPP

/* tabulate.hpp
huUq3PEHuOEAWHZ5oX2grqLpSLMzBJSJqFgK1qCJzXK+O5h44we37ZWmvKRQ75YnAgYF3brvFvlzSq5QnRs0PJ9KIwLo3JzuVY9p8GY8L4VUdZN6J0zrBfpZ7KcV1IG+VHgP1E+Gw1nfHTwhQDrdMeDLx3IoQCYpnVckr7C0bsSolmA+XDbZq2+qrsQq0hXNOvgerQtwqzX2PG85tDL4PuWkNR9PwMY1Dfvubzy/v0fD6eDjADiCfE57CO1uNTU0fc/dRnxkG3mL9DlBfRGecH+sJcZyqVsQpCESUpZusgiQh0JlUXBbOa/arSYH26ivWJNBbfzzGd6hUwZ2SNnGwh4yp1v7hsrpAxbjGguI00hLa9GnLdoD5PdgkdtFRjwaKL3FMiZeb4CaU5tm5j8NJu5vsNAdO3cu40SWIsxRADl6F37+zMllf7f7A4IdAf9I56CHVxSNg1Q34Outou3eiK4Fq2PVRZTBqiDJ0Bse8ixzwkInMaJgXyxJAS+zWkW0k1S9wYfugBvwBn6uSk5QBtcie91gV2XyTG0R6EhAvAs2NXEo1G3sXl3WGL3W0Swq1gUvhm3NwI0IbkL9pSHfG5Sc+6peJ5gCEpuBlPmVy5Utst7+VA68NgOph8JhosucHwpg9uGNJ6Px8L7n
*/