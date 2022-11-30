/* Proposed SG14 status_code
(C) 2018 - 2021 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Aug 2018


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

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_STD_ERROR_CODE_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_STD_ERROR_CODE_HPP

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_NOT_POSIX
#include "posix_code.hpp"
#endif

#if defined(_WIN32) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
#include "win32_code.hpp"
#endif

#include <system_error>

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

class _std_error_code_domain;
//! A `status_code` representing exactly a `std::error_code`
using std_error_code = status_code<_std_error_code_domain>;

namespace mixins
{
  template <class Base> struct mixin<Base, _std_error_code_domain> : public Base
  {
    using Base::Base;

    //! Implicit constructor from a `std::error_code`
    inline mixin(std::error_code ec);

    //! Returns the error code category
    inline const std::error_category &category() const noexcept;
  };
}  // namespace mixins


/*! The implementation of the domain for `std::error_code` error codes.
 */
class _std_error_code_domain final : public status_code_domain
{
  template <class DomainType> friend class status_code;
  template <class StatusCode> friend class detail::indirecting_domain;
  using _base = status_code_domain;
  using _error_code_type = std::error_code;
  using _error_category_type = std::error_category;

  std::string _name;

  static _base::string_ref _make_string_ref(_error_code_type c) noexcept
  {
#if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
    try
#endif
    {
      std::string msg = c.message();
      auto *p = static_cast<char *>(malloc(msg.size() + 1));  // NOLINT
      if(p == nullptr)
      {
        return _base::string_ref("failed to allocate message");
      }
      memcpy(p, msg.c_str(), msg.size() + 1);
      return _base::atomic_refcounted_string_ref(p, msg.size());
    }
#if defined(__cpp_exceptions) || defined(__EXCEPTIONS) || defined(_CPPUNWIND)
    catch(...) { return _base::string_ref("failed to allocate message"); }
#endif
  }

public:
  //! The value type of the `std::error_code` code, which stores the `int` from the `std::error_code`
  using value_type = int;
  using _base::string_ref;

  //! Returns the error category singleton pointer this status code domain represents
  const _error_category_type &error_category() const noexcept
  {
    auto ptr = 0x223a160d20de97b4 ^ this->id();
    return *reinterpret_cast<const _error_category_type *>(ptr);
  }

  //! Default constructor
  explicit _std_error_code_domain(const _error_category_type &category) noexcept
      : _base(0x223a160d20de97b4 ^ reinterpret_cast<_base::unique_id_type>(&category))
      , _name("std_error_code_domain(")
  {
    _name.append(category.name());
    _name.push_back(')');
  }
  _std_error_code_domain(const _std_error_code_domain &) = default;
  _std_error_code_domain(_std_error_code_domain &&) = default;
  _std_error_code_domain &operator=(const _std_error_code_domain &) = default;
  _std_error_code_domain &operator=(_std_error_code_domain &&) = default;
  ~_std_error_code_domain() = default;

  static inline const _std_error_code_domain *get(_error_code_type ec);

  virtual string_ref name() const noexcept override { return string_ref(_name.c_str(), _name.size()); }  // NOLINT
protected:
  virtual bool _do_failure(const status_code<void> &code) const noexcept override;
  virtual bool _do_equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept override;
  virtual generic_code _generic_code(const status_code<void> &code) const noexcept override;
  virtual string_ref _do_message(const status_code<void> &code) const noexcept override;
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
  BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN virtual void _do_throw_exception(const status_code<void> &code) const override;
#endif
};

namespace detail
{
  extern inline _std_error_code_domain *std_error_code_domain_from_category(const std::error_category &category)
  {
    static constexpr size_t max_items = 64;
    static struct storage_t
    {
      std::atomic<unsigned> _lock;
      union item_t
      {
        int _init;
        _std_error_code_domain domain;
        constexpr item_t()
            : _init(0)
        {
        }
        ~item_t() {}
      } items[max_items];
      size_t count{0};

      void lock()
      {
        while(_lock.exchange(1, std::memory_order_acquire) != 0)
          ;
      }
      void unlock() { _lock.store(0, std::memory_order_release); }

      storage_t() {}
      ~storage_t()
      {
        lock();
        for(size_t n = 0; n < count; n++)
        {
          items[n].domain.~_std_error_code_domain();
        }
        unlock();
      }
      _std_error_code_domain *add(const std::error_category &category)
      {
        _std_error_code_domain *ret = nullptr;
        lock();
        for(size_t n = 0; n < count; n++)
        {
          if(items[n].domain.error_category() == category)
          {
            ret = &items[n].domain;
            break;
          }
        }
        if(ret == nullptr && count < max_items)
        {
          ret = new(&items[count++].domain) _std_error_code_domain(category);
        }
        unlock();
        return ret;
      }
    } storage;
    return storage.add(category);
  }
}  // namespace detail

