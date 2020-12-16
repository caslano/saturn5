// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_TYPE_MPI_DATATYPE_CACHE_HPP
#define BOOST_MPI_DETAIL_TYPE_MPI_DATATYPE_CACHE_HPP

#include <boost/mpi/datatype_fwd.hpp>
#include <boost/mpi/detail/mpi_datatype_oarchive.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/noncopyable.hpp>
#include <typeinfo>

// The std::type_info::before function in Visual C++ 8.0 (and probably earlier)
// incorrectly returns an "int" instead of a "bool". Then the compiler has the
// audacity to complain when that "int" is converted to a "bool". Silence
// this warning.
#ifdef BOOST_MSVC
#  pragma warning(push)
#  pragma warning(disable : 4800)
#endif

namespace boost { namespace mpi { namespace detail {

/// @brief comparison function object for two std::type_info pointers
///
/// is implemented using the before() member function of the std::type_info
/// class

struct type_info_compare
{
  bool operator()(std::type_info const* lhs, std::type_info const* rhs) const
  {
    return lhs->before(*rhs);
  }
};


/// @brief a map of MPI data types, indexed by their type_info
///
///
class BOOST_MPI_DECL mpi_datatype_map
 : public boost::noncopyable
{
  struct implementation;

  implementation *impl;

public:
  mpi_datatype_map();
  ~mpi_datatype_map();

  template <class T>
  MPI_Datatype datatype(const T& x = T(), typename boost::enable_if<is_mpi_builtin_datatype<T> >::type* =0)
  {
    return get_mpi_datatype<T>(x);
  }

  template <class T>
  MPI_Datatype datatype(const T& x =T(), typename boost::disable_if<is_mpi_builtin_datatype<T> >::type* =0 )
  {
    BOOST_MPL_ASSERT((is_mpi_datatype<T>));

    // check whether the type already exists
    std::type_info const* t = &typeid(T);
    MPI_Datatype datatype = get(t);
    if (datatype == MPI_DATATYPE_NULL) {
      // need to create a type
      mpi_datatype_oarchive ar(x);
      datatype = ar.get_mpi_datatype();
      set(t, datatype);
    }

    return datatype;
  }
  
  void clear(); 

private:
  MPI_Datatype get(const std::type_info* t);
  void set(const std::type_info* t, MPI_Datatype datatype);
};

/// Retrieve the MPI datatype cache
BOOST_MPI_DECL mpi_datatype_map& mpi_datatype_cache();

} } } // end namespace boost::mpi::detail

#ifdef BOOST_MSVC
#  pragma warning(pop)
#endif

#endif // BOOST_MPI_DETAIL_TYPE_MPI_DATATYPE_CACHE_HPP

/* mpi_datatype_cache.hpp
03GqEKc8QkhtzVFWJfReOZ0l2psbm+uig+AG4EjZ4ZFyJZgX76coI8UyUGTYMTbiGBtxjI04rTDJQJw0bwpe14HyKevlM6ES6uzhk4MNJb0ogHt79AhS6hVZf8HH/Oon968KNRdM4zbLrxZ7oO+vaWLJTywwsT66ZJZqAG02Tas3fwj8NMXPEk/no4aXRBDtnYmX3xEy+NlHbCIoE8EWCXUZpQZkgpIJcgPPpAocwFvwqSfcNtJuVnb9lZ5BReuo46a3Yj+WmDWy7XcxtQaUBaFMC6UDSrkeUy9DeQjKQd/H1BZQVoQyB5QeKF9AnTegPPxdO3/1nz5c/9TMG2P/atFMQ7wl+8yGp82rCt0apTBuSg8rgfTScBKjI3R6WEnClQG3RRzGjxJnR8KVAbcDOC5NoWhpCkX7jJ79zgQ0McpKnHU/XKXubytSf1uRcGXAbRGHsb7EuSrhyoDbAbz8KZ94tFeRPldZn6s6ID+43MAj7nIDpa4ehWzKLeybvMvBc5FwS8QZlDhXJM4VCbdEnEHqNEt6BAMDj2GaOHOagxhAphnW6+EMb+JcO0VwvYZhThrQjrZhGD5yR6y37C+SzBSa9rKO9rJO9rIOKJlemaBMBFskFGWUGpAJSibIDZTVj2Nj5TuilHaoF31x8yBr7qIvEq4MuC3i0CNInB0JVwbcDuCYOqJoQZmmqn4EqqozqitSRnVFwpUBtxn/W3O1K2eAsLXmag/vE3EF9bvJJxJUkPOArCbRr1Nkk/USL3MlJz8XePglU5SRYsuUogHmRmSKMlHkRsqfsQRH0WrVyf+Wz6byOGiEv315sF3DVCMPbwGdk/QoFPRPZA3wE5SJYMkEAdU6LBOUTJAbCJiVAq3yVYJmKRzOKXeDzvoWDBkOLBhC35vJVXAryVFZIGvlkCORlxiqgmTjsOz6SI8agHI4lJ2grA8lCWVGKJNAOQB6gF4oK0KZE8pkUGqdPeptKI939rTHZO2jZXw4G+X/pcBM9U3d0Qf53VN3oDfE0t6QuDtWHMI9Hzq04bMT98ZVM/eUv06t0LA+d18HZ6f1AtRJw4GhJosoYzTgAWZOM316AsGcTc1hasiMrPTjTWwSF1Mu1s0YWefHwX42HQ7Yx1TA+tC285XOxMA37IVYIT11YuATslAW6SzEpKFXCXqhG/mdtOP4pX7L8ghVGsVURyGuGqpM4MhCGL/xmqVgGbjDiKYc7kh4ZSMyDI3EHQiVEnekS9HHkq/cD46pE779AnQe/amPL3xoozP7ONbxkYrljcjdVYscNge+6gLbCbTqQCc8FgKKPqD8Lbh0oc4/65AE+drHosVp75qfMscz9Y7DOpODo7NTtv+2cyHYCbm/b9J6tdMtRd9JgOC0ZXk9i9Z/WcM/vzNw6nFwa2i5CWfhzagh6Goyx1iRw+PPnHoU0JDjaIw/k5mlT2ecehj8xbeHo+ORw+fJXoRfN/W4ZTeZCddTya4z0ybOy7PyQiuLNmuRtxKWWhnAypuA20PXxPUBVp9pY2d3Wj/OpothB/HbqT/qIHbXZ0iv/vUYriTB8q5HJZm+hnXonHBrozRsIVccfAB/1Ulb1WZSK+To3nePvnhfx/iWoHDbe2c1Q3uqb559LHyYMJgf6Hxtq69nUhs7C45g+F0cnms3tTTaOfp8cnB87blLQSyyDT1I/RtNd87fBPBlI4dN7dZ8ZD2qOTo1qKJeDHmeTQhLDv7a+hNUe9VOLYhdmaGx0fmJ7cOzN8HDuu8DZRrzcR/aeDzcffb1ylUhv3pLuJfaqIJv0HsHt3zvxw3p/bgh4cqA2yIOJk/iXJdwZcDtAB5YX5uDHHWoa7Vlfe33pqRqkcjwsK4=
*/