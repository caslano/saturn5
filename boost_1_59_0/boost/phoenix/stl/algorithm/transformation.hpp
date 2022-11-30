// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
// Copyright 2005 Dan Marsden.
// Copyright 2015 John Fletcher.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler

#ifndef BOOST_PHOENIX_ALGORITHM_TRANSFORMATION_HPP
#define BOOST_PHOENIX_ALGORITHM_TRANSFORMATION_HPP

#include <algorithm>
#include <numeric>

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_sort.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_remove.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_remove_if.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_unique.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_reverse.hpp>
#include <boost/phoenix/stl/algorithm/detail/has_sort.hpp>

#include <boost/phoenix/stl/algorithm/detail/begin.hpp>
#include <boost/phoenix/stl/algorithm/detail/end.hpp>
#include <boost/phoenix/stl/algorithm/detail/decay_array.hpp>

#include <boost/phoenix/function/adapt_callable.hpp>

//#include <boost/range/result_iterator.hpp> is deprecated
#include <boost/range/iterator.hpp>
#include <boost/range/difference_type.hpp>

#include <boost/mpl/if.hpp>

#include <boost/type_traits/is_void.hpp>

namespace boost { namespace phoenix { namespace impl
{
    struct swap
    {
        typedef void result_type;

        template <class A, class B>
        void operator()(A& a, B& b) const
        {
            using std::swap;
            swap(a, b);
        }
    };

    struct copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class I>
        struct result<This(R&, I)>
            : detail::decay_array<I>
        {};

        template<class R, class I>
        typename detail::decay_array<I>::type
        operator()(R& r, I i) const
        {
            return std::copy(detail::begin_(r), detail::end_(r), i);
        }
    };

    struct copy_backward
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class I>
        struct result<This(R&, I)>
            : result<This(R&, I const &)>
        {};

        template<typename This, class R, class I>
        struct result<This(R&, I &)>
        {
            typedef I type;
        };

        template<class R, class I>
        I operator()(R& r, I & i) const
        {
            return std::copy_backward(detail::begin_(r), detail::end_(r), i);
        }

        template<class R, class I>
        I const operator()(R& r, I const & i) const
        {
            return std::copy_backward(detail::begin_(r), detail::end_(r), i);
        }
    };

    struct transform
    {
        template <typename Sig>
        struct result;
        
        template<typename This, class R, class OutorI1, class ForOut>
        struct result<This(R&, OutorI1, ForOut)>
            : detail::decay_array<OutorI1>
        {
        };

        template<typename This, class R, class OutorI1, class ForOut, class BinF>
        struct result<This(R&, OutorI1, ForOut, BinF)>
            : detail::decay_array<ForOut>
        {
        };

        template<class R, class O, class F>
        typename result<transform(R&,O,F)>::type
        operator()(R& r, O o, F f) const
        {
            return std::transform(detail::begin_(r), detail::end_(r), o, f);
        }

        template<class R, class I, class O, class F>
        typename result<transform(R&,I,O,F)>::type
        operator()(R& r, I i, O o, F f) const
        {
            return std::transform(detail::begin_(r), detail::end_(r), i, o, f);
        }
    };

    struct replace
    {
        typedef void result_type;

        template<class R, class T>
        void operator()(R& r, T const& what, T const& with) const
        {
            std::replace(detail::begin_(r), detail::end_(r), what, with);
        }
    };

    struct replace_if
    {
        typedef void result_type;

        template<class R, class P, class T>
        void operator()(R& r, P p, T const& with) const
        {
            std::replace_if(detail::begin_(r), detail::end_(r), p, with);
        }
    };

    struct replace_copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O, class T, class T2>
        struct result<This(R&, O, T&, T2&)>
            : detail::decay_array<O>
        {};

