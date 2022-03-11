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