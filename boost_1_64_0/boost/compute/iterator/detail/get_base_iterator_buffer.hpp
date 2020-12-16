//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP
#define BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP

namespace boost {
namespace compute {
namespace detail {

// returns the buffer for an iterator adaptor's base iterator if
// it exists, otherwise returns a null buffer object.
template<class Iterator>
inline const buffer&
get_base_iterator_buffer(const Iterator &iter,
                         typename boost::enable_if<
                             is_buffer_iterator<
                                 typename Iterator::base_type
                             >
                         >::type* = 0)
{
    return iter.base().get_buffer();
}

template<class Iterator>
inline const buffer&
get_base_iterator_buffer(const Iterator &iter,
                         typename boost::disable_if<
                             is_buffer_iterator<
                                 typename Iterator::base_type
                             >
                         >::type* = 0)
{
    (void) iter;

    static buffer null_buffer;

    return null_buffer;
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ITERATOR_DETAIL_GET_BASE_ITERATOR_BUFFER_HPP

/* get_base_iterator_buffer.hpp
rnjxfjMXQfy9sMtr+GkzvI+0yhbZ3Ghsu1q9bYWKel+weMsoyoO8Qj/SGW1pgPXKeu+o85as8P0wjUpVbfOd3FzalOePmW9t4tILxXt9NcwmF2bly+q+V9dN3CbVbqQQrPcEcZTyIFKiEOwBxw/Fv4jYBwZ/ylI/IlUesGbgTs6u0LmsDqyztj4YttET2nf4Cyvj+hiLnZJ7VZEzuRLgsb/kgR8LO2mOZScKMzctETpHPHVvl8yxId5P6Hzi7jr3UzcNXKY/sRYFQ4Tlt3DSPN9mvAry0C3Bf7VgCdp7sQ9a7c7TsuJJUbD6cyebR+PYPKg4BA3/BcWPdz1plZZF4Tb8NEE2pIC6I9HmeJv0GOvNeFLmWe4VbXwQOdLRd9oz6wWsQ08x421EvitCblQyZoa6drMe3Q8Qq8cov2Iu99ywckviVcGSqPZglsWLdtxcsWL+nNTleC4LqsRx40SKQdspiSKKhrb5M/ad54z6RCyj9vQLj0tB0FokYHVFNYmsxhzyP6wbYzgKwqyMCg/s+poTNnspo+4hy0I/dRInGB13QxQvRxJVpNV9lx9jzeGElF8ZZvWaLsdSUwlMJ2M9eaz5pjVPeJHzXLHLr9V0phYLQ/9m6rpcvPkrg4CpsvTGll+i96DW9gcfa47lMouLMIorpk4KvRNSi0sW6/xewgpS3gEvE/CPjl5C8bS0s8Nw3FxXgyLMnShiUnUTw2Brw9JHq26jF4xvyFnBA7dMCxG3QNhd60sqsXPRW8V+M2fIiFkUuY4X8apHxvJgWTgRrnbeqX30sfa8ijweVGWPDASI6ttLXTTkBCz0i6QIuIO4FsbUNHmvGLwec/3C5zQ4Wl4M8M75b59xH5kQb5b4aWnEoYBS64mFwTfGzfd1ZeV5HndMfqxOmlprYyfFj7P38qXvx07VxIKQ88LkvU7cj22bEBcU4mpJrt7Gha+gR/emPc7TQDcujO+p3Qd/rr0PBlBcCBv5z/Rzslex3HOzwHGu+d2L+AZm2Xo+O26cOkBb2tHSBiugIV6+oGE3r+cq3QOasfk2cmXuBUaSdVvHvpuCZm/AwD+9H5jGyQp3JW++raARk9p/0xaM9l8t/ae3k3QcdRv6fRqftDsI+siDrZGbev5OhBV5ojv7TXmFDJl77jwKh9TZkPnTBntycuLYjJNH1fE227WVZ93GIZO1fod4VwM3Te/+3EdOB7KC8JfTMUoCYt7fTaehJi2vSSepLW3t7jptbXO40NIedg+dJpsBdo5P3W+nnmMrKwqecHU70ky++2hj+DPjPCiU+VxcZGACDSirrG4/2iawJ4RSoznazLSWfnQ76EqaBGBs7thJdOmPj0sTlIL48NOmb3wQpqVTXnMKDjVFqZ+17/v0uH0glVNL+A+ibi8cB846uLZtdXA7MBiEujD9LeapHTYWAoHJdwFjX7K1+TJ3W5j1pfYt4Q1AMy/N8P3SNghM92Ktre/FGwFnXqBp/X/lxsDoagXt84F9oMtvkcnbFUoWp/tD3QzY5sAuZge++/J+ScftlpHf7xagibbXSwDm1bcERkZDrt+Wr26QSmvf09wKGO3Goa3jnQ8Y9KaeoC/dxqBDwxEd/qgaXVZB1+MvuT3omAfItX8HokHn6UNS6gHg3nxH4LShBiD00NadCGfrxc1l6LkDd+7QVUljwPymi2kUMDDn76JjvON5q/NQl/vd1cKokpBfC/R+nTl/N42ueJHD4YSuP0qWJEESRlHx/yoQXX98qjuPO+vu3u3AaRfumxsDTdfyHcC080eHGvmDgcXlsj2+br8bGO1Ct6XH+0267Z96vwMmXfmngn7gTqBrl7Ht91y+C+h13dSMxwdpPuk=
*/