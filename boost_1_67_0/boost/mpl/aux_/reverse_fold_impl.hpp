
#ifndef BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED
#define BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#if !defined(BOOST_MPL_PREPROCESSING_MODE)
#   include <boost/mpl/next_prior.hpp>
#   include <boost/mpl/deref.hpp>
#   include <boost/mpl/apply.hpp>
#   include <boost/mpl/aux_/config/ctps.hpp>
#   if defined(BOOST_NO_TEMPLATE_PARTIAL_SPECIALIZATION) \
    || defined(BOOST_MPL_CFG_NO_NONTYPE_TEMPLATE_PARTIAL_SPEC)
#       include <boost/mpl/if.hpp>
#       include <boost/type_traits/is_same.hpp>
#   endif
#endif

#include <boost/mpl/aux_/config/use_preprocessed.hpp>

#if !defined(BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS) \
    && !defined(BOOST_MPL_PREPROCESSING_MODE)

#   define BOOST_MPL_PREPROCESSED_HEADER reverse_fold_impl.hpp
#   include <boost/mpl/aux_/include_preprocessed.hpp>

#else

#   define AUX778076_FOLD_IMPL_OP(iter) typename deref<iter>::type
#   define AUX778076_FOLD_IMPL_NAME_PREFIX reverse_fold
#   include <boost/mpl/aux_/reverse_fold_impl_body.hpp>

#endif // BOOST_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif // BOOST_MPL_AUX_REVERSE_FOLD_IMPL_HPP_INCLUDED

