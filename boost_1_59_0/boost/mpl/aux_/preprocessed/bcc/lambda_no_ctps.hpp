
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "lambda_no_ctps.hpp" header
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