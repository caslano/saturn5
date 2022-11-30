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
      return detail::c_data(v);
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