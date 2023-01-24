//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP
#define BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/detail/binary_find.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns an iterator pointing to the first element in the sorted
/// range [\p first, \p last) that is not less than \p value.
///
/// Space complexity: \Omega(1)
///
/// \see upper_bound()
template<class InputIterator, class T>
inline InputIterator
lower_bound(InputIterator first,
            InputIterator last,
            const T &value,
            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    using ::boost::compute::_1;

    InputIterator position =
        detail::binary_find(first, last, _1 >= value, queue);

    return position;
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_LOWER_BOUND_HPP

/* lower_bound.hpp
ghbQxoEDEXC7teFnlUwbisnoCYukOzect7Ctna58fjlbzd/TUvMzSSAFIMtV7UPfiIWdTfKFa0m1gXSP7Q3iArrjA5QCnoGBOLewvepbTpGZ0SlnDZLGzA0EDuVzKWajiDCcgsHEVahEittk0ky1AKilt1Al5ZS5CWCqmdv1wgIYNfsTpGz5efD5b7hdDjuQ17U5kGHhBQ8BkFkAwROfsrVYcohdi/EVXGMOanYphsAYKewonf5qJPwALccv3agK+J4wMcv5S4kPbWUouAqOSrI9hjZCNXFJArKvLnmME2lc8qY/94JJqGFifCchMGtspoXxuzAx+TBtJZkCOdr7TdAY2TPZkuCt5nL7vS0JuPDvbd24uZRmCMVS4mFYDTmiJSCJ5DrNKEvTjbmlGnmKiQzQVPuAHoSLUlT7nB7t1UilQ8Nx3KWe+zpyoBfLxE4ghLRgFndWKb85gIBGrbUSPEAAzTWKA1acYOGbrZ1f0SGaaWJygGynBlPMX7iWYJoDWBZ++LuTF7tLqlFmwDHR9DQ2GhyRlmp77B1CTtbjW9iuzUNhgeZFnK/IfzAJawCU+XO/6XQvXKeX/23uZtwZ8394YARcZ9/008TX4Vq8bHLXSXCdt7rY+gJOwV8OBwegFMffe3fjnS4p7JJ+holYjLGevJL6cTyZQ8SiqQu1c+c0k+CTF8aIljOe4ClT4F8uOIgWu6R5qHyj0k6p
*/