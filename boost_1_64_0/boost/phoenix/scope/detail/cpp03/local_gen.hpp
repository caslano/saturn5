#if !BOOST_PHOENIX_IS_ITERATING
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#include <boost/phoenix/support/iterate.hpp>

#define BOOST_PHOENIX_EXTRACT_LOCAL_TYPE(Z, N, D)                               \
    typename proto::detail::uncvref<                                            \
        typename proto::result_of::child_c<                                     \
            BOOST_PP_CAT(A, N)                                                  \
          , 1                                                                   \
        >::type                                                                 \
    >::type
/**/

#define BOOST_PHOENIX_EXTRACT_LOCAL(Z, N, D)                                    \
        proto::child_c<1>(BOOST_PP_CAT(a, N))                                   \
/**/

#define BOOST_PHOENIX_EXTRACT_LOCAL_KEY(Z, N, D)                                \
    typename proto::detail::uncvref<                                            \
        typename proto::result_of::value<                                       \
            typename proto::result_of::child_c<                                 \
                BOOST_PP_CAT(A, N)                                              \
              , 0                                                               \
            >::type                                                             \
        >::type                                                                 \
    >::type
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
    (3, (1, BOOST_PHOENIX_LOCAL_LIMIT,                                          \
    <boost/phoenix/scope/detail/cpp03/local_gen.hpp>))
#include BOOST_PHOENIX_ITERATE()

#else

        template <BOOST_PHOENIX_typename_A>
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
            BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_TYPE, _)>
          , detail::map_local_index_to_tuple<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_KEY, _)>
        >
        BOOST_PHOENIX_SCOPE_ACTOR_GEN_FUNCTION (BOOST_PHOENIX_A_const_ref_a) BOOST_PHOENIX_SCOPE_ACTOR_GEN_CONST
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PHOENIX_ITERATION)<BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_TYPE, _)>
                locals_type;

            locals_type locals = {BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL, _)};

            return
                BOOST_PHOENIX_SCOPE_ACTOR_GEN_NAME<
                    locals_type
                  , detail::map_local_index_to_tuple<
                        BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, BOOST_PHOENIX_EXTRACT_LOCAL_KEY, _)
                    >
                >(locals);
        }

#endif


/* local_gen.hpp
2ZtP7obLrfnkbrh8gMsRzmSSIz3EHcPkRuLO4fJuzsPkU8RsuJxN448W/TqxbqS8lTh7pHyAuHCknFZA6Uf9JW4bIBcXaHrvRu59/i+f0ecxbTScxu0Zt5Xv6VOVnj4z/w3d7vH47tTJzo62xu+lPn3POs99I8meGPFiztQj2c8LN/Xr4Q6P8llW7/Ovnttz+7KGnL5sFdAKbAX2Ax8B3wFHYH8AaAMeASogC4CvBfKAccBgoKfP4El92SjgYkAH2IEcIBnwTorf34sv6ssMwASgCPACdcDNwFpgI7Ad2Ad0AMeBxIv7smHAxYAJyAGuASqABmANsBFoA/YDh4DjgOaSvuxcwAIUAXOAOuBWYD2wBXgJOAh8BLDRCAfIAAzAJOAaoApoAFYD64EHgeeAvcAbwEfAl4Dm0r5sJDAWcAIFQAlQC9wM3A1sAXYDh4AjwHEgeUxflgYYgEnATKACaADWAPcD24F9wHvAd4D2sr5sNGAHioEKYBlwK9AEtACbgG1AG/AqcAQ4CaSMRTyBMYALKAS8wGKgCXgE2A0cBI4DqZfDPTAWcAFFQAVwA9AE3A9sB/YD7wEngbRxqHtAAVABrABagZ3AQeBLYPAV8BMoBOqAtcD9wBZgD3AAOAqcABJ1KBtgDOACrgFqgZuBZuBBYAewB3gDOAIcBxL0iDtgAAqAecBioBG4Hbgf2AXsB44CzIB4AWMAFzATqAJuAG4H7gU2A88Be4E3gMPASSDBiDgCFwMmYBJQAswHlgO3A63Ak8BuoAM4Bcio41YT8gGoABqBJuB+YBuwB3gbOAFozSh3wAUUA/OBRmAd8CCwA3gVeAc4CpwEki19WTpgACYAJUAtsApoAbYC7cBRICETbQZwAbOBZcB6YDtwEPgGSLMijYATyANmA4uB1UArsB04AHwJJNsQNmAHioEAsA54CegAOoEEO8IEDMAEoBioABqBVmA7sA84ApwEUhwoHyAbmAnMB24AmoBHgO3AbqAdOAwcBxKdiDegAyYA1wK1QCOwHtgC7ALeAE4AA7P6sgsAOzATqAPWAw8CzwHtQAdwHPgO0LqQBmAMYAUmAcXAHKAKWAw0As3Ag8A24CWgHXgH6ASYG3UPuACwAJOBCmA1sBnYDRwEjgOabNQ1YBxQAMwEKoAAsBpYD2wBXgLeAD4FEsbDf+ACwABMAAqBa4EAsAZYB2wE2oBDwEcAm4A2BOiAHKAE8AI3AOuATcBzQDtwBGATkdeAAcgBZgLzgFpgGdAMbAX2AIeAjwCWgzwHRgFjgGwg8SLEOwP5A7wKbAfuBW4HbgbqgHlAETAJsANjgTQgEThxIcofOADsBnYAW4AWYDWwDKgCRppQhy+Mfyzrff5zT9MkjI/ARmAL8BzwErAfeAN4D/gU+BJIuBLtDbgAcALXAsuAdcAWYCfwJ+DQlf9emW4dGdKfmYP6rUWbHxGSfZOLd8jmqNzdgPg1Qrb3gpDsKOJxNK1v7/yud37XO7/rnd/1zu9653e987ve+d3/1fPfOL+r7zOxaFZh8TTPstKqqpoyli3M/BqvFmlC/jRP6G6xMdysvpBsEZcoZ80rl/fUkYTf6pLP37hH7G7hk3JzB5vKzeVd5nuEvXK/DPtB0F6YW8kcfkkEmyncqGSbSSYuRmBbuUk54n8cf+dXq7FL+Xv41XCruay23o+vY+UpMa+sDqbpxmCaGhCTe0VMguYZIhYIMlC3FH9L/TWIyX2Kuwj5zxR517VwbiWs4D0njF3OzfyiOAQQ1GatSblFRYiduPPqUe4q4POLomFruIRfmMPO4e/jc3KKeEGws0NmXhwjQmZemIwtSJgwY5JnSu4UrlAhTMHSq+w=
*/