// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file packed_iarchive.hpp
 *
 *  This header provides the facilities for packing Serializable data
 *  types into a buffer using @c MPI_Pack. The buffers can then be
 *  transmitted via MPI and then be unpacked either via the facilities
 *  in @c packed_oarchive.hpp or @c MPI_Unpack.
 */
#ifndef BOOST_MPI_PACKED_IARCHIVE_HPP
#define BOOST_MPI_PACKED_IARCHIVE_HPP

#include <boost/mpi/datatype.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/archive/detail/common_iarchive.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/mpi/detail/packed_iprimitive.hpp>
#include <boost/mpi/detail/binary_buffer_iprimitive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/collection_size_type.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <boost/assert.hpp>

namespace boost { namespace mpi {

#ifdef BOOST_MPI_HOMOGENEOUS
  typedef binary_buffer_iprimitive iprimitive;
#else
  typedef packed_iprimitive iprimitive;
#endif


/** @brief An archive that unpacks binary data from an MPI buffer.
 *
 *  The @c packed_oarchive class is an Archiver (as in the
 *  Boost.Serialization library) that unpacks binary data from a
 *  buffer received via MPI. It can operate on any Serializable data
 *  type and will use the @c MPI_Unpack function of the underlying MPI
 *  implementation to perform deserialization.
 */

class BOOST_MPI_DECL packed_iarchive
  : public iprimitive
  , public archive::detail::common_iarchive<packed_iarchive>
{
public:
  /**
   *  Construct a @c packed_iarchive to receive data over the given
   *  MPI communicator and with an initial buffer.
   *
   *  @param comm The communicator over which this archive will be
   *  received.
   *
   *  @param b A user-defined buffer that contains the binary
   *  representation of serialized objects.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */

  packed_iarchive(MPI_Comm const & comm, buffer_type & b, unsigned int flags = boost::archive::no_header, int position = 0)
        : iprimitive(b,comm,position),
          archive::detail::common_iarchive<packed_iarchive>(flags)
        {}

  /**
   *  Construct a @c packed_iarchive to receive data over the given
   *  MPI communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  received.
   *
   *  @param flags Control the serialization of the data types. Refer
   *  to the Boost.Serialization documentation before changing the
   *  default flags.
   */

  packed_iarchive
          ( MPI_Comm const & comm , std::size_t s=0,
           unsigned int flags = boost::archive::no_header)
         : iprimitive(internal_buffer_,comm)
         , archive::detail::common_iarchive<packed_iarchive>(flags)
         , internal_buffer_(s)
        {}

  // Load everything else in the usual way, forwarding on to the Base class
  template<class T>
  void load_override(T& x, mpl::false_)
  {
    archive::detail::common_iarchive<packed_iarchive>::load_override(x);
  }

  // Load it directly using the primnivites
  template<class T>
  void load_override(T& x, mpl::true_)
  {
    iprimitive::load(x);
  }

  // Load all supported datatypes directly
  template<class T>
  void load_override(T& x)
  {
    typedef typename mpl::apply1<use_array_optimization
      , BOOST_DEDUCED_TYPENAME remove_const<T>::type
    >::type use_optimized;
    load_override(x, use_optimized());
  }

  // input archives need to ignore  the optional information
  void load_override(archive::class_id_optional_type & /*t*/){}

  void load_override(archive::class_id_type & t){
    int_least16_t x=0;
    * this->This() >> x;
    t = boost::archive::class_id_type(x);
  }

  void load_override(archive::version_type & t){
    int_least8_t x=0;
    * this->This() >> x;
    t = boost::archive::version_type(x);
  }

  void load_override(archive::class_id_reference_type & t){
    load_override(static_cast<archive::class_id_type &>(t));
  }

  void load_override(archive::class_name_type & t)
  {
    std::string cn;
    cn.reserve(BOOST_SERIALIZATION_MAX_KEY_SIZE);
    * this->This() >> cn;
    std::memcpy(t, cn.data(), cn.size());
    // borland tweak
    t.t[cn.size()] = '\0';
  }

private:
  /// An internal buffer to be used when the user does not supply his
  /// own buffer.
  buffer_type internal_buffer_;
};

} } // end namespace boost::mpi

BOOST_SERIALIZATION_REGISTER_ARCHIVE(boost::mpi::packed_iarchive)
BOOST_SERIALIZATION_USE_ARRAY_OPTIMIZATION(boost::mpi::packed_iarchive)

#endif // BOOST_MPI_PACKED_IARCHIVE_HPP

/* packed_iarchive.hpp
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
*/