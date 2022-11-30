/* Proposed SG14 status_code
(C) 2018 - 2020 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: May 2020


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

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_QUICK_STATUS_CODE_FROM_ENUM_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_QUICK_STATUS_CODE_FROM_ENUM_HPP

#include "generic_code.hpp"

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

template <class Enum> class _quick_status_code_from_enum_domain;
//! A status code wrapping `Enum` generated from `quick_status_code_from_enum`.
template <class Enum> using quick_status_code_from_enum_code = status_code<_quick_status_code_from_enum_domain<Enum>>;

//! Defaults for an implementation of `quick_status_code_from_enum<Enum>`
template <class Enum> struct quick_status_code_from_enum_defaults
{
  //! The type of the resulting code
  using code_type = quick_status_code_from_enum_code<Enum>;
  //! Used within `quick_status_code_from_enum` to define a mapping of enumeration value with its status code
  struct mapping
  {
    //! The enumeration type
    using enumeration_type = Enum;

    //! The value being mapped
    const Enum value;
    //! A string representation for this enumeration value
    const char *message;
    //! A list of `errc` equivalents for this enumeration value
    const std::initializer_list<errc> code_mappings;
  };
  //! Used within `quick_status_code_from_enum` to define mixins for the status code wrapping `Enum`
  template <class Base> struct mixin : Base
  {
    using Base::Base;
  };
};

/*! The implementation of the domain for status codes wrapping `Enum` generated from `quick_status_code_from_enum`.
 */
template <class Enum> class _quick_status_code_from_enum_domain : public status_code_domain
{
  template <class DomainType> friend class status_code;
  template <class StatusCode> friend class detail::indirecting_domain;
  using _base = status_code_domain;
  using _src = quick_status_code_from_enum<Enum>;

public:
  //! The value type of the quick status code from enum
  using value_type = Enum;
  using _base::string_ref;

  constexpr _quick_status_code_from_enum_domain()
      : status_code_domain(_src::domain_uuid, _uuid_size<detail::cstrlen(_src::domain_uuid)>())
  {
  }
  _quick_status_code_from_enum_domain(const _quick_status_code_from_enum_domain &) = default;
  _quick_status_code_from_enum_domain(_quick_status_code_from_enum_domain &&) = default;
  _quick_status_code_from_enum_domain &operator=(const _quick_status_code_from_enum_domain &) = default;
  _quick_status_code_from_enum_domain &operator=(_quick_status_code_from_enum_domain &&) = default;
  ~_quick_status_code_from_enum_domain() = default;

#if __cplusplus < 201402L && !defined(_MSC_VER)
  static inline const _quick_status_code_from_enum_domain &get()
  {
    static _quick_status_code_from_enum_domain v;
    return v;
  }
#else
  static inline constexpr const _quick_status_code_from_enum_domain &get();
#endif

  virtual string_ref name() const noexcept override { return string_ref(_src::domain_name); }

protected:
  // Not sure if a hash table is worth it here, most enumerations won't be long enough to be worth it
  // Also, until C++ 20's consteval, the hash table would get emitted into the binary, bloating it
  static BOOST_OUTCOME_SYSTEM_ERROR2_CONSTEXPR14 const typename _src::mapping *_find_mapping(value_type v) noexcept
  {
    for(const auto &i : _src::value_mappings())
    {
      if(i.value == v)
      {
        return &i;
      }
    }
    return nullptr;
  }

  virtual bool _do_failure(const status_code<void> &code) const noexcept override
  {
    assert(code.domain() == *this);  // NOLINT
    // If `errc::success` is in the generic code mapping, it is not a failure
    const auto *mapping = _find_mapping(static_cast<const quick_status_code_from_enum_code<value_type> &>(code).value());
    assert(mapping != nullptr);
    if(mapping != nullptr)
    {
      for(errc ec : mapping->code_mappings)
      {
        if(ec == errc::success)
        {
          return false;
        }
      }
    }
    return true;
  }
  virtual bool _do_equivalent(const status_code<void> &code1, const status_code<void> &code2) const noexcept override
  {
    assert(code1.domain() == *this);                                                                   // NOLINT
    const auto &c1 = static_cast<const quick_status_code_from_enum_code<value_type> &>(code1);  // NOLINT
    if(code2.domain() == *this)
    {
      const auto &c2 = static_cast<const quick_status_code_from_enum_code<value_type> &>(code2);  // NOLINT
      return c1.value() == c2.value();
    }
    if(code2.domain() == generic_code_domain)
    {
      const auto &c2 = static_cast<const generic_code &>(code2);  // NOLINT
      const auto *mapping = _find_mapping(c1.value());
      assert(mapping != nullptr);
      if(mapping != nullptr)
      {
        for(errc ec : mapping->code_mappings)
        {
          if(ec == c2.value())
          {
            return true;
          }
        }
      }
    }
    return false;
  }
  virtual generic_code _generic_code(const status_code<void> &code) const noexcept override
  {
    assert(code.domain() == *this);  // NOLINT
    const auto *mapping = _find_mapping(static_cast<const quick_status_code_from_enum_code<value_type> &>(code).value());
    assert(mapping != nullptr);
    if(mapping != nullptr)
    {
      if(mapping->code_mappings.size() > 0)
      {
        return *mapping->code_mappings.begin();
      }
    }
    return errc::unknown;
  }
  virtual string_ref _do_message(const status_code<void> &code) const noexcept override
  {
    assert(code.domain() == *this);  // NOLINT
    const auto *mapping = _find_mapping(static_cast<const quick_status_code_from_enum_code<value_type> &>(code).value());
    assert(mapping != nullptr);
    if(mapping != nullptr)
    {
      return string_ref(mapping->message);
    }
    return string_ref("unknown");
  }
#if defined(_CPPUNWIND) || defined(__EXCEPTIONS) || defined(BOOST_OUTCOME_STANDARDESE_IS_IN_THE_HOUSE)
  BOOST_OUTCOME_SYSTEM_ERROR2_NORETURN virtual void _do_throw_exception(const status_code<void> &code) const override
  {
    assert(code.domain() == *this);                                                                  // NOLINT
    const auto &c = static_cast<const quick_status_code_from_enum_code<value_type> &>(code);  // NOLINT
    throw status_error<_quick_status_code_from_enum_domain>(c);
  }
#endif
};

#if __cplusplus >= 201402L || defined(_MSC_VER)
template <class Enum> constexpr _quick_status_code_from_enum_domain<Enum> quick_status_code_from_enum_domain = {};
template <class Enum> inline constexpr const _quick_status_code_from_enum_domain<Enum> &_quick_status_code_from_enum_domain<Enum>::get()
{
  return quick_status_code_from_enum_domain<Enum>;
}
#endif

namespace mixins
{
  template <class Base, class Enum> struct mixin<Base, _quick_status_code_from_enum_domain<Enum>> : public quick_status_code_from_enum<Enum>::template mixin<Base>
  {
    using quick_status_code_from_enum<Enum>::template mixin<Base>::mixin;
  };
}  // namespace mixins

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif

/* quick_status_code_from_enum.hpp
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
*/