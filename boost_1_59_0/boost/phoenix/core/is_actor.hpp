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
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
*/