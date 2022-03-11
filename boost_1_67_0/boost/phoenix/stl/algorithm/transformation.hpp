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