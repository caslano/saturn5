
#ifndef BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED
#define BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2003-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/multiset/aux_/tag.hpp>
#include <boost/mpl/count_fwd.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/aux_/type_wrapper.hpp>
#include <boost/mpl/aux_/static_cast.hpp>
#include <boost/mpl/aux_/config/static_constant.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)
#   include <boost/mpl/if.hpp>
#   include <boost/type_traits/is_reference.hpp>
#endif

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {
template< typename S, typename U >
struct multiset_count_impl
    : int_< sizeof(S::key_count(BOOST_MPL_AUX_STATIC_CAST(U*,0))) - 1 >
{
};

template< typename S, typename U >
struct multiset_count_ref_impl
{
    typedef U (* u_)();
    typedef int_< sizeof(S::ref_key_count(BOOST_MPL_AUX_STATIC_CAST(u_,0))) - 1 > type_;
    BOOST_STATIC_CONSTANT(int, value = type_::value);
    typedef type_ type;
};
}

template<>
struct count_impl< aux::multiset_tag >
{
    template< typename Set, typename Key > struct apply
        : if_< 
              is_reference<Key>
            , aux::multiset_count_ref_impl<Set,Key>
            , aux::multiset_count_impl<Set,Key>
            >::type
    {
    };
};

#else

template<>
struct count_impl< aux::multiset_tag >
{
    template< typename Set, typename Key > struct apply
    {
        enum { msvc71_wknd_ = sizeof(Set::key_count(BOOST_MPL_AUX_STATIC_CAST(aux::type_wrapper<Key>*,0))) - 1 };
        typedef int_< msvc71_wknd_ > type;
        BOOST_STATIC_CONSTANT(int, value = msvc71_wknd_);
    };
};

#endif // BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

}}

#endif // BOOST_MPL_MULTISET_AUX_COUNT_IMPL_HPP_INCLUDED

/* count_impl.hpp
95XnyJ0l35prleOxS+q8ueJF1b4rsba/LOezJp5Jkz8/WVkjkos8qypUrqXm/OWo8+f4c16D/b4bYs3nlZtsg7p/c4PzWW+FP+v95lFlfOf27bdvuTYtxrNP/85VU9uu+O89A/7e+Az4WHTwuLdXjTr57P1PvNgvwnd0xT0Dtv+u0/WfDcfp5L4Ow+S+qQZGyYE9VdoRm4YeOB1vxzRsiunYCjOwPWZiIM7APpiFF3EJabmsZ7espw7OkfVESr/Jo7AGjsY6OEbWNx47YzRG4EScjDGYgpPxbpyCD2AsPozxmI8JuBMTUfpFl/szli35UfeL3l+2eyC2xEHYDgdjGA7BgTgUI3EYjsHhsvxQF7knk3s1Zfl6/g5ykbba5dl3e2yC/tgSO2B7DMBADMQQ7IL9MAgHYTCOw24YgyGYgd1xFvbAe7AnLsVe+CD2xiexD27BfvgchuHb2B8PYTgex4H4DQ7GIhyCFzACr+FQ9JJ3NRriCGyGI9EPR2FHHI1dcAz2wigcgWNxIo7DWByP0zEa78EJuAQn4aMYg0/gZNyIU7AAY/FtjMNDmIAfYhJeQT3+iclYSd7pqIsp6Imp2BCnYWucjn0wHftjJg5BA07BGZiIWajHbMzEXJyJM3E+5uFDOBvz8Q7cgnfiNpyD+3AuHsa78BTOw3M4n/9/xAVYmWPnHqyPC9EHF2EzXIzBeC92wyXYHR/AUbgUJ+IyjMMHMQEfwiRcgdPwn5iLK3EZPowr8FFcj6twHz6Gp/BxPIOr8UdcgxdxLV7BJ1D5sbMOfTAfm+EGbItPYl/ciENxEw7HzeZ4xUpyDyz3xsp51JW/96AynJF4xbPoiedxMF7AZLyI6XgZs/EK3oG/43y8iovxGi7DP3AN/okbsKrSLibehruwGr6F1fE9rIlfYC08hbWReXR1sBPWxeHohlFYD8dhA5yBDXEeNsLF6INLsDEux6a4CpvhemyOW7El7sFW+Da2xmPYBi+jH/6ObVF5F6odVkF/9MCO2AYDMAA7Y3cMxDDsgsMwGMdiN5yEIZiI3XE69kAD9sJl2BvXYh98GvviVgxF9gX7X+7lcatcd91xpVx3D8r+fA898X30wQ+wJxbiQPwQh+NHOBI/wbH4KcbgZzgFP8dc/ALvxC/xHjyGS/AEbsKv8Ck8iRdxm07ur5GyJp+mOIiNks/n5Pr9PDbG7eiPL+IA3IET8CWMxZ2y/l14N+7G+/BfmI+v4Gbcg3vwVTyGr+HXuBcv4xt4Dd9ED3nXsT7ut7QDLPfXuFbKV90OsJeU7+1Srg3RF32wKzbGMGyCg9BXyrcZpmBzXIAt8EFshY9ga3wM26jqgIslH40kH+o64KelDvgZvL2c/fkrdcANIuirHUNQXRcczWfT+3J/XZ1wHuvYhqXfgyt/3fDh4uvVD5MiapWrjrikuGLrif0u3Hxd8WDm3R1R629XZ9yguquuFymGNIe0hrSHdIx0leRTw1mX7Bycg3NwDs7BOTgH5+Acyjfcivr/9ARe+66g+P8Lqvr/FHm20orkQmpB+qg3v0G9LfXZpnWzlNjETMNsneN1I097aftxp/6LOrXSdf/avk+TM7PStX2fpsdnTwdNOwBH5dlqsdSNI7+30F6+M5SMl7d+3NT392Eflobmz7t9rH2BFzcy9+cdFKCTcScs47p0N497zzouxDzuNeu4buZxXreX7lv8rQal+xFfYR3Hek31npMt40L+svKXNuuQcakZSp2btFkn4+LzLPVw21R919fn85fSF6gSgGFssE4ndeWq+rr6qvp49lysug28wzI+Q+ndUsYdtO0LVuIK4joa57f0Hb7fOp2ycZZ6ad7RoJ9tY/g=
*/