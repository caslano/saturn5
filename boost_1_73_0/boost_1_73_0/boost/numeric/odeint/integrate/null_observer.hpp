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
6ae1bos5ttN6zezActdlTSFQEm2xo0mNpOJ4a//77ijJTuBl7oAqL5JI3vM898Kjup3vdzWgAwevyP9FeOHdW1wZ/Zkn7t9XR9EXKH/Q6gbvh0i6sDP5ErXhsMkXaHmTqGJ5Sc9RdIjohrTRvy5Z3kT0iCNoRpYDnW+MWGYOWoM2nD1//iMcw7PTZ6cBDJkSXELouIq5WQbwMvUjP2Xs7u7E8tcBcAdMnlRQ80xYsHrh1sxwwGcpEq4sT4FZSLlNjIjxRShwGYeFkBwG06vr8eRNAOtMJBmBbHQBNtOFTCFjtxwMT7i4LTFyZhzoBZojeCqsQ8DCCa1OkJuD42ZlCYPombQa2C0TksVIxBxkzuX2RbebFEai+m6qE9tNavdPMrfaenKNIlZsAzp34DQUlgdAKwNY6VQs6I4BwcG8iKWwWbBTg1Qq7WoDlktJWGgnuC1lcwir8AS0DHJULBzdrFaWqNaZXj1YiHEklEVhFBJhHHBRqjHMARQq5cYv9p7XFFVMfYAfTc1ObwpaoRho9kMYh02ImRU2gA/j+dvp+zl86M9m/cn8GqYX0J9cE9i78WSIqRdIZoDf5YZbJDcgVrkUPK04v9/VbRwJlcgi5dB03GKqmo17Qyu+SnlcLP2wdcyJBJKMGUiZYx8/
*/