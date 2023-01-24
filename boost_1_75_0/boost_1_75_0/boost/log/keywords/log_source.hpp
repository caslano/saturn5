/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/log_source.hpp
 * \author Andrey Semashev
 * \date   14.03.2009
 *
 * The header contains the \c log_source keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword is used to pass event log source name to a sink backend
BOOST_PARAMETER_KEYWORD(tag, log_source)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_LOG_SOURCE_HPP_INCLUDED_

/* log_source.hpp
J/BWG/lH1xW1+fl/m/46W9YNOcLORj10E/4rIWcVFAd0heHgHkoJbiEQXII7BLfgrou7u+5CKO4enODu7gmui7u76+LLbr0PbaeduXfu3PNw3r///8/xRDYr4DtWms+ljyuHZQAVnOfAxxQvRC86TZqzvb/I1u8Iu3CKvYsdrmbAJ0TbM/K9RYCZ2pOtE7FjsbndoniTZAVdS4YXZaQ8/4/3khCD4xchKROjlrNOi4s6L12zNIo0itG2ljlSFcR1Cq1Ihk8UeiE+EfZt2TCWE7khAhuh9ri9T1GuXZYq8SN/9JJS91qJvtzL/aZHwH6yvYzRjf95Arw94ZpOEps6YHHu6bN9kxtz0KIlH8gW/zZNquI0fPdDnMJ9OAmD2b5DJOPdcLe8uaE/C6Nl9feAOu0upsRvX62lQld5CcQLjrwUO4WMP6TfU8y0/bzw8g7YeDh+oB2unmYlMSCKHkrp7mDB8MU38iMTkKmTiLdAM5vunv6EcPau4osMRu7qFNMlCV+hdihLt96um2BOlJ3eMG08pblAqcIUS3eKatrH0t0cOdDSg/5qs6MHAOMvrfau9X9XWyGs0Zn6TTW5a33vRtRf/iOH+7c0cwXrNPEblRX6n+eFxxvqyt7rs++zvOSYxQVb2htMOX+xpnm5w8SFVmg6jF6+sDEuVFk4D0VtE+Vu2cV5Sz98HtMW4pjb0ZN6nKbBmDRlXy4b9wpM
*/