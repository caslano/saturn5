
#ifndef BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED
#define BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

// Copyright Aleksey Gurtovoy 2002-2004
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/mpl for documentation.

// $Id$
// $Date$
// $Revision$

#include <boost/mpl/not.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/sequence_tag_fwd.hpp>
#include <boost/mpl/identity.hpp>
#include <boost/mpl/void.hpp>
#include <boost/mpl/aux_/has_tag.hpp>
#include <boost/mpl/aux_/has_begin.hpp>
#include <boost/mpl/aux_/na_spec.hpp>
#include <boost/mpl/aux_/lambda_support.hpp>
#include <boost/mpl/aux_/config/eti.hpp>
#include <boost/mpl/aux_/config/msvc.hpp>
#include <boost/mpl/aux_/config/workaround.hpp>
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
#   include <boost/mpl/aux_/msvc_is_class.hpp>
#elif BOOST_WORKAROUND(BOOST_MSVC, == 1300)
#   include <boost/type_traits/is_class.hpp>
#endif

#include <boost/type_traits/is_same.hpp>

namespace boost { namespace mpl {

#if BOOST_WORKAROUND(BOOST_MSVC, <= 1300)

namespace aux {

// agurt, 11/jun/03: 
// MSVC 6.5/7.0 fails if 'has_begin' is instantiated on a class type that has a
// 'begin' member that doesn't name a type; e.g. 'has_begin< std::vector<int> >'
// would fail; requiring 'T' to have _both_ 'tag' and 'begin' members workarounds
// the issue for most real-world cases
template< typename T > struct is_sequence_impl
    : and_<
          identity< aux::has_tag<T> >
        , identity< aux::has_begin<T> >
        >
{
};

} // namespace aux
        
template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : if_<
#if BOOST_WORKAROUND(BOOST_MSVC, < 1300)
          aux::msvc_is_class<T> 
#else
          boost::is_class<T> 
#endif
        , aux::is_sequence_impl<T>
        , bool_<false>
        >::type
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#elif defined(BOOST_MPL_CFG_NO_HAS_XXX)

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : bool_<false>
{
};

#else

template<
      typename BOOST_MPL_AUX_NA_PARAM(T)
    >
struct is_sequence
    : not_< is_same< typename begin<T>::type, void_ > >
{
    BOOST_MPL_AUX_LAMBDA_SUPPORT(1, is_sequence, (T))
};

#endif // BOOST_MSVC

#if defined(BOOST_MPL_CFG_MSVC_60_ETI_BUG)
template<> struct is_sequence<int>
    : bool_<false>
{
};
#endif

BOOST_MPL_AUX_NA_SPEC_NO_ETI(1, is_sequence)

}}

#endif // BOOST_MPL_IS_SEQUENCE_HPP_INCLUDED

/* is_sequence.hpp
S7AveyVp27pqaVW7IcHV4jXl7GaqdlL0DlxV3fD98rrqeslOXi9gpQhcUgBFc/I9dJcYpTXaNWepIrD46/rXC9trUqwmGl5+Se+0s8WwPoTmVQkxTmCOcAB+cTZ/vm4eW9ldKj2kyvFqqT20XRI5mWNyC6rBnWB7E7pc2wkpJsGQoNnRuEA7YUHLL+mfsZyCtu3NzFWQTlgw6JaLQ+osRUgnbEgrcwiQdn3PjaDrbiJGWzXxQgHRHlALkz5NAbNSjbAp1StF4Cj/nfottS4YTl2f0WPikl4jEJMVrVvxTGBFB5LXSTcqRPZtMDiO0vmU/Avtz047Xe6rBsldAjD1sqS0tiVgTj4q7AZxn9AbzckY7zBcR+sqnp39IkW8KCFeLBOZm6yH7cf/mxcPTjceEtN2la8utbb/V8cYhzD3tnzeCzLwhQwVO5OpavlSBrj5xSFUl/bfFkN9mZk1r+nsCByHJjtOo0LkBauigbquDQIWNDmJ53g15b0AtDdg3r1UGwusXhUL1KU6t6Jg+j3pC7RUW4Gss9MS+buMszacpEJeFH7UwpzPA8xxIdfcVfP87Edom/S89NzE8Xmdnq46fdzKBNf4X2ONP6rHf2qx8T/oyYHyHhn/K/T43y8Fy/tk+Oen3+kcfjx9ph5+bFhUzYzEJ6pmjTrPn+UafiVRR439kbwOV7zicY3dHu+50Wmt935H9wl0//NT9HgvVuvNAb87fb5zwGel4wdZ75dUuwYctNbbyyEHve4+33zK4xpyCf8fIsdrxbU8r6X3OEwA3a0tC6Qv51EpqLbnRY7tzyOcujqQy2w9pHcG3dtfo7Bs/03yVuDt38L2F4599j+KbP9odpVM5yFu/6Lja6L/m1e7z58DWlPfViuqzStDDudJYuFGBScNSS6zJPFbyqRC2NP+AUpyobmW0ETPqG1vTcU3rDT7w1bi1q6OrZ72kPgdNU9yJuLEyF7DSrbcqt6Wf/JFlmetrbC6+rVlkIU7yIGxE8vo34GK/D50DMfDcJi8PXqHiga9Sw2jDza5Iz4+oHA8dsMDUzG7+gMeoPLq+E48jqR0Dg4Ow6g/dO4RD1Ft5WN3+aSRfk/bsfD99IeuvVcBql2wvxcRk3J9+Zg4KU5XS62uPVdVxYbAAqRs5140Ieqgy1EfJ4XOjiEolL2XnCKRTdpnm284Wp74Mc4JGnkDGlH2wbug7jou1/pLfARaxkQ4jm7Fi+9dCorzT+XcsFy1T50xhzbvmQEIxubS8OoOvNz8OId9h5qOoaaLT94eHfTp5p7T2iTNmR8/JtflFi+bgqMMswnndfrMwNvjE5RvnujgqvjgCUiSu/ohRQmAJ94rFzBIz2IJgV/psCEKbPPKEwlaWwSxbkwfQOcATZ6ycsS3v8pChE3i8BowvJJWc5tWmjc/YK35ILs6n10dQwOkFzrcLQVEptLWQgqBNikEWrmIk8QIQcErRalUJrruAPyJKJMsuj4aJKzB+tggL5sGiBWCZswaSPxdUxrxdm1e9QK2OXa1R4UbSjQIDZrbK2/YXztb8oxecaox8l/2rgU+yuKI312OcISLOSBglGgiRkEeFRQURBTQVLRGE0p8VXwifp7gM0FAAmKgcoTzCT7qo2pR8W0t1YCgoAiIoBGjRhs1aKxfvERTjRoxQmf++/i+e+Uuwdr2155tuNudnZ2d3Z2dnZ2dfTeM+F9jPo0VoWnqxGb4L9gMU5XVo4uJPBBDA9pGHnk8MFWIAcaqhFdTJcd0Qx/Sx8DGKsFGAghloFtfEgnlm6W+Vj3+v1Zf+7k/Wn8rOyZMf6u262/OmPrbA6kJ9Lfrlkj9bVPzz6q/eeD/QGZoGXbwRJfaAsM=
*/