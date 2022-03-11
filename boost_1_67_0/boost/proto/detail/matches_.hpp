#if !defined(BOOST_PROTO_DONT_USE_PREPROCESSED_FILES)

    #include <boost/proto/detail/preprocessed/matches_.hpp>

#elif !defined(BOOST_PP_IS_ITERATING)

    #define BOOST_PROTO_MATCHES_N_FUN(Z, N, DATA)                                                   \
        matches_<                                                                                   \
            typename detail::expr_traits<typename Args1::BOOST_PP_CAT(child, N)>::value_type::proto_derived_expr \
          , typename detail::expr_traits<typename Args1::BOOST_PP_CAT(child, N)>::value_type::proto_grammar \
          , typename Args2::BOOST_PP_CAT(child, N)::proto_grammar                                   \
        >

    #define BOOST_PROTO_DEFINE_MATCHES(Z, N, DATA)                                                  \
        matches_<                                                                                   \
            Expr                                                                                    \
          , BasicExpr                                                                               \
          , typename BOOST_PP_CAT(G, N)::proto_grammar                                              \
        >

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 2, line: 0, output: "preprocessed/matches_.hpp")
    #endif

    ///////////////////////////////////////////////////////////////////////////////
    /// \file matches_.hpp
    /// Definitions of matches_ specializations
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(preserve: 1)
    #endif

    #define BOOST_PP_ITERATION_PARAMS_1                                                             \
        (3, (2, BOOST_PP_MAX(BOOST_PROTO_MAX_ARITY, BOOST_PROTO_MAX_LOGICAL_ARITY), <boost/proto/detail/matches_.hpp>))
    #include BOOST_PP_ITERATE()

    #if defined(__WAVE__) && defined(BOOST_PROTO_CREATE_PREPROCESSED_FILES)
        #pragma wave option(output: null)
    #endif

    #undef BOOST_PROTO_DEFINE_MATCHES
    #undef BOOST_PROTO_MATCHES_N_FUN

#else // BOOST_PP_IS_ITERATING

    #define N BOOST_PP_ITERATION()

    #if N <= BOOST_PROTO_MAX_LOGICAL_ARITY

        // handle proto::or_
        template<typename Expr, typename BasicExpr BOOST_PP_ENUM_TRAILING_PARAMS(N, typename G)>
        struct matches_<Expr, BasicExpr, proto::or_<BOOST_PP_ENUM_PARAMS(N, G)> >
          : BOOST_PP_CAT(or_, N)<
                matches_<Expr, BasicExpr, typename G0::proto_grammar>::value,
                Expr, BasicExpr BOOST_PP_ENUM_TRAILING_PARAMS(N, G)
            >
        {};

        // handle proto::and_
        template<typename Expr, typename BasicExpr, BOOST_PP_ENUM_PARAMS(N, typename G)>
        struct matches_<Expr, BasicExpr, proto::and_<BOOST_PP_ENUM_PARAMS(N, G)> >
          : detail::BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_DEFINE_MATCHES(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_DEFINE_MATCHES, ~)
            >
        {};

    #endif

    #if N <= BOOST_PROTO_MAX_ARITY

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N>, proto::basic_expr<Tag, Args2, N> >
          : BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
            >
        {};

        template<typename Expr, typename Tag, typename Args1, typename Args2>
        struct matches_< Expr, proto::basic_expr<Tag, Args1, N>, proto::basic_expr<proto::_, Args2, N> >
          : BOOST_PP_CAT(and_, N)<
                BOOST_PROTO_MATCHES_N_FUN(~, 0, ~)::value,
                BOOST_PP_ENUM_SHIFTED(N, BOOST_PROTO_MATCHES_N_FUN, ~)
            >
        {};

    #endif

    #undef N

#endif

