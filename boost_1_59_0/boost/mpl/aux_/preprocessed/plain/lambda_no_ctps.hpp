
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