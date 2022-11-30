// (C) Copyright 2005 Matthias Troyer

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer

#ifndef BOOST_MPI_PACKED_OPRIMITIVE_HPP
#define BOOST_MPI_PACKED_OPRIMITIVE_HPP

#include <boost/mpi/config.hpp>
#include <cstddef> // size_t
#include <boost/config.hpp>
#include <boost/mpi/datatype.hpp>
#include <boost/mpi/exception.hpp>
#include <boost/mpi/detail/antiques.hpp>
#include <boost/serialization/array.hpp>
#include <boost/assert.hpp>
#include <vector>
#include <boost/mpi/allocator.hpp>

namespace boost { namespace mpi {

/// serialization using MPI::Pack

class BOOST_MPI_DECL packed_oprimitive
{
public:
    /// the type of the buffer into which the data is packed upon serialization
    typedef std::vector<char, allocator<char> > buffer_type;

    packed_oprimitive(buffer_type & b, MPI_Comm const & comm)
         : buffer_(b),
           comm(comm)
        {
        }

    void const * address() const
    {
      return detail::c_data(buffer_);
    }

    const std::size_t& size() const
    {
      return size_ = buffer_.size();
    }

    const std::size_t* size_ptr() const
    {
      return &size();
    }

    void save_binary(void const *address, std::size_t count)
        {
          save_impl(address,MPI_BYTE,count);
        }

    // fast saving of arrays
    template<class T>
    void save_array(serialization::array_wrapper<T> const& x, unsigned int /* file_version */)
    {
        if (x.count())
          save_impl(x.address(), get_mpi_datatype(*x.address()), x.count());
    }

    typedef is_mpi_datatype<mpl::_1> use_array_optimization;

#ifndef BOOST_NO_MEMBER_TEMPLATE_FRIENDS
    friend class archive::save_access;
protected:
#else
public:
#endif

    // default saving of primitives.
    template<class T>
    void save(const T & t)
    {
      save_impl(&t, get_mpi_datatype<T>(t), 1);
    }

    template<class CharType>
    void save(const std::basic_string<CharType> &s)
    {
      unsigned int l = static_cast<unsigned int>(s.size());
      save(l);
      if (l)
        save_impl(s.data(),get_mpi_datatype(CharType()),s.size());
    }

private:

    void save_impl(void const * p, MPI_Datatype t, int l)
    {
      // allocate enough memory
      int memory_needed;
      BOOST_MPI_CHECK_RESULT(MPI_Pack_size,(l,t,comm,&memory_needed));

      int position = buffer_.size();
      buffer_.resize(position + memory_needed);

      // pack the data into the buffer
      BOOST_MPI_CHECK_RESULT(MPI_Pack,
                             (const_cast<void*>(p),l,t, 
                              detail::c_data(buffer_),
                              buffer_.size(), 
                              &position,comm));
      // reduce the buffer size if needed
      BOOST_ASSERT(std::size_t(position) <= buffer_.size());
      if (std::size_t(position) < buffer_.size())
          buffer_.resize(position);
    }

    static buffer_type::value_type* get_data(buffer_type& b)
    {
      return detail::c_data(b);
    }

  buffer_type& buffer_;
  mutable std::size_t size_;
  MPI_Comm comm;
};

} } // end namespace boost::mpi

#endif // BOOST_MPI_PACKED_OPRIMITIVE_HPP

/* packed_oprimitive.hpp
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
*/