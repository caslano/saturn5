//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP
#define BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/lower_bound.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns \c true if \p value is in the sorted range [\p first,
/// \p last).
///
/// Space complexity: \Omega(1)
template<class InputIterator, class T>
inline bool binary_search(InputIterator first,
                          InputIterator last,
                          const T &value,
                          command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    InputIterator position = lower_bound(first, last, value, queue);

    return position != last && position.read(queue) == value;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_BINARY_SEARCH_HPP

/* binary_search.hpp
NEx0mqCdPJszlor+xR9ZJtD1/Hhui+bXX8dTMoE5UM8hb1dm8Be+4hW2suv2HIh4spHxuutHVlPNtwPE2Uzyw5LkA95d6inbhqlx3pNmjx0QT1Dg0JR/eC64EzfvRDNPKgS10n2kAnznpt4Y1ndu0FsN+M5l9wvlO3dV9N/znev6QkO+c9+8GYnv3OEOIXznbhorRvi6f+BE+xtd2o/V/JEDfXw9qZH5+Ga/+f95H98X3/j7Pr7zF/0f+vhmtA/l4zsiH7kyJF9w624q6J2Pk64m+8M/YLJ/yBWJ7IPdlct+y/ZBsq/5TMY6raYqRxzOMD62EDlwSm0+YBEE9oueLlmpzIky1744wwREcMSdUqWESrNpTRJ7Sfm0HRxP6ZdgdJR8ZqlwlNTauV+q387R57GdzyJqp38D7VyjtaPTonhqAnx0ZV/+0QOerpI8FRIds7mAjTEPsHFtTS5OqLuUc4no6hlnMgYz0fR06A33XxfOB9HxWj0DtH9AnHKZFTv+HZogtnwtEnNoh0ThA0L5arconjHBfpECv119QuB3xSUDfu0axW/uteHw+8erDeLX3xSE342vRoJfz7bB+D03un5Oc+N4BGPyz92Npt7fULt3yd8Hbt6tWkZLAEk3fkg5pT95mq6C2akGAqytw1P/ENkNVlqrgUTKAYSojitefePYXyL7Y0utvunsmsD+WPW+qWVj2MJrDFP2x0iM
*/