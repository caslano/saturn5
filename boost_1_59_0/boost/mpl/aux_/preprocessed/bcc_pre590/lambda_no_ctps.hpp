
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