//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP
#define BOOST_BEAST_DETAIL_IS_INVOCABLE_HPP

#include <type_traits>
#include <utility>

namespace boost {
namespace beast {
namespace detail {

template<class R, class C, class ...A>
auto
is_invocable_test(C&& c, int, A&& ...a)
    -> decltype(std::is_convertible<
        decltype(c(std::forward<A>(a)...)), R>::value ||
            std::is_same<R, void>::value,
                std::true_type());

template<class R, class C, class ...A>
std::false_type
is_invocable_test(C&& c, long, A&& ...a);

/** Metafunction returns `true` if F callable as R(A...)

    Example:

    @code
    is_invocable<T, void(std::string)>::value
    @endcode
*/
/** @{ */
template<class C, class F>
struct is_invocable : std::false_type
{
};

template<class C, class R, class ...A>
struct is_invocable<C, R(A...)>
    : decltype(is_invocable_test<R>(
        std::declval<C>(), 1, std::declval<A>()...))
{
};
/** @} */

} // detail
} // beast
} // boost

#endif

/* is_invocable.hpp
4jYdCa8/6iS/Fu1nx8E2Bdhd+nD6IMe6CiHC4DBXPIdeRyKWo+S1cQQmDthz88GDbSZWETQmEjf4dydV1Jec6m0KOCu+NmRPHH78veCG1E9nlOpD/Nq8wR+GYFCnfD0l6gQBxr6NPnD3tGaB1oxZHPMRlYSZGGWoCAfagE2rJWRsFVfDD61JGXxTwTaqGmYF9PhJiXuo7E6u06h0RUUxlWQjyZSQybQ6AgAUO78OmH8soW63u0Yl/djY1veEOSMJZaZ8KRsd4Or8APFfbFpVk9NEiUXP6ty3fuDLLsI1Kje/IND0oT9gAZsPycpmlv41fL2+UsdNnDR/h9GRbCb3nXkiKaxON4lnolVTod0E42OEbCNKcV5Gsa7Ei9Ffx+taYc+06AEUOhQNqH9cEASgJtyv/K1t8WXSyTDYtyLTWGITtJyWoJFTzZljFsO3fYXV5r0suAH2Ohv/5eGfq8NgxeP5PbtnbO3Fg0h+exhDt0NLs0KRP5ASwVEN3a1AipPQV1AimrzI6FHhz9+78XVBAUvQDJRiDNtBdzeJIqx3uHy1Al7/RIfxuQJoLA==
*/