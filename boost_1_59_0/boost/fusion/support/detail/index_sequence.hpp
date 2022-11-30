/*=============================================================================
    Copyright (c) 2015 Agustin K-ballo Berge
    Copyright (c) 2015 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038
#define BOOST_FUSION_SUPPORT_DETAIL_INDEX_SEQUENCE_06232015_1038

#include <boost/fusion/support/config.hpp>
#include <cstddef>

// GCC5 has O(logN) implementation, see https://gcc.gnu.org/PR66059 .
#if (defined(__cpp_lib_integer_sequence) && __cpp_lib_integer_sequence >= 201304) \
 || (defined(BOOST_LIBSTDCXX_VERSION) \
     && BOOST_LIBSTDCXX_VERSION >= 500000 && __cplusplus >= 201402)
#include <utility>
#define BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
#endif

namespace boost { namespace fusion { namespace detail
{
#ifdef BOOST_FUSION_STDLIB_HAS_INTEGER_SEQUENCE
    // Use aliasing templates without checking availability, the compiler should work.
    template <std::size_t ...Ints>
    using index_sequence = std::index_sequence<Ints...>;

    template <std::size_t N>
    struct make_index_sequence
    {
        using type = std::make_index_sequence<N>;
    };
#else
    template <std::size_t ...Ints>
    struct index_sequence
    {
        typedef std::size_t value_type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static std::size_t size() BOOST_NOEXCEPT
        { return sizeof...(Ints); }

        // non standard extension
        typedef index_sequence type;
    };

    template <typename Left, typename Right>
    struct _make_index_sequence_join;

    template <std::size_t... Left, std::size_t... Right>
    struct _make_index_sequence_join<
        index_sequence<Left...>, index_sequence<Right...>
    > : index_sequence<Left..., (sizeof...(Left) + Right)...>
    {};

    template <std::size_t N>
    struct make_index_sequence
      : _make_index_sequence_join<
            typename make_index_sequence<N / 2>::type
          , typename make_index_sequence<N - N / 2>::type
        >
    {};

    template <>
    struct make_index_sequence<1>
      : index_sequence<0>
    {};

    template <>
    struct make_index_sequence<0>
      : index_sequence<>
    {};
#endif
}}}

#endif


/* index_sequence.hpp
S+EWKR8zl1ZAwSpze2d01BR0sn1AS4mBIVN+0yzEN9HRgEODOJw7lBTwPlEpETPTrkvl1o/TD5pClzBLFo+vlSSG+xgs/7aMXVGBtbIqOGo2WQsB7E2Ex2YZ6swCdU/HYk6FeGUPEPuBZHOX/3zQCZcjkoo2Ypc3Vba5guAMM131f4iOCcH2Oe/lUULxb1vo7BcpKUiShqck/t1PJkQLjGVnTBJ/PHVj6konQyZ0EjDOBYRAjjQ4PtACrSiTh9EbeD7ZS8rpFuIA1x1aM4mSBMlFnrXcdtSo9M/r4gmdn7stbFFheZ4h25Lyry0moqYRnRHga4kfu6Yy1y5k9A9S2RLSn+mHKDIg9UKg8hGyA7U9mllU3zS6+8rseWfjzN1kJVggckd7I18Nkos6Ix50Ea6OX2ZNAD14a2y5OOVMziy3leQ2/VcX18VcSWax5OJa5hukOVQiA+jhp9SXIhRb4IpwSS/GeaKMTikcWiIcm2O5tkVf+OOk3nxCLLEzso5lh6VxuH+04esdaijL/zObObqQiUdLsDicnjkqKEuOgoA9OkDEJ7tVQX4BDFJpXYA1WY7DEwnTFY69Kbc+5xpSqLGT/xHnLFrZ52YoAj+60JPXX6oz/WEqCxYZEfui1Vsxctg1cYz9XzpHhqETVLXZ80Q8+UtJHYfkShzWiDMUhLViB0UV6MMZDgDVZpjDyMMyVgo+YW2wJglqFXnUROlrgeht4Acro6pPuVDjAU6ItoSLdxhBsf5LOflnX94YadE//otheASOxoz7zUnmBuGbkILYStFeubH/Ts1ZCImK46fK/Lu3xRrlxY60cYUrdDAC7uWLIbjtDmkdmx6E7aAwM4PLcA3WWANIvXpHS5eqwyjw7IAy4rJwKprXPLLiBbcKORbhBmdGimFjROMvzIkqmpUlk0up7keOdl4NWYxCz2zi5IyxCde8Pq79CqPD9aoyOFYIou/iGzJLVALu4YjV84eRngsCtqR1vjKphvdC15ogx5A3vbAWdf6T3RkkL7wuX77JxhT7IauLwMn038RwTAcpn5FSZ87TFPmXkw9LHaeWA2KjMWEwcqQQNV4PmWBS3jqxCmYliSzDD+xcVZPeHZQpLMEgkzkDn06IdxWvpx1dAMv/LpX1FNUbmUO5EmQxxIM7jQlKfPrzE7cQegAZZA6sEML/apEqiZrqff/6a83E487IhPkvF+FQIhhrYofsoc3G6E1ruQTmvVBXtWrSmleFuEQkskhXl1bh/F5Lv2VwlxAJ2q9JItFdi8/OlYVlVUtfck2DP/tHE+ML17RgtV6fH61wizTsYk6a9gXh9pZR3tUtCideTbM4Jbp5Ee1tOhfjrq657/0ky8seDyAEeC+66JPRQKcRUY0yDpr3Z6VIkeyfwCFGeBbxE402AueSTAscxxLNy1p8lfte23JhrEwI3W7ceXzH6+KCrpbNSOmEA6u688qKtwtqHRAjUU1nwNzT78dllTvjxuANU5dm6k4y4vj92xrpvpvdJvLRa1+RSDvdGoTV2AXYfvNaPl3Lu5UnIWLyaUAj4rKwTZweWOUhhxbAPcInLZ6tOB+6cCHQA3cnYUYB8NMoUPIhJDJoZaHA+bqtFQcN2Avv1/zkhkPRtYtVdXoNE4zNW+xwOUt0YLTl2rBBEOV9C7Y5wGWnnoeQ1ehJptz4iUuz9qonPOxU3X5dnyeFL1vbe54Mcl2MZqoCp9eZeZefbWYiiS5uy3RoncVPB26L68i2MYOME26VeSROju0n7HFG6wO6va7KwDqZJfOFjHWhmpZZb38cmjqv2Z5dalqKsk4/y+B6OR3B+4i6BGUihK6IeZHXfx0kzp1kikt18CvOj20oIxRHzxZQHqLGF3T+u8ECi9OOGULCjYUBF8nLCrfUjfOQoF8nlskoBV+ETzBQu3NewKnIReROEmofwVuZNRjD351cTJijs0eLurlLsHVU/xnutg3eacSjACjORvr0mEOxkZxqfPBTgTPa9O0ZRq80AILfbapl0qyqyHSS4h9eIIdOxhzxVjqgbxuLjLzIiQc19fIiw54WrDZOukTCZmycnbccRFGleEel+fBoKqoGsUT7xq7vzAg8XX1MtkL4uDuBjOLloGCE/ISdwTyflqJ5jBfMKOxFnLePv0WIaho6oSG5ss5mSO2qxx9L8swj9dZia+5MqrHvPx/U8qRT1gg2y6MkxbRnNJqNn2ysykie3f1yL3yITZRPCVdJvNZ3lTZ2YaGYN8Z2TirfJWTsY8F2YJp1Dkr3JftErxtXgqAtgOGWOeL2k4jqhYE6lkNMzvhrOdEJk1Ir2Mxikx9vfnW49jnDMXk2yuQqkJlEAiat62eSaifTJ8XdRTqRR4dObpwspOKo61uwm/Yh3e4w3QMxvrby+mhIhk54qLQTnWqOM3SLT7VIgkYbpqYycM0sSqzIx6tQ9rnJDfqaWp08L5QoPzmePOstRMRr96KRDzpqmEbdwKVoc4X3UL/PInZHxaOnCucl4R+CQo61O9Jas2Ze08oPEYfjazjoNq9lm1Q9EjjCU+UPJcfX6fyjimVF2asZnLVjHWLGLWdalpYdyC7KHP6gwSQ7TTGzehwWtvUE5xwOfADixDYL/VB0+wdNNrPj04ZqVpZQ8w7yCiFZzICTEdiROvOuwM+ZtsGTxWeTxYtjaV6gmlm/YkafZHa6OUWCnQa6wAlVoNfogPCWeGFaVry62rodhx+4CV7cz0egQSlhYGm1hddvd6rKZVVkHpffxBnpfu5HcFDEWCvwTcFUpJimMAFiHFeQ6lfkSB45Uaaqs6SEGt/FiMrpxdfYPpJCzBoqzNQHIkRsOjdblprVs5tIdJQzoxY97w0gKjsmP5gqZKUxcmHxbrJMNvKJC9+7PNZ7Fe1jceZ3T//E4gSD9636TeINspmOT5T1bHcg73nvSr+G5GHXXGUr5g8jB9iN2hSs4UknviDIMq8RIDEzMZ5U3/AzNq95l7zdXc+yOvxjiYLvmE3ryvrAP1krWnLq6MFaCIYInU05mPRw4Xl9beoeJLp7gTsf08WA2lG8gVrm+PUNMPcEnKwM4IK+curyOia/G4AsoLuTT5oNCOl0tAK+b8MjZwLfgQtwtCJOIPOMy5zJa0wRY7m0C8PCLCPf65EFBTpV1VC4YbNO08a1RiwXPvN4GLB5Myh/NL61rDY2aU5cu4jlkI4DL0EChMRg6RcnMBvS82XvUVrC70krFjXTLJsVJYHaC3dmhE3DquNsNypPk8isw/vVbmjBdH+gAo7nboX4DlWnU4YlFQ+pVOOoHyhtDzE1A302mXyD4kqww+gNyGxiAmz5zwqG4xZUo6MGBCxbqjdugZ6nzGk/jQYLHe8e1NEA26NQmhzwgmRZHz0rl5qItFLMlgt8esAH4BvDtjdAgl2MXrhcR1Log20hpYF/TaLsh0ntJNx0NXvHJqMOQokS+Y4R5qEoXKI6jMctjA6CrTvWqLtUk05by7MkoitSXT52dXPRHtlthAHW8QFrBT1xBZ3GHDqMK/bOKDusWySnp3gf99a4FtrDTgK5Sz1xY0f7VmNW7fyyMHRZeHyuSIxVXz3c+Jmu2wkibbl8cEfu0jvfSnqs33EwVH28StFnsEQ0M+FfWPwVziIOnAhzRGa6djIkC2e04cqvvW5M0MOik6a8E5Vg8Y2TI9sP/jQtQpKWx8NkOB1/7nCyltpi1NXzZhcqbnpLihhNB9PymDekWKwxwS+xbqhMT3AyGpC83rKagmixIX1sDZESM8pIo+8HOuqB71Zw3yUT44kv98+PuP9kLf3ZrrWA+p5okw6e5tJk1vKhYdII6ToVncgOnnHZUlWp4vEbydTtPFw7MgUfhqqQLR8c904MvObVsdVemLUSa1DwYHfhwUM2f+a1MRhCzIflW2sdmq9931ZzcMoh64x7w8bBRVU7halXPCyNdv+uZiwhkwr9xAnrng/gFepjws5AshS13RDl81hfoRjvjljKWelW9iprO1i5bdhCFyYs25rDy+5BCLWUahMrdoVqoPfTsKDJgj9Gm3SJDavZu6PLIsxTuQNWGkhZ8aJTYp3O1yaQwVpL5Nj4+KvqCubcL65uaSW8EZNhIAWlLm/FcZhiAk12ySlIVZLVaZghX4kN0pqcU4r0VjJ7Vscs7TyYau8s7p0GU7Tmzyp24GUzxWlWR2wOSn6RLvjZGfhZPsBmsnyRJns/x61FaYtYKOQM46WVTX08P6GDkA8OmCG5oTXxxi+nLSdrC+jM5sIW4lJVO38g7uLlZteNoPm2YHM08GUhcLw297TAEGtC1uqGqK8tOcy2Lkb7Pxy7zUCiByRWn1B2JqCgLhs0iiQ/Wiht21GbZhZI9p1aYGk8JOxqwx/WlmpOcVYSiXdTiGhGEpbjbTj62M0v8CNJ59Pd+MNX7SrLQRjtMmo+Ggo6p865phXh8xnSAS/8ZkjKsnBYNI3uLOxXQpLM0Q/nEMmfZcnXt16z1zl/cEMJvr5Sralsas17rcy+1NJwN9BUmXkHJPQM2JSoUZXIKBwwWP43WWmAIzyGcZqALACAwD9Bf4L/hPwJ/RP2J/xPxJ/IP1F/ov/E/In9E/cn/k/Cn8Q/SX+S/6T8Sf2T9if9T8afzD9Zf7L/5PzJ/ZP3J/9PwZ/CP0V/iv+U/Cn9U/an/E/Fn8o/VX+q/9T8qf1T96f+T8Ofxj9Nf5r/tPxp/dP2p/1Px5/OP11/uv/0/On90/en/8/An8E/Q3+G/4z8Gf0z9mf8z8SfyT9Tf6b/zPyZ/TP3Z/7Pwp/FP0t/lv+s/Fn9s/Zn/c/Gn80/W3+2/+z8+fdn98/en/0/B38O/xz9Of5z8uf0z9mf8z8Xfy7/XP25/nPz5/bP3Z/7Pw9/Hv88/Xn+8/Ln9c/bn/c/H38+/3z9+f7z8+f3D2D23xgY80FJdMSqZ/s3VKE2HLRJZcsIw6FUVvZT6wHnxvHEpFWO1GPUYAduibi5+SMiFUzAbHqotW4T5+ITs4MPrva/czyKXFcDIks7MK1pmZXPNM0X4fvlziBzfhtUJRxXekSPh9Ayq9auudiMUMc2PZhMB7Jh/zuu9CZKxVXnHFOq+GqnnFNSdVKr9+w6pYb80W4p+14Fa9jHjqtFw0NTJEPH+Ld8QGELNwlSXGFej+M0oRia7+IADZJxaX9wC+ydDAJiJeYhyarebWq6ln8pn/LSwbUYqO4CqzIHJG/bec9jyD+CRjkgrCkuwL594zdAVitCSptf7l5MPhYly6n2dZG3dGxZ8abtk579xhu91AXb30+ragk33YXqdSeioCetOXHbK5jGmjRP5N0AjLtdvGc+HKOpxmaX/Z/ID1DXNBI/vpkIovm+dJ2JKeP7HpQJO6nSixNDQT4rnBUnCkUs0QMaSXl2ps5Bnt3R7R0W9PhcnQJZ9Di/ksoeoVsvoiJGLqRGBv2hb4VoCWZ8Q/hNDgYLwOrMavYZVNsRZb9WTjBoot09zaEczOLQ3Wx4+mJLHLGTbe1VqI+jcAIKvV4itM1Mezc7BydYakwJAw5GFAtQqeDxMrcC4NzEc68TeFctIbyLdePyWyYyjzK6ulUmHermha2RG6vnw3j4JwsVt1CMOBbkpWxbDZ3csXXLKA8FQGQV3xR/uGbaIHbK2qK71XEL4eBlfFKJRacUrIoQ68ZFPqDJRNOiu/QqAiGdfAeP+Dv193zpJRhQYHZovg4r1+wJlyaq8r/myQr5R3WEra67G3cYF1LLx1NMavJdQo2j+MTgtGMF2O6gY8848ABRWL9kNFtPTy6VctX2cJcIYfl5FHEwBXcaKwh+ZHNPtq66AeB+o4lvTE3SpIuDfE/N4+W3n0wqSRJFcMYh8DcV8ynowgUhFoVtYyb9KAMgL3sK1tFxGncogxGWIMtoPKJ1KByzqMicIgeIQQiZsJR0Uw5D2rBQYkvxuiKyUnighu1gPuhiSeo9YBoJRQdzx0j91GDdjnp0dXlQUF89dMn8Xgv7BaGaVPoM0q6uYeqLxHNHjruQCTsDnYDIMJ4jBXbHH6Q1kx883o6OunYIZvNvtkTBnxNRnNT2dFtMVO3UYSq+TSj9SpcFaCrxtktlT9Gm6unzveszmukMyuBns3KN2dGo6sLCwujRwsN9HHlBxYRhlwp8whmbA3Kv8KqsXL+Xwa0eUdFKBLEpJ4ASXxBmYDWFnqNSWgjCJ7Ry4iENsuhZQk+Oyrj/VHYXQC5Bvyh79z0Fl7KryCFEf5gp6gpwQCscQBEHkTQD/HvR1qPDnh3zGQ3fPoE2fzuSNmHiJM5Rb5evjBtW4ImiMh6btcfHAwzLcuSRsK1/eM1x1le0711U/UOBpGnuINW+VUQ2hpaz85XQd/dA2i1RrQ+IwNIoBuSwDJbRKJd1DwNFF7NFHXtBd/KXr4TYcnWJ6rw1ta+MYQz71VxAH/Xu3TYI6rSzvyMH5glgLGa1orvkTUxeNse5M4FUcud+LI5w5zpSQDd+sTzE9W4ns639jnBtLimVm/Riuosu3Y5/rvJE/yme6nTQfuok/cTyKScXbHDf8+L9W1Ds7HRuSFOUT5agRqe+1xjoeGvUX1B29j6nHve0xE8wKh/ND/sSY8dCbLEm1B0fZkbp64pJ7harOzpWwq4lcE9KPuAi3hbV5cftwciCG5Da5awc2Kq1IcUhD3xU5NrJmd4S0Wu0GGF8k9Vb0Ry+cUUpYtd0q/slJyON3fmuX7d+YBIdNo3FGKdH/hyFdijkBu0V5hCeLzCmwwyVtCFfufLv5ZIGPr+qIleIHIJr0sOA/+zrYilkLM6QFtOBJsVm1Rucei8wdOeLEQ0BPLatYNn4L5MmmpLIqwVFqBHOHFSAMHenZxoEGA3qewQZr+5CdWFJyoDcIQbk55JM6Rw0AloyREfUGFTTzIpeEDffq3vpJK0jM5Xwnzwd7sGcV48MTJzmSzCevhs7LXMUyQx/34pqZvdwiJjwDiVMJkxOUzRg5d6BECqzPv/J0eAgRDhaKBeW9nYACyz000jktImaOuV/nvACWmcfjpHTJeF6Wa2MgdAekTnsQ/8wSrmn7wk0dbOlbdQL2RWYTGDxDLKwxXHGbkN6NI3AFLXR1mKq/o0p99ig7d/YiBnkrhscJGWX9EyJqQ5H9NYbbDCYp1fIFbQNdsAQL5cgj68qm+PyjpRb1D9AFnJXF3aYH5OFs94Lz4eFqGxCB8HzEXwXr9LKLBp/eASftNeX6fDYnnEGUXR4gcPgfemuV20jSaY67sxflCX2RxcpDctRe34gHUwlGYjX9vOt3dfUWvH051XYzhKpyUDruFuxRfPAtWD8DNi+47QAUHVw45hNkGd0/t5Bb9F4L36qAAJ9wyORLs25KAk4PuqcFf8EVhSL1Be24Vx+uhcCMYp5h41orhgA6+DnTfnPBHW9umP01DnkKOHNaxIdk9In2yZlne2fSVcVQa04XVYEUsupEPzWxDyng/fSNQyp5SQkcTmHmU6abx8XPcED911IFOagZtqB8/Vg/263NgSs+jbxYT8ULt5cFMN6MD5s0OycK81FKxqx4+lwzPMT76Q2cOBiVWlgkSP3wPIuMhOifrcXqXRcnHYSKRVowh8rCHsvR5SY4sMqoR/0lnq/c5vOpN4cgglX0P3nkcOzF6Siwti3
*/