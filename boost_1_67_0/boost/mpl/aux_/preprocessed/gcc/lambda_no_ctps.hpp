
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