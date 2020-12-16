
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
W2ALbIHtP2n7FeL/MbL77OP/Kevp9SJt8QSl70KZ/sOKespAY5vVHhuwN39rPlH1NyYMWpnASLHssQHTVbEBJzaScV5IE2Q0chkf4iyO2IDjZsxIyS1gjR9HTphhrX9ujHp9e+OxuN7HuBqPTT13Y0r9HQNsPMbY+9jgTPuY2K+f2zUyOqXpjz8cHfplpw9aZnsf6+vocxV/Sz3UIOo+11HSxzEGdoZjYR8YD0fACXA0nAg3wm25Qaa9iHz3dH3z3OjDevIxlxmvKR8p3xo3yfdF9dryh1TfDkuQCo/vghbkWG7gO1hgC2yBLbAFtsAW2AJbYAtsge0/Z/tF1/+3FRMmZT4A52ANAOU9Psv5Hq9aK7AQtoH5cDx5r3vX/h6flJyUEj/GGUc6Jz8js9iXWDXM6YXx5JMxX+bmO+OV5mTmZkBnfJBRnLO4KM21NnMo7MgfstOYvyx5RcB1HEvPs7hiLvwQ6o7HclLm0Ocj3uLgjIhyx2upkfSLTI6YDQPeo6xiizp+j03i/r8hvnkVTuSc1PfVvlFma/se21p8InZ5tVtTTovsSxxe4gpoYzD2kBj9uUgbmZs4GT3lH6jtVAKfzV/iqEPf4yuIvbp52c76U+yTud5SBqmbTJvG97nZ2tg0ofJa/4H49l04lfNiP1TZjLEEO1NU+hB7pGm7dUec8ZH62/ebHHXuey+P3daCa7S2u9uN1Ies3Y9t0k7s+z2OaPc/OmLcjjKayhj4IMoKzXAa55QeVZeVSyzDUc64esqZX60vV14wduZr64nYB65yUW5XnZzwaHeHZZ84LPb9vbLPKgOOePaybw9mIWmOebTV/ewr9uWKDSelrWY5fSn7FlXbTungWLM7RBWPvSAry5opsYKOOtu/RevPTRL3/h1pO29BM+Wr+VTlT0ewMrs/Y+rxZ8Xnxv4ksK/4U9tuDktZnf48JPsUXcrOvvr+I/vcusX/4iuP6zpLdQ2Jr8TXkn+++EX2bQU2nS8lVof4TRvLIuo8ffyGGZQr7pjdb7nZKQnmcdMSE6c6gzhkZOZm2jJ9juEg17nLZwMUn0G1DRvO08fuSOK8VG82cHv1J46E2KCNd9RcX+6ZyvXnRafcdvzW6b6nuMs9Rmwob27s+3JvNtC4CnMyr25I2evyf/cWejuSOa/SYYd1kcsOs7MC+MXw3YZhEsdD7QviiGhs2NhC3wbmkK7amw31xg83skHtf7aW+rg0cznPdFyvUxudpn696rLZWurLloKeYK96uEv7UcdXGsSoOd3SuE5jjXVKdBjfdfpSpyWt9Dakkc5sbINEiPH93nKlD/FhjOONeO9LMo5z4j2eyR32PpqSslmWP1zycc4jjx2b8vDWpcne440Y9/X4H6/G33gv/vZVGceB8RZ/xv84NsZ9c97i+XiPV/O63f/fLfkofILlqgkDZk3q/uLa7aPOXR/fKeVaMsm7j7wTVSOR/PuktMqNMu9jMwyHW2A0vAf2gH+Ao+F9cArcCmfAB2AGfBDeALfBjXA73AEfgo/Ch+E+uAMehI/Ar+Gj8Dv4GPwZVsAmMt8mHD4Jo+FO2Ac+BfvDp+FguBtOgc/AOfBZmAOfg/lwj2vekbzfwDek/Op5R51kXkkX2B5GwQjYFUbDbnAk7A6T4EUwD14Mfwt7wNthT/hH2Be+A/vBT2Es/BL2h0r5BsBoeAnsBgfCUXAQnAsHw2vgELgEXgrvgcPgVjgcPglHwlfhZZByMl9H3o9gLqKUszXMlXKukHpeKfW8Sur5FngRLIMD4Ro4DK6F8fBWOBHeBufC9TAT3g6z4QboiBMi7zryDlTtESfkG9F/CvaB38ERsBZmwL/BLPh3aU/fw5U=
*/