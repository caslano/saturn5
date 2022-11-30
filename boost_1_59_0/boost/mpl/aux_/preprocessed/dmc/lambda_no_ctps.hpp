
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
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
*/