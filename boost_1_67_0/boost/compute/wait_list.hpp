//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

// deprecated, use <boost/compute/utility/wait_list.hpp> instead
#include <boost/compute/utility/wait_list.hpp>

/* wait_list.hpp
cv3GtDZXKgVDvzL58KWWH+azRXG3iJLT+JEqo1gLlol1WhcMWJrY/0xD6FJGtn/xISB9Nfm1TYL3YdpoD2O4aONtdPP1mFfAfwN06oJmL15PmZHSEdHErWdJXqqTEkO+OIjt84rbDS5H4/axf8eLnXcVhEbR/s/HBvw3OZnxCWVG9mhG9Ue8lT6xr4g1BCTWwg80kKXrHnN4QNrOG59m6LOB/XW57eFzS+VvJyP30cZb3kJtyPYLUzHedw4HzfGhetwZ9Elx/dE+SvDpZXBMx1476ehooV17oHT7mKM73hPfzWM6oaV8GWY4UU0z/BFtZJFb2k2dU/PNeatwnRtTweWKV77BIdiOw7dD7cYtChzKqzxrVtG+gSXrFrFziQQLwVKkpHc8l+B7Tvq5jXIxGNJ74mX+eRQ/n+efAj8f559t+PkQ/eyz2p/5F9UuG3IZQOvKW4wj7uHb6Igrt+ZFl0MRaQe25koqwcuFWVGYm37GS9SXsXX6YE3VLjp+Jf36WqOd95ynvYwhp4R/p1Dt5VXyYz99iK3VusIZduH5UmGuZo6uLFdSF/NYUMFyuG1fWkK/HvsVLnIKxKdFkk1ZixKXToFXdv41Bqn5F7jYO/CL1pLb6nK3r/h9K9yLi++sUAbYvqO+bE/Sj6ECoWtua8njWaYnF72Tb2f77IbQ2Mg2BosPjVGHRRosXu2hlZJ1HaFyBC21yeuy8NxixfPkT5QsU3XVDnh4aR19b1a62ckp1iqBPadaq/xHE5Xle9JMVLCXfDYnpe00spPVPO0hO1g+i+6X+9pLE5oydg4J9GkaTnSKW8vKqIBQUUTkhAbojqKa67JMdGYcui/L5PNqY5c3EL8pVdGS2soeHhY/jUmJMSajTxmT4ckxuTTGYzIIY3LmGio7RzqimVedgsRGL4L/vkIkRKsrLOzv4qocWosZPnWxVYGbxFB2ZJ7FFLdEbrSapovTLu7RUmAu6jF57i4pOwFkQhpIdRr8Y1gUM23fHuIcrFXSPAij2rr08RNpl28IEjdTkLFRbz3edSq/YAN2i79Yi5/NnhjOU0utdOw2hEaA8yobIx7+mK+3zFPpKP7EuCQUNdlEdfWrQHLBWfUzsR1Mn4PtQMyjUVDcz8TcG4s7pZr3RiX8ihKuV8JvSCXDYAYxZQ+MgUqo62TeqtIMnfGvugQ60vTjN5ck2AE67BjD0sn2YdY/XyTdSgczoFXm5SCpnNgga2pQwjuVcJMS3qsrkrn3jnbvpG1utPtgcFhsitXuVd1NMDnY4/X5fKL2EhwsB9Xy+uBQH82+Dwrko90tlDLB7h/myibtEZ8B+2pXqD/7n2ri1vvgKPE9ER0DFw1P6thH39MRGWidCBX4XnH+es40mAM4+te027l2EQVMyALv+CJ2sTEJKSygA0eU8FGFOP5wm96BCUCWgUvBiYp7Pf0xK+7ntQ8vdD8fnKh9qM48kul+3vXBiktJwHLtoz8165014p4sp7utdhz+yRpd3pbZRGH0a6bIpPw+X0XcAclgVw2dbK4P6N8DCPVOh4L97RdTf3Ppx7GLjOn5NS2OzgiWpDU0GB3ejL7T32P0N343Sdx1O3ADBLV3x2LKngX99zH6uO1FYt9ra7aSPCm6jzMLch4MXbIyr4KKxh7x0OEeLQB+lH4/OBqa2MTClT9WATV9Rg5zbww6tPB6kq+08GNsMuH1iZ0gn/IXsaG/dQu4r2fEzJ9JvNF7QYxzZvPZtIW1yPjSsBUK/GojJK/9+EVkfhXDhV59B783EIfQxgdReXuFN6bi2lN8tyWLdc/CF0LEK7XEh6tNuB1lc+ZrrOo1BQANLPLTKu4zsqC/lk2L5LP4uVoYPDhtXZP19f8ByQdEVtZAhREAoEr9MMqmtlOLovM1eVhqLzOEnKw9TLXLAEgLssBleoGyNHyJa2ZLp+JfZcAq2Oj/rP++/7f/+/6//v/f/5Wn9v/3P9b/+f+p/6/36f/KPv3/far/s/T+mw2NS3lpZVwVU1uA7k/ri871D9T7uAaYw8Xu52oGvs5QMP34SR5Oa/sZb1MscFypWtXl1tjUIpiM82VXODM2dYxWZPQRd9DUEr1J+GJpYnu8XviTTapQ67jemb3TvXXbud5fv8b1ksTfy88HF5kZgDR+GsY41I7xxeB+qVYUuGZaQ/0o0T+LG1hzctKYeFejGadu65LXUzg/jdkIEvMoyNjw93Z0pb+2bABtlPog0onnB1N9ZRbxD0DZrTaevdQzgeMfZBSyZXwNY2fILGrJdAlR/qf+zFvPUMvbA6V/ofoekwGTEdAQooWuyoDLEGBHi34pA0YiwHo9pfi5DLBDGdqqvpf3SINXPDmK2nFPAXwJvO8VoZkSFCkvugwoK5vQvoD4JRW2tL+uYJyThfvn+Ew90lZHkbNTkaPAH4/TI8cvo8jxqcjHEDlcj1yzhCLPNiKrs34rr5R8KmPLx38qV80OsPWLaNUEAj+jLnzTz7AnC10ojYpwPeMNrHiECjvQTxYWHoj+7eH+bb8gQbQe/muSNVAnlED350PwLANf6dYMe4FKVpdd2JD2clipfQhYr0uTmv+8NbKrTu5CyltkZWUwh7MBHVdelPQX96zCGTWTeVPx1skuXXtUlkZnP02uXTx1HhzHmkrhODZD7fYH9VEnrmfIaiZVG3vie/UEO/kx/MlXqrMtPj+/QAWoZKyiIuIjvoUmxnC1wkqlHwgNVncgNNxvKp2yruOLv40fUGvhQqkAZO6xFR/oOna1a/+SQTHLw9BDCVuvRsL9i79FeeU2nzJO/DRM+7zHopbbq6sUM1sNB+31wwqIou+olBfxRxuzO4je5DMWjpriQySvZbHMAWcEN4nlv9Nf9K67tVOToMXtrFQRW7dXXpNni/NwqVEj4oPFnz7v0RjzQHeZY1Hfc1bbwl/iQhJ2vPxqyziOE6o7NefctvATshxxeBMty3UWvqad6tpjmKao68CZp3/bTvm2n/LtOOU7/5TvEfK7QH7H82P8qiIe+l7r23LnE3hQCB+JrfPqDwtC2dWjv1TjiffuKrwnFJiN9wTmHS94+AQFCuM94ZwBZpPs4Jq5vXIDEt++mnxUmEWsn3h9Oh3DkfPAqpt8QWw0qyCA7RN7ZvdqRBi5SXDxFIsrik+mLhNObz+FRw1qgfE0y/OfxGuBt77tTDy1XZKTeqho99EUdsyHXZJJnWmXJDPdWxGLWf9BElLHz7Lki7783NjVpcUWaV1/Hy4vEmXoqOtOajGPWS3vmK8MQEGzq2h6i98VzedJJbNgfn0MtJZRwV5Z1Bp4s1pWADvieTgTExl8IImRzRLuVwDEfeoYqMNJWPKPbzHO2fbiQ0SCcFX4dYCkTqLGJ/5IK2cAZBJl7hGaztGuOwsXn++6c9SykT4x4MXjDEGr4maXRBRkmLC4U2t041XLxEdzByWIPsbHyq+ZwoUI0tlKDfTxzP3hUYbKLfNxVN7PGSf3yspgP3wWPNPFD94XlXpZx4iCYtQgVMTozc134q7ksKR1s6iYA8TsdmdVR3iUCp/U1rrtoCIR2MeiwhC1XOBwv5DSxaa1t37E7wsifrXqbnP+lpHy+wXPRy+WPdulVQZz8fOxp2UbRulNaBevP59sQqYoTzYBL7Dv3QCWr905qwMySnvrMtRQ04b1zFAsvAQv/2sW66QDbj84Qqz5V5dEf8Q1j4XGuH+wn7j/CC2BdhivJvPBV0ZYiFlbjgPbSylSw20xXiRCeZdfzQciKa8JMY5WryQEOiZpQGfDcbIFj0eu70LX6b7FHLzFTBsjlEXYI46EDGeaeLvDFXSoFgoKNOgtn/J28wv67fOKQZ/1aPGFqluwjx9bdxf8TMfHqo2uHuIOcBBRJV+qngIidtekgnAWJOiz8c8g4u+1IlT5wV5ucq6rJ9zYOh1M1rQxqhnjNkkLHxVdv+jU4legOnEVRqKmjYeBe/sHmXUwgytQ/zZzaGevrqPsnaLrrEz+Wacm3p4mcVeW12/EGpk6jUFhixtw09egxFawfz7qhSfRpbHoTe2Pl7LAGQcnWmZRS+3q5WDWoPgWK18pQv1Pairn5GtdzVsp7urVdP8lK4X2/QnaTcJviKpp8s4WiqL1d42k2neXS0D2uVYdQ9jtKO6UEMIk8fydWqR2K1tXAlf4cYAFK68+AtBuiGXP0t6gLbEory5i1GAgSCrROZxmDafJW1cDEEn+gts1Bo5U20XBwwxwDvhicWyevNLi24sYQxt7ZQ4ScaZ/zlqq9/MyyKNlIPPcTuRfvNt1LG/VvTCbP0n8BmxJneW20NDY6uazqOOJvGX9JOIxVr0zhq6FCng0XdtDp8GfxmDtVe7we2Ix/Wm9goqqqNBeRQ00Zng3PavfSS2yFUPBZ0Deqq/A1byKgFhsHlrycA2t2vIXiT2OrkLL+Xh7ydEFh+oqJ5H7QA4x3rQKORHtP0BVx0/x+Y0UeiaA1tV2X7GmvV8Wbag9c0FkfG1BeACJdlNqM7za0AQNm28qRboSKz4H1jrnvaChUwsW6B8/e6pLCzQNddhj0fkMDy6DP2zvxrawkZpgFZfjwjU2XzZK1PvxtSrZRIt4FiE8ySpPeGQrxscUHiPFACn/zNP35WgAKWIgBnOMP6iM3PjZclBjsVmoPrSiU0+TQaxFP+y/7ChgZQXu7z7E20yUY0NDVc4R2YDPE2hfPrVGxpopLxxgI1EgmegkEn3nw/iv5Af7M747obXeae5DcNKx6xVHYMv627/TAdipAitgoE5oYtNJVijjr0hDu1fcVG30DxjZoLjQSf1poGt9lzEkoUFGNxEryhdSpjelrfNWhOStesukG2L52XAYeN+TLUGTTl4xPI8G8TgvXqs+qflkAB8fZ3uxkldyfIyfUb1+8aeEkYlb8hwdv+LQ/byIlqMBL87tTCPUTDRPEinHvnQbSG8tA5N3yDCv+Gg33Kjgt6yNATEqxT96NMZq/v1M2uyG6A3hJ1aKfBuR17eLmpl9CUXlZWmIqdUUq0V5BfO/Lt4T8tZ29EBRz8m7RehWJw9gqFrbnBJWdp9M4AV0V+gadQ2zavtCVzk3ghULXaGuBHPn89GYVWBLuzcbqJ1eYw0TifTHIRPpSu16ucdOaGLhNay4ljL06haHLdJ5xaI5xYfoVLhGbtHsKmRHyJWElvE6vAFHmGS4y2SzdoTO0DayaveXnzB/0L+yshJ0/BIdfs65veG31fuksLJCvM0pwuXpvYuf0IuxqiuhIhEfoceyLPauEVuorsSLiqyuxUbVLe9b3VXHpUfJHQFoDtUvPYd28cwy+fJW46ADQT3GV0QKe0hQogz2/+c6ydZBiQoHt+T9ha9VY+2sJNN6ldnMaZgvnt+qo6D/IsZumPhQK2V2wqasnsL3TfYUj6zwXbT46rUeLW8T/94usiNHzKypsxp7eFQLna3eY4kPU6+nE1l4erlYrsv1lQaB7wv1cQvrnfFhyMfgVcdoawM+hjTTFm1H8ULF3SpmpwquRgZa+3KdBFoLrM3k9lCdECnEG6n02IkpdZ4uqzWJuffqeUxZRh7IHGJNnzxWyjNU28QdbpJ5Rdljes75yZyQTsS0PjlzfyTnU19LkOAA9PVkTnaz5OiTs5/eq3+8IevRNllYvJQZsBbE4hVZJm2TVUqdt9CHfAwoCFkVvo2PTwx4h1C6LZ+nF9xfL/gnL8uCpY04inVOwPEoTfOGUXHOCXP20fdQ5xaogoUGaJtssq7uu1GxlL8lbef1JKTuQoq20+4Zjh1PGJoNTNu07BrzHt3hnNBMW3LY4voUZdtl2Y/fjYqXt1HFFOiQgWsoUGWLdtiAEulQWIjCiGDaA23A3fvwH+l9BDRXPwBxT35adtJrDBwkQuGkrOIPv+L9E94KxEI6nN/8ciKJ95RqgPiDwuqfA/xGvI321+LdxB8/ul3dDnnlVhLr3/waGcQdqcRygXw655TEV0ILSuows5BLcjTkXQwm7BpklCj6Hwp8HNUFTbCiuauWVqwE0AhBd/RKOL/6Qkn5i9lMB+Sb6/RGDxRfrEk1muP9aMcB4pO25z36lmt/3qq/gh3dirgKP+2ikPjYD8hs3kn9PER5YtK3ODisciAHCpfnJO/5yvV00l7bLuquZ/2RoVP0bdXAsS4ITQK0eu2opYWwTg/l0Olb8gI/1cem5Dhgh0FfkyONha6qUYsPw9fT3M+IjWuYrXgKFE+h4hl1Q3XSUa2tUv2oeLdS3qGUJ5zXjsrjB2L29ayU99KE7lYnF2S6exeo9gWuYeHbVa896rOHblGXWyPETJwf0Syhkc4yR2iEWmZTfTbXO6HBeEKPHNdCubh/dUUPhK9w1VrDlzHMlC18kTrNArM5vtO0RHfHT4NbddXuGhTOm17hFdunME47nGxp7oTqTkTcvYWuyaPy7l2kYTtW3R2MSRmcUf8SNuTcq1lzg7bksK340ORVs+x5q+DYmqpRT1PKbTANgwrVdC+rY9F+ehbUWna0sndkk51BJcrXi5mZct92nkX8oElbakHgBgpUc+gX0E4gU8+gQobTt3KWmGyRNwz48ljEZEoaf55yW5Hx/FSkuBCFuK2dpXZL6JdBNqc6jhv8idC3oK/weDgLn/6arKolvarL6LsxGyyZuOg1o8QWVLf29SxT6+VMw+IjvrINbxeeODFOEy1oQovork9mEFWvw9RJvDqJ76Trn3mX32ShbAIVMwf8Qmyn1AvG03H1xruG1wZpLCJDnFWF4bNUzyhnVdHSYf7Ycot2hSQ7IjSHq6po8Td4kL2h1bUtefEbtvrEd9v4im6E6sGD4mCvmPp1l6bgg86b33zVpbvvtZjqX3w3+U4MXZ1m4b66Ow2BUoY9lh7G4qkV+u8U8zHHGKaheBzIqfebclbGz6I00CDkVDm6usl5j2k992TNN1lW4tmwvshsMaVggfMjBab6TI5zyB8pMEtbKo4d+PXuGmwXq6/KoUEU30A/s68fh5sbaP+7qjTpC1aCobEv1BXYI1qih+jUWqKv4NhkY/XGF0ZqC4DX4Rnl8hSGr1c9hZmeMcW7g4U/S3NVe90nJHz7CtQW1TPG7CmcrU4rjB6gc7921G1aYWbTbbsL/dMrKkXTXZ1QghP+TyAtOZSqAipWbbntUGFmVUEpK//YaLKCWbOVyQVqz3cbaJHtuCEJXRBpc/j8bOAF1/TASRxCZFbc6YHOvrLILkbiYrLcFpk3wlStLHIoZflVKYQnIq2X0/zKvX/4lFs01u0pcnnGhz1+6p8j0tAvvYs/p/QRz/h+aoJSqdQlJLitwVGhLR1F7Pq/lqNro8QKJNuZr9SOqka6cislyfSMWqAOWqDY1QqL4rWoFVbFa1UrbIrXpl5jV8rsmqdIPkDY6/djJ/l2AnyMWrWlbbHyoyJ4nAZ3LttWEIekixl2U94qaNEBQWRas6g/rvFrQHiYXGhHxWRioepBV61PIZkN/LxdbDojxxSb6qBtLTLOFLrIm7c5k4K94qGvWXdw6DbkMIowURHqrvgtxZ1xJnFPM+pqdFuRiHWBvLOg2Ra5xWoy8uxt5yvueJEWbhNzRRfrUypuK1FQeZuo/oIapTXm2ncY6R+j9Lw8xFMT5BWJvb4DY/D1+PQxWIDbnRo5Bpru7X6uHcPBpryZQbOfmqZMtYuXuvkqJTkOrnZjHO7HwDU40PFR1PGcSq/4w79+pNu57dztm9Ft9Nn/f3b6w2/SOh348pROB/9JLehoSuv0c98Ynf7TeKPTp51Lne52pXf6zkQXvCfB0aEtVOOssYeWBzNgVUMT3kjioasxPMQocsY3ejfjt8CSxtMMhaxp9K+Nmk4yot70OcSRZSo1ViPbmektf+mLU1q+kdjT+pd2p7X8X18bLf/OJa2DCupdaPlVLuNOqbjTtYu2vMxS08r4wmCpUkQNGEg58OBf+BFrmrFfQ2gLELumdYNyYd0Oid61JLFkFDy/7LqtoTBzcnu0rCA01AvlVPGu6GItVRKHrqMdyxN/n+qLNI7DRCjjqBNinosHEzeFncT/1t/zTq7hFOjTu6G32Zg9Y5/D3ugpKqA/SR6k0TOGrymkKdy7t1BvJl6ZNFxADr6sqnk71/5aOzGpIjS82+D2WEnvQRom1yJr2BKZZwXr+nGnZjj6vJ/qFU1XprnPEb9N0wuc1pLahFpvvluHG+fn0bNpL4xOGhc+LTppfHigOqkEp0WWmc6H+IDihnhu5MYSUz0+eXuU0edl4PigI2znvj5H2BFxr+vUI+yI+Mj140fYEXHa+LQjLD0GZt3eNEi2AkjXE9YCIIHO56BZqSpRqsYpVeO1DxdEG+7qF5k23hyZNi4jPogIl4OsFJRBQWZt6JGn2VcnzRy/x0lkgMfHJTRnVUle9CVMyYQQFb0FKnfa0PHPIr5mHCOr50XX8eYXyAXqJExYgqwkqH2I+3WE46nPawSFJqnuoxMyMoDcNyELf6ZPMOPPtROAnhaaQoJ7dqRGDA9dCZMrT2HK3op1QhVPiWzvaDpOswKH8u1Lc3Qt1EhtCW3Fc9kvIqN1eEr6YAVV+HhBE3uVEOs7uviy2HMkNu0I8VUUpraL38Wx3zDYq0F/264wTK7Ov0v6Ty58D4Rb0AzCrS2k40WpHaPUFgUzYbxQW6LUjlNqx4uVdPA7JyyEVdzl6oTfPgVdooCVsm5JUMZK7cMA3CQHjuLj6fmwA/vwafSmMQt50J1gpvgTuIddYvC4dKrdtTyRpNrf/i3tzXxGfRXWf/gK1mZVw3alfH2sfCN7zZTsR3s4MxbeSEPoagkNqIzVFvqlgXb8fMX9vOJ+MeZ+3itt37TwixSthZ9nL3LPU7p86cJ00js9fE2vj3n8dL+B1hEa+CT64fVSSCESTxSDlS4YbWp+2qfD+YY2/EaRSV2gfk27Qt8l1geW3zzMLqZf0a0FrPOH2dV9akJMoa/ILc8Qb/wM2F8Ua4NIE34mvvmHYB+YWzAkPkNxCx9sNmxgwhkd+wEAXBLlAdgctBeeQeuM8r0C8ymoZDxNdOnTfbhKqMJb++GhzZ5iaqOdfM14UWSifXGXttSadJ/zFTG5z2eEPg98vi/XHpzv5bj6DYCB2lG//j2HsSsuPnxCiyxYRKz2zvfSHaRRlJ+iYBPrWZSMlFp0+Gh96pMTp+jpz/qCQqYuqqYMhi4FexfrKCE=
*/