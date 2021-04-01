/*!
@file
Defines `boost::hana::sum`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_SUM_HPP
#define BOOST_HANA_SUM_HPP

#include <boost/hana/fwd/sum.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/monoid.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/integral_constant.hpp> // required by fwd decl
#include <boost/hana/plus.hpp>
#include <boost/hana/zero.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename M>
    template <typename Xs>
    constexpr decltype(auto) sum_t<M>::operator()(Xs&& xs) const {
        using S = typename hana::tag_of<Xs>::type;
        using Sum = BOOST_HANA_DISPATCH_IF(sum_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monoid<M>::value,
        "hana::sum<M> requires 'M' to be a Monoid");

        static_assert(hana::Foldable<S>::value,
        "hana::sum<M>(xs) requires 'xs' to be Foldable");
    #endif

        return Sum::template apply<M>(static_cast<Xs&&>(xs));
    }
    //! @endcond

    template <typename T, bool condition>
    struct sum_impl<T, when<condition>> : default_ {
        template <typename M, typename Xs>
        static constexpr decltype(auto) apply(Xs&& xs) {
            return hana::fold_left(static_cast<Xs&&>(xs), hana::zero<M>(), hana::plus);
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_SUM_HPP

/* sum.hpp
57ILWc3jOvBFiVjawxFt7KSza7svSQP5ZDMlU656pBud8kqZUC6mWnuUY1uc6meLmFD+ZdSJPny9ni3pCCOFxksvt9ZZjR7V6y9BdGFxbzaweMKtYPYaX6uCnnIwSu8aqiWr1FjdDCs+yiQcihA2k9igcVAlA8TpNzg18bVpC9XO7AmID/IBHbisYvRUKsdYxuZ1Qff4PW4m2FqtqVWVV0QuW9prKU0oz8XcfY2IlavMYLfdTvTVhGGh6l1ybk33oSKEAqvfkqkmTKsxClqsQKMvi+ydHLaYFMlQ6n6fb8hJfm0qD8GpgzbfFNfjWzd5/sT/zwmA6Fp4vAj3G6SlFoIFqkCJywpTNYDv0rdqGDs+oWPvarRXCKsyaKy6dsEyuhgAJbEEerbYf2rcMLN6zfRfd/pPfwWU++4jD9TAt/KnF0Okj1wOYoJ0f8Eo9Ifb64k/m6+TtgtNAm11I56OAyceIU7rmQEhWN/OGs2WawFceT0f7i8gepMotwHE5All45zIvdeVC67TbOyF6YdPzO2yhtspu9LP4wJiTOaURVpVAALyj4WL4gR+wQ==
*/