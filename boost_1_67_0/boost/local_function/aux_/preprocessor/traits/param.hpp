
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_HPP_

#include <boost/preprocessor/tuple/elem.hpp>

// PRIVATE //

// Param 2-tuple `([auto | register] type name, default_value)`.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_    0
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_ 1
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_     2

// PUBLIC //

// Expand: `[auto | register] type_ name_` (parameter declaration).
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DECL(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DECL_, param_traits)

// Expand: `default ... EMPTY()` if default value, `EMPTY()` otherwise.
// Leading default is kept because default value might not be alphanumeric
// (e.g., -123) so failing `CAT` for `IS_EMPTY` check.
#define BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_DEFAULT(param_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_MAX_, \
            BOOST_LOCAL_FUNCTION_AUX_PP_PARAM_TRAITS_INDEX_DEFAULT_, \
            param_traits)(/* expand EMPTY */)

#endif // #include guard


/* param.hpp
uP+KgSW9ZUf0fFj6ndN5zM03QlIAKjKKQ07grfM8FcKJpwwrK2Jy77iS4vSHuot4QLOU/v0vOQVa8Dnb1n6GMwiPBtOvx8Ieg8Bb1ftsryyWr9t7n1JNXNaxeXsxuwYiOH3xQ9twgtVeCaRrevswRnwmHIeZKZiDN/ZwCa5ulFKuJ2XsLKXjwp482fZp04sENw+3uogMvBNyD2LruMHoH7anwz4P9e2cudfIHALvHqczqD7jd/mmEFbi30CmwDv8ck4+AOwzTyMX3xSHaAKOBAeN3LHjxIBFD15xMSnqG5HPfjmSqbSMfQRMVFH2SjNhN0b2CrVixHGjbBbZkq1mMFaNcJQ2bk0fCX7KM1ppgeumjZzUGvflMMRKnt3tBlBR/Ha0bBqWSnrseHSKl7OKgxJgdIKRXZAawPrzxgbyPNlUK5GA7qj4TYY0Blxd/NNzOI7VjWKtdX3EwQOvMr14B0i/brwwgJCSHWuRtjgMFC0OZiVai8JuJwwXbswDy1rMHiTFJ0vtU2z+/cwO4D0ht9UcvpSJ0/t5PBKLesN5fkejO99kLeuWg9VJ4lAme+CB8Gy+sMS8um5fO3MdtOreMsYnV78UYOUJc/Chd99DyZO5i8/mw0udfupZE4QRrQd7jpbjd8aT1RsMv5yhM4+nvatsGVy5R32wpGgcVFzunc5nNLk2iF3Y039G4/J0NMhHkyiZJqV6S2tt53DNaBs1mCOwYrezO1A5sfHdJdwEG3r1GQzYxUGnNxuqzLkM05ZXwFupleAA+R+LKxN4LwnRfJmkzE/e4V1jP2dw5JVGWtOMskJAPPHmV74rqULJg3nWpr2yWG6XfGuC5hskPxsnQSvDfTSmNXiVGy14ZaTWlJRVI/qMjbI5G75a/3/0XVxxhnSOoes6q/Bx62DY7BKSc7ttCWYFdoxcehcsV/CFIJO7I9HTUPRBHFT6J6lPYA3UB49FGIBiYmGYHCSZ9eeU8KXWLTBQmmsAzlaOLJAhroyy+DHEaTtJMwdNfHYKgHg3TWPMKeR2ktZOeK5BkRVRZ8Kue0D8f0W1sOib988Grshpru6X92PqK+TggLKBj7u55+scBQqYO4sH7j2cEhj5Z4np+FIx4ZBbwHjiwj4/cj4dR808cqq/w8tfZZ/Oug6jBaNZ6ugjIrqxmwTjWM03nyB5yvuOh6X8uJiGjvjvzlFIZMJiRk9F3jDig2sUY9jqRG3yDTDbRORUUlsKsKP0h5konvA77DCj721RUHTnpt9i5MP2InVRJtgRCznhM27naJmWpNlV7jaRrtrd00qzL6MQCWI9ugVgyJg6s2C2yRPqJ9xM9rPQmZg/R9H91Jf4llDjBr8dQK+lOmBymNeNwvgw/WuWVutgvoCiuKv04L5x+4F72/W/byarXz4IeLPj8t2ZtFEmfZGrNozP8sEYDy+PiJrWUUiMN5cQNWi/gk78Sc0OH2jkfkSawqmG7fw/AoF4LpZRn+QOhdwPC3tX3oXQ4VyoA1NKkZSIy4KWFbj23+leJn4OFnQBhK135S3LIFh/HfFGLrqeWzMtfjbz17E7h4zCnZfvB6OyrA1jwLIaY7gSAOfNAuAMVd5O1ezbMUdZY5zac8w2wiA3uXFHNeS7uIpvVFBeOl4frzkMhfhu6zKC4Trvu03a/bqFI5mrmdbd9u2HbS7sYAuX5NSep9OnnU46m9nSiqhBk/LQIbtkfZGn1OyGC1ZzD+H4EeQ8SEJ7FvRmZ/fcsH4hxVunM87yZznTeN5a1+csNoMxK9H1W7cFbkE9Fm5J0D84KyqwlQBBBiyUiSjx1N+DaNC6FoYu4Y2nFp3/LmZjfAZkOqhWzHjOQ4+JHoJXxX7f5m20lw17dXVj8IBlBBxaOwyqyXp4Or0+n/aeteBtuhaiARvkh1maVcfnVzmYSo88Bl4XRdZHc/WgpLNH7Fm00dAPjQBnajnc/ouPxJClA75thCbkyLsiXoDvj3JvREClA/vdgQXPEL3yAK+vY/Dxr9FAHr1ge8LNfbGR/C5+kAX3vHlBIKWjVrXAP27+bDKAZuYemoQ7RR+bfKzy8huMzv4OxT8pvIc/Of5q5fD5I97hKezjG5GVBLCeix6s/+rGvtfmsGGPk9ChncHILeVsQ+xL8nRKspEnTAhSWNlm2wDOPx3sf6qK2bExDBrFzAMdp5Rw9PhlBQFiihgpO9er14PzndUxVPpCEF/8D5sFO7y8mDQffiRXcYK4xtXphWLP5+19t84f+NJnd+z7XjaeZ+4BqyxlcGUMW1FLmuTkn3LcHzn75DqA+Q7MS/nc1Rq1QJ45/c6wHhBKqN7oOAELPk3aXfLdalpwxsJleduz2+UAxUKk9XNFvH3quBwpnocoeyAi2mr5EkkTGckCa/m5mIoJ+zZoLsfaIDwInt+FbFBD+tEsCb5LFgC5zDJIp7PgYzj2yDcNthlveITASSvt47MFPXU61M61vMWfjbiW2wVdBXFneSVp+y/f7kmOOWl0+5UQ7ykPSJACp48kWvHzwkgDrLSdJ4uI4PxCfZ+bRhw5WqSehflOImezX0/24oyb7iNydE4BcHJCBBgDhK32lhuWxgfvIcMc+JwJSzZC1gJJBDsm3gr23jRuPrxaOUvbLFNthnGP+kimC1tyZF6g/jRUadhAfg2p7gbBsLOLdTR/5rmpBAgxrkZ4Xalyr6ihreSCest9FwVWTIGcSo2QxSCptPf80KRWnoh4xwevDm5c59BEj4R1EkIPSZjVTiVveoRtXVi18bLUQ1e9yxCQnbtkVI9LnL6GzVm6ZZpUWkfWchfZHWH92w400ftPv1mj9OGA1TXuC0fY9qDbBn8uGDwu0qfE3ijrC/rAPgiOJVWvW5zDNf1YRvM2umq7Zp6THWGeAeStOhIUp1G/VV81j06p+hvRrt6yeQEcYNR+dqxwzU2I0XMSbqevjax0qfMXA0kJ3z/yrPFOQE91mAlZTTnnG/vZ87MxRtYCUFj9qqZN1WWdbS+31AuGWMkZqgyGCPmMi839P0dfDKdhkWK0y0YsY1uRIjcb0ZYkU2pRyotmbFCEa9gq87YqOHl7UpLKo7ULKxczDBzGmlKaMr6fPVujs/S/Q0N4x4/wBISHZRP9foVSWOkY8jYCk0muOTc2gMRbDL/cVkMViqSA1ly8MtJ/lu9NHn53qCYG/CbwyQoTZXDK+b5LjmXpA/clgg1esWNrzOf9IFcXnryO6qU+ilhwQt+6MmsunyNCeaPGve/euG4rHAvoZ4n2/4USNjHKrp4c5IzsigyD6uWwDf3JeTPxeaEliqZpO14bIR0PMxVYKtbfYoP5/SlghxZqPhd3WoyWd+udtE9FII45J4JxFNKhR35xQGKCXJ9jg/CthGG6bS4s6NTL2VhPd7jiurQ7ZCWOD7GR5KOYi2fLmXI9+c+3XhSVX0kmOT+zzbGlViSlpnRrfwmpkCNaa6RAYI/G15FnocdBqOGAgUJBEB+piMQ+b7ieZHWNlks0OJBtpYzYa9YorZ9RpbtY2tKWryUs2H4ezIMhwrMllCd45miAj/jXwemdRE8Uf48tSrXn3lHJn43B73luLqAlwQFdInIEwApilH0GuWw0X9TiN/n1poEr2QfBvHqyZYJ6Udi6LvWzeBzS9jUOLBck9jZ7LtWXqpORkAXeUQMmt3BZqxMxE1CAPp9ZTOMXW0IFzWCvJHmYL+cJmX+c06KR1UYU6PNpZmV6/mq5HhkIxik+ddmkNHO7vlaUew9b7tQsB3Y3fh94u6Oxp8T/wFKYYh21E0WgBW5N744oCZ0MrAOzXyN3EcAA/CbTPsd77/YF5Xbfsystpl0F/zUVh+AbniaiuFk5A9mN1VDNult54AXcf+gD9Z7B78UhXusdJKMh568fj0P9TWr/IRhLae2AfDFiuxFKlCjV3gqqQEffauEZXmDyZVWP15kNP6bQQM6hMp4fxo9O6/64wwQB54Jw4U8vGIKDTI7BdhdnA31RJ0OP4Oi0DynxR44pwAt8qBslC9ABPw55ZysI4bbwHuLH+m37wpTKx9/quJBX/6EzCf5SY2afJ4veVcdMkzQSH1WFJxiFyByyMenSfPmkluD92QIRX5F0YNx4fLxwnWicK2RhxEOw3odmPmYXQmKGwcvi2tkfizXK63ksFSD6VbGd9X0mrheMk1BzW5UdoyemPZt0XY2uju8zDkqs7OS467paSjblmm85tf0azjG1MD23I63cdF6Xd1iEUcvTA+xjM6bwkHRaTpyYL99cbiBTCS1VGfH7D3ahtnXRmPZectxtwmh9snEteIZ68ws2n5S+q5BuzoTlnUHAUlMFsdpQQF56LmnSkL6moe5QVgmcZOiQHR8lnnUPuqLt0lcYkokIF43oTOz2gKyEV/t6O+mMOqEdl31cRT0AW4o4i2cCHitGdUH1nPhTnV7oxC9KIgJGNA6+dFxvRQyfIlG6bRHgbdV7wQ3Bt/a3lzwcJlGWUbdByiujy6OdYWPFKdhJ+TzVLQOMIXfUdA/doWDbXcKgbqiBUqBolEE1qjbpImGZEHCwrKmgJNBcptrYOb8a5Hwoze8tghOdl4mZ20qcjEAnICaBAAaUxnr50v78bhPlpI68Ejdnt6alC+jZbbsTnF1aeRTRTGw4onViOTngg5JzDuzcOM3sP55FzMcdsH7Z1yeP9qLRhwxteOhBM4mQeevwo3JVq+1X40acxP8FFMr9bvm2OW4rQkX7hxsK+gaAocCk6u1+sDQFW0UQrug4YSZ3bxm8bsM/s6/+Ou3Uj+Bc0WIAde8zy6sDgjrJkjrAI6QcQ2/QFwk3Gylvg/TzXz+yGq9C8U33QeH+hYOffkMf2NIFDVFTq60exA9YGlf5P30l5H+Dvtg+jaC1VydfR/bZAZH9Kwj/mZjNvv+487eQj/amVBQCTn3QP+hii5Eqf3j6QiGdiZHS7++EiwMWR5hwfsX/lOq0HsdkycNuFlVc9GNFNnkYBZT3HYFqjoqy0GwlffvXBQ9vb8KqX026TYfM1XWY66u881OrcjvUZ+XJklBUQngmcHCUiW2wlXjP9E42fXwpbm3fxOb+zJSelfbnpouNXgVNHNlQAENtAln3293SkDq7QEpTQuRDCQY2Hu+0NhOvdpKyVnFypu7niTH9efWnmattDQmTVtOktE9+JDME1ilFzcME0ZBc0uUQ2i6iLOh5JyVaIJTl72PiskjXI9lNLPEO1q9kzVaaXCAq+uoyJv79ULHBoC8CqJhWJZan3g3sCJRc8pm9jtaeRTFFRxmsbechVxDp1bAmQRlh6Kh+SZmbr67d51TXAn2PkHtu5j2IMA9CMOwldd25DUOx1T6JCW0JuBP56eR8WYSoaZnijb4Ll8+npKyLJBHwFhHrZAxgGzR5MuPSya/66jG9QLHgxfjJBEHQL4cuyZCn2qNdRzPdd3M8jMtf1YLrheJieXlYdP2vpR1XL72N/47GRw1DTa6lLpRcEkNI6li23/+KFT7lS3C+wVHEo+BJsp3r4lf4+Fule5acxwH2Zt9rScjHknpKSSVlNrK74epAUtpt9fPR6acO1oEeVZwu5Q0H/O4aG2Tk/DxIxi5UP2ZbP4Yy/mJu1c5KJUWzkaK1zfOkIT22077BJLSBebZRD+xvdMvVnw1r0ahcGkEVHERIRTKk9r0ablbuUj7u4EyeoOvIxkR27wM0Cw/1sku83BUjAiZslENhIRn0zbZe9iQoZeWRFhmV6LqoLw6sxRVFkxvmXrtm1nKVq9dln1KcPzxjhl7mbAal8WeuFaD0G6mlsr5oqiKgHjWpKofau9k6m1hi3qOWPEfE88EmTPRHrfXr8w+7OQd9yKtYVFEUbzZ5NpY8rySw7QfBDirzjis8z/fLp9rlOdVVcprH0VVdufkKEepBKxgR9nfgAFbwtyS9XEOogYk581ganzRJi2/pGnG3PJaX9LABsdca2rCA8DDjWuZt9XC+XhEpGNdPEGDIDbVPCLxcEo9NMT8UbTywH7zIQANPSvicRWF/tUPtj3yAr6Xk4139w0eshlj/Ci8ePwAALP/TZTRdY+ujIEIlbWRtxfa+9FcTuxcf8C6ameH/K+IFtVoH+FU1g5Pva7cdM56dDCM9WYuNnPwI85lln8KnMLppqR0jygx+wIOpwbn/CBiVIWfpQdqBdPF6kvvx6W4qlGil5JKV1lDLNUjcqsPh2n2JfF6k2QKMFbsJY0n2ws7ep1jnMfy6SCfcY90jmbDqAjlpT+Q/7jhy/gwmR92UFslCSOHRvLmeV9tz2lk4jI68I5kJ464UJkH8n+2S9v1e+DZ22jk5ijUe2pqHYRVl5i4Wm14Hzn9oxCxpa5sgc5oLuKerh2fNFhZxczemJMluUFFr+O605Jbb5drnpSOW/GXad49VZpeTgvLR69GYrS8ys6bRlFyoeyQYjzV4O5T3CrJEweeSjYn7B0IspguuW29dslPIM3qMYnjgVP9eD9vwLGezMvIC70RL0DZ/zo4KfVU3maWWOaMJv6VvH1AebKs5vDJnfId2Vx2GPph2UJryJH9rcqSRGO87O2B3AxR/pnQFdxbIl3r8Mz2xzHvoHSbgqm2cSgjICyv1GKVf0KnTVGnTK3trDTzPswjib4e9tm7DIOP31euEk7Gv7qXFZG/OPi3cI8TlyCNBnHNWn9xL/zHxq3Godv1b/PRL/uXpIoR76IDPj9VI/QOHy6f0yRrbvz8CeMU0i/wUbUcf8pDXm6Xwj4cJngTUIElc/ysTfZIwB9y155U9f+Q2ssiGn+LHbQwKVTkL8J7lwZESnqED4HZ+ThhTskGjKmUAg8sSdEghnXPGzFzyEUbFDJqby+8m4RqCnKLvc/x5xg+I3IKMfZx3c5ymKZ0lYTEJSykeb3gcNPkLvoodDoZ/HwIXNx4RZ4eT5XtE2PL2GDV6/5M8sfQ9hrkEp0DIZjn4YBXQsUIWQPWXzs0BxaTX3Zf9PG5CmOQK9JuJHZ9CS3EbftgfKhMd+yl+zzY7efTMv4Eq+vbSwNvo7IVGIwwX2O3ThVZmd95ZUUt+++GyonigZFWyIRQQcHFDe5dB8wnWKAYkmfraDau2/Y0MCvYHtEwBgQ4mOGcKlZs6D16FBLfUm2Si4q2E9WOKVDyAIhndP0fWD/VUFutH32Q50GwhF19SxMC1TBuINYLxWHIIzD8lzM0oEuysEVNQKsxq9HK6MON3kTsusrM9wbC1+d9sj7AoT81Tb9mg/pim3o/TfA8B26XzHWl3gc101F5VUs6L1u0yC7rHJMAZJMVBxGZnbmdj7nVNXzD1W76Dt4csI6+o46iNFUxOwkIjlpVRQ97qEspyDmbainSKqqXfliJayOT2pjVbUrScPUJ3KTyNINy88Q0YtTnnWkpxukaopFZi3pitcjuYM5EQchY4qKMxJkzYs01Y9PNtHBtY6fX0yI3vLF5TK81r15ghVraK+je8oLL6jZvmgBDf+z1Y8pnE4kEB2rR97svpQ1FpuftbN6oYeNSpmJxSoDQp2wK00FY7e6MNkLSdJOpdBSZA9DAMZ637Npy8G5i97QHnZOd94+6p6QUOCOtvj65tXIMichJVbs8mgKNavFI4mqAmS71rlXe+IAo/HzYCtEjkoTEUrIqBKrdx2SJr0q8pEEhlruEj2QI5Qazc/PY3ZDE97eli4jZfydbNpoUFwe8+129m7JHzQfk7kEEGjKzd02DjChd9zcie1x7bNZgiiYKpE4ZflSkM7KtAj8JO46zFCAXSn94YmpJBr3f1bNdX4uu8LPLvG9yXmJx4B2zVWXVke/0dM8V39G8H3kKC7QmkEkQYbspOROXqU7EKIZTmow2buIVg7uPP6YTiOOTtwB52VD+7yk4KF9APJi+a6JMdzp9PRgkhCwxm38Pe4RfCoWxwedw/dS3XrurWt03+p5/Fmdhc9Eu8UBr3P4VLOvjhkQ1iZbaiJjwPUVz8r/8E/g4yr2zc/1f0L3SIB3/f2Mnib4R5j2eLxLzN4L/772NcpS7Lb+IFwSGc/Tqb5yqo/a9WZ/p3sI9yQ0QPzy0UoUOWf3A3gmMiOXxzZz3gHzoJy51yQ1aU/2klbGQTeGWZVsXabaGFsBO3RXx7Foptm1hptfkxE6bUo2q9BXUEdUXjDqqN19puMplsanF7Sa7CfmiBeY+vp3UcWmFCsxt6ESWFVGWhpchLNF8657YGwo2tQ1f4Fc+QdaSm68dvscqPOse7ojEKvtYbWNsIyJOkWkXe/JYMn/rEVzDilI69uxkyt0dkMgO0vABvLNNDsC3+YFUTTkMeH7YnFP+UUA7Xc/aHf6LqAxwHsrdcxCVR3oRTO2jQ0cj1G3BlFZIlFXsY5Fe2Z5PPC69x5W7wuI374/9mgLptXP9zkkMGFm0UJXyNsOlGdxv4FQQ/t7fgboMqoi855BBabyREEZz8/gqE3scLKOxkcRGE/gt7NSQ71BWRneg3PLVcD6zwL+RSAn/mEeVZBWd3h0JH/e/4Gm7J7yqYmu73zs/GuWjgVP6oLHY9+BKqvT4dWHqDWLB8RFJIdQuYAtNVMjVQOd4u6Vf+HmYwptlofHzjyMONUV0O+466OTkVKTlfFxWrUditsH8ZZFCj8Zes0ySTw6yQ0jwsZziGeJgVcg37p9NPA+iStPS1Gp7PegOrjH4XSyueu5RZSD1cO2egxf1SKHMQDQod5da+mdVdtSpO/wTicoDp1lTCpxOfe6YW4FMQ8e80k3n2CSK0IbeIaVnLPLAT8bJudJd7mofMnq/p3yVnID1iwMXS5yJVAx0uUGY3ilbXWFqp1URYJ4UA4M7K7Bjid1xRu9xtaOZhYWJFz27Zdo4blxi0mHXoRzNjnCtO7C6YiKk0imR2KLbK8nKEpA3BuONibKjjzlLYzjizNfOP1S7Emkm4eKS+BS9M68ctpp0WpG9btuC0KNb0PpfR1qXH5GQvCJBWHh84kdhDonxZ6f5R1OYO0LsBB//hGxr2b98VKbVMHiDUZ/efPvhP0E0H3ZGuYCoczb/qBRY0Ov+wW/Hape+78QTrO2HkwvjV9yBCLeitWv6tV0TjjI6NPKip17DPKd71cQkuT+6rYsQ1coUZkh+sxI5VgdSS8xKTk3w3u0QomYSgK4bPYIvX1olFL4HyGNiQyLNtVFJF0+VGYvERxY8evheRiZbb7GdeRBENzVem4IM=
*/