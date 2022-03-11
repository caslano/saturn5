// Copyright 2004 The Trustees of Indiana University.
// Copyright 2005 Matthias Troyer.
// Copyright 2006 Douglas Gregor <doug.gregor -at- gmail.com>.

// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

//  Authors: Douglas Gregor
//           Andrew Lumsdaine
//           Matthias Troyer

/** @file datatype.hpp
 *
 *  This header provides the mapping from C++ types to MPI data types.
 */
#ifndef BOOST_MPI_DATATYPE_HPP
#define BOOST_MPI_DATATYPE_HPP

#include <boost/mpi/config.hpp>
#include <boost/mpi/datatype_fwd.hpp>
#include <mpi.h>
#include <boost/config.hpp>
#include <boost/mpl/bool.hpp>
#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpi/detail/mpi_datatype_cache.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/archive/basic_archive.hpp>
#include <boost/serialization/item_version_type.hpp>
#include <utility> // for std::pair

#if defined(__cplusplus) && (201103L <= __cplusplus) 
#include <array>
#endif

namespace boost { namespace mpi {

/**
 *  @brief Type trait that determines if there exists a built-in
 *  integer MPI data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI data type that is classified as an integer data
 *  type. See @c is_mpi_builtin_datatype for general information about
 *  built-in MPI data types.
 */
template<typename T>
struct is_mpi_integer_datatype
  : public boost::mpl::false_ { };

/**
 *  @brief Type trait that determines if there exists a built-in
 *  floating point MPI data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI data type that is classified as a floating
 *  point data type. See @c is_mpi_builtin_datatype for general
 *  information about built-in MPI data types.
 */
template<typename T>
struct is_mpi_floating_point_datatype
  : public boost::mpl::false_ { };

/**
 *  @brief Type trait that determines if there exists a built-in
 *  logical MPI data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI data type that is classified as an logical data
 *  type. See @c is_mpi_builtin_datatype for general information about
 *  built-in MPI data types.
 */
template<typename T>
struct is_mpi_logical_datatype
  : public boost::mpl::false_ { };

/**
 *  @brief Type trait that determines if there exists a built-in
 *  complex MPI data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI data type that is classified as an complex data
 *  type. See @c is_mpi_builtin_datatype for general information about
 *  built-in MPI data types.
 */
template<typename T>
struct is_mpi_complex_datatype
  : public boost::mpl::false_ { };

/**
 *  @brief Type trait that determines if there exists a built-in
 *  byte MPI data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI data type that is classified as an byte data
 *  type. See @c is_mpi_builtin_datatype for general information about
 *  built-in MPI data types.
 */
template<typename T>
struct is_mpi_byte_datatype
  : public boost::mpl::false_ { };

/** @brief Type trait that determines if there exists a built-in MPI
 *  data type for a given C++ type.
 *
 *  This type trait determines when there is a direct mapping from a
 *  C++ type to an MPI type. For instance, the C++ @c int type maps
 *  directly to the MPI type @c MPI_INT. When there is a direct
 *  mapping from the type @c T to an MPI type, @c
 *  is_mpi_builtin_datatype will derive from @c mpl::true_ and the MPI
 *  data type will be accessible via @c get_mpi_datatype. 
 *
 *  In general, users should not need to specialize this
 *  trait. However, if you have an additional C++ type that can map
 *  directly to only of MPI's built-in types, specialize either this
 *  trait or one of the traits corresponding to categories of MPI data
 *  types (@c is_mpi_integer_datatype, @c
 *  is_mpi_floating_point_datatype, @c is_mpi_logical_datatype, @c
 *  is_mpi_complex_datatype, or @c is_mpi_builtin_datatype). @c
 *  is_mpi_builtin_datatype derives @c mpl::true_ if any of the traits
 *  corresponding to MPI data type categories derived @c mpl::true_.
 */
template<typename T>
struct is_mpi_builtin_datatype
  : boost::mpl::or_<is_mpi_integer_datatype<T>,
                    is_mpi_floating_point_datatype<T>,
                    is_mpi_logical_datatype<T>,
                    is_mpi_complex_datatype<T>,
                    is_mpi_byte_datatype<T> >
{
};

/** @brief Type trait that determines if a C++ type can be mapped to
 *  an MPI data type.
 *
 *  This type trait determines if it is possible to build an MPI data
 *  type that represents a C++ data type. When this is the case, @c
 *  is_mpi_datatype derives @c mpl::true_ and the MPI data type will
 *  be accessible via @c get_mpi_datatype.

 *  For any C++ type that maps to a built-in MPI data type (see @c
 *  is_mpi_builtin_datatype), @c is_mpi_data_type is trivially
 *  true. However, any POD ("Plain Old Data") type containing types
 *  that themselves can be represented by MPI data types can itself be
 *  represented as an MPI data type. For instance, a @c point3d class
 *  containing three @c double values can be represented as an MPI
 *  data type. To do so, first make the data type Serializable (using
 *  the Boost.Serialization library); then, specialize the @c
 *  is_mpi_datatype trait for the point type so that it will derive @c
 *  mpl::true_:
 *
 *    @code
 *    namespace boost { namespace mpi {
 *      template<> struct is_mpi_datatype<point>
 *        : public mpl::true_ { };
 *    } }
 *    @endcode
 */
template<typename T>
struct is_mpi_datatype
 : public is_mpi_builtin_datatype<T>
{
};

/** @brief Returns an MPI data type for a C++ type.
 *
 *  The function creates an MPI data type for the given object @c
 *  x. The first time it is called for a class @c T, the MPI data type
 *  is created and cached. Subsequent calls for objects of the same
 *  type @c T return the cached MPI data type.  The type @c T must
 *  allow creation of an MPI data type. That is, it must be
 *  Serializable and @c is_mpi_datatype<T> must derive @c mpl::true_.
 *
 *  For fundamental MPI types, a copy of the MPI data type of the MPI
 *  library is returned.
 *
 *  Note that since the data types are cached, the caller should never
 *  call @c MPI_Type_free() for the MPI data type returned by this
 *  call.
 *
 *  @param x for an optimized call, a constructed object of the type
 *  should be passed; otherwise, an object will be
 *  default-constructed.
 *
 *  @returns The MPI data type corresponding to type @c T.
 */
template<typename T> MPI_Datatype get_mpi_datatype(const T& x)
{
  BOOST_MPL_ASSERT((is_mpi_datatype<T>));
  return detail::mpi_datatype_cache().datatype(x);
}

// Don't parse this part when we're generating Doxygen documentation.
#ifndef BOOST_MPI_DOXYGEN

/// INTERNAL ONLY
#define BOOST_MPI_DATATYPE(CppType, MPIType, Kind)                      \
template<>                                                              \
inline MPI_Datatype                                                     \
get_mpi_datatype< CppType >(const CppType&) { return MPIType; }         \
                                                                        \
template<>                                                              \
 struct BOOST_JOIN(is_mpi_,BOOST_JOIN(Kind,_datatype))< CppType >       \
: boost::mpl::true_                                                     \
{}

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(packed, MPI_PACKED, builtin);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(char, MPI_CHAR, builtin);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(short, MPI_SHORT, integer);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(int, MPI_INT, integer);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(long, MPI_LONG, integer);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(float, MPI_FLOAT, floating_point);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(double, MPI_DOUBLE, floating_point);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(long double, MPI_LONG_DOUBLE, floating_point);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(unsigned char, MPI_UNSIGNED_CHAR, builtin);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(unsigned short, MPI_UNSIGNED_SHORT, integer);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(unsigned, MPI_UNSIGNED, integer);

/// INTERNAL ONLY
BOOST_MPI_DATATYPE(unsigned long, MPI_UNSIGNED_LONG, integer);

/// INTERNAL ONLY
#define BOOST_MPI_LIST2(A, B) A, B
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(float, int)>, MPI_FLOAT_INT, 
                   builtin);
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(double, int)>, MPI_DOUBLE_INT, 
                   builtin);
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(long double, int)>,
                   MPI_LONG_DOUBLE_INT, builtin);
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(long, int>), MPI_LONG_INT, 
                   builtin);
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(short, int>), MPI_SHORT_INT, 
                   builtin);
