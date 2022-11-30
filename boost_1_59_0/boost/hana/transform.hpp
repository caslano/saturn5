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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_TRANSFORM_HPP

/* transform.hpp
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
*/