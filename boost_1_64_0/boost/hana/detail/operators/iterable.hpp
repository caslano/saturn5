/*!
@file
Defines operators for Iterables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/fwd/at.hpp>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Derived>
    struct iterable_operators {
        template <typename N>
        constexpr decltype(auto) operator[](N&& n) & {
            return hana::at(static_cast<Derived&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) const& {
            return hana::at(static_cast<Derived const&>(*this),
                            static_cast<N&&>(n));
        }

        template <typename N>
        constexpr decltype(auto) operator[](N&& n) && {
            return hana::at(static_cast<Derived&&>(*this),
                            static_cast<N&&>(n));
        }
    };
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ITERABLE_HPP

/* iterable.hpp
Ke7BqzRvVLLzNzHNm50ObKry9vX27c+pUhPmyn6tKPu1ouxvU+V4O8vxVpb9HSzHO4nXwTFiZfgD/o3FyRVmfIxF7jd0uuZ3bL9bFu3zv6uxY3fpN0ZG+BPF4wLB2e8W42nzNMeFlPNNCD3DOIDaTui9rMv7WJehVF3GRkdGesfGBoZ8+YoMbHB4H0BCpnZgbJ+QsS2L7CRhGHXtPTAi4ldDBjdq3VmAz9p6fkDUs9rkAYft3jUEg1PPGbw1P6Lem5Qgpi1l/aweyegaTRkKjXyu8MOAFSnp3ESsl1Qwjp9XqHHyUY6TN3KcfIxt+3GF91o1rj9JvE95PIxBMZc/o+byZyvxqbn8OdL4PHGPD41JjrciMfZKMPY2UQ76BSkHPcy8f50o35dU+a6vxKfK92WW74Yp527fOIYWMhke9VNXgtiHTrcix7f24fg15vd15qfmBPU64TnxDab9JtNuSLXlnq0nZvcMpee4DZ/GNeDbcg2YJj/Kr1Mfy42NCbeyEsT2cOPqrWpcfZf1+J7WZ5cndV7q7DGJ+wPiOpm6vRc/2TuKfEJvjv8wti0Y6R0FB4rt2TiWfqRl6r3ZvQO5QfuYaxKMy8+2d/o6X87WwBvOPxX6mKv0W6OIv0Xp8r5FmyWnv9B9/XOBr3D9f4l/u9OL0GcyxhHC0n8zzrOyH6gvN2vMh8Qa8xu2c93UPkjM0dtuSU27HQr2vkjudP02Nb3O+i5LSQBIA74zRPl+L9bGrwr4XQJ+p4Dfo3jcvUr/9EfRb4jz/dpD+9s/C/3iH1Tav/i0iBNp30Sd8wPE//bytA54Tmk6/FvgyTBocczZ8N0M71V2IdcuS/S5b1mW+KADfornzFpjw3cIuq5OdyiaBWukfYodRxNKV1hIepPLJD34axT2EMXAkfYPN4k+WYA4fWd/IWByPi1CmDb81H2Lt1Tl3kHZ8C9eY/X8ayMbf0MUxXkOOX9L/kyBvQmWzdw4zz1xeGJo4Fwbns3w2UPD5wxRJ+jeoF26Rp99HC11zlGRZl/v9ZLW9i4ba+ycnowwWCYN5frGI1uOsYm+PvBV4LSKMiw/pAyCHouRP97q72I/mcJuRdjveP4y4Xz3sH/mCHscec/7Kn7PA1zaEqxak9ZTf0Dp7ytV/Hpl/1Gl4juVHfBaxJv+vS2g516POK3nfhhgAieoP96wRurCbfy3QP9G6s3fj//aDm4jy1HGcsgyH484WadHyLFO2wBZJgO/uixd7k1Io3HewrYoJc5m1VYjyjdqjcpX2xCco/ZGJ7FOZi7r+/InAybuywPH9vcprgyct8Uqz9PWCB9QakydrtJq36XbVHy9srk5Q8W7uw3rGF+HeG83XJh+60LbpTSocg8uF3ZdDNdIm8GHsD/fwfaU9lQvQNs3pfKEHobt38AxJevWrMZUixgfiA+OjzaFg7oouyboVnwb2jjdf50ifj3fP5Dx3SqPKwL2NLsUjhlDGucJa4S9Fv10y3Ahwiw37wvYtnqKa1txV7PgQqyB/k6OfOvCzv9SbZPk6ujvvSqbJLZJZeAt0ckAfs6PO8aLDzRSee/z84Nxoo4Duo/1GQGtdPYauU/lvWnxrv4Bt3avSO8xRgpd3fL5NJx6r2za/iDbPmWzFokPQH2nfIz9jLT+HdqteeUnPeZCrztxSIAvwyTLUJM6G1nBgAmfg3jYIe9x56Q3xucEI6dAvjwjnLtGnhFwyB8bncRJ4oDLWEJMztfPyA5G3TMRtjEFwjaG90vq6zP+3qh+zzVsC4NwM65npO8wtVpC4o6Jto9ZYNO2QySb7VFxC50dDrS1/g6wsqc5RtnTLM5jT1OSR9e8JGA/U6p06ksDev9lSu8=
*/