/* matches_.hpp
DWAVE1HSqX/gWUjKodGp9o+riKITv0MnYO65xoLWayEUkN2RS7ub0sPqKhrAnWoa7Fq5rR8VlFIsDu7o0TUtQ4anaNCWtGohXpA1jvKNWA4/kGs955rQN1cs3W8jrzopnevqwCJR/Cg3dL6WolZUgM6oQJGRxTdGgs28Fb2GTJGdVjusgdVJLq/BbyaGEFxcs6HnoYWQzDhzj3ib5SEsTt2zddcuYM3AJdqkiS8S59EZOB/SyHUj+XRnGLPfdSzOh7reG88RlGqYDKZV3n7mO+k/6YD45WGif15ZAqX68RVp59N4nr+Eleo7XK9JlXnYPYwpwLMYnjAhbeBxBfha8dFO4rF5GCCUn/9sD7bCWvH1GwnS+SaWzr+WSSnlMO8LjI4sy4gocjz+zPjMQtnyoQNpj97jeg2zE7hdzqem8e2FvMmxT7A7sMeaN1dOo2aeHSmsna378mLf8vNm6qOdgInqG6mtxkS6OV7p7zfTqvBiRrlIdfFkXWlCu696I3b1qFbMp66JdUqv0rfTcAj1lYEx7mkhQGU0n60TVU9w4HZNbYOn12wkY3zoSyMsn+leBaW+QHqxyi/6pKdOD3Xqk6A7GFe5kyWBKXDdm64MEvsGY9NwhC8EbbPWALxBon6NFFcMRHB1AdHbWHgieylP/qwLgl0XBHuwJRpHe56uLN5MfeK89USthLoGBEdBU3zVJg7sbwQ61sBBpVatHUjce2lHUwa5SpyK7QLexqMFLv6r3EDsLAsu2n01qxACUrnG0+7kPyeTAPfE3WXdrOvzXExdKGmyg+LFQWbGdtD+UCwXLAvIzhGOH9Q7ahnRn8jkFJwZC9butYPVXxymgNIw1UgcRUwVhbfL+CF2wtno/0Lt9f+DvqbiLqCZLtCqfVBuavkuBgCSyqEJGqAN4Vh99uKzmwjtP5luYfY/sysXiBJvgiaBoWDv2gBSKJDpt8S1oySZ5lM5Rt3QS5JhXBZkxEkQdzO1ZirUhQv0ozTCvhgRAyJbSkp0X3oi+bJMJrwYLrhj42JPVNdPUEgisijxxtxZS+HLE8zv7OrkK6sD5GYMxZTEMmi96aHn0X5ThPeTYtmPeDsJqCip6rHFWpuW2NoAdt2GuEL09XIoiObPiXhtNR7bIgCwBThkHahcdIyVWIyhxBqrWbXcgFVtJzKH9qUBBSV2LK7ChRZfjNuLLDXMs3KJw6mT73f8WCfFZxS1gNkxCsGwI8Vyqg/F19XFDh4StLk0jw2a2YvTYAKTUO/+zYzy1byAmncH8Sf5BICbgX83SyCSCAvC11AFyF9CKtoKvBB7A/Uaqg9njcAQ0FvWvMJvFp/nm02hXaC6TdokiJ+0rkA6Cwt97CXAV5rxy1SnqLtFcpOKlxgXtxE/GPF7QGwViZeNBDCjK55c3K37isQfY2EDalaAbsLgFogZkV5djbi48c7r+2iajOs7ClqjxN64xLvfUf4U4ZDQvenEjz1Kb0XFYmd/IkHfAglaLC68ha+Qau3FMIyXSl+hvU74cegIDJDGgebjOGO/W2nGDuRtgtaDu12ZGNm2F9DH5kax7DfH5fsjNG8LSMPtPHqQOTQxnCgCmqJNhjHtXiWlDgfGDeMiHltIQ+Du1KYCxODhw1H+IGUVXw7uvTDiCidcGBmvvgYmq2YVBNeoJfHCyD24Q8AwBweJUbcMkhctnkM2Q44NwGOrWAk3RA6ILzLZOqxP1Jd365rSAtl3r24A3sAvw7FwaBdYPKk1HqtAfQ1hbm6dIwyNz5X7fmzAfnqBp+ECXEhriOOOhsSrVU2MOhviqDMwRArGWf38Oa6bb8EJWuw0yCd5UZ2rrUbdWqFwPwxVM8VYZciEW8mrEUgZZhABVqCvuxkjNJlW+SQeQO7I0ejLrmBL4EJNQ0kub4syUn2DTwgwkOouhBrDSZCiTEqY0wsHx+e0ssQA6+HxOgeCmTEqXQj1E8D0kzP7OAVN0J4imC6iXUc8I/S4JP0LLA7G8liMAZtrAxjiwC9Z2aUowkxysRB3Eb/Wj+iG611zMwKe2Pb0Pa0brV/pCsj5StOsiecUB8Vn1xG972ClYb9eJJb+nLAY09ZU5hTXemabJ/rNRVAajewBaUhFsYjlUJ9a1t0CIoNzqhWABm1VuixlpGt9JVW93AFFgVXMya8CTbpyH4iHIgkQC6XGOxTe7879sWHClTlox9ih8wauaswDUCrGSNDojw8tyzAFLsJhA9QrpBoftuiSLmFGL/lyCqGh0+hjDNFYc39Mpa2CB1r7KuyxBX5DM3HWRBQW++Kz8MvFZ/T/70N/R16foe+ZG7cgjB3/do+x4680+pfG/RsKrdrS9MSiJM0Z99zrE6sGxmEzc74Bm3wLrkT/H3sSdpj46Gb09Uw71SB4sjt8xCsxDa8fZQIotlhxsHLK7AirJggZYshA0/jiz8HAQNddGYGUIpGKvoWwfoiizgRxtDiNiKM+yCF2m2Yw8G+HXPF8CYixjYFfzjjKIWPmixq+8UBIH8Y+1z1FbWg9TJ+hU0nyLlJvi1wSMbGBh4Rle/uA+FFK/5/TvsOpIkt4S+U7P5uplZuhZ9K3jX5UylgCiJ/xqUSwcgu5wZx4H+2A+MP5QK3NPnHvA91662WIBQHvrnWEIfSVwxm//wOOqQ0GJ5WTqvKj9KSj/BOmHwQcwraIE1/g6Cx0RneU/xPLLcR3gfY5wm+hVZCE7gQ2xtwddbzuFY7XC1s0S9W/nQPfYbrHlyTxOxRbtPkZuUX+noLS5BVAeM2EtaP3h05ZlCVoxi7QX1RlcZyyPYfoJGr0a5K+RD8M8izq0UIT5aS7/9ukB0Zr2kRjMIFiqMyBXKYBTrHVedu1MVzAEg4e8UBGn+sIfebkeU5hiAHPUoVvlPDIR9q8pwFX0dxBqBXaCKxvklQFERDjo/TBsCGDDAjBPWKaJo+AHU0+S1wsC83ucHtEIIc6Nsqgzzaz7nCMHGPVYY/4r/HZHbkGTCVs4wvDHQsC/XvPaeVOctM0GpZYJxOXMKu+x+8/9eu9/1RsoIFUbQVvUUSDhZYtoo37J1g+u0DqmmK3FAMXyqk4GnqOw0PPSTo8xLyFQYfzap1hleP5mYkPt1+DiFferHO9xsjS7nqtlMP+gW6Zz9ZHeQVjHlNVZofbiZjmgPhjlDnyBPLZxVgh0M/Yv9kozXQYMVGmUvrOKBt2oSyXx4aZ4Q7mgnM2STqQBRA0i2AT22iLXmTBBVYsq5CMadEmUFF5VJRM65NcUYH+BJLGd/MD1/TZOBKci1Nf2Mu39ojkSh3lVkkoGo7mMiLPYB8NHzN8zRVkuL92hJsx0iympuGCMoQ/fUFRxNPsJ857QQEfdfpHzvWxX7JmIv6I+1aaxVctuMzdppW0y9q0u+aqnqas6lCX2bEWYK6pKFJcvxMEPqHufo6HcPynZ0aObO3vzGqPXmJpj44l9HsQF++r3bXBjHDHvedRS8+BFaOBWd9E+1m+oVYSX9hxLzEd0aOaUZf7rrmBQr+pSJwhwpRIBALb12uBKoavfx7els18hijVssGPRMeFpoq/gcI93wd+5xBt4jXJCMHaE5Uggcdygt71f7Uc5Mh1povRXHquo8dLT77xXE7PDHoMyT/0sVfez7Qz7smNCt1v668M0/r5+8dEufKi4S8pEZTelXyiQNp4vdxkxXrxvUfb5n8KYuoggQmhW7tYZ6FXUMJvSw0whe7qrACuqxMSAh+woEA7JCLKKdrMWWHCWuGBvGzVL2NCVMtfu3UukAWvNSnLd1CN6z4Hw8vSZG2f+OmvUkzVkZWIZwHwRAoP9HetHE9/FXNOdazQn8YKlaXwrXZZiCHVPfO5PKsjcuOiV7p10fDLmIwq3/EWbsuA7JywKsU0z78Mvqiyj8Gl1koTeKueYskJNEnovUx+Ncuv8yOr7qB6fNmVt7lK7AVw8841+kSUWPfoFG0PhNbIgviyQbFiAhfeFB0YKyUwfGax0dDkhd06bqPdEO7WdW+PUi6V2OO+Gvvw2peqMWm6GBfku39ZcWlExg+JJtZCbg6Yg2yAJfc0gkswgl/eEpuWS/7+f1u2Pf6bzgTZNgEmsCZrsBA+Ex2+TgK3iR/T5Jfl8wElU8/yps5sO43Fr1tixLi6gU/J+EhOhhA9WnEzwW9ZtkGuf7j8Bvd6hASnayv4DrB9PUTP6+rieabLBMv/KT8Tz3NUptYJ8l6/hTVhxARHTPkRV7BeF71XsGYln3UFC9wLXK84jUK48JpVOOnDwk5sNS4/spDGnzRXneYzBGLT5hjyvmlf8H6g5djghTFcWfabgmIN3rWW3UqI6RccZdXSV/PugzH82024+yR1Ylk7y3g9zK9FcNkOFsxkjIIhHyrWfeOoLFjuzLG5PLblf144n4FCXDUYh9CpFeFfE2jULyDQUOVguw8Efl7jaW4rJNjAbYh2pvOF9N3ZI6Z38QZYIsrGub9Zfr1bEUGP5mkhWI1Yt2l8FYyV4rrc3Up6LkUvb5Ci42bxmdqjZ1eKaxbyuMdC36VQrSYqxJZBaJGt4lkA67Vo0VehoO1eZWhMeTS2myopFF6ijITBI63KV0Twc6yTlehbwcKDYZKnhynP8Y2uT2GSBJ0L/LS4xtPWXkBw+MhRmFFA76ZOeHGkIWZGTjOBtu6brI5GcNQlxbSBy+MZi87OaJzXaWbjkq3umxGtom7OXcDdNJC1hBzH67VVwllMCIcRK/FQ3q5e3HoQ/lv//rEuz8jPLYhsgJSBdugdFxLzZ5iKgtqwcekghhpHlMQW9h+2dMN61fdQLjyI9KLcPSW9LQPIP3m6F+TnJ/WCfMWa14c5q2NHY9tujtXy+Y7/2+jjP18koo/eo7E/mH/gaOwvY2JHY2zZXx6PXdQMOze9UlUCLhyXvXezNPGXXvExRqptfqwPF/1f78MlP9KHQ6az+sCmoY7EO2F04NYP4YKjgZddsIkvjreowWbCCZAgUVaL6JCUTTFb9vvnZDMrfyzqhn+KBq5q1aoedPrEfKkob4BH589jnQ48D/DgvZOGSUIIKBMJJMPOJALJk/PlyNkrUjOokL/FC7mcCtGCtuxjxn5GSMEo4AlozmxAATWr2gdLlIh2uZ5pp8EIFMi9CcbYxJwuHKOIsmtcJW1lV1E3Pvg3zVehcLyFBbI+Yr9eK2yLWK9VvUIlqtb1DA5PArgVHKHdM2rLp7ep9EYNbf+57O2iimvQ0LvRUEJ3jbj5Xut6jZfvKE3jabVpGk9snlX8E9lsxPSAajcOvPLG6fIY0rtRnP/nxCO89WE+wtsoLt+QcIRXx0d47bZO3fUaTmQd5f3MscJqcqCqbnxoGiuA5GVo2gquDqCGwzqvkFzX7EjhRuMs0SPdKObpsFG+Uex5Grw7F5IbyMq9QytbllW2GAbxRX52pS/CBarBNjHzZj7r+rUWQggxabhWImRV4coHbNqCZVkLFkevD+2REnKbu+uBq7SGqMvdVXZpAi+Vfbozxku9e12vFDs2odqfUSAsC7VpSi3coqaoC6wSmW8UU/+EWyitGwgS3tIfABODvTHglsPg2pYHOvQykTKOktEk/GR8p3HoTFsVDcFsqfSaGfFW87Hsvy/tMg4jtdXISouIhvxcY2ieewrXYGr9A+ZSG3KtrUsJBbgWpwamuhZnKpO1WpBAOUzOySqY69Hy5xA1QGVZjmS9jWXmaWPpTzNNR+uO+IxJbi4wTjbZsXYE9L5WzACxIQvL92mmiJWYFFh4iO5GlZNiiVu/OysxJ79uTiR1ndEI2YL9WVXRCdn7Q8G2JMczVe6DjjWvUE43d9UReQ6lrONScnwR+8Na/0jqSq3GOA8obMD1CqUe1s8KD/Nh70Y+7JXDlbcsK28xjRN8nuYFsvLuUL3bMWa/+zOAFZPiKOezTS5NrD3B7O1aqJsbjGz4z/FouAlS2tTgblXZqyp14hZOXVYM3XKZ3/sJDvOJD10nT+7XuTwVyy2wTeZ5zOXZjdfdmme9y9PG/mE1z1Muz1687pUF6J46MeAEPMPULX9R+zN3Yfoc7QYfza+lMsuzm8bKW2Hx7LV429TBrYMxG57tFKmmEE/YeoaGqhR2/yqWAgf8tigFd9G1xoKiiLdczLuP1qwOaxnUmOAaxaJ5Vke8h+HTJSUfgtPDarBeDTYQ3tV9PvVNWOqtCcM/Su1eUNiHfQyWMRH/WOm+dLG0zo9kYvyTBIneFRHO5BPf/AGs6gqJPrQJ4ucrexDt04vGxczgheGEiC3hvWrlvH6z+GSNdO4AgdP3DOtFCEKDlZs3+y30P+y1bZYaERBGMI6bLDLm91r24LCIUinV/Fawlo0ToGToFUBr3+dsrexFUUwiq2zQ3b0v4NFW7wWxHIENY3U93kXlz+Plx0pmy9PEsKyIl89Gj9VVyBCdbayiC0Q4MSsUHAo4z2b9UZxoRS8RiyhBUW+85ty8+QdSz54oYQOfbBpqBvVNlw6d+EL6ONxeEPc8SgPJM8MuSuJTKbxLY4oM5eKP93bqomaO3DwmV7wAwJlEnx3J7eDTYSG1UVV2KxeGBnGAWEvcgO+NNnoXefd36KVvRyjH/VcQQ6mFIBOGMqGj/BghSdeyDEf5ETNUZ2JOKTJcKY7wW5COsnJKTWAUzbLWHkO6e0526u52R/hp7B8HxB2N7NmTkjldFT3AmXzVaKUZ2+f/wXTfAXh2CzRCZOrulPLaxGOuwEAq//hvWRvnZVw4qJM3LmXPYK1x/r24SVAX03u1l3XozyLOteyko7wHFO5r6G5pIJzqFH+dLhVO2ZziXwFN3lqicS7Sfl8HfF1Yq/2+Fi/roH6rFdaqLL10vQFXb7Qt0/qrU2+t5SZkUKVgH+6gFhdJrTofl07hPnFeltXk2oVdVrkeF1JkD675wfVipaEI7SNsdJilYodZKnbp7yEVa8P9D5T32qVWU1xnaJSU6vuHhWoJA/h8pRWP0izXTeiSPYcj3Wn21nuh9Vsp/jBbapM6K4YZBxIgop+DNpmzdJsy0qnv3IjO1uo7saQMRb9Hm+m9jwEpsRh262Rap0xLeYzULTK13dTafYOuV2x7I1YXGyvK7ijOzT6mnVJfx57sKklX+mv9pKG0JG0fgW6Bj7XxDolcO85runzieJR4iMFari2rKsvTxVZ37yX6MzLFrHl6tFnWSCoRGPastw3HqRw30QxVlgJQbP6BVJ5x3BOEtpMwt+FGco9ln+o5iRQFnJZTwRe0GmwXJ6KnpMZmhqmiLt4DQ0/wvQ/g55R4Uu0gbAGIwZd3SUNYFaI3KVQV4sKQUhMAY/ui4U6/Sbz0Md+pdkrYhrUZvp27PNE+TIKkkpinSZDmFmfz8RUt7US9lvdxT4jJbgOM9PehetWUz8aHDujrFvHKg3hVPLsWWLoJr0+sBUjZtUl2Xns2PuJ4X6pQ2imNDotX9B3AzeG4pG/5pQkKLvnxhmFUGqneoL1Yf5+txLhCOPYpW4L7CLhs6g7hBCP4ABGxgJWJK6kmB27Q75Pa3EF79Gp4eLvO7p6VSsNWlJ5VlGp5l4LUfHt0THFsBwvYE3L013LTs3JTzTPtNJk5sE3DtS5/GO05IE5GOvVi+ttGfw3lW6F/12EITIjQxiFuirYSqzouJoG5LXNcjV3HzWVT3NpWEff0lJg0BFeSwx2MIXNL03/Kl2tzrsG04k64RrS17rNG/w2VQqkXTuxvKp/lLKvTRvrok7ccWAqTt0pzEox6QSwdegvxpsAgffhe3IB9gT8TbSbc236GLYEZhhLE3789o4f29M31PH8uqKYurYTFn6LIq2hFTYoUt6zAscJFMl79r/GcO/uIeyVOJh1Pva29zRJPhELlNcS59bj14ctMX1MrzskLDMpT0lnkiq1yKN4O441lLcCy8XEvAtGTa+WMxQFHnnKuZtau1tc1IPkA+V6fxJcG9JELebERk3gGO9+RGw3+LrIWmjI1HkiQTeLgZcnE7kJXB8yr+GngOz2y1iY/zeJC/sTdN6bWhwUMJcqD4o9vndZFkTduS7mKGJY8q5pnV/Ocal4qgWSNadPuYc6aHNsQkB15aWhMjRlhrVubu6QJCZqRmhQEiScpKCaiqPiqI0Eqx6dlOK4wES31dovZFFl1swXTFTPC1HVDiql0vBkqtJRRa59HnZRGmNoDDrCRuUTtpdj/PsxJzORzNyaaYyq/4ZQO+9PQ6q9J2Y6GXAZSA1YEcVu/ZhWMPTNXJJtDy1wKXNlidtkNxphKeQyXwj0U73zYFRupj32niH6MV5ufHxPCFwFtE+rrlcP3inl7cBukC4jPMKc14g0fbTxi9aJO3Dza9gJuJuT0NZ61rovwa8Ixzs19zsOzO+BAss41aeLSkc6A7Xjy+KXQnW7EQdXxknqfSNkL/5ct7n3KIJciFJvfOU+rIv71uKc+MndAoyBOMFQ5+INWGJcoaYIDkhn3X3rM09TkrTe8KlU17hevTIcHi2atgYJPVImN9Ilb+x5Di9b1+kY7NIHYw6LATW04I77wE9ppTKHKAe4GOGzf6xPOWAifEUnzK987V3YpLUZbtUdwFznaT/69TvOc1NqzPG2h6jNZnpYsmLxMerKzO7QvSVVqs2q1h3BnWfUeJvSaTluoe2KC1bi3Mvk80tNAvAfOA1/C5M+1ETNbwLaoVG+D+BMsd82Do73DZVe7q5SrtLfQLfepwOCCyCM4AhLvXXBGz96vWYgrU73sg9VbGbl/TkTZDrR8ADacde/h6FTN24TLrs8gP2yxtmCYvVt0y0FV2QQD0J5ttFEh46Z4Rn/S3CxPk9lTCz+UGoxAe2HOD5btxYwuQt0EnzdcQPB5Ii8m0wmfPsPSsLbKYc7IBtj9Vt3q/Vb1fpt6v13dMwEBeyby72T+ncK/Ofw7g3+ZPd9zYxLEY5DJs3jMx4Fz6FfsC1sIpNfekmTgjj/26IQ78hwGZrmUFm3NKnzad8EM+voRHGERQyiiQBuNLbJmFUIRr78XWYVG+fT3IF5ftZvyqavsI3F7B43yqXusSbw+zYZkfg+QlronjRt0GMn3ZIxEinQKSeEUQPP6e6G1jIVxG0i23s6/qfyLnhCWCOYlGIlXV+ISdhwH+3G/jjY9Zs4MDMujvXhm/ACLh5m7GMOzG6mXCaPxe/6Mj9XLkPHxqDKenfuwJWYBXqeJE1/MjDUHh7FsgJsJh6s=
*/