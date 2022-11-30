
// Copyright Aleksey Gurtovoy 2001-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/inherit.hpp" header
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

          typename T1 = empty_base, typename T2 = empty_base
        , typename T3 = empty_base, typename T4 = empty_base
        , typename T5 = empty_base

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
WEdhVYG27LNnEuG6FyH/AQhchIkQ9I7N7sXrLRbWubn3VdqOchEW8302iEV7EydMn/T7NrYNIeSxVp2xtKvpKdxEUXgAhvTtn/5U3fTGcSfz/XqYZfFkybiHkLdzzOjEzFzF6taufTQR2qWNa6AuUpNV+SoPzt1oNJAs6A9K0zq3XXg5WSdayt9ZhOzFcJzaxEpE7NoGTUObUDMIDybzGH7zitRccUSHbKPxjLgNveWBpd3HRJPUIkseW0jDPumm+3Bf4sbMsd52B85Z5dc8KPHf730IUeStL3SJD0i1CQ/62X+E/9XDvMAwN3A3USU0Y1VeiLl/62S6BGNg3vkGDTVQl2c5m1Ib3TRoRdaTtMymeM74OevHNhFcvlLjL7WyAETpX33buKhiZ9k3tpwSgYLwmvWtpUX8BTA5Wh4sPZvYR0SKWRmPJRpi0h0kGm7+xGKe68LfyPLUGDgJlkwn/JUQDKNnZVenYa1UAL5A80r9ByWFpvzO3m0yLxGCarW409KPszH7UHSGQTyDgMZjYKHgJpNVhMKc2Gqj9vIpI/ci2mQkbLgX3DwJGtN+zSchahEw2BZycRxvImYmJxSifiY7q/1jZeHCyvvsgJW2Fj7UKqohtuHMAU1+fqmh1FZI/QpXfv5CCneVNkG2lSexOqq2CNoBiXT4s4uGq17vXcaN5goLpryBXQXWKtmTMB0lRBoIBBCJoJo43TSHrxKOe7cjT8WFwjsEEtUqejbF3PD1cC/dJXNKm8WP/bhj+3dPbUEs8d14wn6AoReeQE3+e2dUy6T6wC8DnJXdCEdnk8Wt2cvoABEBHh5aTAMGrYsYhBTFrdO9Zl/z19UHveGtRsuCFf27cRk9e9qKJcWI8NQV5RExUCvS0h3B5pO9YhkRG5sLolyu0pOdiH5gvtmZFEF5npBP/r93gip9obhl8f3Vxfk32y4/j+GJJDUy0xj6ta4V7+fZLLW/puvroTzHikwoLy1xnfDLioVmO2U2L2YIMPA45v9ibs+Gh04QKxFX0X6Yc9TSoyhE/ILG+c17I8Go7xMJUX0sa2W9CpU3AtNjg4NjqMgCqW+uA8idKKdYGTwuxO7wIBBkMtsnA/JZx4eA7ygODwO6jmQ8j5pwf+TOIHtgwPkM+NvOBK/DX3ho+MplUT/lS9ZGvSGUIw6JNGG+3kSovbrPxKg1rS90eS7OoVdZ8GokCw2kzahJUvvQFcyNfNOdnWa9Rx1Rp9bz1F4L1r2Y9Gef6v/YoyQHlaMfG+PyITVmhdUw32Xcrb6LqHrEU6lVSMTN0JXh4RZpVqAMz5grKAmvx9n9lG2w/z1fJykCeMrTDD559uspcPf52Uj8zhXltW0zB7OlWGTcWWGcq2HO8ybjEW/0/CypqxKjC3fhS4pD2dvSmbSNQ/C6cZAxHMqIW81bnvBOwsOzEa0jmgkVV5BZe1lCguFVFCIV4qwDuiMSBju3CsLMH4rqPhfy+Kb+9OzMtKurfwd4+tOSmr8y9TGBCn7G5SR0G5P9r6Sbeoz//PPSb8UgAnucBhgr1ZXdo+Gbllq0HXl7TmSN0SM35MPdPFP+mc13G771qKuRLwZuXyX5Tza7KuwJ8bOydXZGcUPdsy6iSxPzkqo/MuGWDJ2X5fz2tfU2cNr429MVKj6JUwr58BnhYcRpEySnbmCJ0Xw6TjrQT9IxOVdfzaMod/oPiDsGEVGCNc7Zt9AITFJznLMGt+/ipwD90HFkXPcptQbfWlj/D0kZmeZHcvIf5Ie4l43APXrmGv91EZ3PudnXq1u9o+Is7YXyi9Bd+L7wFuNXkF3vHeIaqsgfEnvcSnFld7XtZWkDP+rPl32zii6LA7DTZ/zbz2QN/HUgNQJtL3NGfHVNDJD6Erhm5hQSCqSOAYvPDZ49Y/kN3pVUsCd9jHoR5R8G+fHCjHSPFntfbM/JHWpS03vweEMandpFsw/+mdzCHn+bXvPr96pxo9xIzgoC8fky3/t45YMZaT/oddfoCGDYM9RNW/EzEMFyJiAdXn1kah1ss6vFoL7aw47r5icUR7hu3y+xQKzqF+hoapCKX6Tc0wqR3RSyb+ir9MeGmV29WyOnSPmzCwjBWf+2v9ZjIBd9UbV+mhEVSXYbUt0uRfg94weJc2qgQmiOU9MJY1OzKh1Qvr29/bMLdH71VlxcdQVExB+AhMAkF0tUCZGSh+bip9ghk3KhEZPJILWAmaLx9l25Wl8lbeRXP5mTuLQ46ekWPr/Fo9ek0qld+bf59EdI3tB+MOG7OPzPrGGTfwTPQ00JuScwiORk/O8fW9cBHNdTCVTN64BfbhHpXtfPn29b1x+BIs9b193127jj6rPWzD8QlrkC47hubi7+dD/b1wUqJ+8h+ZbRCoG6GNJyt1Hx62aXJv4eHgbW508NAunm3n8/HSXyyWMypZL0plhT33zv/UZ5ObXUzK3ORx6KNCdDWoiO8cdr0pEpFChIYpQVMnFZxPbbUwAERDzaTgnj0YFV8rCKnNOi5MlhFY93cux+eWHKHm1q1YC2AzbwjVKxsYjI4hiHt//byGIXE5b/W8W1bTE9VNCC5YGgv/m91irJaWFgZf/ituiRuM7zblacZ/JxN+58kOQwU4gFbOkMvMZjpVh780VrLy7Kv7tsBpFL4HRe/+vpadlBQ4zImfqjWCkrNeZ3Diao7OgsxrlA4Udmfd18OeATeYwzv/y0X6HT/43prwJ4lqefQrtnptslVjvOnlyBKm9/J8n9RcvMS7yGV+tiSSm5sOXf6G+ftlM62ykwiEG8Kj67YrM9z34HJfh7CCmxofBz8C1reWWe6/MLrn5Za0p8mNctvJgpS9r2Fh/VduyINVJXY+s3Ryim7H9GaSQAEnMpurkbbGISyuQxIXOXWELYWf/Io07EG0XwuiOLym8nJwZnUpyZ2rTwPgyjW+8nJd2TGhzXuwWv6Afv5s6RBlmjIyY5kcq9WZZa0/9xM1fRHQ7DlpZAi88IW+Kiegvjz/7OFb5gjttbzpwyFmPBZ3sFaMZdgSS9H2tGWKgfaVnEiEPeIFsaJRye6Dt9ZLgiLkSn31K5SVxhIxykrXxThQRLiMTzBEOAiLQs94n4aGZSLVQAETo/z5rrzGcM84UI8kvHPbqpALUOB5iC2oMNsOPU23WkLV2Z9iYKEq69M/lEJQQMOUjMZORCx8Y3lvj5QNcJs8b8FK7AufZvwvk1YdTR2ouEbbuuceTc2k47INpALSDo2Ho4f2jmiss8QDmRWaWutc2gDDYPvQJFegzq5nzq9nzTKOCmow1JWsoRll4sP7LzJN2ZXUEs8B+yhsnme7WFKdzI1v7hbGqzPVCVPqc3CJ7g5hRVdbek7beSTaR7/qdesaq3ke9ugNPqW9qAxS5kOwKAjZqCIoX0z2jfjPmbPhgAVznRRhlic0vM3HW5KMmGQgyWqynAXIC2DOezgFFXIh0TUdZHZ385CXZYwrw9e6lnVWBNvrTyx+435SL2K535LqydSBtrAgjygDwKGCwzBT6XipxZwBu11+/JlpusHtmZ5WvvACjEyamEeNF90hAvQGIqRYHpllk/5EdwUA4n7emgH3WI8JZEL/xzFM7aK7KCbS0S/DjHKJXseBUCFAxQv/F4bZ0GBgbZxOrGxVLvCgam4W4udWRcDvxw/zGT2JLpeJrtnd4af9YwvXcnf+Ae4ZS3CWFSu9sjgG5RxHH17bheEqTx89NnYEHE2WlsU2RC7cN8klVuXPLYX7bPoIC22E3cZ/80s7vdr2xjgcPxKG81u9N6HHp5ra7AelxRaJ47Pu8vI6TvUXZ6bN7uOfT5tex5Zt3BZ7jHCeI8/R/BGTSBnJ6BDY81mrPTEY7w6n9pEawUlal+8+p39gwzXZGapt8IZi50qcv3q4OKc3Pj7hBv7i9rL6FSH47JoM8XdKnJOKIR0xO07H+v8/WD45MRDM73pkpyWezyymXuRFSm7zP/7E3bw6WJGZugLaLQRndMHbZOE4xRvoqAbb4y70s1BD+UxvPREunWGxl+wqf7Gc05LzpFV69yB2hSOYCPftEWvTUvsmlRUUDDkk7a0yzyDqMtQ5PsKfBGpmV8sngMkPX7ODChTjzUYe9bDGkiUfRDfPgd+HR/QA7tzhj4aEzOmuiONravlUjLkqNM1ZW1bqWS2ePpVKTnAq7h72aqMk8Clcvyy5fQsrfMUamnaY1CU31Hs8RWj07eDul+iGlqpd7HsGNR+/n7T+VZIqHR9Lv737RdCTvqdzvHnFL60/nHnNxi6jf4v4IWb+wI/lEzCKraH/rsr8gHThsm3mz+xNNaSvlVFbTVfaHzpFGDvV4CE40kL93yJhwoldvGvA7lIR3wC/7s5VZM38nfhZVHeIchKf6xeCfUkQBkIK1yksnH4LYbCpI/xBEQUUoVBa46/3reg28//KjJa8NYl1uTsKnLhJDKtiaO4JZJdmE45IK0XcPMQqBM3vR4NzVITS6R26K1nKjBobsNhktMAXcw4qIir7/RceYtqf0l1gjTy0kl764oww7xNyY4/R5ytnT6e4GHoqoDLAWFBTVJzIMYuFsKhLTGWJuOs0Xk4hgCY6XgX+pDyDNfLqvxF9tx3oQUb0zSCjZiimeTx+JLnVNwt1LVdDp4rKqlQpZX0eETVZMonO/8CXdZs35KdTptfYNjmU/3T2r+YXtCSpBMBbgO3J2saZcDUjk+HMQwFv9M/aZ3AlBhqtXsuSpPW3ZCjX0yV/p8zbrXrexqMwaOcU/egHqsdMZUA/dM3b+09s5v+TTKWokHU2xY2lMtz1iLAcBxzzMyk34+FV/bMl+c7JH3/aALrmOr4SSodatNOsQfH4jNpvdGYqBswZSangRn1zPHEGqnEL74MLwhL7eOl7vcVYfGdT8v7lVH+fRNd+GgnZ4Mmj+O5ghO63gh6851dVP0LR9lVxNFpUiVAbkld8WWBvTbBhFq9nJVwLA9wPdbEYNfknYMjbKX/QqVtWM0LSKTqWtRtxB3PJzJGRlJ6r7tV8YdNJ0PWgeJWwjJW91Wpy26pW1M332VP8BLvZyVTjftk404lmhSmn5UMgrPakwphV3XoRhrE+cN/dD2p4OVeoMpqWD8DotwyGiMXrmTIedlJuFBP0DYmzXI9qEXe1NC4d+VFwdFeBf7yan8Em42QIaC3JR58/wxwETz6gyYSMoAACz/0/1X6O5H8rbaVPyKWNIqN0xT9dvXmRHqkLAO9yJMx5C9pgaxN2/dsAVVgV6gX2qsYAQjyXYDfuWGYOyUmezseTig+K1tR47XeKqdr9/QOjnRbPbEyA/JOik6kHNqOLwXmPMk4E6q7HIdWVt5SBws/LDAmKt2euTxSTQhetodUksAsItBtOsADdVvEXkAMprMx6pnAJTG7E2QM8XPOxvq7c87MQ/Mj+Kq1/1EnsdiTz4wA3zJ++//9hkBz+lHVypPIIf0sHPdsXFEIbfI+Zj5DR++8fX211XVj9eKPwj2PyYCGfizO5gv1HDKwnmx6JgsxHxz2TvIc8n0Wax3Dtez8kkW8+EjUo8IELwfejsdbAdCE+CWB1hltx/N06Yzy2psfP8mO3jYUCjkdJhg/WPNlCgtYNXLyStZ0GS0pY5sSxjPGGl+ZxihI00AmNpeRtvLCA9oM5Ka/8LNArOzMX0U5h8qxdVBPDqmrFdh7ayzESxL6/1ILgXKJQ6IOL9q1GzqXYQWrYiI9HoZNGMBh/IXjMZIaFTjd0XBxk+MBwMQGHTUCw8zllKkb/DlwxynERNS9ywhvUsWCxJythbGIpUCBgsV4+KffJu6f79U303xjLJaNNNn0PpECOKlw+wYF5W8kZGYI5t4Y6P2YncX4xb7kYU97vq3Wf1cRPYNEO2C+DmHnS5Qc+ZVRzmIhP7Omp41kU00SnwZ9xbioRUzdd40eyGi//OqGHxx0VzjmxluZmDjr39voYmXgYKQDog7p6ZEL+DN3bk3sITRyOv6W6MtJf6OyC5jJAIQLL+N/CbWX4hQlqGSkQ2xwwBFhZQZ1TYnEA60HXl+kEWFHh+Ti8eDnubf91NCF1ilIRw+mCrcg1wIMbYWUXV3PmTA+ybq3Lzf8IoxqRNuxYPmqCcXMccRfW92IMKickbs1C5aoYwBGxrXvErPTGegH8b8b6dne3mvbzVezNT/nJcU7tZnCCx2fiT1FgcRWS39sOLcBitSqdA89nldC778niMJgVZ/tHJE3BLUMEUj/X4XIvXuRK7OaYRTRzyfz8ApibpJUR5/+7emrKF4BxuPrqpTo5ZporV/8nn0gPHd3DxWeXCNalr/smkRT+pXWETQuVDf7jJ1pWG096hlANHgRDrQf+Zc7b5l7cg1ajUQPwL3HkHJu3f9Lx3J+8zvuHHslmMcez/ff2tu+qK95/ASEtwVQy8KtqKgbK0kCleKgt6h7rnbw76XS1P3BgquwA/vd6Kz1KBCCl/3wxR5+IyMAEGXKGPNaPUm0RttfZeyNShVsUUPdlWKlKJ3HPtfuLUWceExBI415sdFoTUpxCGweex+XlTbjn7PZp/usz2z2puIP+T3w+vk4ROMvIAYhpp6PEMozK6n00lHakf8o3Ywq2NFMdMJWeX7hbVpdrWKyGNVnYntSneyUFVp5dU2eLs7dhaRRKPnj9LVsUnD69p2dqT2Owj0JzJQC2ViLbYyjvzl3HFUaYuaf/2vK+TORNkaNZeD8NaAiahxjsfhLsWzBGTKczSG0QtS2TAlLlz0eoVaMoP+BYu5lN3sJ7eDK/4oTQRCzysuFqTOGbMEj29Obbr2iUA6+9HdhOJF5gtaWkGrl00qoWrccqAL0aVoSYdjVaeBh3bF1WpVZ82gYXRIKi2+6LV7yRHgz5zQNdXC78G45Zw4nx8ZlkCRXk93kHMXc4U5Bj3uPk7BKGLpjYdDNfIDgE4AAsRiusjeSenJKcjnE4HizWWisU/8sRPneiRLFDC+3HRaPG8/dV7o0778PdvCk79ZYZMLDFJRxB9yUxOHMIxnVLXlqPFe1JsgNrU3xIv7gJcgfwevTGAox/qSyatAX6VJsZZJ2z74d+mEPcJgCv+Gd24OFgFCMg0ixKgshUsF8kEhauykcq5pOe0JTcFwBBmA03JTU+JJvqcvuNBoS4zXMk5Yj2ZV32hYbsYP4cdoa4LxUBoh2V2hseELuCVphIqVYIne6Qja+M/IjUKNoK4M9TSGyDY99SkVmDY9NUmHubVVzFR2+/GxZsQr9g1kFPMHpBHdMQb8wZinjM4LX409rx+KRvW2H2ib/XwM1IadSF4Kjok8Ldi2/mKGx0C6sA4sWzak+yAs/Vweb88SuEoFDbM5aflSF6g2nZCBF2XLYHGmMrenKgLhxSWxPIxRnn0AB8n0hiT9bKtrVmVN6wquho+4Jgf1DnlspEqopoyWPlF+JbRFxct+mNf+GDrhEoMg8qimCghHEmqFTci5MMfj9OBVs/md3PrlPEvISDUfFIr8yHdCJM3SXFUp74inQRixEOFmNwh36t1L2oIurSr0WbA2+10UQUwD3uWRHpLmDdo36/Db5KAyq6sJlEvCY9hQOHcqdh7frZ+GNk8/FV4Oz0uKTXJ7h2rp4vn1lrnD3s/73qQU3q5LJm8Gyuzp1jG7KVl/kbhr8OwZlQV3
*/