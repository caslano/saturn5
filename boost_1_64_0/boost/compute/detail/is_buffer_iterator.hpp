//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP
#define BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

#include <boost/config.hpp>
#include <boost/type_traits.hpp>
#include <boost/utility/enable_if.hpp>

namespace boost {
namespace compute {
namespace detail {

// default = false
template<class Iterator, class Enable = void>
struct is_buffer_iterator : public boost::false_type {};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_DETAIL_IS_BUFFER_ITERATOR_HPP

/* is_buffer_iterator.hpp
+8wJK4f9ropiX6GgSkZgkZyBSKE+EVQngwGowE1N8YtORdJ3RWQ24zDZUMrK7ZgzH6GOc4i5sz7ki2Kh5RhQRBGbSLTl5SPhOddGgLVOXa23lEOEeJrakqxsRBmwVS/PxXIDOFcJjJw4eMqVKVyxk22w6lF1Q52W5ZBVbwIjgOFoYEKVmX1I6CSL6TKDzF06JJKseLbCZZydT8bn5cGl3idNy6VXunwfcn4sz1BTcJG8hzcPr80XzZo4FqLkFCOTCkfgcaU24husnmmD7yp7gIyQRldOf1E+0hOgX+xvL9rElRlSTP4BSW7XOjNy57kK9chCF+/fI64GTiNf+LD+dIT6W7xGBIJBfoZLclEkp++8pi/g/df3q+nQWYvTCS5FKj2m/2+T+ttRVpf+WKrC4AlzgWjPGkXrDf/yLfNEScig4JiwQBiEcf1fPgO5xpF5SBzb+fkZdW6LfhkL+upZViex+FiTBvgu5KKtVcay7QJNGIi1apM0HRsRHm4wA4qZbaJ7aKVv7Tin7Jnj8YwSy9zEAbSS7KeiNeZKShXbuW6CVyOzGv/1As4GaA==
*/