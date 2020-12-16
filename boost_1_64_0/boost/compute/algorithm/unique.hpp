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
Ne1qLJqg9j2V30Zq1Uc638b8BspuJOsdrBjjyYYpF3fmNlpa9eY1Ypx6/iGvB5PUy9PUapqxxEP0fVG+7r41V/pVon4L5buCMV6V3XTOaVKaur26Srm47z28o/XcM/qHqvdf5rJW9dbkehuVcy/6fia7APv7hbH4TWqwS9q776jvl904rnfYWMYw9u24fJ/gjJ9RLu487Lw0OEadv1dt7vn+F81kd+qXqXmpwFm7qtrcM8h1rfcTa7upvXCUdtnr6N0s68hjLOUkfW83FniJtd1hLJmNmhbXelPd+Z+x9NHcR+W1Xh3WUclYRgn6VlOMBHtey1hiF3tUX3Y3mHMTY7GZnMkUxejrvv9nLFKD8/ewNFhH30cUoyZzeVy5rKWmXRTX5dzDWPwu6tfbWHQmcx4gNo5aDTIW7EFdhirnNmSjjIVed+d/ys/VNlG+btamKmd3P5+l9Q4yl4TWW+DO/7See0+3ROwKc1mu2lrT7g3pfBtzefuWLu78T/Pifl93jbHMIOdgg3z7cL0t6ttjZNuUX2vG2Kn1KjPGPsV1Z1qHZNeJ7Jix1LJZwE4r7gbujwz1ciPZd/Ltz1n7WTFaM8ZvYj2p3x+KEc0Odk29dDH+k537/mS2uqb9/ZyN3MZC9WiX31j0Bp8xCxlLuL+PKmYs0JOa3qkYK93vfxhLd+/z7lbcYay3qrG4ex8VNhZ0s1tPLMmcGyvGOebSwljS3fNaye5N7suHjGWsp297+ZZlHY8ZS/uL99/O0uUCWXet1439fUqaNqN+/Y1lfkINnlGMPzjjQ6RpmPWOlK/Lb6z0O0mt4sZS13I2XpCvu2/NVL3u+jxHdgH2bb7qncg6FoudIHtNvo2Y30pj4Zbsx1uqbR9n8n3Nhntv+rFi5GZt66Xpu7wWb1Z/s7LerVrvMDXdIZaddnvFTjFGuuLWYR1HNfdZOC+nNJPfcg7OqZfP0e6C7EaR/STt3TPNr8ZivzK/341FzrLev6XzJOZ3w5j/3fCs9UznL6lpLmNpX1H7fMYSf7OXBY2FhlK/osaSzchKGYt9SRYyFo+y3rsU130erGIssJe51DQWjrAfdY0FR1OrRsaiT9G3uXxzUZeWxlIzGfdB+Q5x3/9TLqcYo4NYmKyTmJvTbtLFXdt7KZeV1KCfsYh7zv6f7NznhZi02khNR0jTGNkY2U3jehNk566dU4xljmMdMzQb65nzbPVyMO8BLyu/LfR9RXUU43VjmealajawFerb64zxprTvQvae4p6iVh9pvZZ8Llmnej+i9p+q3ttZb5qx9Oqcgy/Vo+vcq3tUR2PWcVC5ZON6R6TBXmp/Urm4s6qvxXpzJr9VXLfej9LFfRa/pH5EuH+vqG8vuN//Vb17GONfrTeC+WWpb3bunDCnseCz7vzPWHg/cwkaSyuXBayIsYi7z5Q0lnkHe1TWWGAse1RRubzG9e5RjChzqSG7zcy5jrFQHmrQ0FjKJdo1U37naHeffN2+fMBY9AHW21brNeUcPCrfCqyjo3xDvBY/qTrcM1JUdi3I+hpLHmIuT6veDrR7Vv0YRF2GK5cW7vzPWOpO9mO8sVhfxpgsNp51TFe9Qfq+pPW+p6bzlN8G7qNFYvdwTpeqtmJc73X1owS1Wi1dfmYu7xrLyMW+pd7ypS6fKG5W6rJJ81yG630u/XqRbZfvQXf+p5xPMsYBze5csq+UXzWud0LMna2fVc5x2n2jXJz2P2he3DvSi8YSToPLys/dF/7Ufnuec/CPepmbvoEGdv2rzxg5jGWWYi/zGkurwR4VMBZew9oKG0v243oljCX+5H21jOy2cm9VMJbhfkOhsrHgQcaobiwWofa1lcsOsgaKW4g=
*/