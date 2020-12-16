// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file packed_oarchive.hpp
 *
 *  This header provides the facilities for unpacking Serializable
 *  data types from a buffer using @c MPI_Unpack. The buffers are
 *  typically received via MPI and have been packed either by via the
 *  facilities in @c packed_iarchive.hpp or @c MPI_Pack.
 */
#ifndef BOOST_MPI_PACKED_OARCHIVE_HPP
#define BOOST_MPI_PACKED_OARCHIVE_HPP

#include <boost/mpi/datatype.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_oarchive.hpp>
#include <boost/mpi/detail/packed_oprimitive.hpp>
#include <boost/mpi/detail/binary_buffer_oprimitive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>

namespace boost { namespace mpi {

#ifdef BOOST_MPI_HOMOGENEOUS
  typedef binary_buffer_oprimitive oprimitive;
#else
  typedef packed_oprimitive oprimitive;
#endif

/** @brief An archive that packs binary data into an MPI buffer.
 *
 *  The @c packed_iarchive class is an Archiver (as in the
 *  Boost.Serialization library) that packs binary data into a buffer
 *  for transmission via MPI. It can operate on any Serializable data
 *  type and will use the @c MPI_Pack function of the underlying MPI
 *  implementation to perform serialization.
 */

class BOOST_MPI_DECL packed_oarchive
  : public oprimitive
  , public archive::detail::common_oarchive<packed_oarchive>
{
public:
  /**
   *  Construct a @c packed_oarchive for transmission over the given
   *  MPI communicator and with an initial buffer.
   *
   *  @param comm The communicator over which this archive will be
   *  sent.
   *
   *  @param b A user-defined buffer that will be filled with the
   *  binary representation of serialized objects.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   *
   *  @param position Set the offset into buffer @p b at which
   *  deserialization will begin.
   */
  packed_oarchive( MPI_Comm const & comm, buffer_type & b, unsigned int flags = boost::archive::no_header)
         : oprimitive(b,comm),
           archive::detail::common_oarchive<packed_oarchive>(flags)
        {}

  /**
   *  Construct a @c packed_oarchive for transmission over the given
   *  MPI communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  sent.
   *
   *  @param s The size of the buffer to be received.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */
  packed_oarchive ( MPI_Comm const & comm, unsigned int flags =  boost::archive::no_header)
         : oprimitive(internal_buffer_,comm),
           archive::detail::common_oarchive<packed_oarchive>(flags)
        {}

  // Save everything else in the usual way, forwarding on to the Base class
  template<class T>
  void save_override(T const& x, mpl::false_)
  {
    archive::detail::common_oarchive<packed_oarchive>::save_override(x);
  }

  // Save it directly using the primitives
  template<class T>
  void save_override(T const& x, mpl::true_)
  {
    oprimitive::save(x);
  }

  // Save all supported datatypes directly
  template<class T>
  void save_override(T const& x)
  {
    typedef typename mpl::apply1<use_array_optimization,T>::type use_optimized;
    save_override(x, use_optimized());
  }

  // output archives need to ignore  the optional information
  void save_override(const archive::class_id_optional_type & ){}

  // explicitly convert to char * to avoid compile ambiguities
  void save_override(const archive::class_name_type & t){
      const std::string s(t);
      * this->This() << s;
  }

  void save_override(const archive::class_id_type & t){
    const boost::int_least16_t x = t;
    * this->This() << x;
  }

  void save_override(const archive::version_type & t){
    const boost::int_least8_t x = t;
    * this->This() << x;
  }
private:
  /// An internal buffer to be used when the user does not supply his
  /// own buffer.
  buffer_type internal_buffer_;
};

} } // end namespace boost::mpi

// required by export
BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_oarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_oarchive)



#endif // BOOST_MPI_PACKED_OARCHIVE_HPP

