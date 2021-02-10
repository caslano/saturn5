/*
 [auto_generated]
 boost/numeric/odeint/algebra/operations_dispatcher.hpp

 [begin_description]
 Operations dispatcher to automatically chose suitable operations.
 [end_description]

 Copyright 2013 Karsten Ahnert
 Copyright 2013 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_ALGEBRA_OPERATIONS_DISPATCHER_HPP_INCLUDED

#include <boost/numeric/odeint/algebra/default_operations.hpp>

namespace boost {
namespace numeric {
namespace odeint {
    
template< class StateType , class Enabler = void >
struct operations_dispatcher_sfinae
{
    typedef default_operations operations_type;
};

template< class StateType >
struct operations_dispatcher : operations_dispatcher_sfinae< StateType > {};

// no further specializations required

}
}
}

#endif

/* operations_dispatcher.hpp
+jcMMhYwfmN4rPxMgYiQHJmHXCpkmCsu0iOUzUCxLJHEg8T7sRTg3/g89ucoyFewVGolf+t0gjyLUetOKALZCQrjj5YqiY+sJdeoROLfg1gpUAJyyVwgTBcSEfKInixbIHCVz2Mul26lDYpKw47IQLI4Jl5Ix5k0ajOYWve4hAYr1JgrekiRShJ1uxRJAxH9SFyiPEtREPoBkUKBbnYhT0OWaWRteSHC+lQ7+GhbaCp9QxApKgM7/SkMpzsw9yWXLnwYzs4nVzP40L+87I9n1zA5hf74mpi9G47fusA4CsuA3a0yJlF4BjxZxZyFVuaP+3RaP/E0iPOQwY5iEkO101oDYRbEBK6gaGgao2JNaMKSkM3zhWERsoinDGaD6cw774/PvNnw/YCM/rWLZh53u90S533/v97V5WiKhdEEvhlNTt6NhtMZnrRaUvmKB5jiCjDLFE/Yx4Lyc684DZZ+Bvt4TiFIFxswTvAn7C8xRdCErRwkV8ybxyL4gjmoPja0eYDLshuWPY5Nmqd54lnZDXhJ7BGG4fhdDNQPzwsEyf9inmrdZqR24Mfx3A++ODeCh7AfiFSxVGHeGSz9KH+kGLa5CwYVizFbtVt/t6A4zhgWO36FVxqCodMEPcTQ7NsF9wqimaBqgMQKS6vk
*/