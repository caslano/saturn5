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
BxCnIb5Pq4da0OgzsA56/oVtfTE0Bg7EERJFHUdh7Ew9upbYtaxFXQb2hvqE2sLevy4MOovY+tEhRYH9ofFGGcOwr2IFpWOlQDdLp703CtpZmAXaFnTVjChwVxrspdFIQeYolgIdZzp1nOnMZe5EShg0UHM89aTxNJL61nSeegPGTvOOirbooEnEZKTjf3PPm0Ysx0worYEWpOcAK8lBI/DR1skcHWei7g/URleZDm5CawR7IFimMZIojZVe6Ub84AL+jcB208gnLvXaPHWCW34UjL6R7IOaIuyXpPM4MnawD4YSK0dGD+Z1TKKjr8anciRBZrdUCl6PID48SKI5EibufuPBPEniSKz8/Lrlz1ssluLCojIqCESN48iYwkJHi62sqTTf3mRz5JeWlTblN0222/KLyyY0N010lJa2TITJTiSUv6isoBD/ERLGEZ3Dnb+4AWZ6HEkvqKtulE9F8sQnvqd3lhaUFRSDsaLi5UjVK0HxmMoix1got1H6jREIaKSAVgropIBeChikgEkKhEmBcCkQIQUipUCUFIiWArFSIE4K0O8NkHKOlAQ/GVLQKAguX0GD3yu4W13d+OxAsxRJHwlyeI1FEyVToYkrJ5ZOqpw4aVZ++aRJFfmlFZNK8ssrKovzywoLqyaVTJ5QPKG0knFOLiwqLqqaXJY/acKEkvzS8urS/EnFJWX5pSUV1VUlE8uqistmMc6y
*/