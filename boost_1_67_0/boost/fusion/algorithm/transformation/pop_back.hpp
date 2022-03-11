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
Kx3fs7GpdbqMHWUGgOyVjVuS/023JNa2A2ew1WlGfaarU2t2CbMLRy0jQrdtItwtbSg5Tg54V8qmvfiyk794tBeKJWDvAM3B3Pqo/hgvuGsAXNjZClzs3wlfJeq/iL5VA+yB/CJtwKp0ng6JhCjm6/o6q+m2v1czN9cAnDEoG7eH2X8n9T/KHupwa5ktm4jKzPI4hQfzgUqrSWL9nFfveyDgDumz7zOUoMbM+q941s9BJhPslt1rgh3da55Zx8QXl1KrZJnf2CTx9f5/YraRIs56ijmqwUhqT4TdVzFAUzPjmyUslEkEhosd5WHdYYLanHvNzv4RXt/hMWr2JJov9Vy6s0eYEWjGRZAYavIvTAzlb3Wri0yIrzWujzzihejWfRndsopDodEdy+wUe4cgVLBH1rGJ71H6tP9k6G7hg6mkS3/o52bDiastj7xsc7/VZXNfk7S5d9OzjX7O6WE7gqyRf/asMf8co+17nWGj23/h+USEvNOxDmexsbteS11iLymutJeUPZDZR51BoYT4blrpSHsigI6AMbOukcH8lw0+Tuf8FhYVht7tSPtVEOEvrI1EE5p51ag2A82pvjo+eiJyL6TR90aTqdRkRwxS/ePfSIz1v2ArrQBGXeEW3wIKDoFEft1k+EoA/dpIfQVw7wpJGKfrgDxM9jAbPQzR5WIedXKwXB5JXwvPu09BLqOta11Mn4IaPFo4jBujGIZD4HDtCMeasAbRqgX+Q20TasWhcJq3zaVoSu1/TxTl0EuDeNYnycdi8RSTZNsLd8SXsINNz23ZordwC11H2f1eja9eXOfYNVwI57B5tyFAydmd/a3pPPYe/yttbtg7ix2F2wsHxJuGFmaDeIJJuLuwvllMU35e+Hd2ucX+++qFxfTqR7V2DU5KeLL9dLi0uQpfs4Nlz8qfuEJR5S727/EcukqNHk24zrEf8r8K3hAQUgxxZMdpg1Y0PZgD8pFS/IeYqBwntbS89H2LFbkJvhrE7GLJkveGVm3JZ884+yLSm88+0HWGsLVYeXJLIc0bEdjMJ0S0sFL6JslyxHYvS7+VSSIYb1RDPUFwNXvYMdwjRAyPcBCerjKOGI+4h4+LcSHqyaxQs5VAfqcUPlb1nELfpVbp+LVFuoHuPKh0/DtChJaDygGrbVUrs/LV3BuYAGVVnabHwOQsboKSRrO1186smFufkHK52DhpbwOFH6InLdHYN9mlvf6UqUCmTpUVzIjo3/u15EzfcL2hLRKJz3fFb3b2ZkPbiY5bFvDE7YaePWW6wdCkgQZJmtvuAQG9Cq4lDqWm/A1Y+khmaERR4dC6jiMYYU5vhcNpOSkQYqZ9eOeRKGIgcn0RMWzUl5KKS9DvFQsci+POdITGkahIhH98UMKC+MAagFp0MWJluXxBMOR/iaFGakRFgIldp+ExS1Q6Ex5fCFz9O5Gj0imq3HQ9Dpqey/JNl3awQaAFdYREt+kC1+VLVHqC8I7YAoy22Tfa4H3VxxYQt7SDKzz+OZ7YBOgpTBYV0/1zpqtzS7oWrdqMDD3S5sAhlfnef5x6cUuB6PA5Kc1+xH4kEmBemj7hPxi8ckcKykkwXtDe0/TA+jub0XDJEYKjlVHWtEG4e3XGzFhZorxMnSacwQDU5/WHviO1RpNSWOIW5fXN9gDh9zukAJsoiklWVulh7UuanUCB6SsuBFHOdHR3gdN0Ride0QE6rJbHkoZbnrsIVX+eIFg8/LhZj+oz3S/5mouNifbhUt4CarQlRCcSXDJ2Ps56WQgNwGod+me/5L2xEr636dJQqz/3XVSu22B21AM4XrX5aZ7SSqe2wuNsz3kOjscHp4rS6VAXGQf06yjpH8xiDRA5HlHqMUKRJe73gcEaCop5cDsMCXWt/qdfmVPRAWf43Px9RvOXf5cVF0SP2e5YfxvsZ6MgKvaXpGa2lSUqytSJYkY0oJ/7bSlv/GfDIUdxwmUPJhwXBcK1o4WLLggXPfqqs8zwvzHFcPgEYHn+UqNvsQns8SqibwE1s7/ZykK0nyK5Z7Hpi+Hr7VdWUXOzA8v5nrhTRLyIjzE/L15Fz/nxgItXRM2O6q6Mnfy/wQemAyJtiyciB3pqfJD238waXayhoP7ryVWr14pWtBpiPHMMHoBmiIki4pLKzqBeCJY2/hL07DCVKKwA8NX7k8snFfbFFePCKoXYJf1xJTHHar4afTYE3GZ/nmLlOJbYqZ6TUVVsgiHFk8WEIqLprnjQlaJfAvRoMXOVOxVwDX2d7+ywuRn31AUDug2E4a1Oveh4KtVbyYo3A3AKKCpdWo6VgSKgH8RCK+CcIWDisNadG486BroQUgjG5RYqCPpq4A/W9Lgr3f4yX5Nyx0+tnAxEPLCOI5S75CzpD/5CevTUulMzT49N0TZtY806F+XGKTPwT9JwTbXHZidu9UX0hsd492u3FSOCSn5svJiDeLANhd3srbABKsL5IWzsJTJCH0Fo08+Z5ewORvVrjrOchGrHbhywy9qbLOo3ZI/jlW7YNk/X3itdtRV3/uRH2RjlG5R7DW0cX+kRVpH6UutyxisdA93Y01GeJGDMkN6HmcyhUbvO7NfeHdaSufEFjoGfSkajquk2dQH700KwtSOVVVa15R+NxkBVNHCMq5jH1UKz9tZjoFsXPkpUTAmtG5070E5A+QpZPinLg+oCfssPivl1oaD+Xzx8N13r3XrpUV5rmPOLchfsdEXUETc3hoSkTa/Z3O/Qz4zt8mcz/fQS4EzbLn+K6DmLfnLoedR5etEpztOpxi6fKJSvOE63idVQ/5Q+gl4GJMRfBnqke95jrDXF97ycR/AdGRePcffyNfGB05Ko8AX0aY9YTMSTJYgIccrWO7t6V2+TV1dL7+qdxtPoLnT8jG4Q/H4HaL5eLshEkfeREQxl6jsFTW0TpeNRKc1D18IjXVM64A6OcIqWSrW0U1+MzXE7ZfcAACz/09OA2m/S36PzZuYVbd5ExBfSF/8Mategl2ZeQfQNGm69vNkS1rdJvZVYabqNkemfDARgEkVyL9K6z8xu2TI6FOLoSI3btp0KPz41gh+VjpSMajZmupWOD+WYkAXauTL+jTrBEDTJ6vVcnKOVxuT+2SbjJhU+zJq0PKux8awgYGC2BTBOiTanQvG7d/L6YKXQfb32EZPYVPRnoAnUmy6Uns/CR4xQSPMN9AiOhNaVoqTcR/jVHdJv+Zl0Wk4NcfAULZmiff3Fz0DeOXJjIChtpkn4qbH2yfMFPWdT5e2UsDkmvqTGwE9XVYRlkP3Po07e9DNDlWSk/z6j/9/7mfRWXOsu6ersVx7pIixzXtK+FWjDv7U1GxeywWwOEbzV36fczQqYCOhg551ER/r7Of4krNZwx2m9+Xn2F7JnTc6arbv1J6yxs8TWp6y731nTd2TXN5TcvrsUjbdGSr0S7py0Hiu8RRyHLaW7ZYI26NS6+VnrtRq6rYQSPew763eZ4Oay6E4Gh1OGN90mT+IRySnUopt+IQ82R6BpGwuo8eudNTC/eLHf7m7UZvlgGaHmJa62NGozitTxUEbRZlhifx90NkI0ZryLPnVaozYTGZL0YaaRAUdC0tZ0CBeWAmi24eQI6BMeZsVn9KBkm75gPWS9T1jGEGDmemP1sOlLuogk9r+FMNOwICsaFeQBvjfp8hdr7kXYaMDwBEiU9/vfUuc2eyIJ6TM9oL//EB9fLcFwr/wESXivdDzuFRj30ywbaPfKTleF9S8ehF69Mcd5wDg+do9I/aiZGXMpHV84eG8aMan+Eg3r97Qwj6zMt1BVZD3Xgj22+UF4mJdql+HU3gBUHveKS0FCmUqVNSH6AmdmdHe1Qou51Ys7bpXS+Z40KiZ47OyQIskAHC7e5qDzja78OM0CdFxVQbEhIKView21xZN4FwvAu1jgQtr5SMtH2plImyraXcEonWl5+qwwH+8D+9Bau9v4eoHxla8cX1F9FNVHufpzkHYG0qYgzY3qQ0GDORIYXI6KM97/WWvNs8Rqv7Lf4MksYBFlPtLORNpUpE0S5V7UZTJ9Bj38wTXywS7K88Q8byBozLQPM90Kgu9MSE8LZcSwssKkvcxXbXrXPSrKPZ1dsYspJcA+7pOF3bc5II8UqrTVFXsLd9EabKc12Go66kUwniijGeOWSoBAB+MUIvtNBVOYQErOI1ZYzeZxn8YMfWaApG+ppjku85dywV8CT2wQAWlwqXWVdEHC69a7HjQwrdRzZafEtBdKZXBWePBjbVbeNSW7n22AneUQPEPX+JZyZ/bSWcf2f52PGRFrjJBtCIACe3Vo9ywlkOxM0YcVVD/CrKygNuoYvd59I4rNZuj2hlP76Gxs9zXb+ClLPaN5Ij01u3BQ71Oe5BjX2c3nNp8/CCeNLl1pkQ7/pVyDGgqMcmoNWw/oyLrYGfXDHH4aarIF8YfZSbWuXMaasvmGpmzX7RbWETV8lxuLUEwr04TLgxWRfMoYPRcvO4MZcVLZsoDGd2EN45Wi4CCcldbD6Eq6xC0KBVI1viJjnmItEPlKZIyK6pS1iIEz+IP/8xyMv529C5iiHS9DqjgUKtktevQ/XI5954Fk5/0f8R18Id2dzmfCdgSsJEgxymn6LegKPXI/U+WlVnUh/akh4pwyFacz/ZlVl6bdPwrFaa35FvVsylck6yxIZ+ezV//ovpOzXxYWh2UBQp62kiNGMfkiC2/lwr+/LyNed57UZpeP28b6u8yDPYRK8HpQRtxyc3iljtXpYGhK51ZplP2EI1b+G8sqQr9XwIpdncGmwDaV0IhdLaTJb8kiLNF2rjbsVvO04Xz1dG24WJ2sDZeqE1ghx6qWaMMO9duZ4TFYzYDla7gwzAoEIyH9X46algh51GM6rov9b8au1x8b5sPmTXV2s6eW2U76bfdZ5CqGIRTmY6bM5xt1xuTJefmC5+WBe+WkmnUb54z/c6XjSkhwOGs22xs0FcCuNnQvm/9+qXScw9fGAkiueitdVkv839yNIuJpjEcnsluMQCSsn4h9mYI9BqZR/aasbTKVq6Vzqehe7KfaDNzkNbz7VhQkFhQE45X5IlLA/C1BWQft8X/LB3sulh3RZ0EkWUF3PSfI/gUOEfEqT0bckXjUo7+HHrIJtKH0HhW6qHBiXmswrzUcDYrllthLwRDgeD21WxvRf3evZAGijf33meO/hI0nQvdIJhRvgGq2aD3VBriMdeJrKXPJwZlLfFXqjP8ZRq+C0E4fd4+EUXMtJJNIPp+s/1vSD/LE/9dIlFa4yAjHVRyXobFmsE95wqLQusMtQ+m418b0gv8oXVXwWEngq3SGbXAosApADSUZrX26Tem4gtMByjK4MIGzdCIMkB5HIK3cfSa/uZWOyfyQr3SM44dipcPCD6VKx5DVOKyZh0aNfQDFMdU3Sz+dmd5EMh8aIZnzJEev2NAqoCVqmk5g23SXZQT4Xl8HfnVJF6wGVYBftgS/CoBfBYFflMAvMlFrJ/ALEUXUvtygiLxqoaztfkMX8sl10rvH6MMx3wDABQUJgrz4/HxRCQ3OqJ67ngGwIl9rB3BE9RewVgvc8flOWGNEHKKSALDSHY1XePR/Wm8wK1Blkel5lkZURmNuwI1FSs2csIut8dVxD/Njl0g1Iwy9SrAxmJjnCSEyOy4MHE0UjrmpAMdJTcFrN243+EJINt9ielplLSSPEWzTF4zqe9dhZWXHbdRxORU7GFO33M1Q7WWorvHlNVtCY6CaM7/Omdvv5lkrQJu8eaCpAxUnw+18eilFrZdomCBRjvTjpm7TYvziWCpVstu/88yuof0ZiFjKBtK4ONqkMrLqYi1Eugml4m0EXb9hcvysZ+lr01qBCNl7mh7D33g2PT3FTxUOetwsH530+Bf56KLHv8lHNz0Oy0cvPbrW8mNeao92BcGP53r1O7CXhi8Pp0U9T2tzWdSztDY3HcbS9wzRTBO0tjyLmiNvQD2iIt8YfrMPiOpYgtFpzynsv05I+y+YbHf20/th+T7aXp7SSwElE3ut6RsqPgYChYGqxFXWTDcQ2jsn4lYzx1j5UCwnMffE9d1uC3jJ3s6DUaWDGV0t9ELIAC6FDBuA8YtNKZEbAe/otkPdOyN+mZjrilc6XmZl/phl0eIbEnOsyHNk7gV8IVTHdXa1hP1z3a3zRbDa390S8c+paQ0SCRusE9O7O48kHN1s+vQdUeqwz2lIuJ4BSBJpzHE/UI3qEWFXKFHn8+rl50sw1DY7ZGuG8MhtKTlCHxIVVvqG18WmMMmI4QtTCv5CawHrBU9TAa1q800BfbcgBFHhSzt/6xmbHwbyp8nstwb0XwrTED4jN8Ej3EHFshKVhxf3ROlfoiId8rKizt+rTuUKmh7le96bVEe8bWG8rU5UNIwkPs6JXZxYH29roJ5Sojvd0wJO8Yls+qqkOzQZX68wAC29vtgRamlEVtzNbuYDAT17rWFgd35zVtSMMUVwJGejqZd3b3INgHNRj9iyaKS+5iLA7VXUlsw6AHTb1GzVr1/LHJxspYPj6FQ6CPuJSpfoK1zgYCmtvbDSYe/Cf+p5suxnFsn8yUdvpsavqhPZohQ44ge0C9mkv6QfpDyBMDtuSRIIo7zoi8/3qB66IFhK6YLwd+XJpL/vlmyRHLTRcLtos9ImVS+VjVitspHZQjbSgEYaaKyTxcSgfulacxW1vlQPoYRRi4n9mC2qFnb2U7/UPFkh3PcHA/piwZIyn5gYn1M3eBY9TpPpU1ll2LYGzfVexdcOVFKPShrMSs6UlZyRUUlDZiXnciUvxWUlDbISrQuwtFKqz3nExLSMI1llCHN6tgEVKR1ZYGkQIoo5qen5+fGqaq0i30rYBzNQwygKZJOY7xBThWOV/6qq1olifoGggylbuNbEq6o4j4cIKnvEKdgHYs36L/zBAGSLBfYKpyxatuqL+FUBMd/HDtWcccdWynh1vYj4RIUrXr3ToVW4nVqFj5p2o+mFgg7AbMQKtVbV86wQBWjfNTOSt/xKosl47PatTYhxGZ+fR/NFc3Qkzoc/L9fqNZnLZS5nVUOcehOoT35ki0cKeiucI7uS2oU4E10A/77CjXnIXGP/rtZzI2Kp0760ICpWOOKejSLgtAcKxFJHvPrHDq3UaVucAf4SXwJJuiOsNeGNihn+2x2tXiPGqn77CcmQbbIP0/eWT/y3u1qD/jdFz/LLEX9VVDmFmxq9QCxy2hcViJsd8ZqfQbXfHikQixzAvvHq+2jenDa45dS63P5Xlm3VzzdqnYxaXS1PsoeHGWmj5p5R+jF0H9kvb/ZhGbQDOmb3gLr6Vr6hRRROvS519qGqJUFuLrNio/r9qyVuADI2WLFSrSASpVKEcs6S+aG0FtGXrB5l+VzVo12Rr3R6GP4cVqUzF80uciZuzk++77C/mQgf8n+0vDxR7jHmSzhnVh2KnS+qhv1VTvUbsurruOpJY6ueWTXc/hbNSKLqY//WZa8kWnx5RB4W6U2m7eaf4LB+kLkANT7v8isTV1tEuSMRc/sPL58s/ZfOrHDEcrQt9GXZZyzvjeAmNEP3nZD+dlzwfnO5/7D472WbQTfJDkEGENJXdjI9WqR/eJz1n6EYU2ecqWYfQenLMohkEdSrO03tB6TKlCAP75LOMcMz1q8I0DWdjmAxrHTAWxaW6XZgZGrbpd9+TELCD8JiscO/2NVaAZme4u9rLWC7eToU7Z+i53HXnww9R699F7oVL7vHodGQbSwM2mMIDvLs+6mWluf548TjzKBwx2vl/rmeTlFtc1GP5Hbz40n336rOA7UQdLRYpTIjCO1AYnlVxOAt1TO+ip0mDutvD6fNVG8wJ8s/MXYm+ugPV9MeRzTwuYHYODCU/NfUqLtokT3UNZ+uHTUWeZrhaM8PP3S6kugHFM2t9ustU/w31bS6xTV14vXCncIDn1syoADrS45kCNeJ1wr7RM1Whz3cQGfGbvbLojbBwx6sOYXNf6jd6e9tGec/1FLlX+ZonSu+5/AfbUXY50NtNrHFn2wtRuxSKlFkP0FPBXHHywLexgg87MALBfHqpzDbRTazVq3bqRHasMUe4/GEjXWcB/+XS3z5ytrLaIo56S4aKs3WH4cYynwSaF7DJevQc2ewr5rA4cf1x7S0SIIn04Sl0RpApv3ouLGS92xrRbW1ogbiM8iKGkSk2h+paa0Ji4pq/86WSXhxiUV1HC/H9SpNUz99noLPbvFG4X4iZ0TZfoe9ooFP3X510qCd9pt1Bp3UWpeDiMLPtG4rZW/5w/XWtiprW2AQZsPTx5Jd19+RJrvGUFjQD5HIPkMBwLzPutL2rK5ExeG08AraN21wB+c/1roYIxmmkbQZI9lR2JdIj8QYoBxJwrEfoxDTIMEQ18IWwiO88WlioSN+LbsGjSPQtEfrtXLd8SpHy8/R1jyX6C6sqC7cGp9fbe/jscXn12QMr2XVVw3v+6vSw8uQhYyVv2kfN3XuVr9LJS+JROXqf0p7wnn4cRMYjtHjMD8S8NB3Y7K0zU0SJPDwFfI8EcujGWzN0/pThduffT3kGBh6N/mRcuPux4gsSjw9FX9WncDvlsky+QNOrl+eStk/hdE7EdpSIualjAXn0f3grFUnAhX0d8qqEytuZOnfiKKC17joNVtDUlQvrdebV4LV4IyyNI62axWLRr4/Xqqv+OlGyCK8WhfbCdWFpK5Z6BJsCLAnEfKwRuzTdwKHHwLLJqjX3SGZI2NNMrSPA6w/SkiL0GwDEFe9nd3jdiy0S5E9kFi1ne8XTf7PocEbc/r7lA4oJhDJ3CrmVkmPM9SN9WLLQ3TtPFZ47FkaZftDQ6mZ9LVt0q4Tu75Us2mG3h4sf4mDmeI8bYov8S1RZ4m5AaMQSu8veaPwDaP0cf9wRtl3B7NeMhwCN5ilaaO1EbYzyydPLj9119FdLT6Vauin1q+m+VS5A/1xGok6m5UESmu+dgVOswIUR09EuEp5cm+i7KLUQ0NfEvZQ2exobjVCx5fNoI8pEQ5QDnhwMnKxIdLcmpEcCTAaIBbLIGcP612fjhwPdCIGegjQfQTU0/XVhw3kD8VacT3wboN/cQ38tyoJtslTfarYozxZ41uaqL4kBVaW4a88+dDQCSMk4VI7XmZKsWS+kpjCDKdq/35Ca4uB1qJ14lVgu61ssz1ycqQz7KFzpbJOqDsd9luB944=
*/