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
oX7AaYeptAbPn04qjvQ7fgo2kvzRSNTvj8Gf2raVOnyhqFnAmHVLGg2/SdkxB6/paGQ84bgK+El0yLVN5KkJ+Hsj8LIMGvWrWW/qt2D3Z4njxK16Lac2BXOf046L71LqMQJs5jaiLVSUHzVdL03SJibY7e2O7PykNfgQv3BwDlV/xlQ8JMfjIvAp6iGI9CLmpfWq+NnthucbdHpb/eQK45Hgm58r2tIvqUzKo2/E6HUaWuRzYwL9ao0+uz2s9gLHKrVyg/OVRJ7KlHTX5DWOPPMhNg2V1dBZZTq5rX5S6vs6sb53xvU9cc76/iau74n7UV8tj1zfN81R3xMbrG8+E//iEryYFp7dI//uTOM2xGWwUt0y3rZUWjv+LekrFmu0Utjb0tj8sVwsCzq6SGyz0xaYtVa1ekRZaaAfnR7HfveHNQHN2PRUPp6vN3ruTWXKT0rf0ndbuRqMPxALOTou8LpEmiNjHSlr/LFr6GycIo6K0l3pS6Ecq6d7UE90MqiYo8FvemTSj5P2l5BuUk2p1fHYhNe1R/k05ZgoVyD7hDLrMh0v1yl9Ij+ZTkXqJQkLzlvBgYzTUbHQmO8URwDdTUtYFGggHDs+GPhOf6eyjmijGBzE99UN+k5cRr4slvGRoIx7lW9KZfyS+L6G/Yr7OG16nkqzfa52NMdcVpMRzn8/054P+f/BaSeq/M3JPTYqyn3NUmm/5V9UDuWo8foeX7Fsqi3qNbG8z4jlccxpHUg4T8ZJS8+q7VtFPEh/8kkqudFxneWLRPmuE8esB61tUkaI+8xt9V/Cz6J2eUjtM82zfeUhIR8qVOV9mPN+gPOml1mcwjJb1up8u/dZptuIHSF/Ck9dF+s1j8tYPk+XsQrKgLypdXsU5/8+yCiULdbvAM57TksjZTt1bOz7G9vBeEp//u5SKU7jBrI3ypEbL6urxBtHcX5xUoIpT9bDHkN1MXHRFQS2/9i1flx02gsD2zs4wHXE5EbX93U9K3m5//9Q9DMeT2VSjtxU/Uyz3vgETpusVCZoSdWJbfVEjbEfNlupYUwgxgoV2j6D88WHO3kmoz2lMed88cK1XgzxJvYIuc4pY95tTa/Va35qLUUzdPn9XBwzjiT5dXaMRV4baa4Osynj1B3B92YxlfexNr0ecAF/L47itCKkLaG0Lx1AewOU9mZOW0ppdxJdl0prcM+gQuvStUAXvxP9oZVr7VyIXoLJFWGtZrWHqbWrRn28Ch0Nq4pz7btd3xbWv07tHRjKKeU6/hqkK5ezQb+QyleA4K/d07SPWYlHB6kuf0Ve4l4L5aS+02i7RfWw3e4Vv8tPgbahh1Eye4qzlNmOa6cATr4r7Yw3dueikquXymKcpH+K49FmNX6WVR5b9hZKe/E0BZ+eUpHp3PhlvRYbKbzY5nkWpStKlUPj+lzLAKUfdizFjqfv3Du4TwxT2hZKm99i017EaYdAWp7zHgt5S5y2HugmhbynYxkNrjPRvlaRPnqkQ77BF9jeAcuktqxTWbQ6Za6ilaaiYg3uMcwSHk1o7NQdfd1DaskC8p/p43zEJsFf4vLnxRR3vwkKd76BL/fyxus1MOd4pYdHuBADdOd6dONIB2PzeX5dhPsvr/Z4KRTnqG+UZI7/29NPB2xa2mWZ7EIQyHOBR1Mr0jp/0V37vMijUV9DcyaDMAT49JLhf7FfX3M0ydb3PT6NPt5kyl9KsZxAwHKFxGuT5ddhGqA/vm4t353E9Tc+H+dc1uTzc3gnE3H/3uUu4qt6Qbw6ELkxm85mLMqRZAphq0ryvm2t3iNWNKpY5HshYsqf42/s5ZT+0mN1LIaLmu2vxI/GHqG/Llkmje/XLdD6VttTmkc=
*/