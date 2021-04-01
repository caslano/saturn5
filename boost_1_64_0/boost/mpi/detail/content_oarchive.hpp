// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP

#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/ignore_skeleton_oarchive.hpp>
#include <boost/mpi/detail/mpi_datatype_primitive.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi {

namespace detail {
  // an archive wrapper that stores only the data members but not the
  // special types defined by the serialization library
  // to define the data skeletons (classes, pointers, container sizes, ...)

  class BOOST_MPI_DECL content_oarchive
    : public mpi_datatype_primitive,
      public ignore_skeleton_oarchive<content_oarchive>
  {
  public:
      content_oarchive()
       : committed(false)
          {}

      content get_content()
      {
        if (!committed)
        {
          // create the content holder only once
          c=this->get_mpi_datatype();
          committed=true;
        }
        return c;
      }

  private:
    bool committed;
    content c;
  };
} // end namespace detail

template <class T>
const content get_content(const T& x)
{
  detail::content_oarchive ar;
  ar << x;
  return ar.get_content();
}

} } // end namespace boost::mpi

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::content_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::ignore_skeleton_oarchive<boost::mpi::detail::content_oarchive>)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::detail::content_oarchive)
#endif // BOOST_MPI_DETAIL_CONTENT_OARCHIVE_HPP

/* content_oarchive.hpp
k97P1G5+1VYXtQ/N9fFOqSeUS78tHdlApZ9oTcsFMnpVYNqd5t5dZ/mI+8JIsIayh6/ei6Uzntxr2TvqG9EKYJeAwolL+Fiu/gNJomHvAXX6tZB0jnXeptbl82CboUv6Rujo06GG0gEhwxeUIsmuSEmtB1lOG1hFXPW67mosnar4sgNEhVsCaNJZ9qISvr76+B93gmubdLPFjKHOCKF5RZYtOWxtiPfiFdbBxnPaaOChhjcARDItqE/IsWV+9d6ty0vk3zprCVHMVmm4Sde1cVhQj323IOlKweAumWZN+z+NceXbtrhuxz/mRmy8Qk13I3Q/YbxJ5VfM04feanPBdm+iTdLCBseOpY3J8BMx/Xq+mOO1nyQdq4WUyK7Qlj+iG/iv3TsZI3aDHmeP5KrutNSO+i+MlsyBsCZ//zgddOuRQgHtVfkOkxrJaZHWJtki+gvxEyRpzq4H7BnkEVkqhENYGAlnfKlambCauEwugzpxOawCHO2b8q6ewBlEAUSPSAERYqUhJWS/bgKtPLyF5Y2PoAocBY/B9KUEeLl252FY5xfkYRd6en7+OQ==
*/