namespace mixins
{
  template <class Base>
  inline mixin<Base, _std_error_code_domain>::mixin(std::error_code ec)
      : Base(typename Base::_value_type_constructor{}, _std_error_code_domain::get(ec), ec.value())
  {
  }

  template <class Base> inline const std::error_category &mixin<Base, _std_error_code_domain>::category() const noexcept
  {
    const auto &domain = static_cast<const _std_error_code_domain &>(this->domain());
    return domain.error_category();
  };
}  // namespace mixins

inline const _std_error_code_domain *_std_error_code_domain::get(std::error_code ec)
{
  auto *p = detail::std_error_code_domain_from_category(ec.category());
  assert(p != nullptr);
  if(p == nullptr)
  {
    abort();
  }
  return p;
}


inline bool _std_error_code_domain::_do_failure(const status_code<void> &code) const noexcept
{
  assert(code.domain() == *this);
  return static_cast<const std_error_code &>(code).value() != 0;  // NOLINT
}

inline bool _std_error_code_domain::_do_equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept
{
  assert(code1.domain() == *this);
  const auto &c1 = static_cast<const std_error_code &>(code1);  // NOLINT
  const auto &cat1 = c1.category();
  // Are we comparing to another wrapped error_code?
  if(code2.domain() == *this)
  {
    const auto &c2 = static_cast<const std_error_code &>(code2);  // NOLINT
    const auto &cat2 = c2.category();
    // If the error code categories are identical, do literal comparison
    if(cat1 == cat2)
    {
      return c1.value() == c2.value();
    }
    // Otherwise fall back onto the _generic_code comparison, which uses default_error_condition()
    return false;
  }
  // Am I an error code with generic category?
  if(cat1 == std::generic_category())
  {
    // Convert to generic code, and compare that
    generic_code _c1(static_cast<errc>(c1.value()));
    return _c1 == code2;
  }
  // Am I an error code with system category?
  if(cat1 == std::system_category())
  {
// Convert to POSIX or Win32 code, and compare that
#ifdef _WIN32
    win32_code _c1((win32::DWORD) c1.value());
    return _c1 == code2;
#elif !defined(BOOST_OUTCOME_SYSTEM_ERROR2_NOT_POSIX)
    posix_code _c1(c1.value());
    return _c1 == code2;
#endif
  }
  return false;
}

inline generic_code _std_error_code_domain::_generic_code(const status_code<void> &code) const noexcept
{
  assert(code.domain() == *this);
  const auto &c = static_cast<const std_error_code &>(code);  // NOLINT
  // Ask my embedded error code for its mapping to std::errc, which is a subset of our generic_code errc.
  std::error_condition cond(c.category().default_error_condition(c.value()));
  if(cond.category() == std::generic_category())
  {
    return generic_code(static_cast<errc>(cond.value()));
  }
#if !defined(BOOST_OUTCOME_SYSTEM_ERROR2_NOT_POSIX) && !defined(_WIN32)
  if(cond.category() == std::system_category())
  {
    return generic_code(static_cast<errc>(cond.value()));
  }
#endif
  return errc::unknown;
}

inline _std_error_code_domain::string_ref _std_error_code_domain::_do_message(const status_code<void> &code) const noexcept
{
  assert(code.domain() == *this);
  const auto &c = static_cast<const std_error_code &>(code);  // NOLINT
  return _make_string_ref(_error_code_type(c.value(), c.category()));
}

#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN inline void _std_error_code_domain::_do_throw_exception(const status_code<void> &code) const
{
  assert(code.domain() == *this);
  const auto &c = static_cast<const std_error_code &>(code);  // NOLINT
  throw std::system_error(std::error_code(c.value(), c.category()));
}
#endif

static_assert(sizeof(std_error_code) <= sizeof(void *) * 2, "std_error_code does not fit into a system_code!");

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

// Enable implicit construction of `std_error_code` from `std::error_code`.
namespace std
{
  inline BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::std_error_code make_status_code(error_code c) noexcept { return BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE::std_error_code(c); }
}  // namespace std

#endif

/* std_error_code.hpp
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
*/