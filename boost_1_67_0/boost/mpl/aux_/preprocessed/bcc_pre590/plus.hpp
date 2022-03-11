
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "plus.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct plus_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< plus_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< plus_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct plus_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct plus_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct plus_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct plus
    : plus< plus< plus< plus< N1,N2 >, N3>, N4>, N5>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , plus
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1, typename N2, typename N3, typename N4
    >
struct plus< N1,N2,N3,N4,na >

    : plus< plus< plus< N1,N2 >, N3>, N4>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, N4, na )
        )
};

template<
      typename N1, typename N2, typename N3
    >
struct plus< N1,N2,N3,na,na >

    : plus< plus< N1,N2 >, N3>
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, N3, na, na )
        )
};

template<
      typename N1, typename N2
    >
struct plus< N1,N2,na,na,na >
    : plus_impl<
          typename plus_tag<N1>::type
        , typename plus_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT_SPEC(
          5
        , plus
        , ( N1, N2, na, na, na )
        )

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, plus)

}}

namespace boost { namespace mpl {
template<>
struct plus_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : integral_c<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , ( BOOST_MPL_AUX_VALUE_WKND(N1)::value
                  + BOOST_MPL_AUX_VALUE_WKND(N2)::value
                )
            >
    {
    };
};

}}

