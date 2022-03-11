// (C) Copyright 2005 Matthias Troyer
// (C) Copyright 2006 Douglas Gregor <doug.gregor -at gmail.com>

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Matthias Troyer
//           Douglas Gregor

/** @file skeleton_and_content.hpp
 *
 *  This header provides facilities that allow the structure of data
 *  types (called the "skeleton") to be transmitted and received
 *  separately from the content stored in those data types. These
 *  facilities are useful when the data in a stable data structure
 *  (e.g., a mesh or a graph) will need to be transmitted
 *  repeatedly. In this case, transmitting the skeleton only once
 *  saves both communication effort (it need not be sent again) and
 *  local computation (serialization need only be performed once for
 *  the content).
 */
#ifndef BOOST_MPI_SKELETON_AND_CONTENT_TYPES_HPP
#define BOOST_MPI_SKELETON_AND_CONTENT_TYPES_HPP

#include <boost/mpi/config.hpp>
#include <boost/archive/detail/auto_link_archive.hpp>
#include <boost/mpi/packed_iarchive.hpp>
#include <boost/mpi/packed_oarchive.hpp>
#include <boost/mpi/detail/forward_skeleton_iarchive.hpp>
#include <boost/mpi/detail/forward_skeleton_oarchive.hpp>
#include <boost/mpi/detail/ignore_iprimitive.hpp>
#include <boost/mpi/detail/ignore_oprimitive.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/detail/register_archive.hpp>

namespace boost { namespace mpi {

/**
 *  @brief A proxy that requests that the skeleton of an object be
 *  transmitted.
 *
 *  The @c skeleton_proxy is a lightweight proxy object used to
 *  indicate that the skeleton of an object, not the object itself,
 *  should be transmitted. It can be used with the @c send and @c recv
 *  operations of communicators or the @c broadcast collective. When a
 *  @c skeleton_proxy is sent, Boost.MPI generates a description
 *  containing the structure of the stored object. When that skeleton
 *  is received, the receiving object is reshaped to match the
 *  structure. Once the skeleton of an object as been transmitted, its
 *  @c content can be transmitted separately (often several times)
 *  without changing the structure of the object.
 */
template <class T>
struct BOOST_MPI_DECL skeleton_proxy
{
  /**
   *  Constructs a @c skeleton_proxy that references object @p x.
   *
   *  @param x the object whose structure will be transmitted or
   *  altered.
   */
  skeleton_proxy(T& x)
   : object(x)
  {}

  T& object;
};

/**
 *  @brief Create a skeleton proxy object.
 *
 *  This routine creates an instance of the skeleton_proxy class. It
 *  will typically be used when calling @c send, @c recv, or @c
 *  broadcast, to indicate that only the skeleton (structure) of an
 *  object should be transmitted and not its contents.
 *
 *  @param x the object whose structure will be transmitted.
 *
 *  @returns a skeleton_proxy object referencing @p x
 */
template <class T>
inline const skeleton_proxy<T> skeleton(T& x)
{
  return skeleton_proxy<T>(x);
}

namespace detail {
  /// @brief a class holding an MPI datatype
  /// INTERNAL ONLY
  /// the type is freed upon destruction
  class BOOST_MPI_DECL mpi_datatype_holder : public boost::noncopyable
  {
  public:
    mpi_datatype_holder()
     : is_committed(false)
    {}

    mpi_datatype_holder(MPI_Datatype t, bool committed = true)
     : d(t)
     , is_committed(committed)
    {}

    void commit()
    {
      BOOST_MPI_CHECK_RESULT(MPI_Type_commit,(&d));
      is_committed=true;
    }

    MPI_Datatype get_mpi_datatype() const
    {
      return d;
    }

    ~mpi_datatype_holder()
    {
      int finalized=0;
      BOOST_MPI_CHECK_RESULT(MPI_Finalized,(&finalized));
      if (!finalized && is_committed)
        BOOST_MPI_CHECK_RESULT(MPI_Type_free,(&d));
    }

