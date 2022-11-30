/* Proposed SG14 status_code
(C) 2018 - 2020 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
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
BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class ErasedType)  //
BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(traits::is_move_bitcopying<ErasedType>::value))
struct erased
{
  using value_type = ErasedType;
};

/*! Specialise this template to quickly wrap a third party enumeration into a
custom status code domain.

Use like this:

```c++
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN
template <> struct quick_status_code_from_enum<AnotherCode> : quick_status_code_from_enum_defaults<AnotherCode>
{
  // Text name of the enum
  static constexpr const auto domain_name = "Another Code";
  // Unique UUID for the enum. PLEASE use https://www.random.org/cgi-bin/randbyte?nbytes=16&format=h
  static constexpr const auto domain_uuid = "{be201f65-3962-dd0e-1266-a72e63776a42}";
  // Map of each enum value to its text string, and list of semantically equivalent errc's
  static const std::initializer_list<mapping> &value_mappings()
  {
    static const std::initializer_list<mapping<AnotherCode>> v = {
    // Format is: { enum value, "string representation", { list of errc mappings ... } }
    {AnotherCode::success1, "Success 1", {errc::success}},        //
    {AnotherCode::goaway, "Go away", {errc::permission_denied}},  //
    {AnotherCode::success2, "Success 2", {errc::success}},        //
    {AnotherCode::error2, "Error 2", {}},                         //
    };
    return v;
  }
  // Completely optional definition of mixin for the status code synthesised from `Enum`. It can be omitted.
  template <class Base> struct mixin : Base
  {
    using Base::Base;
    constexpr int custom_method() const { return 42; }
  };
};
BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END
```

Note that if the `errc` mapping contains `errc::success`, then
the enumeration value is considered to be a successful value.
Otherwise it is considered to be a failure value.

The first value in the `errc` mapping is the one chosen as the
`generic_code` conversion. Other values are used during equivalence
comparisons.
*/
template <class Enum> struct quick_status_code_from_enum;

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

#if !defined(__GNUC__) || defined(__clang__) || __GNUC__ >= 8
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

#else

  // ICE avoidance form for GCCs before 8. Note this form doesn't prevent recursive make_status_code ADL instantation,
  // so in certain corner cases this will break. On the other hand, more useful than an ICE.
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
    template <typename Types, typename = void> struct make_status_code_rettype
    {
      using type = void;
    };
    template <typename... Args> using get_make_status_code_result = decltype(make_status_code(std::declval<Args>()...));
    template <typename... Args> struct make_status_code_rettype<types<Args...>, void_t<get_make_status_code_result<Args...>>>
    {
      using type = get_make_status_code_result<Args...>;
    };
  }  // namespace impl
  template <class... Args> struct safe_get_make_status_code_result
  {
    using type = typename impl::make_status_code_rettype<impl::types<Args...>>::type;
  };
#endif
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

  // Used to work around triggering a ubsan failure. Do NOT remove!
  constexpr const status_code_domain *_domain_ptr() const noexcept { return _domain; }

public:
  //! Return the status code domain.
  constexpr const status_code_domain &domain() const noexcept { return *_domain; }
  //! True if the status code is empty.
  BOOST_OUTCOME_SYSTEM_ERROR2_NODISCARD constexpr bool empty() const noexcept { return _domain == nullptr; }

  //! Return a reference to a string textually representing a code.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 string_ref message() const noexcept
  {
    // Avoid MSVC's buggy ternary operator for expensive to destruct things
    if(_domain != nullptr)
    {
      return _domain->_do_message(*this);
    }
    return string_ref("(empty)");
  }
  //! True if code means success.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 bool success() const noexcept { return (_domain != nullptr) ? !_domain->_do_failure(*this) : false; }
  //! True if code means failure.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 bool failure() const noexcept { return (_domain != nullptr) ? _domain->_do_failure(*this) : false; }
  /*! True if code is strictly (and potentially non-transitively) semantically equivalent to another code in another domain.
  Note that usually non-semantic i.e. pure value comparison is used when the other status code has the same domain.
  As `equivalent()` will try mapping to generic code, this usually captures when two codes have the same semantic
  meaning in `equivalent()`.
  */
  template <class T> BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 bool strictly_equivalent(const status_code<T> &o) const noexcept
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
  template <class T> BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 inline bool equivalent(const status_code<T> &o) const noexcept;
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
    constexpr value_type &value() &noexcept { return this->_value; }
    //! Return a reference to the `value_type`.
    constexpr value_type &&value() &&noexcept { return static_cast<value_type &&>(this->_value); }
