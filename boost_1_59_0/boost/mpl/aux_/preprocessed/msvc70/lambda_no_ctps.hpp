
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