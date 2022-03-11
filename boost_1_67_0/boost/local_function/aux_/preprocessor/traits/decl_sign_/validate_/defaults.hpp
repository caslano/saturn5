
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_HPP_

#include <boost/local_function/detail/preprocessor/keyword/const_bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/bind.hpp>
#include <boost/local_function/detail/preprocessor/keyword/default.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/while.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/control/if.hpp>
#include <boost/preprocessor/facilities/expand.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/is_empty.hpp>
#include <boost/preprocessor/logical/bitand.hpp>
#include <boost/preprocessor/logical/bitor.hpp>
#include <boost/preprocessor/logical/not.hpp>
#include <boost/preprocessor/comparison/less.hpp>
#include <boost/preprocessor/arithmetic/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <boost/preprocessor/tuple/eat.hpp>
#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/list/size.hpp>
#include <boost/preprocessor/list/at.hpp>

// PRIVATE //

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_IS_UNBIND_( \
        sign) \
    /* PP_OR/PP_BITOR (instead of IIF) don't expand on MSVC */ \
    BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT(sign),\
        0 \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_CONST_BIND_FRONT( \
            sign), \
        0 \
    , BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_BIND_FRONT(sign), \
        0 \
    , \
        1 \
    )))

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PREV_( \
        sign, index, error) \
    BOOST_PP_IIF( \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_IS_UNBIND_( \
                    BOOST_PP_LIST_AT(sign, BOOST_PP_DEC(index))), \
        error /* no err, fwd existing one if any */ \
    , \
        BOOST_PP_CAT(BOOST_PP_CAT(ERROR_default_value_at_element_, \
                BOOST_PP_INC(index)), _must_follow_an_unbound_parameter) \
        BOOST_PP_EMPTY /* because error might not be present */ \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_INDEX_( \
        sign, index, error) \
    BOOST_PP_IF(index, /* can't use IIF because index can be any number */ \
        BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PREV_ \
    , \
        ERROR_default_value_cannot_be_specified_as_the_first_element \
        BOOST_PP_EMPTY /* because error might not be present */ \
        BOOST_PP_TUPLE_EAT(3) \
    )(sign, index, error)

// While's operation.

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_DATA_( \
        sign, index, error) \
    ( \
        sign \
    , \
        BOOST_PP_INC(index) \
    , \
        BOOST_PP_IIF(BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_IS_DEFAULT_FRONT( \
                BOOST_PP_LIST_AT(sign, index)), \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_INDEX_ \
        , \
            error BOOST_PP_TUPLE_EAT(3) /* no err, fwd existing one if any */\
        )(sign, index, error) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_(d, \
        sign_index_error) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, sign_index_error))

// While predicate.

#define \
BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_DATA_( \
        sign, index, error) \
    BOOST_PP_BITAND( \
          BOOST_PP_IS_EMPTY(error (/* expand empty */) ) \
        , BOOST_PP_LESS(index, BOOST_PP_LIST_SIZE(sign)) \
    )

#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_( \
        d, sign_index_error) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_DATA_( \
            BOOST_PP_TUPLE_ELEM(3, 0, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 1, sign_index_error), \
            BOOST_PP_TUPLE_ELEM(3, 2, sign_index_error))

// PUBLIC //

// Validate parameters default values: `default ...` cannot be 1st element and
// it must follow an unbind param. Expand to `EMPTY` if no error, or
// `ERROR_message EMPTY` if error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS(sign) \
    BOOST_PP_TUPLE_ELEM(3, 2, BOOST_PP_WHILE( \
  BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_PRED_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_SIGN_VALIDATE_DEFAULTS_OP_,\
            (sign, 0, BOOST_PP_EMPTY)))

#endif // #include guard