  private:
    MPI_Datatype d;
    bool is_committed;
  };
} // end namespace detail

/** @brief A proxy object that transfers the content of an object
 *  without its structure.
 *
 *  The @c content class indicates that Boost.MPI should transmit or
 *  receive the content of an object, but without any information
 *  about the structure of the object. It is only meaningful to
 *  transmit the content of an object after the receiver has already
 *  received the skeleton for the same object.
 *
 *  Most users will not use @c content objects directly. Rather, they
 *  will invoke @c send, @c recv, or @c broadcast operations using @c
 *  get_content().
 */
class BOOST_MPI_DECL content
{
public:
  /**
   *  Constructs an empty @c content object. This object will not be
   *  useful for any Boost.MPI operations until it is reassigned.
   */
  content() {}

  /**
   *  This routine initializes the @c content object with an MPI data
   *  type that refers to the content of an object without its structure.
   *
   *  @param d the MPI data type referring to the content of the object.
   *
   *  @param committed @c true indicates that @c MPI_Type_commit has
   *  already been excuted for the data type @p d.
   */
  content(MPI_Datatype d, bool committed=true)
   : holder(new detail::mpi_datatype_holder(d,committed))
  {}

  /**
   *  Replace the MPI data type referencing the content of an object.
   *
   *  @param d the new MPI data type referring to the content of the
   *  object.
   *
   *  @returns *this
   */
  const content& operator=(MPI_Datatype d)
  {
    holder.reset(new detail::mpi_datatype_holder(d));
    return *this;
  }

  /**
   * Retrieve the MPI data type that refers to the content of the
   * object.
   *
   * @returns the MPI data type, which should only be transmitted or
   * received using @c MPI_BOTTOM as the address.
   */
  MPI_Datatype get_mpi_datatype() const
  {
    return holder->get_mpi_datatype();
  }

