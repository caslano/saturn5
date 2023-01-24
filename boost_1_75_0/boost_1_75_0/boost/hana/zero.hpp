/*!
@file
Defines `boost::hana::zero`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ZERO_HPP
#define BOOST_HANA_ZERO_HPP

#include <boost/hana/fwd/zero.hpp>

#include <boost/hana/concept/constant.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/canonical_constant.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    constexpr decltype(auto) zero_t<M>::operator()() const {
    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::zero<M>() requires 'M' to be a Monoid");
    #endif

        using Zero = BOOST_HANA_DISPATCH_IF(zero_impl<M>,
            hana::Monoid<M>::value
        );

        return Zero::apply();
    }
    //! @endcond

    template <typename M, bool condition>
    struct zero_impl<M, when<condition>> : default_ {
        template <typename ...Args>
        static constexpr auto apply(Args&& ...) = delete;
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for non-boolean arithmetic data types
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct zero_impl<T, when<
        std::is_arithmetic<T>::value &&
        !std::is_same<T, bool>::value
    >> {
        static constexpr T apply()
        { return static_cast<T>(0); }
    };

    //////////////////////////////////////////////////////////////////////////
    // Model for Constants over a Monoid
    //////////////////////////////////////////////////////////////////////////
    namespace detail {
        template <typename C>
        struct constant_from_zero {
            static constexpr auto value = hana::zero<typename C::value_type>();
            using hana_tag = detail::CanonicalConstant<typename C::value_type>;
        };
    }

    template <typename C>
    struct zero_impl<C, when<
        hana::Constant<C>::value &&
        Monoid<typename C::value_type>::value
    >> {
        static constexpr decltype(auto) apply()
        { return hana::to<C>(detail::constant_from_zero<C>{}); }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_ZERO_HPP

/* zero.hpp
exReeBj0KG8pW9KHnqL4lhNctECdxKa/7Szk+c4t6gYsyjWExlS/h+pJHMnzOJTEfjyWlOxoqx8To60+nqS1et5eWl2hMY5rIzQqXixEb6CH9HfENX6Ou/1pmAXt8l+pUPQUWkfkhDWp3ymRaRTZPmfnKpWt0oDFaExOduQKjAmmMT5fvJPlAtRivm8nfAQ3MDWqBb1rFDy40ID+CWpBt/1d9uZsbbYloRkEZc+xK9B4yl7tpe07i0Hchaff8acrXTC3gqY0qSrL4EvxhHhShX9MRv2ggt9bPYYM+nYHPK9azV0bYz1BVAeoDCEXnRDyhhnSFtr7JkkhlzM4kRzroDKsPMzXFm21fZsvQMcQIEjWayJnFuiyI+ge0sS9TUKzvsPbBH02Qaxt+ohCb09Wx5arBdbyzOsXDvqS0HuxIARa0jfqAQTNbpuFe2MHUAJ5cQAPLPDTVhQniSBx/YhOEZFGs9+s0c9P+fBW0BUKofJ4oE5ipmRdL6LZ/AG+oG/vC87BE5GAHHuW8gXzsDSM3UTZg1ZIvmE0W4FPkxHYQwjMBIBXg/L6K2C2gC57IAcE9frNV5ttjfVVeKUjSYa4S7KP8ITAdeZwBgsqWEwKcFeT3BIu5Ym1lPzEoJ2ITAuklluFQvbOIKUv/S6oP45A/eg/Qr15CNRfxEClo6ES6WgoTO5k2WGUZc49N8rJlof5fs1zv6gxX0Ac/CQq
*/