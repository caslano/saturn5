/*=============================================================================
    Copyright (c) 2016 Paul Fultz II
    unpack_sequence.hpp
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP
#define BOOST_HOF_GUARD_UNPACK_SEQUENCE_HPP

/// unpack_sequence
/// ===============
/// 
/// How to unpack a sequence can be defined by specializing `unpack_sequence`.
/// By default, `std::tuple` is already specialized. To implement this, one
/// needs to provide a static `apply` function which will unpack the sequence
/// to the parameters of the function.
/// 
/// Synopsis
/// --------
/// 
///     template<class Sequence, class=void>
///     struct unpack_sequence;
/// 
/// Example
/// -------
/// 
///     #include <boost/hof.hpp>
///     #include <cassert>
/// 
///     struct my_sequence
///     {
///         int x;
///         int y;
///     };
///     
///     namespace boost { namespace hof {
///         template<>
///         struct unpack_sequence<my_sequence>
///         {
///             template<class F, class Sequence>
///             constexpr static auto apply(F&& f, Sequence&& s) BOOST_HOF_RETURNS
///             (
///                 f(s.x, s.y)
///             );
///         };
///     }} // namespace boost::hof
/// 
///     int main() {
///     }
/// 
/// See Also
/// --------
/// 
/// * [unpack](unpack)
/// * [is_unpackable](is_unpackable)
/// 

#include <boost/hof/config.hpp>

namespace boost { namespace hof {

template<class Sequence, class=void>
struct unpack_sequence
{
    typedef void not_unpackable;
};

}} // namespace boost::hof

#endif

/* unpack_sequence.hpp
UpNBFGLmiOWAnkucsCwxMsWkap1nU/JZkKcUdqbnfl4ria/f7DOwnqAdNuow4Ub4xxzO9ihLk2AA3ioZTmyrMYx1enz2Gq+FWYkZn5kl6tSXk2zcIcManurTNFC1InMM+29zDPtv55n234DEkP23PTxafpGPKWYkoxDoMJzG7OXO8OLnMdG0ld3cKM6wBClQPzqR9NzCQothkLoPIqQJTE9kC6IbB+cgxcLBhWe7Fj2HZlZyXKOzsDqyJamNMq/jQpFaH4MX1LJwsBWKAj7q0xDVp2rxS5uJELkauiMSNtjX2nMtoumLVuYTNdpLiJf6BF61CpWvRt8pWnCeEusNm14pbgIBZqs9Po9wPKuGcWmjYfaYcKSWDD5qcB9EvYhXpvPz90D+yTCeKz7qaNrZzrVG/QERJ7VMrpp0u0ne2kQOGs8Xc/nmyCj3Ipw/RE6eEQ26WhHI5XBfpPpRF8C9ocp22JK9cSfxxdjCKB9+WunhaabEpOlKaQaqNJxCJTtv57FWyo63uZDS5pe+QQmnmyXcF1PC7h3HKuFPqgSdSrj48Hb+FdmpjbMovvjw+NuN+DEU39GMv6bZ/X8xfwX/npoYb+/XMinunemH2goMGy/i83mv91C2YQKnaltV1LV2jjvQXcWlGuQsOm6PXn/5pPj6Cawk+Lf3SYdnbj1PT2VJr0p7cABJenWVUhGdyM5CCov09dAWWtRCa5tMqPHLUhAqhTNWmBkrDsvYYGbcNAUZH5YZucbuRSnBNKxP2nodV/Pux1lEBZ2DmLNRWCSPBd/F50+rE28IQoFYSkl38erTKheiunEGKuwfZjClm0MlPCyDvq+zTsN8Sv5o+GsuuOkI8aLaeVT7WJms/wqwThhTtpc1zDJYvgNEPYKsp5FRhiQCRb3xhEFxLdphY4e+ooqJeAym3kaQz0+BA3C1wT/uyGciWpnM2kEXl6B1GSdZCyaKvhVTXuijwfvbNwyvC5ROe/91+LK52ho85dGTClmHPPQvAl1RnmFwKY/wjipxCYLwUKjDlFG1GL6KDzJgfT20m6xq6qfj8BWPvshTb17ceyApN1MaMaAwihORf5jhv5bhbukO2AwPr5cKwS7xwCvoEhtcvgNBUvz1jfdVuoYQAuusXrHhDTNoljKiLGb/nQNZigIRfqMuj5hvVrTodgvNAim89CWFl9F6Ga+7+wAB8YhJIAPJ4So77M7+ycRjYBd9n3lF3IcSkCgj7DCSSqnbcBllzdatVHYald0N8pWGR/aW1HXD+KFazNjFtIACdrjYcSMXO3YMi0/kIaiyQhRjGqsM4ZbuOFUo4ekU5qGnzQcUZfNMoudlk52EamarecTv3dzjwWwjLfyUwdRc0L9GUF9QJFumedOcxftpFpuf5wKxInIQwUMpbgXu7hX7d6vj3SFlLzJhWRhpIBF6XwyO9xt5iHiaub6WVdrtZmRAReYbkb/RZh4eeRIiGTuUdZhOBTK/n639X/nRyhW86fnlkeCNlB+rxWKB5XcyuA1q2ReE+JCWnrCyoiAW47tWA5S8iAf2RLnfBCVEovchLH9PGLuISWbK8EumESUa9hFliRQDSz14Zxm0WRTWpsTT4uAIQRbzxYenwQxEBnbhdIOlIQ2/6It3Qkj8tBiF5UkDgrjCrYbvWWkz6tOVJlx4DRES89scDVzN1h4AFH72EsE5AqLrpajHc++Y23+5hSBCjfjbFjOIsBpoL176NwIlCCNostTC0nQBVfrcGaR2REPwAnUXA6QMmHxk4I6PI7zKQ0+1bYdtuf605bKx5Qo6S2DJZudOWqm2HNuxt1I7RCWLaT3ypRTTQuXKdZE2IGYT3WfY//9E7pP1tdC94lQ=
*/