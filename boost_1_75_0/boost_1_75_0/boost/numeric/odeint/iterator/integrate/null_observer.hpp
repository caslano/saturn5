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
tESE0l3OLOw9iHOH0DOfpYoxcS1C5zHS6FlgoJ7sG4jmQMdaa3QdMI1lmF1ciEKirs3swWlaZExn6fPEklOvZfZ0G1r9fM2OwcxaHoOQoAUca9qi+3EjMPAtdfm90tIwCGOhrmOgdupbw+afv9uWC2Fr+64Q55VeGJYOUZVCY48x4jQbttGGnnxn806NxiT9Ll/QAmBVUek/zCry0khp+uubjKREw8qgAWF+jwghADLwh0H9jQtj40BDGlDsmgTSXOAdyHqLgy0fSE8hYncR4IinmFfoDHOWKXTVivC2b8tlEtRsi1XFGNEwA6wuT2+ZvJkgnX97NCw4JbMUsY5q1G3T8di3c8TxD/AcLpm0dZeCGlJAdvYzezJpLOcCHtf3ULXW0BOj9+fXR0grOcGt376NrGGe4TSd1+N58S+s5znUHt6LKj//rQ155CAr1jrOxco0Qd6qFZIZ6c5GiLGcZLgAakQgE46nRFRZcmzeGkE2/rlW1oNqaA0/TZ6/DyBqSSDHRgWxsExIu7SAGR9YVUvth+qJ5VvFFfZBDsD3fzd17XVKhY8N/NSc8ULwiv4g7FrB1A13m+gJpbVoUCM3JomadaGTmToduoHbdL+korHh375k7HgocETPmIJ8Lsa/HA0S8iK0fBvVtnt559svCXcT4+NbNGB+5q5n243J1eorXojk2LLYgRTQQy8C095d2HrH3Kfl/m3mRO5C
*/