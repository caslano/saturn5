/* Proposed SG14 status_code
(C) 2018 - 2019 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.


Distributed under the Boost Software License, Version 1.0.
(See accompanying file Licence.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_STATUS_CODE_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_STATUS_CODE_HPP

#include "status_code_domain.hpp"

#if(__cplusplus >= 201700 || _HAS_CXX17) && !defined(BOOST_OUTCOME_SYSTEM_ERROR2_DISABLE_STD_IN_PLACE)
// 0.26
#include <utility>  // for in_place

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN
using in_place_t = std::in_place_t;
using std::in_place;
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#else

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN
//! Aliases `std::in_place_t` if on C++ 17 or later, else defined locally.
struct in_place_t
{
  explicit in_place_t() = default;
};
//! Aliases `std::in_place` if on C++ 17 or later, else defined locally.
constexpr in_place_t in_place{};
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
#endif

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

//! Namespace for user injected mixins
namespace mixins
{
  template <class Base, class T> struct mixin : public Base
  {
    using Base::Base;
  };
}  // namespace mixins

/*! A tag for an erased value type for `status_code<D>`.
Available only if `ErasedType` satisfies `traits::is_move_bitcopying<ErasedType>::value`.
*/
template <class ErasedType,  //
          typename std::enable_if<traits::is_move_bitcopying<ErasedType>::value, bool>::type = true>
struct erased
{
  using value_type = ErasedType;
};

namespace detail
{
  template <class T> struct is_status_code
  {
    static constexpr bool value = false;
  };
  template <class T> struct is_status_code<status_code<T>>
  {
    static constexpr bool value = true;
  };
  template <class T> struct is_erased_status_code
  {
    static constexpr bool value = false;
  };
  template <class T> struct is_erased_status_code<status_code<erased<T>>>
  {
    static constexpr bool value = true;
  };

  // From http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2015/n4436.pdf
  namespace impl
  {
    template <typename... Ts> struct make_void
    {
      using type = void;
    };
    template <typename... Ts> using void_t = typename make_void<Ts...>::type;
    template <class...> struct types
    {
      using type = types;
    };
    template <template <class...> class T, class types, class = void> struct test_apply
    {
      using type = void;
    };
    template <template <class...> class T, class... Ts> struct test_apply<T, types<Ts...>, void_t<T<Ts...>>>
    {
      using type = T<Ts...>;
    };
  }  // namespace impl
  template <template <class...> class T, class... Ts> using test_apply = impl::test_apply<T, impl::types<Ts...>>;

  template <class T, class... Args> using get_make_status_code_result = decltype(make_status_code(std::declval<T>(), std::declval<Args>()...));
  template <class... Args> using safe_get_make_status_code_result = test_apply<get_make_status_code_result, Args...>;
}  // namespace detail

//! Trait returning true if the type is a status code.
template <class T> struct is_status_code
{
  static constexpr bool value = detail::is_status_code<typename std::decay<T>::type>::value || detail::is_erased_status_code<typename std::decay<T>::type>::value;
};

/*! A type erased lightweight status code reflecting empty, success, or failure.
Differs from `status_code<erased<>>` by being always available irrespective of
the domain's value type, but cannot be copied, moved, nor destructed. Thus one
always passes this around by const lvalue reference.
*/
template <> class BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI status_code<void>
{
  template <class T> friend class status_code;

public:
  //! The type of the domain.
  using domain_type = void;
  //! The type of the status code.
  using value_type = void;
  //! The type of a reference to a message string.
  using string_ref = typename status_code_domain::string_ref;

protected:
  const status_code_domain *_domain{nullptr};

protected:
  //! No default construction at type erased level
  status_code() = default;
  //! No public copying at type erased level
  status_code(const status_code &) = default;
  //! No public moving at type erased level
  status_code(status_code &&) = default;
  //! No public assignment at type erased level
  status_code &operator=(const status_code &) = default;
  //! No public assignment at type erased level
  status_code &operator=(status_code &&) = default;
  //! No public destruction at type erased level
  ~status_code() = default;

  //! Used to construct a non-empty type erased status code
  constexpr explicit status_code(const status_code_domain *v) noexcept
      : _domain(v)
  {
  }

  constexpr const status_code_domain *_domain_ptr() const noexcept { return _domain; }

public:
  //! Return the status code domain.
  constexpr const status_code_domain &domain() const noexcept { return *_domain; }
  //! True if the status code is empty.
  BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD constexpr bool empty() const noexcept { return _domain == nullptr; }

  //! Return a reference to a string textually representing a code.
  string_ref message() const noexcept { return (_domain != nullptr) ? _domain->_do_message(*this) : string_ref("(empty)"); }
  //! True if code means success.
  bool success() const noexcept { return (_domain != nullptr) ? !_domain->_do_failure(*this) : false; }
  //! True if code means failure.
  bool failure() const noexcept { return (_domain != nullptr) ? _domain->_do_failure(*this) : false; }
  /*! True if code is strictly (and potentially non-transitively) semantically equivalent to another code in another domain.
  Note that usually non-semantic i.e. pure value comparison is used when the other status code has the same domain.
  As `equivalent()` will try mapping to generic code, this usually captures when two codes have the same semantic
  meaning in `equivalent()`.
  */
  template <class T> bool strictly_equivalent(const status_code<T> &o) const noexcept
  {
    if(_domain && o._domain)
    {
      return _domain->_do_equivalent(*this, o);
    }
    // If we are both empty, we are equivalent
    if(!_domain && !o._domain)
    {
      return true;  // NOLINT
    }
    // Otherwise not equivalent
    return false;
  }
  /*! True if code is equivalent, by any means, to another code in another domain (guaranteed transitive).
  Firstly `strictly_equivalent()` is run in both directions. If neither succeeds, each domain is asked
  for the equivalent generic code and those are compared.
  */
  template <class T> inline bool equivalent(const status_code<T> &o) const noexcept;
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
  //! Throw a code as a C++ exception.
  BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN void throw_exception() const
  {
    _domain->_do_throw_exception(*this);
    abort();  // suppress buggy GCC warning
  }
#endif
};

