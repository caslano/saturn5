/* Tries to convert an exception ptr into its equivalent error code
(C) 2017-2020 Niall Douglas <http://www.nedproductions.biz/> (11 commits)
File Created: July 2017


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

#ifndef BOOST_OUTCOME_UTILS_HPP
#define BOOST_OUTCOME_UTILS_HPP

#include "config.hpp"

#include <exception>
#include <string>
#include <system_error>

BOOST_OUTCOME_V2_NAMESPACE_BEGIN

#ifndef BOOST_NO_EXCEPTIONS
/*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
inline std::error_code error_from_exception(std::exception_ptr &&ep = std::current_exception(), std::error_code not_matched = std::make_error_code(std::errc::resource_unavailable_try_again)) noexcept
{
  if(!ep)
  {
    return {};
  }
  try
  {
    std::rethrow_exception(ep);
  }
  catch(const std::invalid_argument & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::invalid_argument);
  }
  catch(const std::domain_error & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::argument_out_of_domain);
  }
  catch(const std::length_error & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::argument_list_too_long);
  }
  catch(const std::out_of_range & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::result_out_of_range);
  }
  catch(const std::logic_error & /*unused*/) /* base class for this group */
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::invalid_argument);
  }
  catch(const std::system_error &e) /* also catches ios::failure */
  {
    ep = std::exception_ptr();
    return e.code();
  }
  catch(const std::overflow_error & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::value_too_large);
  }
  catch(const std::range_error & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::result_out_of_range);
  }
  catch(const std::runtime_error & /*unused*/) /* base class for this group */
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::resource_unavailable_try_again);
  }
  catch(const std::bad_alloc & /*unused*/)
  {
    ep = std::exception_ptr();
    return std::make_error_code(std::errc::not_enough_memory);
  }
  catch(...)
  {
  }
  return not_matched;
}

/*! AWAITING HUGO JSON CONVERSION TOOL 
SIGNATURE NOT RECOGNISED
*/
inline void try_throw_std_exception_from_error(std::error_code ec, const std::string &msg = std::string{})
{
  if(!ec || (ec.category() != std::generic_category()
#ifndef _WIN32
             && ec.category() != std::system_category()
#endif
             ))
  {
    return;
  }
  switch(ec.value())
  {
  case EINVAL:
    throw msg.empty() ? std::invalid_argument("invalid argument") : std::invalid_argument(msg);
  case EDOM:
    throw msg.empty() ? std::domain_error("domain error") : std::domain_error(msg);
  case E2BIG:
    throw msg.empty() ? std::length_error("length error") : std::length_error(msg);
  case ERANGE:
    throw msg.empty() ? std::out_of_range("out of range") : std::out_of_range(msg);
  case EOVERFLOW:
    throw msg.empty() ? std::overflow_error("overflow error") : std::overflow_error(msg);
  case ENOMEM:
    throw std::bad_alloc();
  }
}
#endif

BOOST_OUTCOME_V2_NAMESPACE_END

#endif

/* utils.hpp
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
*/