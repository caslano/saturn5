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
g6fWQwqxa59zq2a9OUgcXxvrNGATp2x/S3PJbSIpt5lBrdBvGerCjfHnxv68WlCLw2cf65Tx6n+j45HGJC8ZnCNWEboVwGtX8luNO7u2+opoNuKiqmyaqFZT5D0GqWOeeKZHXO7uQcgJciIw1+Hu6rv7/VE3i1ygR1rXg9TQX/oXfDjoc3RC+4icww+G0ifFQ81KS2a/Ugpek6Wa82sN8kpZ9R116I4IPCdvs24BciLfTgfys4CK2traeHYuZoI/jVN9QNS6C3tJN+25Kdp9ME2cWAIq15W6VCUvs+4lyW99j9RjRYLe7uXQXGrh3wNSqpLG5djtS7jx1m+LvzZ9iM4xLne/J1enG6zEqJfEC/LSLcmk3skzqiihBtrC+k6KTvHYD3S5Hww6XOaHWysL4Gy3bfRdjj8nKqKfNMZedm4+e+lSBneaWmAEr3V1mu4Zp/6lLrCpMUUY/Xq8OLPiuUcxsdhsEna883kLCnvXEwaDAzYlj2X0voTfVw0cz5EtYsvgOdT4Rb6E24/2UIR8dyc+xJe9WQac9xefj+J6P9XWXD24QOL5fhxVaSEPdI3iueOnjrSTcsckRVoDhcekaQIHUorUdcuu24evr/ShKEcbyXKvbTz4MqUPQnmkQL2ZF+vdX22Oil3JEwnhTqyBKdwhiXa8bk3G5nrJphsdn5bzN5xM4Jvd1hInGB4yNR3Ph72bZsvay0daCOs5
*/