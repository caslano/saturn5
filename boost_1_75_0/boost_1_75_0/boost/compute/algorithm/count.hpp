//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COUNT_HPP
#define BOOST_COMPUTE_ALGORITHM_COUNT_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/count_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns the number of occurrences of \p value in the range
/// [\p first, \p last).
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(n)
///
/// \see count_if()
template<class InputIterator, class T>
inline size_t count(InputIterator first,
                    InputIterator last,
                    const T &value,
                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::count_if(first,
                                          last,
                                          _1 == value,
                                          queue);
    }
    else {
        return ::boost::compute::count_if(first,
                                          last,
                                          all(_1 == value),
                                          queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COUNT_HPP

/* count.hpp
01RWYwub4bagH+gCHvBd32fNxBlup0XbTsUZTqIZjrY8P+MPUyU/j3SW5EBrKZ4NqGJCcvBFKykwSq9NZ9Vs/5Sx2WgP34PlqEhtU2K+gEd9xrHyH7F8m/L75rOqY9W1JGlneOEhVgijWAtqUwxlhsYBINb4dmr8F63xio2sBWz4B2PD/kY/uNqKH4SvVWtfm6x9bbvxa3c29jWkymb22hcviE9dpX3qHeOn/tgE6GMsFTZ/cvQPbzLQ5Ade+OWmRhvdTo3u1xr9aEOD8M9q7FOCGvC1jdrXxmlf+5fxazfC1/z2LzWqPfQFFnyvFYyAAqGBfjmv4Z3yEHvi9U+P6aaMDyy6KSMpWJEcyXtbpUTdap1kiDMAtg0feYdTTGy41y0Xf8/qodpPyMFRCbi9g9cTVo9Kub7V4yM5hNWjZZlm9di+neweJx77X7Z75LQJu36/Ug5l9yhQHhgcaPc4/VQk6/W/TKHsHpf3DWH3eMce1u7x5FMN2D0KwO6RmmuwewyOCLxRDYDXEEx2e1i6nfA1RLfRktwfJUZzae/DlrSxtVbjQZp/+iKB8xPVHIKM+7JD+eT+o3VYmG9rEOYAW01BoK2mQAP6TFkkQJsaALpBe7LmhvKvVppiRzlYz6FVOTvteI7vwWIGeTG0XlxGml0Bmmy+Ac2uwOV7CIK7gSDgQqiIa10HYmDZ/hA4yIE/s9/+4PNWrlHdnKOb
*/