/// INTERNAL ONLY
BOOST_MPI_DATATYPE(std::pair<BOOST_MPI_LIST2(int, int>), MPI_2INT, builtin);
#undef BOOST_MPI_LIST2

/// specialization of is_mpi_datatype for pairs
template <class T, class U>
struct is_mpi_datatype<std::pair<T,U> >
 : public mpl::and_<is_mpi_datatype<T>,is_mpi_datatype<U> >
{
};

/// specialization of is_mpi_datatype for arrays
#if defined(__cplusplus) && (201103L <= __cplusplus)
template<class T, std::size_t N>
struct is_mpi_datatype<std::array<T, N> >
 : public is_mpi_datatype<T>
{
};
#endif

// Define wchar_t specialization of is_mpi_datatype, if possible.
#if !defined(BOOST_NO_INTRINSIC_WCHAR_T) && \
  (defined(MPI_WCHAR) || (BOOST_MPI_VERSION >= 2))
BOOST_MPI_DATATYPE(wchar_t, MPI_WCHAR, builtin);
#endif

// Define long long or __int64 specialization of is_mpi_datatype, if possible.
#if defined(BOOST_HAS_LONG_LONG) && \
  (defined(MPI_LONG_LONG_INT) || (BOOST_MPI_VERSION >= 2))
