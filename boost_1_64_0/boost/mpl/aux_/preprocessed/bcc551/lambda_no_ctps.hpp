
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
DG6G48Nhx6MqzidveS4cf37waaA095Jn1VMdKqrjHG+x9zM45mfefrGZdPE6UsBfkoerBRM+HX8ZfHqsP8W/Glz4c6bpGeQbjkjMoU/9Itkx2nrJmVhPLVYvVithuXczAZ9XT9KK6KqHSC71CdzBmWbF15BbmpVuZViZ1jdPFr1j7Zn0pnkCHfZ93r7B+bgem3mOvZQaqd/uakw9ST1brYBR7g/qPERz0IROkDOMZdoccPA2kpeenmBOzwH7vqgbRqmxvzkCXzxmHoO/tcp81nwVVPUBqvx+/O583MlS8nz3WA1o87fjRLxj/9oe5NjORlZjAHPlYrIO+8f7UwEhvvYSdKpMEj1P0Tf3Dm3UeIV/essazOXO29UTtFuZzXujS9yO3zHG7GEPwzO6QM50NeK593U0+tkU+Eeq29dV3Rh+59Wk2/byDuBpnIDv2x0OcmyslGTau8HvgxcT70mGpLecMU1TNbUQVW6Ovusk92tGpTnPrILPz7BWkHZ4BmXuNetN+0jnBOd0Zyp7YCbu/jycyHvJ+N/HFBjthV5PzrD+hNreA/R/TXwRU/Ne/IYn42tAPhlw+8P9k/2z/CawU9JNHh+cjzI0BPfheLjZtaJyZCYOTGiJk6WOesu8SqKSRfCQpGq4AdyQxFSmngIbbTfLrL1hvreSPT8ADMZ/rPaW7LCr7mEa5sn2bGFEW8FjvWUf/4Dc2Tb6/20oETvJ6FzifIj2enksk4xuNlhOBXErBb1FYzkK1VbVJ+HdPam/pfdm5a8zlsOC36EDruYpD7DnuMvwXpM/Id073buIpNlC732vd8yJTYLp3YGy8gr58+5go4B8azWncfKC84KPBBHdntgu3La39KR09dLkuQXtBm0rDPdo/XL9bv1pkgHbcQlt68fgo59byZT6njieOu7WFPscanG186V7bby/aPm9BRNcjVr+B22M3qGrxvV0N8082azFYduLTvSSnUePXO08DUIwYlvjW30Vn663eNRL0Pda2f2p6BinaT9Edc/QB+OvzNY3ooMfh17xK/Nkqxi/ssl+Xs6E5jiHgNN+BpbeCJLeFxztobI/5razHhmkDfLomE3e894273Py4Iegyf6Mqb4xlhLfF+Xfk9Og7fiqGf4AcOYYlMLL/FXo8kqwV2AH8eBish3JzJMS7kU9xJlwl6H/PAFn/CLMTRwJg70ssSrxBKv4hXDY3sLhbTVOv7gMRewJkgZfqLmoYhcz21ahxW7Hqc7Vj5S5tkp/Qt8OQ7KNOBrNVcYqusl2+JFtxtE2LqOenzDPI1sxHzYyHSV9HG7apeiRr6NWOSj1t3vx2ITYJ6hEBs51A27Vdr85eB8P4y14bG/RlnPV65iuedoYVM7PjHvNcSQm++Hll5CSPduZ7oxmzUbFVsf7w3Em43zvgCceiiY/gwTds+ERaJNvRtnPut6iCcxR90Jvmyqq0k9JO35CH0gz+5kHmqNRBs40zzOrURtXoy59QkdMtwZySuh0/MEm0nQHOxY86DgyOVfC+Oawa6/0DoyNJv8xI3Y3DtQ47uIilNoe4NkiySlHv7O72h8XfTw+ejk9yNbuID/4irbZfAYXPmGfbk92bgSpv0lycieT12Qm3Ok9yk92WJ1z0Tpup9u8wjrtA0OIx0+Jny8nbRviL8XDID0xDOx7LezyMbgIeKo5WrcM+O1R6rHq3loPVIhjwYo99BAN5FBOKK0xAyvmbHZv8SbEKkiF/Rrl+iZ+Xon/I/9mfwj54B8HB4SPh2fL+2Win9cdrfQYbT1P/0uq+EjjJ6hZA1mpx8x2sEs/axCc5lRrkXUzK/U8a/WFZdtxuMid9nZJaN7olMYWiM7bW+a6rR4=
*/