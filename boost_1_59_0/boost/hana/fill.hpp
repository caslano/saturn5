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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_FILL_HPP

/* fill.hpp
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
*/