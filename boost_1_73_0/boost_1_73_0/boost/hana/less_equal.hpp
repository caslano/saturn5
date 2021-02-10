/*!
@file
Defines `boost::hana::less_equal`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_LESS_EQUAL_HPP
#define BOOST_HANA_LESS_EQUAL_HPP

#include <boost/hana/fwd/less_equal.hpp>

#include <boost/hana/concept/orderable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/common.hpp>
#include <boost/hana/core/to.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/has_common_embedding.hpp>
#include <boost/hana/detail/nested_than.hpp> // required by fwd decl
#include <boost/hana/less.hpp>
#include <boost/hana/not.hpp>

#include <type_traits>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename X, typename Y>
    constexpr auto less_equal_t::operator()(X&& x, Y&& y) const {
        using T = typename hana::tag_of<X>::type;
        using U = typename hana::tag_of<Y>::type;
        using LessEqual = BOOST_HANA_DISPATCH_IF(
            decltype(less_equal_impl<T, U>{}),
            hana::Orderable<T>::value &&
            hana::Orderable<U>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Orderable<T>::value,
        "hana::less_equal(x, y) requires 'x' to be Orderable");

        static_assert(hana::Orderable<U>::value,
        "hana::less_equal(x, y) requires 'y' to be Orderable");
    #endif

        return LessEqual::apply(static_cast<X&&>(x), static_cast<Y&&>(y));
    }
    //! @endcond

    template <typename T, typename U, bool condition>
    struct less_equal_impl<T, U, when<condition>> : default_ {
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::not_(hana::less(static_cast<Y&&>(y),
                                         static_cast<X&&>(x)));
        }
    };

    // Cross-type overload
    template <typename T, typename U>
    struct less_equal_impl<T, U, when<
        detail::has_nontrivial_common_embedding<Orderable, T, U>::value
    >> {
        using C = typename hana::common<T, U>::type;
        template <typename X, typename Y>
        static constexpr decltype(auto) apply(X&& x, Y&& y) {
            return hana::less_equal(hana::to<C>(static_cast<X&&>(x)),
                                    hana::to<C>(static_cast<Y&&>(y)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_LESS_EQUAL_HPP

/* less_equal.hpp
KY3RMsdHsriD5CPOuiMeelmULwN9amTbH75EFvL5R38WTlU1VnyAvwtTEt/6q5KoMNm6BdaQcJU6IvAe9i6yAg3Nihw66Z0dWtlvDygTgD/qXLbPelejVYcRFhtUol6Jjji550HKsdMx6TJCj5lSeqaaJF9dk0COEMlNHSh58zPo8iOGWl5OsriG28RSKiP0elUZIb7VcJRSykQJDkqFs6rYhmEysxZt822z07VNzIUzg+OK4bUr78BZ7xJAaYd/axqr8js8sucnKunVI3twsItqrwpdAc3MQlcV1Z5X+N+Uh8BVwC0btFlNPveKBdK/ykZt9rLWNi1vJCnLovwoM6tyaXC0r6gFJJgHpRSldhNF4inMssT+hTpl4s688FQX7NRUQPbC4i8KbeuGgPxojAwaopa9qFVDlyf60sRpyTQzgKy+mrBs65tjkXzSGHwpcVux2rva7RA3Lq7s969O/fdtUINdPEe2a+IfaSEnD3Vdr2LzPfob7cByHxwn83kS/5HMHBvuxBvBIq/YHbw9+OMbt5FGzvD4rtHVxGvDWFyRD15t6qKc2WuvwrRt2rO0EzyPZ4d7U1bklQVfVI/FjaDQuX9YsvmXncHXXLWazCmFjLhIDz8vsCiXsdWwDlvuo7w/GSRcUxvOrCNl
*/