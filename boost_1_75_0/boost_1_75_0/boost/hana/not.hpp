/*!
@file
Defines `boost::hana::not_`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_NOT_HPP
#define BOOST_HANA_NOT_HPP

#include <boost/hana/fwd/not.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/logical.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X>
    constexpr decltype(auto) not_t::operator()(X&& x) const {
        using Bool = typename hana::tag_of<X>::type;
        using Not = BOOST_HANA_DISPATCH_IF(hana::not_impl<Bool>,
            hana::Logical<Bool>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Logical<Bool>::value,
        "hana::not_(cond) requires 'cond' to be a Logical");
    #endif

        return Not::apply(static_cast<X&&>(x));
    }
    //! @endcond

    template <typename L, bool condition>
    struct not_impl<L, when<condition>> : hana::default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    template <typename L>
    struct not_impl<L, hana::when<std::is_arithmetic<L>::value>> {
        template <typename Cond>
        static constexpr Cond apply(Cond const& cond)
        { return static_cast<Cond>(cond ? false : true); }
    };

    namespace detail {
        template <typename C, typename X>
        struct constant_from_not {
            static constexpr auto value = hana::not_(hana::value<X>());
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct not_impl<C, hana::when<
        hana::Constant<C>::value &&
        hana::Logical<typename C::value_type>::value
    >> {
        template <typename Cond>
        static constexpr auto apply(Cond const&)
        { return hana::to<C>(detail::constant_from_not<C, Cond>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_NOT_HPP

/* not.hpp
yS6uj99qFAV7YT7oqHrMiREWNs1FCZf5oWwp0stNXzKPvLBG+lh+Tits+KEfvFXwU6HnnSoAmdX2Embrmirr1l6fg7IkFFu8Hd5us91UbtFoQQeGpIq0IN8i2F7YxlspX5tCRzqmb1DLzCJT1R3nuR/StSlDbJPrvM+VYnuF23SFlONCJ5d6eoKydcGFS89pis+6rMZ2D8gowKDXChzbSV9O/zzyS7mLiNd1ellhi8BOwRW1I4oCTYgcvq1jh6kOibzhc7yxk0GSMRIcHxKz/xq84ha4Sx40o0HaMMCsCcHDzEw2bzsoYffI40OJLhDOLNNLlWLYtVfaYz+wxhcmpvNMxAY9bc4udjqYNhuGz7/9bVxJLndTJVP38+r3bitbCYJDSOAco+Gz7CdkhQOB29h6A6enH8oSZlMHFNCnPrdVGej73st9c8NVWeJBLsSsJJI7xuvhPtE2sT88xW+q5fj2MXFSKx9lCZBNquCx9TsxgiqkrxBsOYNOac/r3DcezJn9M2f0tl/TTReszMooanR3hBk9TSto1lsYtLq/gt1QJAn4FukS/grhvO2u+rpWJuJ35Rvz2nMzGTI0M7MobvIWVPnjFQmUyfI1K0KbfP1YnRXZ/Zis8fY47wHhVdnsVz3yIMk1+FdnB4lNCVWJou57JgmwRCPjpPiRRF39BBcC4M4ZBbbief+3xMf44K/OfQT2mhn5U3udMKd1
*/