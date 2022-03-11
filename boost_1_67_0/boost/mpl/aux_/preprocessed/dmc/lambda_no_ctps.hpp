
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