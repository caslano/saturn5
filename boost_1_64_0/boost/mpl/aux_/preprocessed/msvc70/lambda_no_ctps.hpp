
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
wlFwChwNr4FjYT4cB21wArwBpsF74BVwJ0yHlTAD7oGTRK80i3yLAlNFLzW2+2rRa4bolS32y4EJMBeOgFY4Cc6UfA8jNsmXb0rk67yv9rme15LvbBgF50j7FEr+RfACWAz7QxscC+fCCbAEzoKlsACWwRI4D66E8+GtcAHcCBfCx+Ei+Awsh6/DxWKPJfAIvA7+GS6D38IboFaJ5bAevBG6n7t9zftBO+kHMdIP2ku6gSSolnSbxC5amt515L1X7PKi2GWL2GUrjIO/FvtsgwPgdjgE7oBT4ctwOnxF+sGrcAXcBR+ElVL/38DN8DX4DnwdHoS74RdwD6yGb8Cf4Jtih70wGr4F28Lfwm7wbdgP7oOD4H6YBn8HJ8J34FR4AGbDd+Es+B5cDA/ClfB9eDf8AD4MD8GN8LDYb69FvjPBk2L31nCn2P17eZ78A0bBf8K28AfYCdaV/lQPDoZhMAnWh1fBBnAGjIDZsCHMg43gEngeXA4bw3WwCXwONoUVsBncD5uLXVvAD2AUPAFbwa9hayj70Mg3JsqQcULdh+ZJde92ua6Vn+tsSn6VPtedX9dz3VJXfn6u2+DnuopzvMd73nvh//Pxl7+EfS1+6fu8+4vL3PReuN/YzNra36I29noPJE4z0L0tlr4f2uPdcI/3L7ABshTZhBxEfkTiT4RbMpAVyBbkCGL5kvNIGmJHNiD7kB+RLl+FW1IRG7IWqUSOIpFfc08hBchaZDdyAomuDrckIwXIemQfYvlbuKU3koGUIxuQSqQKsXxD2UgqUoCsR/Yi1Uj0yVAcaegIHaEjdISO0BE6QkfoCP44V/H/JSVnHv/fgfXJ72WOUl5/7Tudc5lee0mmNk1Em2Dk+P+1/P9x7/8vsWaVMt/U4lg/YKmyf0CGfK8bgYi/yzK0Fd9enOsHpEycmFlQnJWb6coJZUoDmUMp80VYey/4+RnG80vM520Yz5Mwn29hPI8h+HkGxvMJgp+fYTyvxWweg/l8lIsd8yqGrOm56b3ht79fvi4xuuGKnqbzS8zn3zj3J5Y+IH0jr473/sQTxc8yCXaAV8I+cDIcAq+CSXAa3MSFe38Itxz/IfyMv53p1ywz/l7WeILRd7Iav5Ep38Vq55uY+j1MXYtM/Qamfv9KvUL95mX8vWsv4vWdK8B1xvTftby/acWvCGxNMeXbVY3frYas9P5etQaJUb5NyXphnu9Rp7FOmP77k9H6YLrvTfKtyfc705mtBebvO1KF11pfZ/7NqObvRfp1vfTfhry/C2nfhCJ+DH1PCR2hI3SEjtAROkLH/8dxjv7+zymopf3/rlf+fo+vo499uU+LGWtnFu+akJkfwNp/rtil8UwKKkWDAqv3mieRsj7eRokL2wDvp9wD7XxjHAlRys/Nty/0H2vnKvNCSrDn5ZeW2XJdcWCcc26M5jqH8pBzpdYcIOsLQIQ9izjrs3+Y1e7Zc4rf9kyipyTdCfe5ouL5UK1nhdRzEdIEmY88QD2r2hvG5GFc/3vkaXFiYzr4xhTq4/MGxjhiBN31iOR3cZHVe60XWXPvbtHvTuQh9FvawSRmMMdaYrf4j8/01cnVDtMoVbJw63WQa0rzZ3npdUT0soleBcjD6JXYUa+XY+8zx4aSga/doItl1PpHoUend2nQWT6xjEck42Tps4nwUa3PGuhEfYoC2etOa8vvYn3b0thuWp5W7Rrpv1dwbo51obvvTqZ9c2eVeq2NUSH2LpVzXKKslyH1Vff/kz6ulbfAJ4Z3tPx511HGivZIFvW3dVLrX2pzRMMHsf6CxCF7lRUp6+Stlva/A3mMsjb4ljUzvyg3IDt7l6XeI/m5+nUBgPt+b6+MYb4=
*/