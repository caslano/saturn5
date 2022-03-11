
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