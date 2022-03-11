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
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
*/