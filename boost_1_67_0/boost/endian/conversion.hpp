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
#include <boost/type_traits/is_integral.hpp>
#include <boost/type_traits/is_same.hpp>
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

namespace detail
{

template<class T> struct is_endian_reversible: boost::integral_constant<bool,
    boost::is_class<T>::value || ( boost::is_integral<T>::value && !boost::is_same<T, bool>::value )>
{
};

} // namespace detail

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
    BOOST_STATIC_ASSERT( detail::is_endian_reversible<EndianReversible>::value );
    return detail::conditional_reverse_impl( x, boost::integral_constant<bool, From == To>() );
}

// runtime conditional reverse
template <class EndianReversible>
inline BOOST_CONSTEXPR EndianReversible conditional_reverse( EndianReversible x,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( detail::is_endian_reversible<EndianReversible>::value );
    return from_order == to_order? x: endian_reverse( x );
}

//--------------------------------------------------------------------------------------//
//                           reverse-in-place implementation                            //
//--------------------------------------------------------------------------------------//

namespace detail
{

template<class T> struct is_endian_reversible_inplace: boost::integral_constant<bool,
    boost::is_class<T>::value || ( boost::is_integral<T>::value && !boost::is_same<T, bool>::value )>
{
};

} // namespace detail

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
    BOOST_STATIC_ASSERT( detail::is_endian_reversible_inplace<EndianReversibleInplace>::value );
    detail::conditional_reverse_inplace_impl( x, boost::integral_constant<bool, From == To>() );
}

// runtime reverse in place
template <class EndianReversibleInplace>
inline void conditional_reverse_inplace( EndianReversibleInplace& x,
    BOOST_SCOPED_ENUM(order) from_order, BOOST_SCOPED_ENUM(order) to_order ) BOOST_NOEXCEPT
{
    BOOST_STATIC_ASSERT( detail::is_endian_reversible_inplace<EndianReversibleInplace>::value );

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