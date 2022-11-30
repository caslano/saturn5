# /* **************************************************************************
#  *                                                                          *
#  *     (C) Copyright Paul Mensonides 2002.
#  *     Distributed under the Boost Software License, Version 1.0. (See
#  *     accompanying file LICENSE_1_0.txt or copy at
#  *     http://www.boost.org/LICENSE_1_0.txt)
#  *                                                                          *
#  ************************************************************************** */
#
# /* Revised by Edward Diener (2020) */
#
# /* See http://www.boost.org for most recent version. */
#
# ifndef BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
# define BOOST_PREPROCESSOR_ARRAY_REMOVE_HPP
#
# include <boost/preprocessor/config/config.hpp>
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REMOVE */
#
# define BOOST_PP_ARRAY_REMOVE(array, i) BOOST_PP_ARRAY_REMOVE_I(BOOST_PP_DEDUCE_D(), array, i)
# define BOOST_PP_ARRAY_REMOVE_I(d, array, i) BOOST_PP_ARRAY_REMOVE_D(d, array, i)
#
# /* BOOST_PP_ARRAY_REMOVE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_D_I(d, array, i)
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
#
# define BOOST_PP_ARRAY_REMOVE_P(d, st) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(4, 3, st)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I st
# else
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_TUPLE_ELEM(4, 1, st), BOOST_PP_TUPLE_ELEM(4, 2, st), BOOST_PP_TUPLE_ELEM(4, 3, st))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, res BOOST_PP_TUPLE_EAT_2)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# else
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, BOOST_PP_TUPLE_ELEM_2_0)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# endif
#
# else
#
# include <boost/preprocessor/arithmetic/inc.hpp>
# include <boost/preprocessor/array/elem.hpp>
# include <boost/preprocessor/array/push_back.hpp>
# include <boost/preprocessor/array/size.hpp>
# include <boost/preprocessor/comparison/not_equal.hpp>
# include <boost/preprocessor/control/deduce_d.hpp>
# include <boost/preprocessor/control/iif.hpp>
# include <boost/preprocessor/control/while.hpp>
# if BOOST_PP_LIMIT_TUPLE == 256
# include <boost/preprocessor/logical/not.hpp>
# endif
# include <boost/preprocessor/tuple/eat.hpp>
# include <boost/preprocessor/tuple/elem.hpp>
#
# /* BOOST_PP_ARRAY_REMOVE */
#
# define BOOST_PP_ARRAY_REMOVE(array, i) BOOST_PP_ARRAY_REMOVE_I(BOOST_PP_DEDUCE_D(), array, i)
# define BOOST_PP_ARRAY_REMOVE_I(d, array, i) BOOST_PP_ARRAY_REMOVE_D(d, array, i)
#
# /* BOOST_PP_ARRAY_REMOVE_D */
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_EDG()
# if BOOST_PP_LIMIT_TUPLE == 256
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_ZERO_D(d, array, i, BOOST_PP_NOT(i))
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
# else
#    define BOOST_PP_ARRAY_REMOVE_D(d, array, i) BOOST_PP_ARRAY_REMOVE_D_I(d, array, i)
# if BOOST_PP_LIMIT_TUPLE == 256
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_ARRAY_REMOVE_ZERO_D(d, array, i, BOOST_PP_NOT(i))
# else
#    define BOOST_PP_ARRAY_REMOVE_D_I(d, array, i) BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, (0, i, (0, ()), array)))
# endif
# endif
#
# if BOOST_PP_LIMIT_TUPLE == 256
# define BOOST_PP_ARRAY_REMOVE_ZERO_D(d, array, i, zero) \
         BOOST_PP_TUPLE_ELEM(4, 2, BOOST_PP_WHILE_ ## d(BOOST_PP_ARRAY_REMOVE_P, BOOST_PP_ARRAY_REMOVE_O, \
         (1, i, BOOST_PP_IIF(zero,(0, ()),(1, (BOOST_PP_ARRAY_ELEM(0,array)))), array)))
