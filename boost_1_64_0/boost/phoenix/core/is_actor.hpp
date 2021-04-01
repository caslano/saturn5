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
b7nDcR7ngVj4XtOzZD/20Mth57yOjzYt22rjNIV8a26QWY9vBj3SiEbSABRchlyPU564xorrBV2FH1Fg1XPgd/oqozdyYod3mSs0mSztrVcTug+LaEtZxLfIs/rh8F9Hn7BvY7eG8L7k1OJlqaX0GBHTV4Z+WIQgkrP1q302XDbUzQUCMzJYpIZtE8/OfwvrYloaa+OZxExwGx64/XrdcGODvO4xRpxabc3co8oyOU7lKd/8F6iMIY0B9HBQmWNuStj9flZFZB//SwdbczyXH7Sl6bk33mCEYfFYTSezGS0ydI6NCvVwfRCHgXzlIImNsWsZyITP8b0kx00yWM9OoddIKrMrobFsFKwT3EaXVKVD36O5KpP78pJPQDTNsAZQorZ0rE0jEczYmSJiL3KdpIPDk+PpGEcDmKuyZkWJMpfA4m8rKGR3Xcv4ao0woygU7c04kCOJIBxmJASL/dWJ4eP2Wad0ry+cU+t8kniLM8o2DWecYeYhGVQW725GuljsPaDYBfinHc1cXG1zQqG6yEkBpbMlE5S+djALJxzcyphklkT8NflUz20peg==
*/