#endif
    //! Return a reference to the `value_type`.
    constexpr const value_type &value() const &noexcept { return this->_value; }
    //! Return a reference to the `value_type`.
    constexpr const value_type &&value() const &&noexcept { return static_cast<const value_type &&>(this->_value); }

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
    constexpr status_code_storage(_value_type_constructor /*unused*/, const status_code_domain *v, Args &&...args)
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

protected:
  using _base::_base;

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
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class T, class... Args,                                                                                 //
                         class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<T, Args...>::type)       // Safe ADL lookup of make_status_code(), returns void if not found
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(!std::is_same<typename std::decay<T>::type, status_code>::value                    // not copy/move of self
                                              && !std::is_same<typename std::decay<T>::type, in_place_t>::value                  // not in_place_t
                                              && is_status_code<MakeStatusCodeResult>::value                                     // ADL makes a status code
                                              && std::is_constructible<status_code, MakeStatusCodeResult>::value))               // ADLed status code is compatible
  constexpr status_code(T &&v, Args &&...args) noexcept(noexcept(make_status_code(std::declval<T>(), std::declval<Args>()...)))  // NOLINT
      : status_code(make_status_code(static_cast<T &&>(v), static_cast<Args &&>(args)...))
  {
  }
  //! Implicit construction from any `quick_status_code_from_enum<Enum>` enumerated type.
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class Enum,                                                                                //
                         class QuickStatusCodeType = typename quick_status_code_from_enum<Enum>::code_type)         // Enumeration has been activated
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(std::is_constructible<status_code, QuickStatusCodeType>::value))      // Its status code is compatible
  constexpr status_code(Enum &&v) noexcept(std::is_nothrow_constructible<status_code, QuickStatusCodeType>::value)  // NOLINT
      : status_code(QuickStatusCodeType(static_cast<Enum &&>(v)))
  {
  }
  //! Explicit in-place construction. Disables if `domain_type::get()` is not a valid expression.
  template <class... Args>
  constexpr explicit status_code(in_place_t /*unused */, Args &&...args) noexcept(std::is_nothrow_constructible<value_type, Args &&...>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), static_cast<Args &&>(args)...)
  {
  }
  //! Explicit in-place construction from initialiser list. Disables if `domain_type::get()` is not a valid expression.
  template <class T, class... Args>
  constexpr explicit status_code(in_place_t /*unused */, std::initializer_list<T> il, Args &&...args) noexcept(std::is_nothrow_constructible<value_type, std::initializer_list<T>, Args &&...>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), il, static_cast<Args &&>(args)...)
  {
  }
  //! Explicit copy construction from a `value_type`. Disables if `domain_type::get()` is not a valid expression.
  constexpr explicit status_code(const value_type &v) noexcept(std::is_nothrow_copy_constructible<value_type>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), v)
  {
  }
  //! Explicit move construction from a `value_type`. Disables if `domain_type::get()` is not a valid expression.
  constexpr explicit status_code(value_type &&v) noexcept(std::is_nothrow_move_constructible<value_type>::value)
      : _base(typename _base::_value_type_constructor{}, &domain_type::get(), static_cast<value_type &&>(v))
  {
  }
  /*! Explicit construction from an erased status code. Available only if
  `value_type` is trivially copyable or move bitcopying, and `sizeof(status_code) <= sizeof(status_code<erased<>>)`.
  Does not check if domains are equal.
  */
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class ErasedType)  //
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(detail::type_erasure_is_safe<ErasedType, value_type>::value))
  constexpr explicit status_code(const status_code<erased<ErasedType>> &v) noexcept(std::is_nothrow_copy_constructible<value_type>::value)
      : status_code(detail::erasure_cast<value_type>(v.value()))
  {
#if __cplusplus >= 201400
    assert(v.domain() == this->domain());
#endif
  }

  //! Return a reference to a string textually representing a code.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 string_ref message() const noexcept
  {
    // Avoid MSVC's buggy ternary operator for expensive to destruct things
    if(this->_domain != nullptr)
    {
      return string_ref(this->domain()._do_message(*this));
    }
    return string_ref("(empty)");
  }
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
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 ~status_code()
  {
    if(nullptr != this->_domain)
    {
      this->_domain->_do_erased_destroy(*this, sizeof(*this));
    }
  }

  //! Return a copy of the erased code by asking the domain to perform the erased copy.
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR20 status_code clone() const
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
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class DomainType)                                                                        //
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(std::is_trivially_copyable<typename DomainType::value_type>::value  //
                                              &&detail::type_erasure_is_safe<value_type, typename DomainType::value_type>::value))
  constexpr status_code(const status_code<DomainType> &v) noexcept  // NOLINT
      : _base(typename _base::_value_type_constructor{}, v._domain_ptr(), detail::erasure_cast<value_type>(v.value()))
  {
  }
  //! Implicit move construction from any other status code if its value type is trivially copyable or move bitcopying and it would fit into our storage
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class DomainType)  //
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(detail::type_erasure_is_safe<value_type, typename DomainType::value_type>::value))
  BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 status_code(status_code<DomainType> &&v) noexcept  // NOLINT
      : _base(typename _base::_value_type_constructor{}, v._domain_ptr(), detail::erasure_cast<value_type>(v.value()))
  {
    v._domain = nullptr;
  }
  //! Implicit construction from any type where an ADL discovered `make_status_code(T, Args ...)` returns a `status_code`.
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class T, class... Args,                                                                                 //
                         class MakeStatusCodeResult = typename detail::safe_get_make_status_code_result<T, Args...>::type)       // Safe ADL lookup of make_status_code(), returns void if not found
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(!std::is_same<typename std::decay<T>::type, status_code>::value                    // not copy/move of self
                                              && !std::is_same<typename std::decay<T>::type, value_type>::value                  // not copy/move of value type
                                              && is_status_code<MakeStatusCodeResult>::value                                     // ADL makes a status code
                                              && std::is_constructible<status_code, MakeStatusCodeResult>::value))               // ADLed status code is compatible
  constexpr status_code(T &&v, Args &&...args) noexcept(noexcept(make_status_code(std::declval<T>(), std::declval<Args>()...)))  // NOLINT
      : status_code(make_status_code(static_cast<T &&>(v), static_cast<Args &&>(args)...))
  {
  }

  //! Implicit construction from any `quick_status_code_from_enum<Enum>` enumerated type.
  BOOST_OUTCOME_SYSTEM_ERROR2_TEMPLATE(class Enum,                                                                                //
                         class QuickStatusCodeType = typename quick_status_code_from_enum<Enum>::code_type)         // Enumeration has been activated
  BOOST_OUTCOME_SYSTEM_ERROR2_TREQUIRES(BOOST_OUTCOME_SYSTEM_ERROR2_TPRED(std::is_constructible<status_code, QuickStatusCodeType>::value))      // Its status code is compatible
  constexpr status_code(Enum &&v) noexcept(std::is_nothrow_constructible<status_code, QuickStatusCodeType>::value)  // NOLINT
      : status_code(QuickStatusCodeType(static_cast<Enum &&>(v)))
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
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
*/