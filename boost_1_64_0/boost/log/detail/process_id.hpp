/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   process_id.hpp
 * \author Andrey Semashev
 * \date   12.09.2009
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

#include <iosfwd>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/id.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! The process id descriptor
struct process
{
    typedef unsigned long native_type;
    typedef boost::log::aux::id< process > id;
};

namespace this_process {

//! The function returns current process identifier
BOOST_LOG_API process::id get_id();

} // namespace this_process

template< typename CharT, typename TraitsT >
BOOST_LOG_API std::basic_ostream< CharT, TraitsT >&
operator<< (std::basic_ostream< CharT, TraitsT >& strm, process::id const& pid);

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_PROCESS_ID_HPP_INCLUDED_

/* process_id.hpp
/6IomtH+6xjfKiRzF8K3CUFZrwkrp8kAPOVvGD2di+DrL2ErRsVhZgC45TyUXZhsDKlljEk639Wx/UWMo00x1kJg6x55GVGdmdzkKeAj8w4yQIY1oSaDPvzaH5y/Jmm04/0n5fB3/uSLZUQgCNVD/hgVUT+fLblVCBQMFMIZpgiOszFVCBmh+XdqnXLGZZcGOyUrzNk2KcJnq/iZ1/NfEKxRMrF3osSlMqUNlLA+Ew8i9ij0EcihNqwBip2jL3NTM7eFav++h2ShIDkFAcjNSnVQUAkdW8MRp7NJDc1/rdNVGXLO4D4qFpSt/NorchZOLDlW4I03EjJCpKwIgG8X+dUU46SpvviHBCyWA5MspuvVJTkzmAM5fdHiPwJzqTiaPRadVzFvK141HqEXqFoAwIVBZWCe9fhmmEVNO9aCnmkkO6rYA37E5dBgzWTexFStASQCOlq6alk/ezOplkl2DfU03LeXEdLpbesvYrGADbEC/FxQxOxj+JeA0a7aYgZgS9x4kdPlDP4YW8+3XoDwQaLH1E2mWI0A4UJDfn1l9x0I9Y8YaqMNCqjzKA==
*/