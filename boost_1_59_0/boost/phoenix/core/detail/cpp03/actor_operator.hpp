
#if !defined(BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES)
#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP

#include <boost/phoenix/support/iterate.hpp>

#include <boost/phoenix/core/detail/cpp03/preprocessed/actor_operator.hpp>

#endif
#else

#if !BOOST_PHOENIX_IS_ITERATING

#ifndef BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP
#define BOOST_PHOENIX_CORE_DETAIL_ACTOR_OPERATOR_HPP

#include <boost/phoenix/support/iterate.hpp>

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 2, line: 0, output: "preprocessed/actor_operator_" BOOST_PHOENIX_LIMIT_STR ".hpp")
#endif
/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman
    Copyright (c) 2010 Thomas Heller

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(preserve: 1)
#endif

#define M0(Z, N, D)                                                             \
    typename detail::result_type_deduction_helper<BOOST_PP_CAT(A, N)>::type     \
/**/

#define BOOST_PHOENIX_ITERATION_PARAMS                                          \
        (3, (1, BOOST_PHOENIX_ACTOR_LIMIT,                                      \
        <boost/phoenix/core/detail/cpp03/actor_operator.hpp>))
#include BOOST_PHOENIX_ITERATE()

#undef M0

#if defined(__WAVE__) && defined(BOOST_PHOENIX_CREATE_PREPROCESSED_FILES)
#pragma wave option(output: null)
#endif

#endif

#else

#if BOOST_PHOENIX_ITERATION >= BOOST_PHOENIX_PERFECT_FORWARD_LIMIT

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A)>
            : result<This(BOOST_PHOENIX_A_const_ref)>
        {};

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A_ref)>
            : result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>
        {};

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>::type
        operator()(BOOST_PHOENIX_A_ref_a)
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_ref>::type
        operator()(BOOST_PHOENIX_A_ref_a) const
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_const_ref>::type
        operator()(BOOST_PHOENIX_A_const_ref_a)
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_const_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

        template <BOOST_PHOENIX_typename_A>
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_A_const_ref>::type
        operator()(BOOST_PHOENIX_A_const_ref_a) const
        {
            typedef
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<
                    const actor<Expr> *, BOOST_PHOENIX_A_const_ref
                >
                env_type;
            env_type env = {this, BOOST_PHOENIX_a};
            
            return phoenix::eval(*this, phoenix::context(env, default_actions()));
        }

#else

// We need to define operator() for all permutations of reference types.
// For BOOST_PHOENIX_ITERATION <= BOOST_PHOENIX_LIMIT_PREFECT_FORWARD
// 2^BOOST_PHOENIX_ITERATION overloads are created
// For compile time reasons,
// if BOOST_PHOENIX_ITERATION > BOOST_PHOENIX_LIMIT_PERFECT_FORWARD
// only operator()(A const &...a) and operator()(A &...a) are generated
// this is all handled by the PP mumbo jumbo above
#define BOOST_PHOENIX_ACTOR_OPERATOR(_, I, __)                                  \
        template <typename This, BOOST_PHOENIX_typename_A>                      \
        struct result<This(BOOST_PHOENIX_PERM_A(I))>                            \
            : result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>        \
        {};                                                                     \
                                                                                \
        template <BOOST_PHOENIX_typename_A>                                     \
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>::type\
        operator()(BOOST_PHOENIX_PERM_A_a(I)) const                             \
        {                                                                       \
            typedef                                                             \
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<    \
                    const actor<Expr> *, BOOST_PHOENIX_PERM_A(I)                \
                >                                                               \
                env_type;                                                       \
            env_type env = {this, BOOST_PHOENIX_a};                             \
                                                                                \
            return phoenix::eval(*this, phoenix::context(env, default_actions()));\
        }                                                                       \
                                                                                \
        template <BOOST_PHOENIX_typename_A>                                     \
        typename result_of::actor<proto_base_expr, BOOST_PHOENIX_PERM_A(I)>::type\
        operator()(BOOST_PHOENIX_PERM_A_a(I))                                   \
        {                                                                       \
            typedef                                                             \
                BOOST_PP_CAT(vector, BOOST_PP_INC(BOOST_PHOENIX_ITERATION))<    \
                    const actor<Expr> *, BOOST_PHOENIX_PERM_A(I)                \
                >                                                               \
                env_type;                                                       \
            env_type env = {this, BOOST_PHOENIX_a};                             \
                                                                                \
            return phoenix::eval(*this, phoenix::context(env, default_actions()));\
        }                                                                       \
        /**/

        template <typename This, BOOST_PHOENIX_typename_A>
        struct result<This(BOOST_PHOENIX_A)>
            : result<This(BOOST_PP_ENUM(BOOST_PHOENIX_ITERATION, M0, _))>
        {};

        BOOST_PP_REPEAT(BOOST_PHOENIX_PERM_SIZE, BOOST_PHOENIX_ACTOR_OPERATOR, _)

