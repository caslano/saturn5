/* Exception observers for outcome type
(C) 2017-2020 Niall Douglas <http://www.nedproductions.biz/> (6 commits)
File Created: Oct 2017


Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.
*/

#ifndef BOOST_OUTCOME_BASIC_OUTCOME_EXCEPTION_OBSERVERS_IMPL_HPP
#define BOOST_OUTCOME_BASIC_OUTCOME_EXCEPTION_OBSERVERS_IMPL_HPP

#include "basic_outcome_exception_observers.hpp"

#include "../policy/base.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

namespace policy
{
  template <class R, class S, class P, class NoValuePolicy, class Impl> inline constexpr auto &&base::_exception(Impl &&self) noexcept
  {
    // Impl will be some internal implementation class which has no knowledge of the _ptr stored
    // beneath it. So statically cast, preserving rvalue and constness, to the derived class.
    using Outcome = BOOST_OUTCOME_V2_NAMESPACE::detail::rebind_type<basic_outcome<R, S, P, NoValuePolicy>, decltype(self)>;
#if defined(_MSC_VER) && _MSC_VER < 1920
    // VS2017 tries a copy construction in the correct implementation despite that Outcome is always a rvalue or lvalue ref! :(
    basic_outcome<R, S, P, NoValuePolicy> &_self = (basic_outcome<R, S, P, NoValuePolicy> &) (self);  // NOLINT
#else
    Outcome _self = static_cast<Outcome>(self);  // NOLINT
#endif
    return static_cast<Outcome>(_self)._ptr;
  }
}  // namespace policy

namespace detail
{
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::assume_exception() & noexcept
  {
    NoValuePolicy::narrow_exception_check(*this);
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(*this);
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr const typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::assume_exception() const &noexcept
  {
    NoValuePolicy::narrow_exception_check(*this);
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(*this);
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &&basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::assume_exception() && noexcept
  {
    NoValuePolicy::narrow_exception_check(std::move(*this));
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(std::move(*this));
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr const typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &&basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::assume_exception() const &&noexcept
  {
    NoValuePolicy::narrow_exception_check(std::move(*this));
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(std::move(*this));
  }

  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception() &
  {
    NoValuePolicy::wide_exception_check(*this);
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(*this);
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr const typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception() const &
  {
    NoValuePolicy::wide_exception_check(*this);
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(*this);
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &&basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception() &&
  {
    NoValuePolicy::wide_exception_check(std::move(*this));
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(std::move(*this));
  }
  template <class Base, class R, class S, class P, class NoValuePolicy> inline constexpr const typename basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception_type &&basic_outcome_exception_observers<Base, R, S, P, NoValuePolicy>::exception() const &&
  {
    NoValuePolicy::wide_exception_check(std::move(*this));
    return NoValuePolicy::template _exception<R, S, P, NoValuePolicy>(std::move(*this));
  }
}  // namespace detail

BOOST_OUTCOME_V2_NAMESPACE_END

#endif

/* basic_outcome_exception_observers_impl.hpp
4cIOI3zVf7JDTgNJXnAP7GTZJbc2qXNI4ee9hGI8g/2DZaMcKSNqbp23SnMPtSdqrzbJf6qrSfz0AKHz6sN9OcZzjqX14UxdGC7Xb0n7CaYORIP1QpZVBsxiGTQ6d9OGhkg8A3ItwcyGFrL/XtGp9LcB452Fx2Yq71JYQbSJYnfUVCIT/RLbClCK+y9FfSYwOORmpDhyhz67+K9Fdh0HbZHL1oYM9ay7k8Fg7dGU2THGZnKK6vu9C7+P5I4hogHoGmp/XmqJzeHu3qvZpWS0LZt3A85gCv+x0e07A3IFSa8HryCQobGpgM77TpdZXZetsMbcltOMXalAy/qv2aM9xAhuR8Bd0rIchuWZsqnzzq69HksDE3tTifHVlKA3keIsmFUbjRC9dYQU52SV+zPSkfp5VjQhJyjoES1dcHpVz+8ftrNI3V9icBlsHa8FrMymkKWn69QznUY7Ujq5zKL6qR3tZt6dZ1jZ5WTWIOLudW5E6lm2OgF1Lyvp+6eh0AFfqYQSQQJ4Xp8cMVGujdwpWsLfeSJTiblOkoyW5TEdim2xStIIN6LQadwnQA==
*/