/* packed_oarchive.hpp
ouYSq7bzdjUQk49P7G5xyYm2Q23kYRtmJ1O+VBkVEV5xYiK8wiwirJ5Hq6NQoLLiOz9FsVh9YlCtToHKaYWqwArVFCtUhclQOcJbVwpUpQSVQ0FVSlA5FFSlBJVDQVWaX78yRZzOsa7jM63r+CzrOj47xT5YfmL2wfIU+2ChFYjzrECcb7UPLrAufbeVNidbafMUK216Umhz2YlRwTKF75NmHQPfXHpifHNpCt8ssSJvhpU5lFqZw0yDOZwM6wnGQeriIuFyBTQQjxpIAQ3EowZSwCqmcDlSFxeZuBwDsci6yBZbF9mFssgE7iU8RRaXeoo/3epMt3rSmZBoYIXhrQtlYJNpYIVqYJNpYIVqYJNpYIVqYJPz6xemDKzYOrBp1oG9wTqw6cbA2K4M1+O9rKM1LNkVohauJz8y37JwuwdTfE+nW6E6wwrV7GSoPOH6edDs0RouBJVHQVWQH5mXwk7mWdfYudY19iYrO3mzsSJovkrDkbnQLE2YgyasVE2YgyasVE2Yg5hFqWIWjvytWB1YhUktWGoF4iIrEG+1Lsu3GWusw3mS7tZMfCY+E5+Jz8Rn4jPxOdL9n2nHcv/neu3wsd7/Kab7P16+4AQBgkEBgOdUJy7//Kcu/9DrIXTGl24BdfEtIMthdbf3WO7+uL0TV3+SjnI8nu5KhevYrv64Jq7+HPnqj/fYrv54J67+HPnqT/GxXf0pnrj6c+SrP7OO7erPrImrP0e4+oP3TY/l7g8Un7j8Y1z+EZzSAyrz+QGVJQG5BSQ+Qn7Eb7bhqrHJ9Z8Cuv6zQq7/mG7WJOieT8zkV0y9/sNQolsJm+bfcvknjy7/rODLPwQdehzpFtDE5Z+Jyz8Tn4nP6+ND7yuV2KpnVz17ls1LjwdaY6/k/hZt5eLo6VXfhCLy9JY54r+2ypPAIkexmKA/vadZ9HpX2uZ+8yvscda13z/O+nXuxAnVb805sfqHiserD0+k2WtOA1eCiv0yMogDdkeLklJ3Dx4+4ttURvxnL9XBTYgGLzC6NVrdH8nFce33j7L85T9X5a3vb1G4Za/+guzF8LgRulmqp8GXLvzihS82O3zJ7XgVQ5zNVI9AumEYf6NhQJfhOuzK13Xt94+CPkoq9KjHlUlI2fwnbK3E3ITVXzOP3n/KxfefSvQIeGhjAnHTq2mz4HbVSnoxc4jMlSF6K2cI3j2HjDdSJH8NznH/jJ+o9zyB18hQ6ZBAmZLozfePpEt3pUu3JirdZCS8dnKfqaNYuo5i6dJd6dKtiYZqAcmrs/sQn5Hyvgrt7gI9MDZ0mTB0EijBYa1B9xLVL9HgVa8OYY43Y44rQ066ZEOxXX4qqn0s20UxTDTkqQeTMMebMceVISd9cjEB5PI84aC4/JrnCbit2FCOT4VhEXr8anNgrKHAeIuJy+lpGqSFBnPB6TL89D/HxoYvFToaMNHRANDR/P8XOprv+X+mo82OhvJXgdMRKC4KV6xh2phQzasNBZ4nysc8T/hf9XUDO2xwmAhLg2qhF3OBQw1/B6jp2fJXbVgjMIZVYCzK9ojj5Kq5pp8SdD5G9FCCcTcdEwrtSf4Y77s9baP3BGV1jRpPqkGirK7RdOmudOnWRJOpClMbf407YksTlnEcn2utnoLqXgRffH5/Pj+67kX9IIIRTX79AxS3Cj4AjiPJgumvH191N9iBsKl5N2V4M2W40mekSTXABBjZrDcxEjeufjctOTfleDPmuDLkpEsWRvLc8lPjNuU+gN+T4Te/ff66O9lh6DszXj08RttTqM+DAHqYAmsVg3yDw9x0Ya2Y2E6xJHohnne6dFfadGuiajmeruV4unRX2vTUxNAwKG3FINFCh1w=
*/