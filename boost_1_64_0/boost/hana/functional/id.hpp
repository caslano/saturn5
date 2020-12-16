/*!
@file
Defines `boost::hana::id`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FUNCTIONAL_ID_HPP
#define BOOST_HANA_FUNCTIONAL_ID_HPP

#include <boost/hana/config.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @ingroup group-functional
    //! The identity function -- returns its argument unchanged.
    //!
    //! ### Example
    //! @include example/functional/id.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto id = [](auto&& x) -> decltype(auto) {
        return forwarded(x);
    };
#else
    struct id_t {
        template <typename T>
        constexpr T operator()(T&& t) const {
            return static_cast<T&&>(t);
        }
    };

    constexpr id_t id{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FUNCTIONAL_ID_HPP

/* id.hpp
OZNBJDdy5n3yiM3ItXaDH/vYY9edNVTWPYcksIZILukX9nIsDGOfdQx7y8l91MzDeutUyj/GewOsu+zdRg4zI3zJzb7sPax9pDNyR5q3+wzeHvoX+Bqg+XpEy88x8G1qHsNfLVNZk/m7Hezy5K16X2OPwePEWuwDvEF+LY51DfJZHw1hL//j5P/J2/XchpyWYp04A3tQ2KO0djZ7M/qwZ4A9fV268htQ7IUIZV23KHsEDvVmLz3rpW6OayTrcg1usD7CvfkeJXfVmpw5OawvX2LZrB2yvpk8EOtRMSuQ+Z6sjTKW37LG1DiUvOlu9gpcIme4FD5+wxoy5UolsY7Ffpzwway1kMN2eZshm6lrhp4ZObrTX5LHOmDJumqsGRRi7Ym1mtGXLWNs/vvyniWbq+fJ49Lp/rgk6/18zX9zbLJzX+5syh7kzabanz0POUTWOIqxJj/4LP9PYr00nj0BWd0+/PP+P76IfDXrfFvPpC6fMZv7bowqnzmbkdf8jr3p7M/4az4omZzBWC3ZxB5e9OtBZUs8jXwNeHCZXO3ZI5D44GduGslehQMPrufmedbWeqTsq+JnECiY7Z+Pb5FsipfNOUdqnobzd2sQDdqBLi6/XP6BBWAqWA4Og53AlInd/H8AMP6+60dBlvS0K32yfuZOr/if16W7++XZ91yL/H1F1gIaBtgPbHO+KPb2NHxwvyqTg85b6sFl/HKwppovJe/+NVsV+U/s02lXXgx7RF+1HVL9PY4MlWQfTR7s5mb2yQ5kL8eDcu+1r7JfOJT1+AbywHLdK7Ffhj2N6Tf8ub6i6d2y/7xf92xwHrNPKfqin8WgsrezFrasmPmsh39Oav55P++9Lejqpgf3P6Eyfn88/Ye/L+95sBwd6I+dn8Aa1FL2o+dlD3ECa7O8u5KFvUBbq6V+TgZ4mAmYz5v/B/u5/ubotQjK5OBPd39bTmzME9i2XPQVH1ssgDUB1iJK5eZ/1iKC8/C/u7eM5xY4yRpqXsoLe/byQS/Cvs9A935L0o60I+1IO9KOtON/4SjwC3FTN+9rdzmCMlS86vo1v2r40KpqrXv5JLUG/nf23PvO29T51HI/3zmHpf4/0kf9f7urv7p+Tt3/Y1NF/3624zs/+66qr259dd/x3er/9aVU+eOxqlyOl9T56jF1Xv2svm+c+n8UexV810er+ls391f1L9b0q6pcdd2+Sbzr4mvfZ6q8fy1V7sImRT/Q0lbPKWSr+h5T9eVmb5/vuTksdd8iXb+oc8tzqr4uF9X1DpNE3c+8xPe8W6Luf0TVl/i8Otdmr6vvvj/U+dOOil7yFz/Fj8KqvoKhij6VPf0++l1V3+Jx6jyuj6LX1s9rEKjoGVo4qh0VRfG/tq3Kxyt6llHqOW8W8FP1P6H5f0edOzRX9NjD6lySPWq+c209zln81fmSHv/1ij4nSJ1vxKnrY4ao6+MOqHpn7lbXJznqemAPP/W8TqrchRBHnZdqOVur+bNanbf/oOjLt1rqOTt95XnnV11PmqzOBRPU9dx3/NRzp+rxCdZymSSq/5fVdauVHpfZ6v5BtfU4nLaVXCWp56z3V//3+Uads5BT8/VnmSrf5xE9PtnVuXI6zTf2D/v6c1CVK3pbXS9YTNG/H6n+3ztGlDxaur2d9f3P2Gp8grUcva71ZLcqH7tMlV9MTsnXP92vsloPj8xU9JIzdT8GavmvJIpeUut7BlVu/j51/7N5/VW9oxQ9No8ud16d/c+o+oZruQy9q+4Lva7bsUjL323Nr4vq+nshtuK7vv5pbVV+dXrdj0na3mxR1xuwN9A3juxT8t1XVT/PT9G36nGtPdBScnBSPSexnebDVj/1HD8=
*/