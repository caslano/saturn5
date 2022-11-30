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
xojn8KOhr6f5wD19NUB8H4awA/eWnM+aHFbvWfVgrYh4SnI7kAAALP/TeD4oA8KF9iTLm2l9z6cPSdygS2CL5bEE7802aR8KRVQJ8IDWa9zv9cer2plJ3yfW9oofSfeP5eFlNg506FM9hCKFq2c48H7lTOoQmKwHRLYzdW1rRGNSuj035Q4Xknw9JDyby+TfAi9DxvqAhvybW9e0vUSNom20BdsMGWap8Lt6uS732EdnZap+J7uUIwNGFhWQfwuqd6zUVzmaYV4YV2tdUBWhDK7ncVzqz28P3NZd4HOyWPSCRewGHmE3sLxI8PiUAIJs83NCBdlhwa4VQ9J4/JIohTjCoFg7cOZkCYzsO4Qfw1tUmxjRS+GN3mvGwu+R/WcEebeW24viXNj59KqNJt/oXWWh7Uh7D6Bd6pFoHEZ7uNE8gcIHRke21Uh4A3W15Gy+dv5mlVZPM4Yej7C4PIYG5JznWUXdnWFdRHeL7+V3SxA9Bo8GA0Y1E7GxmY9Z2iH987CFx1j8G2CiGcBhW6Vo29l+0z8uOdov0cxKb2L8yGUKd2q4mknXU6zwcE9jTFMH1ii956aEBh8kodH6G9gc3XF312fhzWuCfzwTZQIc78hnb1Ch9PV20f54IqmzdnSOhg4b+Dkw6bG+AhJKjoG2UeG33Kkg6Vzv3BWC5JLlDWSurMVBptjS9dEIjNSRBWxq4xHWdXRjJTFHnyR33G4f5GCrgSJcG5YF6uufbI9xTJIY7yB+4OyQ+1R1uxX+PWwCVq7hZjP4w5Kj6ruMs3AmcE4iVww8juXSqQdoXBGp+7yyyE7ElVev26HxYivJQxzEEUPey9i6+KbmB1Elo9QYYBFkdHrtZ2wLlCdf5hUtEw8ZR0ldB+H3888KsG+numYCrG5grb6UwEdVZf2f8o4kOh3xm805dwVeggMfICGWJEYBmFWMj70xmUDIC8furKCqT2S5Lin7zHEm1aupvxdTit3EUaaCF5PmDvRJJsM96eJkqBVGo/+X1z5hMAtkq4DqX74rwVSGcZ/qGQCuPHy7LtIYno8x6751lykAaLPd2EYlLz5OMcle7por6YqovhEzGnA6Al10Am8B33f/DPbsnD9bJoBbAkZuVs0o+UJbTI9tCCdjxEvWT4yRIog2S8f0blCdp1Q9g3kObn/cFiTMatU4z8VX1WPMAkZrHd8YTrZFOT6ZTf4anrktXgWlGtx405sitC5CtnRZN5YMqNwRHwqGrk/dmjAFwXY9xv2Lm27ALa3Fkvz76SA1bCxp8H6XfcsZhDEq4jFlwQkZqVYZ1vzAuWSz8DrdYn4GQeo4m0VkljK3fMu2YVPOw9M4TW+InfXv3GivmDmHyQkEzT5eLd8lIdK1G3i6Nd06s90++LQOWeSWAWqLDr11jmuh6FzQtKhzLEsadwNSRUB72H7SBQ3hn8V0bhQMw4sqa+utFQM8JsjQLKJnapREb2c1FZXJhqDU81hEtXKHlF4H/wiP9ma078pYLtWxHCsY4RZGB+12yBTtMusxvbeOzSleJeIQje10gdIKKq1dYJzZTdZc/Wnyd75Rr8oIDU9IWdyEhlSsSYMApnbOeSRsjN8yxCm/XSbr+niJWJuYx8pa6yd8qnYeUInj4wKCVV0AJc0XIoL9btBK/h6PifJQihQai+TMglFL+FJWok+qfsJ9YT3113YaU8Cm+gv4TslraDks1YEHRzahN590RZiosb+jtfj6faU5iB16v6JTKbA7PvH047kqTYhGJHgUPUuad9EcIMOmdz1z12kGLWa8X0lwQwtj+4aZ1qZXkDTqbm/VnekM6dO0xhYrmOp4Qq6fxQYFo6DMszLIMQsZOfkDHCFuiKpucbLtsiTRjQbsMASmUsQ/Q2EVBNTFyIVwMADykGtHYNuFi5WgW5T4wNIJsZzhkExsR8CQjXrpGU5tQxJUulcFiVUdZiHPeMCFW3C9A/JX4V7k58VIz5NurYSWxVM23nkzZRSvIvZHKux/8hKLkoUdZDVmFzDuxfMB3lBMD64n7gVNPybzE3AKyO1ERud7gXuqnjYeqwM9eTQKbZ0+Lh1XApk3biGh7JC8lLfJL7QsNFAamotdEzUAYOwtgrzCqN1fhvvvvC0a8li3Y1/oojU2vArMtDNt6tqSaAKj0j/c04umj3oOdPNxzLk4ABiC4eT736vbkeMdvnG8zyOex6sLZNuv6LoQjq1QMX3FnloP+wUsFM/zFB8Iem6KfK5RLB9372uJ7/FvvTdi7URVDY2ePQwUzxAvALCJV5SRTrCz4/qj+zU5iSWoXffgm1jQAUudF4hlBsNpBl0mnqGpAFzNfZLBENTE4ZJdHaDvWMYIVFZfML2cOVbdgNiW/hgy669Qr8ur4Wp+MjTgvYPKdN0VEl2AXZYCBSn8Gs74vZtTt0uZE7aTGDEfzfc+ousRuoP2vYI+l+B0QHGR0x5gYuh1Pj1eCkdwYSbO5XQAfkP1qqMlfqu5JwjH4sRQR7j1BO/d7QeA0b1AR7TmSp7KaI6QtEzD7+XUEMRnxFEt+DgnuYDxDrmn+jhZnnck4Oi0i7eObVKNSdIXa/mr1CSzQCZSPtOBZbxKgjRPHYgON5cOsDX1ekeIqw4T5gzWdbco2JMvdl8cI39zWoVmySGe4XbQu+rTFk2HiknNocnBx6541zDJqMPqjliGWBVmKfOH5IJc3kYVsQlLZbI4iDGg8TsrtWjsTDEgRr3PR1biNSzl3NoXmwQ1V6bWj3RQtDpLdMTSqdWGO4TTEb+g4d38+etewllRFlSzpUiyz4sY3ommdRAHZY/CyAAQ1m3bnTVJqCNd3nxgdpyCAViLRIjuc2zMgPyDrq0HHhodwrMgnGBrpHUsDO/dsEg8KGZcVf0WTU/w53Sb8jRxZMG+IpKqn6aim5qLHB1MyBrIKYim+OeWJ/BfAEMXdrvxdcYXUu0h6eWSgJKQAnMMu+RYOtQXDcIHDEs7J620UeAk24uVA/54faTPnLJfqxyEM01NRYglhyOuW9dJlWrPgOoUmsHrlSevWh4/Mab9TTVRDwcmdZQMN3VLhXNQyRovUVA4NiT+V606k1MFnVHVRtpJCUcEJ4h5eLR4nhrnRp3oQzagH+ZjIAWfvaY4uvBijSNBkf1ejGAaiePuqY90bLFgdf88qDuxSZ2dtvD8wVyAE0/Hk3juLzkLTqIjFWmTjGJfIC6AUnTN0J3TZl0LnlHYcAHQSGDn1IAiELdMmbvAT1dC9m/eAwe3X3ad5KGzRfg4XdpenkPt2EvYSxy0090dgXUSPCdnh5mHIH7HER6X5segywIXk/HpxAz0uuIKQAqshsQmVrpRhuic80raaq1mQi5Wq/jhOY30Bheg9KyiiefHIiI1bfcnvNduZnPRce2+2iiHKrP7CZujqVxZzLxIZhZc/a0UetfGGbWJmfMYUvCiXOjxawg3RkcH2G6TmlYhpVftcv+m+nnODNrhRZER0pUSo74gIPsC/02knjrmfQrOsDDCxBCYpXTNa3J0DDqTyPbMGEak1YDnBBGALb7vHl599zpk7mySxZtdZFHgQBnKqRz5H2alLy3I3H4YeaTFxZpME6Kl5AFCQKTGeEkrQ8M3T0AJnPqWBfC1/14d/tDsjmoRQNR5dggeHd03FTTBxtDiA/VHYIfNws6+c3qWgftBcAsO6ozi1DLl96M5mTRCqOLqo5SBL4AQ9E3kBhRg8a2Ufektwm6thArz7prKfFUqJ8TnESgz3fUgNrxfDgFwkGQl8y0oIP4SvxvD5WNbfjRdzbP1wPfcBJvVsVYThOIb9pXVo13ByGn/Y9+g4y35pCdPpndcHhJJ1rRStwq2wE0GucCfui4kbRSgDo3x6OdwH6BDUQjBUKkK97W+IsPIJ4YE9RuWOJAB4dkl5CUKNr9BA08djz9qdclU05lhtnDiAxp27B72//oLwSAWKApd7KKfJPzNCn+reoBqdHFX+GlyTljEKQpcHckf/6ppSze3N9Rj1O3OzLQ1iJrRwgyctPBFb+ODzuMEfTw5IjqEzeJ5D9xlCR3s/M2nfFMyucUXhVlptdSFCkDLck/CrWVbDQtONUk8D0QifliLmrf1Qcd3WEAjWfmZA/BXZpdc6DApJdAL6XDjN3lp0DO7RwSV3It+EwPBF3m1YaOWI0BuUqvzylimQ6GYONMRt2zGKw3ErVO8enHwKDdFQ4muTEq3CtiX4ie92ClFUaImkT65piFV8Q/8+obHm4PaQE/47nYBTWZetEvY+vtX48/aDwDEUOJxhxIjkS930mYtGbT+qPQH9o00JbczpMVAWOFaBkTg2pPrVxJmujHiWqFHNzxW/kcfL8FIpypUsyywteMka5u5O21JqZ9I028zrwIMvgOH8NkSgrbvrJRyHutw8tF3I/HI/cWGoW3YSJFgncopHXylBlD07Ng4L/XbzzJpGMt33Imq2xHWkgLqnzyDE+8Jt3TVeCB8KEah2UPYhIKJ9esRbCjXpJbPeQPXmMMVbCS8zwqe/ohvWEOt4NuPIMJJDgrOq4/ax0uX+kXElFFZimwMSKvYN9Op8lrjIcqWfYCk6HZ5AzovJTLdniae+N0UrrvZUwsAdpE+tl4btiGaVSBuXcFp2CWOUvNj3bYMFKxN1kbWGTtpLAOOZ61xJELpIDnjdTGQIdR4GIh9EEreU4fQ6GHNzPa8dOdkJw3zScJPvJG3ZQyig3YNz7iR+yB+AQ6DAds67H15UL6Fpj5ndi1UeDzKa2yQ8Ry8Lzg9GL2FYyrkMdhKDlJTKZq3T2UNxtWMgtw5P5Y0jUoc1tXnn0tzwepEJQTRmKGDsMiL8WU4kEZjm4MSlmvRdJqLhvB1ZxTsaHHreETDWLyjufWhGviXQ4Kr+iBxywF/hLYWP2dmL7aMsCceppljn3ZHQyFYrM0vnRdWebLCloRGS/g8Wa1RmJwfwKDPaYQ1lDS7oWQ6v00MQNJ/wa++B66c92F+BhPf01lMIWYymarUwZ7vUM78xz3rdDvfta4hrauB9hlJNWBZHVIeR2BFYryAD6o9yGwxhtpD/k9HnC3dfyzMGM+GzCQhgQc9olKRxVQDbhRwCIWN77OE/exn7Od12jiVAJkIOk3MwVQnTyqEj1rhT4FaQJJESA5KOJgxmLKdo9oeSER/NJPbQN+r1d78ZgnXnP8o9PBkO7OJRPWDQdES/HHUiMuLxJfFNdDEMv7HoNcywyWohRZfk7m+MG2oGVMf3T13MwS2wak9m1P5gJvRuMotbLJ+zqpVhPO4OJSM3fD+dIIHI3RDW8eWLR/f7qZcbzeVWnbjHvSR6QWxH7vTADBAyFtZzWwbGWnF7VPSN6R3Vk+Hjarc/Nf61eAoMdBKG9TfqIUFIlTLt4l6ZhEaD7AhG6tmiEnv30VDyPNWVcMVH0JYjTCMCY5VnzHOBw91tZNheyn5/BAJ7z7iur/fN2sO6FAM2OFY5yhnE947Hiui+zyhEQyZADJuJ0YW5y1DqAy17xKkbHS3fGpClcEcW/k9cle22ppt0AlFy1wXCKtHPRVBHjQNpokSUyDs3fWFa2GHufJ0roUa2nGP+OhkSVuKriev6Z71oLq1uUh7E8Ypsf0oA8MFLIRL8iJBRc0PhISnJ5El94DRYrUum5tspI9WZ3xB3voySx/29TQh2ZKabKZjsvq3ddbJEiiD5s8ynH1b8PrjGYxziEeSlRLj07eVLma6SrtSvZ7NC9eZQYrM+PxHrQyv8wi2sv/fL26IceyWvamxdZGm0Oeg+tAwRV0q2qvoKPqrREHoM80VM9W08eWjbczOYhBdKkBlzUcf4MbtVCIriQmr1GN5CEkTGLJ5hzV2MgnJLeIjIbUG4ePBqJk9GPc4WRY8eVhFud5PuE2H8K5xyTe0CgZwy9uC8FJOBZ7WOUYfzidyX06wh9itv8DmZhDfSnKsdflUhyQdy6l9uAPN3gdzR7LuncDlnfu5jik92O5xTVY47/dUDvEQ2gOp8DuOhApOWME3cq0UQI+Ti089G5K0/KlqCvvj3EippY2p2hOdhqEtiLeCq6WlVwvDJNdZfuzdbsys4M7hzqemdhhgUaeutgNVY10AM2PMVZtOHc4s47J7VA47fIlLAyL5IhEy7X2xQzocdZFEqC+aIPjzssUc50kXeUZSt0+sDKD46qbNvJ4gDEwa9sINGG6nE8JgqFvcBw6cf4/ZvWXpuRB2k3SLBlmGCEKe8niIZUDrXrfOkcGpVOUO90LzY5hNVMuIdNJh8XdxmQfh9ACgWkRuieaT0vkuXrWfqIveqxRCXiNoPCJE4/dfpOiuUeCJnwM833gZQPQ8OM1mJcSDinAT3A/aiGZi5I0I/vlT9E3mgWNN1CnAn7W5bU0AMkOCyU1HPxkUUIixvsHYnlV+3KEohFyovdcskd+gb908ZfEcnZkF8nkBmf2rglvgLfNKLWfW+4OrZRJyTsfiX0obMUY2aQMEbXTOMGZ9izWeVq5WNr68/SyHqZZ787ddqcht9r106enrqbzNYLhbfL6MfupMjAh6I0KETej9KYQwaiZBG75Wio9p07H+9Yo9VUohawyJxEokHBxKbE83u9Ls+Fang7w7DR4yE2IOzUqJcC5XvjvduFx9y3MLmsF/dhKnPNeujixMONERGBFDlnvEiD3n+7ObCzojefK0/RaDU+x6Pyer2lmoJbdq6SyjmOPf/qpAwysQsAITwbC/WPYxzSpFDjkQ/3Mqy+3ENGKhh4RL/IYQdg9YAtthsyYGRZ/pNSlPEBlw6q3jwg73O+51uSN7rFyxB+QG+NozOPAaiFYKa3MehQBQQAujJ5KDT6+cFARAljjqgM/puo5gxEUiKmK+GrMktc9Qwf2SGDw7p1qtv8wt4uaCUd7V0hRvH4cZz5AEZISjAQ73W9oxK5rGJH7tOfl3qbZUAAFw3r5mDjH6H6A1DEM0wBrntlYg0XLvRzGA3CFhSoRIhLGyrcsK/gv73jafQiFLwKFIGYkNfpykIhjzPT4xTG1V1o5D5aL+095m8cBEKfGFvAgpY6mBP2f0+Dk5ucSw3ytkyexpK4WzEEP991gQHFvv8Ehg4veO1wPyUil/AfQQ1MKg/fsfx2ClF5JMVCsSY2MnLBDj6ej3rNAiQkEHQqcEUrldEmcDoTKVtEJA5l/A66U5vUgKPQg/pYFOrLeVcEJc9Wwv2kX8/1H9xTKm++7bgIW1e5hOxBE9O9He3EJS5mtSMgx8wvWRbR0RNCmFZXpz4EF3NgkhXVsiVXoRyF4zEZ2hu8x7OzpDLBcQm2yIHS+1UspFdeqpi/KrZ8yUkeLcHRitN8gfJooDHIXmoV9ENjiSxJrH+nIoBJ5HLbtdzYCX9c61jTAf/QNPsw1U3q73mInLFiLTB7CWbH6txEOzvsG1tbFGEkm6nrQv/Q09H1mzT04Im6twpY8ArFNktBBZI0HfHc0Kq7gKcSx/7bB4+h29dIY5zF0jLKR8LB/Hki29UkdCCCZ3R7AXvrlY7iOSZkVHHqUuNvFC9tzE1hB161LHIdyX5W+FflDuG/vU1HIY7VT9d5d+A8B8ghFJi3yOjObcmCnyy9AqezAlQ3LqHC5Iz4BrCyLMrdAkjO7noM4CiRggVZ2Rg1EPIxqUusj43TYTKJ+K
*/