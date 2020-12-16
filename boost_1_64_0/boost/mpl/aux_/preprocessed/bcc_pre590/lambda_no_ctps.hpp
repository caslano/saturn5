
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "lambda_no_ctps.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

namespace aux {

template<
      bool C1 = false, bool C2 = false, bool C3 = false, bool C4 = false
    , bool C5 = false
    >
struct lambda_or
    : true_
{
};

template<>
struct lambda_or< false,false,false,false,false >
    : false_
{
};

template< typename Arity > struct lambda_impl
{
    template< typename T, typename Tag, typename Protect > struct result_
    {
        typedef T type;
        typedef is_placeholder<T> is_le;
    };
};

template<> struct lambda_impl< int_<1> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef typename l1::is_le is_le1;
        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value
            > is_le;

        typedef bind1<
              typename F::rebind
            , typename l1::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<2> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value
            > is_le;

        typedef bind2<
              typename F::rebind
            , typename l1::type, typename l2::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<3> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value
            > is_le;

        typedef bind3<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<4> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value
            > is_le;

        typedef bind4<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

template<> struct lambda_impl< int_<5> >
{
    template< typename F, typename Tag, typename Protect > struct result_
    {
        typedef lambda< typename F::arg1, Tag, false_ > l1;
        typedef lambda< typename F::arg2, Tag, false_ > l2;
        typedef lambda< typename F::arg3, Tag, false_ > l3;
        typedef lambda< typename F::arg4, Tag, false_ > l4;
        typedef lambda< typename F::arg5, Tag, false_ > l5;
        
        typedef typename l1::is_le is_le1;
        typedef typename l2::is_le is_le2;
        typedef typename l3::is_le is_le3;
        typedef typename l4::is_le is_le4;
        typedef typename l5::is_le is_le5;
        

        typedef aux::lambda_or<
              BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le1)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le2)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le3)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le4)::value, BOOST_MPL_AUX_MSVC_VALUE_WKND(is_le5)::value
            > is_le;

        typedef bind5<
              typename F::rebind
            , typename l1::type, typename l2::type, typename l3::type
            , typename l4::type, typename l5::type
            > bind_;

        typedef typename if_<
              is_le
            , if_< Protect, mpl::protect<bind_>, bind_ >
            , identity<F>
            >::type type_;

        typedef typename type_::type type;
    };
};

} // namespace aux

template<
      typename T
    , typename Tag
    , typename Protect
    >
struct lambda
{
    /// Metafunction forwarding confuses MSVC 6.x
    typedef typename aux::template_arity<T>::type arity_;
    typedef typename aux::lambda_impl<arity_>
        ::template result_< T,Tag,Protect > l_;

    typedef typename l_::type type;
    typedef typename l_::is_le is_le;
    BOOST_MPL_AUX_LAMBDA_SUPPORT(3, lambda, (T, Tag, Protect))
};

BOOST_MPL_AUX_NA_SPEC2(1, 3, lambda)

template<
      typename T
    >
struct is_lambda_expression
    : lambda<T>::is_le
{
};

}}


/* lambda_no_ctps.hpp
3AC2Ax+VtC21MdkBfNOcvVbbiGeDfzW2HtUW2DngYcZuK8ob7AKeAXYFW4PnWhW+3nhum+e5kS+Xr7fhuI/P/42PhpGW+jgaRV9vF9jx4H/0/e4Rz0WMZwzjuZjxjKW781TLttXXhvFkMx6nrb5NLOfNlranLZI/vhfelu+Fn2XOH6nNuycttT35FJgJPm3ZtgS3Mp1jmY7TlmAy5e0OSj33cPi0K+Pv0vg7p42/vvxdP+azP3gEbeCdaO5Tm3wDKd8gMBUcbDl8QSXTBjDbmdMG8LPM//OW2uh8gfHuAG+TPXpLbeWibxgb2H+21OYt2opp529Z6ivpbUt9GuwBrwDftdSn2HuUY4iEHs56cPtQep9y7AWlvj+ytB9/LPEa2+hqO/JTljuGJ9oW5vldnutFvC7bwgcY7/fsRz/w/f9D9Nn3o6U2tH+iL0BEVHqBwKc2DQNgDhgEi8137U8J4FPGNqz6lIEuMPrjcHCXzB3BD8Ha4Kcyt6WvtqPBBLAuiGBBZ5j+VB9MBBv4tD81pO+2RmA32d8HR4HHgheBx4O5YFP6cksES3zqg24W2Mxn6sH4oFsBNgdX+dQX3YM+9UH3qE99z8mecUvwdfB0n9rcbg2WgW3Bj8F24Ldge/AHsANY368+6BqCnWgj/hzaiO8Mdga7gFInXcEUv/qmGw2eJ+UKJtO3W3f6dusF3gL2BjeAfcCNYD+Q/YXnkjFP8OgvN9JG/q1gE9rKb0tb+QNpK3+ssZVPG7w+2oxm/AUI5Yz/LsYv/S2D8efQdnBuQPVFHm3+FgXUd0Ix2EFko43a6bT5WxJQnzqX0EbtDHCNZWy5Ml2eCeZZ4fB0L2S6o5nuRUw3jemOZ7rpTDeD6WYy3QlMdyK4FswCqWd5fteMGRF6dhZt+eJ/Rv/MButYZs5ibILODTj0GOPJ86iX+bTpeyXlvgoU3bg4oPprCXiuZWzQmvFtWUD7+3KQ+pXnXtEnPPTr+/SV9gF9MX4IVtoH4e9G8XdO+yDT2V4upQ+imfShdhl9Nl4ODpNyYHzLLZ5BlfpifE5b73MY3zzKAR1oymkh2A5cRF9tV4JjpBzYDheDEscScJmUA3iPpAfeZ9ZPaqt8BbhF5i3gEzJv8dnlU065DqfdGmf5jOU4Mg6Uekmzxy2e/7TtNzt/N7MWfZ6CLS3z40ob30n83SyWg9PG90rW921gS9q+lrTWsJ2upU3nO2lz+y6wt7GBrf1zHTiJtrDzaAN7irGBbftUK2P6fTmuOX2qPcD0N9KG9IO0yb2J7e1htrdH2N4eDZj5orGZnS7zAKb/GDhN5gG01f0kuNJSG9m3ShsAV8s4GtD51DbanH4e3EVb4x+A28G9tDW+n7bGv6at8QO0NX602HQP6LiwE2wEviH9DNwV0PHgz2BnGX8dNppLBznbt9uG71/Yf/dIfOC7rI/3aPP8rwGd35SxXN4Hz6fPv8H0+TdCxmOmtxGhnOl9z/ScvtK2s/1jTDHp7ZBxTfJHPfyqT20e/wnsAe4ER4Kv+bT8XwczzLuharv5zz4t9zd96ivtLZ/6rtoNviH586nt7rd9arP7HfBvkk/wG8mnzzHf5nnB4R7z7Y9o6/hjv/bbffQp9SltH38Gnm2pb59k46/D+GwwPn4GyTMW+pT6ErxBysiv7eMr8F7L+Pwx84Nv6EvqO/BDKUO/zg8O+VXun/xmPWF8/mDMNz5/MMYanz8DpE/TpnuQ9YFy4DlGc77R5KuTKXf61OO48buA5uvwgNqIrk3b90eBp8leP/tn/YDWTwMw2fiG0Hw2Yns4Bkyhj4ix9BGRKXuEoOiBJvQJ2RS8hj4jVtFnxB3GZ4SWRzNwPX0=
*/