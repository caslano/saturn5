/*!
@file
Defines `boost::hana::for_each`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FOR_EACH_HPP
#define BOOST_HANA_FOR_EACH_HPP

#include <boost/hana/fwd/for_each.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/unpack.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename F>
    constexpr void for_each_t::operator()(Xs&& xs, F&& f) const {
        using S = typename hana::tag_of<Xs>::type;
        using ForEach = BOOST_HANA_DISPATCH_IF(for_each_impl<S>,
            hana::Foldable<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Foldable<S>::value,
        "hana::for_each(xs, f) requires 'xs' to be Foldable");
    #endif

        return ForEach::apply(static_cast<Xs&&>(xs), static_cast<F&&>(f));
    }
    //! @endcond

    namespace detail {
        template <typename F>
        struct on_each {
            F f;
            template <typename ...Xs>
            constexpr void operator()(Xs&& ...xs) const {
                using Swallow = int[];
                (void)Swallow{0, ((void)(*f)(static_cast<Xs&&>(xs)), 0)...};
            }
        };
    }

    template <typename T, bool condition>
    struct for_each_impl<T, when<condition>> : default_ {
        template <typename Xs, typename F>
        static constexpr void apply(Xs&& xs, F&& f) {
            // We use a pointer instead of a reference to avoid a Clang ICE.
            hana::unpack(static_cast<Xs&&>(xs),
                         detail::on_each<decltype(&f)>{&f});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_FOR_EACH_HPP

/* for_each.hpp
+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
*/