/*!
@file
Defines `boost::hana::adjust`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_ADJUST_HPP
#define BOOST_HANA_ADJUST_HPP

#include <boost/hana/fwd/adjust.hpp>

#include <boost/hana/adjust_if.hpp>
#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Value, typename F>
    constexpr auto adjust_t::operator()(Xs&& xs, Value&& value, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using Adjust = BOOST_HANA_DISPATCH_IF(adjust_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::adjust(xs, value, f) requires 'xs' to be a Functor");
    #endif

        return Adjust::apply(static_cast<Xs&&>(xs),
                             static_cast<Value&&>(value),
                             static_cast<F&&>(f));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct adjust_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value, typename F>
        static constexpr auto apply(Xs&& xs, Value&& value, F&& f) {
            return hana::adjust_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<Value&&>(value)),
                static_cast<F&&>(f)
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_ADJUST_HPP

/* adjust.hpp
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
*/