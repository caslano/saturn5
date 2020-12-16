
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_FIBERS_DETAIL_CONVERT_H
#define BOOST_FIBERS_DETAIL_CONVERT_H

#include <chrono>
#include <memory>

#include <boost/config.hpp>

#include <boost/fiber/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace fibers {
namespace detail {

inline
std::chrono::steady_clock::time_point convert(
        std::chrono::steady_clock::time_point const& timeout_time) noexcept {
    return timeout_time;
}

template< typename Clock, typename Duration >
std::chrono::steady_clock::time_point convert(
        std::chrono::time_point< Clock, Duration > const& timeout_time) {
    return std::chrono::steady_clock::now() + ( timeout_time - Clock::now() );
}

}}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_FIBERS_DETAIL_CONVERT_H

/* convert.hpp
ldWEVYu752ZCgQOr90CbZZXndRPmFc+PoMTDzy4wFCJfA/3IV3gl4fIjKI75a4Jwb04X+4cuvEBymjPUN7aWigqPTQEdq4x0SYXzPUEMZMfV/ESjjUmSHy3B0fKYTuAp6gyC2KgzOxpyZTPwakuopNGJ4h8RwF9uAQDnKQEMJDPaUG3+c3fX1Dyf0TrA3fmMRNZNV03/rT9Nz09BPEkCf93F03o93/G+v/vzHS+z3AX4H+xfg39onmE5vtXunG3tye+6RbKSNVcdgPwN50cKzFrPj8S76Z8NQyqSy6HYaN6DgmoxhlQLuJV9dEf2K/UJ2pyUsEoTHDrez5+dPMutd/WnRKfHjjlyf1OyT66omqLS2kTSsfhBoeP3mJ3xf/6Exg97QIoPc6HG0IlwnAF+BoROhjNa2F8ifNHtRPWvMBikw+W5ZileWitaAOKKK6Mikrpc6EcToDPEEPt6E7+mPK4FpDCntWYprjYQM0PTxCjS5MjT0C/Q2jGfP1X1zehjI8eI+22sUMWnQBWfzKt41PfERl8EG13phz2AZEqRzK1kW5DMNumDlcxoBWCvZjpSPN8RKE5VUiz7jlHMIwkJKomBRLq0c8Jpx2RbHM2gkBdHBmHc/jQTXoIYzLo7UkgymNjRu4WY82iac7oy50Sec4ScGiuHCQJxwb8pzqqu/IIOBUPwLY++YQGXYzaRNJv+ymzOfsuyWUXYYqhb7PPoLBa7+4m7RqqaYHLKz4zkP0byq28G8rlK8lM5+QdNKL+6IL8GTvlJrpcdIYrcWmBuTVlufNdARlOujdAsukv0NYS70sdPpUY5+p1cClKKBTlzExTkLWVBtn7DCpJlxIJYoCDtKAm8cU5ZqGgoVH21ckYjXx2MNaR6CJnpe5MbqXbhzFygfZujuCOkI4nLEIy1B8CQHTXkarrmMaq5Imu6nSSJ1Tib43L8uiWW9i3Yiw1ekEmSv4xJ2oetQibXdXDD5AyHxKSjl0wK6IEcMY21OW6lpB0d8U8M0PwdaQ6kNF9X0ryD0/Snf+gw7rP7mhqWEAs4S/avTPZ3Pv+H72dI/Hr3NjVkkX/7yL+63ZoafroHwvD3/eT7QumvjcQv9T1/+yOfT+N7d2/+o5K2nXz/DdXBOrj57pZ2/HL4KVxfGlTRmY0RZlo/upMofNPFG20sBpjhfxzrTs+EYAPfCvgy+cauXaaq74eRriIEeKRHZJFMEOkYdk5nhdVxRoqRRfKDSKsxUkVbGaW6skhmiPQ6RiqWRzp1I40UxCI5hpEYy+QxNspi+EOMBLAJU+s5Y7wtixEAMW6U7WA9H4NbMRQCLPuaWRqrn2LzCG6ljFsNnZQ4Oi5aAxTZUqf9DGyaMfvRcoS2lcm9OfJwF2OqumHMuHCcdeDUyQtSN1HqkSRMSX0qUF+MO4m3xsioF7Z2pV6WSanHyqnHInU/St1cg3oHoG5D6hly6k8j9VS+KRBGd1MoWHTmmqST2qYgk2wDbDQ7+hm32uwhyyLpWCeew5Q2sjT5DkcsVWuNKEc5L/tvoLy8zMHNOCRtzMad1Fg5uiK2zdoAtnOU2P7yFVQOvj8p0YVVf8rqOT9XVhsRVquuR45y28g4infl6OzBSvmaO3J0F3KUc6MbjvohR9ulhibJhaM6lCNDDY7GhhGOZmKdqSvn6INWlKNX4MhVPGfrdH3lZUgwt/gEn/iMhtEv6keQh/zCSX7c28LoiLiCHqgrn7Zmw9IJIegwTGqmfBt4a/u4+odt9Ss2BWx2UTGeioa3aLxIwWo/Y8RxBfkUZ3F+SY0gs8xGAwZAj/eTOrz2fgpZdC2urHFz8lyWFe7AbGsvP608MxGCmy9y6oIbJWKinZc=
*/