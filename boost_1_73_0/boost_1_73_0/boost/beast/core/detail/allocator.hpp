//
// Copyright (c) 2016-2019 Vinnie Falco (vinnie dot falco at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/boostorg/beast
//

#ifndef BOOST_BEAST_DETAIL_ALLOCATOR_HPP
#define BOOST_BEAST_DETAIL_ALLOCATOR_HPP

#include <boost/config.hpp>
#ifdef BOOST_NO_CXX11_ALLOCATOR
#include <boost/container/allocator_traits.hpp>
#else
#include <memory>
#endif

namespace boost {
namespace beast {
namespace detail {

// This is a workaround for allocator_traits
// implementations which falsely claim C++11
// compatibility.

#ifdef BOOST_NO_CXX11_ALLOCATOR
template<class Alloc>
using allocator_traits = boost::container::allocator_traits<Alloc>;

#else
template<class Alloc>
using allocator_traits = std::allocator_traits<Alloc>;

#endif

} // detail
} // beast
} // boost

#endif

/* allocator.hpp
8OmqysIptN8udzY0AETa3sNT+2eNGxcDzpwuljQvGiUwZUQNxaGoaf+FCQKkdLbt1jYh+9BaRa1O351+C+LV80Zzi8UK+4d9wkuxAyuq95gVH+wLeCp2EqbGfva2ho1eL5XyN9q8hEO5Pc8TBYrMROH0reU6v7meQJcKot+8xSqhSWL6X4uZ2tLROW0karlCskz3ll9aPkVAcRNbYxX2znZ04TwSKZgqjrH800puNJzeTCYUEJYClg06C5dSRUyGohC2TWzCy8ns42ASXgxHg5vJorM9iSScAWdmXR/vNMmk5V0Sa6HrMRVxi92PwZWSxTU9Cn+F3YmNTQs4+lZKfzZ7jVlNcwdkuMU55yB8p9bsahHizfe++TlpoWI4RfG3xx8ZtjzvxSoPtk24/2vvuHe0UbApFZTxgqcC+ahKYylIGbH4M6m6xA6ld5xDq4y7T4PmH3BAMctoP+KuTPAb9J3Mb6/Hi+HoZnq+GM+m/q4Bd0zmbiiUCkuH5qdynJqywLeSGTeKScot0/+BfTFYDHz4pSmsOrs1LiYlpqzgNJcSSq2sipUMEh5VSyrtEvv6+4D+Gl5/nM2HPhxONgBY3q/qBz8q2OF5XTo7Ekyu2NpALDkrqvJruGbjlRkWIAEPw9kn2DslpE0tOpcr
*/