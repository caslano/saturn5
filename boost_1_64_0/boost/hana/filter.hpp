/*!
@file
Defines `boost::hana::filter`.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILTER_HPP
#define BOOST_HANA_FILTER_HPP

#include <boost/hana/fwd/filter.hpp>

#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/chain.hpp>
#include <boost/hana/concept/monad_plus.hpp>
#include <boost/hana/concept/sequence.hpp>
#include <boost/hana/config.hpp>
#include <boost/hana/core/dispatch.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/detail/algorithm.hpp>
#include <boost/hana/detail/array.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/empty.hpp>
#include <boost/hana/lift.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <utility>


BOOST_HANA_NAMESPACE_BEGIN
    //! @cond
    template <typename Xs, typename Pred>
    constexpr auto filter_t::operator()(Xs&& xs, Pred&& pred) const {
        using M = typename hana::tag_of<Xs>::type;
        using Filter = BOOST_HANA_DISPATCH_IF(filter_impl<M>,
            hana::MonadPlus<M>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(hana::MonadPlus<M>::value,
        "hana::filter(xs, pred) requires 'xs' to be a MonadPlus");
    #endif

        return Filter::apply(static_cast<Xs&&>(xs),
                             static_cast<Pred&&>(pred));
    }
    //! @endcond

    namespace detail {
        template <typename Pred, typename M>
        struct lift_or_empty {
            template <typename X>
            static constexpr auto helper(X&& x, hana::true_)
            { return hana::lift<M>(static_cast<X&&>(x)); }

            template <typename X>
            static constexpr auto helper(X&&, hana::false_)
            { return hana::empty<M>(); }

            template <typename X>
            constexpr auto operator()(X&& x) const {
                constexpr bool cond = decltype(std::declval<Pred>()(x))::value;
                return helper(static_cast<X&&>(x), hana::bool_c<cond>);
            }
        };
    }

    template <typename M, bool condition>
    struct filter_impl<M, when<condition>> : default_ {
        template <typename Xs, typename Pred>
        static constexpr decltype(auto) apply(Xs&& xs, Pred const&) {
            return hana::chain(static_cast<Xs&&>(xs),
                detail::lift_or_empty<Pred, M>{}
            );
        }
    };

    namespace detail {
        template <bool ...b>
        struct filter_indices {
            static constexpr auto compute_indices() {
                constexpr bool bs[] = {b..., false}; // avoid empty array
                constexpr std::size_t N = detail::count(bs, bs + sizeof(bs), true);
                detail::array<std::size_t, N> indices{};
                std::size_t* keep = &indices[0];
                for (std::size_t i = 0; i < sizeof...(b); ++i)
                    if (bs[i])
                        *keep++ = i;
                return indices;
            }

            static constexpr auto cached_indices = compute_indices();
        };

        template <typename Pred>
        struct make_filter_indices {
            Pred const& pred;
            template <typename ...X>
            auto operator()(X&& ...x) const -> filter_indices<
                static_cast<bool>(detail::decay<
                    decltype(pred(static_cast<X&&>(x)))
                >::type::value)...
            > { return {}; }
        };
    }

    template <typename S>
    struct filter_impl<S, when<Sequence<S>::value>> {
        template <typename Indices, typename Xs, std::size_t ...i>
        static constexpr auto filter_helper(Xs&& xs, std::index_sequence<i...>) {
            return hana::make<S>(
                hana::at_c<Indices::cached_indices[i]>(static_cast<Xs&&>(xs))...
            );
        }

        template <typename Xs, typename Pred>
        static constexpr auto apply(Xs&& xs, Pred const& pred) {
            using Indices = decltype(
                hana::unpack(static_cast<Xs&&>(xs),
                             detail::make_filter_indices<Pred>{pred})
            );

            return filter_impl::filter_helper<Indices>(
                static_cast<Xs&&>(xs),
                std::make_index_sequence<Indices::cached_indices.size()>{}
            );
        }
    };
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_FILTER_HPP

/* filter.hpp
OF5/aB7dfxedu9C+oEp5PDQBP+sfiGPJs57DvOc8ZT9QFT9xtD5WJ+PYR888pn9Jb2+/1f2L3G+TfEmka3vxH+vk23R9qysS+Td+9nF4aH6nHEmf/8W3/6g/9gk9cri6GSVP6Mf2B9RXN3x5Md0k//Lo6Br4XmIearf5+1vzPg++jeV/L6WLHhS3JjgvLrF0PLXVuMbLrxvpP/W5rBO9OdD67Rx6/He6JyU4pv0Nrw+B4/PUDTzLmITHj+YPNuo3z6XLxTuWBdfxRP2v6qsjvhwH14fzJ+8k8o/i/y++JJ2ev4fO+He4zoW3P5EXF4mzfQ/L6acZpdZZlqpH55WE+uFQ/IFfu9kPszKCD4bT/xPNx2X039twP4svG4vnt/Dt6qd2puvaX9BvKbyabRztwv1m9Ae9WzpIHLZ6/ucdJ8P3GfRBF58fBYdeoSNu5q9fp4uT8MBEuL4e/96mD+Y6GUPxcw/6jH+o7gpfzseLj/Iz6fi0p/z6lb8voJfwZWq9/WHfi5N5XvYiHVHlc8fq38G96H/hSh84Mp4PP9q+GH3SJH5q9p6I8evjvhCh//mz/8IJeFSrD7Y9x3pPAd/9fiT43CXWEerEq0RfqJ3xnwNvwv0Zw/TdMuxfSPC6PCl034Jj1Sufnd6Znz+Dz3vcsUZcOvL1fOvcmL4Ff9h+G335gnpqQafX02FjrD8c4++W1l/XwFPr4rPhXlt533i79eCnPK/1q8Lm+BMv5F9GVz8o/5LpsyfE1XHL+/DC8+RYn2ywv6Fgn/7JSNd5Cd7J/wL4mHkLfj4LH51Dt8T0h11naoTOKjM+ei57JF9mHvMPgtfyb8tw+QZfU6fAo/58FBzNOlu+0/PZqyPir78LR4uup+eOCN4vTPf+DeL8pjrDr2V8V3Y3emKQvnV3vD/Ub/46ZjyMX5Pg1ttwezLdusM6NN+evEe8jqMvx8q3Mv2KE/i2M/W/r0+0fuI5uuCNQn/fpA5el++lfHW5urSel7LIvLxHB2ep9970s7xPfYsuF/+VL7pfquNtdBmdWtZLn0k9F8O3LTH9yhf4lwPiZNxTqjzHxfplx+JT41tl/bNuBdy3TroSPtUXyftZ+tcD9JvmiIv6qZufaD+n+d2vrunh9gPpMr6mbKH62YU/psKf2jDf8LDPLaRLpr3teJk64K+rXhA365EVdEXeEH76Oz70BPmbjScL4Yq6Xv6Q+q10fT5gFb826zV5exVce8y43sV3P/vt1Rr85vnqJvBZM/R57rAPnw7IoF+28N/Fb+sz3QjPnNfT/E67Irhu6pX03X/1vdeJ/1z14/MV8jK5O37ST8w9VJ58RRfthUv3NAuOP5i/4fBlCr2SZb3Lc09pZ/7wftH6CN4Sx6H8ax/P0ZxOGGD9brH73YXfDtInMc6eK/gFz52k/lOmwFk8VfQ9/o6I9xj9io3q/XD5d4E+wljrlh/rpw5LtK5Hv9rX2iVORy0VtwHm52d1Mdo63R7jamZfTzXc+9Y84vfsy/H1Bv2JVV6fp27kUexcOo8vbuwkX9XL7A/1t842H8eLh/0CLT1PKp1U9jo/chzfdoY+58PwqIJPKTTv91rHegN+yPucKL230HWeV0+v0FGefzrea3sL/b8A/6biy0HWhVqbr1r+cxo9+xSc2+d+/NUc60p5X9Ib/eisFD60A3zq7flm8lMH4Yd55vcTuv1PuLkZD4pXPt9YO5Pe7IvHw98s/859jufb4V+XO+T9F4l4OBGf8gf03UK8WHqw5/qF7h3kOr+L/xD9vsPw2E3qyXz0fMo+eXk3/VfrbD30vfLg1S/yoE7/boi+zTrxFOfsq/FnFlysw+u16j0Rj7XiK9vzhVs=
*/