# endif
#
# define BOOST_PP_ARRAY_REMOVE_P(d, st) BOOST_PP_NOT_EQUAL(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_ARRAY_SIZE(BOOST_PP_TUPLE_ELEM(4, 3, st)))
#
# if BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_STRICT()
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I st
# else
#    define BOOST_PP_ARRAY_REMOVE_O(d, st) BOOST_PP_ARRAY_REMOVE_O_I(BOOST_PP_TUPLE_ELEM(4, 0, st), BOOST_PP_TUPLE_ELEM(4, 1, st), BOOST_PP_TUPLE_ELEM(4, 2, st), BOOST_PP_TUPLE_ELEM(4, 3, st))
# endif
#
# if ~BOOST_PP_CONFIG_FLAGS() & BOOST_PP_CONFIG_DMC()
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, res BOOST_PP_TUPLE_EAT_2)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# else
#    define BOOST_PP_ARRAY_REMOVE_O_I(n, i, res, arr) (BOOST_PP_INC(n), i, BOOST_PP_IIF(BOOST_PP_NOT_EQUAL(n, i), BOOST_PP_ARRAY_PUSH_BACK, BOOST_PP_TUPLE_ELEM_2_0)(res, BOOST_PP_ARRAY_ELEM(n, arr)), arr)
# endif
#
# endif
#
# endif

