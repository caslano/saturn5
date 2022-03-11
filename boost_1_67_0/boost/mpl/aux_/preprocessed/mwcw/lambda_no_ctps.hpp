
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