namespace detail
{
  template <class DomainType> struct get_domain_value_type
  {
    using domain_type = DomainType;
    using value_type = typename domain_type::value_type;
  };
  template <class ErasedType> struct get_domain_value_type<erased<ErasedType>>
  {
    using domain_type = status_code_domain;
    using value_type = ErasedType;
  };
  template <class DomainType> class BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI status_code_storage : public status_code<void>
  {
    using _base = status_code<void>;

  public:
    //! The type of the domain.
    using domain_type = typename get_domain_value_type<DomainType>::domain_type;
    //! The type of the status code.
    using value_type = typename get_domain_value_type<DomainType>::value_type;
    //! The type of a reference to a message string.
    using string_ref = typename domain_type::string_ref;

#ifndef NDEBUG
    static_assert(std::is_move_constructible<value_type>::value || std::is_copy_constructible<value_type>::value, "DomainType::value_type is neither move nor copy constructible!");
    static_assert(!std::is_default_constructible<value_type>::value || std::is_nothrow_default_constructible<value_type>::value, "DomainType::value_type is not nothrow default constructible!");
    static_assert(!std::is_move_constructible<value_type>::value || std::is_nothrow_move_constructible<value_type>::value, "DomainType::value_type is not nothrow move constructible!");
    static_assert(std::is_nothrow_destructible<value_type>::value, "DomainType::value_type is not nothrow destructible!");
#endif

    // Replace the type erased implementations with type aware implementations for better codegen
    //! Return the status code domain.
    constexpr const domain_type &domain() const noexcept { return *static_cast<const domain_type *>(this->_domain); }

    //! Reset the code to empty.
    BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 void clear() noexcept
    {
      this->_value.~value_type();
      this->_domain = nullptr;
      new(&this->_value) value_type();
    }

#if __cplusplus >= 201400 || _MSC_VER >= 1910 /* VS2017 */
    //! Return a reference to the `value_type`.
    constexpr value_type &value() & noexcept { return this->_value; }
    //! Return a reference to the `value_type`.
    constexpr value_type &&value() && noexcept { return this->_value; }
#endif
    //! Return a reference to the `value_type`.
    constexpr const value_type &value() const &noexcept { return this->_value; }
    //! Return a reference to the `value_type`.
    constexpr const value_type &&value() const &&noexcept { return this->_value; }

  protected:
    status_code_storage() = default;
    status_code_storage(const status_code_storage &) = default;
    BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code_storage(status_code_storage &&o) noexcept
        : _base(static_cast<status_code_storage &&>(o))
        , _value(static_cast<status_code_storage &&>(o)._value)
    {
      o._domain = nullptr;
    }
    status_code_storage &operator=(const status_code_storage &) = default;
    BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code_storage &operator=(status_code_storage &&o) noexcept
    {
      this->~status_code_storage();
      new(this) status_code_storage(static_cast<status_code_storage &&>(o));
      return *this;
    }
    ~status_code_storage() = default;

    value_type _value{};
    struct _value_type_constructor
    {
    };
    template <class... Args>
    constexpr status_code_storage(_value_type_constructor /*unused*/, const status_code_domain *v, Args &&... args)
        : _base(v)
        , _value(static_cast<Args &&>(args)...)
    {
    }
  };
}  // namespace detail

