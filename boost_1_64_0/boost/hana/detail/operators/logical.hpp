/*!
@file
Defines logical operators.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP
#define BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/core/tag_of.hpp>
#include <boost/hana/fwd/and.hpp>
#include <boost/hana/fwd/not.hpp>
#include <boost/hana/fwd/or.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN namespace detail {
    template <typename Tag>
    struct logical_operators {
        static constexpr bool value = false;
    };

    namespace operators {
        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator||(X&& x, Y&& y)
        { return hana::or_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename Y, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value ||
            detail::logical_operators<typename hana::tag_of<Y>::type>::value
        >::type>
        constexpr auto operator&&(X&& x, Y&& y)
        { return hana::and_(static_cast<X&&>(x), static_cast<Y&&>(y)); }

        template <typename X, typename = typename std::enable_if<
            detail::logical_operators<typename hana::tag_of<X>::type>::value
        >::type>
        constexpr auto operator!(X&& x)
        { return hana::not_(static_cast<X&&>(x)); }
    } // end namespace operators
} BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DETAIL_OPERATORS_LOGICAL_HPP

/* logical.hpp
SvEnlpzO8MnDvJF9FEyoQU+ZaFCosaIPsfElijeYZjOm3jLhzMincPgWbXKWTSh87BBSmA2T5f0lYWtEG/EcurR2mxOVjWrb+KVMlg5swKPrepDs50YA0d98GwQYR2g4jPJDXHY3vr741W05xQ6mfkk6oE85IC2bCJGZkg//op3X67fIDMEA7enFIhrGaNd/ICN5IpvuEeyycraEjcNHge+uuY4fQR7bm3xByVxkhnXN7yxRoDTeynblhdl1Lg4ZRKVMYTtMXQD96XHTgNy1IuvsEuXYygzYAAWspP8jQRI8IP8zspEK1V2rbxLUq51rB21Lzx6DkUadGuEhQvzV9ugA6f+QdB3kymBJuynz95UEp6lfIK3ZESHyhu7jMcr9NGQVPqT5ru+4fh1jzIMkv6TrMIawEpDQnyQRE9xCsrBfuBgw1nAF2iHxsyn2PT+Wbv02qCIgxG2rZZ4dfO1OHVpEltAx6f88Ge4CM/DXqxmltTp4QNAdMwMsnxlSkfVZlGGqhk21uVAe+mkKEv+YacVhGsOvsW2bmstTajO/qHho+cO5l6c0UMBIpw==
*/