/* Policies for result and outcome
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

#ifndef BOOST_OUTCOME_POLICY_RESULT_EXCEPTION_PTR_RETHROW_HPP
#define BOOST_OUTCOME_POLICY_RESULT_EXCEPTION_PTR_RETHROW_HPP

#include "../bad_access.hpp"
#include "base.hpp"

BOOST_OUTCOME_V2_NAMESPACE_EXPORT_BEGIN

namespace policy
{
  /*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
  template <class T, class EC, class E> struct exception_ptr_rethrow;
  template <class T, class EC> struct exception_ptr_rethrow<T, EC, void> : base
  {
    template <class Impl> static constexpr void wide_value_check(Impl &&self)
    {
      if(!base::_has_value(std::forward<Impl>(self)))
      {
        if(base::_has_error(std::forward<Impl>(self)))
        {
          // ADL
          rethrow_exception(policy::exception_ptr(base::_error(std::forward<Impl>(self))));
        }
        BOOST_OUTCOME_THROW_EXCEPTION(bad_result_access("no value"));  // NOLINT
      }
    }
    template <class Impl> static constexpr void wide_error_check(Impl &&self)
    {
      if(!base::_has_error(std::forward<Impl>(self)))
      {
        BOOST_OUTCOME_THROW_EXCEPTION(bad_result_access("no error"));  // NOLINT
      }
    }
  };
}  // namespace policy

BOOST_OUTCOME_V2_NAMESPACE_END

#endif

/* result_exception_ptr_rethrow.hpp
xvDxneQ+tKUWsDYyN+Uix4K77/+ZDqG2bW3n8nnsWRnQj1L173zxWEtjcxd1srebhgYt8HPafGL9pX3A/JP/hVzT7+KGekqcizJFB5g3rVAMuPHONZS7JDG9riBWfLkc1jFK+775q6Or8vtmqCFfpfe8ItzDfJgsDjru/FAnwHWhCKEJxfr3DTbD/fygpnUxGLWy2vxT6K4vcQn2MK1nEjedC/u0QHkHBvPzySEBIGUsnrSCo8fJkrwaodc6XhtMkkR0Z8g5eGpe5uuUhUl3OkZF/3LQRfl80FmlhVrA8E/m9ARviAHTPiLAx78z5IswPebe6ObIuIuuDry6z+bGc3fltTxfQxWk6wlYcQhD71dI0+QYad0i3G0ebnzIKps8OD4lkm2Zoj8LWDQGVKwHsUGYJMTMcTAgKEVLp3Ihds4BluberwTzZveF+Fdtajb7TcE8OizYr7J44fu+J3e1tVxa9qSvvFEi6fEa4acchm5SwhaieNqgJifbSPPFwGm37TguD37hJ9Jcs9ausuV5ykRFOIvmALO7fCiMiD1oadz09Rbxc5KyzAg+5w==
*/