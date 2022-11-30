/*!
@file
Defines `boost::hana::replace`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_REPLACE_HPP
#define BOOST_HANA_REPLACE_HPP

#include <boost/hana/fwd/replace.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/replace_if.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename OldVal, typename NewVal>
    constexpr auto replace_t::operator()(Xs&& xs, OldVal&& oldval, NewVal&& newval) const {
        using S = typename hana::tag_of<Xs>::type;
        using Replace = BOOST_HANA_DISPATCH_IF(replace_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::replace(xs, oldval, newval) requires 'xs' to be a Functor");
    #endif

        return Replace::apply(static_cast<Xs&&>(xs),
                              static_cast<OldVal&&>(oldval),
                              static_cast<NewVal&&>(newval));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct replace_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename OldVal, typename NewVal>
        static constexpr decltype(auto)
        apply(Xs&& xs, OldVal&& oldval, NewVal&& newval) {
            return hana::replace_if(
                static_cast<Xs&&>(xs),
                hana::equal.to(static_cast<OldVal&&>(oldval)),
                static_cast<NewVal&&>(newval)
            );
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_REPLACE_HPP

/* replace.hpp
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
*/