//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP
#define BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

#include <utility>

#include <boost/static_assert.hpp>

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/max_element.hpp>
#include <boost/compute/algorithm/min_element.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Returns a pair of iterators with the first pointing to the minimum
/// element and the second pointing to the maximum element in the range
/// [\p first, \p last).
///
/// \param first first element in the input range
/// \param last last element in the input range
/// \param compare comparison function object which returns true if the first
///        argument is less than (i.e. is ordered before) the second.
/// \param queue command queue to perform the operation
///
/// Space complexity on CPUs: \Omega(1)<br>
/// Space complexity on GPUs: \Omega(N)
///
/// \see max_element(), min_element()
template<class InputIterator, class Compare>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               Compare compare,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, compare, queue),
                          max_element(first, last, compare, queue));
}

///\overload
template<class InputIterator>
inline std::pair<InputIterator, InputIterator>
minmax_element(InputIterator first,
               InputIterator last,
               command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<InputIterator>::value);
    if(first == last){
        // empty range
        return std::make_pair(first, first);
    }

    return std::make_pair(min_element(first, last, queue),
                          max_element(first, last, queue));
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_MINMAX_ELEMENT_HPP

/* minmax_element.hpp
pbfWt617X89gVv9XfLvIxz72wA4R92Bepvhc8sK8xnMjphaz1jvAesbbnFzPCJ27llfZsj56jTFytuQS7OeI/VZfS3YH3YDrEk8Op0BP9MT61miY4PUn+DpaW0kwwboPaYwTvX5y2DH0TN6a8uI5Zq9xFWkPknhzvTd6buDbKG4mrVa+ZPQDnOjNDKQheb1b5q55gdNjZP4qdJ6nLPEXk+aA0+rOit5CrAGebKvGM4B84mfS7u9r4bndesJzjrTRL7zt5RpuMhGPSNmbm33Efol/hjeFOeMdRlJ76qGj+AXT7uprb91Vrw7ss5wXmbPK+kv4ed5PeHvSwXOV5Ked+AXTau/zU9O7SEvrwSFT1C74vlnyON/3Al8jp3uS0BV6nOc1b7XVR/vt9ZJWCXufm3LtVXwb3oR+3TTrBk8cJ10PRqduF6sI31Tdp91Gwp/ke4z8f6x1r2cnVS6rqTV1Uz7bHg8tTJ43OMbDu1ZbdDf7pB/u8Jwn9Z2kZ53vl3yf5/vQUycr0rpO9mmRvCNWGa5aCfOgbxsSNj09C73p4h681mTfMite6ln7iJ53RhfRNGaQxkJJ41e+X1hnekZ6S9jTjrtJY5LvTI+mYfqqplFTeUZ5yFx2rvQrzmHVPdxrJN2Dvlne+udY9dDxXCVhttE2d1q3cOUnPQc4dS3KakrL9vaNsc73pVqpuiaIkfq80crAZRh3iSEqw5Qn+czxnUC9llp+pNh6ktpA62P6TRz1+pRnNHpw+1gTvO3Qpz7V2umdYc7jv0XbKEn3tK+U/HzlKyXPpqzUuRbVlLVAyhpnzrB7SOztXfrnas+VnuGO/plVV39GxuqXEjeduAE7tSH2HM4Dz0XuYAS6zE9Cb3eGnKczg3l9axM51wAZqpkJXRL6iKxTpPN0rpXytFU7PUXsUfXvRzqXbRD/TJE9Gs29szl+fyXdg5hPMJ+q2aX3+2LMZ3pvLVXzudih3m/XW/o79Nngsm/+kdlm33zYWeF6n3KcFa73Cz0nvFvYWSe7TDiZv82ZocyTuMk86biHdmpmyS+wrzEFDoUPEXZNidz/5uZUOu6h0pYPJju/bRFW6jtddWNsEnsX77n0xXjG+U6MjIU6HRfVtm4PjUvMdNXRcY3Yu3rPo3828UQzNqIlbpJZD9v6La6SsL29F1Mivh9Yz2F0razptgpfL5k13z/Fv7M566moVNbOnP/UH73QftezD/8qcX6O3GB39j43NedN3Spxf82+zzPNGsOydYHIfLNDwvyePc+Zdd+ndL5O1fzcI2l7PZOtLtyjPUb3xXaJ9661wUozZxlOmlMnH9qKvDYz6/dann5sPUB96MdN4Jeq8+FDzEchfbZY/8bdrBErIq8RpZ/GzbH7aTOVIaUvyJo2SeVHaWPs0saqpwGGrfmzzVpe8uzojxfrivAODEGY+er6Y8ncujPbGtIf68J2MXpUzhP7ecgjecL7odHVcpaEucAqts8v0nSomdD+N79Wqkn7mYbJdugcmRdy7uL14n8isktNNYyeH6bnBBeZMIvD+6qZzz4T/zTn2bV6/VvFrzd1SH80/ivnLiqtqQnRCxXa5xw6npLs+VDyU2Hnx5ybvVz7yBf+w58fFugnD8519pPCsH5SFNZPUnErMf3E1LEdVtyps3p6jUw5w769VptnUJNm2LPDNim46Ey3MpWPkce8MulnlTmljn4WSb5cw/c043Wh2JM9F1heqfPWIc+aE034buZM4wqxp3ousnyh7Wvuuf3LZV4wcuS9xR5rdM38TOI/bnUnzXVWvNkf8Bu9jtyrjT1OrlEd45x7ysWvtaeS8Lvq0sA9GKdrJBl0uTev91Pn1OXXcm8emeg=
*/