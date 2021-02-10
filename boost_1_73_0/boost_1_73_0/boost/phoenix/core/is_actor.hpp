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
VYnKjevQo4TjRUvsAuzlSMhMVWvOmGBSWYQkeZmylNTc9qGESZMssDyvdgCoOCXDbFk0eOWn+UWZW8FREzm8AgF2FK5Yp9/8eNeJHpq3ncmQlA6Ea2NToRr8g+cZG1uRYB9LLEfCMc2Lfem+fH3/DTlZyjJoTUZ3Ubs3doqtweC21xl7gBEp9YQboOJ7r5jEzfNr/Gg6DAdRcxJ2HUdvCqtOU9oDB22r7mlcNwyHB2F6qMel5ac59737DsHvxYKdRvY74ahFUMmsTk5jh83RuNNuhk4azzI8GWN7Rn84Gvw7dXit1pvT2HF3cnNDlem7whteZlnO6qk8U/xwOuy0up3WLbHspmAJZ8nTac7nzujjYIye4QjPGueH/TvDnVmng0XOX3pKEnjRbcRYxU+sLI5AgP7k7s77fuV5Qlo8gYWsLpVIa943fEdT4gpvsHOrAt7D5dVhD38RX69AvH5d8+gfr8AAbFat/GEeZcX/GVRDacDtiqeBRL733fsBUEsDBAoAAAAIAC1nSlIpvqLLPQkAAHgdAAAkAAkAY3VybC1tYXN0ZXIvdGVzdHMvc2VydmVyL2Zha2VfbnRsbS5jVVQFAAG2SCRg7VltU9tIEv7uX9GrrQQ5CGzgdq8ukNwSAgl1jkmBqSQFlEpI
*/