/*! A lightweight, typed, status code reflecting empty, success, or failure.
This is the main workhorse of the system_error2 library. Its characteristics reflect the value type
set by its domain type, so if that value type is move-only or trivial, so is this.

An ADL discovered helper function `make_status_code(T, Args...)` is looked up by one of the constructors.
If it is found, and it generates a status code compatible with this status code, implicit construction
is made available.

You may mix in custom member functions and member function overrides by injecting a specialisation of
`mixins::mixin<Base, YourDomainType>`. Your mixin must inherit from `Base`.
*/
template <class DomainType> class BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI status_code : public mixins::mixin<detail::status_code_storage<DomainType>, DomainType>
{
  template <class T> friend class status_code;
  using _base = mixins::mixin<detail::status_code_storage<DomainType>, DomainType>;

public:
  //! The type of the domain.
  using domain_type = DomainType;
  //! The type of the status code.
  using value_type = typename domain_type::value_type;
  //! The type of a reference to a message string.
  using string_ref = typename domain_type::string_ref;

public:
  //! Default construction to empty
  status_code() = default;
  //! Copy constructor
  status_code(const status_code &) = default;
  //! Move constructor
  status_code(status_code &&) = default;  // NOLINT
  //! Copy assignment
  status_code &operator=(const status_code &) = default;
  //! Move assignment
  status_code &operator=(status_code &&) = default;  // NOLINT
  ~status_code() = default;

  //! Return a copy of the code.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code clone() const { return *this; }

  /***** KEEP THESE IN SYNC WITH ERRORED_STATUS_CODE *****/
  //! Implicit construction from any type where an ADL discovered `make_status_code(T, Args ...)` returns a `status_code`.
  template <class T, class... Args,                                                                            //
            class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<T, Args...>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
            typename std::enable_if<!std::is_same<typename std::decay<T>::type, status_code>::value            // not copy/move of self
                                    && !std::is_same<typename std::decay<T>::type, in_place_t>::value          // not in_place_t
                                    && is_status_code<MakeStatusCodeResult>::value                             // ADL makes a status code
                                    && std::is_constructible<status_code, MakeStatusCodeResult>::value,        // ADLed status code is compatible

                                    bool>::type = true>
  constexpr status_code(T &&v, Args &&... args) noexcept(noexcept(make_status_code(std::declval<T>(), std::declval<Args>()...)))  // NOLINT
      : status_code(make_status_code(static_cast<T &&>(v), static_cast<Args &&>(args)...))
  {
  }
  //! Explicit in-place construction.
  template <class... Args>
  constexpr explicit status_code(in_place_t /*unused */, Args &&... args) noexcept(std::is_nothrow_constructible<value_type, Args &&...>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), static_cast<Args &&>(args)...)
  {
  }
  //! Explicit in-place construction from initialiser list.
  template <class T, class... Args>
  constexpr explicit status_code(in_place_t /*unused */, std::initializer_list<T> il, Args &&... args) noexcept(std::is_nothrow_constructible<value_type, std::initializer_list<T>, Args &&...>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), il, static_cast<Args &&>(args)...)
  {
  }
  //! Explicit copy construction from a `value_type`.
  constexpr explicit status_code(const value_type &v) noexcept(std::is_nothrow_copy_constructible<value_type>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), v)
  {
  }
  //! Explicit move construction from a `value_type`.
  constexpr explicit status_code(value_type &&v) noexcept(std::is_nothrow_move_constructible<value_type>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), static_cast<value_type &&>(v))
  {
  }
  /*! Explicit construction from an erased status code. Available only if
  `value_type` is trivially copyable or move bitcopying, and `sizeof(status_code) <= sizeof(status_code<erased<>>)`.
  Does not check if domains are equal.
  */
  template <class ErasedType,  //
            typename std::enable_if<detail::type_erasure_is_safe<ErasedType, value_type>::value, bool>::type = true>
  constexpr explicit status_code(const status_code<erased<ErasedType>> &v) noexcept(std::is_nothrow_copy_constructible<value_type>::value)
      : status_code(detail::erasure_cast<value_type>(v.value()))
  {
#if __cplusplus >= 201400
    assert(v.domain() == this->domain());
#endif
  }

  //! Assignment from a `value_type`.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code &operator=(const value_type &v) noexcept(std::is_nothrow_copy_assignable<value_type>::value)
  {
    this->_value = v;
    return *this;
  }

  //! Return a reference to a string textually representing a code.
  string_ref message() const noexcept { return this->_domain ? string_ref(this->domain()._do_message(*this)) : string_ref("(empty)"); }
};

namespace traits
{
  template <class DomainType> struct is_move_bitcopying<status_code<DomainType>>
  {
    static constexpr bool value = is_move_bitcopying<typename DomainType::value_type>::value;
  };
}  // namespace traits


