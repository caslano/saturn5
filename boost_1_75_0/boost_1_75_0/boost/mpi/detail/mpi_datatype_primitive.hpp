// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP
#define BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP

#include <boost/mpi/config.hpp>
#include <cstddef> // size_t

#include <boost/config.hpp>
#if defined(BOOST_NO_STDC_NAMESPACE)
namespace std{
    using ::size_t;
} // namespace std
#endif

#include <boost/mpi/datatype_fwd.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/throw_exception.hpp>
#include <boost/assert.hpp>
#include <boost/mpl/placeholders.hpp>
#include <boost/serialization/array.hpp>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <boost/mpi/detail/antiques.hpp>

namespace boost { namespace mpi { namespace detail {

/////////////////////////////////////////////////////////////////////////
// class mpi_data_type_oprimitive - creation of custom MPI data types

class mpi_datatype_primitive
{
public:

    // trivial default constructor
    mpi_datatype_primitive()
     : is_committed(false),
       origin(0)
    {}

    mpi_datatype_primitive(void const* orig)
     : is_committed(false),
       origin()
    {
#if BOOST_MPI_VERSION >= 2
      BOOST_MPI_CHECK_RESULT(MPI_Get_address,(const_cast<void*>(orig), &origin));
#else
      BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(orig), &origin));
#endif
    }

    void save_binary(void const *address, std::size_t count)
    {
      save_impl(address,MPI_BYTE,count);
    }

    // fast saving of arrays of MPI types
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int /* version */)
    {
      if (x.count())
        save_impl(x.address(), boost::mpi::get_mpi_datatype(*x.address()), x.count());
    }

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

    // create and return the custom MPI data type
    MPI_Datatype get_mpi_datatype()
    {
      if (!is_committed)
      {
#if BOOST_MPI_VERSION >= 2
       BOOST_MPI_CHECK_RESULT(MPI_Type_create_struct,
                    (
                      addresses.size(),
                      c_data(lengths),
                      c_data(addresses),
                      c_data(types),
                      &datatype_
                    ));
#else
        BOOST_MPI_CHECK_RESULT(MPI_Type_struct,
                               (
                                addresses.size(),
                                c_data(lengths),
                                c_data(addresses),
                                c_data(types),
                                &datatype_
                                ));
#endif
        BOOST_MPI_CHECK_RESULT(MPI_Type_commit,(&datatype_));
        
        is_committed = true;
      }

      return datatype_;
    }

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
        save_impl(&t, boost::mpi::get_mpi_datatype(t), 1);
    }

private:

    void save_impl(void const * p, MPI_Datatype t, int l)
    {
      BOOST_ASSERT ( !is_committed );

      // store address, type and length

      MPI_Aint a;
#if BOOST_MPI_VERSION >= 2
     BOOST_MPI_CHECK_RESULT(MPI_Get_address,(const_cast<void*>(p), &a));
#else
     BOOST_MPI_CHECK_RESULT(MPI_Address,(const_cast<void*>(p), &a));
#endif
      addresses.push_back(a-origin);
      types.push_back(t);
      lengths.push_back(l);
    }

    template <class T>
    static T* get_data(std::vector<T>& v)
    {
      return v.empty() ? 0 : &(v[0]);
    }

    std::vector<MPI_Aint> addresses;
    std::vector<MPI_Datatype> types;
    std::vector<int> lengths;

    bool is_committed;
    MPI_Datatype datatype_;
    MPI_Aint origin;
};


} } } // end namespace boost::mpi::detail


#endif // BOOST_MPI_DETAIL_MPI_DATATYPE_OPRIMITIVE_HPP

/* mpi_datatype_primitive.hpp
ZpWVExlui2VNSeE+Ua0NdK3cRKZiO3/cqLQ3Ksxya+mSEKnVhMB7/9jWADJnLOcbDFTzQp1rLCIquCKp9YZwbHL9TpmoG4JDPfA5zjPEO+PhvIiHxS+8FTkfUKFFt5V6l4MqThDzteHfrf8skxRNjTjayQ6Yj3B9/nE4OOcf7LN9WJwqn1VIGbPudj+0r47owm9Jb4U6TujMiLh/S23u+caoYwYgLpI729b8xOY835CF/KVG01qHecNT5ybB/B6uhqla0WHrZJ/RK0Q66233bK+Wcp7FSZzxz4W6RKBvjK7x0Vgc2ulit4ZJGTbQi3mC/f1LtGKu0tqbuqVEt067J01OBHzN+77JNdtgPL/zUopTo/JIZpQ1LwueinkvsFH/9hq4Hxf0xhr2/f1FJzP+uPknVeKq59SXGySYrV866DYu7zbG+O5hlN4DGCkaGkoa9yxKWMXdM1N6O3laLiUM2uksSslFy9QyGUOwVC56G4HLLyMr7XzYtyIn34kpctveUcmD+WUPXPbLnrWjSO//yKFOCxJnIq6mq1Zs4yUkB9SWMMqz8pmAzRcoQsNfUXUZ6c6qFI0IzHXjAoKvScaV4HLxvayNmw8PFH5xj1nt+HZPrzTW822cb0VatXK9Nt1iCLMi13QcJwlj5ItKmPLgw+UHEfsy7iWmJX+zeI0FE/wyYd4j08Pg5PQzPRt5cbCujZApstzXSMSF/8pQ
*/