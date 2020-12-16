
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
DMVojMMYnITjsAKT8AacgDtwIv4ek/E7vArjyGQyJmAKZuIUXINTcTf+Ep/BVOxMfU3HGZiG6TgTs3AWlmE6XodzcB1ejffgXKzDDHwT5+EpnI+dWE8D9sBMDMQspD7ot5BtXvaFJvQibpH66Cr14SX10R2Hoy8uwJ64FP3wFvTH17EvfoMB2IvlBuIoDMK1GIzrMATvwlDcg2F4GAdgAw7ERhyElSyPaxltbUpfGQ+5o4xjbB3DWCdjFB8lpo22tzfV4wxvUT3nv1Y1hm8VUX3NUwxt0nStXaoFLWhBC1rQgha08H8fLn77n2GNL1D7X3kG4MPBtB1WK8+SK8nNZawrZTQ4HcGbvz0Yzd/WKH9bmpdVqORaZk7fS/oxczoFMpQVcs7H3JfwnqovoUr6EqYRuxCnEB/mfQ3fd5Z2tDysnqVKtq0eW0vdVj5jPRdLVD9T4HQL+aeeseXP0FvW9Wr9uF7OeZtc5F0lfQg9iB2I3Ym15F1nz1tZa/Pp97aMVWzN25tpdxfn8NXPHjsjZYiVMkRLGRrsZZAt6cLmb/38V8sY/+Mk/zGSf8QPzvlbtoO83AtbjtFSjt3yof6dQnTDv+Jvmb/m7HKUF0tJrJ9JAFpDxx9ZFuuYreprNE7LNktGTKuudZD97lFl/9qg7F9l+QULTGX0OThs6zkyfdK2/TGtuo6iTKZPWJcbxbT1Ggg3yuv0WYXJ8wzGyr4ymvhYtPnEsLqOVAeIH7+/yL7q8BnVXnb28zGn9WFbteSvjOKeW7LU4HDMaM1+E0RdmrBonrJcQ35Bbp7zQv6v+8OGlSnpNwUfuWP5zJD5Q5IKmr/ceZROLBkLQY7VfBZyD796LIQr5TqQsdgfx+FYTMIJOB6TcQJOQetz3EjjGOy43MuJCbLcRbLcxbJckyy3HCdjhSxvqe0eezmuYg9Znvoe2mvkHtoq7I7Xom395H2xLtYvQN4XiF0wCPtiPwzEYIzE/hiNobax0uQYh+Nkueqx0obKciOkPJHoi1EYhtE4FGPwSozFMTgMpZ9Sjl1sNy76KYczXzccj71xAg7CZFyDk/AD/CVezkJScQBOwxScjktwBm7CNHwaZ+JXOBt/wDnYU+lnxBCci3GYgck4D6/C+Xg1GnARZmEFZuNKXIjurEcRXo+leCeW4aNYji9gBX6IS/GvWCn1Ea+T4xSOlfp2I4ZLfcTJ9jQC++NIHI0Jque3Ncj7O8v71c9v68F8W7CGvr69xEP3d7rkfY315Kl7oJMugJhATCdWEbcTDz2g9UFqQQta0MLPIVz09n+p0XwB/oVo/ytt9g9Vz//LbyfjrRJ9iPuJzyhtxu/MbSUD2RvUzzRb38Zz3kYqJ7t8ge2ct5zDtp3zf5q8yMN4vnP+rP4lvb762zIlvUfdU30+Hr3jlVF9y3sWvJIyuO2//y2/D6U+pZ4znX4fdpPzqt1xIOpxJnrjfPTB1dgLH8PeuB/7YDy67e6k893dqU3X14bt1n5DaEELWtCCFrSgBS1oQQta0EJbw8Vv/2cV5yrnri7Q/f8nVPf/+0v7f5ScQxkp58xrvrOdK1VyL1ms5N+K82/2c4DyzH9ps/sSB5iUNvLfXvEL2B/bf98LsV8Peq36zV7Wc0+Sp5RF53RupquMF+uB3uiJvdALB2J3HIZ6HIk90B2t7d8krb2rBS1oQQta0IIWtKAFLWhBC1r4ieGit/+XlOcacgrLFl+g9v8nqvZ/s7T/P8Eu+CE+q1yzfdrW/l9SnmXOvnyx9RrpVjx72nLts7HcJGnu9jHklMRzjlNnIjIfz98uLzY5jVNXlme5Vrurahy45RHqa6GZjpRrn52ulW6yjkEn081ybXQ=
*/