/* defaults.hpp
/aISHR474ZQZn7CZ0kZg7ALIMDwE2DsqiDg7DrQSBS6HeiLu7HOk8gH15x4aihwG+cGD+4e8rLBk+RFvALknRqdTDkbT79w3cY3TCz2SPznb9VC850+GkUf6fiuIA044snh7XaKPfsgdxvfM4DpNFqs4iSJ1Hg3NeNf+HKnkvZRJsL29wyov1T0EUhWFYCe8AKDdnnpF9/A8ZtpE88iJaS91c6uxUBkpf4k8k8QsQ2/bJ3u5emOvVoIkMDyN5b7qlyeFZKf6dVvpb4sS8nx3+3sVLA6ZpxBvFtIzibk3/zZBeMsTwtW7xFKJKd1lJgzVPABAsiYmcB68/20gfnTEmpKVg4p9hZf3o417YUt4RTAI+fCTbpAj6JHQtxa2Rra1bpe3LpTG8Skh3IU96xCsm8yzC7OrtKe2K0DCvmJOWcsNBTX6UVo4HrZeu1Wml8bUW+mJG0POSZATO/bUV+AKNkT7C4ILuGJvmh7qMDNzttnjxH98R9n79j18gbHaI8lnQw+bvVarXac5FBvHppGcv4nxUiKP40hTyfKSCule6DUyWBeGet8L8aDAlHymQSz/vnJEEwcVjZsYYcnpqmEAh0avvC5RvVUKys7C9aUQbPgOVonHNHJoALjNvpmHC5Oha0GXkccUqQ+h05zWMK8XRcXy2Xu1GDkcDxZccUdq6ehvYW4R3OCwb7x2l4AhYSYZYMTAzT4eY4W3IIHA9ZZfaESklKbZEY86ljfgIJ1UtS4AN9NgaVK3s37lJ7kMeIzlPAykJhBpF1bFi9DHVO4HwXnylaVINWMJsu4MfAvoqTUDIE89+b51a82QI7O80Tl8NwXyus4CmGAzGfBaaRZGIC9BWitMQr+uaEDdSwbddGbQg3vI1yc2qupEABUs4XbCaCc9q0LzDe+mzXqqEPyxgSTbwinAMq4LUcoPxoRWTG77aepIebHYFw4c5kN8FkhYycO+lQ2flOWMzvROj588whxYqCb7PmNm9Rxk0wrJdp5u/OUzoL2Hm78AVpC3HEfjQL6S6PYAwQWHNwnb1/BwXdgWRCJKdTMrFiMifvvUUtFF1yq3AxDRypqGC1CkM6HGHc8aQAEK4v2yxcNfyqTREcPAxkBvLF8vNBXGMvomC/IWRcDsoIXqWLBsMhNUq6zlbULvOstsBC6ghJPNq02RjdD2IPaqznVtGvVlZU021Zpr9Jo3Rp459OlF6TBWImfpjiWeZt6/eeBNoWp036r6kv5GyNdg6Tjy5tGIdjZodf0vY6dUzn97pxS+w1t+XJiIF5ZfVW+uil7V+BKzqyRGaukeeXSEdAw9A+y3il1dtNPWiQOFt4UiMpV6EwE5w013Xi6wSze2rtafEiEhZfilOB4k3lliYjRtlMdGfJphgxAZtgEtq8+2eAzzbvB3vMFXksW4sZAdqeltqScFHidCkjEXQ84w8xjSovpD3GGqBoWn5gcucUpoy9bVNQQuK7ksC73HVT/SyAtsnbfg7XOGSZi2o0GFuIxNOWUFjpGZNSdVtnvwRSaafyNcAKEhrJLHiia9PLe2qPEsdzQbm7lU6vRUOLe05fhtCt7TnXDNuTaAVQR9yQnm3VRCQOGMyYrlFs4sV1fvioGieeYxuaUlBkbNoCx9qGPiVqjbP+oSWZfBImmiaMw2BfCbU7PJH9Lx8wVRwbjm0ZO6+OuW5vvym0XJxl6Kr5NDRFrG+Vrb9Wg3iJ60nv189KmxgU3QAaKkTexBfAreM//yphPGMeAOtU8siV9ydkt7knrohbVxolrzsu6NJvtRKdqDALbevdO6Pm7TlpxRJ6PnzYJMjgal+U8CO8d7ZyqL7Yf0n6dSpCe/1DuuVjQJ5sHDURSreXMio5KZ3LQNGhyFfWujhJQSj+8kxGbgj9gJb0+O4H5oRaIVqhE3PWDyGNHQbX3qtdINZ2COZcDt5KYlAFJCLRdZJIUvCPYGieAAL5wbgJm99OGrOYVwIFBj2R/ndRPqwvXlsr5ErKSmj3RelnOTtjvitonHI8DOVhhANVmmXV8rmMTSVNsM21mL5akSrjLyt76nSPm6zjb7EKI2YiCc5zAlE3G4MjT9z/P4DRbBTjBzaw22mKI7cJ/IMn/egobc1OitRNCK4hcM9N7Tjh+5ZSZ1MB3V84xHIkSZO6OE/csDhLt7GTYXx7Te+EWAGQS5/rshvxOWxnT6xPXUsBP9QeX2feqxDpoIEV37w4QDNEhjRynQsDtqrkzUiXM4ejQlTIxpBBV32KStGLTXcp2roC7BNnjaGnAFPoLIBJDsnQBnDe60KQ3cma1bzydSm2hnlAtLTmbjIOfXxHttGQGCSTwX7sbqwJuGe+WYasp233FYj87Jl70oyXaHx7egxZA5ZIqBS4qVQtsGyy/SgaZqDj1nhSM84TWq0qXqi8OE8+ipjXI2h7dhGmSJnFuWor39AqgTMrQ3UCfl0IVgZVsbgiG0zXbQHgxX3y6h+upjqjKkh/kyu9tW/Dfn22hLkNyUHuSApoaLmCH0tqa2Mbo17eDRmkTNXD0Uqt7uNxctMAbjnb0SR7uqRVgrzwDingmU8AeZsJNDhPLMcJ08UAI12+tvUTkl6aOqe7dWbROWdl41E1keELUMENgNU9Jb7EhihDLCxm/JESNkmwfT9PhFqe1JS4O+8/2YarWHp77sDiK7GsLp1kPDGUISS66QZL8TXTCeTpCYrqTn6iBH4D19VjLPo1lY0lXUyOkWUJf525AxURBGz0TIHdAwDqrG23O4eJU2l6+Celp8KLC0Id7EHLP6OHnHMk9ATjzdKXVmyKGgR97aHqmV5DV2kjXaPZNlvfTsSXWDANdJREErhi9OxgJOG2PLPk1HSqR351kgmbJDf82GaBB2zCQ64fgocnmw6BFwpDJtd/KzoSwGL/7Hx1EopK5reoevjclIvzU6TLnGLDfkc7GAhlTspbjBR4nP11YZP1Blp9FMadZlI6OecWgYZHq9Dh5s9wOFhZxOJUeYypbpkmAuEzUqaSIOh8bCfLRBLbq4FnXIctc0zvOCU0XQXArNHZ35wr287Gqw+pYWgnVjEVvyAJDcT8D6Unc6DX8d6R1iIw+vdnmDWVe4B6L5gqBjlXT+fWorpLNDCw+2218G/+d1koKm7LFRp1FVJnsis2/JFn0hF25uXcvLzfixp4rCg/UoLGxjEvPHa4hQo7EVsbjiSHd6VSMjEiSEzL+GmjZZULHECdzHzKs3fyznoVkBcdMf0x/lcWdiIMY4ok/bqenm0tCP5SDlpPhFWBmR8vrRnsIm0p3o/rVu23k1yfkShR7b27M6aQ/Baibx/hwTwkWnXU5f7B4YHHdLXY5SRYGFEhRH6jHA2e9rmSGCzL6P9kJFrXFF0aGtDtJMQpV0zHqh9Jkr0s7e+0ms7fn6AacD6nqoRGqTu/QZ4wsdgNC0PHErZEixU3+Mx5DY4es8kEwAjufDLs8bXo/nUC2wVfLVMny7Q7B+F/VyPG9uOHCS4d80gKEECa4FmfFRGf07R3KPuxlsJjeOygrMmicN8TKxeUPRd3AZVl+bMByCYQsPNuwsFtoTzJyyr7qIvhjkaCtWtip63BlBY7txCJruQfbCc1I/vciZhdVtuWFDq3KtqIFfwjiQwbhXImg9EqM4lOxOyWgAIi+5Ljq+kxgzCzLXNB4MNp9eeCtz2mnKFLrC/7lTjIYEKgNHTW5CdnMMJQ9rdY9ihOhahBO1mmSxmNEz2Nmne6mh5/X+WZbRn3ymfvA44plKuyf/d2vRleYh3Di4x/g4EmoZj42hJNqfEVBU3CQXUa4NIHh4PKRrk28xxPKV1KIcteTlF0p8ypIKTg7T4jLGUn6kQ7ublyumpbdLdUZhhCV2fhhYyKTMnR9sFa078TYGueh0zjtJFhMEejHNpdS7NQg5RB3hswct6PFX5RQD+wWx40K62YlGNTOR5TG4xfZNxotjk8lR4DfXzHEmpx7TYkZMjLwzk502HKVV6zxEtx/GvNomaIMTQmrYwG0OzDDxFwSPtll0jCjJcr4CTATL8itqI0/khrewthItP4oeHg+05zPuXYmF82DXw9FQmM8BnA43+EYu/rIM6Fq/8iE9B9h7s1sqO5OaVBVfPvJ+L1PJE2iv05PdWuytaRRvtK1xHf4dlwgj39SfqHc0IZGMzN241ZdUke46vXeKIZjnIfDq6O4xQRydurw2G80CdD+MEaSuF3s3Vy0mEzKf+o8XvBQm27RqqdtWG745F6EeoxGtYdGQbFT/IyNJrMRSiaKrBIioXD8fi8LXLIckTmqZUBMYmInuRDKDHUoB39mkwhvXtY64clSl730jpmFIp4NDTXdR8xS7D0hMrVhtONfKMKrDPY+Suwv3FwuSpR4yjpBmhrDrhZm72q5vPlEtHKGDvr0ah4wJjb3jIA5nr6/RHR5BqfwvdloFTcZKKjh4OOBcMBBb2ZUMJbychkSpDYFX2oAl1SburareDlmzk6xf18cOoVi0v6O+R63bSSfqLg4eVMT2R7ooi792wBPDNG9531Lp5X0GTJKrXLIMMpbb05b0RRlfekSE+WaYUlpmF7hK2M16M1MHSibXripilPy3kHdLVzHzANCbZI473v8PYbGuqDnj3BnoLBaQnehhNrjiPsrPexI1eEULSAMfdIvdMM6t7WZa+0fJ2iZ4alaCVyRIZY6DHRLSfLTIHzY6YbQEDRaJ1tbmwC1Zp5d8kcGYvopvmhHqkIo4Wp5cO8azZJ4kbv3jhpSO9tX/HdE2PfQsIUwS/ey3ByA1Q+HakW20PSzWnQROvOvTpusSVs5t90g4lmxzFnNRVhMaj9QaTeTaJsqm3uU1NlGTuKp7kE7ePDXycqw9T9VHOCXfEjV+wcxAWtcBIsDngYADhh28aNLkjx42hFyQwqIv8qfWJVtC+ys2SwSHxqalneSgV2MYOw/tCzLMet5XiE5z0GZ63g9kf0x0JLSvvEok5cZzh9atW9VVo6aDLTiVcn9qDeLiHmK5htlZCzeYvL2zPSl1o9wq2Xqwc9OT0UNalSN9Utg1cQ/ZSjjt9Ox0OJagh/tqR6JDdM703D2kOgKefqEZBf8dWL99rAdlxwBtXHyN2Rnwekjzy8I87BAwVcwF8/j4fZy7Nx5sCL0wgXr2fD1AX/9fv3NGxSSdSL+DeQa/thAmFZ9ARou2/Gk+8z07cpi8y3gYvGaSJVdFIo5QjYVmlcUjQjZGmBYGdCJ9NVRDmtQ1RNkJPZ4S9qBwmNGTma7+NbpeRzlWnnzk+J4PoVXTs1Z3EbLcrq42ZXDG2K0es93sP4xo6aJod3Xv0zbZ3Dg0WbeZjCzW8bUipDEPPlr8jXpm3d7hb/eJtu1wDpl4kgOGI0CL+ra/ij1jBEDF6doTRHpgCJMdEdzWc38etkGUAJC48tRI85XWD/1y8K5D0bk2gHzr48ih67M7w/EgNKTDY1Fj9Lo8e88J8fazI1S1/xd+vyfC2MbsKGZbwh8kO+TA7W+C8DGUfPb4buPo8130CxkEDu35H83g2kf4NdgmoWCg9817cGedPDajU/cK/g+ppvj65f6oXnXPz5Ct+K1Vs95vpuY/ffbWBeXPW6LkcKk4kzFKQ+U1z8ACGvkT3Fq8Q4MRW86uSVbaHYcZRpOdng1ZURpZt/Qf5sATITsSGR7aXS6vbHA1MeBMfM7S+hqaS91gAgnvrWch3gyDADlHkMFETDybacxAWrrTlHDjifPkDayhirSAELpCHUiZ8kwqkbZlqkb6GKBOyhlU2Fr7JrxYO2syJajE5+HilSlNobOGzfK61mQLktXMELSNG+zVHtuPZayJAhLx2bLBcqoG1X/MRXhuQoIHLQdzhIFLi/+gpYear7G1VmAGR4o3FN7LsXjspHLA3Ws/FzAHOWVAiRqFz3iKS/GF+KcktFB0r6yJB0PgfdtGdx7Tano5KIEhWvEwyRWGmTcNn2k35NCKVN7TJ5qHp2n4qAiYI4P0BJlOxI4iXf3kJp2unoEAy4s5kpLqukg3ULJgGsaKYcX1rlB25rqAPI3Bq59gJwV49PpycAfnKoCH8OpCOhNB7Pr1o0YRHX6tDOpJbi52n5VWVkeSUVvHREeW46O4uzeeiH6K/6r7vfCwLD+NfTvKnh1vuc12gm7GWp5hy3sVWw5SIBFpNLe547Hpj7iMkNz/AkEabCYlGT6WmT3/ph4YYw4DEzFQawLQVFjwWP8EEm1DWiyZ8sEXxHY7EPEqXLFSY9vGjdl2flaAoHeD2qzhz0Lq++KuRu893VqMUYqdziTA23u/t+t67FdToSHrWSBXXNrmdPyOYnyM1/ItNroOSjYbjV/LpehXTXGq38R7zs+TcjschffbzBGulzfX0RdYhMjfh9MROJXPbD9t8SuPgFPvfzTHkpaHJee1siLSK7pxtKw801siI/c4G0YOz7Iajh5TEMZEnoQV8D3k7j167OmGJr9jt2G/vdh4Q3ZtTmfqe24HHgquOPBH5+f0ukH02NgCdBPy57SmMGUFc1Sn9IVFugGlOgmrYVo/z+xeOmpm+0FIbeTcmqqf+yV3YlnRBu2XQJOil9g2tnJ+wPA7P9y7L8PX6YbRvyy7DQveoQkHcBR0UFEk1e8/HBDbpAfadC/dQ5iPml02yxI5q9IsQRB2IbGgEsNLqTHthz4E2gyje/s4akaezgaHX5kZcomrsmPDNTyE+1rHKA1qJ5IUdtJ83kxWAUE8Ch/KA1X/OgkHuEBIrQAii1w5MZ1OBLVdX7AmABLHrQHo0Qpjwgbt2ZhXL2duhjKQvph0HVUY6lhTy/MIDXsB+KCgrIjVwL95iO+qEIL/SgYriv3FQzJTsXjZvLWtjp6FCwGKP85X0Jz+TT/HoIa/Oc+XIQ4I+Hpv7yY08LdbWVSTNZyWJxidRasOzNH9JsiKyWaSO2gnoSq60vP48aBTuCl+RL0g/sxjEnK9HGG1qaLtD0b7AFlaCgZY9EhhaqjYsH5RDAbUQ6tNq1lVRwU75zpXDS5OhgIVZkiL38Rdt0QaM+y2uVYuQn3/2B8AWgIv9MoAeB0aPawcesHpxKmA6b6KsxA4eDIRLdwENzod5wln3B4uf5HdxrP33upxIkkxDOE4a+WgN8nPl8+MJS2MWXSsD5Mf05pVZtHu5JkYJ/GuoPPRSLv3WamxgElg63VvWQ6cTlssbQ34lTI6gMo855/iWING3JYb9KFRGdNwjqFfXRE7o8rJtDaJiGnDHTzGatWo1YNqpriX77GnmW9O8NQAXzR4W3lwjafsmYoJ9BCDw+hx0pab6irquoYCKiif1bcwf3YtqAOMvV6gOB0Ajw6Q5aB2oCv9kVUohKebrk13zMG8OW/0MRg5ninX7kH3uZ8SNUL1L76M22i1Et9JsjTprVaGSMtha451MacwPR2blXw4MsM56Bup9ICVl0qYHDOwFpcKxnLRL0M7j0ETkSRUyG46S3WvxcPK3YOrhSRE+S9G699Pt++i05wzz0a05bhP7h2bjivQ9SJNmNxU4SkLxDoeGG4v2MiS4CIRq8hUzhTuMG3/Gp1xtSB0EbSy997sdWY3RTOuDcLR9DPj17u4WJcFZQdy0y4p/ZCG8vZgCTVRBUqb6qNE9Cq6V+hRhFnRqeKvt4fT5ASg6rRNlzrmO5eZFQK1NvLUeslr+1DHN9nvE35/x/xAcecwA0K60SsmGtrFTTCYWgs1K71YR6uFR6vXVR1dV6vHhEvSwJ4UbOTq+wjq4eGZXxSc6CS+QB+Nnhnwk1/utSaXWD58fYlYOFuMROigtxOgS8Oj8tN7sLIv4me7I+gMNT1SyyI910zOyyoTSeRzOX3adGsaVs2KihS0comqd/NFrp+y20qbv68zcXGb2CdBIVtAgzZvptIyGcphVIzR5uI0xhOwBgz7udGycgbQQD3sOeKXfPBnz+FY52zMC7NBn3G6/fV9ujcN/aOPmfu0n0nzHnLxk4m1HaC3rskWr9oOxOqO5ptXILVR1zO+teWEOxYGnJf1zaJpgXKG1VShmZUDUuOtcxxSfzDQXPdqILJgd8NBj37QQkVVl6Nqd9vbjmsZ/OW8H4+R4ZeYII+y+YGu4u7jTPiiXBY/EMgx/KU+3jx/WygyVZcxyiqh1Ro57/u4ap0tcSIuxOJiFK84D/gVomvhe7QeRwVWWNEPfZov2LQu5h6hucqsQxrN9Qx1jY5gVaaLlPu9aU3wqblaosMTF6khMEKHKwRo0d/bCgbva4XuWHknaUjc77pCvJC2qGvNQWImaGKh54LLV12aOmt8j11bHLstZWW4xmT/nG2PRw+l208XqxYkUPjyfFO8kREL4PMICDwvy3gNSseSukLlfhTwr+W6Ih1WGn+hfA65xLcemkyheYBBlgh9Q65C0QZhJYKBfRd27boEA4kkvgBOvLTMMl/rRj/BAiAiH6yVX6VArq5dceNiiqMGrUcT5VStGJJd7EArl64KMhKaiosloyKv1TXNoKNyW9Rt6Shb5Ak7Hjw92zQdnVbMcvY9VOgH27XvvnaIEoz0Sg4n0Zx3dBybffM2WGRw+QsfXn5SV08GnMplC5vr0tDXJSLLWG+9i0yPpRDC67LWOIk0712hpx9wIlTDYp1EVfHTcVERqNeTX2ifV+fnqtyvK/c52vngqOvcCgXj8jqtfnxPX/KcUuObwXweyafxbNOhArShWzmfKoXQMIIt2gtBBzPJz9q1oOKBC5hZxC9Zr5HLjMxM2c3aYKi/jpAyS4b6DdU7S3JcIM7AZew3YTqCaI7Bqsd+4JrWBN0FrT51u2xPRAKDWMNM22VsEjRIg80o9kbG300TJrtPf241ejUnkvWxEbzgZ/0AMxiX9FxRU8Ow+Xw5QdGZV7MXGnpiKFspKpe4ei3+l+hvA2Nu1MC0Juy2WOI/uZs4AoNcYKyQ1E14eXc3AG1vcRt+uuNsYQZ+Adrb6WIDkOOssKn5jPb76pknzjSZL2eIGv8V7EU7d1BU7qQReSTGynm2wTM2XL5ZazYbzTrvKyvRi8KfPHhqvruXFnDrry0tt1Ff/CNJ5bpToHw4czssBGq/h4uZY8Dpoldv9+OCA+PZHPVGTv39GcltW9WhoCatKxtmW3U4WVpeg5E32HF+3nB4RDaihYs+8k6IHSvVru/ynCLWh7j7JjAlJNAwZnQcSxUhoaExM7/J91LCBSjaW+F8rZw=
*/