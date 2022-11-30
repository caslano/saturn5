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
qImqcT/14VAvcUdVbUJax4UEbqQ6n4TkcaYJyRngpU84K3jlE855cXAYJ044bSIi4zJf2Px55hhBF8dkHayOqk+ggfAL4m6AxEycwg//nBQMYLUqsxpdPCWn2KY3oGCV6QpyLZ6BxPR8ku6VyF6oorfwYZkrpgsGGGMbH1TQVg2btsrYbCECPYpScejgE/P1BOatV0Iap9GmxaFCWREVwYyqDrOII62IQxTZja1WQox2D4/LQT6tpJQkJXXSgZqhTgbIKSP0naFKJw22bieEcV3Yo5IIGCqrdcu4POsVF/iZPlnvxDZgmFZni2tnC7hsXcZxcl0yqAG2FuaHSl2hYpceRxhOiCB6iSl8bNvEincxBVxtCfE9gD4/4dtm4UvYusU1ouyROQo+jgMOl7K+AxUqVKqmYe8lIIie74zoFbhCbugkEHbu4rLieFWx4nqOV5xDUJIyyk4ysSCApu2FqqwU8UbbBaGwYam7p1jSJ1HDi1W42kuxGaIdFKn6EmeoUHWqhJmBsjXLiYq8tOj31XjObEcUpF5qfA1LP0LjklpfxVEHnuxEntyI4O7FjAAaWqtcKFe5+zDDz8uNCwUolR3GEdK6o6YKYMfaiPcWKKF5CkC4GiHsQwj70egF9E22UqHsUgewlJ+XIpvyPXxmjLbe4GOCAwcXGGTE4N4mjMxybjF+aUX3BS6/44QrzZi7bM5Y0IneiVqfUf8XVv3CfKifn1Y/315fPl1o2tf4F0CDqpfoN6G3Aq6pw6k4jWkkRJ7CpD6DIK5NzXvgs4FylBuVcp/2mjaFZ/D+u1mNw+AwYdxM5BoHcZB1HR6paIqcVs3yLv9x44tWjYrTLutGwHYj6Id/pk/gx/kLm87XlyqkwGCIS2SVaz2YKvSgLP8XnxMGUjLgVPn0W7jNskSSi+ooH/cquRl1GFu4n6ng7jSEizCPI7wTm6gEFDuK+QKxunKFDGV9oejzCpk/NeRPo8gFxcmoONJLO7glRPurshFhf+M34tBrcTQlVd+c2o1q+SWU+a2oHLfhuIuDYvwI1mnLWacnR52F3MGzxWdXiPis04rPjiHTt9GQMokZlOtIXRpfRkmSr/4VvFrJzzDMDPNhZqY6a4CuTg3QVeSNqcGjchJGaFkYFSqZZjCuwUK/iT+dTmCxperIZqDyOovKP7eorCa/fmYRH3APLuIOCspa58+7vfKMhv4L4VhJFqu+NHGKu8l4RzUQV64fWGce1amx6qhmnSpepyatjkz+P4zBXpM6Km+Sp9Io5wxH1FCRKiJJ1bgdTXBooRyazwc8cCB/ajmQTtm4A5lnwq5MwZ6stMGmRDbsr2bD/pkd9p1cMMYhPrdj08lvI/srLXewxKZfN1icP4ycvws5j7yL/1jocY46Eznq1Iigo9bUGponCm7iOcqdmOKqY8UpS9KilqVpqcWY6rKc4sWWn2ubt6Eaa2Q9ibxwyopxE3f9hZ05l/+/1xoTjqX8f8xcdTv5/3s5i2fT/f8bP7P/f+PZ/f8lKZcezZ+K82kzdp8/VSD4Rvz/UEodVsfymlIKEMMTd1u9qTbLZhwQNmOvfU4HkUtJ4SKsdAdZBrCNR9A+pyb+LkrhAXLX7cEmWQs9ZS0gElhmjwSWpW5hX6hn9JwG5HQUm1gi64e5Kz8fqP4qsusemr4xU/faYmVQerZQzHXcLsKD2yk8uFGAM/iZpOBxVvvQ94Chr8zhL8ur2+R1ePOOF2KsxFmYbxyzBsCL8klOnP75+teI/nwOzof+FyfW7c0L9JblefO8jsMjjc+p0PccbKPZ9wolHooJCZVZ/YjLBbkUXyiljRmZZZZxE6g/IKKroIhB6vC8g6IgFEiQzz3UifkNPj5XUewdTo/1XTxmD/OYXckV62fWW3e2eoBLyBY/wjiMviTIk0IyQC1E0b7+BGrXYVk/ZoUoxbL+GO++SB24CvpDYpKt3rT3HB4f2x8Q8Oo5vBN8CKJsCFDozAMB2ReURfrrAuByM/RaLtjXYGY0iIyImUEXb8v6IwiXPMqnMz3KR7kD+zieOJ2cOnx2dYhPb6FO+vSHqe8ShjvtGFbzRBps4dM+yjlhcQk97QfR23eGSp08H+MD96RE9qYWqhAeKjWmcHTCGNNxxJ5EeHEuTejAdAb3IHEPAnrQ9CNllDnxWUE34CnEGFy0h7AhdKOW1su10ClFWXw+V0M+nFUAOmy5akMPnGoe+fqDz5kcy6aZ+GnnYBWfbkOj0Ww3Gs1p0wctWd5Ji336IGP+YC+fP3hWGIhnyUBArPkCZkCM+WL6/MHzn2X+4Hkxf3CZlDV/cGHmVyzz3CimHr5hn3poOdPUwwqh5U2mljdlTUEc4FMQjakpiBVk5F8159Qc9Mx5EeE+TfLca4v5eUFnaJ4t2D+ZFuxzTttDXISJz1cXW3IyI/IZ3rUs0fiMlwnCt1Kx+MmMWPxFKxYHdadU7rgaItO/EhHsi1wfX8+MYL9pKxfKVU5EsN+0xTWL+BYZED/7ybOU02Nt3t9eN58T8XjbXt54MWe8PS58kfT4mLgRTI89tqSPI36bz/btdJ+NxhXsUfE9Upprbq/zWo46LVl+xEvCj/jL9Njj5bPEHg9bsccj9mdIS0kHYtYzpCHxDOlR5PcX+VOfPbZnSGXn8QzJDrPIgmncYoP2QTa07GdIbyjGvkyHkGNGj5UsFJUAWnE1uDv1dAnbUvw8ez5N46czsEEwMGJ3xBrFqNVq9tZW4QRsEOHXY9zQmbyrJToft3h3QvDuCURsFaf2SRvvAufBOzvMIgumcbEN2gfZ0HI+f3vCZJSFj/3528WcNacEzW0mzW3pz9/etg8PwlcBI8bAxHpnVtMcwtPYjhafRqWutgzqM6jDzxL2B7EcFYbYskPElnTeof8Yp++ehqp0w/gLbEbkVsq5cqdy5v4yZ+5OJVfuyzlzCx25cu/Nmft+ztw1eblyT+TMdai5crvSc1GOL7sZe+sHH72BC1SO4DrgrNckzSv87BW+E3sBXwpZnN0Y/yiwmdEdQ1uPD5v4IrWOTvz/4Y6Z4wc2/NfxguSpUxO/eeofNoXeerf3vn97P/ZG14fHb2377ei/n5beuul3l+XN9G4tOLRu15VTdxyYByPQKwoH8xOMBRV6UZPtgjPYfnYK7r8G6X3Q3gxcL4TzpWB24/bNOTfQMtxk1paXa2n74FGx5bm5kSNueZ6kRd58A22+qXziPDZ9ZOzq82n20zdxCTQxnKuJHrH4eQ8t7+24IPQcxtWt527swjIxBLLsO3ejn76BYWhgh/nuAd/9sxNSMbEbKd/bc4SaxN1VM2W3k96aML/HkA76JIC+VeqknUqjAsFMwSTFGxP9tJ80f1sitT9pemlzH+Fu+h2w9ug+906sfwBMujppO9NRWogeFY0laTH4Rtq8Nlts5wIbhc7Vu45W3o9n0bZG7HyeTlGq9LmAPwHArz4T8FwbIKfKnu/Wx8vAaFzbRTu4pvZyjRHfOaezdy5P0tckDGuX7nPzfjc0svlCAnwPAG69kt5j6BfKbtDOtAkCk7k3rcmMs2lqF+4at2otX2CciCW15HBMS0THYpr53Z/UB2s0+D8GA8TIxGhMM+hzvImwtK0DlyTj15wGIHdIi1o1beuWo+KbiFrS0MaMeAyaiSI8Ew4UgIo4cISlByWBzrCRgNxM6GkfVcbF0BZK4o7to8FaYgTvRsdjxmRidH9Y418c00aS2lDcGCMEsmoBvkOIYnQQP+2IZQHpKCA0HIuHpZW5eJUNIyertmaxKskrfkpOre0BBAaMsbHo+KC2aKphepE2aMQSGoKK7RsB7oEQRnh6ggby0f1wA7+qPYgYTkWmw1I/ryiKRTX6QKGW3D8R04ANRKMgDzdY0CbMryyHtS3R64F+cBfMtmNx/DgrZ63tc3xhabVgGrA0xTQ7JzgA5DNcRuDSTvoAQPiShLTGcG8PURjwJyR5+eFogqvKAH6nPInfQdTwDfIoujN2VJMWGFxgT0zRkH0JqJQYGgH0sYT903ZA12hsTzQJWCwXdAyNQA1ojgMaB2oGc2EVlm6TQORCcECmuIUFhcShp4DMtammaVztT99JsxVEGNpGwadENgRe3RgHsZ4RRiPiMW4KgLTLDgV4fr6NUTsZKip0O7O9xVfSl7WwBH7naRSwTH1SmIPE97XWdG9aI/1/VWcDG8VxxfH/3t7t7n348F18xth3e2fuq+Zsc/4I2ED5soNDSiVTjHuRCEFOQ0oFCZWbOrQ0wdg0ojghJC2JEiiCRk2jkCiJoihtLRWChURrNaGFNjRWhUlKqUAJoqQVtIn63tuxl1q6v+e3M/Pe25nZ2d27nTu19pEfiOWv12hsKbY0tcvXqMhnqB/QDXz6UaAzDZzJ848qyI9Iyc9GVX0FeJGu8dJr12B0tbMeId21diWvaxwnHqE7nfTyzQ/1TT2HQZPd1+99O+jnm/yb2RZ+Y429r1ePvq2g11V6DTnPx+Goimu5egA873wmIa+ZssYQcp8fVKw5z0fKf00tMdCd52PForOnBt7wHPEEcFY0oF/2hJHVbT2MOaKtogtFu0Rf1HfpUSzxprxhXPfyFstn6wa+7ztCdY8ZrxphZEy/GUbJXEHab3LuK+YRj4EzJpfJWVxr0lphGugPHPFUIh9k76VwRziAYITLVMT0WBh3xIqkoRou/3nNRzVhVMbZZoPoXaL3iW4XfVb0ddJqfBo/F6+GN3EuHkYiwdaWiD6W2JAI45kE2zyVeJnSmv030oToErve/jXW2Pz+W5/NuTtJbRwljWLcTnmjuGrzvieT9TZ5T7Kdx5Ps93lJHxZ9hzSKPyS55H+S3CbhFOuGlN8M4sEUv4+6N7UtFca7KS6v1V6ldKJW2ln0XtGttRzDHkn/Ms0eT6evpgK4LfNFOozGDG/vJq3G7sy5eCXezHA7j5NG4ctuS0VRkWUv67O2HsC+LLftySxHq+VYQznuhQU53v48paO4kZvMhVGeZ19fzvOWe/Js57t5tvNCfk/eXSPMx8thfkwTCxUN0rgvERmU9go9RFRGI69c6BGicsqNQ9PKaWwvpJFowCYC9hNFiDKS9zpRjEa8Q38UKqNRP0h0mWgW2WmQPI/mUKN4KNfY320oCsWJiqjCYqEGolYk6XqD10QvJaJ+pCsPtvlVsZKi45xL3i1W0nTlwvQAUSf5HhZ/A0RRosfljYw9RLWYw/e7RIfFSj1+LPVek3rNeFlojKiE+fiNeJ8gqiQ6IXnXJc75OCV5Hg/bnI9x8TeLqBpteE+o4OGWaMNZ7CDq8HzNMwvt+EBoq9ACIp5/Bj38ifZSIp3yDtYyLcc/yMMbejfpr/QS6Q3vpul0zLcFhnHcdwC9O075DpGeFp0QvSj6GamGZQbrZoPrDogOGRQt+szPebupUYduN73alOURcxOacNyMaPPwdzNG22+3bNJDFtd9y1pG6d9bnaRXrDupjO6PkVb5ueTbwWWUXh+KaU34reiHpBEsLONaj4i6XuZhsIxrfVJ2gWrdLGM7gTBv+XOYo5oUrZlxgTQ14zPSBTNukM6LsIXeCFsbEs1EObb2KKfXRDvJTl+UrQ1E2VqpgrcfrNhEbTJWcUHr3XFG9C+i50Uvijq5n5JGkIn9yBPB6tiTHvI7mz1Ozj5AeoXUwInqEml9uqTOESfLVuuLMPWdDid9G/Vlt9AWvYvOIu/Ld0EMW1zSg/NCQ1W/kzznb8x3+v9o4hY6YV7S191C14h0VNQyDeILKunFZkWV3nVEY4o2ePvoXLJUlvxN+r/jXURnmzuFLmocp4mfKuI4LYwKDVkNvm8TXVe0ksiPuqyzD9/0DdB8MD/r7lEAd2Sn9mg7UY/QmMZ7FESvogmhkkPY5dtJNJB14nzOx3lPZ904gziQdeMMojPnxhnC/ULD0oIhDOSmYhkhGs65rRvCSM7xd1rovKIJoaLMkic8l/T9RCsUXSMqQ2/ejTNMsyvTDy2fMUp0v9CglTaOEz3o5JG/45iBH6iSTxoDdHTvUnRQ6AlF48b7RM9N1ztLNDpNf6V5Mf4lIXxoXKL5p5M/yqWZt9m8RvSNuqmSljYTx+qcdhk2u2j+mahz+6Ea1hy3j2pQKTTm/7c5QJSZ48RSbc3SatCmqMPKEW1VtJYojl84VvAtq6glkCq4fWtjdsHtWxuZgttmNjoKbm/aWFVwe9PGzYLbm0mk6mX9YtUrmSd8SawT+tjiOJM4VO/sQ8HP9FK9E1mnf5WWxFuK1vqLRO8q2ujv1lI4o+hhfw/Rx4qGqV4ttjU4/bfXfzfRoKKf+9cT7VY05u8jelrRBcqbjXcU/UvomKKyQB/RqQa35dPTR3Em0K1l8M8Gp5WaAg8Q/deph/bAFi2L8kYZdfpKIjp3NbqjtQ6tc93RWofxuU69ewL9Wh2uCO3D/sD3tAJ6ig4dJWrAY0Wn5LFAF+biJUV/EnpP0SeBndpcXFbUFtxNM3akyaEuoma0KSoF92otCDU7HjYGf6LdjuFmJ6+f8uZhVNEQURvMFoeeDfZrC1AuNISfBV/QFuGpFrenF8PX6h7FizGzdaqPRogyQh+B22Ux7mp1WrA98Ka2FKtap46ALjpX9kxTj7Yc9ykrW0PdWgceVvRoqIdoyLEC7pVO7BHa9z9WX7akOTYAgENLrF0JeFRVlj7v1pKKJCGrDQFMMAvYYgZlhxjJYqCGhAAJ2yhgJfWAkkpVqFcJRARBdGy6tecDbW0G7AG1R1BbltHpj250xAWnEb8eutVBurVFG5d2t8dvxv7acc45976l6lWi+M3Hl597zj333HvPO/fc5b16D1v2C6QOTrRb1gzvM3Vn4O6cY1ozfKaogznPIfXXiXI0fphzQpsF4ydJ6oucU9psCE+SOv25N2hBeEpRw5GaAyMnsxa4NPe01gqVk+365sLOybKdd+Yu1+bCw4ram9uJ1JOT7VHcBicn26O4Dc5MlhH6AJZrg3cVdRTLtcGXk22PnAc5U+R1+FXueG2+5Z8vIbUARk2xx3Q7lE2xx3Q7VE6xx3Q7NE6xx3Q7tEyxx3Q7fDTFHtMdkD3V7l8HTJtqX+kOmDPVjtcdsGSqPd474Lqpsu8VefO0DogpakJeB1LbFRXKO6cthPsV1Z33J6QOKao/r0VbBE8q6od545E6OVX2gXq7GALTpH/ej1qWwOfTbF9aAnum2a1eAl/KvMD7qHMJ+KZL6gumcqeb5bqRqlR584dq4u/gWkVFkboGtivq+0PnadfCbkXdObQDqScVtXtoLSyDNxX14NAhYhl8oKjnhm7TlkHeDBlt3sK85TBBUVn5tbgXnaGo0vx6pJoUdVn+cm0FtCiqNb8TqYWK6sa862CZom7BvOtgpaRgV/42LQS7FfVkPn2vclKtpH6bny+6oENRb+UPEzpsVtRX+WViJRxW1IiCKrEKXq+1rRuBt2uVJQpbtAj8WVG7CscjpV0pqUcK52nXQ5GiflnYgVTlldJfTmC5NXD0Sttf1sBXKu/lQqJy62SPPipcjpITFCWKliI1Q1ElRZTXqKgJRZ1ItdTZYyUKfXUyJs8v6ta6YX2dHZPjcLLOjslxqLzKjslxqFeUXjQL1kJEURuYuusqGQvuLLpBWwvPKmo/UgZ8
*/