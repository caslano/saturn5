//  boost/endian/conversion.hpp  -------------------------------------------------------//

//  Copyright Beman Dawes 2010, 2011, 2014

//  Distributed under the Boost Software License, Version 1.0.
//  http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_ENDIAN_CONVERSION_HPP
#define BOOST_ENDIAN_CONVERSION_HPP

#include <boost/endian/detail/endian_reverse.hpp>
#include <boost/endian/detail/endian_load.hpp>
#include <boost/endian/detail/endian_store.hpp>
#include <boost/endian/detail/order.hpp>
#include <boost/type_traits/is_class.hpp>
#include <boost/type_traits/is_array.hpp>
#include <boost/type_traits/integral_constant.hpp>
#include <boost/static_assert.hpp>
#include <boost/cstdint.hpp>
#include <boost/config.hpp>

//------------------------------------- synopsis ---------------------------------------//

namespace boost
{
namespace endian
{

//--------------------------------------------------------------------------------------//
//                                                                                      //
//                             return-by-value interfaces                               //
//                             suggested by Phil Endecott                               //
//                                                                                      //
//                             user-defined types (UDTs)                                //
//                                                                                      //
//  All return-by-value conversion function templates are required to be implemented in //
//  terms of an unqualified call to "endian_reverse(x)", a function returning the       //
//  value of x with endianness reversed. This provides a customization point for any    //
//  UDT that provides a "endian_reverse" free-function meeting the requirements.        //
//  It must be defined in the same namespace as the UDT itself so that it will be found //
//  by argument dependent lookup (ADL).                                                 //
//                                                                                      //
//--------------------------------------------------------------------------------------//

  //  reverse byte order
  //  requires T to be a non-bool integral type
  //  in detail/endian_reverse.hpp
  //
  //  template<class T> inline BOOST_CONSTEXPR T endian_reverse( T x ) BOOST_NOEXCEPT;

