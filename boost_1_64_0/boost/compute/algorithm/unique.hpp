//---------------------------------------------------------------------------//
// Copyright (c) 2014 Roshan <thisisroshansmail@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP
#define BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/unique_copy.hpp>
#include <boost/compute/container/vector.hpp>
#include <boost/compute/functional/operator.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes all consecutive duplicate elements (determined by \p op) from the
/// range [first, last). If \p op is not provided, the equality operator is
/// used.
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param op binary operator used to check for uniqueness
/// \param queue command queue to perform the operation
///
/// \return \c InputIterator to the new logical end of the range
///
/// Space complexity: \Omega(4n)
///
/// \see unique_copy()
template<class InputIterator, class BinaryPredicate>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            BinaryPredicate op,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    vector<value_type> temp(first, last, queue);

    return ::boost::compute::unique_copy(
        temp.begin(), temp.end(), first, op, queue
    );
}

/// \overload
template<class InputIterator>
inline InputIterator unique(InputIterator first,
                            InputIterator last,
                            command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type value_type;

    return ::boost::compute::unique(
        first, last, ::boost::compute::equal_to<value_type>(), queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_UNIQUE_HPP

/* unique.hpp
ImJEY11o5qC1eCiIPXxoaMo70H2AR2b8DHknGx6ukFrGi8r4NRIlPW6ft2TSH61wHa0CKrFkIs++yFkz0Manzekwa+lIk5k+5ViJHJL12XxBf0PKdy8hWC0++0mlhMwLDPO/UijgEhtIqGKaClkPlvK+5EDViDZR2N6sWU6yv90ksepzmch0LS02YrLndrW4hcy6PWSjogdbjPKSzEkFXq80lz+EGkZU9dZI+0mb/OovmvD6fYtts9OQNMTfL0/2wOwK4DkogCYDH/GqKHuzOP/x/qRGqrxqvURWSwkGO8LQirO+6M35GrXRtfjmFqkadYYoHW+FGTj13Ik52Lcxoc9LJbtdLX9UNSl2bfA0zHuud3UTTB4wDCxiuRLW3vuDJL/IqgIy8JLflnt/EGZr+Wt142X6KDkOj25bxsy++Xwcz0giiiG0OpufP6FCvz421RchsEx7nwfwGeEV3zDbGZTyQLkhfcbLiqM0cD4GkWxskboqRIJ5T1hvalhhKz5w9YUYtPikj3ZrDB9zO7p0+5auSLAh3bi6IZI5eDt/7PxFZS3ERzDPIN7X2g==
*/