  /**
   *  Commit the MPI data type referring to the content of the
   *  object.
   */
  void commit()
  {
    holder->commit();
  }

private:
  boost::shared_ptr<detail::mpi_datatype_holder> holder;
};

/** @brief Returns the content of an object, suitable for transmission
 *   via Boost.MPI.
 *
 *  The function creates an absolute MPI datatype for the object,
 *  where all offsets are counted from the address 0 (a.k.a. @c
 *  MPI_BOTTOM) instead of the address @c &x of the object. This
 *  allows the creation of MPI data types for complex data structures
 *  containing pointers, such as linked lists or trees.
 *
 *  The disadvantage, compared to relative MPI data types is that for
 *  each object a new MPI data type has to be created.
 *
 *  The contents of an object can only be transmitted when the
 *  receiver already has an object with the same structure or shape as
 *  the sender. To accomplish this, first transmit the skeleton of the
 *  object using, e.g., @c skeleton() or @c skeleton_proxy.
 *
 *  The type @c T has to allow creation of an absolute MPI data type
 *  (content).
 *
 *  @param x the object for which the content will be transmitted.
 *
 *  @returns the content of the object @p x, which can be used for
 *  transmission via @c send, @c recv, or @c broadcast.
 */
template <class T> const content get_content(const T& x);

/** @brief An archiver that reconstructs a data structure based on the
 *  binary skeleton stored in a buffer.
 *
 *  The @c packed_skeleton_iarchive class is an Archiver (as in the
 *  Boost.Serialization library) that can construct the the shape of a
 *  data structure based on a binary skeleton stored in a buffer. The
 *  @c packed_skeleton_iarchive is typically used by the receiver of a
 *  skeleton, to prepare a data structure that will eventually receive
 *  content separately.
 *
 *  Users will not generally need to use @c packed_skeleton_iarchive
 *  directly. Instead, use @c skeleton or @c get_skeleton.
 */
class BOOST_MPI_DECL packed_skeleton_iarchive
  : public detail::ignore_iprimitive,
    public detail::forward_skeleton_iarchive<packed_skeleton_iarchive,packed_iarchive>
{
public:
  /**
   *  Construct a @c packed_skeleton_iarchive for the given
   *  communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  transmitted.
   *
   *  @param flags Control the serialization of the skeleton. Refer to
   *  the Boost.Serialization documentation before changing the
   *  default flags.
   */
  packed_skeleton_iarchive(MPI_Comm const & comm,
                           unsigned int flags =  boost::archive::no_header)
         : detail::forward_skeleton_iarchive<packed_skeleton_iarchive,packed_iarchive>(skeleton_archive_)
         , skeleton_archive_(comm,flags)
        {}

  /**
   *  Construct a @c packed_skeleton_iarchive that unpacks a skeleton
   *  from the given @p archive.
   *
   *  @param archive the archive from which the skeleton will be
   *  unpacked.
   *
   */
  explicit packed_skeleton_iarchive(packed_iarchive & archive)
         : detail::forward_skeleton_iarchive<packed_skeleton_iarchive,packed_iarchive>(archive)
         , skeleton_archive_(MPI_COMM_WORLD, boost::archive::no_header)
        {}

  /**
   *  Retrieve the archive corresponding to this skeleton.
   */
  const packed_iarchive& get_skeleton() const
  {
    return this->implementation_archive;
  }

  /**
   *  Retrieve the archive corresponding to this skeleton.
   */
  packed_iarchive& get_skeleton()
  {
    return this->implementation_archive;
  }

private:
  /// Store the actual archive that holds the structure, unless the
  /// user overrides this with their own archive.
  packed_iarchive skeleton_archive_;
};

/** @brief An archiver that records the binary skeleton of a data
 * structure into a buffer.
 *
 *  The @c packed_skeleton_oarchive class is an Archiver (as in the
 *  Boost.Serialization library) that can record the shape of a data
 *  structure (called the "skeleton") into a binary representation
 *  stored in a buffer. The @c packed_skeleton_oarchive is typically
 *  used by the send of a skeleton, to pack the skeleton of a data
 *  structure for transmission separately from the content.
 *
 *  Users will not generally need to use @c packed_skeleton_oarchive
 *  directly. Instead, use @c skeleton or @c get_skeleton.
 */
class BOOST_MPI_DECL packed_skeleton_oarchive
  : public detail::ignore_oprimitive,
    public detail::forward_skeleton_oarchive<packed_skeleton_oarchive,packed_oarchive>
{
public:
  /**
   *  Construct a @c packed_skeleton_oarchive for the given
   *  communicator.
   *
   *  @param comm The communicator over which this archive will be
   *  transmitted.
   *
   *  @param flags Control the serialization of the skeleton. Refer to
   *  the Boost.Serialization documentation before changing the
   *  default flags.
   */
  packed_skeleton_oarchive(MPI_Comm const & comm,
                           unsigned int flags =  boost::archive::no_header)
         : detail::forward_skeleton_oarchive<packed_skeleton_oarchive,packed_oarchive>(skeleton_archive_)
         , skeleton_archive_(comm,flags)
        {}

  /**
   *  Construct a @c packed_skeleton_oarchive that packs a skeleton
   *  into the given @p archive.
   *
   *  @param archive the archive to which the skeleton will be packed.
   *
   */
  explicit packed_skeleton_oarchive(packed_oarchive & archive)
         : detail::forward_skeleton_oarchive<packed_skeleton_oarchive,packed_oarchive>(archive)
         , skeleton_archive_(MPI_COMM_WORLD, boost::archive::no_header)
        {}

  /**
   *  Retrieve the archive corresponding to this skeleton.
   */
  const packed_oarchive& get_skeleton() const
  {
    return this->implementation_archive;
  }

private:
  /// Store the actual archive that holds the structure.
  packed_oarchive skeleton_archive_;
};


} } // end namespace boost::mpi

#endif // BOOST_MPI_SKELETON_AND_CONTENT_TYPES_HPP

/* skeleton_and_content_types.hpp
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
*/