  //  reverse byte order unless native endianness is big
  template <class EndianReversible >
    inline BOOST_CONSTEXPR EndianReversible big_to_native(EndianReversible x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is big, otherwise endian_reverse(x)
  template <class EndianReversible >
    inline BOOST_CONSTEXPR EndianReversible native_to_big(EndianReversible x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is big, otherwise endian_reverse(x)

  //  reverse byte order unless native endianness is little
  template <class EndianReversible >
    inline BOOST_CONSTEXPR EndianReversible little_to_native(EndianReversible x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is little, otherwise endian_reverse(x)
  template <class EndianReversible >
    inline BOOST_CONSTEXPR EndianReversible native_to_little(EndianReversible x) BOOST_NOEXCEPT;
    //  Returns: x if native endian order is little, otherwise endian_reverse(x)

  //  generic conditional reverse byte order
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversible>
      inline BOOST_CONSTEXPR EndianReversible conditional_reverse(EndianReversible from) BOOST_NOEXCEPT;
    //  Returns: If From == To have different values, from.
    //           Otherwise endian_reverse(from).
    //  Remarks: The From == To test, and as a consequence which form the return takes, is
    //           is determined at compile time.

  //  runtime conditional reverse byte order
  template <class EndianReversible >
    inline BOOST_CONSTEXPR EndianReversible conditional_reverse(EndianReversible from,
      BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order)
        BOOST_NOEXCEPT;
      //  Returns: from_order == to_order ? from : endian_reverse(from).

  //------------------------------------------------------------------------------------//


  //  Q: What happened to bswap, htobe, and the other synonym functions based on names
  //     popularized by BSD, OS X, and Linux?
  //  A: Turned out these may be implemented as macros on some systems. Ditto POSIX names
  //     for such functionality. Since macros would cause endless problems with functions
  //     of the same names, and these functions are just synonyms anyhow, they have been
  //     removed.


  //------------------------------------------------------------------------------------//
  //                                                                                    //
  //                            reverse in place interfaces                             //
  //                                                                                    //
  //                             user-defined types (UDTs)                              //
  //                                                                                    //
  //  All reverse in place function templates are required to be implemented in terms   //
  //  of an unqualified call to "endian_reverse_inplace(x)", a function reversing       //
  //  the endianness of x, which is a non-const reference. This provides a              //
  //  customization point for any UDT that provides a "reverse_inplace" free-function   //
  //  meeting the requirements. The free-function must be declared in the same          //
  //  namespace as the UDT itself so that it will be found by argument-dependent        //
  //   lookup (ADL).                                                                    //
  //                                                                                    //
  //------------------------------------------------------------------------------------//

  //  reverse in place
  //  in detail/endian_reverse.hpp
  //
  //  template <class EndianReversible>
  //    inline void endian_reverse_inplace(EndianReversible& x) BOOST_NOEXCEPT;
  //
  //  Effects: x = endian_reverse(x)

  //  reverse in place unless native endianness is big
  template <class EndianReversibleInplace>
    inline void big_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is big, otherwise endian_reverse_inplace(x)
  template <class EndianReversibleInplace>
    inline void native_to_big_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is big, otherwise endian_reverse_inplace(x)

  //  reverse in place unless native endianness is little
  template <class EndianReversibleInplace>
    inline void little_to_native_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is little, otherwise endian_reverse_inplace(x);
  template <class EndianReversibleInplace>
    inline void native_to_little_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;
    //  Effects: none if native byte-order is little, otherwise endian_reverse_inplace(x);

  //  generic conditional reverse in place
  template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To,
    class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x) BOOST_NOEXCEPT;

  //  runtime reverse in place
  template <class EndianReversibleInplace>
  inline void conditional_reverse_inplace(EndianReversibleInplace& x,
    BOOST_SCOPED_ENUM(order) from_order,  BOOST_SCOPED_ENUM(order) to_order)
    BOOST_NOEXCEPT;

//----------------------------------- end synopsis -------------------------------------//

template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible big_to_native( EndianReversible x ) BOOST_NOEXCEPT
{
    return boost::endian::conditional_reverse<order::big, order::native>( x );
}

template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible native_to_big( EndianReversible x ) BOOST_NOEXCEPT
{
    return boost::endian::conditional_reverse<order::native, order::big>( x );
}

template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible little_to_native( EndianReversible x ) BOOST_NOEXCEPT
{
    return boost::endian::conditional_reverse<order::little, order::native>( x );
}

template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible native_to_little( EndianReversible x ) BOOST_NOEXCEPT
{
    return boost::endian::conditional_reverse<order::native, order::little>( x );
}

namespace detail
{

template<class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible conditional_reverse_impl( EndianReversible x, boost::true_type ) BOOST_NOEXCEPT
{
    return x;
}

template<class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible conditional_reverse_impl( EndianReversible x, boost::false_type ) BOOST_NOEXCEPT
{
    return endian_reverse( x );
}

} // namespace detail

// generic conditional reverse
template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible conditional_reverse( EndianReversible x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( boost::is_class<EndianReversible>::value || detail::is_endian_reversible<EndianReversible>::value );
    return detail::conditional_reverse_impl( x, boost::integral_constant<bool, From == To>() );
}

// runtime conditional reverse
template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible conditional_reverse( EndianReversible x,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( boost::is_class<EndianReversible>::value || detail::is_endian_reversible<EndianReversible>::value );
    return from_order == to_order? x: endian_reverse( x );
}

//--------------------------------------------------------------------------------------//
//                           reverse-in-place implementation                            //
//--------------------------------------------------------------------------------------//

template <class EndianReversibleInplace>
inline void big_to_native_inplace( EndianReversibleInplace& x ) BOOST_NOEXCEPT
{
    boost::endian::conditional_reverse_inplace<order::big, order::native>( x );
}

template <class EndianReversibleInplace>
inline void native_to_big_inplace( EndianReversibleInplace& x ) BOOST_NOEXCEPT
{
    boost::endian::conditional_reverse_inplace<order::native, order::big>( x );
}

template <class EndianReversibleInplace>
inline void little_to_native_inplace( EndianReversibleInplace& x ) BOOST_NOEXCEPT
{
    boost::endian::conditional_reverse_inplace<order::little, order::native>( x );
}

template <class EndianReversibleInplace>
inline void native_to_little_inplace( EndianReversibleInplace& x ) BOOST_NOEXCEPT
{
    boost::endian::conditional_reverse_inplace<order::native, order::little>( x );
}

namespace detail
{

template<class EndianReversibleInplace>
inline void conditional_reverse_inplace_impl( EndianReversibleInplace&, boost::true_type ) BOOST_NOEXCEPT
{
}

template<class EndianReversibleInplace>
inline void conditional_reverse_inplace_impl( EndianReversibleInplace& x, boost::false_type ) BOOST_NOEXCEPT
{
    endian_reverse_inplace( x );
}

}  // namespace detail

// generic conditional reverse in place
template <BOOST_SCOPED_ENUM(order) From, BOOST_SCOPED_ENUM(order) To, class EndianReversibleInplace>
inline void conditional_reverse_inplace( EndianReversibleInplace& x ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT(
        boost::is_class<EndianReversibleInplace>::value ||
        boost::is_array<EndianReversibleInplace>::value ||
        detail::is_endian_reversible_inplace<EndianReversibleInplace>::value );

    detail::conditional_reverse_inplace_impl( x, boost::integral_constant<bool, From == To>() );
}

// runtime reverse in place
template <class EndianReversibleInplace>
inline void conditional_reverse_inplace( EndianReversibleInplace& x,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT(
        boost::is_class<EndianReversibleInplace>::value ||
        boost::is_array<EndianReversibleInplace>::value ||
        detail::is_endian_reversible_inplace<EndianReversibleInplace>::value );

    if( from_order != to_order )
    {
        endian_reverse_inplace( x );
    }
}

// load/store convenience functions

// load 16

inline boost::int16_t load_little_s16( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int16_t, 2, order::little>( p );
}

inline boost::uint16_t load_little_u16( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint16_t, 2, order::little>( p );
}

inline boost::int16_t load_big_s16( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int16_t, 2, order::big>( p );
}

inline boost::uint16_t load_big_u16( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint16_t, 2, order::big>( p );
}

// load 24

inline boost::int32_t load_little_s24( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int32_t, 3, order::little>( p );
}

inline boost::uint32_t load_little_u24( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint32_t, 3, order::little>( p );
}

inline boost::int32_t load_big_s24( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int32_t, 3, order::big>( p );
}

inline boost::uint32_t load_big_u24( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint32_t, 3, order::big>( p );
}

// load 32

inline boost::int32_t load_little_s32( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int32_t, 4, order::little>( p );
}

inline boost::uint32_t load_little_u32( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint32_t, 4, order::little>( p );
}

inline boost::int32_t load_big_s32( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int32_t, 4, order::big>( p );
}

inline boost::uint32_t load_big_u32( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint32_t, 4, order::big>( p );
}

// load 40

inline boost::int64_t load_little_s40( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 5, order::little>( p );
}

inline boost::uint64_t load_little_u40( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 5, order::little>( p );
}

inline boost::int64_t load_big_s40( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 5, order::big>( p );
}

inline boost::uint64_t load_big_u40( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 5, order::big>( p );
}

// load 48

inline boost::int64_t load_little_s48( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 6, order::little>( p );
}

inline boost::uint64_t load_little_u48( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 6, order::little>( p );
}

inline boost::int64_t load_big_s48( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 6, order::big>( p );
}

inline boost::uint64_t load_big_u48( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 6, order::big>( p );
}

// load 56

inline boost::int64_t load_little_s56( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 7, order::little>( p );
}

inline boost::uint64_t load_little_u56( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 7, order::little>( p );
}

inline boost::int64_t load_big_s56( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 7, order::big>( p );
}

inline boost::uint64_t load_big_u56( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 7, order::big>( p );
}

// load 64

inline boost::int64_t load_little_s64( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 8, order::little>( p );
}

inline boost::uint64_t load_little_u64( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 8, order::little>( p );
}

inline boost::int64_t load_big_s64( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::int64_t, 8, order::big>( p );
}

inline boost::uint64_t load_big_u64( unsigned char const * p ) BOOST_NOEXCEPT
{
    return boost::endian::endian_load<boost::uint64_t, 8, order::big>( p );
}

// store 16

inline void store_little_s16( unsigned char * p, boost::int16_t v )
{
    boost::endian::endian_store<boost::int16_t, 2, order::little>( p, v );
}

inline void store_little_u16( unsigned char * p, boost::uint16_t v )
{
    boost::endian::endian_store<boost::uint16_t, 2, order::little>( p, v );
}

inline void store_big_s16( unsigned char * p, boost::int16_t v )
{
    boost::endian::endian_store<boost::int16_t, 2, order::big>( p, v );
}

inline void store_big_u16( unsigned char * p, boost::uint16_t v )
{
    boost::endian::endian_store<boost::uint16_t, 2, order::big>( p, v );
}

// store 24

inline void store_little_s24( unsigned char * p, boost::int32_t v )
{
    boost::endian::endian_store<boost::int32_t, 3, order::little>( p, v );
}

inline void store_little_u24( unsigned char * p, boost::uint32_t v )
{
    boost::endian::endian_store<boost::uint32_t, 3, order::little>( p, v );
}

inline void store_big_s24( unsigned char * p, boost::int32_t v )
{
    boost::endian::endian_store<boost::int32_t, 3, order::big>( p, v );
}

inline void store_big_u24( unsigned char * p, boost::uint32_t v )
{
    boost::endian::endian_store<boost::uint32_t, 3, order::big>( p, v );
}

// store 32

inline void store_little_s32( unsigned char * p, boost::int32_t v )
{
    boost::endian::endian_store<boost::int32_t, 4, order::little>( p, v );
}

inline void store_little_u32( unsigned char * p, boost::uint32_t v )
{
    boost::endian::endian_store<boost::uint32_t, 4, order::little>( p, v );
}

inline void store_big_s32( unsigned char * p, boost::int32_t v )
{
    boost::endian::endian_store<boost::int32_t, 4, order::big>( p, v );
}

inline void store_big_u32( unsigned char * p, boost::uint32_t v )
{
    boost::endian::endian_store<boost::uint32_t, 4, order::big>( p, v );
}

// store 40

inline void store_little_s40( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 5, order::little>( p, v );
}

inline void store_little_u40( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 5, order::little>( p, v );
}

inline void store_big_s40( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 5, order::big>( p, v );
}

inline void store_big_u40( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 5, order::big>( p, v );
}

// store 48

inline void store_little_s48( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 6, order::little>( p, v );
}

inline void store_little_u48( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 6, order::little>( p, v );
}

inline void store_big_s48( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 6, order::big>( p, v );
}

inline void store_big_u48( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 6, order::big>( p, v );
}

// store 56

inline void store_little_s56( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 7, order::little>( p, v );
}

inline void store_little_u56( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 7, order::little>( p, v );
}

inline void store_big_s56( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 7, order::big>( p, v );
}

inline void store_big_u56( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 7, order::big>( p, v );
}

// store 64

inline void store_little_s64( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 8, order::little>( p, v );
}

inline void store_little_u64( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 8, order::little>( p, v );
}

inline void store_big_s64( unsigned char * p, boost::int64_t v )
{
    boost::endian::endian_store<boost::int64_t, 8, order::big>( p, v );
}

inline void store_big_u64( unsigned char * p, boost::uint64_t v )
{
    boost::endian::endian_store<boost::uint64_t, 8, order::big>( p, v );
}

}  // namespace endian
}  // namespace boost

#endif // BOOST_ENDIAN_CONVERSION_HPP

/* conversion.hpp
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
*/