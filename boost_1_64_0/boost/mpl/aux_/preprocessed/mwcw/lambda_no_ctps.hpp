
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
NngC/BGeDKtUj3+Bq+Cv8EH4G9wI/4DPwj/hVkgGlHwKG8MfYRO4u3v+FYyC4XAUbAZHw+YwDUbAfLgXXAJbwGWwJUzdRX0sGzaE75J+li0bwp2+Fv7eviE8pP0tUQ+F16vPZcuZTerV79L7ofB/VN9LykPh9e5/mcO9S5HVyNMPOX0xTnCCE5zgBCc4wQlOcIITnOCE/05oqP5/o/s/BP3/I017AEbIb9gEaST5KhIf4xZLn/C4tLmZmYGsU2xe1/01+e7v19iCW6G733CjSbelA1b6NwTRZ3hoRU2fYWtzn6Gnj3yn+g2r+6Fr+lYD6zt0X7MAG0eRaMwwjnNr+g2N40yOp/Q0+mON4/Tq/kLFO4dj3/7vVJv+wuk2/YXEg21pjADw2PIV55ZHokvXTLTpP5zlHctgrCL/j5hj4fQfNswci1D1Ex5q9BPmdy9aMnd5v4OueqvqjxmFeySHtp/wL/bOBDquKYzjU1qpPaXaiKhoi9KUtE1JKalGaboQbVRQkmjSJmSZpqk2FEWRQxB7UQS1B0FRe+iCtrQoajsn9nIcYjs4x8FvJv+ZvJm+l8ykM0nK/Y7rZ575vnvfMpP5lnvvIJe+m2APrenFP6ylrLXflQ/q48sDddP3jb6HPO8/zLvGo/Z6sOQV91VeMRUeCCcpr5gFh8Bi5RPnKJ94BUyG1yp/eDtMgQ8qb/iK8obvwFT4ufKGm5Q3/AmOgr/DI5UPTIO94GgYD49WfmgMTIFj4STlDSfD42AJHAfLYYbyguPhIuUV71desUF5xZXKK36gvGIjzITfKK8YyzWaDA+EU+DBMAtOhCfBE+FUeBY8GZbBbDgLngLr4KlwLTwNxnDdp8FUeAY8HebAHJgLS2AevACeCavhdHgTLID3whnwYTgTJkcpTxONHM3/KT+z9IoeZj5MlHIy7c3HrH+J9cxeMnkYI0aMGImGRH3+fym7Hc2OzPz/MZba/1HdNt9D794k6hI/8M//T8/IHDd2ck5+GfsUFYey95OvbncxdmaoRnunlr2o/Pt83cH/z58eWGe83mE8ozfajydndll5RUF+VMZ0qMY0bZvNx3Q/76tpGdOkY9pxfe5qYyz3aCzWeMr3DmNptI6lndcmnPH4rk0hv8O91HjyaQ/yvuQP/eMhapSj0Enbex1qLKrTDlr3IXi/N/X9ofp+j/YQfTcE9K1ti8O4L4rrBPWtOnvNC/F8HDfb77375ns/Psx41n/kHw/bKetanFnpMdHm9bDOq1CfGpfq/d3WMSA9Nh9DHWNI/Ng6Bl2TCIyBa8UYAveSq+ux+d7sj+BMu5vH0Pxw6jLkzChts3/ffXkYG6UlNs+nxvKonk/PPIYHPH3p8+55vcb/OnB/tqzt7MfaFDDWkvxIjrPeMs5BikvcpXFO8L8OfNbrNc4his8OVozWzfu1t+D04oK8UnaTY9PO0GK0kZ4bYB/Dc4752e9L1nmxPfsYnlPMb+uJ7YUbw6ua4r2PWRVp1572+36HHfzVO19N//zK8Pd5i2TMb5xLv0n0ty82aJ+FWarlnqMa7rmK5c2DB8BKeDg8F8oevymc7V0oe5fI3qWyd5nsXS57VRZ7Nbb2AmvNa2Xvbtm7R/aWyN69FnuNrdh7SPYekb3HZK9e9h6XvSdkL9elv8mwUPas+0vtJnt7wN1hH8VE4+BhMN6yPs3RMAHmwX4wH+6jfmpoDernQ/WzK1yofvqrn/0tcziGw0FwpGKuoxVzzYVJcIZir2cp5rpAMdclcBh8SLHXR2GKYq2Hwfdgqv966u8wPMLmeh6hcR0F99HcjQHwaJgCx+g6pFvsJX7sbO9Y2cuQvfGyN1H2Jsne8RZ7btk=
*/