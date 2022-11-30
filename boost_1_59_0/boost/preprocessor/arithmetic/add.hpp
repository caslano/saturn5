# /* Copyright (C) 2001
#  * Housemarque Oy
#  * http://www.housemarque.com
#  *
#  * Distributed under the Boost Software License, Version 1.0. (See
#  * accompanying file LICENSE_1_0.txt or copy at
#  * http://www.boost.org/LICENSE_1_0.txt)
#  */
#
# /* Revised by Paul Mensonides (2002) */
# /* Revised by Edward Diener (2020) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
# define BOOST_PREPROCESSOR_ARITHMETIC_ADD_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ADD */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD(x, y) BOOST_PP_ADD_I(x, y)
#    define BOOST_PP_ADD_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# define BOOST_PP_ADD_P(d, xy) BOOST_PP_TUPLE_ELEM(2, 1, xy)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I xy
# else
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_ADD_O_I(x, y) (BOOST_PP_INC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_ADD_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_ADD_D_I(d, x, y)
#    define BOOST_PP_ADD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# else
#
# include <boost/preprocessor/arithmetic/dec.hpp>
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/facilities/identity.hpp>
# include <boost/preprocessor/logical/bitand.hpp>
# include <boost/preprocessor/logical/bitor.hpp>
# include <boost/preprocessor/logical/bool.hpp>
# include <boost/preprocessor/logical/compl.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
# include <boost/preprocessor/arithmetic/detail/is_maximum_number.hpp>
# include <boost/preprocessor/arithmetic/detail/is_minimum_number.hpp>
#
# /* BOOST_PP_ADD */
#
#    define BOOST_PP_ADD(x, y) BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_PP_DETAIL_IS_MAXIMUM_NUMBER(y),BOOST_PP_DETAIL_IS_MINIMUM_NUMBER(x)),BOOST_PP_IDENTITY_N(y,2),BOOST_PP_ADD_DO)(x,y)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD_DO(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD_DO(x, y) BOOST_PP_ADD_I(x, y)
#    define BOOST_PP_ADD_I(x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# define BOOST_PP_ADD_P(d, xy) BOOST_PP_BITAND(BOOST_PP_BOOL(BOOST_PP_TUPLE_ELEM(2, 1, xy)),BOOST_PP_COMPL(BOOST_PP_DETAIL_IS_MAXIMUM_NUMBER(BOOST_PP_TUPLE_ELEM(2, 0, xy))))
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_MWCC()
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I xy
# else
#    define BOOST_PP_ADD_O(d, xy) BOOST_PP_ADD_O_I(BOOST_PP_TUPLE_ELEM(2, 0, xy), BOOST_PP_TUPLE_ELEM(2, 1, xy))
# endif
#
# define BOOST_PP_ADD_O_I(x, y) (BOOST_PP_INC(x), BOOST_PP_DEC(y))
#
# /* BOOST_PP_ADD_D */
#
#    define BOOST_PP_ADD_D(d, x, y) BOOST_PP_IIF(BOOST_PP_BITOR(BOOST_PP_DETAIL_IS_MAXIMUM_NUMBER(y),BOOST_PP_DETAIL_IS_MINIMUM_NUMBER(x)),BOOST_PP_IDENTITY_N(y,3),BOOST_PP_ADD_DO_D)(d,x,y)
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ADD_DO_D(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# else
#    define BOOST_PP_ADD_DO_D(d, x, y) BOOST_PP_ADD_D_I(d, x, y)
#    define BOOST_PP_ADD_D_I(d, x, y) BOOST_PP_TUPLE_ELEM(2, 0, BOOST_PP_WHILE_ ## d(BOOST_PP_ADD_P, BOOST_PP_ADD_O, (x, y)))
# endif
#
# endif
#
# endif

/* add.hpp
AQ+RBQrD+1b3K29tdWtEd3vosamCf/86lfD+/vlCqi1pOamshSs3MN5frrPSRHMR3knk3MrePlfBrHSDH0wYdVcKuHH4gCVXKmHCno8FNX5gco6Qea++C/RQXhWhGZ0KzuMrgaCQCsW/EJ5eDVytM/biRz2wt0ZHk+wYN0xINMPtoi386R9/n8kO1F0N8Il5z6ainbry8RxVgkG2eiEC0Rzmf9EEHrR/UN0k4x49qSzgzLqQSrjpBdkdmxHNzUFA1mx1V1eylPpQ4Uzez/fM+TWA37hFll1FejJj3ejDjuHvWRdMiJU5CZQZmf12seg4tSVT1MBc4kdRyq1ALTS+2RZN1fSGpaGybZtD62RbYMDNeAPD/p5kXjbp7V9yD+k83iKa7FgZjo86k9Wwqq9sAV39EGwfO0m/FzbHD+nTcqsK0yMNuENefMn6QuxP5HpRfVaWQouJdVSSxISG3vGYYC3diyDS5J7LxRjV++ywwvHMuWu8D89B48vQWHDLnEeI+gUp74lagc8I8vtX8SB5IwdCeWJ7iiriAhTC5QikOtEaM1Rd527CuwydB4qCPj3JKpGejDpS6NCQX/g8HJK3NUt8UyXxj6iV1kV67xe1i852raKfJOvS1/aUdtlRsCpOT4wSb9b0P0nqIXcwwLi7qEwtY/PuGsne0usLYIlteqXWhNHstg4SB0nKDrQ+S0igFJvFSuTov5ZraQ6zEbvM2bziCB6GYyriJNtcVkgl2d6uqiQUTKrLO6rI+65xj+U2r0LaiLSkN4k4pInPIIsS4fYQREYMd4UKU5lRLdO7OwyiBeX7iXR/VJMMFdBB8L4rTIUURzFy59wx0v5tMtOldhQmdjFi22tfln4Bnc1Y1WW27XKdeg+oG+XQjTs55F6VaGwtUaSbF0l97ZXvtl9R383JJZ+1uf5lAwMyQeiW+LJzcbmY5VhiKS/lZ4KtMJeXCrDAVlrIywRZYv0NcF39fb/Nfgp+x/1tauRVEDZnkxvpv2SUFzVc8rL8K+iQAgpQAnkLa9IMhxNPNbm0NYLHFEoSgxc5AHm5NtaTeHHa6M3xX5IH4/E3Zfm6jBLx7wXs/6+pc1XIOGqMN0F51Jw3zVFs5/YFug73cJrtFmpHALObRav1XhDptTVA0s3NVcfxCGnguwetMFG3YjAMfgrdmIPLiJXa/NC5na/JFxMESdhR33fmELq1eH0xXw7XvRCcaH1WHkJ/lLmlwI7gv4gV8UjPPAJ0JN5k1hK4fU1FrbXw9xIUnTrd7/UFsgMWmq0cjdlZPG6RZGrCh2y4iI3Jfot0+yCzP8VROFTMBAEjigExwqqKqQlhFYkaxyMLxCc3Ql7xfpHAqi7XX4AytrIxVH+haaTETtJKTWknqLV1ow+aES+aZAxJsqMgxE6kNPFUvebZaYFb0lPUzhEySozeyXGOgjc31mTKeZi8qL7ACDlGgN4Nm833xLXh1rqV+CRFbIPXlkBcIFctbIcIS03t61nMUNnd/H5e0DY6hDII0G9IxpygQXSVLDOUyd5WIYykM55x42+x0P9o19AAkG1k3npd9BIfxnIaOBv4x1XrU8yp7hIMHAcmb/DewScVZyeVH2YORxVyvKLfnG9H+C1CjNpxhmMyzgFznY30V98mwABySV3lPtFCKXZk7puSZ5JnmN9Q3AyXUloH9p0PgzgRiG6L1lMSJbFflN0Ycvo00OvxM7OAeuBTVWIcXdFV7JRnQKP5Ld4bbtL47FkDVQTwj5UFlIA4GKoPmLjiWiqPSkRnPgkD9urZ/2Fg7SAsxJunslYZqLS2tiZ3gESxfSB0cnz1D8meOFyWrqMOgK0N6JdMz4TA2/W2sSjWJp1lqmFZbgmIEYcNNswhNEXbSNBE0PhnSbAJ7LHs9MMwGKD/OncxsZmZrTtwm7nPHpT8aV95yLknrSOuNbjupVygm5CnoX5DtEaw7Rh1iqrMoVB+qd66HhXOLAYxIOvs3pqkorQiWr9xGG6Fu8qSi3/NW0q4A0Cdrrn0cwFAhDg84XJLSi9h+Upz49YHZA+lPaV7FJCeeoQKK3HLjw2ZWg7lJFmn8d4G1xQweciv/5DZRIwkkC0UaSJFFYeICynecIJg3tneB1MdooKr+/JP6QgN89DVEf9hTE+xB3CPyEN4Citew0905mrAqrJQy8JX50/8K2NIyddHcS55eHwmZay+NCDtpHB3j0p6YyCcyPw4Jmi5Ynw6yJKHYtj2fHBpAIqZJT0jaZhvDerRec2FaArJ8Uf4c3WRAJSR2BJRbrtVA344nHjEzNWIuevX8KampBm5we1zaoxL9i2dJf4peLflhCAmYxgSbWxohIbeNcyUsTVwn61PahLuy+HB50N0y/92ZnmxPuTgbZMXpN/5WKey1ejkjLcJa7dnuvVYyPzAvXCgVQZW8nGcPujx6EXtySnwyPiB5zvsZHAFAIzl1D6IimHElAt9Y7IxoEH6hcGzxgvdyn9QVuR6l84bLmgSeRZeW5a67CMOZd+00XPgKvhKcVMwzIxWS2T1xfrnohPeIuGeu6q0RRyL9NZhxlekNWgynrIDUSBI/A2YcI+8dzZeDLANoM8BTyAv+w8usx00vcWc8UHmJeL7S/YXt6HC+QaXwSvbtWWSpvKiPVD6Yz8pNl7kBpDXa2u2HKYCaMA5szwzJbVX/+dleujW4eIHBgk/xFViCbgQKvkSeTQqw2kbvPmRzKeHJmCEytUsSdD4cBnsX5rHjhJrihcdrSq7nfCGr1MEDank5nZfFzslRjWKrxCRm8hpfrbqB8G7Xeq7bPOhW/oNU19w1qB7Lf/8D2XTj5Qx4RE1lr20yyfEdGiNpmfw6nwSGVVJefzElDXRsCP0tvSz13kU43LQShfimJNcbYtiKbJg8RpOPfrbiwHVXRao5PjnTmHjMyfP78JYGzUs7Sq2oHtRv3i7VqhbajOUoF5Bnt0n48BsiWBR9L+C71fcXmaCT3XhIENG39+Lj1rmpWLx+6c5nOBm39CkWqL1RzYPrF0wf/WetaufZ9xdknaSUDDga+pvKOA4tS5G4xK9in0ClB/EGkeoligoJs9t5yqiXGmqhDVqqLMK6kKSl2ee7+GR8wKu7N55eZkN95j9qPELkS1WsBrK6VTInJLr7JqikparpLOkZDMC8RaF1dakBfy2ZSPXXFYAkayNdkZbP86DScl1diwbDmszgOO817P4Jy6k37g998tQzhW18l7BF9TKOnmfkEsqZb2CT6gVtd892/Kw37vQT0U6NWs+hqBsSqOCn/QXh/vbDwYh+jZcTdDqvRHKSnmh6zHlTcJzFxyGR6W0dUjGqUMov2gDCkQTwgFwY+tzjTzPrw9GA9pnlC3UDbgJ81ayJJOtOyvlw76ek7UqX1EI0HX+u7xbuu8DWdyw5hneCS3bJs9ucIRBBwDjNphUrjqzFLjrm/sY6oRVv0JhlXDIizgpgoktnjWtaq6PJexowOcnPdrO1UZmkVrYt3wXyyRZ5r96LTWsA7ZV2rXQD9LnpVm3H2EHZ/7ATPXQrBbR6+RMzFCBMM9iGdnjI5n+guNXB/nInPdn2Fgh/utL4POf/SR5sLBSvOL7nME972Eq4EFSjpjN6Iq71td70oi+y/cchgRQGgG1IVw9WZ05TROzhjUpi3BWcT6IfjFrWoxxFLaQkYV9nthPH/XgC3tXURny8Sms4jzozpIxS85u2AjFkoG37urvNGLPN+4UbQ9y7OitolXuj5A6MeaRmo/PW/RCqf2wPn3xMRgKN9gemazA7ZcjxdGAfr8WtzU9GfZovDGxoGDnmFm6cQCLC9NgJKTEwGgccQk2onCowXEFyh1SFiwUFMxoPMKZcgqG9MXtM463X1+/rrOOs3u97lmPvKcP5XKoejoxZFIaZHzZi9W1vK3FzoFPPKhw2j7F9EcL+gAX+U+bjb0ClnSNj/SuHURQRBnN06JheyxrCJKfVZvu0Z5PC1fQRec6R3OpnYNsI3PtSD+7VdnGzoIvKePFEf25Sd8yG9JLoq99ML/73rfT7k2xinLL49z350TNMdCNPximjS8KG4gmdgTmuzto0o/39265zIkSWhR7iGvH8j800luDKCj4xPk7WHWGzzerTpl8fKx1h4HmTilMa8PQlw2/dnwSZU1e9OG1vw+MLDuDUJGOAWV2WxiyGEDWjSUpqWB/5Cv+2/Obn67kVWpVS3z+sr77IfhcrOysQSA1zZBqfxRytmt4qAH2Ot+W/eNnf7y/HdT0mb2F2Xe+nkNd1OPID+w7IEpWOChwRbokyjiYlYDPUKYV0Kekp3X4DVHlpv1/YYXg4XaLW4FmyNm83aV+Hf6cnsRmP1qktnEkHe5gXzvSk/dpBmyT7krd/klXSoKrDRfpk0+ln4ajPSTOHZnt/6Z+aP0c7Mk3Y7bZIED2Y/Ows5GnMRWA7Mn24p2yEn+PlY3MbLVfezYODYYO+cq57CWPIo/4AHLrpZGbOUVTsY/6VNWUsuSQ8qWX7xAICj7LV3YQSBYH+PoRuarzyOXzGYfAROEBsq+bDro1FcWPGx6dy19ur70JJH+GyJqPENHu5/POiQ8IJftWuCXFTyjycClyNk1Q4Cima4WzBZfeLeGTTFifPLhJjJkNC95Jlv0mG8tKxmATnwhbbx3jzByAsMVfFOfGap+vzSLHeAm1TsufD5UTmyYViKRc6aalTGh2aWy+rOYrvHpwm9xX72jccGAJ08z3LYZns4KBkPoYKsD1TgV9NDpSd/xUsb0/SOLRjhKoMxJyZDMdlgkwM1Az0ATsyw1CfW4OVH9SWX8TY47VR1pur+uYnCGfuoX3AgDyudtaNvBN5kV+RrWWeEMLJeqsEKMy+Elw1pItBizXdHKNC6XesPAGinZ7NvbW7ArbSe64+rIdauWhuA6aEMry7lwxrBocutH8oFZyzYj+bUGHejwF19yVK1biHAWvAH0P26gljW/OrIqoh3aw82yf7/0axDUEzsimePRQ+l04dytJiW775z1Rl873V3GxXYb8Y2XdOk/IGaxcbuUrHI/L4s1ssWfUkvP09G4+aAwWnAUFv4ig8lHmNe5QMXxjnHi0FN4L5A6ZnE9+myC04/Ifcnjj9+PE37ufPT1hfw5sM8Qc+VWPVAIEYbE+0g2Yx0vRYrIPIlvkrRqTY3eL8HoiW+fpGxZnDl1fw6Ard+CzySDn7TgGs+ZVOtsOiBCXJMIInaWEqMczFgMalJ3JbM2gO4fWrI59wjenLVk8Id5BSKp+dKzOPxxrdvbhbD5M4oLgSHU4jp2w4iAKMxjrV+U04RXO1b6PAKNNERDmKLTcDemu6pDacWPIFeMkYDi71SXjAjpUkBcfJb3INMopcXsgedk3Srx3jsFUBDEbK/DrFUHK55IwSKI/V76Lc3A3eSwnz7yuwZeRUpH7ta0mVEsWYgv08E1809jsffMsMsxjE5C/7S4h+c/yHLmnYIZYI0m0+CvKlaccGVkfRspYhO41zIG9X/5tSnxTc8PDKt+IySh1J5lm+m0EfIptchjO1B7gKWRDCEaQgA+JTb+KuBVrk8qLdDpz/hoxhjjc9rcbq2Q7G6UBF5WALp/IX7UNwJSg2EwwE3O70jP8KRE9sMeR2Meavh2gb7T9FKslMRIuoApFd7vpK1p1WQABXl7c6AlZmDiCv1fsLSSaKLk/AjjFKkdbuveNONSbjCoRv/ZB3e6QA+UpAhHL1DZ3thKqfj8TwcYpsbi6hfk6U40ue0qMA8F7TxxdLeAM+HxvC+JJYID1vE0dlvuBuWJajCR+63Iqlnwmf38p5iSntfblTDhPa4ctag7lNxlkvklMC8B62GBq3n2Xi3ZEnv/msVAmhDmGt8Y7TaTF5N3prEaxOz/e6xK7fzeRIL37vVX4AAK+7kB3xOpG7eFnxCej8VCxCNBjV/Rly+5BEgFopiQ1aQyJnBs9z94YCQ6gUXPJhAy2q0wz+6DIlqcMs1hxSptadlpUBxmBcLpa1AM+MWlSQ8qtoE7X+hqoFx+jiQY1tcY7x1qW5DIu45slOyFjktYkE1Q0FzXWNK/QSzGUzBvJl19AN3V/NBUL01xf8CVY2VjQjsqXeYkX3pCpNtescPGmpeodvIQPy7ecInqrqGpaockclDdLHEc3ntle7NmjBaBFd8PBRmQik8DXJ9oWbj/4CEjZQ6l3IsU26Un1IouZaE9Bye5t+0AZWIroDTbfN71zfMY1DXs6IBHVNalD+8ECrutdHTqvTqNHEakjlabz45yLnGiH5s705fR2qHZ9PFpqbWkYreLMrPFGgBvtFeRaJAyldMLrVXdCiCjq+simURYgdqdN6ZzIUBwonkBvFbc7V6gZBDTeREkeoO4Ibnl5HgcNBhcpbcGWVDO2Zc4OgNiRpdNMgbM1MMVVJPB7zsfxuOGVGDSgHQUI2Bv6fo9Hd6r55RVVwOWtyKP1HMJ3XJjq2M571/deSIn2KIUXRvROAJyADXmn7xw9P7mlNN9kJjHHhrrjezbYrphJbAjTDZnV9W0RpWs4zC9MgwbUTSnaV0NfKBQlm/QoTjuFFyT7XDmiga+eS3JMEXG/0JKr8kFfqBU866bqtgUePsAw0EdY3Wm5RHT3V7pqIPsy4b9PZD22kOeroL2cArUg8ByQIQ31jku/xR7Xjt6fmUoqsDq5S0/LD0EcDzP1ntAXeuhy6fSc4N8GyMjVfmMqEjJyoCvphmR61eWRt5VYFQWrGUTBOF+j/NFDtxIxRFWBbtKNZZC5SkBIq3DjYKNEWpioLo54Ryc3Ton0E6zI1AgyeQhmk739K2pqKJl2yVpnOwtb4mZ0mIgl9RaeW0M1bFyTShrXSjn2aiJEAiZN7tLJUCxP3nYHlyZDbnFsmE0lI0vtr1d2c+fHKa6dfFOHpga23ljr28egc7ojBrWYe5PWJ4DGE7zDoG25vw4DGobt5/4hg1d8Y/9wF21ECNUrEDtMecwb4WNoL9M5JyflzRxWnn4pFeGmTSjkrR70gCdOEH/y34Nv1osCvEokZvh3D0YB+qVMOEeg3PwPc9EaSHLRhSwIIlyWXylBXGQVeBnw4t4UWR2d52v3nRKGjVBKvOoHyuKxzXYzx7EvJJKDdck/8jNGy7rBVJtdo8gXY2Hb/k+JCqvTiTtiVyudy1wyP2kYuK/ffyae2qJyh8FvTf5CgjmYlKbzLfSV0OonlHGu0QDKtWokFfMmhVBkGcwENo5AlHUQm1rOQRY2cbCuFZmHbVNEBBv7hzjnsaVYmqU7ywT/WgPc5aem41uFN3i2p9kjLWihdBR6DGLNZsTDXt4xRNMec9bDMjV8QCuhw0f5ZL2OkzFCyfXAx+IGE+I9O6u9pVCjFJ5nigekBFR+QKqWPWRlaC/mQaQsB56B2XJeG7CdlIpy4JWEyOjH6S9ya5q6aePTeURJxz3XqsgrodGx4mb/h6YX8xGQhi2hSVkcgSND9ESywgiOpN/OBx2fhPTXhYhm5a9jabUgqV25FKLjTYLlokzD7XN5w6avBrDXfwUKZLr+ayQyqydb6EIwAD8naoau+P4pI88tSbD5lGB0iLRPwPH4CEPxDbRi7pXDKHXv3aDgdZbvif6WRxnkdEAEl1uFAuhz4G0m1aCaoJr1goQKBqqcZgOTRIu8
*/