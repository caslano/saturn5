/* Policies for result and outcome
(C) 2017-2020 Niall Douglas <http://www.nedproductions.biz/> (12 commits)
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

#ifndef BOOST_OUTCOME_POLICY_OUTCOME_ERROR_CODE_THROW_AS_SYSTEM_ERROR_HPP
#define BOOST_OUTCOME_POLICY_OUTCOME_ERROR_CODE_THROW_AS_SYSTEM_ERROR_HPP

#include "result_error_code_throw_as_system_error.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

namespace policy
{
  /*! AWAITING HUGO JSON CONVERSION TOOL 
type definition  error_code_throw_as_system_error. Potential doc page: NOT FOUND
*/
  template <class T, class EC, class E> struct error_code_throw_as_system_error : base
  {
    template <class Impl> static constexpr void wide_value_check(Impl &&self)
    {
      if(!base::_has_value(std::forward<Impl>(self)))
      {
        if(base::_has_exception(std::forward<Impl>(self)))
        {
          detail::_rethrow_exception<trait::is_exception_ptr_available<E>::value>{base::_exception<T, EC, E, error_code_throw_as_system_error>(std::forward<Impl>(self))};  // NOLINT
        }
        if(base::_has_error(std::forward<Impl>(self)))
        {
          // ADL discovered
          outcome_throw_as_system_error_with_payload(base::_error(std::forward<Impl>(self)));
        }
        BOOST_OUTCOME_THROW_EXCEPTION(bad_outcome_access("no value"));  // NOLINT
      }
    }
    template <class Impl> static constexpr void wide_error_check(Impl &&self)
    {
      if(!base::_has_error(std::forward<Impl>(self)))
      {
        BOOST_OUTCOME_THROW_EXCEPTION(bad_outcome_access("no error"));  // NOLINT
      }
    }
    template <class Impl> static constexpr void wide_exception_check(Impl &&self)
    {
      if(!base::_has_exception(std::forward<Impl>(self)))
      {
        BOOST_OUTCOME_THROW_EXCEPTION(bad_outcome_access("no exception"));  // NOLINT
      }
    }
  };
}  // namespace policy

BOOST_OUTCOME_V2_NAMESPACE_END

#endif

/* outcome_error_code_throw_as_system_error.hpp
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
*/