/* reverse_fold_impl.hpp
DEIl6oN/Pi9xaYtASv2OYeXJWQOObrsGgLrHDEEKm7m476/rr1/VtVPhYYMbjyL6kB7cyLKbS5aLkPaLuapJr83ZzBhwLJ7QiFAV7uVPe7+ERtzLZHl+rKLcyhphvLiWX7XXD/KLuG2u0wiv79hznlZeCOCqpnFgLIl4PPkOWdubrpQ7pHJjfrqi3VPLRmkod46Pl8nuaRpav6qHOr7JZXFuEYkOI13jE3R36XGv3Fk/WdxXU1sbVFoUfliBW1CtMzULCkrGlFqBj62+00bLy+7kR5DRZHt7ap5/a9ynP3r7dO1/VAwX99E+Fmy+ZYlsvmdGdpH1E8TFCacmYcz/tcaBmKnYgR1mkV2x3WT1ufpNWZU4NC1+dK6sAayODjQuDnfR/coHezF8owVhUX07HtIiuM9BnGhuwOcOjri4IXmX05GCYCmHqBjhVmTvOF7UIaeHBsJiOyHUGjmNUynxo3vGWxw1VwYZMBdh8ZyQiCJDpOAemJ7ZOX5UAMLiuJng2FaYdfUiPgYKQWNSCKrr8LQ20fb1cGbTedR7NX2OtP7M9Vguso3jxsEXT85voaY/Wosk3QELjIkQ8WaFB3C6nQXC9LvmH5Mh0Eqb/po1cG6I/mjN46dCIEYbJH2ROMZ3OcZClACR50MnsG5Q5zrBjZoSK0K22d3lfdSJ6HfhG2eIHvfQEwbUd+HTH5jeKhBjOE76HcMana9otd5yv3pfOWDvG0anr4I97uenyHwwy1hUUtSBFRhLvuy+sEbfO+AJoSlMupM+GKqNgG5fuwCqzQ/hMgSmIz7Z84yIbh+4E+AaVNsI+RSagOy+KLVesOZ4yBQEBtexPLVLWB438uwSFpxm7j/ewUmcXleFoz+Q820aZ2MkY3S48+s5/nVUd1S2980R1PMZ3vyWKEj2VdpJ/Ww+4qBWVwTPtTBp+G3k6ZYofSX3f+EDqcTNzP8DQK51vNS1TzLyAoAyziOYKBnOE4PJG8rLyY2BQsgh6INAQzHg61foXWVcUDVwjqIjIJOGA8Yn0opqVyy3zHtqrLS0jlY7FbSiDDOGpQ57HiJeJnhj5pzM66NEFfA0TPfefnqdTrMzDhDp/lL4Qp2+Zj9q717eeupg5cjFH3xS3oU7LfvSg5KlVb+2HKN5lCfECDZzhmlRy62i/PnAvw+TVL8NA/y1PhKfrHBFCe3b5OkLIW/sacZSL3qM9tGgiB9oB+l0LUfoStXsXhyhfB30Ud9HeGP1oNFC6KEVLLwgfR2gafzn+QiA+tBbB4kFg/WQD8IovzeLyrIeoq4muBhcDk0hOLO0xsU+kJmKsHgknI0SzjO0oWLFmzJ8woQ9VvauymVyvi3X8kSbK+gk1HM2OzkfcV5LuExYJhensaRlNyBZRX+dHSd11WVI30CblFoTuEywJii0cpwnP8cptvxlNzh3KLAQKdosm+cJH6VDh8niVgCjzlcOmOeMyUfGVG6lHvOcps9FY46XZociEopMcB1cM2B5vcEi7tM0TO8JdBbdQW/jXW8IYeUEy4NC4HOVWXs7wExJB3hvD2ZJvYsOiDznAC2Yaf8ihjChQKoTuvi959ZR/yTl6ONkyOdxaQh17pATUME76wewFYow9w6Ywp0L9iXtj8/KOIMd2GBP3N1lt2uE0KG03pGADZ7xvRnmSEe1eshM3D5dYXHnyfoFjdnAeyhZ9ImxrT4wxo6YZrf3VVawJRqj34GcplS+OQaZUo1HmXqrjjBeTnT9kXDd3glzExhz+rGakGzRYqbzoNxHLbExfKSBAxXw0n73ifF4qH7wG4jdCw9iuA9JWBEP5keW30x9dTbYnY89x9Z064akRJ7ZjDLT/mwWg3n3ty600xBFhZsyuO+GZnszO4gpNHruhoiizjat9zgLMtqYU+an105XpcXMH5UgZhSmQAo+8k72kAsynBJD5qnnR+WyYQowOoKAUEPUkamPodTQNFEh+g/XDaX+CUUx1/OKYPIHpEgB1RF3lYO3tZzrjwDAnlKt8Ooa+KN8mf6jSp2GrF5/a+mPTNPsj7zwfptpotEfCdAIQvmS1h+Zn9YfiQdQlT4ZVK0nvD8YVPrP821SP/kpgJK5O97OcS/JcXC4lPqJaXUPpl9UQEtxO3W28s0xosktdaJOW9Ke+iaEqqtnIFS5hxK/bwBBQVcb8jkSxv5JGkVw3VhQP/CxHyFqxwsPKNeqlPp0x7ejDmwzNVDv3JRM8b4VD/uv0/ZHFxKB218hcZuSpjYFNGVbaQR6nFDGikdT/yuB+DCTEk19mi3QdO0RxsrOrSA/tlmY1TT3R4Za3OyXL6cR5q1y1wksi5xMxQCgKC9Ly8N/FYm+oNqMrnN73WOcaGEOJE21+optui8SweBHsGBKKNiKuVNc5xYeHx5jmjPDF8bmv5MQnDfjq8pCXRpPw1L9d7PRV8qU27W1iA4nm+W+mmz/AYZQyh5S3AC97ApUql772biPTfIuJo0+kkcoqnCAPjJjXXs4FxTm7H2oK/S0ImaSiarbQu6yQ7tWW50dK+TDliIEIgUSxvmXbRcp9HPvDqVSvkzLmasUguxtSG7jl8EgT1NGugh6eVcThiTdxosAObHxhuhKSJAgmvtnKlFoZWC5llsxgcKUMKxok7a0+N7UEntkKoII5xRciCLFwiK4QEg2Ey3PrT8VLP99epM0917WLFf7A8b7IP4QgYY2C5rHrvs5s4/0luxUcNa3dB8hh5s0TPZLjJPXTsLE+4CJk/cewBSz1ZeFkfc+eH0f4dJH4k2IMf69mYr9KZuwSozHwanwcebsfLhlNhOOpv2WNsHsfOgx1YvI+TCZ0Uc6sNYL4nwYZjYbLrv9uXvMFiG73bqQaDKHiGcGTQDGdvHg8GoZwI2AN0bTZKReBoQTeVXz4BBaYi0X+s5uk59z7EQQN9Ly160Qd+GUS1E6B2glnWeMndHczrs0nMDwlaZzruda8pHm8R2rEyKGelfkMFF95FNdPE7Cf9FMTk6jSoZddjeW9mus+ZflaeN7f/Cgtwgm9gEm0t/MGmkteHkYxf2WltBeFQwmrHQ1Nl1gvQ/iGnCSzRkK0ypPR5RJPjmD/HBqdUy20Qr8lFS961j8IWGKhleuezX5aOHnbsGIgDU7ts9X5Ltz0mk3YB5IuPFeL4isfkYb2kKOjGDWGC3vpAQKOFheYILM4jz6zii/p3f9udH88bk78pu3fNVGIK0V4rSsGTFOIkOKNv1d+/Sz+UtfAtMoWjgFHzb7+MPpxC2gZsodMm1ZtSHjwmtjbEGI0FUxULob/ABsVRZNpp6FKVffqql0hsl5oM0VQckNnRerDY9rC2Psz4LUj3J5iHvBM2zhjg08dD9+vqeW9XTkdAt2AHLbK/qHjfmTNLafh2hPAVDARdkTfq/NNOppEv0xDDGtu/P01550vmIozOOcHu+Gmy9n1Lv+9CEKrj6tOc4izhO4PzBs5anLgCN+III/8uuNwCtvZGMkuXvaLJ+Ozbl5Ri8Iu1XqbyoXgndv5N+3l9i6CKF5HjpVeV78Zoi6dPT18aSlHCdcs9KLJyCtiGPTYbUaUbHI2qBLueUjTngI4USGkHGfNEYA5wD9PJgbNgnKpQT0iy3gPbDWJ05sGk2XvvFHGzeX3NeoowUmpRgTyvWs8vBA4vmulYxlv7gvKRPIxy5s3OUfXv7GQ31PVPNA8wbFHL/a8TYEDA1v4OiOv7Td6Tv8wN0hAlb17RsFq+oRFXsfskjjHmzncKDgipBzVaDARNAbI3B6s/NbUdGTkYW1BTlzA912OTPD23hqu5B1xcTylskTHD+BUDPNW6i6iNVQcp26Ft1fd81q3eJIJRPc5WBCxbfLIoLnLBtgFvzbfgQi1Ts1TbE6+lzs50U9IJFRRlg6MIFeO3MfAnNQApPgB8P6cK6n6cJKcsqUTlh2VBSmCtKj9ticQoYhZ5yVOw+LAoolEtg41/RM1igth73MqqObnBloZ+lx8KsxBfVbQ1WF4F7MSgJ66eD52aJkknWTaHHPJTYqF1kX6joSCPGMSaiWsa89MrJpHHztkrNX+KLHI1VreAwmNb3nUhrePVo0dVjuHIrGEpwDw3WdIOLwFTKfsx7Y/gNI1O263bvJnotIl0JxyPAYVet4wpvp+3YjKZgkHU+xT5aBr1Tmw5YwT6CUXmxzHEkBr5ThuT3v1me36nYnsWSPx3Lk4BkpKXAKcAM9wC6X+DIvb/e0oK6kD3B0TXTV/wUYnTSGsu1asP+YNURKP/s1ayN9KLlR32SHRIq/2xBlZTEZqxbcyWqtsnYrN+hM3vgD5iWhIWh1Bdt4u+2xexCMSU6yD6M7cTiOw1fgHKklcFbNkH1lDjhZKqwml7jY+IT5SQoNPF3HweF2yU4fjz4bFressIycbi633qImFH46gSa5kNRqfO4RV82KJZHCKaxYUjiMha4svUwRph2azix5AhnzigWv0nnt6VuyFinuQTmbLX4eC4LsXwy67DdNZRLlY3H3YbDh/vdr/k8p2/AVHhjNeItiK4HSkfm47b6fofBCHcYZEBlLItbXFbIazb3EflueB8ZaoFfZpf0MLX0plDri/gMR/WAEyEUkqkGV1yYE6MyV6vVOZDNgQmL5dYVGImRlWwg9KzrwCQrK1sCxXJz1hgHGTGvGAH+0nAnxvtIH7iKaK5GTCBP2s/aoq+dJ2pNIG89iohFC1Fb9SSuE4c/W6RqgU7DUD4Cxg4ahQsqPbcs5C5hnpP1CzKpz2/QKK9pamcFTDk562Oacfiz7dTCy78iA12sU5luFIUOr4VJsQGgdavKfzFsMiQOiePBO9lw8kjz0lpAGv+QE9m75za+j4jq+ZQiMYQg9nCGCBNeD8u1PTimX01zZMljMrxAf/xOITO3WLRsW8FOwAD3dCOAE38PyIgbfAzwtf8Ka/+j1gJp5xGnGqEwXpmm7uGESLO4stxF5uD99i+zbj9Isksxyn98jFcapdHvqZjpz71CLkJQSHhYsGvwLk1yVQRQHoRFU/O6ojZFIP7tVfDL78GrTXQYj/6hNO5Jj5xdMmZzfX6PFHREf6iCQrbGFmoBajBVfqMkmROaw4HbiovUm8f7BVhA/FDDH5/ZA8nHj/doAb9zcRujqVap2Fg398IfOQt+e2UQbp8is1vHh7fecrtfy7XWSwwnLVLDbfQ7IskkR9NT1KLVky7JzfePGwfZiTFSFkOGiqqJ6tk8cfDWsM8r81uYKDD0dZr653+DGm9Xhxr1tiduzgte7dmTPwO4eN4RRu7vObNN7HEtM5cqboQ3nd/050hNYftN1T5EZdmy3T3n2Y1/jUFbfMUluEaJN0X2+5g8X5XJi+h+6aXScGGb98lfCmoJVpQN/k/vP51+IclFQtZs1SXMB5Ka9k4uojcQatX+JMdnpHf8i8M88eEzB+K332UsBdqjEyAa34TUx06dWeWZZDcf6JklBaHnPl12VdY05DH2jl1Je/ev33O65F1O3dA1fP6zQy+Kn4NQyGuaLSMmmK7/FkiIXkG7iNXTeLsbs74k9WlQvnkfK/TuYt+SSluSP173KbbpxAkPkqUsPEFFR801QhydnVW8PHwJvCSO+GGo9aw3IUAimrLiZH5+CsJgf4WOaunKjAJ0wzuZoDTCSixQgYSfST/DL3UezkoKvOZaRzFdylEmrrOFJGyUBmFUCPDyki0W8c0AuuIhUms6zLtmzbvUbvnkLX+Y0tyy17zkcxSPNcld0q9LKPf3WB6sOTZ6h39ryFMTDYd5bHwIHZbqS0Vaxjg5Hpv5V1JTrW1xYnMhtfPk03JwWBhZ13WbTbVJ/R1COkP1L5c5J9SyApZ+Ie3JOVbJgEMJt56yATaoFHTI9ath2Hxd3nE31+C9h9pQNNvgLnmQSmBcOK3PsZQp6BfrIebdJ0I8dP0khibXdSYSBmsz1x2MlmjtJvV4tJrVZjFOxNZ1q4cxArFKsyS6iqlkaQxd4Vy+hF3RvZpWfihpSuK+8d+xRY7zvPIfHUGMjMI9Ezdxbr6RPKy4bfdUn+McezYhTgvxQkxgJG3jcGtf1QVEiV4TAwYQ+3fIUEcEf50nCvF/OY5rPyCNOfrZjYi8CZ1jahXhqBNi0yfOZBXiW2R83zMNhRp4dzZYeRvwgSwrA2ItZM5PzZf2jlz7HNJp7NI/gHEH8oFiLCsBY54/JF5dG07Gc7TWseP9Ksn81sDZ/qT8gRUC3VGji5wZlU++t+JlqQ/kUKgWQ7+LJY8Uut7sTzKKyHa8Xz1cM1HLnGu9G/lrZTsk7duQWypI22vY9QlSnfi5pOK+IY8j8xjU5lvIpOa7Ew/g5qVOXehDRQWoAEaUuGj11eh2N8YnU5SpnT2SZqaJcA9+w6CARGlqksYIzbQwynWSuHS7B3AvjT8J6uNFww/i3t7vxEOLVx8jI6WN7ncXx0ojoR2LC99LiXt+ws1/ZCW9kChHHJ9XIl2Oq+hzfeyz7XnNBPyqtKW+HtRtY9Ru3atLYbBQMJyXVIOP8wGJl2qqP462+vjiHaRgP/TDmoz2fUsx0rMKVdkSlzppZHhe786iUu5t4nl+WmFT084Kf4iXZpobw6Pjxw2+b/ylSrxN34o7v+JXa19sAijpfujXNayGQmlL9EKtZ0qvrhrmgykNtn06PFeAvGJvCYM/H1+ODAhr0WzZVsm93UeV7FIVhe0oxBHEt/0ZVzqaYFU0txScVljdomxt3jBc7LqTeb/VNAe73RjCfz7sT1+92EN/Ww5nv90VonrssvC8d5RcKdsj+uSK74qmdP5HJ7r+dPdA+g05PMh0fdF83w4IC5q+p96cts104tLmRugqFsHiylgFR6GedYpZ+ZRE/aW9YX9mqYCUGnweDNqCq0p9yBb0vU8/kiCPTRrgdxzvpR5LPAyq61Owf3K4ZU/aUZBakycwFoccCDsJeYC2myWOvtp7v8hk5uAtZ0nj+5c8g3lcT6/WCn4/UOUT6fCr+xf1AsdsZ1QGglAtV1oqfUowVMRiewBtESF9vJkmuSRzLoOBaKgDSWrGDNTBBBet28Qo+fUgHzhL5Zef+PEJkm0liZBcb1jUab44hZdAnhiqytNB8w1LNAGjoRXjxsqIGulPONh9xxGQiXSKFas7HXhkzBiKPc40kley4OdGn9/ZS+oCxHcRPYWU7B243rFmttmf0AW77/EnEyjbhixz6Rbb1FPMKRBq1QhTJZs2IVfIFTmmYC1vz4Y3nLsT52+40h71U8oQa4SDJZq2I0OTzTTDISrwGiltv1jp4uG4Qa18E3GY0XnnovxXSmbr2KOYWO2Vjb5t4ZDsOJwa7ikVdoE9kKzq1bpRkdTjL6varZFeEKn5tqoZsndE5XPLAl5FTlKO7b0RtV9sxoJL3PSqjaiy3XeZVl4nSJyebCpoly4tsSr6xjYnfN7keb5kc2uqR6S2d1PJNrNyoUPSKKdjOarQv+hNEZ/N5R4hNqB3q5ttyBsq4vJAixUIxQ4rZ7ggn8p7ftjDf3GK+i5W34yNxVrR9elfkQXRGuYRN7euyAApE0JvYRNRP1hxg2iDK1kv+X8URncisPQN/Lkp6r7oyTQe1plPMEa0hzkvNBo4bl8LyMoUXVkuRqocuK5S3zeR3nmtg/Vd8nXoVe466KdHRDCT1VIfmyRE4I6wg1lZ4m84Dpq5HJLtHd9rACaXbyNP8vTKeL+S200iPgvaghpidVnuL+MRxUqmNF0WcHRpemrPWZMWdhpgC6JLGaLuQfa017jxFSuOM0DTjebn3d/ak31U7P5s+Le6dTdOeRtQ/vqAh43s9duuLxwY28E55XUfJtaBx1OITYMqaQxhMqqgaaFiT+LqenYuTrqSTLpmTLqZUuJI0OJKpMOkTIYzVsXnpb48Y7VR/XNCIRCxeXVXCwi4GfEEZ+FU/Fe5rGqy6bXwxnp8jrNpyyIkevn8cySp8Ab3GFxHq3HSuR2St94KpOFv//hA0z8zonmx8cT4BCPQCbcl3npjHdi/oows0jOOWtp4GUr3MwsP0LWABqecHDJrLsjaHbgRSuD5uV/IUn8nP+pXAc47XlvUM9aDvfyrlhja5ZVNyRXvw3LwUpWmwWFVsMF12WYaLbAyUPl/D1PB998/XYZbhbGpRiz46pkO6gfT2jeie1jW5ZeJTvQHqisSWDbdQyCE0Pit1c1XMMH5Wnr5fMV733jjhUxgLhEUlEvZnBS/rNvP9e/PdTs7WDQg2PKhM41bf8AihoUCXKw6r1GOEUlz5x6ANacsYlL4bShlaH5HwSV1gvkXf+HjMuwhfPzYSjhaeGy+TaLvaF9T8GWJeJIiTkIV8lllXDbGVYkl6+iwtRDnadGR4SLI8KXMNPMre3xh00zx4UYxdCQKxy1dPQRRo7y3wmH/sAoG9zfyAJqOqor5FjVz6qMPVyPAPJ2WXvelOHYgJRadtXkrk+w2Q80XE5MwOluypPsx/eGnawMU1bYI2m+XmjW9GOLOPUnrACq02Mt/sd3uDiua9+it6JbHyXtKGAvLcVFsZUBH/kof5SG4duOOCkmQmtRGxEvdDeOAKp7c4B1QnLi8hInnsqzn9NdHiiznQc2tw3lF3056/nARgN1O6c9lcOFrc8mBlP+qU4MiozwuQlcjw6FBoUIRP+XgxdDgx3mHmp2BZKvlcIbpZVRAhiUUKYF9AKWzLyOYCyIAyPtZUqG6zcv1IqlwgVKEY6BIvU5zjniBaWLVMZYXeBdUTBJSrD1/ylo5yh+hjrsj0WbxvzfR4wy4zULsinCNXUjjKT0RkDank1ZZwo7xTw2v6pVh3dOc/xSjnA/ess/CPC6ZPj4gE48uMkk+I0Llm/42BtPPx7vSKIWBUBG7W8ZF65J0Y+dO2rDUgpQjbDJhu5t5VTQvYMDWm1/DHPHB0ujGr3LtKgXzkkP3C3gG6zjMLoHTvKA9siYBYEVs5IwLdtZqcuic4Jn6fi7Ph4x9D2SEYcOb/DAXDmiUhFxnVBTmn13xRa0rv/Y6DfLs0NuhSGDohM1dgCWcpx+lA0QQU2KXFG1c8MnHKCuYKkEgOjRHsnnNyeIqGeSYFu5eZqFzh9JSYj1s6lT/Cpp4sLcQZbOi45Gw38fE3dQTdLKgiD2KzEsW5++X8XvicfnthXPA9/YM6x4umDZZLVYtZQAtI/NJsAVB+5IZ1W1Gf0/vLazcLiKwab/wYdjY=
*/