/* plus.hpp
SYstGZACCBD4J+hP8J+QP6F/wv6E/4n4E/kn6k/0n5g/sX/i/vz3J/5Pwp/EP0l/kv+k/En9k/Yn/U/Gn8w/WX+y/+T8yf2T9yf/T8Gfwj9Ff4r/lPwp/VP2p/xPxZ/KP1V/qv/U/Kn9U/en/k/Dn8Y/TX+a/7T8af3T9qf9T8efzj9df7r/9Pzp/dP3p//PwJ/BP0N/hv+M/Bn9M/Zn/M/En8k/U3+m/8z8mf0z92f+z8KfxT9Lf5b/rPxZ/bP2Z/3Pxp/NP1t/tv/s/Nn9s/dn/8/Bn8M/R3+O/5z8Of1z9uf8z8Wfyz9Xf67/3Py5/XP35/7Pw5/HP09/nv+8/Hn98/bn/c/Hn88/X3++//z8+f0DmAoIIGWUW+c77kaB8IhicKHyaJ2TgR5OoLpbFd13cYCVMSpK3vFDE2x69l/kOUzP6FAKlNkV8rKy3PrvYDDALXfSHnyYTMbGEE6MSc0aOcM+RnopUKWrmy8adVTMcPXCIxoDDV9UKcVsq6p6fTRRa6aDvDrt1h4cm0kdWtsM2mZNpKEZpf/E0IgjjO8CU8YF6sanZUfkVU8za5gnVF6mpkMddB97c28GpybVhA7GdU7PdEuvN5avniC6wsUBQMkxsfV8VhMHoPMJmOOqesbdediN1MdT9t1YxkyjRHsXl1CiWnXSG7WApc3KITfbdDjnt/aE325mdWft+dZbNT75ya+jn9KXKjUUkCpHJAWBPlseDXKRyMkMFejLNuRvGuOxdXnGarkGj4D3S6UekMfC21PwT86NTqq5QSQhqgdCfGJCNFu6IoBE6ncVe+IQBJSp8luaK636CN2h2TiT2nMV1LgWucelEX58a7pX8jfybBro1P0o6M/iiYjpCTBTfc0puCNwDkLxsgaqukIZf+BlYCzEJ7kg7wc0jb4jK48h877Z7f6ljbnW6DVbiBtRe3U+XpBP6p2kuGVZQEGqOv4DajcS5jFjQTPGsQB8+Oz3wAsojZxQ49FZoNNwnRwS47tK2JF8lnWr1APhEEbyyCY+9idPFtlAaK3GI2vWnf0Dy8GssPsGjB4jnncYmEuKStJkLBc6MU0y1VkkAnyTeww7Idi+NStE/rKXLIKgyw/+G5PBzyQdz686vz0T4c8r+1LYo5GrBVBv3RXQV6BnsLe02JiuhHAuYLQtgeuYITS/oCZS7H/SXII4YvoF/k4yMgI22hjDqK8jZeVRviyiMjZPxOFYrdIyhylgXQ3cjacd5iQKi+HHiDToBfviDAXmXDtSRP0z3fG88xMx8dfZnQosgv35TGtGobaxfX4G/gCxtZxj52McnBOFo0ZJGTPzx1SnIjzayQm+YLUrwR+Q8m7tXtNMbmBJJ+8bwahQFshaABljjDAk/rbTVzbWVFV97gUDKRMwBlIekXXFwvTWEskMU3VAk1U6V7Au6cyagrnp3DjYzK6tUZJhhfXMS3QvLhyB2YTXm4r3hZ6ilhNaxDyhRD1GA9wHjIobS+9M+mKvIngXVrVXWrH8sR5+kYLdrVChLEutnmRtBfsP5u4aFw2C3w0DKMczvaOG/qqBmDMb4lbx+1KddrV3VZnW5WrnwKxPh+Z8NJ6da2Q8XrToSgMOmSqCK1E+9epu3DnfcFGnvNWfOa0JVrRXxMzwcZ6WTxv8z9HU4JJxT0lA656jg4lOU3WQWBlfPWzZdQejY+DhXvHW0NQ45ujBvAgC8JvUtILfsPItfbfchmg5GgIt4pfaTPOhiuk0Q9kmksQMuAoOOmHEi72DE/x4IKNGWLp2faiI98XAuosqJupEsoulR/xcdOxr3Yhm3FXT02Hz4rM5lC5xJewry8vnHX6Q9KVDI+C1kKBBjMgwlZdkso5yZZs01v1pN0VbQjeh1wHjcC5a+5A7fUD+qRyvphleAJf+bNvxOVGAzyC1bDRoJVngmgZRhXEh+iaAU5hv7MTG8IXDaWtaCnj8BK8NE7oce8Fm7IDvAUJwJ2+ohumopVysF1kwt4ubLDA+mNGwTt7ZO06goddGn8mJJu6gFmD9xUsa+VNUv1RsbrFYe8fM7ioyChU7Q/Lx95K7EWpYU79c/NUKbnB+mw9BdnO3Z1Z/KX7GuPjCy2ym8nh+b7SpwafdzBB1Ap9rLvzWCV2ncToZCp0cEOQ52QT36OBaeSdQ8nSEfMTqO7Bc4l0vFXZBadWjSMdE4T4dA7Kzj6CI6I2hSVmduLovZKkLxUnl0mXwNEUawZ31Z++KoDsVd1f8Vgv5OOT9dJrf2DRZ1ZWnFVVoNBKt3LH46J/XL49Yipt3DvEm840yIc0YSrYZici2Mfhdt1dMryveyL1+ImYdzw3aSZP4TTeM+itb2T5fcO0DLYbBbD0wCBAHN89vubVuK3Ri/E9gJkSNi0EHzwx8XgTRSKigVxnaSvSIXCn8E/pRbmSbbECeAKACflHmsHT26oA/nvIlQ42IHNfdXJrh9nyJyKLTlX4PwV1CHfXXAeGi/hFnPfrwAI+0XAhTSwQqWiEEH2r4XENl/VJYRUqydUt8ckbxRHOCV/arpH64zXQLWcNIQuOiv1FSLoNBUq/GCcrbVE6pPsamq1Y4TDscbp61MYFjd98Qm0cFJ+6QORc/ewJDNyoxTceqmgal362ohLUxJV37ENUsq8TBY309p7G8huHyAATPLM5l9lVNSD3bySaMO2IrEA1h4PDclDe9+FhvTXIMJgo+QpmdSySNK+YL9zzmhJuy4OYwOCXcneFvJ712qFr9o8Iu9ZIdGfA1DULf77+Ge8//LlapWn0X0OVIrs+A+kFkEvf43bbMpQkL63X3bPP5sGJ8Utn3rR80TWB4Xr4QVkNPwSdmdrO5t81v4B5lGn0wc20cqrm2FyMZm5VTuZan4qeHnpe5UtEuzjbwsyJIZ3Go6/M+BNRQFx2Uki23F3PPnUWzoRHCVhcOqAb3FYWQwQK1ypNWs8LrJ6x/1vEV0n6eCR6ji55tAIq8/0HO0NrNWbIburay23t55sj3+PqoVWnuPnKwwDd5tdQ/DP/wO3n3DHdWnm4HnDVKcrqGyxf8uqprh6hfcSb5D6tM6Lpf/cAXOfIPBijVZVa534wXJnkp5m8ldh+neT+kGv9Kn1VPzztA23vEJl/Pa0MG9/3mpYEaqreQXwNLirBIflvHnQMHJ+VEtynyqP52qhBT1nxWiqUawci9PIG4j4hjq1nVLuhOm95dEB03NnOMoiZJIS+ftCmvFoJv6SSOxzx+ezoyt2f49Hqy2CoGR6Rw/uSp6Pb8h1PqGTlhPOrJUdx2zDww1qNnUi1UjWqKrVVrA/+VvMYQ2/pckX/D8ANU6TvgcQPZAfLxNpIO8sFx3jXjokoSfyyqamFQuk4xPg9WhCQkYYTVzCNWgvCGYFPqmvQDuOKe1ulb7gXhQ1ImDcpTBcS3HY1IexojcacNW1kX18DpuueRDxZri+ZFeeesEHvKnWXZ1nmUrmpKf5wN5OHwIaRKq644L3iTWsmgB+5vHWTyyOthKcm1ECH7eZ+BgmaAylpm83lGyfwZLAkH0Ngr585JwRvEvByjK2DNLS4hzhJffz2dmX74HtG7joWMmlKZQBdNXT19+BN8/g85je8mg+3peU9M6eWm0NUuajZwzaYRty4VO1czqBfwyoHNDb1Sec1IVEs8x8WCC2AHXD903cndeON1KYNkND/HedwLYgL2zmR61ryU4kEgVigheXMkpxHC99moB6KKi+/33O99+v09hgrlv6RIQdYZ9VxTLKyiO1u93EjSEDfsgTCWFY7VnMldYw+/75gvQYsJixgg9tIax5pvshmC+t+I9d4fsB/KfCFS76pfwS/kJ/YSGsaeHQaEQ9h0duaI6dxCMHZX9QRvDGOxXf1g2vV8eVNb9KpCnQImwwCSHxmPw1ywHMyNbbVIixOtfUzkUR2PJxbS/0RTMc6aL4q5x5Xf5tzkQa0CHuHEBpJT4EdFX0iL0kKYyhnEtFI4ZddoWNEBaUJQsDO5v0OSB399MirTDZrOvZ3hzBKk2k3e1DmcQsfN3PefgzUxSG0u7i4hv1Ho63KUf+ysiX7dXtnPwxpCNx6Bd5OgrDlDSekZVUfnDnBdDfNBcR+9dBKwkbnKxGq5OzXVNGP55ux88DHWEj10Odh31GZjiJ633HOv3jp0d1CDerze752hH18koqKnvIBkQXArO9lRU3aImB9fUiWiaOrZqu8hTLYnnYtihX2HHnWOi1PfBVYnyWBzjduB4DvQ7/MKaSbv2yrzfxOFNw6/GhSfmDThNOMB05Mj2T7TzFuOv7Xcl6LQjM/IAYvTgkAM1L+hqL3nyqNt+TGdqOzCLd+K3IEMOkS7pvxGG4xu++5dzVwkOaUPv3oSeWKxW2XEwwsV6ApmA0dDs7drXU7WQWzQev5bM337KtlqWTEDpOPsnkiqrVSq6O2kVlXAw94881FLveoF2KYLL8l/hd/5OUC1WzE6EtrX7hOlreP27BaBVveYAOr8THuNBa1icAnQ+RrI7AQA4XH3GvDi7ZIJayXvVuvTgu66fo3NzkzTMDqJgziUCfJgvZGXOnjY1lVD+h4UKqZb79VxYpQwmU389MAke3kaVeQl85s664aYzF0t71cfr8vn3CeDOWxfBMXzij0oulx/vGybJwDVb4aiD1aHyHY9LqDxsG35egvOQXRUiOVxK/h6i8EIXqfhBPvSK+bVRZ60uNNuFWavNhMUmDWZNpZfd2LsFG94iW6JuRjXP4QB32uFfHwSrNwKClA1OH7xqgkVTOnvMdsFJ7nTvxaZ5mkwDbXRC/j2pw+5Dp24CeCpJMduhDPqouX4Yqi4TEXF7HDHoM1RSfGdWHQerdUp4Ab8TQfIQrzbNX/uVZJHC/oNTZxV6Gneyco3krodpoC2yEibziFrWnLpi1W5NUsPFkneHh087xg6lSd5f68mHp+Vax1kvqXXVAP/dvE7/YWRYcfy64XZhT79i008E9z/1sKXjT+tvyWpeTAzlrk1PPWCPXGPGy+Zw2uujb4lASQMpMqgOQCb5jzOla1r8hnAM+z3On4D6+bfvjysxR4egYVysJvM6GaZK48yBrJEx5PhFyqOMia2Uhxdo57EGbWMk/DSAxTzJiPmaW8n4pqnOcN2bnPuM6GzTit2cF1tkw8GhIskqgi7SJVheFfegU5fITWKT3vl+tzuP4P1TuDb5fauyXXyvouGXkzeB3fFWEi2xLRdR9kvC/Xkyn5fKdFr5F4KcFPNycpKDAHKhGrTfoGzbz9IX/tK4Z+dMseHiXf72EdPYD2YhfmVALRmrHsnr7oRx4anFbo3GFAsrtuS4pg6Dj1/FpuGuhTi9EUGW0Hu7Wwre/lF3AnT/ul9yaW57FTOS9swfrWxVCzq4woU/aep8K0VOLgzy5yarjiD/xQrqiRiJ8qict3v1N29dUXrz85OIuDBefur6f/gCHdsstGuv/TeK/h2EbSjy+WH4PwMHovOuh11pvSJXkBm9jXfRFLd3hf9zQK7D480g45WUJuFQTo6TXg6grGPa7wW/9B5G6f0swX/TctocvE9Hvzrt/nLuPPLbwZ//nt25Sf3q3f3gx36ovdrd/ELcvvbkv99+pX5wT/++fsWJvSxez/4t+W7y+927uf0V+pbj9/6F13g1+fd238qHxgjFFff/Bc6bXOi9qVpyAha3yxwa04LbmH0HtSdJ4ocTfyG3v92nFf9RpuAM7bfqPehNPFoDOJqpfzuTb9H2Xzm2z6WaJed5WAm5Hf0/Bs44mEu+vEcWr6M9bQlSPm7eQ4hqeuyaCLmhWxvk8rZwmUitwa4pKkP5mgkU+f4fbrjrZ1ABY4lCtsh15VeVCzat7s1K/A4b0l4tOQIu2whxIUneCaGYuOqkETuwJR8NUO8JyYJ2tPplaRM7xhkoOAF18+BsSv8Yl6oSTqzOEb3r8970694MEmrbwAfVTRQ6RRpXQ2+T9Aj0gx22/ol7jqU16fESd7S2q9XcmQRHD99FTdEkOQmGYVzv0rYor1reC0BX6SoP+FtMOJdbdJXnxuCcFLhUqSqiYvRcUPV5bEZwRBBdWBFdLIWdRHiiGJKUHO6ll+WqT03fv1QHHqfi1P3ywleL+Isq+IY/WW1pb9mPe2Ou6fjIdLqCJJydr2B9q3M1T3jOaxoKYq3k0YwDjgptmr+gmGcNXdMG53txxq7nOHt5fPT2luNeHEZDGn0Lw6bEG2R88AKhpnBpSbFL7qsmU+fT3iE+yp0HBXcc+V99Ve0rCEqkWoc7gbGAxZgcdk59SiogJ9BKnXkgbfJmlYx8A784VfKdSubBX9gIIvH7L6rDJQ/UfTlaQ05uqyI3a1Z5FSoUXPEM494dzNWEA5AYn73/WWi11KBeiId2by69uiyxIXtUsc983DJo3puF/XpYeezx485Uoydzg+ABQlDrh5L+s2ohbVeAuthkZOa38nkuJN/3+WJVmTM6e68EEANjyNLPHdf5vlyjG5nSa8ZhwByVttk4fRqo0t4OyxAHvrV5Rv7veFhTPoFrW+es6Rm6XWuYFOi6lKgC69PwCm3L6i+G/H2ghbHI1RNIEU9qRuw1toHaTavUU4bfpk+/9mGxexo+w12tBMAoyp2eYgMwTj7/FjGH3kz4uXThYo73ZCi0qsBeDhurlMIujhDIpY8JzVNWpCioSjqnC6De6kNsNGs8HSAZfQ/vXyf0YB8gRD9Bj3MBFSJEa8En9PnsSfeGTrgQgVUa8iSW6Hk5NCRoCL3kOyCQE/zw1ad97A68k+kgciesAm2YqYTI78lx5MTop+U9RwZX93xsB3aXcJKWS+fbFoBK2Vbu6suHdJqrPdK7a1MxCIrALtxY9KJg7hCr5xbCOxLAH6juiniXwzvmEo33dtZl5bCvLuP9qQDt/DAOV+bJ7bzjK0z8CSrZJAM8O16fuYPH1nxddZtwtVnejlLABoGaeVhBf1Ndglu1oAYpW01eazLgFUPn3we2WTYT0FhOLyEHXXQkZ0EY2wsdoDSfylWKo1XB2nYv1ZxZwA17aOXxBuDri3exGgRW/c2ArvaQ0KgPwp9X2tFqcuTTrWr6tkdpxVPi6ZXr8jiDBx/UyzImOKMCFuDkw7fzzIb6DXP3cIZUzTDJ2C7fwBPRVpQOgZoCfa1Gsnr0BlxmyiRSOK+coXJgdcLZhOLPOTgUlFXSXoE6f55XSHQeNHFfq4tSiy2ocA3CgiipGGVFnllfJP/ivrF3pCH4Zq1OVujHU9cDv1b10/QxXmbN7iPJTcQz+5HLsF34dEYvEy8yNcvIc0+jOoQYBk0rvVHHFBSATywDBiXbFXlqVs6VQM0XTiCMTvb6QlaHuP0rulHmMSKstmmN7ot2MyyeNOVDHysM3yLD0vmMBTMuX3XjimFGz1UpdbVseD0h7uiAlFN/1wtHPdUh2hr83TMy+CLTGkjKl+xR/diQJdru9WuXfFUlLmZJ2FbEyjBUR+/pwp9yrZnotyi2veyLqoDomNIPJDabyUAv6C1cGNltiV2Qk6Jfi/fDqtWgiSXlVj/WbCzqY/LVj4rFjTeeYIUqhDOO6+9J7jbYob+kwRuAtYkrY9C1UDIxekcANO840BkmoHUz2Tdu3ngL0qDIeziQPS63gwxc8pD5hOgHIgspeQXKdn3X2KIqxqt+8rp698AX/oXbAw/eii0ZtG44p3LiYLtU7dIyv6UfZz5SPpflQeyu4xYOo+6IADmzUz0+Fdm3Vwnop02hODnSwY3AIQBcMzMEN2gbaqwzd6XdX/P1ZoaMC2rQr7V6q1+xIpAzmfZLMxuC9Dh2RawHGs5oyadCiv9t2opoWb2mfNIqrtfyuyUwDnmPjzVF/nEFpqBijiReHqWkEFn92qBMJAdD7HV6Cdq1MbUhrSfgt8sv7LOq+AeuzGbuNNFEjCHtwoZDac6S4dW+Ovi2U/1j81SyOrJbiixoJj4cnc5DYOJvYVaen69lFU01CNYkfnPnqAst6TDYJYf+hwOlwZUwvENo/kxC/eivAfKrSdkqaIJvbcRne8uxC/bUOaOVwxUXNUAMfnAYByKNKFAuRrjf5wnwFCb5t9qepSdmySjhNJuXh6UdoAqoQFT4ze6Zaa9VNkkyOtHlOxvhkdNISkbz3DFKCu1kZPIrV35+wnj4ZCunHkhNUezUSHB9Rzt9NlDowWP2G7aB6FDwg3e7po07xKf9sOGTSWp5HOI+dmQdfTUNO4UBz0skgcKwDbo00i1ag40xUHL88XZVcgzvBqAqcPOUbrRrWdfxtl5OVX+103nJhuxbXiYM1BO6b92ZFu+yHfxTMbcpYB4mnU0yRMIJRZNhOD/bVsxVJZanMrckSyOw+wypPcEJJJaEaUzkWWbij5/eT6fyR4UZAK7c3CbWX2B8lE+f5lkDYsfaavkHHuzH0zeSiAEKOQEAH+2OT6novQFv11JMTk7gV1nL93hvTTmaPmTFXILbwR9H8FpwLX9s4qVAq7GM9rLWy3KahDYbRX/HwAkgNt/3/WHjP7txmLvl0OFGq5/xTTx9gKzL51NM8rGpymwxFZbtk7z728uIFfd6Giu3lL91T2XdlyG6i2uLRunKrdYCJnMaDjp8dvoE06QSoH0CeVck4BqBXjMXEAqBccxKMtC1QI0AgG4l5QLJ0m54P6focoFtgvVCzdP47jN0iXZa6NKsdz7FCCSNIKPRfVRdz/XfPJvMz05TmMd0C0vKqJDfPizzm50lE+NuvsuWLlPrdxR2a/GBRj0ykRlpfrjluAQ4eP/E3ymJf8SfPH7jo2wj+qD3hvRT7jI7L07EPTaYPBBPeoV/OsndtzMf5qWXDE3QZHarypSe+bGNalzE1Sp54zX9f9mPMTVt8Z3h2iJuq3JVcfyqsrie9DD04o1uztDsKyjWc35tJG47cP/arwHzj+e+VuPB/sLV8m3/URz1G0ZfsiGaTikRR0yejnbNeec+Nn/8ngPnH+8a77VeNZvj08G8wdbRvett8xD/cxxPnqYnUgPs+IEkOurEihicj5sf69FLpjilN0nSv2hYuX2GNqQsxbtlmNM/EbmsaJsXX7STcx8rWSIPP/arG+0h21OnVq2VlPhVeuUTb3EEKTIK/D+Vll7opWbZHAlxF9WfMiPN66i+AQeNQOJfcrKrIzzuYeq9L6MRRjbQV5hJ5Rp69N1b+isGC3uMDd7RfN/dDNB70+hfjsW+uk=
*/