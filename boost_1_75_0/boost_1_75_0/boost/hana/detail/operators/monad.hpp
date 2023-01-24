/*!
@file
Defines operators for Monads.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP
#define BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/chain.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct monad_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename Xs, typename F, typename = typename std::enable_if<
            detail::monad_operators<typename hana::tag_of<Xs>::type>::value
        >::type>
        constexpr auto operator|(Xs&& xs, F&& f)
        { return hana::chain(static_cast<Xs&&>(xs), static_cast<F&&>(f)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_MONAD_HPP

/* monad.hpp
ilrVmPkQS4g+xvnw4CDWT49VBtWkqJOsMAlnEzYbPQmr/e5IYXEBLmV79C5N9m4Lacdrzu+pmb6poyZx61+jpzoSuKfweLPftMDWxD1FubtZtHf7Ojajn42GJQm99aZcvExNLUfbu/OWQqit8fG/0asZ0Dd6bOe5rXgeMPywVHm7jGpNiw7POoSvgw6S+zptlmnoJBGaeSxrFuiE86ApHAzKf0UGw9l+Z6SguLiY0majgjykSAGc+QT/Jjk8Ukq/nYoNln1tTRe6q3EeU1feW2J34E6N096BoxadUS2hGyx93huA3jfA01CfWMj2HAyikbTk1mRUg3aTgXbEnqjKlH69gu6vrIbYHdLPVqgL9seW0+2VB2V+EmiK6cXS2Av00iuOjZi7Edf3H4ToRBe25wHgJltL1bVCTYbsnQBBtmj1aOmOFepmzZMst0keF2lZTS/SNS8BnqFvCmJB7Y49dreh21gZdKcpI7awC2KLXvYjkRI0RZzmmbNmcblo8W809H9IBtEaEF0Y8C8qEc4lVxv9i7LR02izYTFMFBJsbkvFSfw3kd4bLBfN0ovLVVw/WkZxzUTfDYnClwboTtzukcq7yEF72gYrvrAGQIeMW50thhnAaGntcpV821kmC9lC4GdUaSwX9XgNwtZenSzNpcWFjxHo545BITqtuhFqXLyqAOs6ntY1XV34LhBq0lP4FFzdb7YP6B83wX+8
*/