
// Copyright Aleksey Gurtovoy 2000-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//

// *Preprocessed* version of the main "apply.hpp" header
// -- DO NOT modify by hand!

namespace boost { namespace mpl {

template<
      typename F
    >
struct apply0

    : apply_wrap0<
          typename lambda<F>::type
       
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          1
        , apply0
        , (F )
        )
};

template<
      typename F
    >
struct apply< F,na,na,na,na,na >
    : apply0<F>
{
};

template<
      typename F, typename T1
    >
struct apply1

    : apply_wrap1<
          typename lambda<F>::type
        , T1
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          2
        , apply1
        , (F, T1)
        )
};

template<
      typename F, typename T1
    >
struct apply< F,T1,na,na,na,na >
    : apply1< F,T1 >
{
};

template<
      typename F, typename T1, typename T2
    >
struct apply2

    : apply_wrap2<
          typename lambda<F>::type
        , T1, T2
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          3
        , apply2
        , (F, T1, T2)
        )
};

template<
      typename F, typename T1, typename T2
    >
struct apply< F,T1,T2,na,na,na >
    : apply2< F,T1,T2 >
{
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply3

    : apply_wrap3<
          typename lambda<F>::type
        , T1, T2, T3
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          4
        , apply3
        , (F, T1, T2, T3)
        )
};

template<
      typename F, typename T1, typename T2, typename T3
    >
struct apply< F,T1,T2,T3,na,na >
    : apply3< F,T1,T2,T3 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply4

    : apply_wrap4<
          typename lambda<F>::type
        , T1, T2, T3, T4
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          5
        , apply4
        , (F, T1, T2, T3, T4)
        )
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    >
struct apply< F,T1,T2,T3,T4,na >
    : apply4< F,T1,T2,T3,T4 >
{
};

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply5

    : apply_wrap5<
          typename lambda<F>::type
        , T1, T2, T3, T4, T5
        >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(
          6
        , apply5
        , (F, T1, T2, T3, T4, T5)
        )
};

/// primary template (not a specialization!)

template<
      typename F, typename T1, typename T2, typename T3, typename T4
    , typename T5
    >
struct apply
    : apply5< F,T1,T2,T3,T4,T5 >
{
};

}}


/* apply.hpp
qhin+CPd9S4Od1a5sGcF8DVUUzstvHF4nR/g4JWYXd2pvWLtEJS9+6Akqyh+uH2e5kZ1qpNdsuK0TQyFAnl6yFqdKjnj1x86HAORI2OB/UFZjtSKuCaYkjd2rbIpDLZnQg+OL+/sp7/C2a8DadmrKy6giNbFsDuGOK9HOygfEMPX42hZv4rRl4wZC1A7SBfu6LSUYc8G5SbOkOKEjt1zebEvxCEmFItXOoNOt8ydQKkvKzzwo8VrlPhJpr9Up2eWftcERlwIHnTrIw6Sji0ObFTnPpH6bVQob8tUcs++VZv5ZZ7+fsTIZUzva5vjcQ2vX/gnDnchkDpoK7tKWE3VoovBTvs3QotoIBtq7eGq/LRUY4mZDsvSKbhfgPnqwATNeyBf+YJq1lvMro5GJSWx4gzD3cFjd6ZI/VWCXuu1USyfis0AvBYCDatbgnC1/IxD4jxG9HcVMAjeM1Hlp0Sfq3Tt3AptX32R89j+S9C0zeC5wrXGFBoqv9btUf0pbJwNQFqqZ4KnzGvEBApf4NZ7F8FjZVg3+ORdXwIWOqAJ1NzJMtyOXkYfVeF9IQ==
*/