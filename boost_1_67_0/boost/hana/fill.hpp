/*!
@file
Defines `boost::hana::fill`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <boost/hana/fwd/fill.hpp>

#include <boost/hana/concept/functor.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename hana::tag_of<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            hana::Functor<S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Functor<S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<Sequence<S>::value>> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILL_HPP

/* fill.hpp
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
*/