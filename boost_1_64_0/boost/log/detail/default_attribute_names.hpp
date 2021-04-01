/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   default_attribute_names.hpp
 * \author Andrey Semashev
 * \date   15.01.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

namespace default_attribute_names {

BOOST_LOG_API attribute_name severity();
BOOST_LOG_API attribute_name channel();
BOOST_LOG_API attribute_name message();
BOOST_LOG_API attribute_name line_id();
BOOST_LOG_API attribute_name timestamp();
BOOST_LOG_API attribute_name process_id();
BOOST_LOG_API attribute_name thread_id();

} // namespace default_attribute_names

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_DEFAULT_ATTRIBUTE_NAMES_HPP_INCLUDED_

/* default_attribute_names.hpp
LIzESJVZSmB6pwUHwOskv+w/ekWHMdABQmCou8hw05Hi2v8z33VcINpbKZ4lu5DzbBaSa9hDnb0LvNJYppRhTsTBex7H10TLS1pGocMOllpO4pOKaJu/BLqQ0tDCR2wAPRnoLZIO7axat/MhOK+GWpGjs2vZPBEQDOBL5VxixE0erDe2EksQDvKrmUV3yCfWm0l2AODULiJ4UuJME980C5lx6vR3kctuqJM86ZNNiKhA7lqEZEYBBlws8h/d2Sg6D+SMb5NCI8UbG8lIyqKASdiRL4cv6iFA0p9y8gyZuQ37/l1jLDLwuWz4eupVyjdA4tlNzyly4zu4r3LBCy7L3u3ZHSJzXI27yiBtcLdpbiYPFIKBwYGImsoSxVk40kBu/Q/Fjeehey+xgOwPRRKhEtJ2s7aPRXrTUYuhAcTsjECF7c/X+gl8zN77a7vLjTbTQHfo/e85x3tiT4Oj3TJaAH9xJM88/T+3aZbCeivUYUXTllQOSPb5s2mHWkeO9lddpxFXQc5ZmzMYZKJMXRXnH1sNVk10fvfZ2aCLSy9CyxWc4+K4g0JS4Hc2qw==
*/