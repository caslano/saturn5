/*
 *             Copyright Andrey Semashev 2016.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/block_size.hpp
 * \author Andrey Semashev
 * \date   23.02.2016
 *
 * The header contains the \c block_size keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword allows to pass interprocess queue name to the queue constructor
BOOST_PARAMETER_KEYWORD(tag, block_size)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_BLOCK_SIZE_HPP_INCLUDED_

/* block_size.hpp
qNwUqmCam0MdOdeBt+VLP0Zdww69Qq9Ha9yhfVtEuHPD+Wzk/z6cnA9ParzWRiQreUSsYInVQGciqosR4qmkk1zm8oQMi+x1p6ZtOPUEuoGycrGjibOpbMM+XCDNVmmkQyJNGTzOkbEHc+jZI5ZLX9cWgi6CuDRTS7Ad+M81/9BJ4B+mvtkP9fPSU4n93vobUEsDBAoAAAAIAC1nSlKHTbtCTQIAAGoFAAAbAAkAY3VybC1tYXN0ZXIvc3JjL3Rvb2xfbXNncy5oVVQFAAG2SCRgrVTva9swEP2ev+KRfEmDZ3f7tG5lLKS/wrqkJCklUDCKfa40FMlIctpC//idnHRlsC6w9Yx9snTvvbuT5Z6qTEkVLk6HJ6ezfHQ9u8wX0+ll/n1+Ps8vOj1eVIZeXc8Gb2cdDLDX8vbO2di3iCtnf1AR/hyd50/YXoy6Zb9PJMML5Ck/wH7IE/otJN+pHMdxnu8Tuo25xUcWkbd5HPIMwyJyZOtHp+5kQH90gPdHRx/xDh8OPxwmOBFGkcY8kFmRu0twXLYzX6V4eEg9fUlAAUKnO6qFVB7eVuFeOAKPtSrIeCohPEryhVMrflEGQRIqpQmj6dVyPDlPcC9VISPJo23gpW10CSk2BEcFqc2WoxYuwFYMZ/JS+cCE
*/