/*! Type erased, move-only status_code, unlike `status_code<void>` which cannot be moved nor destroyed. Available
only if `erased<>` is available, which is when the domain's type is trivially
copyable or is move relocatable, and if the size of the domain's typed error code is less than or equal to
this erased error code. Copy construction is disabled, but if you want a copy call `.clone()`.

An ADL discovered helper function `make_status_code(T, Args...)` is looked up by one of the constructors.
If it is found, and it generates a status code compatible with this status code, implicit construction
is made available.
*/
template <class ErasedType> class BOOST_OUTCOME_SYSTEM_ERROR2_TRIVIAL_ABI status_code<erased<ErasedType>> : public mixins::mixin<detail::status_code_storage<erased<ErasedType>>, erased<ErasedType>>
{
  template <class T> friend class status_code;
  using _base = mixins::mixin<detail::status_code_storage<erased<ErasedType>>, erased<ErasedType>>;

public:
  //! The type of the domain (void, as it is erased).
  using domain_type = void;
  //! The type of the erased status code.
  using value_type = ErasedType;
  //! The type of a reference to a message string.
  using string_ref = typename _base::string_ref;

public:
  //! Default construction to empty
  status_code() = default;
  //! Copy constructor
  status_code(const status_code &) = delete;
  //! Move constructor
  status_code(status_code &&) = default;  // NOLINT
  //! Copy assignment
  status_code &operator=(const status_code &) = delete;
  //! Move assignment
  status_code &operator=(status_code &&) = default;  // NOLINT
  ~status_code()
  {
    if(nullptr != this->_domain)
    {
      this->_domain->_do_erased_destroy(*this, sizeof(*this));
    }
  }

  //! Return a copy of the erased code by asking the domain to perform the erased copy.
  status_code clone() const
  {
    if(nullptr == this->_domain)
    {
      return {};
    }
    status_code x;
    this->_domain->_do_erased_copy(x, *this, sizeof(*this));
    return x;
  }

  /***** KEEP THESE IN SYNC WITH ERRORED_STATUS_CODE *****/
  //! Implicit copy construction from any other status code if its value type is trivially copyable and it would fit into our storage
  template <class DomainType,                                                                              //
            typename std::enable_if<!detail::is_erased_status_code<status_code<DomainType>>::value         //
                                    && std::is_trivially_copyable<typename DomainType::value_type>::value  //
                                    && detail::type_erasure_is_safe<value_type, typename DomainType::value_type>::value,
                                    bool>::type = true>
  constexpr status_code(const status_code<DomainType> &v) noexcept  // NOLINT
      : _base(typename _base::_value_type_constructor{}, v._domain_ptr(), detail::erasure_cast<value_type>(v.value()))
  {
  }
  //! Implicit move construction from any other status code if its value type is trivially copyable or move bitcopying and it would fit into our storage
  template <class DomainType,  //
            typename std::enable_if<detail::type_erasure_is_safe<value_type, typename DomainType::value_type>::value, bool>::type = true>
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code(status_code<DomainType> &&v) noexcept  // NOLINT
      : _base(typename _base::_value_type_constructor{}, v._domain_ptr(), detail::erasure_cast<value_type>(v.value()))
  {
    v._domain = nullptr;
  }
  //! Implicit construction from any type where an ADL discovered `make_status_code(T, Args ...)` returns a `status_code`.
  template <class T, class... Args,                                                                            //
            class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<T, Args...>::type,  // Safe ADL lookup of make_status_code(), returns void if not found
            typename std::enable_if<!std::is_same<typename std::decay<T>::type, status_code>::value            // not copy/move of self
                                    && !std::is_same<typename std::decay<T>::type, value_type>::value          // not copy/move of value type
                                    && is_status_code<MakeStatusCodeResult>::value                             // ADL makes a status code
                                    && std::is_constructible<status_code, MakeStatusCodeResult>::value,        // ADLed status code is compatible
                                    bool>::type = true>
  constexpr status_code(T &&v, Args &&... args) noexcept(noexcept(make_status_code(std::declval<T>(), std::declval<Args>()...)))  // NOLINT
      : status_code(make_status_code(static_cast<T &&>(v), static_cast<Args &&>(args)...))
  {
  }

  /**** By rights ought to be removed in any formal standard ****/
  //! Reset the code to empty.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 void clear() noexcept { *this = status_code(); }
  //! Return the erased `value_type` by value.
  constexpr value_type value() const noexcept { return this->_value; }
};

namespace traits
{
  template <class ErasedType> struct is_move_bitcopying<status_code<erased<ErasedType>>>
  {
    static constexpr bool value = true;
  };
}  // namespace traits

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif

