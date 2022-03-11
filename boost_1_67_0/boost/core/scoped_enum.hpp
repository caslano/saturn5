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