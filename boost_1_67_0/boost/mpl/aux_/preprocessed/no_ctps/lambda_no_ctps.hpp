
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