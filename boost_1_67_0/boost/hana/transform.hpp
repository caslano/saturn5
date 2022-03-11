/*!
@file
Defines `boost::hana::transform`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_TRANSFORM_HPP
#define BOOST_HANA_TRANSFORM_HPP

#include <boost/hana/fwd/transform.hpp>

#include <boost/hana/bool.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/fwd/adjust_if.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr auto transform_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Transform = BOOST_HANA_DISPATCH_IF(transform_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::transform(xs, f) requires 'xs' to be a Functor");
    #endif

        return Transform::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct transform_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::adjust_if(static_cast<Xs&&>(xs),
                                   hana::always(hana::true_c),
                                   static_cast<F&&>(f));
        }
    };

    template <typename S>
    struct transform_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename F>
        struct transformer {
            F f;
            template <typename ...Xs>
            constexpr auto operator()(Xs&& ...xs) const {
                return hana::make<S>((*f)(static_cast<Xs&&>(xs))...);
            }
        };
        //! @endcond

        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            // We use a pointer to workaround a Clang 3.5 ICE
            return hana::unpack(static_cast<Xs&&>(xs),
                                transformer<decltype(&f)>{&f});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_TRANSFORM_HPP

/* transform.hpp
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
*/