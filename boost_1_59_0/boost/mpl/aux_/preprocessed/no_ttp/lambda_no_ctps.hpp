
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