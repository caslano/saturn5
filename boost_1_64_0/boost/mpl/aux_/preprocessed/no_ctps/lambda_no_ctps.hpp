
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// Preprocessed version of "boost/mpl/aux_/lambda_no_ctps.hpp" header
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
q163wGJ5160L+Qy3lw8VXqAxoavlXbcjxfKOeeyiBJ/Yy5MhmO+1Ts0xgiU8VGMw29RBaPG85fmDmWV2y8Pwy/dQFvNxySDf/eoyHNcow9fU3W57ZRgTHptSkDGpZTvYPI/DeV/jf0Es339azN4Lxr611+r0Sni13snA+VObf5j2Y5NX/70xe1tc5LeU/Laqz7L9+fda5QUZw7ck1saq+DDWwnr4GNbHQGyAEdgQR2IjnIKNcQb64npsih+hP36GzfAcNsdL2AKLk3crLI+tsTm2xf74GIZhAI7BDjgeO+J87ISZGIhbsQvuxa54BrvjL9gDS7Ouj2MF7IU1MAgfwWBsh32xB4bgSOyHCTgAU3EgTsbBuBCH4GYcijsxDI/icPwew/EGRuBtjMJy1LteyRejMRBHYDcchb0xHkdhAsaiAeV+R/nNxW8xjfsdp0sM3gwsh89LDN5MiZGchQE4GwfhCxiHGTgFX1SNSZwr+RTVGJO4koz9XB3dsIaUb4FOfqfAAfmcB86Uz30k5fsYK+Bh9MXPsTl+gf3wSwzFrzAaj2ICfoOp+C1OxOM4G0/ha3haYinPSuzgOdyLOar10lW0v14eqrHM3VRjme92kd8Z8vujPqmZEiMq+80s2W/mYHl8EWvgXKyH87AxvoQtcD4G4MvYFRfgEFyEY3AJPouv4Apciu/iMtyGy/EDXIHn8U28gqvQhTKtxmK4BuviWmyIb2MrXI8BuEnJF7dgFL6PT+EuTMc9OAM/wHn4Ib6Ke3EN7sOP8SPMws/wFH6NP+FR/BO/RyWmMhvr40n0w1PYFn+U/e40huAZjMdzmI45OBUv4Cy8iEvwMq7Ea7gHf8N9eAs/wT/wMP4p2zFHJ7+h5LeVUpbKxnZkmhZL+8zEOrgEH8WlEiu7DHvicgzB13AYrsAR+LrE+q7EBfgGLsVVSNKtxg24RtrpWjyEb+NFfAeLUK53sQRuQE/cKLGum7EBbkdf3IHtcSf2x10Yirst90fLbzI8pHG8uCDrexHL4yWJcb4sMc5XcRNel/3pN9yHN/EA3rLEHsvvMWynMSbwH5LPn5LPX5IPH2BsYMBHsAg2wxLYGkuqx7Cvbn9s/zSJOXlajitjVfexZ8nn+H2V5z72JNlvx2BTTJPvubE4DMehHsfL99sEXIgTcROmy/44CXfhZPwGp+LP+Axex+dQ2Z7TsAxOx3I4A2WMYPmdZCpfLkk9RvDLqrGEg+V9xfJ533AHl5cu7yufz/uWOfi+3fm8r4RprGOH4qiPLXbX3SBVzeT9JK0YoeGZ7g7FVj+IuGpLTHWm+9+6v77fM/f/HvvYZ7VjqjMo61qS7f32ezPd73ts9ZFp9uOrj2e6P/AY66uZ7v+39997LHEvcIx1wyXuBYqz7qbkQcogrScdIeWSSrxCTB8pmJRKmkdaSzpC0i1119UhBZNSlzpju5yTc3JO//3TPzX+n9L5fT/G/zP38d+uJ8/5D4tPUB6pHJkYw7sT4s0x/n+pYvwNLnLeLH0xCTJOXnAR9X3rSgxATBJd/frIlOTwiFjHxgi4S5+4qu/C9l51ufegkPwOkD6UFFTiBrKtykXNybMQPf9GWQraP1+B+YuWfrVoqoUb8JOsx9RTSiZ/MPYLBrubzqFHeFo/p7Sl9MPvlfrfTZrog+6266lshPz7wO42VgALMId6FHidK0vfu9RZWIKxRYVT+9LXp+qXUvf1BUphn5Q+3jicpKzfQ1rrZxkUweG+MUfXk/8pMQOsB+vp4HpIH5m6jVr60ZQy8CFLn5z0bRi39YHipm3dpoJ1H/AxqYvRsq1HkKYo/YIlLP2CloqISFNWIf/9TGItLM+Al/Ww1EU=
*/