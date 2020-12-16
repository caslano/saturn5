/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_MAIN_09232005_1340)
#define FUSION_CONVERT_MAIN_09232005_1340

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/container/map/map.hpp>

namespace boost { namespace fusion { namespace detail
{
    template <typename It, bool is_assoc>
    struct pair_from
    {
        typedef typename result_of::value_of<It>::type type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return *it;
        }
    };

    template <typename It>
    struct pair_from<It, true>
    {
        typedef typename result_of::key_of<It>::type key_type;
        typedef typename result_of::value_of_data<It>::type data_type;
        typedef typename fusion::pair<key_type, data_type> type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static inline type call(It const& it)
        {
            return type(deref_data(it));
        }
    };
}}}

///////////////////////////////////////////////////////////////////////////////
// Without variadics, we will use the PP version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_MAP)
# include <boost/fusion/container/map/detail/cpp03/convert.hpp>

#else
///////////////////////////////////////////////////////////////////////////////
// C++11 variadic implementation
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/container/map/detail/build_map.hpp>

namespace boost { namespace fusion
{
    namespace result_of
    {
        template <typename Sequence>
        struct as_map :
            detail::build_map<
                typename result_of::begin<Sequence>::type
              , typename result_of::end<Sequence>::type
              , is_base_of<
                    associative_tag
                  , typename traits::category_of<Sequence>::type>::value
            >
        {
        };
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence>::type
    as_map(Sequence& seq)
    {
        typedef result_of::as_map<Sequence> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    template <typename Sequence>
    BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
    inline typename result_of::as_map<Sequence const>::type
    as_map(Sequence const& seq)
    {
        typedef result_of::as_map<Sequence const> gen;
        return gen::call(fusion::begin(seq), fusion::end(seq));
    }

    namespace extension
    {
        template <typename T>
        struct convert_impl;

        template <>
        struct convert_impl<map_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename
                    result_of::as_map<Sequence>::type
                type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type call(Sequence& seq)
                {
                    typedef result_of::as_map<Sequence> gen;
                    return gen::call(fusion::begin(seq), fusion::end(seq));
                }
            };
        };
    }
}}

#endif
#endif


/* convert.hpp
/u5MUOLftkS9j9KfP5EJSt1svbRk/nAH86v3KSPlQYEsqWfTpZ5lzbRsJ2sdu6Hjgpv9rgnfcrxrwnrcfwf/MTxaiTLikkry/pcMaxm59vbX/W7W09SxqakJ6elxyZHaOtmI8hIvidkcl7BdJ0ocJXUjPTU6IZG2S+ZI5JyX+C3zK6OlHoez/fNYP1tZEU2msj6U8VIvM2S9J0UnJBOZ3T4qsBn/MfSQ38Mu8ntonKlerzf+e6gqu6buejcvXnhkBdYFDq0g115M2vT5PSzzOF1JO8om7XgHvykmB78pmTa/KbU12yw5birZUO1LSEPGx8hviraMmnVcIGUcK+eso1D5frqlqcv4135HjaXkf2OA4/e8FM0uyf/f7XxqcQvpW0W2yRbLu8cSrWVSrlv/Bee9CcmUymZ/yNVzVTkbm8s0lUQ0vz/y26b9DQ9ryX8MAfLb0FR+G4yTNeW0Vr4b7YfVtv5FOah/8TrHIVIuu/pnuJP/GO6QMhgs574R1jJwD+CvO0+0ngeZ859JhMXngDHjivfFVVpo93kG6WCwBhMNWBWVfZ5hjLY87PPKLEt1bVmkHPb7vCgH+7x4neNoKYf1ONqf9e9Hntcq+zBzHmWf4eC4OEC1vN5xcaGU/3nZntstxytj1eX/a6/Lasuh3X6mVvzHECe/mVGEO5g3a7k5/2w3OnFOICqpi756eZd1ZrDWu5iUjOT0uFTZrh4l+zTlc3HdITCf9RnfldfxviqfOuY+cV86es3rH6Y3Znq+GfjNhpcu6T2bq/dMsN4ztXrP7Oo9a6v3LLLzz/g6fuZY79livWejnX/W+Vnz+mxZd0KFF3+4pfIvD5wLXNE7aYPlPVbSLlTuZWa5a9/TU+Sh6otVM5/2GeDlvEZDcRl6ymfr+4zKEb+BUFTO+dyyyzefdznnM5RjPqMSsvXLf7FScfm/Qk/5bFkuuJTlFlQpXi4HPeWz9X1b5cxXVCnxX5Pt4laZ+MEdLcuZSlmuBfMptpTl7kTr+7hKyVeOp+p9XKXM950q/7ml5ONhyf9D6Cmfre/nKkf85vpdzvkKyjlfYTnnKyrHfJSfL7R++b+RevU1espn6zP5pSy3SOrVQvSUz9b6Prd8+TKWEn81qR/VpX7chtb6XspynWS5zrJcF7TW91Ly9b26vpcS/wqpL4+gp3y2vm+uHPGb63c551tezvlyyznfjnLMZyTkl1L+Iqkv36KnfLbuv0tZbonUl8XoKZ+t9b2c+SoqJf76st39ZLs3QGv9n6e/XB9Zrq8s1w+t+/d5+vla4Gl5T5i0m5H2NMyneU9YOvlvjBloxKnYEzNxEU7HVTgDP8QHsRZxzEZfnIOkQ7zSnkXauSifWynxozIMpB62w0HYB0NxFA7BGByKSTgMp+Nw3IQj8QUchfvwbjyL4fg5jsEfcSwqid+D/XAcDsPxGIWRmIgTcC7G4DKMxacxDndjPOZjAh7CyfgBJqIfx2vJ2AxTsAPehwMxFV/DDHwLp+ApnIrnMRO/xGn4Hd6PT7ChZ+I+fBAv4Sy8htlYifU4F+vjPGyJ87EL5mB/XIChuAi/l45qpF2M2wnZDv/g70tort/UCwMuwSBcilG4HFPwIZyJD+MSfATX4Ap8Bh/FV/AxfAsfx+O4Gj/GNXge12Jt0lyHAZiLU3EjzsJNmIOb8VHMw834NO7BrfgaPoMncDu6U7ZnsQ3uxJ64GwfgixiGe3A2voyLcS8+ifvxBXwNX8F8PIKv40k8iFfwDbyGb2J9tsMhbIKHsRW+hd3xbUzGI5iFR3EhFuDT+D7uwGN4Go9jIZ7Ab/ED/B1PYjW204fogx9hYzyLRvwYe+InOBw/xdFYiJM=
*/