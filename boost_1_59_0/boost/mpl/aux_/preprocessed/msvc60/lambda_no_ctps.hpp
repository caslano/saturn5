
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