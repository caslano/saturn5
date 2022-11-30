
// Copyright Peter Dimov 2001-2002
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/arg.hpp" header
// -- DO NOT modify by hand!

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_OPEN
template<> struct arg< -1 >
{
    BOOST_STATIC_CONSTANT(int, value  = -1);
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<1>
{
    BOOST_STATIC_CONSTANT(int, value  = 1);
    typedef arg<2> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U1 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<2>
{
    BOOST_STATIC_CONSTANT(int, value  = 2);
    typedef arg<3> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U2 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<3>
{
    BOOST_STATIC_CONSTANT(int, value  = 3);
    typedef arg<4> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U3 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<4>
{
    BOOST_STATIC_CONSTANT(int, value  = 4);
    typedef arg<5> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U4 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

template<> struct arg<5>
{
    BOOST_STATIC_CONSTANT(int, value  = 5);
    typedef arg<6> next;
    BOOST_MPL_AUX_ARG_TYPEDEF(na, tag)
    BOOST_MPL_AUX_ARG_TYPEDEF(na, type)

    template<
          typename U1 = na, typename U2 = na, typename U3 = na
        , typename U4 = na, typename U5 = na
        >
    struct apply
    {
        typedef U5 type;
        BOOST_MPL_AUX_ASSERT_NOT_NA(type);
    };
};

BOOST_MPL_AUX_NONTYPE_ARITY_SPEC(1,int, arg)

BOOST_MPL_AUX_ADL_BARRIER_NAMESPACE_CLOSE

/* arg.hpp
B6LnGihc7XT4pT3OpxBLGykthOknp3Qr5aivYZXSrMQq56p1vicRAHc1wp6p182sjvq5c+divvDVcs2TmHmiQMlbBfUgSC5BnFfojPq8BZ7yqfWsM9STzRI51OLVtDpWszrWkdXOteqzOcDZwkBNDTxUouQJnGCnejMXCC/EvH55G3t0zjkxE2ODCQz3BuPFis20+nZocuPEtsc0QkSo3BGoqZ9deKVQ4/PD3e3i9scE3pYPCdrOCLodwWrVMrM48Zzo8d/pRC9DHGP1mdn9smt9OJzTD9WPzO7P7gJ567/V6ejf40ToF2i1pP/dAPx6hifvWAJfn4Wv8LGffxzgH238o4N/xPlHF//o5h89/KOXf/Txj0H+McQ/cAWw/xX40s5/I0Rr/ypnfv9ep6zdGuW3xvjHh/wD0VbhoQn+ITDRGz7KhmCJ2tU50P2SGhRW7IsPoQOA8/VJzi9hPFb5ZTmmX78dhQ6zKvtrGYAwUx3ReB9UagBUqPnE3Tl92SKwEIGCGRvfBdp2cRJbeF+QtZj7boBBR+sFqtcB3fiKfaDCV1zto6Fbi0NroYoiqKpqoGItwiEj4nRs1A4PtvAKEDa6CH6q9RWpVfTzLkJpK/wTYWwtYB0YVmmyt8uA6rUolfSurajXW33wY7nUwirzBxoUfAe93PA8U6lM3AkDd9Co1GbgzCqVM8mOwiAAUfk1NX7Sxsgc4NQ2ZDWf1h6CeTs8UwBU3Q4cq8LngZMwOvDNDr1r03rXxMUPO9nEBfJW6CvoJVpDMFMTv0uaKU3igaYS6JoM0qEpCoPyvrYQCPcrb2gai1pfjyoIOntMfzYH8Z+h5r09+iUL1LiWriiHh3xQZi3aEeVNzUIhHjTqa1XKZRNUE4ZqlkChXbqdXu5T3kjwB9TUsbfCoJWherdwz2Dwfy3Me5T2yFWPXidkSPjB16epvxz3djAEcH8VvXE18Ymkypo53uD+avMKA976siTe+pJUvPUqHeETnBPmlwUBKWSHABqyGrIwNxBw+QkMWC/ZfrhVYHeV11mW1t0n0e0DU+xtWY8JKpI38s7uMD+GNtin4jgERKhniY+dLODZ3H0WBpxeJTacx3Tu1GdtOM/agsvLeHtaSzyFObbVrKjOpRJh0B0NloCPw46uOsxy9uQjGfBZgB06As2jX8lHWvCHOXbEF+L1FfD6WLqXHZaGLH9tLa8EnzP9GkuQsDOf/cIU6/LXSj9QEJAYLsANO35irnV5DVxHyUgFDl8Co3nPw9PGg44VhmBimXH+OZqK9+yxlp5wezBw8NppdKPtPw6XDri9+aR5EDGK/6OTSEMYwq+9QCGhZdKtixTb8+fI+uV0/Qbb82+Zz5r7XBVFkUWu6pLIha71SyLzXdGyCIZN7oqwrWmDGadPieZRqIINYfMYQ5We4JfYKKrbN2EQrRK7yoexwolYVD5+SV669rzCAZuTJXGnlsTuXvVPwCVGMGXUIsIhizbJ+ipSUUSqS8h6FseGwhB4QpQCIYv7UDSHVJdDMEoxhFnNf68iFathrtH8IZt/qnEK+2UIU3CLlh6u0HEesEgSds0vBVsCZ/pqiacl4dmLAUuCdZmv0GJ0QveNJSdJ+zo4+DTOxiX2IAQRhgIYeFGJFxhic6JBdbJCQxtpxQZaXQ+hpxTdWr8BgniQsTa2xuuoH3z8u+oUsjYgP1CtLeFn979L2dX+1uOImi30t/aon3yi1sXu4V9ff+swspKxtb9VVh8bZWsBeKefdcRfEzuq1GDyQesxhjGdwyntb8YG5O+BlPY3Yxt0XH4ERTa0DIJ2Nh+IblbFoRnBwd3Ho9e4KpZHHbRiCa0uI5xN+/DWyJfg5gVws3EO3OR3Rq5wH29cgAXmwdMUBpk/aoPLc/DRHLhGq0voa8VvSlEf7StefzvJJWssVMLnyG0I6k1bWRcCwLhncJ03l64R2TKljVSKaATWWJlYrLGQSmtSipMjhPPjg0wWXx7lA5OLJs7K5ZKfdLrL2Xw6bA2pgvwN/3m25qEXyFZl+KvXfKDw9wi9xmUYMx8A4C+6HW2OI3XwiTy6hfTJ4ihMFuskbhwcGl6pM0TfQ7xJyg/TsOTc2fRGC/x6hQZL+j0FARosAnPnwTmNVXWs/Z585lM9DhakeOzMr5ZbmU8tF5k/LbcwX4rzCj+d5+e+FLPhwoRyfd3hIp7wuyjl/bGfv5BlLwmAkMuAEMkzgYEHCz+D7M3BhfSIuk5PcvSvun1rP/jw9PvD38PlzBz0y6wZGrRjBh08kQlzBc8YdBLC4xwMjtXAODhGKkQSskz5vsJqfF9RcNiw/r5qKjB98KsfgS1oI96OhOcAA/iWjn2kSJE47ZMfvVifaRpWiVg2rHI7LRdplZ3Op1nKcWmzgks59KgUjFfIqxexxISL9fex3QlPfAzUHzg5C7NmWRpMyvHS+Kl2lis94qCVhWRLAWaABCnKB1NFthRK3rhfzroE57gO4mmPnd14h5l4e6i3I3bWHFmBQS80FpAfugx70Y7Xx822pnsFnjxuW2zcEv5qbDw3vIF62vy+GqiPvil/3yoII9+MnTVFbCyn69EGwS954r6RX8bOZkVejjXahfACxD5jzZca6raEv4e1fYcG2wLQMH1V9iyAu+MjVfgo9bbVQPUX4BZWOzziD6gNlmfjQ9SD1OFuI6Aam1uEq7qzMFcgFB6ZGxvPisxlzWKXOi4VMLXzPcCau+i1+Iq8IR+zPFmAD/jCkOXS7pb/dkGOmigA3+Y1D4RvrJVf+/w5pX4c01RvE9UiB3CNQi1yuChboGOIAcOKnA5fhLsMWK5JMAQ19Ii8uSIbN29HDmQePJa8zTQVMv4uwpXaLmTw928dMshj2TTyWGclnh4wAe8Tbx/xDBJPtzHJwycI4lbcJXF0kSLnQghUaWv6FW4jlX919CPwzD0ZylYBh3qhawX1jmZ8NaimdZ9Lvb2g88Q72PxKZCMvpyV33myJzFLT0YYXN1xR/zpmb53I3Sc0iPXLxH1CPc7f68fggnz4K+ztUuzXbSy7niPxbfyCBRLfbodvV7DF21Pn1GxyS1AvqHcQvy9n32920JWFtKaAeIfozfnQ/WJ8NUWCwInjmNDhWbYINIho7kVScAhMZE9ArQJ3t9EbypTjp3DfEg048cUgy1bZ3K2X8pVhgvape+ecrnfDG4y9s2F+EiW9h07ew4tYQrAhnxQqCL2Iq87y/fZzSoMdmG9IVd4FPtc74T4UXkiDvWxHwvGE8NRf9wo81DfkLfdJ1ZgQCc/9eKC7faSihGVrckDnPTJcKPYM4Tk3O/S4Rj5XwNLRNv+W71+F20yQOTNeYMzAK3Z+4RmeNPONS3kOW3xnj6z+XkZW4xOvq3fmpzD5Sd1qaqxdN3PWkts4a1/SBCemMTMR0xiMqTBw/igvX3xOOfVLIZ3Di23nQH2P+30h4LL8tXz4FewNcAMLXDMBy+B/6LnKuBr59UW8ywPnIU55ajrip5X6nvVG4m3NNSgXMU3eT32JmRUm5GU4XN2ZTMmK5uRUUN0PbLQf9VNOFrj96OD2ox1kCiwgMyE9oDLACOLpm4EJWaRUksY2zXxsS6D56JjCfMQzmo84Mx9dn8l8xOpmZD72Z6eYjy7dfIA7M6H/qnJQXz46z6oCEjxOfYXE20uCfbZmzOoNniaAhbhc94BcdwTUapImxKWZkB4m3ZEdvASaj5dQKg8iUfLbV55TgJ6CbBTFHoMofsd6DhgYx7fZnuOo9d0Grd9v0Po40/ruGWh9N6r8ApRcehSlqLfY00MXoMYzMDdPOzhX+T6IH6AxkOkH7zCxFLE3WPBx1M+v8AtZ2m8//vb0gs2hXpCVYSAWPE4xNIT7JsANDQGn/o2zN1AkeQYhDO0AbsCV5jg1RRZxblyhc+P3ixk35rF9zE4pOMjMReQmdYSArQbWPcsfxiz0knfQn2TdbXNQb7sDqMVx+fsO+OWJq2ESOGdTNdNinRHsfGWym5FosouRO+B5Gmz3B+SGAsYXCEK210Fvoc/QQ3B5uO0BjKlXLua9xi77J3cZbQQLGrjYJPu2Rlrn5P3pcwKhjW1oo/A4ufxEIUrAgVMACyz00x9npXcwOtvYwfiCT+hgrLFbsD10EULd/4Axe+TBhtmSd7eSt3ygNXnUspd2F3t7Ep42lBvi7Yb4FjPFJnmvv/uAkssGcBXn1EakDfmnSUGDwNjSB7wAvoFMFHs6GkwBPAbiGZTz8lDMB328H9Ah+eezsNNyceMQynjcKONqEJYPhkEVbjAdW8VEuVVQ8QP4VjBNwEm0BIfRUcukewFayVTR/uHFGFgCfx8cE9Ik+6SQKtmvMo7IyPbihE4tCLScBQTXcsZXXoDDEFf9gymayvWU+nek1B+5k3rba/3yhYygmGLa/q/oVMAtB3tQkl6FhoCjIEwSahHy0E+CgwY6BuV7RJ2Og/OnowP6+9BmPBJZdek5xMuq9rEBXDKAWVbbQFTb5fMLGXUQc3ebEyDkUNROj5LGDiwdvcSoHHYDl5pywOnFGvcK4esx+t/tlz2LmMjCc9e4PHvDn6crSqAZeglu2MJW36RjEEHPDSl5XUcwh/HreJ4FKoj8MV22RmYn5Y56DmSaD3uj3N9ZdX/nnam/a0z6uzhpfJY5uzaYzDHJn7nbW6ecGVg0sJLU7dfcXlN8OrfXntHttTO31/2Z3F5LaEZu7wepbq87ze3Fp3Z7J9DtDaDb657k9ro/we11T3Z7o5cx233BJLf3dDaPcduNMW7yyPWlGKd6QU/aNX+HB84MJiGD20MHSl9F37dQC3eZ51vIzAPiFILxlGdfwANelvhDgZscMQ4v4TscuJDFf0e2S94DoDZx+cxCdAld6BLqqZcr7xCzfYMYjHOXMIwuYcDWxGNmjXmDKvNQi95V7/BYeFCNhZ9HVddcw8ugurRuP218FtqVggcC8jbeNrrpz7GNatN5JGg+nmwkxRF3M0e8Nd0Rr76Ujc8dZm6vk+NjtmCE3MUi5HbZMxctT7seIXepETJjNMPpwzWB5+08Rv4hmItTbhgd1tCpy1FSUr1892Qvf/gSRok8yQnebca2uwKckpes6ATbdSfYpTpBnRJgQvNjuJXq+ovQRrWdehR+oBtsSXeDxWgA2kCLQd4vT9KkW6gW3fvVsNw7cYQi98uueYLATTgXAW7DpaBqwNEFphjwF7MmSzrzebROZjnvg+30aLF3aApBT/V9tBNnbylCvpB62lIkvMjGJbyFi3NSvrelyvc3NflemKfL9y00OFwc7CjuQ2lIcUV1Q/JfTVwmaF9NSP4nCL5q1FEIdplCGeThe8gp7KStKcwmNlykn3WoIh2tpN7hYm8HSgaIdHFfSms7sTVwll0+aK1rdrK1yWMuBxfqLq9Fc3m8b3Pmsz5DPW3mThhu5vJeJXXo8gbA5SX5Ay5P542tae55XDKH6vzyOgcTJO7snkh3di1TOLsnjM6uJensunVn15bJ2W3YknR2+vrQx3GDv9swjb97j36Eor6XNMbZRAIFvnSA1E0kQPzQ59UNAmtJ3TCpk6f3eRwb1t0ZXqh3Yq+uD5j/lFYW0DUOWpuPxmhNIQg/FxncSJ1U3g7lIxh3GcQbVaCDVJcY7T07LgxN4FJ/sMOoAGQdm9xgfurqZT4u+/I3884p7k5bUwMz/EgPjjRFtRtExoZKoE40vA7NXYH08IUOCUwGfVX+GCVy3H3O9uBxbb2DjYeFK8hLuvHM4hd+jBcgwoUueobZEqsM7hJ9IsYN4KKMMWOPfOz8R0zVOwydfAJV/ZM6mVRw+QEHdjJcauxgFyMKQ7YulF+ISLztTLqv1vrzUCnwpEYK7g3IP8IocYxE4u4PImWuumfD13CBZfgBWCnIq/uD8HxdXrVt9vBs5CSNxNMHfPKCJgrqL8OZXmFyef2i4bxBxr1sCL7R99N9EMpbSOMEiYooCSRqZWaxwuJOhOfALQZagN6rQuRXxOQVK79i1a5k3kCWCV8sRN+TF+MG2mkPaqX0572s5HmnmikPPPXx8w0M2r9CLB2AUZxD1qfQzK7oNLvWW2x74l/qZH/CV7N8kZHZ9eZy4V659MkFgl6yk6y38LI6T5BhvEa9AUwBD5wyXNGYcpcFBhwx/KrEkPLadHuu1fOkWY9kWo8enbT5uZ/U9WqneUD76/ewMyT53v0glZL3uB9X7cHr5+2pwC2tzacjNvCc+H6Jij4gESIgdaGu+bStGbd2SNssWJFctkgQXEuBMU1x/qcJ8+26lmrscTwB7Fkqefv88r/n87NCVHCtFCFwvFMkK0XWhp0juYFxFum8EGsP1/YhUjSSEPuyoNX668dZrZ4+n/zoQoHvYNxmlXMXcZChtIIqd0fWsFe6jb3SFlEuefe0Im2xyk72aYldJyT7EJ4tr4CJoCzCPX6WKS6X/O20ttWwff5F1UInreuNbbMI4QWxbaIQnhvbZhXCBiC9DIr4hW8xRew0jN9Ni5L5WifrXyIH31mUoqUybCU1mCyEFAL1En3y1UAZtht7RSHeCVIhtvONm0UQgCBaVNSZqLBuRIFP0bukUKnnN6tF3mjKi5KZKGDChMXojWJKyXQ8o2XG/bMFU+E19NOP6BqoyNb0DksXbWv6E7qoWR8rCnp83KsmbXGEIMwYvGk/vqXLBdqOV+4XauVWk8D9KK0UXetETV4ebF2AOaNJ3SjNwZM2IbobN9QpJ9ydjdb6Vc/tE0I+mcBDm1x1oxEzua0otXy1Vl7G8jKWf2ZS+Rt5eRnLl2iyknYoQ0WRYDmdvX3yG+8npepri0CqJklOqry0JHYn95vgLs/kKyiDwjfskJrHzmPCb3A2eb2VyKPwLZKE1+rbYZj8huzgkRuk1lG4EQrIfa+68BoeSarv+inmtR5lh+uEAbbVP5x90JQ8iaLdZHtuU4Ay+OJ3+TcM0q7nDzTaq6Ipxp+1QhplPo4QLJUbh6Lz0QXgHIf9MBzyD/NUi+IZBmt6Bx2jdsyj7YMplTo0Dj40z0Eh6hmqio1nb/mi4myuv6RaYM2MFB1ENzBy+UHcHDJy8UE8iT2y4CDb9m49iHP3keyDuZwg3swciMo0y4KWnF2cZGvywarKZ8aSw1txCRoNrEQkWy0ZoEVAo8DvnyioFvrh3xD8+zP8exf+/Q3+cf6VZ81Ef85m0ICWR5Bto4xtmx0q2yKj7g9sTZ2oT3gItXs+N6XUI2P09m0U3TEqNpiga2UqQy2coXWPIENlzg5Z6zz1jPIro/qVSisEhb2/aVXHSTbyinFv1HhlCnWZXO+MalNZn0mnUPn+5a/J0Xnp0mohA56F3cjvJVPiy0AM4aqzhm933VYU/tok1s9/mBkPmlMTorvwtaXyWnP8bt1sXAC3Nan5PLKfm26PvMszgWT+7N0kmfQyJkQiTNbU/UxsB8CK2I4iIbwUpsel0HRsq6g7ytbdvO0LG0wheh9r/LixcbzPNgy4YjtKhEnFQ2rxeQ1CiD7MjrufMBZn9/UhntbmwUSJbbzxdstD7yR7VFeY2eoZsRCS4zFkMoyHb6rxqIOwFdQV7BgTk5Wia6tV61HTQ5r5sMrr7FzeXcu0u5vgLl0i2y5AydcsS0KNUETl+IvI8k3E2yWFFBLs
*/