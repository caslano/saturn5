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
 *  C++ type to an MPI data type that is classified as a complex data
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