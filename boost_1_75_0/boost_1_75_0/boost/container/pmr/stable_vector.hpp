//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2015-2015. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/container for documentation.
//
//////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP
#define BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

#if defined (_MSC_VER)
#  pragma once 
#endif

#include <boost/container/stable_vector.hpp>
#include <boost/container/pmr/polymorphic_allocator.hpp>

namespace boost {
namespace container {
namespace pmr {

#if !defined(BOOST_NO_CXX11_TEMPLATE_ALIASES)

template <class T>
using stable_vector = boost::container::stable_vector<T, polymorphic_allocator<T>>;

#endif

//! A portable metafunction to obtain a stable_vector
//! that uses a polymorphic allocator
template<class T>
struct stable_vector_of
{
   typedef boost::container::stable_vector
      < T, polymorphic_allocator<T> > type;
};

}  //namespace pmr {
}  //namespace container {
}  //namespace boost {

#endif   //BOOST_CONTAINER_PMR_STABLE_VECTOR_HPP

/* stable_vector.hpp
ShnqXZJORT9JMQhaYDlP6JoE8KRGcSI5wpra4PlLK7x44Th75gH04G6ujncx57cYFJbd6jhVvs718RjZ2eGe4fO895hiYPY40/t+3qQGPLtj+ecv7/Oszemt9fBKc+7aEo/d3GXlyC6r6ihiQmxfK8WfnB/xT58eU6wu0ylSyqlFJ5pKPPnacWRynBfOn+HSpW18lWD6K+gkhAWbqKLTGAVOhGK5RzXs8Puf3uaFl6a8/b638PXnC4qjl3nfT8Gf/fbtFH/6Lu55j6L/sx9n6eQFkv4HOPvlXSb7dbeZOjRY8wGt/IBbJgnp2XsXMwXnmoTWxiRAflt5KidhVJgNboHWGhV7bM2UQL0pFo1DK+1X1cKtFpQHLWUx/97mY7aQj2o2XdudWLT+Bz4Z7SfUbCdHnaNiNyBpTQb2JGZMkhiqyXw5fzsJaHEaUEsBeF7FSPD2CgjAu4bc8E1r6hp++EZ4Q997PbP+8ZsaZYILoWB/vMOw3J/dkwVINfdcyzWau2EzxDZDBQdQXbilSresf42lUZzZ/Ck29d9gWO5z7b5/ilk9h1hh3+6gu7DSyemQgffoNA6i0JArzW1qjZXxbXzh2fu5Vr6DYnOT5UGCLhTOd1DmJMP9KZlc5FQ+wqp1ruWbnN0f8ObSctvamK9eP8HZ/S7PDB1Vf5XuIKP0HiUKMxhwdmvI29YtK8aHaACBgN0rhe5qj6RfUE4t
*/