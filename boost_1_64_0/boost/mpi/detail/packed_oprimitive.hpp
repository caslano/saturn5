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
3BGJ8YeCWHAKgsefcQqCnXoT7Pi0j+wO2xgjCNhr1mRGtS4Sy2VuEK6m2Jt8OibKESbHqmOpSknqpcnxtY/MpFA0rzqJ4oQOTbI9g26w3W+32WRyDJOHruH9l7QcieYA6gubMCDK3t2AivHNR202CSOynwnDGp/nPrXGJ9Yt0TDHpz91vt3zn7pM4TZXjI4ifZ52quncO/i0e2DX8kIorZdxlWXB8y9qcUy9Y3DvuDmkXpqWrzzmT35qwljoTv2H3dlXWbhqNa7pGpdH44I+X0Kt1eJS5l249KC/33vaXhHmoNZ/fKgpQ2NLZmz2uLXTuEEOnPS07SRz+d++pnHbTZ/ssSui9Un1ytbobfJp6mPiIT10BvqwCdMr557Hm/n0bTJ/yd4nq4LoVWt7faM2tIQOxEj7W80v7Qj3QcFukgDgmgO+qq+QfI8crri56MeHk4Y41uLR/gFOIVX4ATF/B5rkdYm87qV+D9oqqpmW7Qpls8eCU/OTvIaK7M4tHBrLz1Ev9RpWjFIu7R+QuP0Mo6o/4fFo66QfPSyvPemUb7+TLQzad075yOq4i/6i9y5AhD/Ur+16swysdxkVBVV7yQ9KnbeF0SomaTrCW+E1dzRGaCAfA50MoGYANdfT7nJ1MwMNwPRsuMmRtCLQnkqm85+R/1mKmhAGP7SkSL6n6pSgH7to21+2OVmxPpAOun/Kkfy8KHlYc02kwilUOA2uZXc6oH7PhZNAOXWO5PlSOIULHxf0YPcigHxh96tNeTvGkXYxzqm3ChmLzwNBYURl/j8RtOsH8MlBqpZB1U0KlI5UIoRWS/Vrt2U5jJ1MVtBCsoLTpJOS0EnF76CTYA7VkhzDdvh6zpDLXy941nxu6zIvfB0/TK/jIP8jEUe8iQ0lq2QKWCL/3cv/zarOpL9FV/HadDVr1vdtZqJaVVO9ShasvwXJke/Y3f8y6XZ5Q1k2DUOWKWn9tBBZQdsg95arXkQfcExYVlO9jEmxxM0VrXSbtsiVsEWuZI2L5fQqcg1ONi1v1MsisSS9KgXpIB92NKKycsrSjtG4os7noZ1yfQYIZ5Kef4PTk9OQbuh0ObJnZ/h1hhzwK6MMkn/LqOZ76XtWkQE62a79OrHYFFYuvyIfSr2AnPOkTWgXUf4xlcvpxBS9jEK8oOV0MDh8GjmhlK2mj1o1Wh3hgD+RO05ySL2+pd6M2LIcacq7QaxqKS1/pTUsjRb2vW/hP7nd2CR072h11HZg467Sm0MNJUsk9kTfjyN774r1tfwwPRbB/kdNnVWdxQR3dXcn5eWCTrbVnXc4Kdebk537z1vlTSVj/3Czji3e1FipcDLVT4EmN5Q8KVCbRLnx89lyviBlbWPl2vpKe3tDRH8bO3OL6D/r7xGHvg9j8yJtfJTodCSng0YjycNGlgJvUCaGEXNwiHJI2DWylN8QlfPjYKq4dXWQW3BUTlEw2cJ2a1TOEcHkAPcARMxtsjFlemqSQMYRgQO/FiWEx4vHRjXS/iAMT7KBQAafRuo8+bBW+eyNH0NeYnKLzNrJ5na0mEwd7YUlBm8htUlKPk10qVW8I5FU1gqEXvrSYzxYWh2zWa9d8ZldMz9ye3Ow//V+xLZPNFuGidjViTpqTaTT3o99WE+qfp5Ux7U6J/Tb3UAlAgwKppx4FB/Y3uqhZ53q80S3BZaJ0CVeCrVZ84Y7dDzv5DvtC6Vi/s2mYxptoEDb2HEEIcGB69m3imEIm0unadMA003qJ/bk+one4Dx5tVaptkLteEfp9yfDI4GGLH/pQMP8E+6tZ9KzxAyPw6tNEtlZtpW3i3dPZBVaiNrqrTWdcAxJs2lyrzyUgSPfNuVSK7OZrZhH5JE=
*/