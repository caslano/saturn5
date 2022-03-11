
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