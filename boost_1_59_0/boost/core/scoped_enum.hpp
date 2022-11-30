//  scoped_enum.hpp  ---------------------------------------------------------//

//  Copyright Beman Dawes, 2009
//  Copyright (C) 2011-2012 Vicente J. Botet Escriba
//  Copyright (C) 2012 Anthony Williams

//  Distributed under the Boost Software License, Version 1.0.
//  See http://www.boost.org/LICENSE_1_0.txt

#ifndef BOOST_CORE_SCOPED_ENUM_HPP
#define BOOST_CORE_SCOPED_ENUM_HPP

#include <boost/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost
{

#ifdef BOOST_NO_CXX11_SCOPED_ENUMS

  /**
   * Meta-function to get the native enum type associated to an enum class or its emulation.
   */
  template <typename EnumType>
  struct native_type
  {
    /**
     * The member typedef type names the native enum type associated to the scoped enum,
     * which is it self if the compiler supports scoped enums or EnumType::enum_type if it is an emulated scoped enum.
     */
    typedef typename EnumType::enum_type type;
  };

  /**
   * Casts a scoped enum to its underlying type.
   *
   * This function is useful when working with scoped enum classes, which doens't implicitly convert to the underlying type.
   * @param v A scoped enum.
   * @returns The underlying type.
   * @throws No-throws.
   */
  template <typename UnderlyingType, typename EnumType>
  inline
  BOOST_CONSTEXPR UnderlyingType underlying_cast(EnumType v) BOOST_NOEXCEPT
  {
    return v.get_underlying_value_();
  }

  /**
   * Casts a scoped enum to its native enum type.
   *
   * This function is useful to make programs portable when the scoped enum emulation can not be use where native enums can.
   *
   * EnumType the scoped enum type
   *
   * @param v A scoped enum.
   * @returns The native enum value.
   * @throws No-throws.
   */
  template <typename EnumType>
  inline
  BOOST_CONSTEXPR typename EnumType::enum_type native_value(EnumType e) BOOST_NOEXCEPT
  {
    return e.get_native_value_();
  }

#else  // BOOST_NO_CXX11_SCOPED_ENUMS

  template <typename EnumType>
  struct native_type
  {
    typedef EnumType type;
  };

  template <typename UnderlyingType, typename EnumType>
  inline
  BOOST_CONSTEXPR UnderlyingType underlying_cast(EnumType v) BOOST_NOEXCEPT
  {
    return static_cast<UnderlyingType>(v);
  }

  template <typename EnumType>
  inline
  BOOST_CONSTEXPR EnumType native_value(EnumType e) BOOST_NOEXCEPT
  {
    return e;
  }

#endif // BOOST_NO_CXX11_SCOPED_ENUMS
}


#ifdef BOOST_NO_CXX11_SCOPED_ENUMS

#ifndef BOOST_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS

#define BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR \
     explicit BOOST_CONSTEXPR operator underlying_type() const BOOST_NOEXCEPT { return get_underlying_value_(); }

#else

#define BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR

#endif

/**
 * Start a declaration of a scoped enum.
 *
 * @param EnumType The new scoped enum.
 * @param UnderlyingType The underlying type.
 */
#define BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType, UnderlyingType)    \
    struct EnumType {                                                   \
        typedef void is_boost_scoped_enum_tag;                          \
        typedef UnderlyingType underlying_type;                         \
        EnumType() BOOST_NOEXCEPT {}                                    \
        explicit BOOST_CONSTEXPR EnumType(underlying_type v) BOOST_NOEXCEPT : v_(v) {}                 \
        BOOST_CONSTEXPR underlying_type get_underlying_value_() const BOOST_NOEXCEPT { return v_; }    \
        BOOST_SCOPED_ENUM_UT_DECLARE_CONVERSION_OPERATOR                \
    private:                                                            \
        underlying_type v_;                                             \
        typedef EnumType self_type;                                     \
    public:                                                             \
        enum enum_type

#define BOOST_SCOPED_ENUM_DECLARE_END2() \
        BOOST_CONSTEXPR enum_type get_native_value_() const BOOST_NOEXCEPT { return enum_type(v_); } \
        friend BOOST_CONSTEXPR bool operator ==(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)==enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator ==(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)==rhs; } \
        friend BOOST_CONSTEXPR bool operator ==(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs==enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator !=(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)!=enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator !=(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)!=rhs; } \
        friend BOOST_CONSTEXPR bool operator !=(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs!=enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator <(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)<enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator <(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)<rhs; } \
        friend BOOST_CONSTEXPR bool operator <(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs<enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator <=(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)<=enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator <=(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)<=rhs; } \
        friend BOOST_CONSTEXPR bool operator <=(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs<=enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator >(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)>enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator >(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)>rhs; } \
        friend BOOST_CONSTEXPR bool operator >(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs>enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator >=(self_type lhs, self_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)>=enum_type(rhs.v_); } \
        friend BOOST_CONSTEXPR bool operator >=(self_type lhs, enum_type rhs) BOOST_NOEXCEPT { return enum_type(lhs.v_)>=rhs; } \
        friend BOOST_CONSTEXPR bool operator >=(enum_type lhs, self_type rhs) BOOST_NOEXCEPT { return lhs>=enum_type(rhs.v_); } \
    };

#define BOOST_SCOPED_ENUM_DECLARE_END(EnumType) \
    ; \
    BOOST_CONSTEXPR EnumType(enum_type v) BOOST_NOEXCEPT : v_(v) {}                 \
    BOOST_SCOPED_ENUM_DECLARE_END2()

/**
 * Starts a declaration of a scoped enum with the default int underlying type.
 *
 * @param EnumType The new scoped enum.
 */
#define BOOST_SCOPED_ENUM_DECLARE_BEGIN(EnumType) \
  BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType,int)

/**
 * Name of the native enum type.
 *
 * @param EnumType The new scoped enum.
 */
#define BOOST_SCOPED_ENUM_NATIVE(EnumType) EnumType::enum_type
/**
 * Forward declares an scoped enum.
 *
 * @param EnumType The scoped enum.
 */
#define BOOST_SCOPED_ENUM_FORWARD_DECLARE(EnumType) struct EnumType

#else  // BOOST_NO_CXX11_SCOPED_ENUMS

#define BOOST_SCOPED_ENUM_UT_DECLARE_BEGIN(EnumType,UnderlyingType) enum class EnumType : UnderlyingType
#define BOOST_SCOPED_ENUM_DECLARE_BEGIN(EnumType) enum class EnumType
#define BOOST_SCOPED_ENUM_DECLARE_END2()
#define BOOST_SCOPED_ENUM_DECLARE_END(EnumType) ;

#define BOOST_SCOPED_ENUM_NATIVE(EnumType) EnumType
#define BOOST_SCOPED_ENUM_FORWARD_DECLARE(EnumType) enum class EnumType

#endif  // BOOST_NO_CXX11_SCOPED_ENUMS

// Deprecated macros
#define BOOST_SCOPED_ENUM_START(name) BOOST_SCOPED_ENUM_DECLARE_BEGIN(name)
#define BOOST_SCOPED_ENUM_END BOOST_SCOPED_ENUM_DECLARE_END2()
#define BOOST_SCOPED_ENUM(name) BOOST_SCOPED_ENUM_NATIVE(name)

#endif  // BOOST_CORE_SCOPED_ENUM_HPP

/* scoped_enum.hpp
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
*/