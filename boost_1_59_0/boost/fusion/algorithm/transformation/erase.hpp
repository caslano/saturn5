/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_ERASE_07232005_0534)
#define FUSION_ERASE_07232005_0534

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/iterator/equal_to.hpp>
#include <boost/fusion/iterator/mpl/convert_iterator.hpp>
#include <boost/fusion/view/joint_view/joint_view.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/support/detail/as_fusion_element.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/adapted/mpl/mpl_iterator.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence, typename First>
        struct compute_erase_last // put this in detail!!!
        {
            typedef typename result_of::end<Sequence>::type seq_last_type;
            typedef typename convert_iterator<First>::type first_type;
            typedef typename
                mpl::if_<
                    result_of::equal_to<first_type, seq_last_type>
                  , first_type
                  , typename result_of::next<first_type>::type
                >::type
            type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(First const& first, mpl::false_)
            {
                return fusion::next(convert_iterator<First>::call(first));
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(First const& first, mpl::true_)
            {
                return convert_iterator<First>::call(first);
            }

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(First const& first)
            {
                return call(first, result_of::equal_to<first_type, seq_last_type>());
            }
        };

        struct use_default;

        template <class T, class Default>
        struct fusion_default_help
          : mpl::if_<
                is_same<T, use_default>
              , Default
              , T
            >
        {
        };

        template <
            typename Sequence
          , typename First
          , typename Last = use_default>
        struct erase
        {
            typedef typename result_of::begin<Sequence>::type seq_first_type;
            typedef typename result_of::end<Sequence>::type seq_last_type;
            BOOST_STATIC_ASSERT((!result_of::equal_to<seq_first_type, seq_last_type>::value));

            typedef First FirstType;
            typedef typename 
                fusion_default_help<
                    Last 
                  , typename compute_erase_last<Sequence, First>::type
                >::type
            LastType;

            typedef typename convert_iterator<FirstType>::type first_type;
            typedef typename convert_iterator<LastType>::type last_type;
            typedef iterator_range<seq_first_type, first_type> left_type;
            typedef iterator_range<last_type, seq_last_type> right_type;
            typedef joint_view<left_type, right_type> type;
        };
    }

    template <typename Sequence, typename First>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename
        lazy_enable_if<
            traits::is_sequence<Sequence>
          , typename result_of::erase<Sequence const, First> 
        >::type
    erase(Sequence const& seq, First const& first)
    {
        typedef result_of::erase<Sequence const, First> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::type result_type;

        left_type left(
            fusion::begin(seq)
          , convert_iterator<First>::call(first));
        right_type right(
            fusion::result_of::compute_erase_last<Sequence const, First>::call(first)
          , fusion::end(seq));
        return result_type(left, right);
    }

    template <typename Sequence, typename First, typename Last>
    BOOST_CXX14_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::erase<Sequence const, First, Last>::type
    erase(Sequence const& seq, First const& first, Last const& last)
    {
        typedef result_of::erase<Sequence const, First, Last> result_of;
        typedef typename result_of::left_type left_type;
        typedef typename result_of::right_type right_type;
        typedef typename result_of::type result_type;

        left_type left(fusion::begin(seq), first);
        right_type right(last, fusion::end(seq));
        return result_type(left, right);
    }
}}

#endif


/* erase.hpp
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
*/