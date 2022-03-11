// Copyright Daniel Wallin 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_IMPL_FLATTEN_HPP

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_required required,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_optional optional,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_deduced deduced,
#define BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY(x) x
#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM(z, n, data) ~

#include <boost/preprocessor/cat.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub)                            \
    BOOST_PP_CAT(BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT_, sub)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED(x)                    \
    BOOST_PP_CAT(deduced_, x)
/**/

#include <boost/preprocessor/detail/split.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(sub)                        \
    BOOST_PP_SPLIT(0, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(sub)                             \
    BOOST_PP_SPLIT(1, BOOST_PARAMETER_AUX_PP_FLATTEN_SPLIT(sub))
/**/

#include <boost/preprocessor/tuple/elem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_optional(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 0, arities)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_required(arities)               \
    BOOST_PP_TUPLE_ELEM(3, 1, arities)
/**/

#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/repetition/enum_trailing.hpp>
#include <boost/preprocessor/tuple/rem.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0(r, n, elem, data)               \
    ((                                                                       \
        BOOST_PP_TUPLE_ELEM(3, 2, data)                                      \
      , BOOST_PP_TUPLE_REM(BOOST_PP_TUPLE_ELEM(3, 0, data)) elem             \
        BOOST_PP_ENUM_TRAILING(                                              \
            BOOST_PP_SUB(                                                    \
                BOOST_PP_TUPLE_ELEM(3, 1, data)                              \
              , BOOST_PP_TUPLE_ELEM(3, 0, data)                              \
            )                                                                \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0_DUMMY_ELEM                  \
          , ~                                                                \
        )                                                                    \
    ))
/**/

#include <boost/parameter/aux_/preprocessor/impl/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                             \
    r, arity, max_arity, spec, xform                                         \
)                                                                            \
    BOOST_PARAMETER_AUX_PP_FOR_EACH_R(                                       \
        r                                                                    \
      , arity                                                                \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
      , (                                                                    \
            arity                                                            \
          , max_arity                                                        \
          , xform(BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec))            \
        )                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC0                                 \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_IDENTITY                              \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_required(r, arities, spec)       \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_optional(r, arities, spec)
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M(r, arities, n, spec)   \
    BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AUX(                                 \
        r                                                                    \
      , BOOST_PP_CAT(                                                        \
            BOOST_PARAMETER_AUX_PP_FLATTEN_ARITY_                            \
          , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                   \
        )(arities)                                                           \
      , BOOST_PP_TUPLE_ELEM(3, 2, arities)                                   \
      , spec                                                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_AS_DEDUCED                       \
    )
/**/

#include <boost/preprocessor/seq/for_each_i.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced(r, arities, spec)        \
    BOOST_PP_SEQ_FOR_EACH_I_R(                                               \
        r                                                                    \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_deduced_M                        \
      , arities                                                              \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_ARGS(spec)                            \
    )
/**/

#define BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC(r, arities, spec)                \
    BOOST_PP_CAT(                                                            \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC_                                 \
      , BOOST_PARAMETER_AUX_PP_FLATTEN_QUALIFIER(spec)                       \
    )(r, arities, spec)
/**/

#include <boost/preprocessor/seq/for_each.hpp>

#define BOOST_PARAMETER_AUX_PP_FLATTEN(                                      \
    opt_arity, req_arity, wanted_arity, specs                                \
)                                                                            \
    BOOST_PP_SEQ_FOR_EACH(                                                   \
        BOOST_PARAMETER_AUX_PP_FLATTEN_SPEC                                  \
      , (opt_arity, req_arity, wanted_arity)                                 \
      , specs                                                                \
    )
/**/

#endif  // include guard


