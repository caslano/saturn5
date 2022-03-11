
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