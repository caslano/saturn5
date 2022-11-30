
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/times.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2

    , BOOST_MPL_AUX_NTTP_DECL(int, tag1_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag1)::value
    , BOOST_MPL_AUX_NTTP_DECL(int, tag2_)  = BOOST_MPL_AUX_MSVC_VALUE_WKND(Tag2)::value
    >
struct times_impl
    : if_c<
          ( tag1_ > tag2_ )
        , aux::cast2nd_impl< times_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< times_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct times_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< na,integral_c_tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template<> struct times_impl< integral_c_tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct times_tag
    : tag< T,na >
{
};

/// forward declaration

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct times2;

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    , typename N3 = na, typename N4 = na, typename N5 = na
    >
struct times

    : aux::msvc_eti_base< typename if_<

          is_na<N3>
        , times2< N1,N2 >
        , times<
              times2< N1,N2 >
            , N3, N4, N5
            >
        >::type

    >

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , times
        , ( N1, N2, N3, N4, N5 )
        )
};

template<
      typename N1
    , typename N2
    >
struct times2
    : aux::msvc_eti_base< typename apply_wrap2<
          times_impl<
              typename times_tag<N1>::type
            , typename times_tag<N2>::type
            >
        , N1
        , N2
        >::type >::type

{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, times2, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 5, times)

}}

namespace boost { namespace mpl {

namespace aux {
template< typename T, T n1, T n2 >
struct times_wknd
{
    BOOST_STATIC_CONSTANT(T, value  = (n1 * n2));
    typedef integral_c< T,value > type;
};

}

template<>
struct times_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply
        : aux::times_wknd<
              typename aux::largest_int<
                  typename N1::value_type
                , typename N2::value_type
                >::type
            , N1::value
            , N2::value
            >::type

    {
    };
};

}}

