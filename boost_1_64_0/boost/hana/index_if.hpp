/*!
@file
Defines `boost::hana::index_if`.

@copyright Louis Dionne 2013-2017
@copyright Jason Rice 2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_INDEX_IF_HPP
#define BOOST_HANA_INDEX_IF_HPP

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/detail/index_if.hpp>
#include <boost/hana/fwd/at.hpp>
#include <boost/hana/fwd/basic_tuple.hpp>
#include <boost/hana/fwd/index_if.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/optional.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto index_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using S = typename hana::tag_of<Xs>::type;
        using IndexIf = BOOST_HANA_DISPATCH_IF(index_if_impl<S>,
            hana::Iterable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<S>::value,
        "hana::index_if(xs, pred) requires 'xs' to be a Iterable");
    #endif

        return IndexIf::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <std::size_t i, std::size_t N, bool Done>
        struct iterate_while;

        template <std::size_t i, std::size_t N>
        struct iterate_while<i, N, false> {
            template <typename Xs, typename Pred>
            using f = typename iterate_while<i + 1, N,
                static_cast<bool>(detail::decay<decltype(
                    std::declval<Pred>()(
                      hana::at(std::declval<Xs>(), hana::size_c<i>)))>::type::value)
            >::template f<Xs, Pred>;
        };

        template <std::size_t N>
        struct iterate_while<N, N, false> {
            template <typename Xs, typename Pred>
            using f = hana::optional<>;
        };

        template <std::size_t i, std::size_t N>
        struct iterate_while<i, N, true> {
            template <typename Xs, typename Pred>
            using f = hana::optional<hana::size_t<i - 1>>;
        };
    }

    template <typename Tag>
    struct index_if_impl<Tag, when<Foldable<Tag>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs const& xs, Pred const&)
            -> typename detail::iterate_while<0,
                decltype(hana::length(xs))::value, false>
                    ::template f<Xs, Pred>
        { return {}; }
    };

    template <typename It>
    struct index_if_impl<It, when<!Foldable<It>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs const&, Pred const&)
            -> typename detail::iterate_while<0,
                static_cast<std::size_t>(-1), false>
                    ::template f<Xs, Pred>
        { return {}; }
    };

    // basic_tuple is implemented here to solve circular dependency issues.
    template <>
    struct index_if_impl<basic_tuple_tag> {
        template <typename ...Xs, typename Pred>
        static constexpr auto apply(basic_tuple<Xs...> const&, Pred const&)
            -> typename detail::index_if<Pred, Xs...>::type
        { return {}; }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_INDEX_IF_HPP

/* index_if.hpp
nEvfhG1vQR3b9t3U7j7jMGgMZsRU29bUsSB9xVhkGKvpCY/pV/7ksD4qf0b506O2MezxoHZGRvVT2XWMKjfXPvNvt00bspU3rv45fR+ybYsuj0fos31c+9P1M3PU/BuT06wOKcfYpdCtzpgyw0zbvirvmHp6jFerNuVJT6Hd9n7t3tKfCW3fNjezjNuWLZ5kNT4fvnu5Svd11ixVNJLW7pxChJOsv8p8vlo9zJL6GvPIzBOtObJO6S89TLBC+pMcS8QYZYmUJ1tbNDPMPNvk1iuPfqZZI9rr/brT1gjdjLNMaoO20MoYq2RcLT/tDDPHyavMq5h9xmN6mWDoaeplpCDk/VrrL/7vbopDzDO56fOuTuXRxSgLZMSU5+/Go2I4/u+OiAtkn9MWZsm43pwxwAr5N2hP/N8hFufJ6NIWYn5nsMtvO51q895nlzQyztuXOt9pGhPXyHm6vEwzv+qzQzHnGca53/7iKAvkdCuXXvprfI4mblL1TGPH1s7fguPxMik3ahunGWOD3GcZP5bif5MuhnqsZXL8jXlMnCb12caeZlqzrXdxmbzn2EaB31s4zbjHG0SeayxYIaNX3+hmjE2yn2cbW35PtFdcJPv5xp0xNpns9F7zCxwfU9ohDjPPFtl95t/nPY3iNGvkvVAfco2FmObSd4RuUh9tH/GkuHJL7zOLS4SOG8PbySf2MM4a6Vd5zhybFJxwnmGCFXIfY24YYY30x1rDjLFEn9+a7s+3Xk56zCIZj5eHYb/jPCJusPCwkPfMtffpPtu5rTF+Xcj7ivpMWqp6/BbTSbHd8TAqLrFqW6bf0qu6rfd7L3LuFFvF03c0d+Jkgc/ebiffjT6vEYepOhryesnn6X4Ldy4eR9TxHXVK63uDum5vzRNjhpQ0baWPI3f3HjbzHm+x+WzfjbnY+DDBBll3sCYYYpHwHdVJF7NsEkmXhylWybtEHeT4O9pRcZ2MO1lLDNAX//fJxXQx987mxu90xsRp1snP0GfGWSbjLq4ZDDJH+l21gXTvi0cY8nie0N3sSzsjLJOeaV96GKfLsX4k21j6jddZjxe/bB0N+H4aI7YvkHlf82X+6sThEt+dKHZe8HiKNQrupy9MscGR+6uTKVJyHLMMskreA/SXRdIe6Ligj9iiz9RY8DjzQdaX76s0iiMskpGr3BSfddq+rS0nPO8nfKnt9DFNyoOVyRAr5D/EmmOOjDzjyAjr5F1m3Px2z+as7y95PMkG2ZebP7+h3SpOsUHOQ/WJUdbJyhfnfPYnjrLOwMN9jnlYWoF1RLfHs6Q+zBgwwjqZD1cvQ8ySVqBd9LFI9hX68ATfXRGnCD/Cc4aYZYPMR2ojk6yQdcRxyyhr5D7K3DJL6pXuDxhmleyj9mWMbaIRabcynuLgSd+xEDeo07+CQuMX5/yzKGYWqYdxNjlSLI0p1iiIWlvMkVZi3TPIKrml5plpUsq0iT4mWCO3XJuZZZ2sCnnoY5Ztco4ZS/qYotX5flXMq7Qv06RUGV8Gr4+fC+xLKMW+FPiNw2ZxWBwSw/2+qxCPfps4dGv9sv7LxfBt9Kva90xu7vscHg+zft55Ndfn885hkcuVc8uQdeEzK+eV0TcibYGRX6jOb5hnx//eS0z1O44Rxvw+3yLpb3HZsb3Ptmk2yPyZ6yT9zLBJjt/vPUkfs4TWbuFcYB7yfR/B4zy/J3eKzIeoh0FmiOVpAykU0O93MqdZ8zjdb3Y12neAUfsusOhxqt8KC/vduTzaGWaRkHNshFYi8vQzR6rfgCunlwlOK7ef1me4TunjljFat33V8/Ruxwn9dBmvUea/4jsxfh+uhwlWyVj3HcNhY8y6POn6WU6MVL8=
*/