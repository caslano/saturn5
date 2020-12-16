
// Copyright Aleksey Gurtovoy 2000-2004
// Copyright Jaap Suter 2003
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "shift_right.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename Tag1
    , typename Tag2
    >
struct shift_right_impl
    : if_c<
          ( BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag1)
              > BOOST_MPL_AUX_NESTED_VALUE_WKND(int, Tag2)
            )

        , aux::cast2nd_impl< shift_right_impl< Tag1,Tag1 >,Tag1, Tag2 >
        , aux::cast1st_impl< shift_right_impl< Tag2,Tag2 >,Tag1, Tag2 >
        >::type
{
};

/// for Digital Mars C++/compilers with no CTPS/TTP support
template<> struct shift_right_impl< na,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< na,Tag >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename Tag > struct shift_right_impl< Tag,na >
{
    template< typename U1, typename U2 > struct apply
    {
        typedef apply type;
        BOOST_STATIC_CONSTANT(int, value  = 0);
    };
};

template< typename T > struct shift_right_tag
{
    typedef typename T::tag type;
};

template<
      typename BOOST_MPL_AUX_NA_PARAM(N1)
    , typename BOOST_MPL_AUX_NA_PARAM(N2)
    >
struct shift_right

    : shift_right_impl<
          typename shift_right_tag<N1>::type
        , typename shift_right_tag<N2>::type
        >::template apply< N1,N2 >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(2, shift_right, (N1, N2))

};

BOOST_MPL_AUX_NA_SPEC2(2, 2, shift_right)

}}

namespace boost { namespace mpl {
template<>
struct shift_right_impl< integral_c_tag,integral_c_tag >
{
    template< typename N, typename S > struct apply

        : integral_c<
              typename N::value_type
            , ( BOOST_MPL_AUX_VALUE_WKND(N)::value
                  >> BOOST_MPL_AUX_VALUE_WKND(S)::value
                )
            >
    {
    };
};

}}

/* shift_right.hpp
hNUElx/R9t3ehrNDYzIy/+XchtX3BcmK1UdmaPj4TWlbhrbfelPZ+4NkNsA3ptVWKls23G3gn5SdElI2EclcWW5P5DTJSIqiDU0/5FuKEUa5SM1RIb65xos9+0Rn4OYuW2yrz4dsuM/he/nZdt1Ltwq97gmd+fwBj+6+QbXB13+Ug6/U+q2cr3/afJvMBveDtMHhfaXStw7tB02ob7m9vg3qDz6fgrGaVO6o/tAOJiKjyivDPCONC0lBHv0hszinID+qvrBl22UL+L72hlH72mz5WznY8q+12vKrX3BPmjiP+cUWe3/tYU0bJrbNoo3SKHy++buRGbQ/dmG21wfKOj592izUP2wr6pxS4fcPCxrrI7epv/93jt43zHe/u5uH6tOcctIC+gR0ieL6+nTZOgZd1DZ09FBdWpl7LFQXjd/R69MiBn1898AsB33aUE5FQB/dBw1ro9Yx6LS3by97xdc7Sus4w0g/mLhz3mcCw58rc1IUazYdpUMxibfXwgzdX777o07xTPlfvz7fGf2KvXmS5VOXPT2jcIrl/tAYbLvP10rnB6TzvaS2ndHZ245TzBBdFLjRzWlE/cPd1250MoVY15cu8sbULEqw3Nvm/p+ST86g94fiVqG+ku3NmPSgz1ey4ffnKR0ix02rc5DfAfl1fvkN62uzo4gZ524dKruTGZse8slu+P1Hv6jHR1TvOyHySWYs8svfsPttVD3t31t9tVox+75UX/2M9Bv5yu6VDoWe327+OKGtolgXtfqWtbP4o7pVku/+yuMf9NH9JT+4/Kzs/GIHfzM9s0yfMsUkOD+3LGOHAkJxHKDn7f7Q1K36Dn/dcrLckeOfRqyXp5To62V0NteGr3nvBembqqs6T9diLml78zzw9gd3IVV0ZeHA66lsZF8/9QOfPuoH9vfGpCD9zHN+Bu12EH84ls+XG9nQ57eXgd75xmtPbW3tSzXS/0Lpfx6pK/qnP2zR3wxMMcScle7+9raMbQ76h7zj2tp3Pv+a4y3p9zppR/RLesSin0wKorEDCKejUcobBlk6au/AQs0tOPWLdpb+PjmnsAj665KCju5J9mfMCqOAKV/7j20Du5mx61Gvf2q2t6fglWwqZZSJpr9s2bb546Hvki2M/Cx32D0G9Y4ofT2/Oah/nvc9U8+jyZybvlWB9pUIW2vGaKOr6lkbeIf03/vm90x+nnxN9QzLCjzDyDeg7TCV8UmHBFtfrECm5xrq3t8OdjfPNeqn9tGVjq5dnqvke0H7L96DTDelUITteSx34OB349D3btXbNOIk2YgEX3O1BXWnjKJptj6QkuzsE91r4cb1iT5E8uYnh/pE/8BJmpM83OEjx3O2y6SONn/469qH94fv0cHZP9v9N3vnAhdVlcdxEl/ZCwUVHxmV2/bQRPOVtYrPfEuoaaUBCgqJMAGaqbVYbmpZkpqRjzSzzcqK0t3Q1KistKyorKysqMysbKPNXa0093tnfjNz78wdZgbNdlvm8zl9u3Lu+f/P85577vn/z/rjY59d2NDnXVXrV4Vu+ZZXRbk7CKEsTHmkIPzr9yH+bYWNjHDr90EbfwdzG/mX6TlGn7GRV5X6nezj72BJJfV7cmN/Xc5Fl3JbXXB3UAU9VL/MFf39Hcy1kf+wUT4b/OWH274eDMHfwaHG/nV/AGXiPPItLu2p/dDld4rxr/vZsf75/ZGLBHt5qv3QfTzwDLDUfXRM4Lqv28Rfl/PRLyWALtR+2HqYzxSh7q39wEb+z1wU2MnX6BJO3+sUE3x8iWjqX/8XGutRHh1G8nHFqQB7GIclXRmmv5NWsd420EMyC5v65zve6P+BZFbB58kcn3Zws9XniaUMYpo=
*/