/* Proposed SG14 status_code
(C) 2018-2020 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
File Created: Feb 2018


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

#ifndef BOOST_OUTCOME_SYSTEM_ERROR2_STATUS_ERROR_HPP
#define BOOST_OUTCOME_SYSTEM_ERROR2_STATUS_ERROR_HPP

#include "status_code.hpp"

#include <exception>  // for std::exception

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_BEGIN

/*! Exception type representing a thrown status_code
*/
template <class DomainType> class status_error;

/*! The erased type edition of status_error.
*/
template <> class status_error<void> : public std::exception
{
protected:
  //! Constructs an instance. Not publicly available.
  status_error() = default;
  //! Copy constructor. Not publicly available
  status_error(const status_error &) = default;
  //! Move constructor. Not publicly available
  status_error(status_error &&) = default;
  //! Copy assignment. Not publicly available
  status_error &operator=(const status_error &) = default;
  //! Move assignment. Not publicly available
  status_error &operator=(status_error &&) = default;
  //! Destructor. Not publicly available.
  ~status_error() override = default;

public:
  //! The type of the status domain
  using domain_type = void;
  //! The type of the status code
  using status_code_type = status_code<void>;
};

/*! Exception type representing a thrown status_code
*/
template <class DomainType> class status_error : public status_error<void>
{
  status_code<DomainType> _code;
  typename DomainType::string_ref _msgref;

public:
  //! The type of the status domain
  using domain_type = DomainType;
  //! The type of the status code
  using status_code_type = status_code<DomainType>;

  //! Constructs an instance
  explicit status_error(status_code<DomainType> code)
      : _code(static_cast<status_code<DomainType> &&>(code))
      , _msgref(_code.message())
  {
  }

  //! Return an explanatory string
  virtual const char *what() const noexcept override { return _msgref.c_str(); }  // NOLINT

  //! Returns a reference to the code
  const status_code_type &code() const & { return _code; }
  //! Returns a reference to the code
  status_code_type &code() & { return _code; }
  //! Returns a reference to the code
  const status_code_type &&code() const && { return _code; }
  //! Returns a reference to the code
  status_code_type &&code() && { return _code; }
};

BOOST_OUTCOME_SYSTEM_ERROR2_NAMESPACE_END

#endif

/* status_error.hpp
JXrA0yXh2ZiXRTzp899FzaXiKQ0d8q+PgQ==
*/