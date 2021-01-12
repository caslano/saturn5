/*==============================================================================
    Copyright (c) 2005-2010 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_IS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_IS_ACTOR_HPP

#include <boost/mpl/bool.hpp>

// Note to Thomas and any future maintainer: please make this as
// lightweight as possible (as it is right now).

namespace boost { namespace phoenix
{
///////////////////////////////////////////////////////////////////////////////
//
//  is_actor<T>
//
//      Tests if T is an actor. Evaluates to mpl::true_ or mpl::false_
//
///////////////////////////////////////////////////////////////////////////////

    template <typename Expr>
    struct actor;

    template <typename T, typename Enable = void>
    struct is_actor
        : mpl::false_
    {};

    template <typename T>
    struct is_actor<T const>
        : is_actor<T>
    {};

    template <typename T>
    struct is_actor<T &>
        : is_actor<T>
    {};

    template <typename Expr>
    struct is_actor<actor<Expr> >
        : mpl::true_
    {};
}}

#endif

/* is_actor.hpp
TuziHpgw8FN09Bw5CjXnQPx2Ez2O8MFe6VfjI8zfk+R2D+JzPlLEY3DtJ5DJCzzXqFAWaynPeIQ8SxHYwrzmNMB2kU3NhXDUBsyfAw5LO4Mi4LzNFC339SI5wnJvksvHLlLQb1/whP2M2lnBA1+WxTjm4ngf1giisY+G9MUMx9rNGFkL6Iv8ciORMbrXYSY+sTz8Ag57h3XfamDOvTP47iHMM+sHmcxZyBvww2ZwbjhBLerb
*/