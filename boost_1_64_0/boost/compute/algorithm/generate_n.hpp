//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP
#define BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

#include <boost/compute/system.hpp>
#include <boost/compute/command_queue.hpp>
#include <boost/compute/algorithm/generate.hpp>

namespace boost {
namespace compute {

/// Stores the result of \p generator for each element in the range
/// [\p first, \p first + \p count).
///
/// Space complexity: \Omega(1)
template<class OutputIterator, class Size, class Generator>
inline void generate_n(OutputIterator first,
                       Size count,
                       Generator generator,
                       command_queue &queue = system::default_queue())
{
    ::boost::compute::generate(first, first + count, generator, queue);
}

} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_GENERATE_N_HPP

/* generate_n.hpp
FDVy4bS92RyPHg2jaRfHwWpPqUki3fPBF4gCRwQEbtWy4gKb2GafReriLKVrowth302TPPI8r+HG8QMq/euK0GzTbcOoqfUoXjAxD726qKWwA/TbZnoqKCGw8ZF1RunFAgKog6/EvZYUWLTsQs2JvnnomSwkbLDH6MoHIEZ6vS7IzUgv2qZnoIgD6d8Eiz4b2tMChTpnAfvSH0iLjxdGKMfgi0ksb4DetaD3OcgYoVSy63bjDfnuWmzImSMGK3+AbpKNmu+MVMnap9lYb2DZO00fhu/LBl6wCVGJ18TEs3Mvo3q5H4qP069iMIznOsZiWIZY5jgQsjkWK0W3TNhqmfx1B/QKpcxCEyJX3K/GG8wgMtXA5Ox8QcYgw6j8NN3yFkyaFj+KKB2uL3surCVXQfYHK18PhKuPyKOewGjG2XWVW98b8w0xan6iDsIoGVE64/dOd5anL6dGese4BaRKJ2iKNk0WaL0DoSrci6iuUTKNwKDzmefxTMg7P2ZVDKQyiqKPqJz4ywD54mkNdCiQqDDuKGW5/U8pysO76UelfyRkFDjUFuqtiKUoPg==
*/