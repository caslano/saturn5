/*=============================================================================
    Copyright (c) 2001-2007 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef BOOST_PHOENIX_CORE_AS_ACTOR_HPP
#define BOOST_PHOENIX_CORE_AS_ACTOR_HPP

#include <boost/phoenix/core/actor.hpp>
#include <boost/fusion/support/void.hpp>

namespace boost { namespace phoenix
{
    template <typename T, typename U = typename is_actor<T>::type >
    struct as_actor
    {
        typedef T type;

        static type const &
        convert(T const & t)
        {
            return t;
        }
    };
}}

#endif

/* as_actor.hpp
KtoFt4hgvBhEO9T6WvuchqBDsAHWLDGpZj2qNYM4SPTDChaAVeBg+QIZQilW1eFx0fm0xKSaBLHFUj/iGzroJAY5GmAVa2+jbnS2q9vTpswzGVrvZstoqCB/GzQAACh0vsPdKgZx34jtaoBCNCRtLVDcC0NypyOAJK/s692M0MciVJzSSV4CVPD62mwu0qx08Pm2JoeL7WqwoIf2IBaGVSA0FxZWpWl0rBKJ4mJKIYBCdDtAal/YgwU3bqOBq3URKIgXzQVNrpG2dls3THwW2NwQN4iFdEGzy4UdcXFNAyyQXaRTDgGRBeiQBY3EKwCRGU1CaduBKYhXIuDuixSWFlRsR09cUokIncUtsIEZSbnLJdgrBdwDrHW0k1leh0PBoJnhfJEsojVGgyhWpAlSUDUDpLjoPWiYmY0ETchZ/ahw6urAGbcggp5MCuOyVR7Ga21uUiEIMGC76dwO5uXgZomddoJGAXWD6RLMctUEtulCg9jMoMmAP5LWyBXCqhq74CZOBHSBu6oBJ/OA4bxOXEUi2hCI4jwAe5vIqUJnCS5YOeBM0y+m6zuyuUs0MajHBi/Wve1+cPIBg5rU/ma7hCbcxAkgLnK0iDsepAYWM1KYNR0ZVTVQ1YonNIO05OkrOW1jqkhcZqhQaResvokOI+oINUbXgH6b179A8FF/RrAxBFJk71Np88il6nv51x+XahUosbG9Jeb6JVpl
*/