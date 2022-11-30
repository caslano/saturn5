// (C) Copyright 2007-2009 Andrew Sutton
//
// Use, modification and distribution are subject to the
// Boost Software License, Version 1.0 (See accompanying file
// LICENSE_1_0.txt or http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GRAPH_NUMERIC_VALUES_HPP
#define BOOST_GRAPH_NUMERIC_VALUES_HPP

#include <limits>

namespace boost
{

#define BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(type)          \
    template <> struct numeric_values< type >               \
    {                                                       \
        typedef type value_type;                            \
        static type zero() { return 0.0; }                  \
        static type infinity()                              \
        {                                                   \
            return std::numeric_limits< type >::infinity(); \
        }                                                   \
    };

/**
 * This generic type reports various numeric values for some type. In the
 * general case, numeric values simply treat their maximum value as infinity
 * and the default-constructed value as 0.
 *
 * Specializations of this template can redefine the notions of zero and
 * infinity for various types. For example, the class is specialized for
 * floating point types to use the built in notion of infinity.
 */
template < typename T > struct numeric_values
{
    typedef T value_type;

    static T zero() { return T(); }

    static T infinity() { return (std::numeric_limits< T >::max)(); }
};

// Specializations for floating point types refer to 0.0 and their infinity
// value defined by numeric_limits.
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(float)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(double)
BOOST_GRAPH_SPECIALIZE_NUMERIC_FLOAT(long double)

#undef BOOST_GRAPH_SPECIALIZE_NUMERIC_VALUE
}

#endif