/* remove.hpp
9oRgaHGjH/V+VUl3ZWATdt3t1fhcoVUUCc6rMJ2jjfCztz1OFgTV1Mr1spb9TlBSZ0l1CkwcEEn0RMy4S+RqJq+qqfcTYy0WiMBFwxozTJpwf+SK2uMzXaXbBAdCzc4GbcFHxqYHs0gAeXnLkcBMIaRq8zNPwdB+wSPvRHPHeW8MRhUzEN5TDS4+VWtOHmDeFUCvPyK13n1WqayNIy+6pR0cxpY18o9UAWFCOGiSpLlFTUxM+xKOeMfpSTwzqvvtdybFojG58opWYOm1YyC06z6W8yUgEzuZ8tFlAydra0W2N1DoQhI1rpWS+G2Si9DHs4zVk/KQcjVobsuPln1XxfqRsWraVqawzHhUjIV5KUQsrWCn4N00l14DlXUsso1L4kEnxOJdL1diJZGVW0NXAf3rwEoAf9LJOKi8G1VdPW4NYrXZTt1Pu88Sbxo2vq0vjFf4yzFsttf5taSJLsfn4lrKTI/za3Ej7X9Je39n11M9SvN862um2z8sPxve/3fOf8d+9xrptEGsLGRaWXkB3Ua9KNkLH2QxQCvJD750qAAKREjZOb30x/nJo6lWpZCZ9dYggAwXMgmoUI3KGQTgj0JZHskNqb9lqHN+eLJZ5gloSMADofYQ74fjcQOU5bLRIWVXQH7mQ+68f3dhAAH90uN5mAU497j8V0dL+Xm4EYGVFeQBuYQMJvlZYEHToaQ1cMnglYMHkwnkSSGkIWGUgoVY9ulR9/HBISYanEQRFmjtnXyC+EK3KiwCt8eNgXCACuT/QaGQgnIvoAItzc/786MSRkbu40LTT8xFXYuDeiWQ+EZ+K4nhCzmSGUIaU+9Cv/fcnge/EVoF8uP068XyrZ5IvDsR0C3ir9meUQqWx4JASANCfeQgb37I4QfCI74ZWZqbQYCFPQy7J0hw+dbvfSL+ejz9fRH+Xf+mAd9Nr66/782tLT215ZI8Kug99r2RaHwi0iM4wUDeCTmP4rzsaEQO3xWPq6On7VH53H2kOY3JN/wN3njNybEd6/mG57QMvoRjiDHmmkeMHcXzuW3ofTcHyYXF4OY06O5dMUKM7934kYcs7FGM32UhwgQFGFym0pO2I6HAqYAIqezLn9MR8dH8lRpEixnpfP+WhYaSSn90hTZO1mH1qf/qGJ1NBbmScP3WKfu2/IiA38C4DSDz4E6IV5cVUYEJ3juK8P9afo88ztGArg0d3Q/nWBjES0KM32X6XbUAV5TyYaJKMP6NbeegcOvkzMDQzEw7xzzDJMQIKIZd6unpUc11HyYOdx8ry6Fz5fvrmppGpoR0VAgkKmQ20MZLr7IwSDEut4i30C/ISDXSyzIzNEnLMEkAgQNWusIU6TwmSQlowFk6Q82bI0MDEytJJRnrLKEYEesgO0Ez6UArATvpMDUxTwkTT5EwIT+hpC+IbzJEv9JNgqClRXCgaAaMYMBUcTNGBUS0LsKRLvlDN+4vCyorpAvLkrXrU4lTU8qCmmhpkar3qgzOAywCz/6qRkzkEy3QYmb3B8gKI47U0CAzAUVAA8HctN/8mxOfGUpjSFA+YC1m56sp5m74t8KAi7EIAg1j7UkPpIWPtMkcHnI4zDh56N8uLeyKo48mAYwCDtGUxIT0tKikdP1sgGUANCyCLYzCIjfwSGGK1wy4Ypr/De2sRMTu6k+KF4rR+QkhDzVOATqlkYkJENBLGB5sKZIquoYVoWdFglcDUTHfPY3ERVyOxmxAopNPia74Cg6sFVZBUFcAXVAFN14tPhNhPwGSajiyP08fcimQ1l/JgCRBPC6lbtIefwRZgQhuQXgplBXev1rB2+0RSdMijx+tyWg5UU5alPr/L0Cm0BwIWr9Lz0g1qFCqNbZ1MQo4sFiQkzBQ8cuJZzYwaJGqHKr/eFx9UYJD645AgWmzl6qhDFiUOhNfXvSJJjGW/bv4yyEyMKVyorNwMiYl51R/Vx6jd7EYw1G3t0t7+TmOM9vrluD6a6HOPtKP8d84W/6cY72L2bvLpaCiImeTYs6+GL3ZWlBkdXW1RJyohGn709Lirnv46e9qSdXKW9p2a0qJ0f57LnU6m1X5cX8kIX2ydGJ6mrr62PsZfPomv/v+tfnw3POu09Cr7LtT1Xj9Hpi4e3Ra0XAlSfX+vvRT8/U4unyB0bvzjXPKmV8cNy06Gslv+82+Der8sVpHKsp9nfZlJz93adlajXwikgMlo/i166EpuUXFezIpFa5SG+TQDdLYrmjjrOO2Y1bNui45J3tbaXbcY5GbyiLlTXKfns2Z0Wh5XcuKaQuOJvOohYDNcjO67cpwxUpbQdYj4UXe1DJh2pA2HruZqDKlXX95O9lNG8zVqhVjtO0et638KjDL3Sh8Aytg8hYhw9enmOyrKnGl4mBu1XEs0Tq11aUDJIwLAZ9lQbHl+sew44Q3xZga05kJF1nbAA3smomz1bEQSrOzqX2UkiEQdxbsJkNJtQYabkktqZDL3SX2+XqYTju3byqwRLpSOaZaD+GIC7sgy6rGdDdVeat7kGMvOGQ98sX2lV6KK+n9S2tewn03xMKdx8vNV+dmtTp0k7aRl5fGMfv5efHq41abOXW351HNWnj09vWW1DpCU96+2ezTWZj8s3f6+t6RRFa9jpf3+J79tjilhafNRcxxZkipVAYdlfYc6UUb4Neyt61RH6Jwf96qQiPQE5Xdjlyd8yGozCFs5kwfUuO9pYXvsPYrDo6/l2h3abi2Rj0/X9up0z1/+l1FMffzRtV9kmyw8f6vNX3E4WIFXLeuJdYtR9F60tGnsuX2sq0SPs/OjktH39FVrNbvbGTqDVgI16XYHW9uwtkptanN84/6cS5sLCpt9PbvR/57cSQKveq2KjUtRcbIyI4XwviUL/qXsPXuLKxMTunPC0viXrqJ6/1ur5dubPms7o/24ybt5e3C+uxN5S++TcLjXYr26eIqv7nlVqHObtTjz7qrxS7LreLpxnAukm6OPJvGfDntq0/COM58M7oO/I6JqVvb0z0v5VmbLTnKyyEb9hiYF9s8aXkrdqEpQHQODIsH2/zZOv+/DUQuLAiADRHp5gfz/4y3d8SUlbyAxh7mIcXvFEsgeUsgFItDTPkvet6IQrE6CyL98/XPESQREBCEA52JeiKS5ZOJVBCJEDIhEIkMdrufWJvSmbo47BJGeqK6urO8ePee+PqkNsGIbIATWgPEt/iLbfL/tmhpPQ73LqcufPrBTddGhLUmQw7AaucXOnvySs98uCaLj6ev3YYdJ19IX3tUqLnh8lDSErkWzhLz950jGJ5MpreXbnjwfyBvj64kpnHSlmHu6/Sr6lcn58PD7/wmZ/qIeXh6sOYV59cTqdFhfu0NOs3pOubEl9N9yh6hw55U/MzUzla8uBLdndep/51+edOucroF2Lf7qzVHj/rlZDWR0FFeklXHDaE+wzaiCE0o9LG2NZuw095Absx5u3LKid+DJOocmlPdka558TndAYZA0/l6hcUXqpypNI8muwH3+XCkzDHKiOKkykVIi2Pjvxucse0VsyL3NXtY/FNMNdtmOqx2SlHYMzRuQ7L5lOA43Ck5izbDRXFhg2kx4fvDK0fraUmXEJ/Ae4BQkBKZllRp15zXuOaQ7y7oZSoxxHNDUxD1PU290GH4ksZJj4Au/GclEyWn4xY4D7lXQqN1ix2mSsbK/Fh2PGmupQ6xqKjrpUWW4DnWYhnsMNEKacX1Rmtbj1psJpkHJclSwbo6Q017CvQJ0/vjnGM234ClOilNTmFtlnM8ia1LXaGv3M5wcTY7cFHt+yqq1pFtafADFRxFLSQA8DVNyny5fw0ontM/8chQ18XkaT2N5L5uZ62N2+un/UZh4a7QIXPBzVGnNb+NsuKK2GZwE40vYXDvM6zqJgP04Jr1MqpbAcLYkN53infjsF9lSYH8StaI1ppFVvfvPb3Mc1raRwYk+7ZixtjpuhFVsJqsiSM9hNQYOHrYfGf4gzkDsf9nox4I//knp3hnLeoVaVVTZJz2fqp0nSJU0KQVPy7W9J7rdEz9TH1aS+wM5+xjZcVWAwOlMgTrWvw7ynLZ6gpgS+p1ehZHT+wvSDXzb0QVzW9jEvECXagRdUKVRCvBWuR/wR+OlsL8t01Vt6wfHL0bEpJeez9ZUh0giFRgJnOL7eVuDxnpcmlZTy1S+EHetzXZilE6DcuYdn58FnE6eLMhmuS/SyuFRXUOFuwhCiF7SHDSY0xEuqmTeUoMboPDXhUbmxoFxuElpbSRkTGzKX0b11RkoIB3rt6kxESiPJDPvoKQLBumQkj1zfVYojt8hWh0LCulN77HOmqag39uo2GlcqH463Ji93QiuNPUfugvcZycdVwenEqegr5ev88IFeGI98BKotHgt0ZP356pMQIZ5SnctBcqh7sbk4ZYoNhHYyyRwI2JTeE2CcXhNyBkpjeAp//mHy1JZmp4J5BaodbQXuiHxrUoSuKY6uUmmnr3W5wa61prK3Rv8Y1pxj6O5rlrxrP3LB9EmklhVGpJ9ezoZZjd64pEOy2Wqqh3CfXCCoqYlLDHrZ6GmG21HNj0lJJpnJLuVGEYjnbDKnC4ME2Iz9HOCoSLhW8eq5KjJadlkvldF86wKUMF7kau8tMEa/9dQrWFmgnGekcxtvibbwGp/VmI/VgFIWXwpsUcZ5+EyFAswPmYfpJ/HPZM5fCq2Ib1OqxR48xUwOow99D+MbR2w3ywLkLUdBxBee+s4V8S6vKLUPECBWIxRZpSZ6CDh/bdet1U/ajmn86InrTZ3E7j9GYbaX/Cz1v/OR4AZ2a6op7BEjcEx9lFy2z1di9YMFwcDYMOI91DH2DJdc7Bt7oVK9dDquz4QYDf+Dl8Z67zzti5u1yswEU5Sz8Py6NJ868uNwhR+b8TGGWYEjULw8PoXiJo++csNQGAg1p28mdfAlD3zaKqYtHKGLSR0OSA0ciCFBlM3ryDXxN9UDc+tC5vcuoyLXVaVLIdknwtDfOYBjrxOevg5qg65+CjRXd6ysHATNz9mx2yzqP8cOz7NzbJbIi+Gl0jD13ZcFGrH2RmNoGUXF6zafWl3G+R6lho1a0O/aBm81fw4C/615lQ0dzMvOpOw8CgQJvLT9BdWwdPLp9KkDDu1KrnfTmRToce7W1scHBA2YMeDSA7EV/KWnc183eUh/Xqp6vptyFr0XcKPOFKspVgLdaI+7/gx8lajOuj7eZ65RJ3ACcW4XghNxsxWyhYB7a9XAwaXnpl4RjNlm4tGYXVpg4Dghh5yaturNALPYH6I2p6T1ssNyeV6gRKCvSyIkJGatQFgTQKDw7/2CZSqz82p/VmSxZHwzN66kgtljUKytqga8bJCDaxn9vCbBa8npEPo/peZ1y1FFGRp2YB26hEyTAwlhtpT+uiuIw+Iu6iy2Fems3dVAyefmpgIUShQCv0hxr7z1y4s2D6zrHY+/0pA3+sz26GgIrOCqX4tVQjoIgHtSDh0titgcXcqZrAJfxG4H0XCRNgxWXfvLu98VAEfp79xicEJVik+q2DcjDK8Z2xQ6zMstPV2y3yk2VnRXnolRYYTjWeysZObi3yIiflv87UwmfQJzXQCgwHILpuimq/a/AiX4ujtDRb549LRoVIGlpLfjS0/NAVvzc05vQ70scmRwL4BCKNZZDj5hzMZ+wW6q4L1cTpamuL/aqBPjkq7MuNx6WrDPVYBl4uduDn7KiYGpmDUDS3ckBIJnNFKc29Madgr4Gtgq6mkib1SUD0R+k6XsrxFt+Vuu4IS+B1pjGSDCsdL04CB2qkJVBimEzb/8VMENw5ky8mHiwiW1LxXmzEeGIv4vuSoyjupADn6/4tb3I3Sl/X+SYUneixzJQ7kZb5VASrC4mPSeCvXTBmxD4ZecimTyDrdJV0wGXf8fOzR8ql/QwRRBZmx54lwJJnrTMMMZj8+euSYhfHRYpVYxYMMz5TsSPSswIaVOQv83js6WBQv9w8DxZ3Qx7g/VDK9nLiPMVD2963l6weZ9Gt0bpCzVIR1Vm5de+j7FrjHR1Hph0pCIaYn13sQPUrm4T2rMWUhBDUt6xdPPOY+n5v4RYL79nlQ+YlG7Germ4zkytK7vtySh81KU9W9uV0TSPiPYwb051eexKGbZRd7aoy4a8jk2drN98cfiLR5X3woxOEFS3qGKhT95htbfoiqJeT8VGjZ9kR7hrkG+Ye5p55IN93TZMWnMvaALs2YZGwSHuazZAFS4HN/+9bfHzu2mzEvxiSSPsAiTzI9tIfruERPoCfil2nOEZtLnrK0ai2z9uKr1bRGan3yftRYSBwhjjIZdnq3YmHdlatda3LVyKCIkUkkzGIV3uFyKlplctIxf7yIgUnsUYAx09BDKrrXkoJqsextowVSwFzOy2s6SmIN36CV5iF/8uEO+tScWRtykK9IjeYHt+hAQjmgG+yw0uPzIcy8vlErMRao7Kb8HhpYAzHOc8dhnfrHDFPONleaV3NCqojz2v20Wbuz7TsKUrnlRE63rFrt8loSknqDGKuLbpppfNi9h45GsHkNHpVymBF4Hg4KUD2IdpBzh/1MSChdHKv2KWxZ41uCJf5WfqOd3Kvs+FPgFuKQ/k6MhzWS0SiwQy6BHUh1fPZlRZLSeIUQPE3OTrVSC9BaQ00Fc18RwX5irpvxP7LakCZrtmpOLnGIsQt8Y4fYO9rxsfmUbtnWZqfwmCMgHrzXmTINakz3Xl0Bx2dD3KvcMKL7NjluG/jFWiZI+qk9tAyMNQUxUP1jGUv8aPRRMvn9Knao71s7jyUxN2hsZvkTIWgajt/JjEtoQzvyeY0af2ap25yGVNmHYQGbUHdxFHkbN6ERLONL7UQitdd5DYRNcT7Ydq26wVVWx2CjeYZB/rmzAkCt323mFLmZLC00K1SsCKxFvMwt7SWPLdtdqeBXdLNBEn47CUdzWDLim3MmJiWLVabx8zajzCZxIRcICH7/dEo1XfoDXbKWaspEkncs1f0L6T9KWEjYMBAw8F2AtmHhpXyI3hkySMiiI5lJVPAi7FXbkKMXWE32Mp7KaMNzZgwbri8HjQo8UqLp+0Af5rZgjbNFsOpZNFSRYA7GxRSZE14CtnRET31p5A6uxrYdoChyTRa8/q2NJE5k5hXawF47eR4hMSkyfZyj+vBVLl1blVIGR5DRlFm54YVa7boSCNcqN5l5cAU/ZHohfxU77p9ue8+Ub2UXTNE0dLEx2Fb0treLlFptFMllBG0FRKL/Xj8e117ijd1on3QMYTSafbLJJ/VOZLqLKvw3xx6Y74cQXvDFULcAjS6Y2PmrW4D0q7AjDVfv+09EHKzELHK4NJ2MLKK8+sPvC4GD8nODNX6J/OeKySsXdaZgzTbOjZAYxjP2E2tjGToMIOQnP8IYDW/g0TRloaxpwz7ylrUQKGm7ApuF8IKO7T5BXmsFgzyQcnc5QL1Aw1PFoU2jQFWWdTZ/MIKmE7D4IvijlCLl+awo6eYkZWl8plw6ppr+y2QUTo/ejZHeFGZ99hrjlnDSUkzASiH16SMZCc9SLtnAr5Am3aL5csuWVarY1yPMuO3jZBatNKBvdtSmRLOzC1F8c17Np4Hg7L6SEREZDBOFQyu9zUqFJRHVmfgHrXX/qL+xS9uoeZfExmDLn0igE26AUYf
*/