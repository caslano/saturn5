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
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
*/