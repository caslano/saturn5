/* 
   Copyright (c) Marshall Clow 2011-2012.

   Distributed under the Boost Software License, Version 1.0. (See accompanying
   file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

/// \file  partition_copy.hpp
/// \brief Copy a subset of a sequence to a new sequence
/// \author Marshall Clow

#ifndef BOOST_ALGORITHM_PARTITION_COPY_HPP
#define BOOST_ALGORITHM_PARTITION_COPY_HPP

#include <utility>  // for std::pair

#include <boost/config.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>

namespace boost { namespace algorithm {

/// \fn partition_copy ( InputIterator first, InputIterator last,
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// \brief Copies the elements that satisfy the predicate p from the range [first, last) 
///     to the range beginning at d_first_true, and
///     copies the elements that do not satisfy p to the range beginning at d_first_false.
///
/// 
/// \param first     The start of the input sequence
/// \param last      One past the end of the input sequence
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
/// \note            This function is part of the C++2011 standard library.
template <typename InputIterator, 
        typename OutputIterator1, typename OutputIterator2, typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( InputIterator first, InputIterator last,
        OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
{
    for ( ; first != last; ++first )
        if ( p (*first))
            *out_true++ = *first;
        else
            *out_false++ = *first;
    return std::pair<OutputIterator1, OutputIterator2> ( out_true, out_false );
}

/// \fn partition_copy ( const Range &r, 
///     OutputIterator1 out_true, OutputIterator2 out_false, UnaryPredicate p )
/// 
/// \param r         The input range
/// \param out_true  An output iterator to write the elements that satisfy the predicate into
/// \param out_false An output iterator to write the elements that do not satisfy the predicate into
/// \param p         A predicate for dividing the elements of the input sequence.
///
template <typename Range, typename OutputIterator1, typename OutputIterator2, 
            typename UnaryPredicate>
BOOST_CXX14_CONSTEXPR std::pair<OutputIterator1, OutputIterator2>
partition_copy ( const Range &r, OutputIterator1 out_true, OutputIterator2 out_false, 
                                UnaryPredicate p )
{
    return boost::algorithm::partition_copy 
                      (boost::begin(r), boost::end(r), out_true, out_false, p );
}

}} // namespace boost and algorithm

#endif  // BOOST_ALGORITHM_PARTITION_COPY_HPP

/* partition_copy.hpp
MjFZfcxk5THnfDdjaak/z+aEQ2h8K+TZU5yXMZEAP4Hvz4/vd0r0EA+kXXIm7mH8z9FDM3/CmXz0+4UuHbBqZAO6IktVarEekiki7C6Zz6Z9L95p8+cbZiYxfsGBkI4O3cV8P/cj3u/ToXWHtcnM6dfEUImbfVdZHb4BY5VUWFNQ6csgdclVdX+U4744gH1ltXcQLJWR4Y3bgXeXNwPaPavy8jFANermtlX9rfwXxQ+v5uLnVNysLSgrY3hBWRCgBeV5LCgxyks1Dc2v2v8ilhOR+hH2w5sJDJTzP9fliA7ZmhxR0jU9hhZ5U4zhEqwh65usQ8qMt7hPH2xnFqGz1WqyIIURWAzei89BaqUjKR1k4ybjsXYXC+OxvbwAgnIRLxM2yQM42RM3O6eHJw7rZF0tTuptJURwlRYTEhgqgaEK28PAxIw0NbUxk4sdIGOcYbDrxPfxIZua+qnIoCP/7HjP17MvNxVmVcab8MrZ/kyuKFXAX2VGOu65aJVlHcrN/j2I9XBdm6xDuNSwZzbmrqnwYo7AgEbQ1bNhDUwhncL6Awf56jrlDhAEmQcfgmkn3Xh7gLuN1vOnsWNy+57qSh2cJ4/EtagJmXnyZ2RoHlS6rG74Nxz96/sJjwWbRJcspQXD3wukFHrP1WTJ3+7Xj/Ho7C4b4tJNNwqhO4vPfIlcWRUS2l8XfCwUX8m0M4W+SogtbOjEYSqdWeuJ0KZKFR1jUZBiDnAFFy2enIQ/l965LMk0F/yobTN+tNtl+VhOFPxoi1t2fGB1Z1QRP23Oj7L8TfjRdsGPBoEfbZjxnEvG5zHI54gobxYRq9GXNFt2vAe1vkBIoM1ZWX4k/roimJz6Uh1Yx1rLVm/qAjxFfkNECX1sL49G0ZGu6Lm7L8UdbsfSJBMG40xXQQD9MlsqnlFjN3na0rCciUlXdz1nxM7Okx1+K0WgRIvinhmJIcQIDeX4nhjXwVBT0+BWI4HHNJPVX0/sCRtJ/BcVUN3ns6h/ixB8G9dAwPUNNpMJbswm5lOAO7leEu17/dPw9v0O7bv5pVbb9xmZdw9BBo1cni+2Wm+e/3rRvGt+onkVH4rmJTRpWoMprGmdRNNifAOfVc7feGpNC2vfjk8i21eypNX2/UjtG26MX6xfb9/eEaJ9Q36ifR/uFu1LEsNnMpqYFD56vVdzEy2+gQsUx4ZTbWLuEHFM8d3HGr+oDRlPDoaCVrLTihuDD/eSUgpJ63sWWqEdObBygzkISTGsTFc6acifJpAHHFiJqIxVvG+vQRtZzytuo/rO7bU4ycSXUqHQ3TxTyHjZ7gJPCuuAfbGdhYDXGBLw3AVHELBDMiS891M8HUjCOw8S3vtpfKkxP00J5liFaHeYRbvR5pxPZqykZSof6nyKdZokyfFEgxKc7dndMr4aumIa0s+yalbfEww+BZEnev83iSZ8+0f6yn1DZkgD4MxS3QX7HST18h1GNiSOL9020+Io6+XCzZSSdPRpfq+pabCntoi7v+V60FInhnMcHSdesB3SSj1G5nrISPmKLjd5bJCsFhqvhX1IZ90un6yxt+ch64flDaojO6fwLM1ffpGq24cHJbbIY/vww10kSEKT5QEpRAWT8sizAYcqnZimB4ElKeNPMTR+qiQfDvM3fiPu7ayD8Rma2tUTW7JnagdgkG97A9bBm4v3z1IKl/K5bX+8KmdvaVDZqQs+ItwSyKKtPFTG7vsA2hMWthfyR7B476zExpI900YjOOtFRSp+zHcNgFrek6x8+QW1XqHWz5d30meC37CA4HvbzEwlnj+wg3JGLWQJoWQiKpCBcG2O9hD4Mr6W/Ms5euEuTeENfKWmWB08+beraZlFi1I=
*/