        template<class R, class O, class T>
        typename detail::decay_array<O>::type 
        operator()(R& r, O o, T const& what, T const& with) const
        {
            return std::replace_copy(detail::begin_(r), detail::end_(r), o, what, with);
        }
    };

    struct replace_copy_if
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O, class P, class T>
        struct result<This(R&, O, P, T&)>
            : detail::decay_array<O>
        {};

        template<class R, class O, class P, class T>
        typename detail::decay_array<O>::type
        operator()(R& r, O o, P p, T const& with) const
        {
            return std::replace_copy_if(detail::begin_(r), detail::end_(r), o, p, with);
        }
    };

    struct fill
    {
        typedef void result_type;

        template<class R, class T>
        void operator()(R& r, T const& x) const
        {
            std::fill(detail::begin_(r), detail::end_(r), x);
        }
    };

    struct fill_n
    {
        typedef void result_type;

        template<class R, class N, class T>
        void operator()(R& r, N n, T const& x) const
        {
            std::fill_n(detail::begin_(r), n, x);
        }
    };

    struct generate
    {
        typedef void result_type;

        template<class R, class G>
        void operator()(R& r, G const & g) const
        {
            std::generate(detail::begin_(r), detail::end_(r), g);
        }
    };

    struct generate_n
    {
        typedef void result_type;

        template<class R, class N, class G>
        void operator()(R& r, N n, G g) const
        {
            std::generate_n(detail::begin_(r), n, g);
        }
    };

    struct remove
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class T>
        struct result<This(R&, T&)>
            : range_iterator<R>
        {
        };

        template<class R, class T>
        typename range_iterator<R>::type
        execute(R& r, T const& x, mpl::true_) const
        {
            r.remove(x);
            return detail::end_(r);
        }

        template<class R, class T>
        typename range_iterator<R>::type
        execute(R& r, T const& x, mpl::false_) const
        {
            return std::remove(detail::begin_(r), detail::end_(r), x);
        }

        template<class R, class T>
        typename range_iterator<R>::type
        operator()(R& r, T const& x) const
        {
            return execute(r, x, has_remove<R>());
        }
    };

    struct remove_if
    {
        template <typename Sig>
        struct result;

        template <typename This, class R, class P>
        struct result<This(R&,P)>
            : range_iterator<R>
        {
        };

        template<class R, class P>
        typename range_iterator<R>::type
        execute(R& r, P p, mpl::true_) const
        {
            r.remove_if(p);
            return detail::end_(r);
        }

        template<class R, class P>
        typename range_iterator<R>::type
        execute(R& r, P p, mpl::false_) const
        {
            return std::remove_if(detail::begin_(r), detail::end_(r), p);
        }

        template<class R, class P>
        typename range_iterator<R>::type
        operator()(R& r, P p) const
        {
            return execute(r, p, has_remove_if<R>());
        }
    };

    struct remove_copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O, class T>
        struct result<This(R&, O, T)>
            : detail::decay_array<O>
        {};

        template<class R, class O, class T>
        typename detail::decay_array<O>::type
        operator()(R& r, O o, T const& x) const
        {
            return std::remove_copy(detail::begin_(r), detail::end_(r), o, x);
        }
    };

    struct remove_copy_if
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O, class P>
        struct result<This(R&, O, P)>
            : detail::decay_array<O>
        {};

        template<class R, class O, class P>
        typename detail::decay_array<O>::type
        operator()(R& r, O o, P p) const
        {
            return std::remove_copy_if(detail::begin_(r), detail::end_(r), o, p);
        }
    };

    struct unique
    {
        template <typename Sig>
        struct result;

        template<typename This, class R>
        struct result<This(R&)>
            : range_iterator<R>
        {};

        template<typename This, class R, class P>
        struct result<This(R&, P)>
            : range_iterator<R>
        {};

        template<class R>
        typename range_iterator<R>::type
        execute(R& r, mpl::true_) const
        {
            r.unique();
            return detail::end_(r);
        }

        template<class R>
        typename range_iterator<R>::type
        execute(R& r, mpl::false_) const
        {
            return std::unique(detail::begin_(r), detail::end_(r));
        }

        template<class R>
        typename range_iterator<R>::type
        operator()(R& r) const
        {
            return execute(r, has_unique<R>());
        }


        template<class R, class P>
        typename range_iterator<R>::type
        execute(R& r, P p, mpl::true_) const
        {
            r.unique(p);
            return detail::end_(r);
        }

        template<class R, class P>
        typename range_iterator<R>::type
        execute(R& r, P p, mpl::false_) const
        {
            return std::unique(detail::begin_(r), detail::end_(r), p);
        }

        template<class R, class P>
        typename range_iterator<R>::type
        operator()(R& r, P p) const
        {
            return execute(r, p, has_unique<R>());
        }
    };

    struct unique_copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O>
        struct result<This(R&, O)>
            : detail::decay_array<O>
        {};

        template<typename This, class R, class O, class P>
        struct result<This(R&, O, P)>
            : detail::decay_array<O>
        {};

        template<class R, class O>
        typename detail::decay_array<O>::type operator()(R& r, O o) const
        {
            return std::unique_copy(
                detail::begin_(r)
                , detail::end_(r)
                , o
                );
        }

        template<class R, class O, class P>
        typename detail::decay_array<O>::type operator()(R& r, O o, P p) const
        {
            return std::unique_copy(
                detail::begin_(r)
                , detail::end_(r)
                , o
                , p
                );
        }
    };

    struct reverse
    {
        typedef void result_type;

        template<class R>
        void execute(R& r, mpl::true_) const
        {
            r.reverse();
        }

        template<class R>
        void execute(R& r, mpl::false_) const
        {
            std::reverse(detail::begin_(r), detail::end_(r));
        }

        template<class R>
        void operator()(R& r) const
        {
            execute(r, has_reverse<R>());
        }
    };

    struct reverse_copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class O>
        struct result<This(R&, O)>
            : detail::decay_array<O>
        {};

        template<class R, class O>
        typename detail::decay_array<O>::type operator()(R& r, O o) const
        {
            return std::reverse_copy(
                detail::begin_(r)
                , detail::end_(r)
                , o
                );
        }
    };

    struct rotate
    {
        typedef void result_type;

        template<class R, class M>
        void operator()(R& r, M m) const
        {
            std::rotate(
                detail::begin_(r)
                , m
                , detail::end_(r)
                );
        }
    };

    struct rotate_copy
    {
        template <typename Sig>
        struct result;

        template<typename This, class R, class M, class O>
        struct result<This(R&, M, O)>
            : detail::decay_array<O>
        {};

        template<class R, class M, class O>
        typename detail::decay_array<O>::type operator()(R& r, M m, O o) const
        {
            return std::rotate_copy(
                detail::begin_(r)
                , m
                , detail::end_(r)
                , o
                );
        }
    };

