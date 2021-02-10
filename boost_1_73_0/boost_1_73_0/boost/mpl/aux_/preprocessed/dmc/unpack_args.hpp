
// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/unpack_args.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template< int size, typename F, typename Args >
struct unpack_args_impl;

template< typename F, typename Args >
struct unpack_args_impl< 0,F,Args >
    : apply0<
          F
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 1,F,Args >
    : apply1<
          F
        , typename at_c< Args,0 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 2,F,Args >
    : apply2<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 3,F,Args >
    : apply3<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 4,F,Args >
    : apply4<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        >
{
};

template< typename F, typename Args >
struct unpack_args_impl< 5,F,Args >
    : apply5<
          F
        , typename at_c< Args,0 >::type, typename at_c< Args,1 >::type
        , typename at_c< Args,2 >::type, typename at_c< Args,3 >::type
        , typename at_c< Args,4 >::type
        >
{
};

}

template<
      typename F
    >
struct unpack_args
{
    template< typename Args > struct apply

        : aux::unpack_args_impl< size<Args>::value,F, Args >

    {
    };
};

BOOST_MPL_AUX_PASS_THROUGH_LAMBDA_SPEC(1, unpack_args)

}}


/* unpack_args.hpp
6x3PzsxGMwW2JlAKumpXTl6ftNs6X4QU5nm+zIYnPj/lwFVDrmPQ6gTRarwF55iR35Cfhqog0J7W9U7ahWEzEqnZjxlexTEufkbwaJgSzDu6xPgOX91GOrMYZzfJzV0imOffeQQPrm3JcuXaBG3tAkUQwUfP+OEpdDWP36JhnKLXTrw0RQpbU7EwSud4pNVekih9qCtqea/UDoUAVmS4E+IUsuyX4E+1DoO1FErmdZDWoUbdmob2QeG24hJvMZANeMgKtRohqK1rGtOKlOknDkSJUpP5IstflslkYFgu3nK1NS2r6/gapw3eyqzjNfncSxUL7+Sr1Q5742hWTB65JOyXiaUJ+JeoxbNQOj4DvRmwfT7esbOuTkHWiadJh/VEMJe4EvyuKoI/4nl6/0/myzI6X6vJ+9Nb9rJ4jeDeWlrL8YW66DckoR/naPLeeesKSeCqd/Ol1uooTJ3+wv9QSwMECgAAAAgALWdKUvQLUcprAgAA7wwAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QzMDRVVAUAAbZIJGDtV2FP2zAQ/W4p/+FWhLShBaeANghpNATbQGO0ohn7NslNLtRqakeOW6i0H7+zQykDDWkf0KSppyjV+Z7vXpz2PTWx2NhcNJiy
*/