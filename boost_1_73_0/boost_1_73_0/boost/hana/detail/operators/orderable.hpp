/*!
@file
Defines operators for Orderables.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP
#define BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/greater.hpp>
#include <boost/hana/fwd/greater_equal.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/less_equal.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct orderable_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<(X&& x, Y&& y)
        { return hana::less(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>(X&& x, Y&& y)
        { return hana::greater(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator<=(X&& x, Y&& y)
        { return hana::less_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::orderable_operators<typename hana::tag_of<X>::type>::value ||
            detail::orderable_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator>=(X&& x, Y&& y)
        { return hana::greater_equal(static_cast<X&&>(x), static_cast<Y&&>(y)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_ORDERABLE_HPP

/* orderable.hpp
7I1waPOmWCJxGwaR47FDS9cR5zwqJJHWwvcE8qoBiJeyMMbzJzyR6KrJyzqy1VFekT+eMrIvh++Ho49DfONowcTaVo1OTwdoDouxim+nkLyEgpaarz4mO6VpEPx7U7u8/EChZG4V38Saq5/1020rpkymH9eiCjZp0jcGQnn9RQhrk34X2pdD9hU0xXg0mvxVeOuzfhfiubJgl4L+KsT1WR+OeKOs/SULaJy9vJDvR4a/OnQBC39FDu+eHr68q7lqWFELja7jZqcmG1+7K0ewPHeEedV2zbmnWlXVXHtRd0ypIlSNC6RDW3MbVYlD6uMJCbUmh8Fww3tw1eu7oqRIDtY9opXIlPoe5RAqmdtGMOKGbVOyt3qQwpPbaINrXwLL3l6ad1FfaotP/hdQSwMECgAAAAgALWdKUu2pC3eMXAAAWboBACAACQBjdXJsLW1hc3Rlci9saWIvdnRscy9zZWN0cmFuc3AuY1VUBQABtkgkYO19e3fbNvLo//kUjPc0lVzZsew8nSa9iiwnvnVsX8tpt9vu0aElyuaaIrUkFce7m+9+5wGAAAm+5LS793dX240lEhgAg8FgZjCYebz59T4PnE2n9jOh/0/gA3+pxlkc/c2bpvbSk8m/HP4f1PoN/tY18tjJqvxr0nXq
*/