/* times.hpp
kFdq6zdt/NeseQg07zYfHfeaUfkLStCEi9cWsR1UIdllsEjoNXzven87EvNExQvm/F6xj8jdE6yKgzRxTEEDNepMBOUarBT739Wz9tDGBWLAj4sqIFiVmiawNgvaHBtP4VdnKZmR6jiV++rNmua99x1sv9Sx58Qkz/lcaLCUbz9IURWrCYRx0in/X0aCmra/j06FNVU782CDiZRUiwtRkLHOdFnxJD3ekKpGseHmM0E1q8jNTy4KrLJWcO8s8WpC49wL+f2CiQBA6TXt7/XTfg+hc8meHwBE0DkiEMCcXIEOBffBnZscePdCanqgtQH3VI799f6DblQFsxM5rdNg3sboBxRuBtdD4jP8jiprMVPa9c+awoiWzN8KR/Sst7rHPzYVWF8/Rvtddmlf9g0OpULPlgHjgpmJQ3KO5JwVxDVREnhmh80LlmOLaA1f3Hya23wy4FYDWwZihmP60iIR4bFEfGgP6rsOFk8YrFOxPYGBwBV22xpOrQbwrhhax0jUdHKopYFr1CV7TRWuSKyC3XUAWj1M7nPENZDzFNvzpMhZjk3cJ5XErAm5Bo33xhPCkZtn0INGDpFvw5OT11PDN8sGuTV3AmPrDfQDDRJ+vjXm04vpJqeAMj1OYUzeAtNj7kH59U2NQSzUjYUQ+RUORfYBT3nABUekAt4UIFrIsg1DOC3EOk2lCHiUP/KC4dg1lbDvUT/8akXpfye352Xtfxd3KJqwt2P1q67Ymr2zbML4JjyiQNPJFV2D7EL6ii3cM7rzVRG+8/3dJf4Fj/uVv3vy/w21M/Zk7uGPQcztMy3qh2gaEDMLBLD4j6cRzByBHXaAHi4ghqbVzQ5DD03puHAx7+kimTwtcr7n3btwFM2tOaT7ewq79Xpkfh5ssMDjcGqTOEUVJMRoVzFZx9rNdsglFI7o4KNfCtg/6gDYAENH2HFjhfKwnHyVqPOC/pKiGU2BsDjZiJcCCJpCTi65hNEOyCioQohvxVzieChXrBzBrqw/SxSt5EuUBL4esQ92ifZ0ldrWmyWlXD0jrzlfXayx0zhLeHS1RKCU51O439sayylhBwnUhvJuXHiGJgAHamEVkTCAPJQAvNq6x9EDgueJgGM9Mluo9x2nrHyc7axu+0uvWOBB+2jpad3z14E63S2NA41pGKpWJcmn2cCj+R8yVd9iTwt4O0RC0a9MS1IblDtfantkiWmbymvWsQ7jTO8N8oj7/NJXzF4dC+qrSp9j/xPcMkMNJfDJXSwDhb/gbp7DbQm0uNZWDPonPQScQRtj5ArKKZjmWIe/ueW8FLYxy5VmTWnk+9iq7l66ntT0YGJ/F3GFYVXHrG2VD7oc8w4sipJh2kS8LVcVpxRk3pgBVwWlu8zPdC/xrytf1xAFs4upV2ye5Bv0A40Ggl09Lb1ZXhfV85F9LIkUhON7qRA9KBUsgDXiMIzuo3oCbms/eQtykeeWHJL4VP83hd0jxFaTMlYav2dht0wTJGkqPa5wZvsFqCAl2gmGYTYrx6wLwqq+bD38VC3+cD+g64KRZSsuzgavQBr8qNUkmJftXbN/nToWQyuxuaTQBEEAJZsCWrCIc0BdpCSRDIF+gN8QKlb68HkGqkLEAgwn7ntYEdwGJ+BCjA+FGdcIHJAzf5obi5/OsunUPo/R2ihb66K5dZ7x12E4jtdaPDoMiliP81UbHvOkWvCdjMCZ4Oq5mqjZeFcCL6rSKxYABCz70/AXU4WllDFFKWqwfV/wfNaziNyll/qq2MINjd4Ool4aXySuyQPFd/9/YaleE79ZYLfQRXI/C0NwJ6J0efyZVpHpfLLatno/XmYR7zQ2zt3htzoJNMX4GXG7w+bCHDXiDuoctHsYPHeMev+m93MvmUA48mYRjp7d5ksgH7zt/AO90NHwxCAdoUrHjZ7onf1UokP91ZbtJZRFlNyjcnuE1WpmXyCTx+1e8X4hJN9FbQOWbArYQdOx4vAR9pf7ZRttBS3lFlRJ37juULs86ROqE6HltFXP/AdR1RPVYFyoYlGA02q8mmaSyzC29Tj4ZysBoflwsMUXsvBDOX5H7BlOof/z+Xgjny+F+Kj4BXc2wc5TpdaCC046eeDpWg48I6Uf6SpdQ9zcT/H12PMHFwmN8enfgH+YfLr+0NnE6Gj3r88PrTP461hvsfuBGZTYeqoSeH/eiIEOSDRAyND4qy94HZ9150a1nUrP6iW3qn4goLmg/+3zVtNHBPOtZ0gHw2rsY4cpHLUlzqrBHfChx/WlDLsV6YUCmibjfW/P4Yrgqu0jAGTxlkLDtFxcq3YfZbm7WzBYxA1bT4jdRd6CP1VwG/gi5hfLwudYkOY5NumtlT9J7jr4NLLWgQqH3na+oK9Op/z3q8xein4axiF9WbpKcwr/yxOXgt7RnwhqdH7MjYIkSjdyO18XuAmBvBYMxckj2MgnFo0AHUVPcNCFg6+SLwgXYGdZZqONRrPQprc3SlvcJm8rhunSuAEmXJPo4fb97QS/7y+RdYemsqgb3t+LhzJKZ5WbGgP6MCRN7TmLBkooCU0SoR1cU6Q5HdgrDoNTywC1WnbFHU/Sjt67Al59j9+TShilKoNQoLZ9qs3x3Bbk+vyA5BQ2srqj+NDZ+VbKU25quFh9y2r6kQqqi+wruKpAK3Lr8GaZ4mzsAA3Nj41KiMUgjSCJporQOVHW7t/bRuGZgSCGWGOuHMyAt0m07/I4euUPlAvpLVdefMoqd2ri2XehCJd3Ys4AYN9m4QMNoLwexDDJgLLC+fUVHDJ7T1YmNvt0gdhErBn+5lWGi9UEHuFVi5vHHATmCV1z/+awWzRZlWDTds5WARizfeoycYYq+Ogm535u7ytD3tWGgOXWNaYVjVH9xF6ju3d+ZcWG1zizcdflJOcZzlFlgrM9vK1AiIYNhQiXC5Qd5tgD1xjV4S3bUJeI1x2Ip02MV33zMhuQzkwVVr8HtQSH+PsPRVyD/PT8yCvbat6AnIh+RG9F70P2W28D91npv/kDffPhY8waEzpfPErYbkGzmbCga1ZEd3exHAfKeyX6vvz10XxWiq5i/mNukdPwxu1XpORXaMpQFCjXU0ViNIsifmbGIMnng3bnJ5zrg/zE/vt2QY8ZiVnUecfhDUc0jQiMFzfBiPHpXlyBYk2Cd6qzbWeHHUEOX8IuLrmzRTLjRLdbwJ230Hoj7GDYr0O/4zQDQT0NnRNBLh6GUBCEJb8HAN8TOkPxhoNH9I9Hpx+v7N2Et5WjHCS6sB60D2nMzrDboBt+ZBLKxJiuoqzcJBoCEBPPSfZweckWhEKICEcbaKLOIS2kYrR475CGVJqDAB/kzOxz2BxVs1L6PULoJvgASnQAnpPTDf0s6QFkl84sY68rbbfGmK/zE5wLYFUsYLczzzELvS2cn+4kQICdVEYAfqUJAADb+eBFfvTfEOTCEwEkuVy80tPrxBIy+1esE5b6jgmSDW7pd0G0k2ngy+hyHUv+SzW9AAHUusO7gT0T6eWa2wIThviMf9cJqiEZaNM/zBahSlfstDT6ZgW1QmVqEWOGAXUGnL1abgA8PwoyhuSRSRGlOl9PoA/3i3gB4X6oY+8j71h83+iWXU+zc29numA2INBH0tTIJ4uM+cEpkNBbZfuAODlYDFKF7P3cYyt7aTNsxOwpxjUjjgAB1oacWPG2e8MN+6i1B8PqRJXpT8LPufaYIbc+kIUi8LfjakwXqP21ydj0D8EV5cjQK7wQZcZwtxqhcsf0ujvU9COWbrfD2kiAaIDPFKhF/yRB68FpTK4yHB53JtgOO3kBZ3/LmuU8UB+1vuEL6nVjI5/3vt3H0BdlAN6+x8P1NNwQflNs+4Ksp+e7ig98Xp/2RbYSIUxKPLkH74+/YM1sOE+kLfHdS7y1HHaOdoDAQgTAhmydG+AZdLzOQzmjbFgiybNIgQxP7kw7otaHnDEby+HpdhZMFFNl+s5dzUhY0LZWJQbVuuFrTRtpcNXbrGKifovL/IPvnfSfhffdOuy+hfVtO+5qwgd+nPajlTCOK+k4ou91mL5abG0IB6zSbpHOk4ibTAIrgw/t/CtZNYyAUJ0oiycQ9+F/NfOF2221u45gp4RK5PRFzGYMndtB+4ZAx6LG5GkrrYumA+yh1kDhYeYImf0E80YI3DRjfFCZpAoxEoTT3NOyZQ463tnWmS7p35x3jB8cYISU9fg7f3ahz//dZkPHBry+XKmV/yefVu7qXvIR7J4m+kife5JPMlRHNCU8J3483qbWMP/GP8mK+JMd2pEYjk9gmVw2CfvD/pVQSEtWUykVGe5HibLi62Qs2ylo975PwS4zdtpta3R0qqzNzkcXtyB4X7soyAY0I3XZT0RUn0Z/QjRQi96Xm+pr+h/HU569Q95rBmmEAJ5Kd7RWKO+Afhbpaz+dVC4QaJ2UUWfpQqme006Tf2KvIeoI3zGplaTyS0nG5xFLhI7NakEqn6YPa7h75s9wGstV70dxZ3eRq4MArc5mpHJyGNpQl2E7hIFNKcGJTB42DFziI0UQx5QL8xHxUZkBF9b5qEpLYbiPlSFXxrkojWKLv62RagXrCWOxRXEFwNG2TaLrxW5jth6XRX8d/jfzmyfuBPvNTc2rLjJ3Hex0t638XZ/KRz0AHrVyC+gJOPzbiR/g7zpM/C/jIl+h4g1ZFyRAoy71yHVwOF0i46qC0dgPaMZ/u1Yqou1nEsCVgzjpQepFI3KAJqNrA2mIhbX5whgkEfFyxsiVhU4YExAGMW1iCCjlDNDH0h+GtM+g+OcTYRLp1V/4MlLkeqLAYQyFD04+MMe3pUYBCvFmI9YSAhUQvt++I+QdW0/P5gx6n+DjL44N34NmzwzF9VzVPcReR4P1RgMxO1odDNBh0WNAfSYGF61LqGBa2Wr+2LJLqKQhMiUpKMgwS5I9WXp5+I5esXfgMVEDlYQJAmVA3LEXYe3feZc+hchbr95COF/QGhQMxCgjyKHKonyKH4GyKALN9BaS7VBFARwtjLbVlK11pWDUY3cQmwxhfDjVafA/KKG7lQwyPYZqSbSmonOrKcSrj7EdIv1ssu93eVsQKBusdCMrnU5zJykBVvFUqP6dVo9EXfkHUB3XeRdlpqHWMSsLZnqs1a4rmy173t+EyjbFqm01A5QNxPa58k9np+XIjKcRyIx8R2QhMnBZ5235oPA+HoJ5c//9NU20TsIYZYfcJ2aIxOzapApUsG7Ck3ri0RoHpQbjSTyBM870Bnm4Fnkn7mbD6hosYYdQCkShaPFm45mhLoWhOmgVArdZrChtIGh1BpQLW0qKukUpOXvxjpTgwPI04eEcWPaIVBcoHoLY5rx1T9RmVz9KP33MniAuQ9UojgH1+rLDVexpzwYknyqGaGuem4TYN/CWeQ1LNv6Z6EPPAMJxu6t9nhfwCwVy3XryPCI5fnytmE9kdtt+aUdgA+R0h1fWxONDx3IFgCZbQXKEyQy2ID/PqYAe6JuwGGNJWwgdhJN6qdUYofUHkwZ7rbskD8j9yciYleXFQKKGYufOj+nRbeTR1E1mm1D0RVDcNJpXQ891Hwgi+Dg851urVXGF7kTiKeMM0oTm6bUg/5JGKMZrbdIwv3pf9g4uWn2zZ9qg4glj29WSTPmkzWvB5pNTcspCM8u3hnLCs1aXn9RkKdXr0UVDHXTg01u1K5EXUW4yK3NSSJF0FputQoXxywsdGJHIexMYsUpAJEhOSig1DgxfVuPZpPkcpJ7ySHRP/qNkUmBj8oTLWWSqI3mc3+qtP6UIMgyxfmSOJTMJ31++8ZejT01GNWCN5XKHCaKla6OGgwAshSDROI7AFydla1D2O4qV3xJYuseW+EBat53+L3WWHwzW+bzrVQSR9qTF7B5pTlGe/9xT4AjIvn4XhOeWlKxyRcHpU1ssAdpVJQRHJZX/O8aDk3+xODuXYsjuAMUvh0LTwbN5UKykX8qXk5xe8X7o53eEjfHuawHan8SaKZD4xVnv3GTLtlwt25dLbwBdpK/oU6SF+YlXZOZ1Wzr+sbnfOzrIZRIxc2mfsFHR+8irIRGtIRF0bx5P6nMsAzZwXLuxAle7RPPeNrsxe0D8js0+1Oy5Grr1Q8WkUqFiWcWiOVnDulhF0166Ap/H9Rag5QA3SMWpTbxS99nBzDJ/gEHualrzDGPlVbA6gbfTtb79IzRtBQ6ANyhHEUVpzWWKRa7qZokUdksX0TDTdjhs4wTbqcxdZ7JgCNE0Xm3stm/XMig3z+OwohWcTcD9M3HbgCuoZd2whZ2D/MbkWmZeunSLknGWqAJ9ztOyBB24urg7TWXnDckG1mwYtgD+GwoXy7JD2/GZhjM6FmO52bNQYyNsNaJTp39ved+9y6Mdwh/yEa3cFSg0cpkrGkBKyR3xAa1OnKtehcLgQc98S2tZwLJrtRt2pPskpFU+XHPdhltIVRnt/FBxNQZ9vkAkntTRGC0+HLoZGTuNWy+R43J+cvigy5QF2gosMZL8sCGNkRZdv6Y4hoMGL8t7mP9feeCnjR7LJLzeryT8nsk/7ySP7S84vMOsFAz9RSU3iLC70TV4tfZgNCPDitULQrpLiN4X1KcGs7SIYLrSd8lqc9/yZN/mFi4Op6Q6VZS00X8SyRc0I3M+Ws5q+6DKt0T4beuRIbxDdCQcEaFm2OVsIwGVctwBgtwt5tFvUZm7/cQ+yBx3u8BJfU0nDmWzcilrjW8QbQSVc9alZAxuu/NkrmsHAOf3o6O5uXZDbbFIlGbNjmDkTQuB2I124nYAqol0TYXzjj0kx1wvuY1FMB/iQds2DVEj67nYzj2Ta9YiWzlbcvDJk9FXIoGb5/vE8GILG55DiHBf5m3K/lyoba+Mbs1OxcTnEucv+fezkjNr+EzWWllzoSqSy6aUqim8JlDUhmyYgasskoRCjXSx+1GZkHp0Ew2UTuNv0XKGg5+o43PXIVDhvZ8/WmewAMvXaD+jkonjza84BySd0IuX4bQtAxoJAxfL8dG7wFcG1K9ht8HKrqq0NNHgKXWiUGvO+EEpXn0+FnWpH432v7tXycX3sPjErkf29gkDG55Kxl+0K7Q1b7c6f90S76ARP3pycDGVFCD0F/1hbLpVczwm66Iil05f2GDRo66PVwFr8a/2IsjlW61FjLzJBWCX27InmupMPoSf5Du0gXwM0RFgofc6O4AEX5qwuXaiEQufsmilVSm3TI8xIG5iPKcc8e9LRxTT51syHXrJpFpFEzdH6f71qZw0jRg26zVANEV7bl+ckBcDgkoNEuiWXFA3ZglvyICFkql+sqOidD1if6zsbpvcD0NaH45KJ1WoAnBHm5c569ro2TVKY0U+wAqBthJPDuaGBz1TU7NKavzI1QiEQkNjCTjwatuYEMyT7gNSAtTWYGOUv2fBGlvqaA74eS1zvWDXibUdKBrkIjTYe4/qwmhKnXr9gyqJReB0+KCs80r3a49E+QCt88z3XSJZTzZnt7DoVy77AEjGh27n87nQKOnMY8XFI6oKmbeID7KLpjmUC8myZZ32M5YVYz3i2ra6kA4HoRwstaFIlsNEd02aiHvcbf6I93A6GRvcw6nunOTYBtpGHrNYTqRGYFpAx9X7sZO2DCesynOsoZD62tySXwlrj+oNrOzYJ7Nh5Yes88lW
*/