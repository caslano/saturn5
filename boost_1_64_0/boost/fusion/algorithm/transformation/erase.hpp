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
NL6v5/h99U+S4QNT8UZ1Uy71VFZEUF6O39e13uzdNqw3a691ZVcPMH5fsfrmnyfcuey3m/668qMv98592n292b4Tjd9/9ELue/eU9Xz3X1+vn/lK/4eYRP6x7/fG3yzve3P+vad++bQDHZI+3Pmo27q46NenOa9zi61bO17r1ub71q39/hpP91e3/PqUl5uqkyZNefyZtq1bS43THC44R+stresNWFqg9TWaTwWKdZ51fU2BYtKvgv1hIRwJi+AU6IHT4GqYC0vgSlgKC+Aa+Gd906yVnftk53Nws+yMxp9EOA72guPhOTADToAT4BQ4EZ4LJ8GlcDK8AE6BXjgVXgrPhV+F0+EdcAb8FpwJG+AsqHUzmhNF2ki9bd3MTR38/nwDjoXfhIH1JY3SG4rU29aXDOO8U2Caym04HGLZ4yELOSz96Ui9w3q9RHgZ7AE3wV7wC3AQvBxOgTQXSk/zhOAKh/RyyG83eB7sDhfD/nAJnASXwmVwmaVc9iq9rg7l8qr2YHgNdoGvQ3P9n/Q+56BXL707YVd4l3XPh+7u9n4lvZdk72VLOaZKL9Mh31kn+M+fC8+E82AfOB+Oh9nK/wJLvr1h/HhBfvxCfhy0+F8XRm+k9EZJb7RFrzGM3jjpjZdehkWvqbt7OS+T3vkq589Lz9tB8zo038PQG+a/n33HA1oX9SDso3VSQ+HD8Fz4CJwHvwfPh4/CAvh9uBY+BtfDx2EtfAJugU/CG+FT8Da4D34b/hi+DH8CjW95++E0+Aysgc/Ca+Bz8Db4PGyEv4A/gAfhT+CL8E34Ejz5BOoH7A1fgQPh63ARfAMWwWZ4MXwTfgG+Be+Cb8P74Tvwu/C38Gn4B/gefA+eRrkdgp+Df4Jj4WG4DH4Al8Mj8CL4V3O9m+abwPVIvW29W67av5WqnxfCofAiOBXmwVkwH34eroLlsBAG0m9S+jc5pL9L7fhuOB3eDxfDB+A62Agvgw/CK+FDsA4+rHqTE6c5HnCu0j8ZzkQC66C7wErVlyo4ElbDsbBG9Wc9nAkvgUpXczjIq0O6f1d9/Bj2h5/AcfCfcC78FC6D/4LLYZx5f2h+BZzlcH/sUbv+KMyEP7DeV9Ib76B3vfTq4Ch4g7n3jeYfwAKk3rae9gnp7YVj4JPQ12fU83KfpT2rVzrlDu0Zdd3X/v8MToYH4Ez4LMyCzym9583rpm/1sNShfLurXvTQc70nzIG94AXwLLgK9oZFsI/S3Y/omzvf4v3pJvnvfw58V7qVsA+skt/VcBJcD2fAS2RvA1wBL4MlcBOshl9QvfwivAPWwgfhFfBJ+CX4DLwSPgs3w7fhl+Ef4VXydws8Aq+GnfD3q7ALvMa87vrmDpMcrnuOnufnwTPhYoteZhi9+dLLlt4Cy3XOl95sh+vcT3r9VX4DYBocqPo6CM6Cgy1+7A3jx61Kb7v8uM3yHtMsvZ4O7zGTpDdZelNgDzjVtKvvuDDdwe40zkuC0+EwOMNiV99ZsRVqdwXnnQovgClwpfQvtD5vw9idLbtzpJdlsdtk6oXaLdb7wmqYCkvgMFgKdd30XZK6gJR0OLo9P7bF6Tujvj/W2/as6qg9yU6CQ+HJuk87qR0/FRbC0+Ba2BlWwC7wYtgVXgo/p3a9G7wNJsJ74em6n86AT8Az4T6YpPJ6N07fDuGfdZ/3MPIh/wZr3f0ImA7PgRfAdHgrHAnvgqPgU3A0fB6OhS/CcfA9OB5+BCdA4/6cCBPhZDgaToGT4FQ4HWbCcjgdfhnOgFfD2bAezoHfg1nwGTgX/grOg2/DbPguXATfhzlQ9Yrvie7tP0uRadfIJxwF06G/v6XvgTBZe8FY+1vJlvPydV4=
*/