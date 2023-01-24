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
yLyQyZo/gZMYdPEU/x15E6Th9wJ4s9jqtc4lGHUSRbly2bCvL6XEZ6XO/AwGTvxnoZibuDqABYGVaFg+0f+Ya7c1P8gQuvmiJNmGWzNZv8iyPTYvcHsVncJYqWVcTzYueOEygEYFrxO1mnmeFcQUrfIlDYFBGdGvC1Iy8h0e1sZW0F8M559P/JViyT17dgMnwXvIaOkVWs+GnTQ5I2r2sOAMzmkCpr8Qy6MJHcQFRcP4wnzhq2N6VCVSQO8O8WeAO6wxV2nBYvnX7bwxZn+Qv3Ffdr8b78bzV5XzEWgJukjjR1SP1Yc5eKtw+5TxWDFHrdRuqsiAO32Ty1zYu5EMVHasGuaFEoQE1Ehn8h8Zqzf0jq3WrT7hOq0JX0XpLE/yhx3eSNEdD4K3EMa71hrD/FQ3/6x7iyyDbAWwfr3xzb3Xj38aiPj+OPHhPrmQe46kizy4DeOpGmZk5iUoPnimGmnRVQoA030WZzp2i36aV8dj2qoYh5R5jvPp4sHaa7Rk1b0t8F2i6pOKvroTmXIXxLlOvGQdWBI4Ue49yb6zAI0GZfnS8gNiqIIYIkF2JcEWNXch0VfXlb8Q0cDcYO+HxArSwofz6m+U6Y7BIg9R9NxLAr5RJw7alpJmrUekhfTM4nVgqjnt1oM4QATUMPj1mmPvySSVCOLRselpWK5aY7fkRsh3qlWd1qUEJA05gil8lDZ6HSl+R+XOTVLv
*/