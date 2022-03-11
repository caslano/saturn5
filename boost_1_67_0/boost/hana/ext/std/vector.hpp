/*!
@file
Adapts `std::vector` for use with Hana.

@copyright Louis Dionne 2013-2017
@copyright Gonzalo Brito Gadeschi 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_EXT_STD_VECTOR_HPP
#define BOOST_HANA_EXT_STD_VECTOR_HPP

#include <boost/hana/config.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/fwd/core/tag_of.hpp>
#include <boost/hana/less.hpp>

#include <algorithm>
#include <iterator>
#include <memory>
#include <type_traits>
#include <utility>
#include <vector>


BOOST_HANA_NAMESPACE_BEGIN
    namespace ext { namespace std { struct vector_tag; }}

    template <typename T, typename Allocator>
    struct tag_of<std::vector<T, Allocator>> {
        using type = ext::std::vector_tag;
    };

    //////////////////////////////////////////////////////////////////////////
    // Comparable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct equal_impl<ext::std::vector_tag, ext::std::vector_tag> {
        template <typename T1, typename A1, typename T2, typename A2>
        static bool apply(std::vector<T1, A1> const& v1,
                          std::vector<T2, A2> const& v2)
        {
            return std::equal(begin(v1), end(v1),
                              begin(v2), end(v2),
                              hana::equal);
        }
    };

    //////////////////////////////////////////////////////////////////////////
    // Orderable
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct less_impl<ext::std::vector_tag, ext::std::vector_tag> {
        template <typename T1, typename A1, typename T2, typename A2>
        static bool apply(std::vector<T1, A1> const& v1,
                          std::vector<T2, A2> const& v2)
        {
            return std::lexicographical_compare(begin(v1), end(v1),
                                                begin(v2), end(v2),
                                                hana::less);
        }
    };

#if 0
    //////////////////////////////////////////////////////////////////////////
    // Functor
    //////////////////////////////////////////////////////////////////////////
    template <>
    struct transform_impl<ext::std::vector_tag> {
        template <typename V, typename F>
        static auto apply(V&& v, F&& f) {
            using U = std::remove_cv_t<std::remove_reference_t<
                decltype(f(*v.begin()))
            >>;
            using Alloc = typename std::remove_reference_t<V>::allocator_type;
            using NewAlloc = typename std::allocator_traits<Alloc>::
                             template rebind_alloc<U>;
            std::vector<U, NewAlloc> result; result.reserve(v.size());

            std::transform(begin(v), end(v),
                           std::back_inserter(result), std::forward<F>(f));
            return result;
        }

        template <typename T, typename Alloc, typename F>
        static auto apply(std::vector<T, Alloc>&& v, F&& f)
            -> std::enable_if_t<
                std::is_same<
                    T,
                    std::remove_cv_t<std::remove_reference_t<
                        decltype(f(*v.begin()))
                    >>
                >{}
                , std::vector<T, Alloc>
            >
        {
            // If we receive a rvalue and the function returns elements of
            // the same type, we modify the vector in-place instead of
            // returning a new one.
            std::transform(std::make_move_iterator(begin(v)),
                           std::make_move_iterator(end(v)),
                           begin(v), std::forward<F>(f));
            return std::move(v);
        }
    };
#endif
BOOST_HANA_NAMESPACE_END

#endif // !BOOST_HANA_EXT_STD_VECTOR_HPP

/* vector.hpp
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
*/