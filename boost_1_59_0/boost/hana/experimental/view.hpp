/*
@file
Defines experimental views.

@copyright Louis Dionne 2013-2017
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXPERIMENTAL_VIEW_HPP
#define BOOST_HANA_EXPERIMENTAL_VIEW_HPP

#include <boost/hana/and.hpp>
#include <boost/hana/at.hpp>
#include <boost/hana/bool.hpp>
#include <boost/hana/detail/decay.hpp>
#include <boost/hana/fold_left.hpp>
#include <boost/hana/functional/compose.hpp>
#include <boost/hana/functional/on.hpp>
#include <boost/hana/fwd/ap.hpp>
#include <boost/hana/fwd/concat.hpp>
#include <boost/hana/fwd/drop_front.hpp>
#include <boost/hana/fwd/empty.hpp>
#include <boost/hana/fwd/equal.hpp>
#include <boost/hana/fwd/flatten.hpp>
#include <boost/hana/fwd/is_empty.hpp>
#include <boost/hana/fwd/less.hpp>
#include <boost/hana/fwd/lift.hpp>
#include <boost/hana/fwd/transform.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/length.hpp>
#include <boost/hana/lexicographical_compare.hpp>
#include <boost/hana/range.hpp>
#include <boost/hana/tuple.hpp>
#include <boost/hana/unpack.hpp>

#include <cstddef>
#include <type_traits>
#include <utility>


// Pros of views
//     - No temporary container created between algorithms
//     - Lazy, so only the minimum is required
//
// Cons of views
//     - Reference semantics mean possibility for dangling references
//     - Lose the ability to move from temporary containers
//     - When fetching the members of a view multiple times, no caching is done.
//       So for example, `t = transform(xs, f); at_c<0>(t); at_c<0>(t)` will
//       compute `f(at_c<0>(xs))` twice.
//     - push_back creates a joint_view and a single_view. The single_view holds
//       the value as a member. When doing multiple push_backs, we end up with a
//         joint_view<xxx, joint_view<single_view<T>, joint_view<single_view<T>, ....>>>
//       which contains a reference to `xxx` and all the `T`s by value. Such a
//       "view" is not cheap to copy, which is inconsistent with the usual
//       expectations about views.

namespace boost { namespace hana {

namespace experimental {
    struct view_tag;

    namespace detail {
        template <typename Sequence>
        struct is_view {
            static constexpr bool value = false;
        };

        template <typename Sequence>
        using view_storage = typename std::conditional<
            detail::is_view<Sequence>::value, Sequence, Sequence&
        >::type;
    }

    //////////////////////////////////////////////////////////////////////////
    // sliced_view
    //////////////////////////////////////////////////////////////////////////
    template <typename Sequence, std::size_t ...indices>
    struct sliced_view_t {
        detail::view_storage<Sequence> sequence_;
        using hana_tag = view_tag;
    };

    template <typename Sequence, typename Indices>
    constexpr auto sliced(Sequence& sequence, Indices const& indices) {
        return hana::unpack(indices, [&](auto ...i) {
            return sliced_view_t<Sequence, decltype(i)::value...>{sequence};
        });
    }

    namespace detail {
        template <typename Sequence, std::size_t ...i>
        struct is_view<sliced_view_t<Sequence, i...>> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // transformed_view
    //////////////////////////////////////////////////////////////////////////
    template <typename Sequence, typename F>
    struct transformed_view_t {
        detail::view_storage<Sequence> sequence_;
        F f_;
        using hana_tag = view_tag;
    };

    template <typename Sequence, typename F>
    constexpr transformed_view_t<Sequence, typename hana::detail::decay<F>::type>
    transformed(Sequence& sequence, F&& f) {
        return {sequence, static_cast<F&&>(f)};
    }

    namespace detail {
        template <typename Sequence, typename F>
        struct is_view<transformed_view_t<Sequence, F>> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // filtered_view
    //////////////////////////////////////////////////////////////////////////
#if 0
    template <typename Sequence, typename Pred>
    using filtered_view_t = sliced_view_t<Sequence, detail::filtered_indices<...>>;

    template <typename Sequence, typename Pred>
    constexpr filtered_view_t<Sequence, Pred> filtered(Sequence& sequence, Pred&& pred) {
        return {sequence};
    }
#endif

    //////////////////////////////////////////////////////////////////////////
    // joined_view
    //////////////////////////////////////////////////////////////////////////
    template <typename Sequence1, typename Sequence2>
    struct joined_view_t {
        detail::view_storage<Sequence1> sequence1_;
        detail::view_storage<Sequence2> sequence2_;
        using hana_tag = view_tag;
    };

    struct make_joined_view_t {
        template <typename Sequence1, typename Sequence2>
        constexpr joined_view_t<Sequence1, Sequence2> operator()(Sequence1& s1, Sequence2& s2) const {
            return {s1, s2};
        }
    };
    BOOST_HANA_INLINE_VARIABLE constexpr make_joined_view_t joined{};

    namespace detail {
        template <typename Sequence1, typename Sequence2>
        struct is_view<joined_view_t<Sequence1, Sequence2>> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // single_view
    //////////////////////////////////////////////////////////////////////////
    template <typename T>
    struct single_view_t {
        T value_;
        using hana_tag = view_tag;
    };

    template <typename T>
    constexpr single_view_t<typename hana::detail::decay<T>::type> single_view(T&& t) {
        return {static_cast<T&&>(t)};
    }

    namespace detail {
        template <typename T>
        struct is_view<single_view_t<T>> {
            static constexpr bool value = true;
        };
    }

    //////////////////////////////////////////////////////////////////////////
    // empty_view
    //////////////////////////////////////////////////////////////////////////
    struct empty_view_t {
        using hana_tag = view_tag;
    };

    constexpr empty_view_t empty_view() {
        return {};
    }

    namespace detail {
        template <>
        struct is_view<empty_view_t> {
            static constexpr bool value = true;
        };
    }
} // end namespace experimental

//////////////////////////////////////////////////////////////////////////
// Foldable
//////////////////////////////////////////////////////////////////////////
template <>
struct unpack_impl<experimental::view_tag> {
    // sliced_view
    template <typename Sequence, std::size_t ...i, typename F>
    static constexpr decltype(auto)
    apply(experimental::sliced_view_t<Sequence, i...> view, F&& f) {
        (void)view; // Remove spurious unused variable warning with GCC
        return static_cast<F&&>(f)(hana::at_c<i>(view.sequence_)...);
    }

    // transformed_view
    template <typename Sequence, typename F, typename G>
    static constexpr decltype(auto)
    apply(experimental::transformed_view_t<Sequence, F> view, G&& g) {
        return hana::unpack(view.sequence_, hana::on(static_cast<G&&>(g), view.f_));
    }

    // joined_view
    template <typename View, typename F, std::size_t ...i1, std::size_t ...i2>
    static constexpr decltype(auto)
    unpack_joined(View view, F&& f, std::index_sequence<i1...>,
                                    std::index_sequence<i2...>)
    {
        (void)view; // Remove spurious unused variable warning with GCC
        return static_cast<F&&>(f)(hana::at_c<i1>(view.sequence1_)...,
                                   hana::at_c<i2>(view.sequence2_)...);
    }

    template <typename S1, typename S2, typename F>
    static constexpr decltype(auto)
    apply(experimental::joined_view_t<S1, S2> view, F&& f) {
        constexpr auto N1 = decltype(hana::length(view.sequence1_))::value;
        constexpr auto N2 = decltype(hana::length(view.sequence2_))::value;
        return unpack_joined(view, static_cast<F&&>(f),
                             std::make_index_sequence<N1>{},
                             std::make_index_sequence<N2>{});
    }

    // single_view
    template <typename T, typename F>
    static constexpr decltype(auto) apply(experimental::single_view_t<T> view, F&& f) {
        return static_cast<F&&>(f)(view.value_);
    }

    // empty_view
    template <typename F>
    static constexpr decltype(auto) apply(experimental::empty_view_t, F&& f) {
        return static_cast<F&&>(f)();
    }
};

//////////////////////////////////////////////////////////////////////////
// Iterable
//////////////////////////////////////////////////////////////////////////
template <>
struct at_impl<experimental::view_tag> {
    // sliced_view
    template <typename Sequence, std::size_t ...i, typename N>
    static constexpr decltype(auto)
    apply(experimental::sliced_view_t<Sequence, i...> view, N const&) {
        constexpr std::size_t indices[] = {i...};
        constexpr std::size_t n = indices[N::value];
        return hana::at_c<n>(view.sequence_);
    }

    // transformed_view
    template <typename Sequence, typename F, typename N>
    static constexpr decltype(auto)
    apply(experimental::transformed_view_t<Sequence, F> view, N const& n) {
        return view.f_(hana::at(view.sequence_, n));
    }

    // joined_view
    template <std::size_t Left, typename View, typename N>
    static constexpr decltype(auto) at_joined_view(View view, N const&, hana::true_) {
        return hana::at_c<N::value>(view.sequence1_);
    }

    template <std::size_t Left, typename View, typename N>
    static constexpr decltype(auto) at_joined_view(View view, N const&, hana::false_) {
        return hana::at_c<N::value - Left>(view.sequence2_);
    }

    template <typename S1, typename S2, typename N>
    static constexpr decltype(auto)
    apply(experimental::joined_view_t<S1, S2> view, N const& n) {
        constexpr auto Left = decltype(hana::length(view.sequence1_))::value;
        return at_joined_view<Left>(view, n, hana::bool_c<(N::value < Left)>);
    }

    // single_view
    template <typename T, typename N>
    static constexpr decltype(auto) apply(experimental::single_view_t<T> view, N const&) {
        static_assert(N::value == 0,
        "trying to fetch an out-of-bounds element in a hana::single_view");
        return view.value_;
    }

    // empty_view
    template <typename N>
    static constexpr decltype(auto) apply(experimental::empty_view_t, N const&) = delete;
};

template <>
struct length_impl<experimental::view_tag> {
    // sliced_view
    template <typename Sequence, std::size_t ...i>
    static constexpr auto
    apply(experimental::sliced_view_t<Sequence, i...>) {
        return hana::size_c<sizeof...(i)>;
    }

    // transformed_view
    template <typename Sequence, typename F>
    static constexpr auto apply(experimental::transformed_view_t<Sequence, F> view) {
        return hana::length(view.sequence_);
    }

    // joined_view
    template <typename S1, typename S2>
    static constexpr auto apply(experimental::joined_view_t<S1, S2> view) {
        return hana::size_c<
            decltype(hana::length(view.sequence1_))::value +
            decltype(hana::length(view.sequence2_))::value
        >;
    }

    // single_view
    template <typename T>
    static constexpr auto apply(experimental::single_view_t<T>) {
        return hana::size_c<1>;
    }

    // empty_view
    static constexpr auto apply(experimental::empty_view_t) {
        return hana::size_c<0>;
    }
};

template <>
struct is_empty_impl<experimental::view_tag> {
    // sliced_view
    template <typename Sequence, std::size_t ...i>
    static constexpr auto
    apply(experimental::sliced_view_t<Sequence, i...>) {
        return hana::bool_c<sizeof...(i) == 0>;
    }

    // transformed_view
    template <typename Sequence, typename F>
    static constexpr auto apply(experimental::transformed_view_t<Sequence, F> view) {
        return hana::is_empty(view.sequence_);
    }

    // joined_view
    template <typename S1, typename S2>
    static constexpr auto apply(experimental::joined_view_t<S1, S2> view) {
        return hana::and_(hana::is_empty(view.sequence1_),
                          hana::is_empty(view.sequence2_));
    }

    // single_view
    template <typename T>
    static constexpr auto apply(experimental::single_view_t<T>) {
        return hana::false_c;
    }

    // empty_view
    static constexpr auto apply(experimental::empty_view_t) {
        return hana::true_c;
    }
};

template <>
struct drop_front_impl<experimental::view_tag> {
    template <typename View, typename N>
    static constexpr auto apply(View view, N const&) {
        constexpr auto n = N::value;
        constexpr auto Length = decltype(hana::length(view))::value;
        return experimental::sliced(view, hana::range_c<std::size_t, n, Length>);
    }
};

//////////////////////////////////////////////////////////////////////////
// Functor
//////////////////////////////////////////////////////////////////////////
template <>
struct transform_impl<experimental::view_tag> {
    template <typename Sequence, typename F, typename G>
    static constexpr auto
    apply(experimental::transformed_view_t<Sequence, F> view, G&& g) {
        return experimental::transformed(view.sequence_,
                                         hana::compose(static_cast<G&&>(g), view.f_));
    }

    template <typename View, typename F>
    static constexpr auto apply(View view, F&& f) {
        return experimental::transformed(view, static_cast<F&&>(f));
    }
};

//////////////////////////////////////////////////////////////////////////
// Applicative
//////////////////////////////////////////////////////////////////////////
template <>
struct lift_impl<experimental::view_tag> {
    template <typename T>
    static constexpr auto apply(T&& t) {
        return experimental::single_view(static_cast<T&&>(t));
    }
};

template <>
struct ap_impl<experimental::view_tag> {
    template <typename F, typename X>
    static constexpr auto apply(F&& f, X&& x) {
        // TODO: Implement cleverly; we most likely need a cartesian_product
        //       view or something like that.
        return hana::ap(hana::to_tuple(f), hana::to_tuple(x));
    }
};

//////////////////////////////////////////////////////////////////////////
// Monad
//////////////////////////////////////////////////////////////////////////
template <>
struct flatten_impl<experimental::view_tag> {
    template <typename View>
    static constexpr auto apply(View view) {
        // TODO: Implement a flattened_view instead
        return hana::fold_left(view, experimental::empty_view(),
                                     experimental::joined);
    }
};

//////////////////////////////////////////////////////////////////////////
// MonadPlus
//////////////////////////////////////////////////////////////////////////
template <>
struct concat_impl<experimental::view_tag> {
    template <typename View1, typename View2>
    static constexpr auto apply(View1 view1, View2 view2) {
        return experimental::joined(view1, view2);
    }
};

template <>
struct empty_impl<experimental::view_tag> {
    static constexpr auto apply() {
        return experimental::empty_view();
    }
};

//////////////////////////////////////////////////////////////////////////
// Comparable
//////////////////////////////////////////////////////////////////////////
template <>
struct equal_impl<experimental::view_tag, experimental::view_tag> {
    template <typename View1, typename View2>
    static constexpr auto apply(View1 v1, View2 v2) {
        // TODO: Use a lexicographical comparison algorithm.
        return hana::equal(hana::to_tuple(v1), hana::to_tuple(v2));
    }
};

template <typename S>
struct equal_impl<experimental::view_tag, S, hana::when<hana::Sequence<S>::value>> {
    template <typename View1, typename Seq>
    static constexpr auto apply(View1 v1, Seq const& s) {
        // TODO: Use a lexicographical comparison algorithm.
        return hana::equal(hana::to_tuple(v1), hana::to_tuple(s));
    }
};

template <typename S>
struct equal_impl<S, experimental::view_tag, hana::when<hana::Sequence<S>::value>> {
    template <typename Seq, typename View2>
    static constexpr auto apply(Seq const& s, View2 v2) {
        // TODO: Use a lexicographical comparison algorithm.
        return hana::equal(hana::to_tuple(s), hana::to_tuple(v2));
    }
};

//////////////////////////////////////////////////////////////////////////
// Orderable
//////////////////////////////////////////////////////////////////////////
template <>
struct less_impl<experimental::view_tag, experimental::view_tag> {
    template <typename View1, typename View2>
    static constexpr auto apply(View1 v1, View2 v2) {
        return hana::lexicographical_compare(v1, v2);
    }
};

template <typename S>
struct less_impl<experimental::view_tag, S, hana::when<hana::Sequence<S>::value>> {
    template <typename View1, typename Seq>
    static constexpr auto apply(View1 v1, Seq const& s) {
        return hana::lexicographical_compare(v1, s);
    }
};

template <typename S>
struct less_impl<S, experimental::view_tag, hana::when<hana::Sequence<S>::value>> {
    template <typename Seq, typename View2>
    static constexpr auto apply(Seq const& s, View2 v2) {
        return hana::lexicographical_compare(s, v2);
    }
};

}} // end namespace boost::hana

#endif // !BOOST_HANA_EXPERIMENTAL_VIEW_HPP

/* view.hpp
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
*/