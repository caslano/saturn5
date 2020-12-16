
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/greater_equal.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct greater_equal_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< greater_equal_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< greater_equal_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct greater_equal_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct greater_equal_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct greater_equal_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct greater_equal

    : greater_equal_impl<
          typename greater_equal_tag<N1>::type
        , typename greater_equal_tag<N2>::type
        >::template apply< N1,N2 >::type
{
};

BOOST_MPL_AUX_NA_SPEC2(2, 2, greater_equal)

}}

namespace boost { namespace mpl {

template<>
struct greater_equal_impl< integral_c_tag,integral_c_tag >
{
    template< typename N1, typename N2 > struct apply

        : bool_< ( BOOST_MPL_AUX_VALUE_WKND(N1)::value >= BOOST_MPL_AUX_VALUE_WKND(N2)::value ) >
    {
    };
};

}}

/* greater_equal.hpp
HYfgHTgCV2Aa3oUZeA/OxntxDq50ty+V+2O82qCd3XhNu9+WOAnb4WTsh1fjKJyCSTgVJ2Cytl3gAmnPbtB+bb7U/wKshwvxYrwOO+MN2BULtO11Jb5og/hukvgWYxjeLPlfgo1wKTbHZe72eXLfiq0M2uflVyY+nINNcC5G4zx01Z/NXT7f+suR/ORKfmySnzysj3aMRgd2QM9cK574Y84S/3SJP1XiT5P40yX+GRJ/hsQ/U+Kf5f58yP0lNDH4fCyQ8i/ERngdOue8kPtCXC/baee8uE3ycTtG4t3YHu/FLrgSB+B9OAlX4Wx8APNxDS7HtbgK1+NqLJR87w6R+zy5/yN94uY7VIjMPyzt9zfI/t6IbfFx7IRbsAduxX74BA7EIhyJT+JE3IE23Cn5ehrvxN24Ep/BrbgHn8Tn8CV8Ht/HF/BjfEny/TKewb0yx8ErGIX7sCm+hq3xDbwM9+N4PICT8S1MxxLMwoN4I76N9+Ah3ISHcSe+g8/gu1iM7+E/sBSP4z/xBH6A3+ER/B6PYiXO08ewOn6K9fA4NsWvsC2exE74LXbH73EQluOd+AOuwh9xPf4LH8Wf8XH8Bbfjr7gH/42v4+/4IVoqUV9YCX/DyhjOAVkVo/AibI/VsAuG4UCsjklYA5MxHGdjTZyLtfBajMC7sC7eh5G4BqPwKayPf8cGeBgb4hfYCL/BxliVY64pVsfmWBtbYCRGY2NsiS2xFcZia5yCbXA6tsVZeDHOxnY4F9vjrdgB12JH3ISdsBg74yvYFd/AGDyM3fAL7I6V+L7QA8MxFqOwJ/bBXjgYe2MC9sErsR/m4qW4FONwOfbHu3EArsJ4LMaB+DoOwkM4GL/GIViGl2M9TtTDsDsOx944Eq/ABEzDUTgXR+N1OAZX4li8H8fhA5iE63E8Po1X4Vs4AQ/iJCzFq/FDnIJf4jX4O07FMM4b0zAKU7AjTsdumIp9MQ0T0YqpmI45OAOvwwxcijPxdpyFGzALX8BsfAdz8T20aefCk/NuuMF5t0DOuzdidVyE0s9Cng9QZwb9LGbJdlkYjtnYA3NxJNpQ2r/LfT73qgbt3/vIXFX9sD1eiukYhxnYHxfjALwF4/FuHIj34yB3fuVeHocb5Leb5Lc79sEeOBhj8XLsKfFEE0oknkYSj3bOjTx53wpCmbxvsbxPO/fhBCnXRKyPk7EFXo39cAoOxWtwLE7FyZiMU3AaTsVUnIFpmIlWdGA6XoczsAAzJF/LLHLvjNskX7VwoeRrqOTrcsnXcMnXCMnPSJyGV0h6CbgYR0n9j5H6T8R7cSyuxytxE47DzZgk+SmoIvfPcl+t5Ceb/zvkt4RV8v32AWyFazEG12FvLMQR+De8Bh/C6fgo3ogb8FbciPfgJtyNj+EhfByP4Gb8Cbfgv/AJbEpetmFLLMJOuB174pM4GXdgKu7ELNyFS/EpvBufxnW4GzfiM/gY7sHN+By+ic9jCb6AH2AxHscXkfnZLC9hBL6MLXEv9sNXcCD+A0fiq5iI+3ASvobJ+Dpm4BuYg/txLh7ABfgmrsK3cAeW4HN4EPfjO3gI38Vj+B6exFL8Af+JyonjfQzDIxiBH2F9/Bhb4FFsi8ewG36CY/BTnIzHcRF+hsvwc7wDv8D78QSuxS9xA36FW/BrfB1P4jv4LX6Ep/A4luFX+B2W4Wk8g9+j8tCoHKPwR2yOlSuzn7EKXoohOBir4hV4EY7FapiJoZiD1fFWrIH3YDhuxppYhLVxL0bgEayDx7Aefo2RGMHnoDE2xybYBlthJ2yNXbANjsW2eBVejKnYDhdge1yCl+Aa7IAPYyfchp1xO3bBTs7+MRX2jYk9HWZJIjg=
*/