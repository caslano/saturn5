/*!
@file
Forward declares `boost::hana::or_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_OR_HPP
#define BOOST_HANA_FWD_OR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/when.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! Return whether any of the arguments is true-valued.
    //! @ingroup group-Logical
    //!
    //! `or_` can be called with one argument or more. When called with
    //! two arguments, `or_` uses tag-dispatching to find the right
    //! implementation. Otherwise,
    //! @code
    //!     or_(x) == x
    //!     or_(x, y, ...z) == or_(or_(x, y), z...)
    //! @endcode
    //!
    //!
    //! Example
    //! -------
    //! @include example/or.cpp
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto or_ = [](auto&& x, auto&& ...y) -> decltype(auto) {
        return tag-dispatched;
    };
#else
    template <typename L, typename = void>
    struct or_impl : or_impl<L, when<true>> { };

    struct or_t {
        template <typename X, typename Y>
        constexpr decltype(auto) operator()(X&& x, Y&& y) const;

        template <typename X, typename ...Y>
        constexpr decltype(auto) operator()(X&& x, Y&& ...y) const;
    };

    constexpr or_t or_{};
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FWD_OR_HPP

/* or.hpp
vq9MDxQZyjaWF5hFnnzSVFXJPBq4QMZPV/ErY/Ed+uK09eHzNX060Se4EHNaT1TMUtWtOm3KCgSJY15iXEEf2WcLFpOzTcpg69XJYWv0zCJRIFPn7lvwO5AM2T2x7NgP4Cc6vtcgDSaDLEEX3otEmplpO62WNFptrG4eBgUY/6FzbGkRGlp8on80ynr/Odar56JsOyp090uqQrloD8JEIddH2umCeaH9tmCuYSEbbIfxMoWmzEhXJH72kqpnY6jKllR5PBvnjwmdkxx0VzSmJDHC8WDlB5mx4pBIwPVn2BNE5iPUce6DL6y5sHZs4BQ1b6oCte99PLaq1lMupAkblk5wPK1+niNsAbHewpQgcIz4TDpLhVPAiOUNCL9zpTkh2tlqQjRKwu3Qmtr+fCt/5UHmW7seM8FzdTqwB+n5pG711fMm4seNRVvbhZDX9nHRN+VcpwspHQ1tr+01rcFMJP794vrE91Ut4rf/OvG9X4v0k1uk75oYH/2JM/k4p6jWDR6r7K1RAJyxN0I6z4v2hkwSH2xs1w3NJ765iaj+2GZzpp5WbVxoS9KpBxmIvUDwuhqppZ8cyGDn2eW/UHrpRXpKIIMsN1/foTzJyrUbJyU5idUfXK9GAzsZRMOFJKYge5yNEMHSRDWSjeySm8BIfJ90PocFvFrmMh6w7pCEzHxUztuLqM4+0UvO9A+DbcyP+PZGgCLDp9i0tg2rJ2yVVHGyZNIG0mQ9H+ZIdETToAmTMV+BDUScItvQ3AfvQAx6Mrt3G+ZOO7Jyary7TPNnRxUXE6l+wvl6W+4X5vx+OrRSH1mMqXzPHvEjysQuUbTGJla/btBq3knc1IBTw5FDcpnytgeV/3LqOl7kcwemKqzfbtj/H+Yk6E8UzisGp97FEEGkQ5xuy1VsCPsUKb4CzsB3XBnxPIO0yRqfWCdVFydUFyskmihdjRb5RekvZLgd4SkVfG0RYHUNn8O8TQn7y4TfrDH8Qw9RItaW8P2vv41f7/bSfkppeJ3s2eVnNzNG9DY8uVgIPrQCBND3iXtWcLGsJEbhDQ6BTPrhI/j1il+tM2QUhiFtHbIxPjU6OLBpAVL4xEvXE7ErIwzkbDq9CylfMlPeRykv5JR/vDmuv3oQNLhPWnU2fsVj6BvUYftBIuqCULWr0qW9bQJ5kIAciZR+MErKOjU2nS79oWHb+TV0Vah8+lZohaL5erUU1h0Wni0vKAvPFr94Rb0A/HYT/P0E/lHSbCV/XSydzvTdARsovZWQ9ba0jaED5/J+EoK/B0B2mUAeICBT5Rp5updUUxhGF2OUYy5G0i/NpA9T0nOQlLZD5HYHvvaacfdQ3IkW5XuT0b7vTX7M9+bMeN+bU+N9b9Kl7w2K+M4s4m4q4kVi5JTAd4GBYs/tsm3FooLR4+TqplpU+kco/fVyN4dXfGdqgT207ioNq1bN09gMUCzueFStTffQeppJfk1JLgBDYnpGw1/BdQpQhnacmeo3VM07ZSdu+rXU9U8lnuWO3ld7VTUjsFAlWy+TEWTxyQ0sZR+HgU5ctJoNfvfimfYHy2mgy5jfn8ZyuKTzvew/5yPvT0qDI36xT5dHAMO72qc6PtS77yEdaVoG9PMMbnACkbS7JF4DD0j0X2HwyeZbVR846znFJxna8Hg+MfOeZuQdQDYNNQPTrSRk4IsRSMJDhqiFZJSOaiLvfimc94m+K3hJ4TPWf+zk5kX3rvwQOrG+JW2Wm5eRsEoL0d+Hl3KR0pRtrsLNccAkeDfFT10U5w3Zrjg2/fnueCLBn48KLeHzo2XJJVzy6iX0d6AqOfjTCFaEx7GzEJd8Epf8+UI1vuXT0Me9KmBjQeQXd95tRFY=
*/