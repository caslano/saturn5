/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_POP_BACK_09172005_1038)
#define FUSION_POP_BACK_09172005_1038

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/iterator_range/iterator_range.hpp>
#include <boost/fusion/sequence/intrinsic/begin.hpp>
#include <boost/fusion/sequence/intrinsic/end.hpp>
#include <boost/fusion/sequence/intrinsic/empty.hpp>
#include <boost/fusion/iterator/iterator_adapter.hpp>
#include <boost/fusion/iterator/next.hpp>
#include <boost/mpl/minus.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/if.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator_, bool IsLast>
    struct pop_back_iterator
        : iterator_adapter<
            pop_back_iterator<Iterator_, IsLast>
          , Iterator_>
    {
        typedef iterator_adapter<
            pop_back_iterator<Iterator_, IsLast>
          , Iterator_>
        base_type;

        static bool const is_last = IsLast;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        pop_back_iterator(Iterator_ const& iterator_base)
            : base_type(iterator_base) {}

        template <typename BaseIterator>
        struct make
        {
            typedef pop_back_iterator<BaseIterator, is_last> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(BaseIterator const& i)
            {
                return type(i);
            }
        };

        template <typename I, bool IsLast_>
        struct equal_to_helper
            : mpl::identity<typename I::iterator_base_type>
        {};

        template <typename I>
        struct equal_to_helper<I, true>
            : result_of::next<
                typename I::iterator_base_type>
        {};

        template <typename I1, typename I2>
        struct equal_to
            : result_of::equal_to<
                typename equal_to_helper<I1,
                    (I2::is_last && !I1::is_last)>::type
              , typename equal_to_helper<I2,
                    (I1::is_last && !I2::is_last)>::type
            >
        {};

        template <typename First, typename Last>
        struct distance
            : mpl::minus<
                typename result_of::distance<
                    typename First::iterator_base_type
                  , typename Last::iterator_base_type
                >::type
              , mpl::int_<(Last::is_last?1:0)>
            >::type
        {};


        template <typename Iterator, bool IsLast_>
        struct prior_impl
        {
            typedef typename Iterator::iterator_base_type base_type;

            typedef typename
                result_of::prior<base_type>::type
            base_prior;

            typedef pop_back_iterator<base_prior, false> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(i.iterator_base));
            }
        };

        template <typename Iterator>
        struct prior_impl<Iterator, true>
        {
            // If this is the last iterator, we'll have to double back
            typedef typename Iterator::iterator_base_type base_type;

            typedef typename
                result_of::prior<
                  typename result_of::prior<base_type>::type
                >::type
            base_prior;

            typedef pop_back_iterator<base_prior, false> type;

            BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
            static type
            call(Iterator const& i)
            {
                return type(fusion::prior(
                    fusion::prior(i.iterator_base)));
            }
        };

        template <typename Iterator>
        struct prior : prior_impl<Iterator, Iterator::is_last>
        {};
    };

    namespace result_of
    {
        template <typename Sequence>
        struct pop_back
        {
            BOOST_MPL_ASSERT_NOT((result_of::empty<Sequence>));

            typedef pop_back_iterator<
                typename begin<Sequence>::type, false>
            begin_type;

            typedef pop_back_iterator<
                typename end<Sequence>::type, true>
            end_type;

            typedef
                iterator_range<begin_type, end_type>
            type;
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::pop_back<Sequence const>::type
    pop_back(Sequence const& seq)
    {
        typedef result_of::pop_back<Sequence const> comp;
        typedef typename comp::begin_type begin_type;
        typedef typename comp::end_type end_type;
        typedef typename comp::type result;

        return result(
            begin_type(fusion::begin(seq))
          , end_type(fusion::end(seq))
        );
    }
}}

#endif


