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
      return &buffer_[0];
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
      return b.empty() ? 0 : &(b[0]);
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