#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
    struct random_shuffle
    {
        typedef void result_type;

        template<class R>
        void operator()(R& r) const
        {
            return std::random_shuffle(detail::begin_(r), detail::end_(r));
        }

        template<class R, class G>
        void operator()(R& r, G g) const
        {
            return std::random_shuffle(detail::begin_(r), detail::end_(r), g);
        }
    };
#endif

    struct partition
    {
        template <typename Sig>
        struct result;

        template <typename This, class R, class P>
        struct result<This(R&, P)>
            : range_iterator<R>
        {};

        template<class R, class P>
        typename range_iterator<R>::type
        operator()(R& r, P p) const
        {
            return std::partition(detail::begin_(r), detail::end_(r), p);
        }
    };

    struct stable_partition
    {
        template <typename Sig>
        struct result;

        template <typename This, class R, class P>
        struct result<This(R&, P)>
            : range_iterator<R>
        {};

        template<class R, class P>
        typename range_iterator<R>::type
        operator()(R& r, P p) const
        {
            return std::stable_partition(detail::begin_(r), detail::end_(r), p);
        }
    };

    struct sort
    {
        typedef void result_type;

        template<class R>
        void execute(R& r, mpl::true_) const
        {
            r.sort();
        }

        template<class R>
        void execute(R& r, mpl::false_) const
        {
            std::sort(detail::begin_(r), detail::end_(r));
        }

        template<class R>
        void operator()(R& r) const
        {
            execute(r, has_sort<R>());
        }

        template<class R, class C>
        void execute(R& r, C c, mpl::true_) const
        {
            r.sort(c);
        }

        template<class R, class C>
        void execute(R& r, C c, mpl::false_) const
        {
            std::sort(detail::begin_(r), detail::end_(r), c);
        }

        template<class R, class C>
        void operator()(R& r, C c) const
        {
            execute(r, c, has_sort<R>());
        }
    };

    struct stable_sort
    {
        typedef void result_type;

        template<class R>
        void operator()(R& r) const
        {
            std::stable_sort(detail::begin_(r), detail::end_(r));
        }

        template<class R, class C>
        void operator()(R& r, C c) const
        {
            std::stable_sort(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct partial_sort
    {
        typedef void result_type;

        template<class R, class M>
        void operator()(R& r, M m) const
        {
            std::partial_sort(detail::begin_(r), m, detail::end_(r));
        }

        template<class R, class M, class C>
        void operator()(R& r, M m, C c) const
        {
            std::partial_sort(detail::begin_(r), m, detail::end_(r), c);
        }
    };

    struct partial_sort_copy
    {
        template <typename Sig>
        struct result;
        
        template <typename This, class R1, class R2>
        struct result<This(R1&, R2&)>
            : range_iterator<R2>
        {};

        template <typename This, class R1, class R2, class C>
        struct result<This(R1&, R2&, C)>
            : range_iterator<R2>
        {};

        template <class R1, class R2>
        typename range_iterator<R2>::type
        operator()(R1& r1, R2& r2) const
        {
            return std::partial_sort_copy(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                );
        }

        template <class R1, class R2, class C>
        typename range_iterator<R2>::type
        operator()(R1& r1, R2& r2, C c) const
        {
            return std::partial_sort_copy(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , c
                );
        }
    };

    struct nth_element
    {
        typedef void result_type;

        template<class R, class N>
        void operator()(R& r, N n) const
        {
            return std::nth_element(detail::begin_(r), n, detail::end_(r));
        }

        template<class R, class N, class C>
        void operator()(R& r, N n, C c) const
        {
            return std::nth_element(detail::begin_(r), n, detail::end_(r), c);
        }
    };

    struct merge 
    {
        template <typename Sig>
        struct result;

        template<typename This, class R1, class R2, class O>
        struct result<This(R1&, R2&, O)>
            : detail::decay_array<O>
        {};

        template<typename This, class R1, class R2, class O, class C>
        struct result<This(R1&, R2&, O, C)>
            : detail::decay_array<O>
        {};

        template<class R1, class R2, class O>
        typename detail::decay_array<O>::type operator()(R1& r1, R2& r2, O o) const
        {
            return std::merge(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                );
        }

        template<class R1, class R2, class O, class C>
        typename detail::decay_array<O>::type operator()(R1& r1, R2& r2, O o, C c) const
        {
            return std::merge(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                , c
                );
        }
    };

    struct inplace_merge 
    {
        typedef void result_type;

        template<class R, class M>
        void operator()(R& r, M m) const
        {
            return std::inplace_merge(detail::begin_(r), m, detail::end_(r));
        }

        template<class R, class M, class C>
        void operator()(R& r, M m, C c) const
        {
            return std::inplace_merge(detail::begin_(r), m, detail::end_(r), c);
        }
    };

    struct next_permutation
    {
        typedef bool result_type;

        template<class R>
        bool operator()(R& r) const
        {
            return std::next_permutation(detail::begin_(r), detail::end_(r));
        }
    
        template<class R, class C>
        bool operator()(R& r, C c) const
        {
            return std::next_permutation(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct prev_permutation
    {
        typedef bool result_type;

        template<class R>
        bool operator()(R& r) const
        {
            return std::prev_permutation(detail::begin_(r), detail::end_(r));
        }
    
        template<class R, class C>
        bool operator()(R& r, C c) const
        {
            return std::prev_permutation(detail::begin_(r), detail::end_(r), c);
        }
    };


    struct inner_product
    {
        template <typename Sig>
        struct result;

        template <typename This, typename R, typename I, typename T>
        struct result<This(R&, I, T)>
            : result<This(R&, I const &, T)>
        {};

        template <typename This, typename R, typename I, typename T>
        struct result<This(R&, I, T &)>
        {
            typedef T type;
        };

        template <typename This, typename R, typename I, typename T, typename C1, typename C2>
        struct result<This(R&, I, T, C1, C2)>
            : result<This(R&, I, T const &, C1, C2)>
        {};

        template <typename This, typename R, typename I, typename T, typename C1, typename C2>
        struct result<This(R&, I, T &, C1, C2)>
        {
            typedef T type;
        };

        template <class R, class I, class T>
        T
        operator()(R& r, I i, T t) const
        {
            return std::inner_product(
                detail::begin_(r), detail::end_(r), i, t);
        }

        template <class R, class I, class T, class C1, class C2>
        T
        operator()(R& r, I i, T t, C1 c1, C2 c2) const
        {
            return std::inner_product(
                detail::begin_(r), detail::end_(r), i, 
                t, c1, c2);
        }
    };

    struct partial_sum
    {
        template <typename Sig>
        struct result;

        template <typename This, class R, class I>
        struct result<This(R&, I)>
            : detail::decay_array<I>
        {};

        template <typename This, class R, class I, class C>
        struct result<This(R&, I, C)>
            : detail::decay_array<I>
        {};

        template <class R, class I>
        typename detail::decay_array<I>::type
        operator()(R& r, I i) const
        {
            return std::partial_sum(
                detail::begin_(r), detail::end_(r), i);
        }

        template <class R, class I, class C>
        typename detail::decay_array<I>::type
        operator()(R& r, I i, C c) const
        {
            return std::partial_sum(
                detail::begin_(r), detail::end_(r), i, c);
        }
    };

    struct adjacent_difference
    {
        template <typename Sig>
        struct result;
        
        template <typename This, class R, class I>
        struct result<This(R&, I)>
            : detail::decay_array<I>
        {};

        template <typename This,class R, class I, class C>
        struct result<This(R&, I, C)>
            : detail::decay_array<I>
        {};

        template <class R, class I>
        typename detail::decay_array<I>::type
        operator()(R& r, I i) const
        {
            return std::adjacent_difference(
                detail::begin_(r), detail::end_(r), i);
        }

        template <class R, class I, class C>
        typename detail::decay_array<I>::type
        operator()(R& r, I i, C c) const
        {
            return std::adjacent_difference(
                detail::begin_(r), detail::end_(r), i, c);
        }    
    };

    struct push_heap
    {
        typedef void result_type;

        template <class R>
        void operator()(R& r) const
        {
            std::push_heap(detail::begin_(r), detail::end_(r));
        }

        template <class R, class C>
        void operator()(R& r, C c) const
        {
            std::push_heap(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct pop_heap
    {
        typedef void result_type;

        template <class R>
        void operator()(R& r) const
        {
            std::pop_heap(detail::begin_(r), detail::end_(r));
        }

        template <class R, class C>
        void operator()(R& r, C c) const
        {
            std::pop_heap(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct make_heap
    {
        typedef void result_type;

        template <class R>
        void operator()(R& r) const
        {
            std::make_heap(detail::begin_(r), detail::end_(r));
        }

        template <class R, class C>
        void operator()(R& r, C c) const
        {
            std::make_heap(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct sort_heap
    {
        typedef void result_type;

        template <class R>
        void operator()(R& r) const
        {
            std::sort_heap(detail::begin_(r), detail::end_(r));
        }

        template <class R, class C>
        void operator()(R& r, C c) const
        {
            std::sort_heap(detail::begin_(r), detail::end_(r), c);
        }
    };

    struct set_union
    {
        template <typename Sig>
        struct result;

        template <typename This, class R1, class R2, class O>
        struct result<This(R1&, R2&, O)>
            : detail::decay_array<O>
        {};

        template <typename This, class R1, class R2, class O, typename C>
        struct result<This(R1&, R2&, O, C)>
            : detail::decay_array<O>
        {};

        template <class R1, class R2, class O>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o) const
        {
            return std::set_union(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                );
        }

        template <class R1, class R2, class O, class C>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o, C c) const
        {
            return std::set_union(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                , c
                );
        }
    };

    struct set_intersection
    {
        template <typename Sig>
        struct result;

        template <typename This, class R1, class R2, class O>
        struct result<This(R1&, R2&, O)>
            : detail::decay_array<O>
        {};

        template <typename This, class R1, class R2, class O, typename C>
        struct result<This(R1&, R2&, O, C)>
            : detail::decay_array<O>
        {};

        template <class R1, class R2, class O>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o) const
        {
            return std::set_intersection(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                );
        }

        template <class R1, class R2, class O, class C>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o, C c) const
        {
            return std::set_intersection(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                , c
                );
        }
    };

    struct set_difference
    {
        template <typename Sig>
        struct result;

        template <typename This, class R1, class R2, class O>
        struct result<This(R1&, R2&, O)>
            : detail::decay_array<O>
        {};

        template <typename This, class R1, class R2, class O, class C>
        struct result<This(R1&, R2&, O, C)>
            : detail::decay_array<O>
        {};

        template <class R1, class R2, class O>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o) const
        {
            return std::set_difference(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                );
        }

        template <class R1, class R2, class O, class C>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o, C c) const
        {
            return std::set_difference(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                , c
                );
        }
    };

    struct set_symmetric_difference
    {
        template <typename Sig>
        struct result;

        template <typename This, class R1, class R2, class O>
        struct result<This(R1&, R2, O)>
            : detail::decay_array<O>
        {};

        template <typename This, class R1, class R2, class O, class C>
        struct result<This(R1&, R2, O, C)>
            : detail::decay_array<O>
        {};

        template <class R1, class R2, class O>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o) const
        {
            return std::set_symmetric_difference(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                );
        }

        template <class R1, class R2, class O, class C>
        typename detail::decay_array<O>::type
        operator()(R1& r1, R2& r2, O o, C c) const
        {
            return std::set_symmetric_difference(
                detail::begin_(r1), detail::end_(r1)
                , detail::begin_(r2), detail::end_(r2)
                , o
                , c
                );
        }
    };

}}} // boost::phoenix::impl

namespace boost { namespace phoenix
{
    BOOST_PHOENIX_ADAPT_CALLABLE(swap, impl::swap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(copy, impl::copy, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(copy_backward, impl::copy_backward, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(transform, impl::transform, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(transform, impl::transform, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(replace, impl::replace, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(replace_if, impl::replace_if, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(replace_copy, impl::replace_copy, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(replace_copy_if, impl::replace_copy_if, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(fill, impl::fill, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(fill_n, impl::fill_n, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(generate, impl::generate, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(generate_n, impl::generate_n, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(remove, impl::remove, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(remove_if, impl::remove_if, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(remove_copy, impl::remove_copy, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(remove_copy_if, impl::remove_copy_if, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(unique, impl::unique, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(unique, impl::unique, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(unique_copy, impl::unique_copy, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(unique_copy, impl::unique_copy, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(reverse, impl::reverse, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(reverse_copy, impl::reverse_copy, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(rotate, impl::rotate, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(rotate_copy, impl::rotate_copy, 3)
#ifndef BOOST_NO_CXX98_RANDOM_SHUFFLE
    BOOST_PHOENIX_ADAPT_CALLABLE(random_shuffle, impl::random_shuffle, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(random_shuffle, impl::random_shuffle, 2)
#endif
    BOOST_PHOENIX_ADAPT_CALLABLE(partition, impl::partition, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(stable_partition, impl::stable_partition, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(sort, impl::sort, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(sort, impl::sort, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(stable_sort, impl::stable_sort, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(stable_sort, impl::stable_sort, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sort, impl::partial_sort, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sort, impl::partial_sort, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sort_copy, impl::partial_sort_copy, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sort_copy, impl::partial_sort_copy, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(nth_element, impl::nth_element, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(nth_element, impl::nth_element, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(merge, impl::merge, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(merge, impl::merge, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(inplace_merge, impl::inplace_merge, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(inplace_merge, impl::inplace_merge, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(next_permutation, impl::next_permutation, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(next_permutation, impl::next_permutation, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(prev_permutation, impl::prev_permutation, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(prev_permutation, impl::prev_permutation, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(inner_product, impl::inner_product, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(inner_product, impl::inner_product, 5)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sum, impl::partial_sum, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(partial_sum, impl::partial_sum, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_difference, impl::adjacent_difference, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(adjacent_difference, impl::adjacent_difference, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(push_heap, impl::push_heap, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(push_heap, impl::push_heap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(pop_heap, impl::pop_heap, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(pop_heap, impl::pop_heap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(make_heap, impl::make_heap, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(make_heap, impl::make_heap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(sort_heap, impl::sort_heap, 1)
    BOOST_PHOENIX_ADAPT_CALLABLE(sort_heap, impl::sort_heap, 2)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_union, impl::set_union, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_union, impl::set_union, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_intersection, impl::set_intersection, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_intersection, impl::set_intersection, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_difference, impl::set_difference, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_difference, impl::set_difference, 4)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_symmetric_difference, impl::set_symmetric_difference, 3)
    BOOST_PHOENIX_ADAPT_CALLABLE(set_symmetric_difference, impl::set_symmetric_difference, 4)
}}

#endif

/* transformation.hpp
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
*/