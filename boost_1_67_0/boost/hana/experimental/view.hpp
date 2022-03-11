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

BOOST_HANA_NAMESPACE_BEGIN

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
    constexpr make_joined_view_t joined{};

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

BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXPERIMENTAL_VIEW_HPP

/* view.hpp
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
*/