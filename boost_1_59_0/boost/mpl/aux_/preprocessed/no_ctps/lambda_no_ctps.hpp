
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