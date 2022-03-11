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