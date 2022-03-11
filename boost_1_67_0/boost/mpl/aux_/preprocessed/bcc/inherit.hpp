
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "inherit.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename BOOST_MPL_AUX_NA_PARAM(T1)
    , typename BOOST_MPL_AUX_NA_PARAM(T2)
    >
struct inherit2
    : T1, T2
{
    typedef inherit2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, inherit2, (T1, T2))
};

template< typename T1 >
struct inherit2< T1,empty_base >
{
    typedef T1 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (T1, empty_base))
};

template< typename T2 >
struct inherit2< empty_base,T2 >
{
    typedef T2 type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, T2))
};

template<>
struct inherit2< empty_base,empty_base >
{
    typedef empty_base type;
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(2, inherit2, (empty_base, empty_base))
};

BOOST_MPL_AUX_NA_SPEC(2, inherit2)

template<
      typename T1 = na, typename T2 = na, typename T3 = na
    >
struct inherit3
    : inherit2<
          typename inherit2<
              T1, T2
            >::type
        , T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , inherit3
        , ( T1, T2, T3)
        )
};

BOOST_MPL_AUX_NA_SPEC(3, inherit3)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    >
struct inherit4
    : inherit2<
          typename inherit3<
              T1, T2, T3
            >::type
        , T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , inherit4
        , ( T1, T2, T3, T4)
        )
};

BOOST_MPL_AUX_NA_SPEC(4, inherit4)

template<
      typename T1 = na, typename T2 = na, typename T3 = na, typename T4 = na
    , typename T5 = na
    >
struct inherit5
    : inherit2<
          typename inherit4<
              T1, T2, T3, T4
            >::type
        , T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , inherit5
        , ( T1, T2, T3, T4, T5)
        )
};

BOOST_MPL_AUX_NA_SPEC(5, inherit5)

/// primary template

template<
      typename T1 = empty_base, typename T2 = empty_base
    , typename T3 = empty_base, typename T4 = empty_base
    , typename T5 = empty_base
    >
struct inherit
    : inherit5< T1,T2,T3,T4,T5 >
{
};

template<>
struct inherit< na,na,na,na,na >
{
    template<

          typename T1, typename T2, typename T3, typename T4, typename T5

        >
    struct apply
        : inherit< T1,T2,T3,T4,T5 >
    {
    };
};

BOOST_MPL_AUX_NA_SPEC_LAMBDA(5, inherit)
BOOST_MPL_AUX_NA_SPEC_ARITY(5, inherit)
BOOST_MPL_AUX_NA_SPEC_TEMPLATE_ARITY(5, 5, inherit)
}}