/* flatten.hpp
+67hD72KR9ufBVxcIXBATStLTeKAK7/aYcILCp8NJWH0I1q3DT1PKL7SFpPeBQnJr4/4NdmkWLE2BTAq0akHRtrDPcVvvEe63a/s+kvC7lITdb1FHUm91EuAwdhxHFp5fCj3bx2KeoNO/OV5wA6eWnFnAhQIiFHZvF3kr9p8Ci01CLCsk6zBscFvoiysrK/tt40FSr+oxZ6yaBb/7mJI8YhDW/wH1fEumdmF2Hy8lroTs1AOLNFZaRmVdc20UWBW/T2IOTbD5GQdmCSjYL5IBalOBWkPxhY83xZStAHjOHY9+EU0/lf1VRQIvzddilT409Uq/OlyVAURvFqFoU0dkQoPX6VCoGqUQUoqnQ9zyYdcgJkQGnB00J0xCtGrRdxaSaUrNo+w8/PFeAAC958xoBSYb+4AKnfHCnLrqfEPI2ESsu6BZiV8h2aDDOh8LTK1S0bpmfu6V9C/UKXtMXHE2SYX5j9WeC+R9JA3Ql9weIFkrDyrIGmNXqs9hU5f9bzDtD/KgHXQM7xK9CoDdvijquiMGCb3YtZJWeLOr201yUT0p6ITSW9KWKcax9tqfjAI8UX8dKC99h7uhREyztYq/kcxyJ5II87KLB1oNXeHNJOICqjd8zXKa3BDoAqd6ljOhLCJ5YxFmctPCgXhkQA1YIDha+l6gk9ObKNPbIXivvrXNrRrhZ2nSL9m6DEiu1AZje4DqI1WZXoYn6P2pH8WGZIf3woMNZ4l15l0V8tD9SaT6/g02XXK2bDcJLtPAe8tHQ8+MUucNhRbuM+iaxEgA8ekbH9veVI2GRKtI7s2iQNMfXK/UEqAFyc5WEtPtCjg/bdGzKm8/MOn0BWEzjFahUlWbLx5q/Kr+ar4KckQE6uHUNzOiYTixqA3NFyHefOBGZDzFviMgfqxUVEl/UCHQBERwHqVhnzUEBnjO1geRicITrPyWaL58xh1pHysgRqfisKBvDy/DTuxRjsRbUdE6wtit0dw7T44ol7ZvQnmqVdgGa4l51uAH3/xMJ7zk/7egSegEKU872HxXgycCpujd2A5FR/l/wXF7E26Pjr8ZiBZIlcIsCbwzncPawu6NqPq8fM+pPnEWCS+e0hKQ6qmcZtR2QKFTa4de+JEYpxNHp6I/UHpftdfjcqHKP3+5mVRAvVETF7x4ig/9XIoKhbv1yNiF3LltUYGnHDPTjN78oWWouhHBESI3OMr4C4KTKXg184GyQprgAHMc50N/vhgmTVsk92tQELJGKy6Myi1kl/O1q0yw09kqqwM2AOrUBqvmkic8hDnhulesw6wQHI8anix4ZT4aMNjf7xh/ECmyv+uYdG1qBeZl28TI/MiPG6D1atFzHDh/ay3t+suLLsYXLnaLEK/22rux0Q/c1JtNfeg4NPxIiYRlgbJLyLHJb9IGb8pO6JwX9s7AT5M35tpxvjv92Aqx16AKNMp0bQJRTR758ArIzBvlFRgFjbWg88Wiq3+jqJT/j5spQXbWIn6cFMna9p4aS/2iR5vefJKSigOtzMGuHU2ovNKlV2tkScSkIf7XQmcSMfoPFQpnOXfY1QznVrLdh6r7Emv0Hm5QSS0FsBLM3wpJagMLPDw/la4FkSGc1croy/RKpBqoyOAq91nxAsD4ZQrzzS5ziZS+CHOp+zFwPjYXolkcRBUy00+07wCX5zy5jbaNduFLoNWLjshunKtd+ltjT6CffmRrQbdaNmUVGeDreYbTD2u3zzuVnQCpTBHlK5U3N/+Pj7Fp0Tdxwu9wZ0YPIs2GizKblqUrbAqW7M6WKdjJ61LLziEu9toZR51/uD3wfhYGu4xY2Fw9hszlXX3IA2SbcYduxubI7+5Z3Dd2G6sCIxXUnBsnEfeaaFkRmZc1wDWTP/KKLV5ZioCCiYqK8+NjcN1DvcJUiUAtg0GUije8/bxgA92Z2A8d3LRQxLrNnKoxTCd91BDuG1RosR7TAiphdJEx26c8qqxWu4Uhrac6a620TvHQnXfLA9ztQMebkvf7/GKJrjLGVJGS+3hAaUrSKsD/1PfpMObYAAzZQCiqzxM2t2dKQhU5R4a/ziE2aN8GAykUFahD7M6HDvpJFQ4duJmqbqZMTwONG3YEH6mBOw0RfivqUEOJFOCkbbgVIsRd9kh3vdLWojRLBD5NkX9lrFROLHNMkvF3GsHlPRmo8AjNFtYJXyNY2cq4py+vnjCHKthF8g7KU+KmGvCKQM2oI54HN4kgEaHowuWthQoQfJqiOdDagMvs7AJKgXurzOIOaEEN6IZaGCwlx7Fp+I9PciVdersoNY0pvqeSPUUffVAZR1cv/4ekX5JoD6PJ5nwrPgW1JUh63LzsDg0hGIfFXiC7vX84IXzCvG7QfcWh2uTZGLuDSTsPyu7OBxiChL2WKrsXidOTFA6E6wkvbzrGHqutXU/RclaDfRvU/T+bSaVZFgnFP5Ij6w7RglgMU5VV7lQ3PGlq5C8CLqP5UNVJLsp8CPxU+v5pi/PK/ziUJK1AAu/A0fUcS0le7nvLx2KL5PPX9ItRkMvn9E3iG88/q1Cuqq1o0yiuer9qbhowLLx/vFh/HR45NOoxzN+ncznaV/PsOCn9NGnZvhoIm+TdB/FaR8ZgKUqWfEdfRSYP5Y69GDoliP8FfiODx4aTSMCzX6kYpdCwC7eLBQ4OnYjnLa1mC8FvXJQsu8UZcEX8RIJYGoHNrYOWjQBdIH6UKAzbungrHpHjlXq7XB1+S2OAKIo9BrPlnOsUPHjD6Bi5yCpD9QK+IV8UM5BQrSe3iRLA1jAGo93e55aYVODPMOeq/a8htJZHOLhxzuUbvQf4Jnfvt4hpMJJBv758xrBGOP9TUqm6iqzCXXG7LKtFj1E2VOqvGMEawCu/QkkEXuwbDvwmi3Od/wPsXkWNi8DOPqh/gXOd6TzzoPSh7ZdOX1su4rhRhHRPZamyrNb5dlt8ux2eXanitzJQe/qyF2hqCAFEYWxvyeyx735mOdFUMdZGzui5NMHilFVScH1wkxam9JDhVoQg7f/IayV/aRywfOXRscVyJev/VPUaBlqHIln/oHpqv391cca+tT5tXQmfA1/5vOQopRZlTKLkFFrGmEMOdOtd1st6tIjENz2v4CgbywEcXoI+v4YBC9Zz40kg2hY/9Pfqp0Bg5Ma4Zv8PdiR4nmhh8ehSke7m0fFhHUJcDORkbaavwPwebZaN2Z9cJ3J6vDI0hlZOqsMSEUkI5AO0HOPk+UKu62OTFjOaAgStU52B6HmSovC8MYIXwcVBUaEiqLKT0WVqjFKgAicQ/wgaj5MhYivkDjyxRcWRojEUD0SjlHUD1d5BMGKa0BgfeVDfBPF1BF8G1ouXO7pFrHVIDvk2LmGkmLPQnlt0yNxQA6dTY9fT6YV/KSLnxo3Z3uq/ZP4+tph9lMNHx3g1UCqs92d2Bl9innOAuuQMGySXS0nXS2ydOpj6dSnDdwLNQOdPar6oHHFRl+PuZcuZ1Nt6v3PEg+UZxr8PdN/kKm5sMV0Sd6Jv4I7iT6oFC782RPyiMU8hZRZq5h2HCVlyszq0M2Pbt5EJ8x96mptORsqgPVs69aezxzbmGghL9N5xG91EFwV/ZxHpDSW50nPy3MwLKkaCHTLAZnmUw6043RQOXOdfRnnMNzXZ9bd1FgNWcVDfEpAd3yTuoyGbv4gzkv+MY6qVP9w/hZm+U7wotwOB+aotPjtpA7yCu0pwlqijxOLYRiSmqYkU+Awd1ftASmet/+aK8pjFj5MaH6hj3I7cITuQgrKf4aVWVhOGrvDOcUsjYVT4MiZ4M+QcybADOVYUbmmC4+TAafKXsgfPS3i/DTzBTeFMLj2X4tL5ulsd0YBHF4M/+RYel5hux8mughlhiiSaXK1oEwM1deuTgBguYiWXSikF5RXClDsHazMHp5DQacWsVugBC6uvsyT5sxPW9zDmT9qqZCsetLk2acC5WkGfwbLTguuQw1P9beo4lky5DaDYjA8loQ8uLsFpXXvYeRM6qy2Q9qiuM4A5HIxWlgfwte/fAZuCBiGxcAb1kd9OxtIJlfIdtDVc3KGY4e4elBGp3OrjWqAbz7L1ViXD19QolEJyZZZQu7FxDxmco+kdAMzPcoiM69TFJIksmo/IdDyfs5q7LCyJ5MtuBfN1Y2hMevVTOWoEfOka4FXBpEIYjxcDIEfQgrKAJ/NBsxVnFVfEvGE4zcN/0Kf0OEPn0TkiX2eQ3kiOkv1QAEvx0iaEcVJVOHV/nE76jxGYNyHBJ9B25MqQ+szRDZkVDQiMt3u7RKc6HdwlErMJIP4h/mi4iiySP3oBFGuGHkt5ocJj8Su8DWKCTatNRrUvDFqQhnyF5lTRmaQm75StCgmEUAKCnTnQu/IrxfS/PcYEsdMhoNg8ahlD0MZwRiNhAVdOP7nXZDw+3LwqbuwtftEDwth3xayXQ9T6BbMZZ8JTdGezmdz0C6c3eKAUzcgP/gUAXFu9AXA/9D9Iegew6jNg0n4K5oQJgJ6QnohAgUgq6XafJeQ+qv3r3Sut4hImNuaBZRXpvOolOCYICWER8G/aTJSefdejMEr1KIOpcDGyY4NuraSdCoUlGI4+uQ1w4+pzMCmWZwnpETHskwpMWzBPyY5P9PZJH2KgXba/m0nAm/xwqejwjt1kWgKU2EuqL95zGMR/cNDBvpaU+93kh7FkW+W+jtPdwNhLoLw0TyAofw/wwDH/f11V8Ag9F+jBAwkz5sdlefVQDmAcJ657bDCML+JjvKx0P1P8M8YOW8sGtN92Q11J/ntV84zRV6wR81LYD+SiQnqUfadFSIVnSOsInXxWYApdK7DenhbR9K2m1cAuwv9vYLTrbwFyjAfhH8Ku9uiC4zkxZdL8OURPpNgzVJ00NqvDu08/eEWW543/QMjwWSdDA8IzrDyIyMuIPkW1RY5ipOlf8E+vvAF7uOCmF1cUBDZxTEhCrTDRKMaiECiKxsJ7MfhDijQqDq43gY8BUix0MIm27M6wnbYG/v9YbE35mb4ezv3S61Z9fOETg8je05KdSzOlK4HgO4hgH70WCHJ3aTFO6VZ1nW6eS1aunZGVusIX/IPRbVStuJq0VL9BE294igYqiUmDN5KFHPya86TocvxC7EYNUsf3zLi17unD9lovtqtss5XMVI3uDKDyD+Ve7DVEB+zUr1YrneupItlMFuLF0vQXK1kqmdu+/ALwiy6IYhXmKWAvUjnHsjjcC5rrD3p/ydJyLvYEEceUgvl9nA6URHvAhWBoX/ZHf7BuPFyrHqDV39CoCrNgIEGpfdqT0p/BfwyT8zJ/vA3ER3PXg/p0BKz6kNIBWAzNJCYlj7/n4zjbJo6jstrYBxv4hjoSITTCPlywPuAeUvMEhEHuWNjjHN7w05rIQhpapvC3xw+fFjbB15Y9Cy4my7KlZ1yZZfGEHQK+b1gCLpw/Tv5AxiQYS3KdZ1H/fGOZROkHoAzhjjKJ/gHvrXiEBoAHDmPmqxtQuofTnfQDPhTHHtRDix9jE0lQFO41lwwdfvR5OvvaN8U9a5vTY0RgyO6+Ei9sz9/DC1FuCFAcjSg9GtpYu1snGBZrEJ85SVbpaTAbuRDDFW9ApQMUfEZw6OgshBTQWVR7TqgYHNO0WYfiLx7gNJDeyOkdDgx8DIWQaf0x4+RAz0q57IGKoQq4wQQJkF60djwuZOe5cqzPB1VyG1Ckg+sFxxiq2N3MvEtSNnUdthqdwvRA/0VcnkAaHywbKxK7md1yDux1LGTJjNBiN+BpYrQ/XjIm1ycTGSoJ2jg1mCZVdcAljp24hpqDQgscdU2DnHzN+idUmo8A9jk5yZhJCfCHFRynHxhxxVaSsmubDW/1YEuDVcGjHocKbO+x8nlpdarmQ7vW4bF334QUsLDtfH54reiEoGg2Bp4GdswqKxL5dnIaIZro+lWHV9Hq/viZZpbnyHQNNYbZTjfxTWsmmCQcMVHt//I0EJ/NsTCn/+BgB/juOngv1WF/z8CJJ2JLOf/ZLjSGV88vANWhRjhqebImyVpGIRM5QsR4epFj4L5eu4Lo0F3kCbqDpL+GIWDHRjFlqZVSnEEaEMkOQhM2JmBFNqZ31AsT7FNGM1o1vvskvNb//Dum93ZKdkcu2lfArbLBpYA2IKsevkZLHK+o8bAg2fawIWZtvX1ck6m4xlMf+i/ZabgJVnOXWyGJz1navqMPN9QYjX1XKg4a/xiUZyBuFFYw4fOoXgBKclDsVeetuS2XS74z21tOGPv1UBeHIY4nf16CGUuMJ744FLUeOlEWqTxQkk6tbgVKAlNbCyWYqc4yPuAs03FyTiE9rM5lxXF2SbZmlyYx1g9Z36TXNkM1eID+1Fdp3MajmrVqBPqg2TZ8m5qfXdeZOkdlc3+Uubex/LNQBYE3M1IraUADYExrw2OGRa/NZdsaiz8xEquQI8B9z6FBR4WNit9qOZZZnAWWvyJoiaAtU9ZNAqWcRGF6mtG16p1aM5YUqxKsu9s1W+mSrvBn8y/asNjA0OOGM0OmE/+6REFb4z+X9t0KEjTsCLOlUxbjCd1KopMuw/gm+qlw3ScZBuu4+Q20kISx7Ni5vctpRXlsKJnaUXZ9FSPryu/ND7q63AVJf5jqhI/5pog73TUkON9QPoEij4KRdKgGAH7NbDPLNfDUbdrsOMBOiGTxIPO3A1h3TQViOC9QgfHWgKXE22rtuLhTgu+vSrZnhf+SXY4I/AK3Uvh0UJ5Fx4itH7h/mwt/jU1y6QbDPegxO5RZWHtgWU/piykVzplIVCsN/uMpPnj/RtCSGnddvY/MrpktjUE4BwK//0U/rsV/rtT/e86+G8M/KeLE4uUixdIlydU0uUxQbqwIoszpdpfzNZiaTBfcb5T2Te9eVp+NnCnZlz4xPu6FEbfOFeirY6Uiuao6svzP8eXgiqqSsyT6WeB8iY1Jqq0f9muxY/j/wxEmZ0shV103Jbxz5FqzOu5jr2kaLvT9rbLWuDhf5wdZ5jLWsLjhDrZw454FzoqrVUmbzjOZ+QOIHF85XOcLcvjWCPFIiF2Ib1FzA/wZU3IhG08HFJ0fA5K2THYR/xevE340Qt4RApjbxVhzmOt+wBVKDvNESPUVsNuyvxVxCkW5YDjy8hRlPOKx4E8fhONzsJDicgrBEpVKTOzW0pXTCbVpNSqDKhAEq9D+hS/KMcvUEw8gLnbeA0wA6Wo4/QUwvZ/fJiaboGj9vdxrLmfm+PjDI38lSd14blw73r5qoqvFLYXZz3rZK1SdYdYjPTGvHKnutBZYqGVsdUqhTp5MHFqQ4icxsBiHu6q+kqZ4jxd0aAt1MQre7qWesIm09X+7oYOJ4sOg1OTjbC5frTPI9dc0ed7laLPvVqfzdVRzYiVIp1/ZNvVXNjA7V7CD+1C3dau0bqdeK+1R4m4TtZGzzIc+oVfK6grgvnOBzThRkP4C5icjBE02deoNPps6BJYa2BNxzBj8Jl9cNJnFigeazBAJrWdQogLSM6Dapy/Pw6HE1ic3ftEZESpC5rpgEEleFFM47E6Bb3Xs5rB5jKYDakGJgEM/mRdDbq/EwOihsixS36ZlroO3G9T4igy6VOc9GW2miB2lZt6WwVsJKlPcBUaBnt4Jzq69b+tEgutWqEbTgT6bqm7tDVml7byD1EeuqsNkdkQ2qVOXIy7U9ktIlZIW2SLfgYPQkWEIfU1H+6iVn4BmuDL4nArDlmBiyULMCUMvxw60KUodWW1arzn19E4LHw99XS9CN1PZtYpAdWCMJE1/x+ZlZVKlkgAgENLrX0LfFTF9f9usgkLBHfRIFFBA6IGEy0afGwXFIQN8ZG4IZKFyqtWadzaFmQXopIAbhK8jjeioqJVpBWqbW2rVTQqYiJIgiKgogRIINpUJmzUBTEEjNz/+Z65+0hQ28/v84fPZ3Pv3HmemTlzzpnzkKnwb9YZ3DNzo3xvMVVYCuFx7ZDhBIhnrWxPv8U1wPIBoYhUTYACgQJDJVXsuj7TUXkPHgRku47K3/cHPTuKnSA4HvglvoSgTOKomdI/KtgXqfjm4W+j+ZsL394KUC/4JHsZVgTsC0j294cN8eJTTCXDqABGjv3lt7dT6hLYNBzdV3K0yatXoax5c1as63COJceX444fulK5CIeHNBjxP7203dCqcuhN91R6jXUT6UmZyooQxIwuT2VFsvBUCr60cfyzUQvhmkNwIKvseq1qLq4Y+e5RexP3Hu6GRSPdfClZPkyIOB+q1vj007/s4a7VX8E+BI7SclfEhqZfSRW21/WBCQR9aRF32oVFq/Kiv+sg6XEV2hxVq/vgkn8Ty0HV+HYionaFXfSBy1RHJWjw0jVbL3Can9ctwTinw+2PXtV8wojCQEaCBw1jHT6YCYJyitDzMeg+Xgrovsg7T4RWx9IXczpsR7SqUgAh8dA/K2SklCf7U2aF3lzNaKBfA2c6FdXo8F2XvN2tI2VxP8F/w0m5W8Sji9insqtieiBTvJPN85hd78q7qdwh8qa6G8vt2fVWBjlcOtiD4wVnEW8BMFpVGxhs/qxVSey7htHaox1ojCYqQn/1dcjCq4phmWtYdZ5AsxCDoQpggLLaPbsJ2m96+ULsz+wSd5RyDy3y7Owq+iEkvsk0+CA3k+DBAS6+vapIwc1MgH4cVe/hQFf91BdxM7ZYk/lalZ2TnJzEw9DT0Iuyifo6W3QLzHWGz8GedVS+Bz4YSoM5FnF5sB8rCrJSA23YlvZZKRx7W9dHcaV38K+aHDZohMRcLHDCx28YB2OqWDeVwYCU36PqVLHArlVN5dUGk05XRY6j6i9JGPxoR+W9eHgL1RLxHHolthbmz8FaYH/65oZ4IfbNx99e4XUym7+9GPvm5m+1sTXkqhgRpI0wN5n7FrqD95Oj8mxovnJhfR3gqPwRW442rfUmKmyopkUrX0O2JTeKEMab7GnVCjqSuX7W9ahjjuGV2N6AQ4DHCDsIHjD7YRH5R0qhtaNPqZtc5BW8IlRmw1vqM4sxeOX0coS4GgMtnH5TXZy2OFV9MzFIzzQdv8kFbVDgo34RSfwWmg01pJl+JRLhetZtUbgmc+nQWvyaQA6txZAs7Y8kwSlVfKu/h6gwXXqenRDhCCO+01PvPGiYfZd/Rh49K9ZJjbvlbox280dGhE47qn7BxRi23IDQMSkKwuJRTFPyO9hx3bwdebzvafoRvPE=
*/