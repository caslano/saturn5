/*!
@file
Defines `boost::hana::extend`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXTEND_HPP
#define BOOST_HANA_EXTEND_HPP

#include <boost/hana/fwd/extend.hpp>

#include <boost/hana/concept/comonad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/duplicate.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename W_, typename F>
    constexpr decltype(auto) extend_t::operator()(W_&& w, F&& f) const {
        using W = typename hana::tag_of<W_>::type;
        using Extend = BOOST_HANA_DISPATCH_IF(extend_impl<W>,
            hana::Comonad<W>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Comonad<W>::value,
        "hana::extend(w, f) requires 'w' to be a Comonad");
    #endif

        return Extend::apply(static_cast<W_&&>(w), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename W, bool condition>
    struct extend_impl<W, when<condition>> : default_ {
        template <typename X, typename F>
        static constexpr decltype(auto) apply(X&& x, F&& f) {
            return hana::transform(hana::duplicate(static_cast<X&&>(x)),
                                   static_cast<F&&>(f));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXTEND_HPP

/* extend.hpp
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
*/