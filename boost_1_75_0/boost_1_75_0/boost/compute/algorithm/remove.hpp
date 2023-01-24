//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_REMOVE_HPP
#define BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

#include <boost/static_assert.hpp>

#include <boost/compute/lambda.hpp>
#include <boost/compute/system.hpp>
#include <boost/compute/algorithm/remove_if.hpp>
#include <boost/compute/type_traits/vector_size.hpp>
#include <boost/compute/type_traits/is_device_iterator.hpp>

namespace boost {
namespace compute {

/// Removes each element equal to \p value in the range [\p first,
/// \p last).
///
/// Space complexity: \Omega(3n)
///
/// \see remove_if()
template<class Iterator, class T>
inline Iterator remove(Iterator first,
                       Iterator last,
                       const T &value,
                       command_queue &queue = system::default_queue())
{
    BOOST_STATIC_ASSERT(is_device_iterator<Iterator>::value);
    typedef typename std::iterator_traits<Iterator>::value_type value_type;

    using ::boost::compute::_1;
    using ::boost::compute::lambda::all;

    if(vector_size<value_type>::value == 1){
        return ::boost::compute::remove_if(first,
                                           last,
                                           _1 == value,
                                           queue);
    }
    else {
        return ::boost::compute::remove_if(first,
                                           last,
                                           all(_1 == value),
                                           queue);
    }
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_REMOVE_HPP

/* remove.hpp
NhsdrDF/H3y1SrU3fEaombStojrkXbg1xrwHnifFGyoBQj8/3isd9koPZXul/R5Liig5c8lvlE6Jzp6c8cULYjyh8cUeaUyKR5pSLEqZlEKgWtzXKjoaFi1EXrGns6XS5LeicLQIfpoxf8cO/52iPGImvUnGNzZP6GYx4xBUlAenSyiJCl6HBa+GZ/lw+sAFCP54uADKjJkkhjK9GTX40ANthbKxlCskeEKXIRHZWfUE747nQs14JDGSkPJJIb2TJzQaattW1bHdKBvuYRyrB1nR/R7pho5H7JPGFCNXTCkBssWMY+K+n91QbLqTBGLO4FmTrZxYPakqDA0GGy0jLLYy3AEt20x+DPkU6ETx0V+nQtViRg0ALty/ZZvZVvY7tup4CbLHkSrD/8yq8MoJ6V7HrkUL0BMrGWuy4tqeDV8x0N5xi9x3Ij634/MkT6i/N6MKIQuQAhBhuV+GbDYrzyCbwiHrC3U2QBbhSqlr56WlIHhTKWQWh6yT8gRNAjBW+qTOPoZRPHliYTcgECd5HTsWWJ229SZoIzdXDGYL/mxnS25JTOBajyQWiw5AC6PjPY4dCwd6QiJA2uwJmcWMWigNa+NsCDqaCyxlPNaARouC5ieGXUFtBpeSOymtwEnb+iNbsRSfw5tFaVwKtLFweJHje39CkWPSRX9sy7gScyCNKS5U+5UHAHc5fsDjYRw2VBTqXWRzfW5bXxW2
*/