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
GwengrDdhzdV/xw0ZoEtszVwUldO0tW75jRdzivwr8Ly52DOIEpFfVrBmbTumfStQeTpBAzDG8lDAS7o15AXCB7I2VaXfX6noeozWWHKT63bpEUFKA4fEoWTvKGdqIs345ZQFhE8EEtAOurKSIWP6Zl86OwpN3W75RCvaqni6b3hkiZJf0KLIQ/N+083sPy7ALkWFwrGegOYpc+p2Exnp+s1CxWUXwA0lrvXP65cgBJhP2bXmMC/5ngV4ia9BMIrbVpWgLnYpCkqY6Bsvh56gccw0KCi+Uq1njwxG3cTonGnYu9QhPxlNNLchWDpqa108q2xXHkkl2HsnD9KhTWq+8OlMa0q6StF7xbqh4P3F5k/qt7o7zn3v7KzFCcSTWQcrcktvFxgM+7XvDdwUbXl5CeIZccVBFwDLAJnzO3NOrXeD6P/PaNeDwg4NQxg+VDk3tunMY6WV82FW0hVZ0gvUSkx1C715qPopgKpP3Np1QB0jFQOvEeoBcSpIziMJ4LFkPlHuNrx+d+VfQrsV4effEzUy6DLkWpTmFfU6fYy0J3DY4RH0m36xr+CFA==
*/