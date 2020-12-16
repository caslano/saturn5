
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
4icNO6HTx+CjYD7jooOafGjPIMelwzvj3Ig9M8DZQX0/Y/2E8ccvgJ88+I6Df2jNRLfHJGN/xv5uJrLVQY96EJx36VeUhH/B/1T6JaYj/1xyE+UkyqX09cRgP+yrgPcWuuvMweeE/aYgazU5kmMX40yhfVssccO4b2OTI1fBHzH3MnRX0DYIzvXg5tm4BkDvEWRKQ54TOf5+BHrMgn/s1Mj5Tmg8LXKUWBuMhg6wefhUM779qwR8mnY3sLHwuBG5V2PnXORZgow/Rs+nMlYtvM0lXt5jnD3YICh4FPlsNnmmHHnR51axVoce1zDun8F7bjUyL6ROI1a95HvKRuwUZ8M/xXo+sbEb2NuMXxhBviZ2W6BdnY5dWuCzAJ1D7+oWZG4HDx5y4HmGG7tUoW9hS7F2zViVk8m/M5AP/Euc5B8/fIt160r81kfsL4JfZFzFOBsZ4zFw5lbBB77eQJmdio+B9wOO/27Ht7H9B8i+HvzrkSu5lLhA312ULCv6obxSB33kiSS+fsN5InrwVqDHKnwmGls5sCUy9uHLfvof5SW3RGEvcujxgs/V5Ckf48H7M2XkKCs2wyfi0/DJWvINMaYg45v4/4N+bAbOw8i/iLJ6Cb6XQb5hzEc43pBHzBSRE8hnEYxlo3SgrzhkWAb+i6uAUbZlERfUfwLegFyXit8K2Og1eJlIOZviBL49Fp3EoDuOF1SRw6hPr8eWSdg5E79j3HPR/a655CJgO+zoGJ1ZMrAHfJwg1hOWI4sTmwnfWIH+sFMn+Gdgh8fx427G/SGxNCDyn1ivSEQXHDczXgC9p2D/+RSXWHtNx0cX44/oeksGMoF/CrgfUldSp1ASgN8/nf6z8aVs7C9+T1FvBfYAxxe58U9orc1iLOrvtKBPeFuPrO8H6I/tzkOuFzm+Bh9uR+anSpCR49RljE3bNGA7nMQZ+W6wEH8Sv8HF7/lq8j84u7FTDPVsYEvzyfGrkGEGtkdOK+UcB75F20dizVjcfypFb/CwKQaa+IWD46exwRpobEcHl4s1u7nw5SLGphLb1A9STmXssfSpQtbGaeSiFHwKW57PcRztx6RjI+pAFHYAdjnlU3Gto46F11TioY62aso2yjzixK5ge+oV4FQAe4qSwnEm5QsXbW5khcar+PHkicgF/MFYYgb4B9TrwV9FmQ78ygDzQEo9/pwAX4/jg0/MRzbxu4H6Wsq6TNpTLQwGH+XwoECD+plKeARWS7GW00wpzUJ26u8BO4Y6l3ompXsWcSN+m1AHOX9W/D5zExPQWLkQXVeBD+9dwJLjyM+L0RVjv1iNr1CXcV5JuQKbbBA2dBBvdvI19cWcn0WJLOd8EjLhMzdRL6Kciu0WImsMOTFALB1NbnaK+VcxOcGN/1NfBp38duhTvi7Ej+mTWYA8yHIexQLtt06AL+r3KZ+h01RxnQDv4VT8x4fOKDdnknPFOil1KzH1a2wejV++Q+72J5IXKQkUOzh7kGlyGdflHHiNQe/FyNWEfNjtJXjspC6m+Di+wYovpxF7k8hVwN4Gz0seUSbDIzJNm4jdI7BnA+OVkyPEPQP46p2HnRPAXcWYjJWJj45ZjZzYtgRYRym+Cd7zlfCInE/T35sBj8g4bzp6AS8deykF+KiXOJsIXi76BjYJfWwlX37sZ85Ae3E98hNHpcnwL36HYtM0H/EUQR5ZjL+kcyzuK9Xgx/B8PrDzgB0DrNGJTOAfiX+UkR8ehZepi/BXdPRGHLoib3ZHkjeRwTmF/MR5G37wOro7Hf6nzMOXyGX9jP3wMuIQ2Am0x9C+FDn+1kb/DOxVTb4GZxftpzJeQyMx5CTHIltPLL5Dn3xoteRj4zL4AL4=
*/