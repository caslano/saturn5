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


BOOST_HANA_NAMESPACE_BEGIN
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
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_DROP_WHILE_HPP

/* drop_while.hpp
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
*/