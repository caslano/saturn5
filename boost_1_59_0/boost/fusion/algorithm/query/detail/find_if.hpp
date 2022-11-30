/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2007 Dan Marsden
    Copyright (c) 2009 Christopher Schmidt
    Copyright (c) 2018 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_FIND_IF_05052005_1107)
#define FUSION_FIND_IF_05052005_1107

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/apply.hpp>
#include <boost/mpl/eval_if.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/or.hpp>
#include <boost/fusion/iterator/advance.hpp>
#include <boost/fusion/iterator/distance.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/support/category_of.hpp>
#include <boost/core/enable_if.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename Iterator, typename Pred>
    struct apply_filter
    {
        typedef typename mpl::apply1<
            Pred, Iterator>::type type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if;

    template <typename First, typename Last, typename Pred>
    struct recursive_find_if
    {
        typedef typename
            main_find_if<
                typename result_of::next<First>::type, Last, Pred
            >::type
        type;
    };

    template <typename First, typename Last, typename Pred>
    struct main_find_if
    {
        typedef mpl::or_<
            result_of::equal_to<First, Last>
          , apply_filter<First, Pred> >
        filter;

        typedef typename
            mpl::eval_if<
                filter
              , mpl::identity<First>
              , recursive_find_if<First, Last, Pred>
            >::type
        type;
    };

    template<
        typename First, typename Last, 
        typename Pred, bool>
    struct choose_find_if;

    template<typename First, typename Last, typename Pred>
    struct choose_find_if<First, Last, Pred, false>
        : main_find_if<First, Last, Pred>
    {};

    template<typename Iter, typename Pred, int n, int unrolling>
    struct unroll_again;

    template <typename Iter, typename Pred, int offset>
    struct apply_offset_filter
    {
        typedef typename result_of::advance_c<Iter, offset>::type Shifted;
        typedef typename
            mpl::apply1<
                Pred
              , Shifted
            >::type
        type;
        BOOST_STATIC_CONSTANT(int, value = type::value);
    };

    template<typename Iter, typename Pred, int n>
    struct unrolled_find_if
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              mpl::eval_if<
                apply_offset_filter<Iter, Pred, 2>,
                result_of::advance_c<Iter, 2>,
                mpl::eval_if<
                  apply_offset_filter<Iter, Pred, 3>,
                  result_of::advance_c<Iter, 3>,
                  unroll_again<
                    Iter,
                    Pred,
                    n,
                    4> > > > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 3>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              mpl::eval_if<
                apply_offset_filter<Iter, Pred, 2>,
                result_of::advance_c<Iter, 2>,
                result_of::advance_c<Iter, 3> > > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 2>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            mpl::eval_if<
              apply_offset_filter<Iter, Pred, 1>,
              result_of::advance_c<Iter, 1>,
              result_of::advance_c<Iter, 2> > >::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 1>
    {
        typedef typename mpl::eval_if<
            apply_filter<Iter, Pred>,
            mpl::identity<Iter>,
            result_of::advance_c<Iter, 1> >::type type;
    };

    template<typename Iter, typename Pred, int n, int unrolling>
    struct unroll_again
    {
        typedef typename unrolled_find_if<
            typename result_of::advance_c<Iter, unrolling>::type,
            Pred,
            n-unrolling>::type type;
    };

    template<typename Iter, typename Pred>
    struct unrolled_find_if<Iter, Pred, 0>
    {
        typedef Iter type;
    };

    template<typename First, typename Last, typename Pred>
    struct choose_find_if<First, Last, Pred, true>
    {
        typedef typename result_of::distance<First, Last>::type N;
        typedef typename unrolled_find_if<First, Pred, N::value>::type type;
    };

    template <typename First, typename Last, typename Pred>
    struct static_find_if
    {
        typedef typename
            choose_find_if<
                First
              , Last
              , Pred
              , traits::is_random_access<First>::value
            >::type
        type;

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter, mpl::true_)
        {
            return iter;
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter, mpl::false_)
        {
            return recursive_call(fusion::next(iter));
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        recursive_call(Iterator const& iter)
        {
            typedef result_of::equal_to<Iterator, type> found;
            return recursive_call(iter, found());
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename boost::disable_if<traits::is_random_access<Iterator>, type>::type
        iter_call(Iterator const& iter)
        {
            return recursive_call(iter);
        }

        template <typename Iterator>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename boost::enable_if<traits::is_random_access<Iterator>, type>::type
        iter_call(Iterator const& iter)
        {
            typedef typename result_of::distance<Iterator, type>::type N;
            return fusion::advance<N>(iter);
        }

        template <typename Sequence>
        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type
        call(Sequence& seq)
        {
            return iter_call(fusion::begin(seq));
        }
    };

    template <typename Sequence, typename Pred>
    struct result_of_find_if
    {
        typedef
            static_find_if<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
              , Pred
            >
        filter;

        typedef typename filter::type type;
    };
}}}

#endif

/* find_if.hpp
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
*/