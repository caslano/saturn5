
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