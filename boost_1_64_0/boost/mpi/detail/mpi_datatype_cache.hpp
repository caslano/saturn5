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
c0e+NbkL6xf2XoCJ2O/FmK3Wc3Ywd1OuhVW8DfoxmBIX4Effp7N8JY/ysSEDXRDzveQs6pLmMDJw2YmIYr8Ufcii2GYLeODqReo78sPxCg5Gm211tVLhpBdVtERCnRCUZJiU23DOXrAoRLnGSScGz2IT/JCVenabmG5rsKpT6Q2bCU5neEYH5fiGtQUbwxpd8R28M1ZWBFsmPG7tSGrz8e6yx9oj78j6rWRWK05jrXhy6nhabvGA5vwRmtcvBNRb50fT7WXDicw+QlXyG3Dl6nUb08LgwkFgEgSMCR48nwd9g2rLJBJLene+Kc31A6vXLUiZfI/fslGTDJmdJrf8Jq+j9dtCYYQpM20R9yMGNqGLpMNkW6dgcnUZNoI2WTVzhOW+A75lyp3gReOuaEJHMRdxiu+8lRAWxREFtldKv1VSMgot3Ro9mNbnn3zKum8ICAMUVYlSVWMS7A74zdYoYjuWvBNxauSTIk5Utw6iU83aC6sfaIVgcDLek1+74Qliqxq6g7Kp4JRz9Ftx0DWzvDGqubuvzcJytHCODA3cSTsQfvWMIUHjQ3WWPw==
*/