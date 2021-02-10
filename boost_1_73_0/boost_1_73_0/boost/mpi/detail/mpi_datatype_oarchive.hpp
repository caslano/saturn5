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
RfRTb/90Elw4zqQ7HFytV0YnWodzjnoRKBvUG3YeFW2EdEeQWH9FjmLSMdMQMimVRvHqrYARCy88DXJVZCEHDEQkywP4pAqs8SXkPMHzG9UMHPseHiEGASFtiwM8d4XpCnN70JrLDi8RCx2jA7IqfJPJR3fg216EmBaQgbr+huCpQh3x7KFp/3J06puuuzGPCmk/JR47uE63txu0sXwOsuc4F7shG8vnIDuuO3ZLPe8A7vfQ/ud2Pef95dlzorAOuyV4jtQ57nPAS48foaMxNlq8Y5e81xBTnpnT3oihrPjtVJhwJot0NbXupaPL4fDdCqnIJJjmvGd77z/lKQYO2qFK8jvnWNnntx9Pm68guv0u/xdQSwMECgAAAAgALWdKUkI8r/HQAQAAJwMAAB4ACQBjdXJsLW1hc3Rlci90ZXN0cy9kYXRhL3Rlc3QxNDdVVAUAAbZIJGCNU11r2zAUfRf4P1w6yjaoq4UtDIowG6nHzD7ixU5LRyholjyL2pKR1GRm3X/flZ0lhTHYk47kc889OldmXjpfcScTwpSuDS53ctgZK1xC3pU5YfS4Z3SikCdQSLuVNnZKSMKs7NsBPwvueUJqY5A5YeZGXtWJhKzS/OMNLK4vYT5/ARnsjH7qgbet2YFvlAOjoRtg
*/