BOOST_MPI_DATATYPE(long long, MPI_LONG_LONG_INT, builtin);
#elif defined(BOOST_HAS_MS_INT64) && \
  (defined(MPI_LONG_LONG_INT) || (BOOST_MPI_VERSION >= 2))
BOOST_MPI_DATATYPE(__int64, MPI_LONG_LONG_INT, builtin); 
#endif

// Define unsigned long long or unsigned __int64 specialization of
// is_mpi_datatype, if possible. We separate this from the check for
// the (signed) long long/__int64 because some MPI implementations
// (e.g., MPICH-MX) have MPI_LONG_LONG_INT but not
// MPI_UNSIGNED_LONG_LONG.
#if defined(BOOST_HAS_LONG_LONG) && \
  (defined(MPI_UNSIGNED_LONG_LONG) \
   || (BOOST_MPI_VERSION >= 2))
BOOST_MPI_DATATYPE(unsigned long long, MPI_UNSIGNED_LONG_LONG, builtin);
#elif defined(BOOST_HAS_MS_INT64) && \
  (defined(MPI_UNSIGNED_LONG_LONG) \
   || (BOOST_MPI_VERSION >= 2))
BOOST_MPI_DATATYPE(unsigned __int64, MPI_UNSIGNED_LONG_LONG, builtin); 
#endif

// Define signed char specialization of is_mpi_datatype, if possible.
#if defined(MPI_SIGNED_CHAR) || (BOOST_MPI_VERSION >= 2)
BOOST_MPI_DATATYPE(signed char, MPI_SIGNED_CHAR, builtin);
#endif


#endif // Doxygen

namespace detail {
  inline MPI_Datatype build_mpi_datatype_for_bool()
  {
    MPI_Datatype type;
    MPI_Type_contiguous(sizeof(bool), MPI_BYTE, &type);
    MPI_Type_commit(&type);
    return type;
  }
}

/// Support for bool. There is no corresponding MPI_BOOL.
/// INTERNAL ONLY
template<>
inline MPI_Datatype get_mpi_datatype<bool>(const bool&)
{
  static MPI_Datatype type = detail::build_mpi_datatype_for_bool();
  return type;
}

/// INTERNAL ONLY
template<>
struct is_mpi_datatype<bool>
  : boost::mpl::bool_<true>
{};


#ifndef BOOST_MPI_DOXYGEN
// direct support for special primitive data types of the serialization library
BOOST_MPI_DATATYPE(boost::archive::library_version_type, get_mpi_datatype(uint_least16_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::version_type, get_mpi_datatype(uint_least8_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::class_id_type, get_mpi_datatype(int_least16_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::class_id_reference_type, get_mpi_datatype(int_least16_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::class_id_optional_type, get_mpi_datatype(int_least16_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::object_id_type, get_mpi_datatype(uint_least32_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::object_reference_type, get_mpi_datatype(uint_least32_t()), integer);
BOOST_MPI_DATATYPE(boost::archive::tracking_type, get_mpi_datatype(bool()), builtin);
BOOST_MPI_DATATYPE(boost::serialization::collection_size_type, get_mpi_datatype(std::size_t()), integer);
BOOST_MPI_DATATYPE(boost::serialization::item_version_type, get_mpi_datatype(uint_least8_t()), integer);
#endif // Doxygen


} } // end namespace boost::mpi

// direct support for special primitive data types of the serialization library
// in the case of homogeneous systems
// define a macro to make explicit designation of this more transparent
#define BOOST_IS_MPI_DATATYPE(T)              \
namespace boost {                             \
namespace mpi {                               \
template<>                                    \
struct is_mpi_datatype< T > : mpl::true_ {};  \
}}                                            \
/**/


#endif // BOOST_MPI_MPI_DATATYPE_HPP

/* datatype.hpp
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
*/