/* pop_back.hpp
4M/4G/6KrSpQX9gJf8N++E8cgP/CoXgbY/APtKBzBY4jsAJuxcp4DqugM/Xtiq5YDRuiG3pibeyFTXAINsVJ6IFzsDmmoCcuxVa4ClvjemyDG7EtbsN2+BK2x1exA1qvGynrWcYmPSzbKdsjx3FyvZ3+rj5mowe+jtbr7tgLd+MYfAsfwbdxNubiAtyHG/A9fBP34zl8Hy8peaJSjiN4C/OxJnl/jEPwExyFn2ES/h0X4Cl8F0/jfjyD3+FZvIJfYwPl+jc2xe+wE17A4XgJR+FlnIBXcA5exRVYhKvwZ8zB65iLvyr54Q2U678yVit9scn1X5fi/QX2xso4EatgDLqiBe/DBKwq813rJGOmYkXpx92V42SZ7+mK6nr5CttiIXrh1/gwfoPT8Twm43e4Ai/gJryIr+Fl3IdX8CD+iIfxJ/wRr+FNvI638JeKcn7lrI2L6vSKlE85L/GUdpOu9LOYgS3wWfTG53AorsGHcC1acB2m4gbp35/HTNyEO3AzvoqZ+Ca+gEdxC36ML0p/vx3/gTvwPGbhDXwJb+MurO5MmbENvoadMVv2A69jH3wDR+FuHItv4Qx8G2djDs7Bd3Apviv7g7/J/uA93Ir7MQsPoOyfZTxWZZxW+/3z1qrq+ew2bI0vYmfMwlH4EgZhNsbh6/gsvoEbcTduxT24B9/EvZiDefgOUg6e95XxVPFJWX91lXRSjlymq437sAW+h12VdBiI+zEcD+JiPIQb8CiexmN4Bj/ES/gR3sBPsDL5fYp18DNsjiexJ36OQXgK4/E0zsUvcQH+A9PwrCwHbUTGTGUbk+WoJfe1Kj+esp20wlbYGjtiW/TBduiHHdCCHXEedsZ09MIM7IKvYFd8Hb3xU+yOJ7En3sBeeBt7o1KoPrK9sA3KuKr0PbLe3TBWyvlSBbWcO7Etvord8TUMxGx8GN/ABbgbV+EefA/fxMP4Fh7Ft/FbzJF+nnt6qGTb+4ZqYKrkv5fpamMueuA+7IR/w1H4HoZiHk7HA/gcvo8v4UF8BQ/jGTyCV/EoXsNjeBOPo3Yd/HPH12e2MV09fBG74HZJl66EpKvrbH//01Bntd8Zjm1whBynjMQRGIATMBBTcCwuwnFyfWQ8HsUg/B4n4FWciD9hMF7Dh9Cd/ENQrhvJWKSUiTBeN9rkpq7fzdgKM7EHbsX+uA0H4XYcjjswELMwBF/CabgTN+AulPMHGVeUczKT84crVdV8f8SeWIT98Sf0x58xBK+hHLfLWKDKGKH2x+2dpZ10Qz/0lnbRC1Owt7TPgbgaB+EW9MPXcTC+i/54AIfgMRyKp3EEfo0j8SIG4I8YhEp9T8AGOBEfxKk4GcMwDMNxGsbgHJyBj+JMfAFjcTfOUsqBFvwQE/AczsXfcR5WUo67sSYuwAfwcfTFNByKy3ABPo2bcTnuwL8o88d0PIor8UtcjdfwWfwF1+BvuA4foL7X44O4CZvjZmyNmdgBX9CO22TcThnP03jcVl++v2iIzbARtsfWGIhtMAnb4iJsh09jB/waO+FV7IxKJl2wCnbF9tgN+6A3DsSeGIB9cR764Ersjy/iANyBvngIB2E++uFHOBhP4RD8Cocq+eMwvI3DUVkPI7EeBmAfHIX9MRDH41iMwGBMwcn4KIbgQnwYpT9kQeX+FGf7/nCxs1pvT2JbXIcBuB5jcSMuxk34DGbK+c0W/BC34QncjicxCy/iS1iEr2JV8n0NZT8mY3YqY3na78c6y/myF7bDLtgPu8rxVDecgt6YiD1xIfbCZdgbV2JffA198G/YD/OxP36GA/AL9MUvcSAW4iCUepMxO+lDTPYjb0k/9za2xBzsiO9gd3wX/TEXA3A=
*/