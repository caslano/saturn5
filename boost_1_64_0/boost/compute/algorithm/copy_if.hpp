//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP
#define BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/algorithm/transform_if.hpp>
#include <boost/compute/functional/identity.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {
namespace detail {

// like the copy_if() algorithm but writes the indices of the values for which
// predicate returns true.
template<class InputIterator, class OutputIterator, class Predicate>
inline OutputIterator copy_index_if(InputIterator first,
                                    InputIterator last,
                                    OutputIterator result,
                                    Predicate predicate,
                                    command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    return detail::transform_if_impl(
        first, last, result, identity<T>(), predicate, true, queue
    );
}

} // end detail namespace

/// Copies each element in the range [\p first, \p last) for which
/// \p predicate returns \c true to the range beginning at \p result.
///
/// Space complexity: \Omega(2n)
template<class InputIterator, class OutputIterator, class Predicate>
inline OutputIterator copy_if(InputIterator first,
                              InputIterator last,
                              OutputIterator result,
                              Predicate predicate,
                              command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    BOOST_STATIC_ASSERT(is_device_iterator<OutputIterator>::value);
    typedef typename std::iterator_traits<InputIterator>::value_type T;

    return ::boost::compute::transform_if(
        first, last, result, identity<T>(), predicate, queue
    );
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_COPY_IF_HPP

/* copy_if.hpp
3RJm6TJGUuYsa7fxeyZcIf7yGb83RQY3bO+KW7oV7EPaUWrpDUJ9SCD5PH+m9iIezyvTH3v1G6984ug3NN1tpN+YRRwHMfqMujKu31CZQINwv1FBt+HRd2va+zQI1+UNm+Lqu8rMMjLrv/Lam89Zx53jaVOn4YnGywXpkfHy+vT48fLm9PjxcgHkfuIm99MxLk7RM94nMx7uCnPhk8iu/yxSl6NmzrzGxSo/y9Tn/WL/yO8xz6Hyl5m9KlOPybjUHwl/4fyK+Tr2NfIbxT4du0/k9/jdftNmYf+7yL/g13kO9X+RlWnkiyrWlhcXsqrZ/A797he2rBXvbmU55j/wa+Y0qrFHwigO9iEahs6BxMgfU/nWmaF3DeaXkUjdD2oArBbZN/xZ4TkBsfv9o63zfPt9kXQMiAkXxP9O0D29nhC5QIIZ/4q9qRnP3/950J7i22t9YMa7PaU8k018+THxpeCWadZ0L1m5uDBYfJYJ81GR3elfaC2QvaWeypa5gGWrli4U/4QXtSa8SBbph8fNfxK/r/uDbamadrSdGzhaxo8X944dK63A3gz7GJkviphm2MfGuI0Tu7vpbK6dXCbYLiutE7fLEhhul3tdnjv7XeanDhg5qevidsiK/21bbdxMnRX3Y8Y9Ug9xl7pBfcM9Ut8Im3sY/5zLh9wr3OReOd5z26l9Q/MQZA3nXwm3+rj0DcHZTx4EvXs633PD1fQLKqvvWqyKmYvIgEflehN9/+fEa7lTzDwdccS8/1PZLCTdlzhzYRP4u2x8fylpDeofCukRy1dVFEphe8zXqvxw048tEPtRy61fmmDkh5q6XKjyjn5P56AKjHzAXm0t4WKq2dPXqx87W+SPiL3U+O8f3/Z1HmGyXE+0o/sv/Jh2XKlxraRsUqyV81cspmypxrRh7KxbD6XPyhI3W9zeFrc5PM1HOZ7NL0kbn79qTdRcwSKR/R0zXN1M39L/K+1bzBwFj/lQ01AZ6oH4y9BwbEecbnv9ZsOpIvOF1ZQ+IRF7XmZk7mkOBrvUq4KTjBPLXeaT17i0zfUubXizy3xypct4Mg9S5rhJmct7H9sl/Zb1cnbI/oKxO9+z2N5S56642Fr5W2SqvjJ1Wx/RS0qLaPDe+oiwn3ZGn/USdmTsc23b4zlFPTf+Opi56lfEXmbPsBOsLHN/SuavLuakp/OXLrtgaWSvx9dFdpE91fZFyUqKmSFfsmS+1p8s+KbILrSH2/Uttz0g35LrC+xRdh3J42uZOJJeK2r+pOff7dA7TTp/sknsv7RKmFu7VN6p1XDxJ51mVH+UI7IJZn6qndhb2R8Ea1J4vlTS0NXOo50762ZkTnuy+OtHjW6u88HhdDwaSYeZD+a+0aWFn+HUV43jLDv4vt419G17Wugz0d8hkFiH9/Vasd2ix/t6WeqnGj/j5Tl6Dn6suN9znbGnWqEx6DHMENy/j2mGn/nYoTHm/VXv88W4P7HniznbVZbqaRzPJnUvMHtGm7KQNjFRyozxZLazv2+oiXkD0xjzLOYJZKokDetRTIZmc4ONw7Li53PNnrS27Imp7SPsv6WZ53xB7I9Zo2VmP+B1Ppn6a2bmB5/Fjow1kjTHzUuqTB+Je3qsPtX0pW9IGLcwLk+z9F7F6VSXyvd/Rq9KeXica0Z5m/frZ7Wx5PMMpgXmAdWv77WlvEt7hSbOCwlNtaKefZD6yTXl8KnYb3I+M7UcJhj5u3jqlXrq0D8Sma1iLzB+2sY+V027rpbrlWhvWoifUuMnR2VofT6fPmtbnVCXjj+nftTcT61rWpfqSHiL1E6pib1JlHwFHiLPxPlyvb7WB2d62lAfkvExIdM86xx1YHut68HXp0s=
*/