#undef BOOST_PHOENIX_ACTOR_OPERATOR

#endif

#endif

#endif // BOOST_PHOENIX_DONT_USE_PREPROCESSED_FILES

/* actor_operator.hpp
LYAIxZPEoYCAJNGQ4nej8rGRL+zLA5PlUYol6BDiUeMRFcADkQPmk1EvZDgRPadest96rrbddrpWfzx5jWc2re5YvFZ/6fVO/7iZnraOsU0cYxk5xDKyi6RnFUjPyJP+u7yDYxLZ88/TB+lLUWxpPrUk6Hggaeb84cAW+TJ2OgZ5yVlGR4ZGmSNkSv53xO47Vd+YUV0bhKXW1okXmkRIauQ9PW/fPmrgIUlIIJinJnfQ0OHa5ed0ppSUKBk0qnCLWbY34/wHS28Fiq0bnx8u3N8XQFCBD1zsOnZaxUgaJsnas+6wzj3Coj3Ld2pWee2AHeiGHu4dwPaxEPd9zQyo6/QlwTWBuLnsamzyQaUKjnswbD3CUY50mOetU8zowykpYQpjFkgkbE6nPuCzdaR2lIZU3eFYOu2zX9i8E9N+7eUKt3T392xKFsp5pUylKj/fVcMgBxKmX2dvPQ7/ISE2jEwWv9TowfOO4wZQ4eOCzrb+cd6Zw5qoLlxWJOxT1nkZQYHqvNdliVNO8znqxPhye2BPt0gbgnV5pdRy+Q3zXkpVR36TGf6KzBIrJMMi2AXKT6hcTl1mycneKc77Ce3DlKJiTZJYLCx/fG+pm09zTH5xnEvlmhUcU3whwnCTdN090JYw9ZXNNvxBQUdiZfVG9qLLADnr8sxgJhpcnW2aOHeO6sFFA3NSScLjZxzZ4OSWhsVsU+vzpERNZ83XyEOBguyW+2+/6svWMVLpl6XqtXvHuSUuCC+1h8b90sqLRUKzwBVzgFOVwSB7o4/nAWTdwBMQcHhriRhWe17qyECGcrctBqm91+n7oLdZ1UWGDIo/CNafGQCHhBtt/o23uY5k702T96VICU139Ey0QqHnQJEC5zomqMxEChNSw9fn2g5DxUZ4jy/eOqxxCw5z5xA4TwcA/1M8Y5Hlc/Vv2/r0T7/4ya+1D72ieFosfFrcWJSQCTEjYTxa2JSYkSgBI+J/pM8zekTyr71o57tS0jIar/lQcLmw/WhiNGLn+1QNtUemrkP6VONwQeUEdZCW1m50Ug1voNuRYVDTaGQ6zyHxv+i0hMBKBf8clR7IQbOMB415GgZ8cwdbx+ISlK6OHpfGECJBL0MJthIVun18gmr+TtM2z/4Um3lgy1E1NLniGkkDR+caNtz9IRusS2g8Wx4oWzW2Zq96YEgMXk9lE5ul9jHVdq6syVT4tnwde7kD+sX3x5DuTVLSlbs5PQI+vNqK4c8p21XQBP6uOAuIFsGkyGwbwN2lhHFFvdxOK7uRqF2fYe8SYV071pS/7x00TotHk+HrCHil54UKyLzP9rXh9dvWvWPlk+vbuCmwsbcpxa9wlCp3zV4BfSKizif3O+Y2yILnCHlHG8W8WJUpRwrzoK8NtbqMlfGwWowoKRk+2rRhZ6gOMgcQkOK7zDQ4I2M5nqVvtU5eLsY3Y0UAgwvgq91JbARFb5G+L3LjFk7tsVjuWrfMH499gXKpSw6EHnQl2JuCLk1nCGzLPAJivDnrRMXkaGZDACH0paOzfpfaHRB4eYpliSTVbucLvvwjPyYwk/c6him96QcYMW38OzsJU1hGp/iMoGls41N8JrAMjvFpAdNYP1in7LS/NzuWVEU5VS6MudCsshwPFo4vFiWzD9dITw1gxRGWFUsfdbJ55m7rUVQ6ZYr4kDpJF2E75ddtbVMkfcNDnfYVVS9Y6+RMR5UF3t12eRyVo7jeCaWUcZ/PAhYqqp81gw11nxnVxJxYzuqRUzU0BTwKS7zPtfs6JlLKWT85xbyygr+7gzrY5Lc3l+skOGVf49kJ9329kzEcTgEM7pDeRBBl8VepvRYjmzPGLopPsQFz3kBXPsNQm7bTs0OrJ++Rd4WPz0NiBspz7eBkLWlHLkFWQh+ufYDTmDHNc+VvzfQ6PMpzy8bsiY6+f2ZPrkKVHD0VMfXgC2ajqu9zFoOi1JpGorpGrCkD5tP4nqVTL7fYXx11HAw/KwRaj6IAiPGg7YL7AEzxC0Vw37ne2dig7AAU9eCyfhlAPjzlYr9KPb1YcCxnW5cfGJ/z9OPqOJfNwK3D9pYyHJ60+OpHxtrG8879xYXBw+srhZHl9JsXgTBQ6GnFUiE8WVxZcO+NyAamJWiz0g3zq2eJOfBVztqjY+7jPhjleWnzx8ld3tXOEPKonYjFwhesL9uZvM/6eHE10WB12VR8ZP84MpUgrUWVWezMwJgnH0YZcEefVCAMcSTqBR94mvOhKd8sYXCzriEaic/5zaFxMeg/X50ffIqyvOnzuERAdWZ608n9NtO7PgaL33eGWqr4sUO2/x3N7Su+KkCdg+2BiNhyk2jDD+Gh+RrHPjJhWNdr3Us8gC+nP8J3H3IcgXdQD2yTiSrN4qjLdNQ0Whh80zjw2R2KcOXea8DRmjkuqhc6eOyRVbn19/XwWiqEn38lKvwxdqGANnKasnDVU9oCYXSzdrYLYctzuGNuo16ia2tT+Hg+xbO2d/DFrMpbEcv1/9GypNfAUr00JZbSS8dzXWAhnOWaF0yQFrR49vHLlTT5qLuunnBOTzMPfktds1xVpbQYMJ4oO/3zFnSqN52AiCZtaTJ6yEWJNdvXR38ZmJW20NGhGpmNR9GfN2zMnOWkR2ENCl01DvXBC1yK63NwrRpkYyWWqAtJusUNJaYoUU3zau/Ss0t4ffU7OyuSC54AACz/04KNmw41Pbwbk9DHv1wUTI0RwpCj5zxFiJQEn2Tf3kW0/5eJC5jJr/Wvfcct5CZ7n/BVVfK2jWBTrOG+JpsEpYCh2E8nwlvJkRUoMfd5h4aN47OMdGw0JtkdXmB2tEY0fL/EaE+MYb7Eg4BU90BSUSeiATmUw/M6R5jDRePh4AWiFY0oazNSqXdN6a1KGqtipo9HUYuCZrJro3d013Mr/9IGIoqn5ms8bQmM+aVuJnvV2E+fo+8gVsPePci448KfCp+WGnsTwYEhpRdZYucq31JcWVgSc9IPWYeHXXWAb5V5yeOxWcvKAu5F1i//PX05hRcNZZeJetyUbbx0VJPdoH8+3/Gvwdqg/WI0vYNOV4X0oUIkMUXfFdAM90IkXd3CwlVT6UTI+2Y8fV0SSK09e3G6gzMIulD4rN8h7vv3xraE9B4VLl7IA2DAJdj9mZZZdRvzYE7cZYI5tqvgdKVo4McSc4oBwI4KVYCtWmWJjlM7oevtUSdk1eiUEFqN1CxBXFibL+Lo6EG9Za0pXCZIWrCpxQrmiMq1D4o4jOAf2g5rbdlWCuLJK2Sv5a1HNfRDuFSYeu8zHUmbwSFFjaTZzzMf21FWOIvoLjpPykLrh9bE/vRsKw3fiW60P854ZttY3KZkI6zzOcLSJQJ5T/zUvYTlBJEUJOFODqAn9stj1b4KnK/ZGczc5FzToARyehpeu4u8TeWGLKJjPmZA9ftcJbqQM/5l7Am15vPpsVI34bP6yfgNZr017lwKi2WU+TcuzQTkpkisTbgdxWj15KLbeuRf7wGmWwRWx1YQcj0LwYCv36CYQOfylzJxeQ75CuEG0OWc96ojoHnhLmIVC3u+jP20Gi04KU2YH58mH5g1pfL5DIPdm4W24MheCNZZZIfxG++cMUq+M0MwGGhur4mkP59VJ3y9gSPjnCYFuQ26D6UK7b8yTtLysJq4UTgzdt13IpoGufBEqMUmDelK80/afwa6sOl+xL3jUg0u2T+0vtaiKvhgrN+j9daxlEQXTrOxdlc/TnlGBaqACiKd6bNXSIVfhizkG6y5uxGbz15gnK2fbeDbYqVUIsw568YX4U3zJEgcy+8voqHhJ9GuFMByN511vCZQJry57EnXMlWVXSz5vV5XbrUUTKMOz7D6ODU7SiQRszaubYRIRDy6irAMQcwkqby6V7DMMhXtPMzrCDw20jwEPQ4ZVpLQn+Yc4u3XZxL+LDdi9JwZ+KtUN8LeNL+auqzLV5l1rX+THZOO4LQnDabW7qsU9DoTg/uwfrvQnO3IgpjWpB1VvLw7S4DiWInOklESL53XCLm9dvrFiZUgU6h39S5ZhtBTqEsNRRfFdWyHjXvX8F7PG8qIOq6AWSK5CDKyKfZuLrdLLecHL87rkwEhdcpgEYV/P125Ua6e3IVhXcDqJTFfO9Y3dILb2QdzGFJraAhLBC7QN6mFEZt4DgTW5vdfWD6eTgvLIX1MBlxz2W9dW3rPEaM/7KZveuXP9M6Zk8UXfQU6KIekWHYfjugbSBjXNVhNZKAlSHgJW3/EgXpayV/wuv3zJMw+61E+gwPT4/BX1l81F2yCfzIHH61cCsP1ADlBcaSYVH67MFiCraVBTQtwI9VSw9MOuPMSk02ouE89OqLaJPaJyM0bMUSv/RFHuwFZytpbpYdDq6Xjps++z/z51i7POAZRGuLIwNK2+0lL1wH2XErBPkqDXWfYJfa6Hah1jllT0x/gmRWDmlR3e+ah+R7MutPjslnDvYfsDzkxDvNYnJphycZ4BWz4fKwsEbaD3raxgjF/okQLcoY/nIA+u5ghwDweqpJpahj1MSVQmB0zVQUASFnN1fA675l46FgF0piJt+Z8isPbtVKQkgBsRRqLiOR+0kFm3qlXFt63tVIkO1n1h8gOsg7U+0+6RlZTHMgy2YfjuZljeMbkFF61CHUAM/k0EPjtPrLynt5Sy+Ir8taGp/bT1Yc/zbEywGotkz9i69p5YVV+yUQgfYYWZ0JuyFuEtiLUNC0SEoLAs2mpIWyVfGp6XMzKQjvMCTz1R2h8dAenVxrzZMWUjo62c3bf6rsLyVss3LZ8e7hTWT2K+WLROVUJ/+TLUg7CT1rHkdW7OjFbumubBwwR2+kOoiKY1jx84hv44UxVbw/VyH7XFSRh+XiopsPAjobfUYou1WRhNqIuC9xOT5zYXflq4TNNstpuHDlnihybM1Y+1f7VfnvCkum+QEF0Hl45OfDgou77DaxYXa4zjixfHgdgH5oo6F7Wb6wPu4/3BCCr19Tm2W4sa4+HPaDFs6TfDa7LqvoFTpwLbI5Xzc/a5V2iDaaYMQCy7Negj2uICgbWFX6QI8tYawQ/Gb1AspWA5sMS36JAtm4FZxyZsBM13Zqz5jjVPZHZ1EMF/uNtyTaBRdg46uzc3qdW6dj2Qw0ldtEmHj552nN5cvHBDElykzfAu7iQx6l8ZMnxDpKRKOuCCXkLiR1fHxeiJBA4WhiPBpEyIFnKBOsx7cacRcDgVP316snPzl7IAptmTl56G6GY8cvVjszqEn7xpuzhTn/hCT3gkZ2AIgWgIcX4Rv1pbCx9KXtkADJp8gPGvkVLc9pk4RAtgf+93zM5hsskMj3Nxog+mAVFfcVPa4pGxcoE4+Vp76OaVxXcooK+vWt8wqS79pN29CUMAPAXLgSxJnRRZ3mkp/67YyPv/i/5eNeH9f3BboAl+dD/L7jnGwMLQvo9CdpSnMmhsW1yA1lj5q1e9YyTocIWKnAeDNsoJHG1q6m6OY7I6MHBZS5KWbCaWuka80emPTT7wPQQA1Pxs3eQgZtoxBaNgUzuLjqRjBONItG6L+28NGVX5qR42AdNA8E8q6pI3T5O9fRcZEuRCIsq7gd6sVeEWTe379DS/OCG4aMDRRb+i16r5iO+hKWONOU2Oo/TYbcRd1yOkwbwr/ngWZ2MVC5mBISvFJbGy48skrpOrnAnXKdFN/WSauM/BwKhNaKH//63/g/0yKW0ScrmHjo8uSz2/e5vpNcHVGShxQMADz4eGhgIcjA+yJgkiF4YMCIwkfiMXMExkRpjwiAcKDDfmBgm8SjeCZkYzgB90N8fr+7WdkXVZkX1ZsYXzWlBrezreUnOTe3lzq+yYQck57L9VhgeylNFGA7sw6yEo7Z9iwBqy1ZUQoIlma60QbUstbfb+CefOWFenP1sNupJKRAI3iSBORsUcviGCR8MoKeGJCQ/AeC3459IJeJKAccuiAXt5AvDCCH0TvN6fczyyrBOIUWBbyBwWcKH7XSgNQNwUCyeN+D83uLCAMPLhBQajkHYFF3yVaZFLkVwlWsvEEsxzfrdF5SXNxxd3dKSRw0Op8yMjA7B+8Shui1dQgVbeWtovv706No29/Gtol+P/E9WyDLcEYccDwFBmVuep70T3xJcLNwqFgIifrfSgiY/wt4Va8Ef9tXaiUnRFmpDWNjY1llxwi5AVkNhxL2Lj+jq4todRcmNiopKBAgoaFGdWCtA0af0pzdDy55imVMyX+cuQwPB9XSQoNPTE8ZlTirjy/1lqQ12D/ge1SA4UdfAtDG0sQIq1cEnc8LNkAYBmZnZp2KWs0lsxzIcHioLW9SXY8ylFbnahqy6yHYyzP4REny7ga8LQx8eM1+dnZmdnpNYwigqGJjYgxGidUZsKitfHK88rzcNZbJIyD5iPxnBwsIubK5uZxtlhuHA+09MCcLN9kBBb5sgggI40AEjfT53kEheueIMs+YZPtDEBEZwy9rG3ytkCwOTVGTkZRm4xfOe15bTRAXSfoe17okJ6HrWLv5Y3f0xfURE6SPotOexyTT6lwnhkne3vGdYIqANC0UnErM61Lz33hC425/SrS7i+Xx6p/pROpaufKz7R1lj4yWWqxId3Smm4/o9eDw8GBGPKIFYzMmRqHlZxaPTxjFzXvPN+yEERBswQjm/LAMqLSgKhgPIGJGhwh9wS0kc6Eq6QB7vDTTCblHh5EwoPzbdK63KmE1ePSlZ2S++gMKEcgN3JO72fISXWi/0EBZISqBVX5EpxNjn1Iq3zbdaXoRYJHAqDvY3f7mrN+P4tcuYo9BwPCS7QkYThX2azDSZ7wUtiFOLFam99p+b2n9JaZigjlgWwV8CVdAprD6gm1297tsrs5y9ZH18oh1KssLsaV10mWjo2AreOgnLtu8M9Zr6cVvRoh6L6eQ6yz8AmwmqCIr+yPvBhmVsQQCrTRKu8WGR6RR9up8QhjGYNmtKsulYMJPaiM/0KJG+bLQ+IYEMVcS2b1jKeE4vjnQXESxDn7OimzYjjssTADjyFLE/48ZPLTJHIKpRiLCJmVDdNN6mLXFbdHV4eHimQcC3J1MZ1+f5oX1w5nw0NpATJ51cDeLey6TNbhqI/o81ALwb+B28Yie9nljmW+83BOwvrQHKEUhwYVQUC8vGurnh/ym+9sbXyfxifpTm1klHHg36HzvJd6YViAlYU9bi0gISio9kxBiwnXyGsJLuj0vvo/UP6r02SduEFiMiDTILLKtRIVaRKtqx6uu8h066RkBiVQsp+ZrN5r7h4NxWa+3wY1epbMJ8WslwnNgPiZwKicT1xlc7+lCbTsO3NudF9rCSknDnXwN+kXbhfjrzmlNuAlegDBCmnzj1AkcDLwAfz6wFML3lbRKqOD4DYNRymweSMznaad8WKLDQozY+zsG1m0EPwd0Pj36eEBi8CwZp36PYRUlR0dGy3qZ1DkYeRl8OkA1sTYZ0YKm7xQlMOBXQJEfnxUMScAUSPCgGiT2tSc8l1TyckHwGcBwBBYrksWWn9QFWtSYoJmMTe3wu0ACssfDzr6BFOTjd0Sq4nCQg1bUU8ST3isbS1WfGfAIcjhlm/T/ih/fGZqXwskJNrX6OtWoH0YTMs2e3yuBiZXTbhHWJ6xrmMNr3jET7h/RQGI9UhDveeY1nq75iFF6F
*/