
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