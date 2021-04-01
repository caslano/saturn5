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
execXC7uuo26SGepKTWPimnsrhLfSxMnkUvvb2VEB54KsM+/LIuMqcymt1J+QYbrQtihFqiOez+Wz6PjwOEysxftH9KYGv90cpCsmbaEWZrpsOlBVM/xcwdEfVkIzw13OSYloUOZwxsMLwcjsRUvw3c7Yyai7rAgYG4fhZw06dFuDHB7i0cOnSim7idZJpWqzHukh1DviqfzwRdZfKtTWObI9XlwspLCZdWWdNutDkY9cnbdMUwJo9GjEgJilXv5OkRLwFCsQTerpGpnRLQaPOfhuceKQkf9vFEECXD99NBYTSN7YsD/O2acMaEe5/o7dsAxKnVeGnbxuyZO44Cmp6nKEp+IiMGv53A4OwbzpV6LQPd7TIARMyUbjs7Na992Nl7MAR3tkK7GUb9Q9R2AqKxdg/Ef1fZ8FSSuYoeK74BPuZI+gPHCdUqfnlgLoDjd6emSSRylsU0LBhfMMxWac+R1p+dWeFOq+BGXz3M29yUuPSNjGtLlwyV6R2AZt3S6+HRkJQDWj2MKfClTTYaBPrjk6oHl0JNnwGpcnwfdQDRmP+giEEpSsh7XFA==
*/