/*
 [auto_generated]
 boost/numeric/odeint/integrate/null_observer.hpp

 [begin_description]
 null_observer
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

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
5puSEAgBJIV6BRbdZthv377QtiI0Lh2+SJqJy6w47MxTY3Btro08i8294+Fk1W8+sf38VpJz4VdHELk4UNZJS0BEHqSx5NrjJgkzmbxWV9kVrGwsXId4Rky0e+lU4L+PLOBc07knWUkNWrD91tIG/xp4kRmi9t3t9aBrY+0iynNBe2aD3v8vB60cV9sYzYvHb+WCDI+/i9BtZAw1boeGFVdk5XzCvCzH/cxzA5z/zMi4aZhGSjehozTwJ0rMV5KuBhMz5uaxvyFK6C5JujyAJKBoozj7GlaRDGG1MtYFNGeQne/5odUbG9/qQPlobsikIilPOIYGhNjBpzdU0Y10ueWCJvWvdOQiu0w9wgC0WINygTZ3f2fvMcrjtymvG3mOf5iG3UXo71+Z+pJ+T2QxH4CfSkoB1pFMRTq92RhZkxbf78Vpyj8gwwEEpzbaStvWRclMXmDJGrs0TzmreeEwKF/mlwAh2nJylw4dqu6Ydzt09rSerZo1cGiOneOx/rKYqlkqtFLsyTwGoBXFP2/3KYyJDzxYJPmgcUYNwt2OxQLDyFY2dKNkpyYv0w==
*/