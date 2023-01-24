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
CDRfKXGLxSu72eWg3muSu3ls4OETQ2WAxdPHK7pW0dzh08HuqAsVZuqpKKPtkZbipQRag2gJZ06SHe3hGJ84b4lEbrSI46/6lYs8k4NEjUcqe4ifs1ARuOKi3zl97xbxWeXCYD5mjw92eR2TuduEl9NvQ46vH1tyioZ+iDMlXgP0if5uXI4WLfQWJPJScdb11npkDyL90E8xQSFE8aMNJjdUySchZuLv/W47DLvL6KbH0KpVUL9ugtcwOqKIHCcnxSPqzpzkmzwp+pzCm8pUzLfEAxN2zh717oLAqzX7qLdUy274rDT76Ut9ANl7WqTzXGHpDGgTx/dJY1L7qNB45UJjKdpwycVz+1cdaPRQbREbtGq35a0k+HVpoJAKvjTB2B3rUq5ioZro2TKQ3ucynNp/CQ1CWrSf9ZdPWVLrbY3Dfw2L5yF523uzOFcyNJGFiVdBADtqq5ulsDwfex7lFfr7p5GogyTjvepss40j5uFKxhcelAhXwXMRPK9Z7rXsrvRYt+K95tcrrk2Zss33eLeDaZBVTFfizU1ddqtl4JyayA15JE8kRfI9eYRHpZVtqnLH/RFwTu+Lb5bs0MCtwmRn1ojY3s3nDjjQUgt2kgz8MHrHrdzjd3QxtQEQfruW3g8UWeHvfVBslYjx+YupsEt0agzpFIOZDs+ViHpNfLQm3WX2hOs0krHdSnkHWnt4oXkFp/NFXyeJY6Rd
*/