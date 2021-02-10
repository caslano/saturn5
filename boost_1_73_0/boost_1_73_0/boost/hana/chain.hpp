/*!
@file
Defines `boost::hana::chain`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_CHAIN_HPP
#define BOOST_HANA_CHAIN_HPP

#include <boost/hana/fwd/chain.hpp>

#include <boost/hana/concept/monad.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/flatten.hpp>
#include <boost/hana/transform.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename F>
    constexpr decltype(auto) chain_t::operator()(Xs&& xs, F&& f) const {
        using M = typename hana::tag_of<Xs>::type;
        using Chain = BOOST_HANA_DISPATCH_IF(chain_impl<M>,
            hana::Monad<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Monad<M>::value,
        "hana::chain(xs, f) requires 'xs' to be a Monad");
    #endif

        return Chain::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    template <typename M, bool condition>
    struct chain_impl<M, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr auto apply(Xs&& xs, F&& f) {
            return hana::flatten(hana::transform(static_cast<Xs&&>(xs),
                                                 static_cast<F&&>(f)));
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_CHAIN_HPP

/* chain.hpp
FpzwixAojIJ+tYhq5JgWaqDztGKkmsSH4UVvJM7RTfrnvZPh5USPvuQ+vUoU4mDpyVbN41br6yIy3c7wmHshqXIppfQbU4yZoA9sLRM5V3KJYhPB9ooViDZI8v/rTKGmD0OjwIER+V0kL9ZIwjlP0bfdyoWCl36nWQZ7WsLIEvdmTY6votynT8t8ozUZuhntyqKQfHckC+sYIuOY2lF/EvL0SBwdH+JBT8zFOzYOiLMxjJez7x8YTzZF+Zz54cW4RJGGGLvFSg1bCgsrDQ1tHwPdow1KR86z+plMgqDAw8Q2U2BGX+hJOZ+W047ppVH7UYjvVBN3M4g5kIIVhEfsiQu2FkE/Gg2GDz6MqRIp28g0CLAOLKY55HMtxsfVJnTaORv3jrUCw15UHLIUIZdY0d6dlT/faPVWB69ZwTown3PpIhCMyxk5hIz4UGTy0HcJWL78RwsAAnS+xCaAxHsJJQAgoURAy/cxORtlgMw0pdf9yTQHeTJOm5SXv6rRZhTxZ5h97tO7EUVtPwwjdouHFFUn/I479PrEa9ujFzpiL/R+RHEuM7wNAIhql2moerCv8A5XW4fETlM+jzC7bkqhGzxRQ/qM0k9csW1lQATJgg6Y0ekwW915pg71Ijs3mjh5jkwNX2894G3bv7Xv
*/