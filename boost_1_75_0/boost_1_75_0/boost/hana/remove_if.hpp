/*!
@file
Defines `boost::hana::remove_if`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REMOVE_IF_HPP
#define BOOST_HANA_REMOVE_IF_HPP

#include <boost/hana/fwd/remove_if.hpp>

#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/filter.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/not.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto remove_if_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using RemoveIf = BOOST_HANA_DISPATCH_IF(remove_if_impl<M>,
            hana::MonadPlus<M>::value
        );

        #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
            static_assert(hana::MonadPlus<M>::value,
            "hana::remove_if(xs, predicate) requires 'xs' to be a MonadPlus");
        #endif

        return RemoveIf::apply(static_cast<Xs&&>(xs),
                               static_cast<Pred&&>(pred));
    }
    //! @endcond

    template <typename M, bool condition>
    struct remove_if_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::filter(static_cast<Xs&&>(xs),
                        hana::compose(hana::not_, static_cast<Pred&&>(pred)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_REMOVE_IF_HPP

/* remove_if.hpp
+d+LBJj+0CVt6Zo1A3/vdBvz83yYsS1d2/aX5wc+2gF8aoRrOzptiDLH9Rqen9+NVLWjc+a5//ShD8S3qAX+Re3oux8XZ9RuwuNpGu3Znh49yW3gn4EYfjk2sT2dm/T3tekaT2yvAkrb056K3J28Qqz/1ydIO9BNnnQ7d7k95l8ZmNyBPvLFu6v4N2y/VgRRHemevzZZuvIz1u+1k8M70mNdWzw+eQ7PP12wsSM98pZ0ka8e9EF1o7fQlX4ZetCqJg/6r/q9j48rffni5tEHt+FyxkPuSpf++E3Vwqt4fG/13eVK/33DdbfNY6xPrGe2K33s+A+OqRrM361+pa50Yuczpx+3wPDb/q6daMMb1aqjbvC9dZWdt7QTXRbmaPuiA+iXyuMbVSc6VFeufCaBeKmq84CUTvSCjV06POB9A/hjBhZ0onv//EMHwxY8v5U+Np3p1E+dVnXp8hSNv+rQIJ/OdHnH6NxVxyHep8obLO9Mzxre4u8kIzeffRM700res/ZPJ0I51XSIsTPdf+OdwpWxYA9UI/xKO9P8HHH36gEYfx3t2oUu77Zv5+MU3N4msX8X2turZTxjD7Dq+tDoLrRyfGxPwWbQf5XT8JQudI+MZQNDlkG8TBU6oqAL3d5ik8fYIXh+L5NQbrTVr0lXlqlAP1TGkZ5utNeQfm/VU7F9dvQPd6PlMTqbrCF4vOaOTnSjH78q/Gl8GciD
*/