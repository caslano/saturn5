/*
 [auto_generated]
 boost/numeric/odeint/integrate/null_observer.hpp

 [begin_description]
 null_observer
 [end_description]

 Copyright 2011-2012 Karsten Ahnert
 Copyright 2011-2012 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

namespace boost {
namespace numeric {
namespace odeint {

struct null_observer
{
    template< class State , class Time >
    void operator()( const State& /* x */ , Time /* t */ ) const
    {

    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost

#endif // BOOST_NUMERIC_ODEINT_INTEGRATE_NULL_OBSERVER_HPP_INCLUDED

/* null_observer.hpp
jlkvB+07gvxs2PMIsScvieSub7GvUI19yUF73lAbm2hPvJ2yqaqsGAK18qLdznJctPP1enpSbaVbk0x/JSjGUXsUtu9faALlfDXo9jztX8nLsOWl9GGdZhuv+2zjjaD86LbxJuvsW5qer/bp+Ys+21jPNBs0mnU+mveY5kW2jY1Ms4nLHWJ9Vip/XlZGdu5BTcPNTZNx9AcaDh9yO/HjLAlnNILYJw7MnnTWuc1cX+X/SeeEGrMSVbl35sg4TKg=
*/