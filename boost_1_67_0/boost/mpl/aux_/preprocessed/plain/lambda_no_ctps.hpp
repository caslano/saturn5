
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