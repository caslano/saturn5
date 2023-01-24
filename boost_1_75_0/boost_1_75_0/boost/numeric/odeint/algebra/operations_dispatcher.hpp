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
mdsQpA2nqPIeWNM7fVjBk1UC5wtpFttSrKrUbkD/clr4Fz1y5sG8qAPEAddZQFvfnQ/kPl/mPl94crqPGYMZsek//OxLAD2dg+5nVSEt0bb09cQO0K84PfSLzgz9lL92gF46C+hTu4sMy3LmCTm8INvHohhg8ezoL4zfwxIYOgo+tiO0IDXJtvRbSywaWO0GMWGnx2TWmTF55pkOmOSfBSYjukWpRoc70l2/4isRDDGMx6gyMAApDUh0sS3N6BSJp06PxKNnRqLh6Q5IDDkLJBZ35cT0gy/zIAx6BoKPMFN1ZOOXnx0gnXUyTMwuAxE/+xpwSbYtvZUKk3Sx/v82I5aOyJzNjLxn5ci0+DKPIvgIcKS7fuXHQ/8emI1dPuZJN1Dwsm8BC6ttKQYodoLFktNjMbMjFt3kDdGM5RyZa5/qgMw1Z4HMj8kxCwVQwDpFflA32zgSRVaOhT87Fo2utqWUhimKhjj38FgUCyl/UBwW954VFjP+0gGLq1zlDsACzdM88k13gsUlydFFgvVe6jtCX5TBwY/8yYtLHZCpdIDw3h1JcLT4GJ6ab5H1P6f4H4pvmoH69HQK/scdMpDY47hqKfsozj+MLkE6SvgxCnFRJpTMsAw3AyWFoZJSBKOap1a3iC2zUtQZCXxHXX5wcGAuVQPl0XKeiZr9z11ARZqKOZlKX+GuStlCB5Pzkvh5INAxLuLfuGkc8DN+
*/