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
t+U9887qSEnUNp6uONRTw+cTBrKMxQDNuIiaOpZ5WZzZkPkNbhvpMBVOtshtaQGolTaBZoHSKk+OUEgPBbBdLgD3naMNUpllO2CzT1zjSZY72Ha5N2/BGG2RN8OxWdwPGwZPv3o/j9Rupv99M+BOxsMl6GAJDt3EklVXvenpwUo82Ob9YXU9o5Ldl6t2NsqurwX/tBKiLpewAxaDzhrg4RPHCq7kppbuaRYIhFenVnOqerfcIX3afdk3i4J1b4FxI8YJ7onYUgXT9NHL6iHs399yCVdiqKuebEvHRmbT+fKq68tkKMZJM7UozmT+uxJefTXtn62c9fXHjjYWdTgmVGh8xE/ol8WqNsohy8LlTjyV9kONL3ZfO1VO2duzTgdrcEJXCEPZJ7rkSrbmT7v0mJK21snFhUM5IyLB5ND5zKB+K3iCf9yZ0EmU6iKzStG/xOBfl/LzHQ7UeWLIzTIaQ09zcDgZ+ki++bix6J6aYmK4NGm+JTSV1oCD+Xp4y6id9s8V7LlxQanbk1m3yY4Xnw2LqtsNSeGZxfTU1L4a0QQxzaqczcdBCwWlFw==
*/