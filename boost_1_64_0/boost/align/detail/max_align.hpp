/*
Copyright 2014-2015 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP
#define BOOST_ALIGN_DETAIL_MAX_ALIGN_HPP

#include <boost/align/detail/max_size.hpp>
#include <boost/align/alignment_of.hpp>

namespace boost {
namespace alignment {
namespace detail {

template<class A, class B>
struct max_align
    : max_size<alignment_of<A>::value, alignment_of<B>::value> { };

} /* detail */
} /* alignment */
} /* boost */

#endif

/* max_align.hpp
pm9vpu/K6UdB7sMaf3CggV/sfao1o0g4PvTmZ9JZlvwaguKOhF/kVObG+9qci+h5N6TAl0qkcl5enH+/c/2BbtVH318JIc0wSHs+aUAhHAYQDfMLklQhkTKi1PUo1CrduRm+DkS/nP+NUVVlpHoe5H0/c67/spt7XQrbiU8+o85BF5ZCyI2+/V3YsH3ULHwaBGy/KdRao2spdbSE2tAS+raIGFjnEQEbjqtP5oE24UQU6X6o0I79/bLiHKO7sCzE7ppJaSmLuzwq5Mae8Q1poBU5h1XnvBxpv2NOWhxbisF9MD5eboEs4bzDnRt3hNEnMQ5tNx1CKfNmd4uQa+7IC8AbMiCQRdjKh4lEJ+pLMzxMsBWiI9zDP950LlwRR/ekQXE8qrv+jlEVynFySzmBCCO6jgjpZP/X30ufnUoLexj70uuIU2sIdiPUshI59RUjeZmN4Jpxo7i7PeMmZyPZcEk2g5Jdh2SURH8vgePb8MdVKdEm/htQ64u0BKDwhRo2rzg4pDH80aQofzTwbN+lEgdpbGNiz78BFvpfKxv6lyX+5Xgb+p8l/qd9bOh/lvg+NvS7ZEu87rGh/+VE40/KsKH/WeI3OWzof5b4y1va0P8s8V/E2fTfEj//NJv+W+JHtLPpvyX+w1Nt+m+Jj3fY9L9/NH55JNy4/5b4/nE2/bfEV2XZ9N8Sf2tbm/5b4r1Dbfov8VhAB7F6cj93yK1zLbY8W3hrb6b/mjZ3I/23IKA2vp8CxItOr1T6MYDvIT9pFWcA+IFGAH6i8xOj/A/IqPDgiWeZnK4ad2YEfywTh17Mwrzl4CvPG5yVgSeN8BF9LGZb3cfiOfHNWfpgCXNBzftnCG9xwBGH8Gz9u2Ec7kX4lYTI7Odwl/6RhJcg/GqE75FwL55ifQvi8KMED+5aaEmTsG7bP3t/qriwx3xnWb/pBgJfnu5SbzABxwX/Li4MxlUf2V9rxvGUr+C/n+GvrpgBZV/vGP93RnwLjv4OiEJD+O9n4x+/KpMTdx9i4//eJn3iZtke3EjeCP5tyxdcaDdw7iP4P5RcQr4QdNZKsAvg6EzVJ6MvSgYE/Wup7YomqX31DCr62Oe9Yf/sTEOVBQOZrf+mNT5BEgB6e/ibMKG33a5cSgE4EieDtBIsGRCppm/9XUQDif3QVEOBjHtR0w45tf9JzUVaUAmiUQ+qZoKSpm89h4nAxrDBHg6AON65yvbGJPByVHiKYVC6VN/vP8PsO0bagdqUeR4+uC/O8Oa/QRTIrfqFbU0ubCo6n6G3YkxiUgayVLzJI+BcUdm0zkf7f0Zj+Mjf6mshyHKSkuqx67GC/76cv8ZdZKSrbV0Xjhz5/ivpOWGPrxufFyss8Sta2cC/Jb4EtJBj+WMtUOm1WqCQ2lYwKPSTmc5cb/iCvSTsYJMPqeyQaroY2Jiqd8lgVOxUMvkLoUL4yWJCiXhfuz3DtLXWNZF+Vv9wn6lH4+fPPV1hwbXQQjRvmcQW6iQc+qpTTdgYqTj0+S34ttfHoxWxHW23BH8pjPt24vM4MJjQ3WA39CCcLoyX/G7MbtI3YGmdSJ02+/7JLK3qY9zfcZ0hgayXC9kAhf7pAHOuyHnYY7UyV18j0/qAaQ7lRn1qBxIBJcGC4KWJMFSSoH8xxDp/sNe6Uc0fiTfs6GDO3yXxMn/2SqjZx99Py/nsT8QhLnRi6zeOdEVPPup9T4Zm4Wki3k0XoANRCbkHETcKo+LAFaSCOV+Rcjie+qTVDX1w1uhXZuK+FjrfQX2GlzclvJwA5AYCIcSFIJXFqyrenJWJb20TXRrb2l8YSapNZS9PZdA5E0ZefD3IvkoHoTmM7YXKNFTmhmPOxHAaxCo=
*/