/* status_code.hpp
s4lCl/QOcFRd9jL83/pjlcFnZ4EnN12BNZXBVnCQQteuLKeDdCkdpE/wQXp/nnIPnV9qk7HECdP5jWFajkuGso2PDrArwuydIhnCJKFIPvpk08Un4Jv4dzHmqS5Lq3sNvu6LFn6S6/wkd6iVa3EleJI7juY6j+YOjX65QM91Zu9f4KXvV+MAHZqntOcpThygvUj8DEABiBIo4Pg1vt2aO5QD5/m9TGgjeMZQ/6QH06pfcY7zGM5Qz7v3xe+WpFctwQDd2s9CwQJ8x9t/6Dayj3H0+RBWz6QDCEV1gHub2I3Ak5YAO3JlAGxJDzklnoDeS8YB4y98vMX8BXwG8Ak7epMJeHWvvMgn6MV0MVLBKAS2O78a5taK7FoRfTq1Igfcj/kkEUPTbMYtyAFb+io1Tt/ShULf6nJHMr3mWHiNQ/O1jTji6yqwdVI52a8Y20+uBHfVs3jRfCcbA3xO3UZjrvnhudQq+tfRCyNGjNrUfN30wtL/GVEuU7vM0FZc4ReW4cp1/K7Mpz5yf/w980gSED+9P/6Ot9AF6mqy7M7LTpnTMb2qBd3Z09ccd0DRyB61BODb+8i+2BQM5ynIjE9BzffnTAGiFAWTuiGyd1pFO+OEzY/37I8bzRn42/x4757dCAevdNA5s5Pw/rNIGj+X+zqKDE28zo9eR9c1Gca2T7xLL7In01aMM6Zq6Cv0agG6kn1M/2aiNmeKWLca+KrOSGQzzaD4bAW9HLNJf9kEwY7dlJXZer/RrSPc3sPqteKjpm5s9eKRxzLdIvgosOC8dcSF1Yu5XxDVMwu6yo6xs3rQeBv1RsrxKfmsgKh2pNq0ctTPjm4S0EGGl9MDspDEaJBP5xuVGMFIZCu62LHZ+gpR+Zs/8rjcHCnfQFcC8ob2e1QurnwDrDq/GPNLk3bRcEVQDgTg6t/QCufizJ29RuKSh19aucIEJzis9JUdEMeHkRwt34QW+8O13XxWTBEFFTEkg8NqmglvEBmOGO3NZjN71tGq+68+ltfjFEzAgt4c3k7HaM0CIHnlDuW1fnltbK0P6bnWG8SCTiNhndOaLBk8Qwtv4EiToXUpiLuqm8irJLJDJrKj6ksGR3Zwcrt/bwnfN98mg9mJBa2m9vcMMXkGosRL0al3HVjwMnawAAy26hfjf2xKVM4NUqICn49Ygm84WlifAPfZjGK3McxtZDyKjplBg9HJ8CUw4wm/FP96gkaeUaOJkb5Zwk2DfC8Ogd61kwxmCpaxIESlwayKiXXoMQ6HS+stKYat6rfo8TCHGeuocKyj2ktXh8SRkGfLV8ngW66EPmpp0dslFDM1M8bqzBDx+SPMdJwnHPK6JzgcknqipYlv1nJfHnZwX6rKDOa7wJs1zwdwmVYR6AX+bhp/FvFnMX/O4s/5/LmQPuvSNhugVvN6SWoFrOK6JFxrS1tgS4B4dgSJRdNPifdCNk5EIQpT6fiwJaVBLNbT1IElg4iV0A8HAOFUYhN/u+y0MZdq2x9P+ZRzVpJrHdBs9UF4juhHNbVTpFCVnJyn5ERRlq+GyO2WLUlAmWsOQPvcIF5cBgt0JxxcQgelr83BiO94gNbibpEcbkEmuIOB7BPEYWzjEVCPE59BVYdr+qEK8Ra14NmG11dm6fSsetAExgvXJJec0XzHs08UxkHXPGNqDo9wKw7PtvWsVdfDCCZI8rXr4Rb+0mGM2cAYbPXGmK0NIzhYXwxfeiYO6Tr+ywyOMQFiohV9u2qZtGZeFV7m6KdmhscjBtumDtaT6lYtNOfBSvSYE00LiLdUmy0xxjFcjcm0qRmxCHrx7CKkosHTtnD1qwwW0s9Mw/Mi/4wnLOAgScywGE6LxWLkT88+K5Yy3D6kR45Ihg/BgnKVjYHGjvvgKr8aGurzghTA6cNTjWlQHPrs47qvI5qmz6YB6IRvVk2OpxqLUaGzaRPD68CCG0BMsVyrEnLAU42VqV6j92v8HERdydSTgkhyVmBUojNGgLgPucTFeqKQ0cv03MwgVUMliqGZNItlLHwYxx7KJcD2vnaQaEiTpxqXlau8nyqX09MydungReyu7NpeEyi+APUsNo1vCIOkPlZzp6u38me8vzGIhJkengbFKWdB418WTOoIkWEB/cLhW+kHlaTSSyxtoDcYcO46SEBx7plsjhZ6GI0rfYSXnmXjfV3YetgT5pX+M2BQ/EBSrFg6LEAjbhGrkuyIpNP9rVkOmTot3NYnoPmbpblo7hyiRZdSgcu4DSpxWZiHlM+H5p9wcqIG4br0tGHmlpXpsrATsr/ISEjBYK4nXgE3yLWEeHMMqnKZxr7u4icHAD7Lozg8cRSjgzzVaF7tH1//k34JVN6EVC7SssP1ezwbi2U7G7n+q4OiP6re2GOC+Je2cTN/vgGQ3yjAPsWXC2nzzDRRqP4Kmp+VzNFKm2eaB9PipzjcnINQ6DyFl7K4ccAZKQUcEdH+Eieg2Jmc6cYwQy7QZreL319wRsKi0uQwAYYDRHFTkiyFePTlsRJCknSOJN8cK9EqZsRKtErizqHjC2MlWsQtsRItkvBz8Pi4WIlmkYES/w+hj0PfPUgAgENLpX0NXJRV9v8MDDDq4IwKioZGZWlhZZHlNJpvDZI2OkgwmiG9uuzkVtbzKBaD0jDm0+OgvbubtdbqZptbtllimqH4E0hSKtZIqahouzSsYbFK8vL8zzn3PjODuru/////+fjBeV7ufe7Lueeec+4531MpJdnzmySrGp8jwiAp0h86gCLOPf3D0eLyGtp7eo0kTlRMhE5V8b+RhApIhmQRsMXq9607nRZ/580rc6QpfnaFND5LGulnQ6WBWVnychzmwyeSDaFx+OvYT/Dr4sUUf5G2mAIwhocm4JM2fEKTkgy/FiCqEnJIu5/dJY0FHW1ElpyOT0+foKfyt3gxCQt9hr/ux0+gwzFbjve+xHxYYnPKb30Ow9X5z4oLwz8fbhU/BVAJ0kUYISpcGpN/y5bC/ec+xC351eqeSBJfbZkEsstY+JiexBdeCc4pYg88C6LgnOJFrffBD6GWTZPIgowxWW89ExWYVxtOLbZlR49WHX8djDJLXoDkOEdiLU+DtJfAr4rYUbz6dT5dFbMavArRFTds73yawooyapXVa4gL49QpZOVQyGahkLFCKd8ohAOBzVSmYzPRt+9aDW2eU4z+7nn0swh/zqafEv6cuprDNVVviossUHhNXdAROC6P4Y1RjWi6T8awGrZpAnqMwrCRKhsqxHm+B5O5BrSiOWpesePRjpWZQdOUxf5JtgI509G1cqJ1p8mMqfBQL9OepsB1Xu0g/6MdwEKAXEYhMIeZzZhAMyJZsVYLj7l6cxUOhEgFIJoYXFCsDvGoj4JU4Oi1ls3mIdZ2Ocla9iIlCCsZE8zSHIeLr3McWTkemjKrQE4OWqZn+Vtj4GF/R/XKEYv99gLphKNaHoFny2bCih7fiioo/+718F3HweKf4d0TUMP0Asnq9hYAE335Ot7IGkytYFQHqNkdjv3W4CcoKVqmQZEPHftX7sbqrQE8WJzq3xfj2F/8j1Y096u3SOotHY59vuHB66YHKouegerXLfbfVCCbp/oPxjj2Ff9IaFF6k/xphtBK6Eug1rrmXsQ2PmJdh0H/1CdpTPC26b1Z/h9jbglUlqTgO1PFOxPpnRsL5G9gdN/GQxdj0K1lzYL3Lgh8al2TguaJAY7sDuu6RHq1eFpvgfQ1dCmEH1fGA42rUzuoII29LezrLzj4eoKJ8RpBxuh2k+BZAJw1J5yObJaswab/XxNzh/GZcNVM7IkYMONyz5F7bLCx+nev5xCRr/KkOVi7Bz+PzfgQ2YBH5KGksAN+H2ZtPzrFoWv/xfpN8Z6h73t/IPCYDjeBNXJYGuhRbrtdbl8Zox5F4Flnh93VgYDujk/g7yeOg/DgYMEih7NDjnPktksDvAb3PKgqS9IQY8BR1aMtpHBmU8WvuE2VdSWDsGwhFnJfOx7ejuMBjG62rxyVdptqUN0d6kB1KWkb89x52bA6qp3tZLa4/zOyA/kPJLHB3ckEE5n6BlR7JVZ7Ene5djWzCMFEh6nLJIoe7r8uOnq4iD1+m9ghs/F7mcUZmLIbSpRMcXQV3wU3HEUdKxcAjRUVyJeomRJezoJlXLTYsRqTqMlx9nyL1I+quGNJN1YxE94p3qcf7/y+nI53FvgrbXS880UpHe/cDU2EVcwX2N+Lu7Q6UDDnYuMfOpMsgPBIou/P4mDCWp8it1Qz4eIF6LdF6mAHckTrnwl2oTkiiFmw7HuRTUoDvUY3+5FHEBtD/d1s1hmu4FOBu98Km/hmYotgpB7rgA/4YqGxweumIMaPhdX9MxkDVeF+ST9YAKiHmwYGZ7ezIaUEfbXxDPUCmv44Nv3dX5MJunQDCfcJbPY+kBXvYKP0Vv5zrThwpBYaqLW8ndOj2vnqr1HtfP/NcDv/uIpC+dSHOoJZ7eypVdSCEbwF0YeioIluW97Nz0L/hUIPbDEzXuL2fdhfJsLPxUBZdCktVmga2cUv4elpkuDH6MmexAbCvVAcWw5juyi87ClvpYUngcpvDYHCLxJCuYN4mEYi2Mc4GMc7k8ky1sJGzaP+N7J/qkIKayQpDGeMbcOkKnIjCDTsvjhccA2I+nNnHMo+dQL1p4Elm3UJqYHvf6w2W0TNboBKSbspnIiFXHVkxPlnAmH+WDE0fGpHRi2e9u8D3fhpXoyxu3gxkOYM4WKx7D1eDGMsiOe1OaZ1SDEZmrdgEfPwok3sMl4URLQ6k17UxB7jRS9EzAA0eEjJjqqSQYFKPWK4fUWXZt15DcjtaBQNaNLFeKAiM01uY5NhDELDqqEahL65/3mTrQoD+ixs1WnCosfb7HM3fb+Z/flJ+j4IkRvC309gXfH0/QEIQeRqYXPROO9qRsJZXNKlI08upJ8UdekuCVOWswSPH+vIwJVqwHKNePuqEhIjd57WibwT57X+FK3PSlihPjOo7oSY55C7aWZdZnbwfuQCRTh8+WaEGK2WXLhak+wzOkpm4OI56sN6W8dQnsBi4G8wPZ+WDA/UFo1AhpPVsXIwMJysAtk4c5rjo+If7I91hP6HD+IbRWghKuPQyeiUU0oAuG1GOkRRczocZ3y/wUqzOgK10uUgiVQjx9rPGdg0xKGDe+84zqx8C5jYY4KJSWPh5stw8w94E3i2kLz2jqOIO13IUVxtMxH0XH6hdYKGe0gbbD7pZN0vgtFAF3s7pbQpJnnwj4oebkvuPPC8ZEJAs665lkogY7Wuu4xv4NC2Qdad1BY3ncZvH0TQnsRKD6m5ZvV2GCRYMK42RLnYTEi0VEOQMDWg1iaYb6ryM/iBDNrfWSDPQ0FgPz45ZF33Pj1InbXY8fIqDuyWWUQlXhElQDLL0eUyoKTbc6gpl0JTNMw6ZgZqCaURWxmB9XpFvXfD/4sdplny5dOgfdDSmXB3LYomhBsP4u6/Xu/SVZNjjwFPuVhcfPxYl4jWb/2BNlszvX7wdf02e+MxHlKf8S+dBi/ZBjR4a0efPQI3hRfo3GCDbtH/i0vw3BVPdGncHIncxvllj4byQDtstekIDupsA/q9RXerBYqWJsEuR/P3NZYsgvnzmT38YIwN6Y+RPhYQS72GMLjK/Uug6XPbmfYo7+Wfif2T/zfecbYxGZqLu76lIhNbX/4Ltp4l6E08upqamHEcGwma3KamHlJMYSi+0Ho03QHU/jJWbA2s5ujE1IffdPNMVXoHuO6ypB/sO3fDb6z9eapCyuGPsvuhVk0S28UksbW5kQnCkzc6SGYTLv3P3w8c6b8FHYtpjH+U+MS6X1AEsVT8Fvv4l5+xj1g1wbFt50UiEyQAfA+zMe/3aKx7tmDmhwK6AbkN2/T8cT5d0ChW3EVdNfftaqkZQ1pJEJSSaFT0b8LDxl80zUsQ29Cndrbfy4HTIhN06wpq+d9/ThbxJmux7SdO/i/bfj9iSk3V227t2/ZjxyJtrzxzvrb/T8J/aHtq37bHn9P29UXU9uGi7WMrfsC2X0ttF3lCnXVU2+7thITQpwufI5JjRY/Gv9jozuET6mx0OFkJopSywlliu7mhrIuQsXTyNB7D2CGW7myHp25qdZOb/X54D0kwbPwsMR6aHyU/8m+EXR3kspdRZZXuQnln3r80eok23aNbcOE06BADO5ejJIpiq+RBibQWxVGXw9Xuy3IcKk4RW4SNtgjJOHcaXBV/ExrHN4gnH+7SQP9oD1dvYsv7Vj8fqvegmIFtbK7GML2mbIKHocPKuzoI0idcIIGN4e0hMcJRBfuA45Ca3yTFqTM60C8ttlr1tTlmdviucqM/OtbquRxGiLuMUa1mljERxfp6vcqGZTh3dp4DgMCk0CfvD53no5I/xp1LJXU6lZxq70Mlzb/RCNImQiVe+BIyp7vxf9h7b1/WpYsFc6kRrPGnZAE+1P+vQEAnTyQLl2s0J8glnOvIy6C5NH/VBH1g5LDxhNv43Wny+50lmvTdCY1ETVc7EktKFwaZtgMDSiSrr5a8AygzhD56V77Xg01TQNumb7G9MrJLS8jKrzMqQfg0oy/5BNHE0RWTsYlzqInWnRji2MZ+ie3RtpolyiF5xdShhpBlq02y4tU9U4YarDsr4aUF6ki+INqJ2wnlECj+MxxQRhsPBswfZlt+Iggf2HsDtSssap7kmA47ZABdWl0t1rXF9MNsXfcI/nDCHS/9gDt34Y8aayAXRYC8IjRoWMssRnoq36rOQW3/FtDqE/Xpbc0kLC6EJgp//rKfCH0LjQqwEttLPgNhBO8nLKaJVVxMcbVnc6biOUEC33Zoq9eAGTkY3PzqPo1zHRRUD+6AqRjvNXKzF3ZXiIG3SYQHg2n3gGpm9CNhY6r41ov3iZ0bRooPEjzELgaeQ4lN74hv6Flt957QSD8B+vtVs5YVEiigtfxO9L43ZGe3uhHgjzd94z812tZO9opdHziI+NRhlkygEmZNbiK8WTOsitYLImXvFGXf7SUxipCXyjDOUc1lGbUggrQouc2BT4sewTVb1KH4Gh2fr1wcNLmtOycq6LjXEJxl9FfGwDT6xoHMOdvhalyZiQ999YtVX8Niu69e7qc5W6bBSyETRlj7fU0G+Qj2zdeSvt9RXXJROA7H2ew1BC0Ts92tS8P2ovgHgMPMg37B+LrZqqQeDk+mWcsp7a+vPd0HBNaSXj1VcAwzWwNT4OagLEZ2cFNXhFkY2GsPo+JAwuFcjxvhUU/8TdP5i5mcCNhnGd3RRaSHSelWZ3YoznoYrPJ7UF5d2W0ssdDn7l1OzxfjoapcD3cWg2Z+IdwMofpLcfMtXkNsDXoEMRUKe6KJKON4DioZhxEr7QF4CJ8JVJakg2S6pgtlwkbrul+4SFmAUGmxVSTVfRnfi2/OcDQW/x22D53arryHS0/7lsLXb6DxAN4cJgYzoUbUa3JD6wn4pY87GQkRWfMwa7tb09iQEJewRlesQg4x7kfaBcWixx2u+exF38xJnLbq7SHSlYCAaNFnSg43LPr9tNbbrGt30Y926zr0y3Pkwp3X6AfceZmgMK2Bn0juL+LEuMtIr8lT/WeMJUO9hlnzor51M34rl4HyoEmD7bntvkTi3/CvFTlImDks5N6IwRWakt8G6sk8UGmAth2/rswKmoqsO21KflNwLifkdt8YIOTxwKFWplt3pij5jYsdx5CG2+DxtCgablBz24KmYerXirMpdBun1vn3d2mB40U/Q7fpE42OL1Z+b91pmb/YUc6VI9QT5nesrIcJne/Ib1xZDYpCdkRRsJbNRI0mt21G0DQEmFbx2/Ngf0Xx1Q0NZqsGUdZiWgKVJTdmkbiBgumz8b06GJuRffpSl1A7iYDfeTBM8/Su8fZu2uea1MMeduZODQ02OVE0yY/9DB50tj+Oj2d0ZJyCz10eOGVdk4SWUJgsi0ZE+YiKTkOmm9xslqkX38x0tBd/Dptj6+sE4t/Ylx2tfgspsFFnRytALmvdK9Q8mu5HjTzNhasJtaLXiC1xztOC9tfnkceZsojBNMJcBlfQpPnafaQNLscV42uxrnuAloxNyW1YrOY2LrbnNsgJM2YKHtRmQG0T6EY+mP6J47OSYREG1IQMKAUY0MV4zJsdzJQ4Vp3ibGEmW48mMBMCx0vuU30s3desVqVXu3UByBrXGxHEXBv7SEpXPRCeBOQ7DWzZm2G+00ZhFmzh1d3RJbp/hzu43iIYrbkFUMLX5jl7qkCA8hpyEF7vygJiIJHZWtzDZ2tRD83Wcj5bo9xsYwwxED5bwDHW/Y5zjAbiouH5OvpXnK8GYBqts3v7cox2voO8vwg4xjf/4BxjbEUVcowz30dzjGYanyiO0Xc/FEJDu646PURZVWFxNQcqgX/MkciaTnEwTmZdu45+QJdWE9uAOz6df0iU6dsaqKaQgyL/CiSop4h/tMsRSQFjnDI+nY6pxJ1NgcqiBeoKIq/qlXODlmnWnXYltxG2r6DbiCcMwFTGwQZ4nSO3ZeXV+NBXBxtbPWxsdcQUpsNLSFSNQFSNuLHltqmdsfthq9B5ws2/AZ6gRXhCHbAd5AlFfXhCEecJRQ5f3bk8YSrnCTOB3XCeQOgyLZwrNDJv4jlcoY68m0piiCBbiCvs+X0XpY0RXOGl+6O5QgsL5XKuUI97URP79g4ktpY+e1WE0A7cESY0a/mnRgr1WJMoWEOcphNbIye2qw0RYmvdTHyhri+dPfAG0lkdfJ34wl0gubXuoWks5tNYJPgCzph1zZ+QL8wp0ifOuu5p5At88nx1wLKDRTR5Ol94ROcLXuILg5RckE5y64Av1BNfiJ5CIDzgC/X/hi+kIV9wR439iQFncYXmdF+D4Ap8En41hCchlt2wIWoSYliKtw9XqKOIxGhtx8Sc6d3RJf7x27O4gn3hORN1FlcYtvAsrnCv4Ap39Jw1UasxM0MUV1jxW84VmmjDDc9W5euEbwQMoNV1LldAyXnz7cAVDn2bHI4xwgMuaCJIO+FDoZMs8B0IUkc0u69btnjE6rwnJhKViiG+/s5Lrf7dFF9oFuFs7AJpWpY1cG0MT7EYdNrCdgXe9RxEzRVPoDGj4DN2n03ORnA+C86eLTQZn+E7fUsiM7Lpj1D/+haLWuShsHhzcFYij2q+JRMPYSofZu8sAIp9zWgIW7K8Zrb7FNx7BqlYcEI=
*/