/* inherit.hpp
eDLi1d+IBgM89NRQPgdCMXNxvKWGp20I/nuHf4mLeBD0/xJpzTD4y2ZT4MWO/sT/A4lP0cTLR2xnHUDB5uDuA4UeY8Sj17aK9ihpbLbUhJy5nM6EEuU34trJe6EJKHF8c38YkJ6r4fUUaCH5wv4cuCxQe6qUSNFjt/FveeqWvzDeAbdnucfv9A3p8XVfMP7+9nz0WSstprErcOFO/4LshAuaj7L2Or2IbpIvqWAUatDFxIzLXIjNQfGy92lDeDsCmqY1HZ7xndj9ZFXNGhbwVcW5n5SNZzMxg2DN4vVF7ja32Jo+80G4gfbJrI63jba0UZtpK05zlEYd4Bj7dKCpqlQ3umfavwFEAI0kgBKMScZsAyNTmpyiiGxTLwKkQN6NhrRf0i3TegK3r363pa9+lx0lDvAVcwWTLULk/bpoR/pcTBiVRdwjNKGgEL4YAyEApfT2PSUxKFqjoBwy090QCjqkakwIsiXaxoFHI93FNmO9nVYU7PmxPciyn3QcDjdUUS/+SBNKLsMPTD3C9YKYZIhlnOgIV1dIApFhh3k97HdunSLZTeD+AeUZW3lhDH9bnUQ8PRmmua3pK09qj3cbHKzPLq1a0zW3XB5dqYxbi4ZrqQFgIqe4H0dCYtlsdOHsqnXxtEtLjBbrsfVp1dXnL7UGMLBVNdopbQFB2c81jKGS4WZoEqWBt7tLzo0DLWeoP4zHYsJxQDt612rbJlg5GXuCbfNxL9VbFhztuTiZeAJ18I7T0q1XI7SenfMfPgH7UCuyPz14DfAR1J71LrYeqUU6hgdwbzUFRUXoOZROFQlCQX2izSXgi0pAB9bQnC/Cui37ojiF5Q/ccEGiZmA/pIzye60A5jWhj+o1+Af+EXK96JvXZP1Hwru28YqwtVFUrQRp8ZjDPcDMeWDUPl2vmSLzlqqycm165ZXekhZ2Gcfn9RRS7TvChloPDDBSPPBqKpZUD/Rgd3j5tUlP+C1frc88j7oetw6hpMnJlU5gbJt0kzSfJrj7sfxTKqBEN/KuAV1Zh/uW8bPgriF0pkbMxIR0mKFBvLwT4jOq5wenK/YTWldmaDJGOzpt6LkDn/57DOSNUj6cA087xtpV1KdpNwtKwaFpNbPofGR2jaoYV1Ihtuyzn8XPfa5CkZG+BQ/7YanBoAHJfPg21ruPF3KZZwDg+ySAeCglA2pNrS73sgxcgc7PqtKikHmdC9w2ERbkB08NDiToy8uwTBU5AUviomDOLK+5oEKkEA6T3vBoFrwVfzx6XnhBUXtTRASSmXsaVrNDnddl2xZNbysE0AwZr9YFvP555YwiUXiWEUqdngDz+oqCo9J6yfEn1ODRmN6p3gakiBMsggdsvOj9dQuXRSHs9pHZBWZL1grqoV5d0AG5rqoDvhsOPh6OHaO5Iqw7665AlN2uZsDP7lCnbzg2hETeBLthEYKz8zXdxU1oY0+akAppZ29sVJWVQ2xelK5oFP7vFYzoXQ9kSSSL54XK6uUtmxFMvU7lvCXbeIAaoZtEqV9/vR0eZdjogi8toLu7A7LNjy3BMsXAmNqCGcDIevdN9EB6gBqw2D4VbHCSN5lhQTprk0z2xcL7VvayP+XlioDbe3TqZ2paWvgHzE/px5PArWGfR58dzo/kZgvuO+yIRwDJdP3p6ot9D0l3psUOTmt/99HH0o7PkteGMkEwVTzNIIsVDIcD6qg0wbvDTHxGVGEGc77N8teJmdKcr9Q7S89WWLt6HGVQwRjk3gjo9URWfF4HyFkQRRBKepGdI9gHlod/EagUN4JaLf6rad+AavwIyhPboQA/+8efkxOTqBDHvLZH60UEsKCP1ny4wHbWaI+bP2diOat4ozAmbX1krGFiH5gOh2CRm/9IWQ/HYRoOQ9bsk7GTYZm7h8aj7hUOZjNaiZMxihiLSwJA0smc/f96/ElOu+NZJP/mt/vdCHFC7//6AcsmR7TWZNBZzTc/bZ70/Y0ow33DxqW/cjJ+jHtt57JxDpe87X5B+JP3MmszPbK1Scyaxw1MrAf35yIXefE4zMt7TZwWt0/99Atxsv+gRJx6JjlimcFQih3Xigt2gf0xPGLjr9VNv+VfGdRT/W99ywK7c6iGmaLIdQuxdNhTqn/OuJoUvdNVdv2Tq9HjF5p6orTI6inMaKMUveT+pmEAHfBDi7Y8lQbjKEPWm0zz6wufMFiyQOWXIjIf82zlMVxcsMqEYeUguvpSmJIB5wqA3kErOlmAHfToC4bnubOI2ZmW2uPgbt9aLJJPAdpQJZvqk4yaLjPJNG62IOFDVYUwCV80f/+GIoIYHxX0CBUsZa2I4KL0LvTEzoXqfu6jmtf23MGVwPm7Y+auGPXbcYXTDc74Gm7TYirrygijxehk5Tm+3+LudHrwWOyeVMnDOHbb7g2lvNj4HCRl2PFqUIFEwT95IKy9l9hHZPQub5B24wa/V3EPLutjOyiG0VVAktqjRJfk6GAfnEHeOmHWzvvdueL1Wkx2gkvbLjqal/q9xzQ4g66+f/Sah8hNmyyJnNWflakaWn3lrEEcSgw2AQn8Ra2Dawc20cUxPeTeLMPq+vabw4FC8zyqR/uIcYU1jnx7U9WeIa20mR71XVllf2Ref28IizOcVVlo1lp/810o4xDYzdZw49BLrx0bErjQL+u5O8hr2IxBQ9luuruZpv/sYGzucfxB9Fxga9HEGqmPbf7EiTaRO5Xmgzadr+hOmCyUBU7oTql5cdhfBAca/sJiNDcsFpYvER6Azkelc8QIWYFYKPMwTRCmorecNHIIhnLKvkm3FvIFTvJduHk+3OE7b8EqJKBP6h72PR5/Y/Ui4ESaQjnpFFrOKvC3Tjx2il95i6BRusw68RAucZrGJgLP6GUJFiDCKpSFrG95AX4XMrU2RlWC+tfurwU3nk3QgiX4U3K/jdCYvq0JmYMTu3ncq2t9asmz2pxeYr8ZZb3usWsk2PfBdR8Ddzqzjfx4TPHu5cdD3xe8uYl3syWm3TJ7kqx2CUYdI+gKTed+Q/7OJZ2TGOxTE8xDbkkJWpr0Ml18k7jgesP1nimbk3rE3Ii+MHguzlzZ8U3MNjqecQHx6eLREmZxLZX6fncmaNZ9+w3FyKJ18YU6uWMNSquF/4PLCTxJbd6s1KMiAmDwyo43JOKXNhN1f+L7Jpg4Q0iMLtcd4tgc+bNI/nWbgB2xVtXi9US8lYrlA4Ha66kiWJNl+NDQEK+qUhBrm9VNAxdWNH+b3MxQsEbre0WszQULiDcgi1jyMGVypPPMJGOcu6pZ4hrEMrP81ycR+TfYJoKctyXwrLP42wpPqf/AZnF8Y0kNdeu+qw7Lr9ulXMDwAu43nGvdPplOOHDXLb3FA4ke0jsGvhUeGXhw5wLchHg6eWGR1PnYnHsnmTUm0VTI0rUjolsfgIpQChBLByleISiJFhbvCd4DTEh6M2XpPmZf6oZi8WH+WCleeOAET1kVSQ+PP6xSRM6tq+QTi2eFZhli2UTtwveG8cqccrCmZ4FTGx5OZQ2Or+JHqfP30bodokKBQQT5oumYyjB5cu4e7DhxNEx/2G1FAQwbVxTM8TohCnOqA+BNNidrHOuHMVwYD+iXdZjDc1IJYyyouVrOGAZQc3CF+wifP+J8W7yauDWxzTR+CGXRvMat9fB2GTCH7NnfNgXmHWkUFCdj64J0c2W9dADgivyrWBjZBV5ddZD0R9ZopGmZFEWDIS3cpuQvjeVXg/0bAtCvaOLr2m7IbKG2tBTNnpdLzdjbHHi6eawg4f3AMKOjA0K05SJXVnOMPxclftc9+44I4tH3eAz/oqN101SsGruSj38at0uafzZV8MrJZsTStQZcpLhq/9rVo0JD310UaaBzEH+2pJxluKIp79WF/O8rKDQL8JW+HKeSM9NV0qDVoBvsPjzMvac/7FbDFY8b9q+yDfe6FzclvYYkX7J59qUeeP4acSt1M755MmyGhlMjbJxQhgYdixkPvIVipMAObv4NGtmkILzdMZkZYNSchB4CFRqpWe5ovLMDJuj99zgwy+AJlVviSHNVPteVcDLB0Z915xtE+lvY69S/VECb7fOhPH3LPFYA9Bij0dmybhiVE6DItV4uxguFMwEQMwNdYF+pSz4BzLMzLCALeUDC6uIG3ISzOOdrA55gfUu9Kvc6dBz4j0ATW2f7XdCyI6cG7shhGXG0c40p840J6pX72kMnPp3ekb5CStJmzfVXf9J4G5nlWM6NQpXL4BirDU456564MPJj8zED1Oo8/JOLQ/r6cj5PCeT0wXiildhWSYyCbmupBGbUi+Z8xW86oIzkWZUqzKL79VgO87acC0Lj2xnO8XAlskkM78iSYHe2PRZN73Sj3k36FzJKeY6D+kiW0s9lNWUv3Bca+CdbM/XgbXGlmW6qAUlYWXb+RuHGoka21Eczve8u8x2ZBbM8by+7mA28KGM5jNKUn52jDio+8s1sb8QblJC4QoAEzsKqQawRfn6xedAlcjXSda4sX9tGCG0Vm26wk5DYyGEH5EaeSJraLWpmIqt1Ip8bv2P6PUoZp11CIMlkzm0L5UkdxYKqQ9xjd/acIUfQfqZTLEWflJgc07WvWSpZH1gi1bgGlsn/i6nJmuRYhbfRWOLUCcL7xCBny8NZLSeUc4kR9Topu/yC76LFJX70jQXfmkms72q6OfXSNTE2wVJrQ9cJeICJ/ZGpaEs/yXV2H/373eGP4W3ZqB/diJphVW7IWYq9Z02OjXkfoeDBzeLGeqN4vlELIkMR/D3xPiy8LGMLq3HS8BXDt+yIHON3myyYdtcbWrszKR8vnkytrTCqaeOFA2tu3t1jap0IosfH2bmkr0dqqoc5bheh/GKfCHxLCzNbRsUlW2LBmLk4yoUdZN2SJu95d4DbWCt0I6eJFvFNXp4f8LevO+YguWFbYBO7JDY9KdxMDD2W1U1WQIwYyWIfpE0eyq1tBt6sbhc2ArTr8gfp+WxXyshk0maYzb0SIcERSX628+2eIte7gwokI9vaKyg0YGLv7J8NTNNsgtrlayFeluARl6AXrPDojCBcsZbZNMJVU9YIXkex9ZmcPmdI9sX+1am7NStoavA5+yb4pTZOLo1kVZKIlWyhRMVMm85cc1HZkz0RATGgER+s8TjvKpkQjuASAum0RSQPq1JadJ4OVOb4h2QTUfwOgJKe25JCpPHfXiFVs8gEUb4ubzrDv68uk8S9lNDPMCZC/kRw00HNKGyJtlqtgil0EYVuRZpKn4Cr4UND8aj/apEfctbXAfHbIFaZvkDC+9ESA9x6kmR1uJJNy4rgVzsvl+OZHr4ytuwejbEVXtXuO0XIcg/dMc8iR+s1TyPl3V9s58zy0zC6eBl+dBN24GZUE26yMmpIdiJnUQvm2b69f8IIUaYtE+cNPFYFkEL4OOpvEryvYH1XVOIHZPjE18hpaLL0nh0r4/PjWL31ThOubOk8VXrZBjC8oEQt19E7b5pt8OCWYclXE0NoULpCvpb/chI4B+4uQgEF/gnYIUIpFKOEkvcBSst2HbhkX54uNJlU+cDU4CQMqXdUYcMtsYLY2N1Nimbw9JRuuvqSAxTeUSszUnHojL1D7Yc3nDVxfQy7rDZdE4ukADrSPNoXTQwOSO9r4HjrlCYSpHEPkrYMWp/mG1NZk69JbVy3h49ZsNXDiYUw7+VUuHPNF5QbA8yUZjcLY47j+znz/gK5qbhNqQToE1QtCdQv1Sgh6oUjGUjoURNb2kz9LJ2tLJgD9py8bBTeKjdKkqRvn1LU33mNQvtyMJygRtpNkjadPrJxw8B3qt8RjtULm77wRxPr2aADbZU3quoVuETL0Cmp0JtGhi3NxJrl3vat9DzVdmpvIsu4ZZVMco+gIujVI0ITCgD0MadTy7skQWonh0T6CxoBNGRTupDXsAXp2sgqk6d4uxBtO/hECiKLMiJ6p5JUnmwrbD6tltcHGg+NNblqYtDLSYavlYCe5eTRyTfORXNUQoMNFMbEKckx5zYCxn+u9WLsBVFeKSkGbwgGwUh5vceQRW1DhHFdXMKOFhBnXWCzPWgDnbWSAwC4vIrxJA1M4ET+XIzZUI6rUkkTNTzwlzllmIiWO47gdMd3w023RgzrJoRT75lzxeLA+3Z92BLUJcR2EyRS5ipiOKpOYWtVnN2p/10BuprxaHf/nshB4UVPOegtiuyFOP3y1u8LZpChBrNR9H3jg/dr6y9HIrK377leTpU2spwsDVXaO2WWw6DxwliCUctfXdl8m0ofExW6Pp3BVIYB6jDdDGSJdsViOwipibh6VEF7kjGCCbl0fGnpJdB/wi5o5IBZZFC24GInqf+iTTtDyJO+S/eyB70gqpFu44pLr2nY6JOM7j7re+S9uwZSSw/AnoETp9p68Nu0p09qeqG8V7oSd1sjJCAiaLl5EgDZ6V1IVKRT5xxoHdPlBYqWo/kwmm8GTXJbvOan7+pRDY03DI15I5Oso/9vV1FJXflJzCd1wUTAO1Fsj9ux4F7KlrmMnkVBZRzY3HkWPV9M0u0waWpu0H/vB2m2tWiRzBwdKmWWYjnoW24glLkru8+7at7km9OOEf6FCuN5s6qkuNkabdQiDemJ9pIrsWVKuBRRABoyW12gwebKy+pfAGiGt4aO1H2P6Hta9YLL/GwijQsjT0jjSdiM/EOZKxiUal2EFeUms8nbb+9QY0u/asWhWy5SMQ/raiO+mxpWu3se3I9W8+JGUfwnzY2d/1qA4mUUxT0/hENcrau97217/gqWqO0Ogkglu19iFgEla/lUB2o4gcDAExsVdzb8pjKqrL+0gCm7vBex1Fbn6CrUbmXBLRjvySbnrlHNMRUuWf1udfGTb1qifd4czyFdhd3JgajtP66InJoJArw2IOm+Lkl7DzKgVBbADzpMOdm30Lgf2+q1ElfsRLiSOA+IHPG0De1LNKXKljnAkpO/gHXWzpoQ4qUJBd8LBumQGJ2g2gdL/pLLOs+iFC8J3qmoRtI8PF+bQdkrGnfUrEdwUZiKgYjHxISTR36awD63bRPwedpK6Xqn/QZImuukSt+aVrFjnwGnknWPG9bvGCElUNJcXNvuOxJPh8ejG/dGJqAaCT1PzhoNQiGqI3swEGKuXkXZlwCbrbf7pOXsT2R8t/+KZmPoFl6jd2iuxSsxdA7XKIiAzv6BdBZAG4kxLNETfRTzZtzDYMbr7FDac3LYqC6yK5RmzIJdT7E8lab8rrnHM5m7b0Tchoc0nB52pkMSYjFZqsi2ZdnAJOYeLpCRfYThrN2DsM4kqTxRofVwR97qqZv3JcPePzxzk9xGqzWlc5BvjfdDKtbjHUm/HEULnVBAxaDQ/o5p7kuO/N1jk1iB1DiEyM3VoHH+SqOKBhdagheHayINIosVgy2CVF/Y0O1uIRbOJSWryIxwGy1HRNh1f6mkM9Dhd6xPdLT8Rzd6uda4FzQFPHm3uDpjEjG3jV4PszJvfCFRAJaFWBYb3KkqIExhy8jVgB1KFzRgSjXIL5Y2xcmXgWq6QXpn+5GdJPR5q3R4bDVa1RUWNeTk+wkLOiZPq01QUdJEoDFDKev+RVAS459mSLZWbnVNxcEtJGKWG2+ghlvUKru5hSfz+RhCW0l0RLceF9Euy5VTtG0IITPWJKswbpBj1suGPQ+iintsDbR13xVBWOPoj1NhGzcMEkCwIefw+lxga0IgYI6QKqjjibsca1uC5O6jVkplBFM7FhmQ0Q3/TaLdOR4GuV3l2FhQrOlJd2JU0Dn9HU7HgOozKW/g+TZg2UIKecsctznmdhps3iWNapwLhnhFaztTnLKH6Uguck0/oV28XA/Wqn9VxZxLbfSwa9v2GrulIqqLePmJnUCHaYZN1ziJYNnBuCSZMU/yFa+YnjxxeAuleBmtClHh+tZ3SDYVj299FmxjLZpJPbH75QVU90/yNChDn30z1YxyiatILDjkk+AVWLVqoC9cLTpFQ8ACHda9WFgblGZhv4IkCsfqfm8kFZxZm1d8KPcjme30JqjyIxcgMVbHpPgKGF+1ya6jNPqzRtTbp6VURUpJdjLA/SeBZPaLDFttmjqJHVpNQgugo0BS2kI9BpiGkCLQEG+JlCLAo6Wb7DBgyL41nQVaytDeIJLOrS3sZwFS3ydChFNmBVXbG+9eS3pObu+nM9JMXvjB5bF2bFeRDm+Ec8gpvXccaAIezgmrz3E7098A+ljLFuicgcSFJOw+zeJP3L0A8+GoYS6owhWGkfOmyfEdblnKkg8iXiwR523MOmuvNYzmpgeK4hw5Fyi37IKHbSPqJrXzeT1W7IYntYG3jhO5aLzHdEnq2oyZrc/46cV7JOEXwD+xgAzUdgq68aEvCmzzr0WVVaQ/4vVMcrSm9FUB6Tp5idzh0sBODw5tPkbf0FxSaBIhC7upzYxkntTEpYKUQGp3NI2LCnpXw2CFjNFAnxR5nHVvMkAEH/7qtGdmIBRG7z+Uo8fahEaOlW6CnPhGHjAMG3z9UsAkgRLJP4k6kP1vUwkAAiz90ydOykIN9jelso4BEiy+HDB8rgbZ7N+v5CCRc06cwB137/UB2CrZu/wCVUNAlKhVC+hWYM/E4J4I0tKZVu0D6n1kbXRbzTBWfdphHfuV5heiaFvtjOSBKuPaomm1KkSm/RS12Eo4lGGhh8RfQjpauJaWrnUUBeDU3HO3P5lWsQBXftgGuPZsb0avOxkzwK0R250ImnC5zdRmnJBhMEgGQo3NsG1SnT/NOm3zbFyIWQd5ID7r65rgUtZXDMdaSJI2F0KEizqJdWaqTbv4B9ztf8kVCwcwodG4pnymI/QyMWpz3rNk4yiRz4Le8QyIa4IAP8zdcoV34N8DB8xXEDJELy/kk3ci69yjqPI34XbUcBty6kMWV7lKqrKQMk7EhLJt2KRQ5PPzHN2AOaFJywc/Ps29inaHgcxuLTdR+kZXWHkGlmUHSmkf88CJos/7/bwiF7v065lfsZ4Yw2PD5e3yyUEgEgWuMGevr8IuUWB6k0QsrW4mhoaTxq+FNWgYk3i7U+xwkBVNe4vMRjcRovqD/cnKQCl1AujZ4YClcwqoemtWhofFuSZmpw+JSvXZOKJmmtxQ4g2kgAXdJ4tJxMp+AkxtlZBUPkGpBR7kwqGhJlYBoCwFBdNvTH48oczcp/RC8y5Ibzd5uMK5+SH9ty0h55PInM0=
*/