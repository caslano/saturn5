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
yJteELJsGQF5X/sj8y7zTM3n2OZB9BIStvDs+VQNhaHai8YPraMQ/x+vo7BDzdLpKLTCQukiDKXDruy658q6byi47rlQuhRD7fcJrUvx3iYe93seXvXMGy9dffq62N1xbSK+HUw9iI68ozdk3rKp1pePnKg5/v0XFz3dOpRuwVA6GX++fUatMeyfOj6tyrEfLnnii8KjBbVPdVqHm+Tz96lr+514IKdTUdtDr3763c0tmTeIe7VDUUsmNn2/x5dPdHqkZu6lk0Pt5wqle/Hn0/kYfN9WqH1hoXQ1ll03YnAdiyF1HYpOww1+Og2XiA4arzyl2IWsnd+b/X6v9/u9zu/3Fr/fa+zfMm9cye9+/N6kv1P4vU1/D+H3Q/p7lEW/0N8T+H23/j7Bb9UVpmv3ZG0gfk5dYTtUp+FO2BDugu3hI7ALfBR2hXthD7gbDoaPw8vhE/Aq8dcz9H3r0sBCvZ45Q1/PYK8Nn4EN1d5E7X3gc3A4fB6OgfvhWPiSpn8IU6zpf6jp14IHNP1KeoZ6ZRgBq8BoGAlrwyiY4NtHB6tD+VYC5XsI7A9rwDRYE46F8TAT1oY5sA4sgHXh9bAeLIL14TrYAG6DjeDjMAG+CJvAt2BTeBw2h6qDSNdtsWZMyuXUQTSLIEnwWrgOXgfvh/PgNjgfPqj+u+EC+CS8AR6Ai+Bv4a/gEXgTfA8uhR/DZUZHpK6P0fU+KwN0RBbpmfm3wRZwBRwIb4epcCXMgHfBLLgW5sH1cAHcABfDu+Fy+BBcBTfCe+Am+C7cDMNd9BFYBW6FveEmOAhug8Pgg3A8fMjo8NT1BnCC1KNzn2Wito9WsD5sDTvANjAFtoVXwnZ6X/LNOgDGP00vEmZqemmqc3MUjIGXwRpwrLbz0bABvBy2UfckOAZ2hFfAbureQ+2npB5Vjg2H6XWj5T6Z83ylHK/DKvANGAX/qPn5HYyFh2Et+CasD9/S/vZ72BIege3gHzQ/b2t+3oF94VG9v+/CVE1f61ll0TBIPQ/SfAyBdeBQ2BgO03aTKvWBXdNbYuSz9H1Nrxqcq+l9RLhEeAL2hx9rvj6Do+AX8Ap4ChbAL+Ec+C2cD0/DO+Hf4Bpoie5OALeoLtCtMEzve5KlMkYYofkJgzIFVZ1Y0i9hJXiNiUdCZ4k3TePlabx8jdcVU6Txqks8p67YmzXeLRpvOawGizR+sk/OAjtJfKcO3AkafxKMgpN1PMyGHeEUk45+9wdVg6QzVNNJheFwmI6zwzXdEX7pRGs6iUHS6a7pJMPKsBeMhb1hS9jHrk/9Xkr8IPU5V9OZp/mZ7xcv4yzx3tf+8wEMh3+C5r5rvFZB4l2q7ToF4obd7g/FGo9+xpzgp+nqTcIc0/SqBclHX02vn6bT347HIB463qUaL0XjYTfjXILGWx5knEvX8ONhPJwAW8Ms2AlO1HnCJO2fuXAIzIaz4RR4I5wKF6u/0bmm143HFAfoXLvQhONvT+nCJZQyXHIpw2WUMlzhOcJ1DWecn1rFKi6qbB3E7J1e2VpyfmUr6s4Ia9HSSlZ44wpGr9wW9q6/iAmlXy4D97Y7RP+U0TW3xOibc+qaa4bZ/bCfboA/Gh1zQfTLhdQtZ/TJjcWE0CGn+uOcuuNq9yypJ64vL0mjMbauOKeeuPD3qAe4BLutH66kXrjTGH99cJnQXw9cEumoHjijA24u1xU9cD59Bpgi3M4k23rfVOeb6nkj3MNGx5vqdwuu2+00tPW7EZ7rn+T3LtJX3W4l9LodxC+qvVenWyIMpscttA43rvlwoB43p+620fwuwCx7T/S2GR0M4Qu47o6y620LpbNtF2Yb14jreG59bT6dDrs2Uy5YUj8=
*/