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
9MKLgJ9s0TIRhnfYW+2ziac7I0+t92Fm+4oZAxL2+1AgNMSqX4LuNljyvQY/gC/+o0//VKvxiVYSAAyEWoP8gaPwObMS6Eu0CsgnH9i0INbmD6CUq0GTM95YlE5VdF3UiImq5qT6iDO4orbFuitVCdzM6B69qphOQcHlyUe1+XQ2zAFWcYCV6WSGmGpj4uHuLJnkZNGQpm+cT0VeBhrLOnoCKATAl8pMOPYtTZf39xo9SiBX67YB8G3WSmuGmfd86oY6iZzVw3D2NIRSn9TCZFqRHE2xPrqWuV1PVn2Nvg/PEtcQMsRcgEgQT+gBy4LT38t0DvixmPZpGDNc6uuu+lmOvGOyNIVVU1IV0RomU9TDDn07Utp3LzDs77l+MGmws2+RWV9G7QHsCr2f+D/LMWpoIV/eCCbL3bBPjdxxQ0r8X6VJjULY6T6esvkSwlKYDpEe5UXZgIGBy9UVQT9sxrGcjTgs3guyIgCMJpVUzB4ckTcAO4iHss0SUgeixe1aAIn20B1c/36urrooKyAWfdkoA0VaFNIojh80lEwaOaZmdiezUtQEBY7KV8i6Kt8koFgya9gmvGB/YKZBGRoqcSI22lIkRicUhbXvPWu09QZNnoOCvHacnIZTFvGzBFmp6u9366lHXiOIiUftv9vq3+Txrou3UI5WIqUZxA77xxaG75VZXSqr+2D4p9/iwNC/Kc8p5CUwtSQ4LlWxx7cHBkt7RGok7N2dtt1hBOcFNllWxPquL4/CKuOzapSHuRwpZBrQR1HQyhzmJiWXpp2ZEkcTRVC+w+co9SjqTZXkIQltOVHG7I1KItMlH/I5H4QPzgmX4r9xUpKIJb/b91DEv9DLs4zM2E6e7vlF8uB4bxXnY4ijMALg8kv4eGTgVtTZiePdnlMBMxV+RPoSvZ7aj+nCigIzz/YbwRPZoPl4bL+Oeh4xdoc/JuPt75LTBhRXIvihkx+PPoffxBBa7u+ddrf4wnzZ/Xq6nVa/Peq09SVKSDQMEDe9vfUKQhBWlWlnTwiE+ZNr1klkqfImOb8/UStic93P9ux7D9AR1I9YVSBCjRZ1t9NawNectJDJouP9tpGGUO1C6tzpF+9RbsW1zeNKO8rPaD83bsdM8OkBSCdfWMrhYEtEJZgACDqrmLgaODhhOHUxeXu5nKSJSTczoV6GB+UEtwTELK6LzSG8wGiLvUcNaFjlW3PNI/cCXLfjvU7e6ld9PnzafY+FDr1RG/oxI0mAsuN1jNhoCURxfvWm65JEPKC5Gk8clCMnp3c50rK49ZE5WMTh02O4o20GcWwgkQhPX2oWfnJBvVUQ01Ej6oBAKGu+gb8IXWbdR37klrLQAZxAQpiJ5VS7xbiciDDxoqq4Yv2BOigBPnzXlbYyn4qDdde3rtsr93I5jf4QUUUUZFyOgmiXgrLwhZyRJlWgj7L3PIq+T/9FCvenfyfri7VSoeB5Z8OmN0p3N/nXoqvoScGRrte6rX7dJPrHaTAb+Hc8j3O7aWM6NtpmPM65Fb2zT89rhqR6Qi8XOXhpL1z2jKEtppMW05EG8ScJN+AUJh2NMSdieM6G9sVzdcHXj8N8pPegu2c7bschU734+lxxfb16HVv7DyJAwagi74vM7poUkVWDWArS6ZOBzEuN+m+rv52PQlI0pqA/oFH6zUEH4A8r+TD25WMNmSjqBTC0Tt9HJsFEUqWXoNw/bAM5OMfxLnDAYNeXBCASh8uPE9kjla5gDZB+VhBq4djjexqJYz+vvDIRyX7xhn+6wnUiT+8u+Cw45c42Yzs2EIslKIgMxNKmRxTYjf1Rad/HISCTnVCIYSoWllwa+QKWINxp5RBj1Xtr0dtYeO1jAg1MTGkrW8QtdoBhAs3KBX5L2WD3qDusdapLq9EfEJ83czBIm9yGPhEMcVsBB2o7AdhNalGCBcBk7iChkUAr8xP8qffgYlZN8fHNHfTlZAGMqh017gJcOm/jn4JPQJU8A2aFr5A4FtgrKLkV23PI8B+oOCNtAmv1AYBkQXsB1wJQ2rYPxEyV/zBqS+Zrrn4x2lQSIgfYC1X4nmiFPmpEq9kcmMPtoglUZhzIwKn+UsgRwSC38xFOANM8QFdnjWtbyeQwaXjTIvslSEuJKEfHyVX1ea3TFM5LixvmhvnqmcwIyfAqcxT3se/r/LllvA6uoSq5GleXvQKZWFPJfgUS7ih6i+1LDw0UwjZC+V126D5q3XjiGzw+dBzyNU2pgJdrLsKF5z4S0I0iPUHDJTfQ8CnBUGyplQZ/hKPSSKpF1lsHCnVAbsdKAyV7HNBL3RbXVkaHPRNgqobQn3gbdDhmVORO9MWUK/lfP70l08cbdnAR5V7R9AGoRjp5nh8CTTbbxuVX85cy+8aoQ2bLd6jvpUXq/n7tv3RA7yQTxmzNiIuw7dNqXew43qvEM7p56K31up3ZLurGm6T07ksdGBMI5avBbWn8iixfpw/yt01KM73K8yEIUMnz61kzRKThoonM6xK7hnisx51RDBRtdKEKlD+FA5z5vadBIhb8aWx+uh1P2GO4BVjC6xjCGx1kFqhxz0CD8SYZUNHie9KBOFE6fRQuMQRAxIgTgtXV3yTIGEZ7XRTMlmSwDp8bJTnPlkfwH6DV05a520IJ/7Pzrzcj6mLisHGZLV0TY7CDDIIqhPtGGoBfPYwltu+JqaCLSmtW9API/vgbgv+1AMFn+ZgOXKjskod69NPk4WMGVElENK+/gDiixJAfLSsdS6ib8KhWIJAwxOTsRdPTsNWgYGu/kwH+3U5J07efas3JBFnNiqHwMX5ZCaf0gSHqKD+SiHce0uL6RpLcvX2AT5cVZ/sfjXJMj7YBsDZyct63JaO0greNcSEpoXHN3L78UHPb/d1LFt3vlkS0lpCAxfZBmCHhii+qxSsfUWEw//KGqUhcEwNU7dRkkFtrTfP4tJqt3hzj55cC0enL0YJ6pab/SJxPOgogklWGyU/fPsqAM7jCbR6psKjP+gRBSAGETFNzXVlADYFfHYKsn90Xp1vAprUZuE6IBjjH4xMYLX2sHT/lhG1szwTevxcwB3q3Z67cn7BznHskUJc0/Kb1egWGqs1hG1M3s1LxKRQZPwGByc1Pb7wpnCweZ7oxQSleGgFRkNVhtBSZQwlSmtLEQydxNKDa6n4gj3JomW/tI0ODP6EXj63UciifvbOfBE2txEmw7h7gDxf/5x3HPf14lO4VcpfXR/x5pu46wCl+QKQQr2OBBOpb99bQxiueHm6AVDkcMLBK/UZR/w6OVG8rpopq2P5Ju8a1aoUMIzk4Fh4/wetsYkJp1+jjKL8EV0Pb5doD5HWv7pmXX/aUL86Li+sbsQGiDd6KvsCdvBBf5tVJHy8gVDa3wQW4puEL0DLeS7xUf5HyIQKZKuIISjOXSR3EI4FVdYY3eu7G4y6xFn9KJDwtZg+MHzOIXqckTgwQH70C8gdm3UjdIIv3BbBGL7pHL1NplfCfIYMxQc4DXZPCMq2RWD+HwzM/Yddu7i8RRwsLMf6EIgjamoT25sgQzQ150DSagUlI39AxXARrEYYnpIgpveA6/td254UW/Wnk0QttOT0bf4IxHGyjS+TkR0YnK1MVeQj0NJhaQXsj2yq264RwBmfMNERmTZAfHsE0ywd+Z5jex5YbgmOOOoIW5DQ1B9Hzvg0YEbP+KvZh8mtSaQwJJnWvorR+Qr4JsfRRfMp36v7awYbkS2vm85G9X/suDGacJzY0np+DhZaKb/+o4JHpd/fbrOSEG7e5xwaJ5fCWhpNZUAWI5zJlYQ6Fquz1iCOswWHnqVupAA6dOWZRwYiejx67HAZVrQmMcCCg4rciEaUQBSjA9nPLx9w26t7UmkG/lcovHNwu5/T6ZYI+6TDC62NdmkArNoTaHNqfABdVIrVnENVtjsONv4XvZCZZqknSNYQQ9zYO2dBBdpWKAf5TLV9MFmpC3XojCe70HAOmCYMs2RR4dB2Qojzqu11kFIszKn/YISUNp1d5xQcK+VFIaZUdCIePm5WLcHwW1pFAz0oNWixQiIFFqUK2VV4aDclpS3GqdKGoGiygYNIzgObAkVf14jwAefZ1kf/Kn83iS1kZk5cHng6+HVHutci+H9zjMoL3iATlUJ/8X019We6cyfZAOE3aPS9GvsTKQd8LvKuuT11Ki+c03yyOMEOuzgO/vk9lsYav7zSnnR4b7H7ejQDclPFe7bFarO30tsNHwCgu9gskOMmaphtNcITQfDQEG99QTR8IysfYdRQdAILniyTh8mwusDFNPaOr3GiGHcSdu5ohQTskmf8HTddJwkc4JwEj/Rx+3nNWI1TChW6ts5Ki4JxQKVTVVJQDsRg3LlURSJLUxv7UWVXEVHZ5rLpZGXf4pltq2ovfVV5gMHQHpaj2Z1WUSIV0JEMNY4MMeM5WX4au8Oz3/DAFMS4puPbRD6WWmNGCkWTKY7bMmyIFmI/sVaZUhdwZmLuFnFdBqbCvnjXL9aGLPYjmmOP72Vn8+VYuk460SEQ6DNhDCX4VUdOnF6SRhIpmBZIsArjgf2KaAtHZQL2k29Yd6CyHQWUHQdT8Apxkd9TP4YhNEAZgDJB9ZfKD0L7Ndrh3gsZ130urdFy9Xup1QcU9V2UNjxUy14Ud8MkhuNzCu9K1C5T/C0zG2U4kjyS+KAqOqooLw4WPXkK2yyEhajFzh3VdkgsaBij9Znv/7gI9y2BwD7FtEJSQnnppG60p4dSMYrWHwKSUYX3ajaK4sQdnvCwP1Nmb7rQ3B8yi3PBjKk9iMJbYtsIK4LK3r/m4lG9GjaO9BsVuaSnjDS027yycm9jf+9N+e23jLV7bcMo49aO7mlGaVHLLfdg/1MDZHf9mVDJ5jAtV1/X6Ceu84jmKa6rjXW7oNOxYCualpHIND0tqYGkptupf2ofZKm8zIoADH1cN+V2XpoCnJnwoVLk/7DTN6wma8ksYn3vnMjXfOzYRj0pi6m/9tusrnQpU75f6/ZABOrW+TT/MRlyuLoG91HGLrr88np4eGpxWPav7NfihP2K/JMc32niPyIx6Bn283w+XFFGi8owPKV48G3bz3sesoX0li8vGnYHkqm5jIR40VU4LK7MWd5D7LILRt/VWUImxZKPY3Y0CXo4ZdMdlJM/jjzho3IrcfSND9vr0N7M/8tbYL05RpHecAD30aSSnWG3hiYDIteqpyz7a394NdQEEmcXwRC/+Jp3EXdjlNHbARMNRRo8u2TszH4VoXuJoTzKIZfFe/OxdU0IlD09R+MpOwduchwK/FKYaSejnqBdLYHCpGlcWY0x8fJP8vdBSynnJivkD9mINeMCU81fXwc3rauM3J8Jgj9Q7h2a5gIKVvcUbG3zclEVS6n4JO0Gg3nx69aiys3Eml2ve2W6KodZGOqwtNM2n//qnjhhZocdzFtp6uDE2Q7bPMNkYQwd4ByNUys1WpXFYPP98yerUW83Jp0r9er012CWKKP5YZrkU6aJD93TqbQEzWDLosfCsZuIQQSSQgpejGgHF+YzKQZQok2/5Ion0+tJk6VxQecJ7W4as4ASAh5z02s/YJ0qbyqAqsRBiisqGw3MJlwhIhltEBlL1ps8Sr9iQWkXSFT7/rxhmGTCCCm6qiLxhIEOE+wxnGpuZlmetBFSmDqpyIft5aCdtonKHpBMCOlPwbx15IOpghbX8U9zNfZ/fINNcOilcF1Yueeq+VtSUt1Blt3tJDR0Yki/1KE9GaBeKxZ/BXvUWpyc7Z9i+EbSP/4g8pqZTS658XxgrLyVRmC75nU1VmFla0UCrfqjYaXzRTp9NNIulKMYK/VFZ5Uty1C5nSmZMwDcX/6PG6fzHr9JY/EjwLrQA74Qq8dV01Jt3WlXIs0kmGP+TAZRozWOjKvig5wUuTRqNsvNw58Cbjux9q6DWysur9uKyvCSuy2i0H+ZHhEZujiPTrY5HRf8vN3SqC84MvNQ7jb9ASldQlyqnrn+OR4+0z5vHK/R/V+vRZWe5q6FdIDx2mxMxzt13BapgHq3K8Smg82B/VVkVYBRIaHSqOa1JXLJSNJarSnSXIVNzCs2UNOIqtg2AXEeIQHqxiJy9JUKHbsR1ul8RNCvNNyiN+TFIngIMSdNeADwRryau+pBjm270EgEZzlCJMtktquqpkh19ahXk3Oskp9+i0E+ZH4juX85MFUClhcbEqM+OLf+K3UJW3Pz6HpJsHEJI6+AKEx56Q34MK8MSdtvyhyU4FVMdF33XPVbJhbQuTKZu+UJmEoWq7+5k7A3cm5Nl7wkIsDSjC4Dp9511/0Wpvm1s4eH0c1yIYBgsZqQR1zzbJjwFG69NiMhDQ6lRccerZM/GPPAOv2fdvXIcDdAYELb7yhJ1/fL1j3hDQdoYz76xHV/lKaKPk63sj1OLcju3JL9V1F7T1amrbwW9GAvRQouMVCJf4vO0uuaVkF9T+JZ3nm6vkl+uQ1LK5Et9nt30V/r87UEMHs5y4sHF5J+PE6oI0wiYNqgUOKGnwatORcurFuFybzIFHUEhoerMiOQcUoGMoNDUCdat0x0xLO6VYFkrVGAUkoGNnQ6LwtEpoUYLBEw0wO8563r2O98P0TSZ77efvocnIYUqBY5IZ29zDtKlPbf82m2P3oerRrOCLC2H9S5+frb7zo2cG5N3xEiafF32gswH4VqiagkyNLUUCK7QkX6EWDCCIUbcixklUntupbH8mSbnUjmLaEqrTkvfIGs9aP3SxyW+F6nw/DYAHr06mv80mWzwaN7p6OE1qYvYtgeGOhccygmc6rCuOBzRdEWq49KKOma9SYoW90AKztv2LZNLqpw6VSVjY7WDCPhjnqCitM3ExZfEnJyxw1Irg//y7NC8D9q/9fOYNSdSTSTimakuPJQAHt3zqSwcjWfZLwfXPY/1eof8H+BfDxxfS35uyA62QUbAa0mHCbcevmN9pdkxXZAgRuYHiN7Z1jT2DrIs+Sm2dnnuiqK18afS8f0kPOZiWRWaJAYqz92/kdRj+OF8MQolQIFA8NeO+7kyovLvj5phpcFnXMNeD0aBPJUvnuC0fnW47Ch4wGWe5JIrjDnkA9yQcrTVagCYo7fifn93F/j/XzLBsqr/sUmpD8fFqnPehKsYoUERKZ1YU+j8eyQfANDSKK6csIySlHydww6KfLdpskqjrAmzJ7qUD0ArFefHbfT3+moYKpMIZDudsBveHQUYD6BcV0KL3o8NNxtteW9kddNvctoDoNUfkSowRbFRUszQ5ER81NRdF/NFexKdaiSUunNjicQb7/3L9ZZm1j+NvgD5zFjlJtX8bxu2C2KvVgKPxTBPzcyuhlRl/ry6RdD3qf1YnS7p8lwH+XSTY1MsvbQGeNcK5wORYXCW3vWxfUzuPQIMeUfNyNp8L8Yi5g+ItfmK8WZi0wjNoCwl7I5QwSAgbekrrdcpA67G8dCC4uvQkzsovoiZ6bzfOwQRyzrgJuPPOt91yWLghNTy0Bc0aI/SXd0+0c26TLbv9xLAEv8AF55W6GJgzy0YTVrRYtElOp4qHYVVpyuhCpcEtpE9y7UApjMuaaJtX5L9yvatIsPz+nh319JjBdRliEW48XvDt5MYPetq2h/xEpaxSKxXSs7KVn1ZOdiYhN7orjamTwAG
*/