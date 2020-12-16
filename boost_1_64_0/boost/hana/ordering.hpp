/*!
@file
Defines `boost::hana::ordering`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ORDERING_HPP
#define BOOST_HANA_ORDERING_HPP

#include <boost/hana/fwd/ordering.hpp>

#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/less.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    namespace detail {
        template <typename F>
        struct less_by {
            F f;

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) const&
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }

            template <typename X, typename Y>
            constexpr decltype(auto) operator()(X&& x, Y&& y) &
            { return hana::less(f(static_cast<X&&>(x)), f(static_cast<Y&&>(y))); }
        };
    }

    //! @cond
    template <typename F>
    constexpr auto ordering_t::operator()(F&& f) const {
        return detail::less_by<typename detail::decay<F>::type>{static_cast<F&&>(f)};
    }
    //! @endcond
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ORDERING_HPP

/* ordering.hpp
xHOV0lAZq+vuPp0mNvG4h0/Hmxcre0+fBllqVSd788lx/aq1YVkX5iSNyb3ZuYA7ZLKu7jPLWyuy1ayd6r8vnQXnUNr9fBq25HOmcb+/TyPNcK/Liceaz3MGyFP5B4Q5tTqsgcAtwhXKW4/8O6yUk/5spfY+cCGv1T2NgYu74fmurRVmGVsbpb8tpPfWx+2n9LdTuv9M1IZ3UDp9f8p7J+Utzpl3hTxsASs8/d1Eg0ndDcTrPRMvIxud7GnvHfPC13Efdcp7X8hrdZnJey1rDDjlvT/Jwxpi4/6BkGd7vzkMfC58kNrCKFkfPhTbs7psJBvbD8d0U2ZtuUL8PjKmh/DsIZfx+2jMvzv6x+SPj4V0Nx+Vz5xoPh7yxveLKf0TIT1IJsTrkyHdb8r5sm0Yr09FXvggvJ+fjnOozVZWWfoPzufST8a5RfP7hyEds5LK/iikuZXDef84pM/P95/w9FEGoLyfhjwSrhi/n011uyxK/3lI930I3/gp14ix8TFGKxoLz1g/uXz+JS7zWNAdHQsAfYUM/TjkH/My9IO39uEef0WkPeSquPt6XzhcfZy9r+sT0g+dTuAxrmzwlfevkaAJeSdGWXyEKmI0d6J0wlciGhHyXFBX/Orb9Lkr4Fzx6TC6Y2lDTDsHaYFe+TQo9APP81wae6ZPc5UdOE9kSn8AS4dXJ7XhVGhDcDCkdm+HdBZnkOrdC3mcz2FIc8GaeB/PhPQQZIfSHxvSfXAP973CneYJPj0JeOcehpAf6nnMPN/79VPbnubpvZu1p7kE+v48nxY9+skAlHg+y+dv+lfetWjKE8bisu5+6fMDFhXQEvn3fZHPczCAwQE/5D3e7d1+HnEcnnGe3+QqSxEnqr37CCFF/F7i+TnLzW0Hw/GgyO9F6Mfr07xHLIVxfiLqOuPHBc14kHtC2UP6JTCeC5huGKcLX+YpKD9+V8wnxwNpL6Y0h0k0pT+R0kc/IeT49FcgvdQ9obbIfCz/MviJ40RiMExoP9KfjfIrUBc5RDCPjpWVeq2tPM1LeZ7pz0W6b+czkU7e2YHPa6g9hFSIJo15L0TeGMbFu+2GD+777O/TuEkf7D/CX6F9vffAd8DuMd2uH7zj06+Dulxb0DWID51p7+XK32i0DbkI7t1LDqoO8+42t0a9Y3p7UZcOFQNVO9F8+2I+D+M6jsc1Q/qJS7p05oQ1ZhPP31zO5W9sbjOe1w15L7iCyzsSB4foxZXGMoeM/oYh7+ZXcXmwxaPMMcZd8Gemen7CymFMJ/spqsfZ16PM6Eu9cWoEhaG8y18beQxvAF0k3uI6Lm8RdwNliP7610WZ4IvtHwdZvWeu5/O4ZzON+fNu6PKgaFx74O7GoxzNDUbd5E2RPscaCDTvHFweuskwscCTxkwsU/4MAwel6HuDz4ovF6umdHE/pLv9OmScG+16l1Jdq+5NLo3Ogs0H7R5zzHZxnkTP2EtjGpCfdrGwQ9kdin/Gy55Qps2boa/F6DS3u09xOiPv1YR30+k67yolHo5HwMhbxLI/4Ni1t7VW2bbuMuGg/SJf8k85dZ6ZfZZpSmMy4OSOjkBhgjllP7bT9QiK/Heygef00jnodUOljBarEs+XZvCx3/ZTY50kOByY0bt10kcotwdnfoJpeoaG+lRBGJcz/9Cig/RXSyFDHb7CR2y5SFIefX/L6Ro9L2SRjhEDlWJ26qyqeqUYH5huBiBzzunu8Gpy8exoHBI+nbBVCy6d/mdxjY9RPNP9xP/8D7M2lSZXme7EwD1SFnltPTiY43Gb5RufL23X0Pe1tKYTzb+K9w+lLhykxqfwyTbprZxfnouishrzRYuN9Z1NJ52s4zXdreKgoyY=
*/