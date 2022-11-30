
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