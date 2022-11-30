/*!
@file
Defines `boost::hana::drop_while`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_DROP_WHILE_HPP
#define BOOST_HANA_DROP_WHILE_HPP

#include <boost/hana/fwd/drop_while.hpp>

#include <boost/hana/concept/foldable.hpp>
#include <boost/hana/concept/iterable.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/detail/first_unsatisfied_index.hpp>
#include <boost/hana/drop_front.hpp>
#include <boost/hana/eval_if.hpp>
#include <boost/hana/front.hpp>
#include <boost/hana/is_empty.hpp>
#include <boost/hana/lazy.hpp>


namespace boost { namespace hana {
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto drop_while_t::operator()(Xs&& xs, Pred&& pred) const {
        using It = typename hana::tag_of<Xs>::type;
        using DropWhile = BOOST_HANA_DISPATCH_IF(drop_while_impl<It>,
            hana::Iterable<It>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::Iterable<It>::value,
        "hana::drop_while(xs, pred) requires 'xs' to be an Iterable");
    #endif

        return DropWhile::apply(static_cast<Xs&&>(xs), static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace iterable_detail {
        struct drop_while_helper {
            struct next {
                template <typename Xs, typename Pred>
                constexpr decltype(auto) operator()(Xs&& xs, Pred&& pred) const {
                    return hana::drop_while(
                        hana::drop_front(static_cast<Xs&&>(xs)),
                        static_cast<Pred&&>(pred)
                    );
                }
            };

            template <typename Xs, typename Pred>
            constexpr decltype(auto) operator()(Xs&& xs, Pred&& pred) const {
                return hana::eval_if(pred(hana::front(xs)),
                    hana::make_lazy(next{})(xs, pred),
                    hana::make_lazy(xs)
                );
            }
        };
    }

    template <typename It, bool condition>
    struct drop_while_impl<It, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&& pred) {
            return hana::eval_if(hana::is_empty(xs),
                hana::make_lazy(xs),
                hana::make_lazy(iterable_detail::drop_while_helper{})(
                                            xs, static_cast<Pred&&>(pred))
            );
        }
    };

    template <typename S>
    struct drop_while_impl<S, when<hana::Foldable<S>::value>> {
        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred&&) {
            using FirstUnsatisfied = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::first_unsatisfied_index<Pred&&>{})
            );
            return hana::drop_front(static_cast<Xs&&>(xs),
                                    FirstUnsatisfied{});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_DROP_WHILE_HPP

/* drop_while.hpp
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
*/