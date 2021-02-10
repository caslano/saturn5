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
yX4Zjg5h6z1YLGH8Kk64gMUT5gWx73FHrXl3n+7Wd15o+5nDWSvlAraqtQWPXIe77E3/14E5OZ2YJ4PJ+P3Jq4H5phj9XCxEF7iLssTmu/OXW9/xELavQnv0ajQ9rhC5dpj6ldH6je/Bbgl8VeIINBr6oAHkqnga8MDhs+xM8xrigkeH5mQwnQz/O4C5kwRU1iJTRqHA0P/IPGC2NKqlWdj6Dsi9EKyifzSYnppv+yevhyPW7v1g5K9G79+a43eDkXT6djELe8h6e9Vxo8HgcHBI43Kyh9XJDWKbSSKn/WE4erwPIPUlf2LWH72dHI4nxUqHg1/N0fvjY9aCf1EWX/CGl12HX3TDzPdL4pZWpl16PZieHA/fDqcGu3+/+mqSv9raEqmVejYgTMp2XIe9YLjCgX4MFp8BfCe0jSzMAjOKeZi/tudWwgJxNstc9+P+kx8+H+QTXkSeA+RRwk3YNxjTtsFfU0myA987tCa8M7b+2mLMc9vb9AVVHIgwTuC121aTd5jw/uRR/t3osNY90erg4sYB0JCibkHawZXDiN1zOkxP1NmqRgEY0UENkN21kTlY6roqoe1HgpuIG6aE6xhEFm18J+VygVTrbRf1aAKYgpr3DtRq9ZfPl54F1tXKwQ8fSo2B+lznY+31
*/