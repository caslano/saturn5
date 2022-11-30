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


namespace boost { namespace hana {
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
}} // end namespace boost::hana

#endif // !BOOST_HANA_EXT_STD_VECTOR_HPP

/* vector.hpp
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
*/