/* numeric_values.hpp
VaY16NnVx7KnMDxhjxS2TqgG/DSQq9TJGM51wi3o4OPSlx5zjckW30KeBFWantCk8V3JYDQIKMFdzRjc9ULiMajFMLkWXOlydMWiajr9EcGVjgiR9PRI0NNLyzF0SyU634quaz3uJBiq8cgx8aJrgs1bNkNF7LcnqbNF8xp6c9KEomUiZVTcyjfeh5MJ4y49jld8/fO9GBIP2somZ6VTJCvvri8Y+HQEj8T5DJOQgfQzkP5scaleHO8tmwTfNEvXLHTiEzImJOybTUPXlk2gpUKRf1K1h4QHmkQIgdJVqPLv7ehaEoilHKhvPJLqK0WI0XG/30TDAXVKZ0cI5DFjHjz76nHvgJSNmLJRdL0CSTGY1EiXe0apv3jaX7D6g6UOfaQT3+fzUTrRF1ajQN8B0LWUE2mXd3b3TFWLjaZBuc3ALHId4aMUzyU992hvCudUSOFEv8nEUxV6q9xKM1krLfvCn2ukASTTTER6fHEc5OWL48W3UD6Sv38uk85JzUZZe29hh5iTjSMzR/5VSZYkSL/iSUoh1o9++LYNpG+Sdqf5izuYRW1nI1rUnmEWtWjZ6PftAdmidtPhYBa1Pmd6NPoVzlQsakiBNB5Ai9qUT1QWtfsbqUXt0h3+Rj+LAnEAhbiRQTwlG/1SGMSnDgWDOKpniIduVyAiBTKGQtzYqIJY9TGFOLcTorFyH05gz8yStktO0yCjobz1tHMBBsec7IgjC2ex0J8DaRhOGv9z9KBexWTqics0CufbZqTn3g8zFR42JmP+IgXKHCElLIAEKVDmw79cFrORg0j4X6SYpm6j5zuDcyEAOCzH09Ka4jCRixnaMKP7Mczo9zVq+8rbegx1ZlKIvbedEaMJrfsYsfziDpnYszSLyXKJK/1KjmmKxNb7EdMPBWJuLbF0LPPFfYzYHQoxmrBOIda7kBEby4g5Vwpus+WSa7YjmozIkK1NLcEDm5ZjYNONM1WBTWOQxtUK8YPbJOLxUkIkJOQA6T27GOnXaAaTLwwIZ2aSxNMwAA/Omz5PqD/01YFfyrKMzvsAD1b9yZnaqlMb3MhqTdVxAJHtexn1O7ex6Kc04fG9EnVnuyhTT5SoX7Aa45w5QGeCw0DGzFQHVkUvKTmwKvqBkNuVwltfZoXThBvlwv9+nBV+5OXOGLh6DLPLalJ3u7Ym1AuqUlsT9OggX3zCiK1TiNGEDz+RiH2tEHvgZSVELCMz348M9W6arSWDXhmkSCEzSiFDE/JkMrFfMDKhEpnduNMJtLjSDpk5sx0TyJnbZI4hwDEmiWNi1RzTj5+M25BPfOq/30u33siZRobjzy8xnqUJRxoZzyadYkiKX1Iq7EYAOQDgITWAQRKAODWAwfzk2tTRISTqU/89WrqzRpYoCIYoCGjCnQqCeQqCC1s75YHJ6UAQMxwxpPlW3BOth/kFQAxFEB87IxEBubiDRVOmFHGjjFz6mFHctpVRpAlffcworlMolm5l43QRUpvmMJNHbmWdHA0kaD+fwqNuIPIMJDatQxZ22IpPKKQmKaRoQpFC6ujnjNSQrXLznu6UdNytfpIOBaput3YEovS8WqF08EVGiSZEKpSGvcko/YNmMZHCW/0l/M704BLekx5Aws9HQHlHZQkfhxT//BGDkqZAoQmPfsSgjP+ZSfj4FwNK+MHp2nqPRaGLp2VU9R6PDXmdQuyzFxgxmjBQIRa3gkm+ihcCSvi/pmmJzUdif35fQywOy6xuYMSWKMRowvYGRuyjpYzYbS8EkPBT0nqW8FtRwr+TqpLwJqQxQyHesoVJeJqQ0CCJDM/bjPS+LRoJH/ldUAn/j1S/yQ13Kqa+q6k66h+ktp5RX76FCSya8Pd6ifrEVsZds7d0lfBpqWoJj16WsoRH7yrygFL4QKVwmmCTC8/5jBV+fnMQCf+N1Y9jsCZHtDVBPynSXseIbd/MiNGEr+skYl6F2GObu0j41X5kqHfkw1oy6OtEnlbITFPI0IRVMpkGhUycRGY3ulh0kfCR1iuT8K8e8Hc0oXvuJFLB8fYmxrM04Xwt49kpJxmSP27qKuHXz7hCCT/2gL9zCN1SJ0ItQ3CzgoAmLFcQzFcQmDcFlPARM4JJ+C2vaSQ87pCTIQrFD59nFGmCTqH4pELxhee7SPhnU7pI+BZFwt8yTZbw6C9GXv2QkbpLIUUTnv6QkfIcZaRufr6rhB+XomWo8yhQh7+tYSiMB0xmKJRanmOUaEKCQunFbYzSJ89JEn5Diups+PMLQcIfns4uwlDtJvOrTXghntWUYDXy7vYDbbL3r9PqnWfIQdPIeXREyDZ7flG23IVUk/Q0CJ6OZOKCTz8NV3tzyNO30GMkllRTod5SV7SLlvA6llBLQgER21x3zKz8Cjcy35iOhrE4vA/bHQ/4Y/DyHTSOjZZu8jnMZ+zA7f/c7eTyV9KBdnY9T0WmcgU6LqBdBg8X2vwpPWBoyMZbo0ny9R0iMAfa9JrqrI10m81VX2ut1ImuU+zKm6tOiBpbqz05evkg9QuuQue9vbel3n1j4gXHuFS6+hwSD5wwUp1rnX4pXs7L7ayySUbBC6M6xFSL69Tyo9T+5ULbmKsSbyNKPJbptb5iy+Zz3yQtH0t84XrFaUzOfROv495xPNrXC+pyvClTKunRGHozMLueW96i4lP0JH0RpNSQPdOgYePlho2rbMXp/K5pUsPiPd3xQu5o1rZys9rIq19qm7NgjnLbEW3OXp6oUB9HTafSvvfnJmpqoJcdMQxpevKBnV5FMFmN4Z7KMchwR6bi9ZmC1XDcGsdbNwvW6KYDvPWZxGPCxfLcjSdOHj+KV2CG11o3KndqQkfLV6M+En68yTfyaMNa93a8Y3PF2aMNHuv2Pp9PxIs2pTwhTigC7z6qku4+es/OW1+h1zkVjB6JkezqHaPxviTpzktqUeCtWy01q6/xphls3M4ZE+szbWTAOHajOO25V8g6TsSe27rqKGZDq2nLWCWL6NqOeeyQx3MaWvQVoZFfuNVGLh0X6SW/+6CdRdczqpNDm8m5ZlHMlMr+40KM3LqZcFNVt6tPqLwbm2vbFPlS+zjhIu/+wFNnyOGt+6HVkJl5az15YCy1UKP7CnA0Otnk4C7yuFpro47MlBLtyeGuCHgR4qkNxdg7lqYiM7AvoLdUr+mTxlXoV8O7wjOSPeXp4xITlImuvnLo5/VRcs0OY82qbGQErVmjkPEBrVq9qmr7SXQzM3IeJu8swLrtJ4lQD3Y/qMoGXj/519vAHz3CbOBJn3VjA7/7CLOBP3Q0sA1cv6fTBj4yIaAN/IW/X6kNfPyx/7QNfO9n/wEb+LDfdG8D3/2Kygb+6LpOG/iX9/0KG3j7Jyob+KR1Whv4n+77320DH1D/P2gDv6khqA3ccHtAG/jZ27qzgWfX/dtt4E/VX4EN/O7b/p/bwJtu/ads4PG1/xYb+JK6X28D/8uHWht4bj6zgWfmMxv4A2ZmA5+Sr9jA30rutIGrwlj7X4FMtvxe65LItMRXk/4pLXHvkV+hJd77Aa2cVktcf4RqiZ8nqbREWZHwJv1vUCTwsiyNIjEtwl+R2Bbvr0gMi/BTJF7/7+CKxKttiiKRkSspErU3d1Uk8m7uQZGIi+9GkQiL/ycUiZn/3UWRSAn3UySaDnejSBxq7VQklt0jKRLf36RSJDqdH9fc9C85P163lzk/njoQwPmR26tyfow94O/8+O7b/zucH9M/Yc6Pu7687Of82Fr5a50fz4wI6Pz48NZ/r/PjysF+zo+HrAGcH63WYM6PCdZunR+NVo0L2wth/6rz47szAjg/Xh4oOT8unaFyjOlj/f/H+fHGKK3z48ioAM6PkVEa58cDKcGcHytSunV+fCZF0+bXhdLmuDNF1TY/pnTr/LgvpRvnx+SUX+P82DclmPPj2endOj8enK6pRUGIyvmxfLqqLiNT/iPOj626AM6PO6cHd348t7lb58fDm6/I+fHYtH/G+fH17CtxflyfrXV+nDZN7fyYuFnl/HjBHcT58fbIbp0fx0ZekfPjz1N/jfPj4awrcX58NUtxfiyY6u/8uMGocn4c4u7i/Lgsq6vz48hN/s6Pt2cFc36cYPR3fozN6tH5cUZVQOfH2VO1vov1U36l86PJr4DHpvTg/Fhz5692fkyc0sX58afJqlG5fsqvdH48k6lxfjw0OYjz43o1laun/KecHxsna50fUyZrnR97Te7Z+XFxZnfOj1G/6eL8eNtHGufHHeeYgraR7J/T6fz4wRzF+fG34zqdH5mB9+DYKzbwDrmgtUgeuaUnA+/cIVdg4J3R8E8YeJOiejTwDoy6EgMvt7NnA++W8GAG3kWzqYH3y4SuBt6VCT0YeD86r23Oxyb1YOC99EtHIAPv1zZq4M1VYZCiORYaSMEYnU4sNJH59H8zmUv/jya2MTQcXV538ZSSntfGU1JFnOrN7ZIiTk3DeFM/Kcfc1k0z1sg/Itl1ozEqGr6BGPJnpxTy5+1kGvJHtJppxJ9vAkb86Rq56dHkHiI3GdFlq2oMi9y0ZNMVR25ae003kZsWXNNN5Ka0a7qJ3HTtNSxy0zpdOY3VtE4nkylPjfwnAjSVv9FNgKYH3+gaoClltBKgKWm0FKBp4BglQBMsqEQaoGnOVSxAE4tZM210wDA+A0ZfaRgf3Ta/mDXpQU6oH9smhfFxj/aPm/P+NQHj5jx+zZXGzVn1sh+GewADyXquu7g5M7dJB+Z/vMYfznWB4eiuGM4PL/nBWYxwajd2B+f9lyU4+df4+yZuupr5Jha9iL6Jm5lv4lTZfXLbdtk3sfWvwXwTozp69E28eZTim4gUiHc7+ibqtqp8E9FfBOTQe1f7Q2y/ikE8/AJC3Mog6mSIegbxzqAQz/R8fn/DSAUiUiDfb0OIuS+qIK59gUIc0gXiPAXiDRTidgaxRfbwvHebDPG1vwSDeKxniGdHKBCRAkmjEN95QQXxiy0UYuFV/hB3xjOIf8AsE19hEI1yK+56WYYYFRRiQmqPJ89ndUJECmTrywhxsBqiRYJ4KL5rZIxVyMqrL0pXinVGxug3IkhkjC9HBYzy8caoK4zyseWFYFE+EAk6X/guUue2kYGjfCx8URpXEfH+gV7SRgWM2TFk1JXG7Ah/obuYHbSh7qDYDgeRiA0vSNgeHBU0dFd0oNBd3pGMURZuQkbZwRhltMwoT2+VGeWbl4Mxyj09S4SrYhVGQQrkka3IKD9uUjFK/02UUf460p+Xvx/BIO55HiG+ySDGyxB/elGGOD0oxMyeIT46XIGIFEjTiwjxdjXEh5+nECO6QExTIMZSiJUM4klZItzBIG56KRjEvEd7HG4nhikQkQKZSCFuf14FsfE5CnHBCG2gB03gg1ydKvBBTFhH4MAHctADqoanmsrDyemzHd2HPdgVKOzBbHGZiWVICOshjkGfsMDBCe6K6+mA/6uxQQ74n90V/ID/E8/7HfCfgAOt94YeD/jfvcn/gP/ffrlMD/jr4/x5IyGW8UbYRuSN9xhvnJZ5I3GLzBueF4Pxxvme2bdmaOctrMgbQ7Ygb6zfqOKNHX+mvJEeq0A0VD6KEMuHo2DNzATRSnjpmrogfoZpw7VeTrTBmv5L4+WE9SJ5m5mXU5+VzG2OJlg3S25zxzuYj1NzcVc/Q+T0Tj9DVANlP0NUVEiIUvjfi1nhNIFskgo3Kk6M64uD+Bm6h2lrQtW8h57S1ARVDrJhEyM2VSFGEx6RiU1XiMUWd/EzHORHhqpvEVoyqDaQcQqZo0WMDE0wy2RWK2QqiyQ/Q5wWuvgZvhQjD4TTnZ6pGj9Dg+RnqDvnP9VRkU9eep7hmF3E3NNowvrnmXta1UWG5Lqirn6G8WoAkQH8DKNkP8PVP/lPaFSik1EKgn2FDAFN6KMg+FJB8EphQD/DTTAa5vFW9DLsT6//dnKUfj3ZvUrjZ4gCmrz2HKOYq1CkCc88xyj2/4VR/G1hFz/DG4Z28TNsUvwM/zta9jNE1YukKqR+cjFSNGGcQirpAiO1zyV5//1xqMr7710csUd+w1ShTiGdZyofLm/q5razLd0Z3pWGTOr4d1He0jVptnRNbEsX7zYIq4dJYfYcEv+4ake3pmg3LeCNi3RHt8/Qzh3dgmdwG29PAQCq/E2wbbz58jaevIG3StnAk3bolrzONvCMnbFJcAOvgCbPel21gZfWKv5fSNUAU5YxAIBDS6R9C1xU1fb/8HSU0RkTCq/4uAlKVy0LNQhNTaesK0mhoimapROXa2XKKNdUsAFlPHLzlqWVJaaWpZX35gNuPgZRQEVFRMVHiop5jmDiI8EC5r+/++xzZrPB+n3+108xZ87+ftdae++1H+esNecAkegJ4P36KQvgmSc3C9/hzhESXTzxuwLrKoMnfpfcJH6XTuN3/pJqYFa6FrybzYJ3ySx415UG74z+LB0km0XvhiN610+L3vVCOC5rHr2LO4PWY9G/tQjetr00gjfDE8HrTyqhXPH3RPAc6xEsMCD6FuKk9x9ZiK44E3dTl+HeeIA53c8To1tSnn7GnH7bq4UI3XmcRLYRuwk0X6bRuTO/NTSJzkW45esPqSGIs3yUZSQ5mbbAr++8ifqpKPVUVOqz+qke5NSSp/0yaVTWvXW6HuvYSdbFZmG5p8Sw3KPNwnLRuuiD4Y3uyEl+npBcEhGJkJwznLtdG6Hanj78fwjJxakhuZH/a0hu9c0GUvs0pdK3aRRuMTlfNdXzmIaerGVf0E+d78la1hOsKu7JWjaFtmyK3rKv3m1AxR09uVboE07vCq5qIfi2pFw2h6v9u4n0L9xlHRd6m9aTtrI5Ay8cqnpZoiG1aOp781N1YwZrJsfrp3prJg/XT3XUTJ5ITZ6om7y5jvgclUxQB3pwhif3pIZnSlSjGtC7R5TtcxrP9sDMWcvoUOq1E9+S+qo3ta1E1Sj7DSWZj7G168nF2JoEWf6V0TzC9owGoREo+Y0MPspmuVeULaQHrXxBxmcQFkljbDgk07UWZQtiUbY4PQz1ek2DGGRjoMY4PewzgoDSdlJZyY/B/8PEUNTBdC7O9sgrbnecGodSJnp7KkyDivK5G25WG1/sCaLGWTz1pXFFeYeOMLL6thhv6x12j/pqUTdWkdo4PaSYer1BDLox0G9xekTxpeue2j5B9HwS6qktjSvKnW643XrgbegUNZmGBhbprNqRCKiK1yg0yCh/7aBxtzg9snf75wY3fkY0lwu7qSG6nTVuIURXRLAIuz3Phd2eahp2O7SOC7v11f3uw1Aa8emqDba67jQoZiHtpgXNnvCyD3bQSLGP/SkadBuo0+MFem5LdE/IbcHNplOuVFf1CP/dx1oZXZfcR+/BpO60B59oZe8oHX5Gfqw7Ny7Pdqfj0tWc31Kg7YtrpMkf0wW3J2TzNmLkKMsd36EjaIyt7EFO+gJV+mE1+s6mYrKUm9PtXJhtOg2zJfMJuVJ5k28xRcN8iqJPJffRJYdSyfYQrckWPajW0YdG2EaRb1U7BRFUgh5gi7pBqvKAFmBrl9RHC6S9V0FcaCs2Nc4FgVnWVRHk00L2RwX+BnnHJLeaCrNK/gRPMlYDQsvwqOQC+Wp77mEieFdrzqC/If+pvbpxiglWc6mXWEOcWUj3zKRZ
*/