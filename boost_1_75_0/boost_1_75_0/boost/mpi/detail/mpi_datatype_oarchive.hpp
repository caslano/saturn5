// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP
#define BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP

#include <boost/type_traits/is_enum.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/archive/detail/oserializer.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/ignore_skeleton_oarchive.hpp>
#include <boost/mpi/detail/mpi_datatype_primitive.hpp>
#include <boost/mpi/datatype_fwd.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/integer.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi { namespace detail {


// an archive wrapper that stores only the data members but not the
// special types defined by the serialization library
// to define the data skeletons (classes, pointers, container sizes, ...)

class mpi_datatype_oarchive
  : public mpi_datatype_primitive,
    public ignore_skeleton_oarchive<mpi_datatype_oarchive>
{
public:
    template <class T>
    mpi_datatype_oarchive(const T& x)
         :  mpi_datatype_primitive(&x) // register address
        {
          BOOST_MPL_ASSERT((is_mpi_datatype<T>));
          *this << x;                   // serialize the object
        }

    template<class T>
    void save_override(T const& t)
    {
      save_enum(t,boost::is_enum<T>());
    }

    template<class T>
    void save_enum(T const& t, mpl::false_)
    {
      ignore_skeleton_oarchive<mpi_datatype_oarchive>::save_override(t);
    }

    template<class T>
    void save_enum(T const& t, mpl::true_)
    {
      // select the right sized integer for the enum
      typedef typename boost::uint_t<8*sizeof(T)>::least int_type;
      BOOST_STATIC_ASSERT((sizeof(T)==sizeof(int_type)));
      this->save(*reinterpret_cast<int_type const*>(&t));
    }

};

} } } // end namespace boost::mpi::detail

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::mpi_datatype_oarchive)
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::detail::ignore_skeleton_oarchive<boost::mpi::detail::mpi_datatype_oarchive>)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::detail::mpi_datatype_oarchive)

#endif // BOOST_MPI_DETAIL_MPI_DATATYPE_OARCHIVE_HPP

/* mpi_datatype_oarchive.hpp
3KHfarHdU7FbVAkp5uT+NoW184v+1WmmFOOiaVrWTMW+JQfSpN4hRkjkJSkhFgwEao7ok0eeEVMGbLa4B6xjaA3s9YSd7Bm44FrZP6SbMlIxc5Fgk2kZWbP36svPHP6a8+LveWrkYmscj8/X1iapqTMWKYwzZwHrWClpE5V16f5RCDR2s82Rb4Og3KeAqzDlVxeXtACeRtcXcaWv8hcL5GNfNruX+Uco0Pmvf7//dsNWs+5Di3NZyOayoBFCkyi25vRH0OBZaW21gi5by6/xwZ54N7hlS3y418Hv3UMXJ0mP7pSVrNq07Wdf/vZdsaClhOo1drVd5Enne4asiNOPTV+WgH9KQ1v1oLMEPXwPJSJ2prqGSh6Sy05pv/kDT5JSaQo99Q5qphxZ/RLjn6Vterf5zIhP77eU6Li4ac+WkAVvFBW75HcYQ6udfh/0OZaTV0QONshpjVwJDz6rKMHVP59Me417+OHKyY0GmBNbFnSKnaPOaiPavNgRxruDqx9YOXA4+KvwA9VqPBzRoxLLRHVX5URX8Ymt7w7flHkt4OPEigOTaeWu55g7KgWiukLpY2Q9tJY9FtZawfbyOLrYzJ9lV3DdVxg3uuRN/rjdDng1LOA1W/83Se414pQth9xn4AhvOxp1DswUuP4nZJ/rwWhqd1nx6BGs4OJmJzGy79vwF7O/YL3eKeEuKZHcRD51X0wqqok0NssgNnhL
*/