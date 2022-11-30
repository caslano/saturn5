/* Proposed SG14 status_code
(C) 2018 - 2021 Niall Douglas <http://www.nedproductions.biz/> (5 commits)
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

  virtual const status_code<void> &_do_code() const noexcept = 0;

public:
  //! The type of the status domain
  using domain_type = void;
  //! The type of the status code
  using status_code_type = status_code<void>;

public:
  //! The erased status code which generated this exception instance.
  const status_code<void> &code() const noexcept { return _do_code(); }
};

/*! Exception type representing a thrown status_code
 */
template <class DomainType> class status_error : public status_error<void>
{
  status_code<DomainType> _code;
  typename DomainType::string_ref _msgref;

  virtual const status_code<void> &_do_code() const noexcept override final { return _code; }

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
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
*/