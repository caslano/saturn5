/*
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * Copyright (c) 2018 Andrey Semashev
 */
/*!
 * \file   atomic/detail/extra_fp_operations.hpp
 *
 * This header defines extra floating point atomic operations, including the generic version.
 */

#ifndef BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_
#define BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

#include <boost/atomic/detail/extra_fp_ops_generic.hpp>
#include <boost/atomic/detail/extra_fp_ops_emulated.hpp>

#if !defined(BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_GENERIC)
#include BOOST_ATOMIC_DETAIL_EXTRA_FP_BACKEND_HEADER(boost/atomic/detail/extra_fp_ops_)
#endif

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#endif // BOOST_ATOMIC_DETAIL_EXTRA_FP_OPERATIONS_HPP_INCLUDED_

/* extra_fp_operations.hpp
9Qh/kSBWlFyR6JpYbIfC0l/UIrWMO+fIyOo7dJgiCH8pJ1axHpYC1B+rXNM7DAaQRl70HaMqcKPDGPaw14Ej97+gGiWXoho9f5+bJXP9jIsMOfhmzMFGLxEnC12EV9x/6EIalwB2O4TxOVmdRd16vwqK27IgnS1CgTP40Oir95Wp8FHpU/hgXWf+QCe7NpVpbw9lsypHlOn44HNIn/z22MFPcqG3rRP4UCZibJWwyXc5bEvq1RBIUEKb/6r7tb4tJm3xaEEhtho9+pvML+9GnAa1Sxz5X71NLfpb0QTZmj9WoqSVyIiG6KvMrGDydAbY9VKi+Y3TKzAYxrjQJ0OTlAjUS55FlV060mZJYl0dhSftg1YdStlNTvJjNYM1o7kkprA3R1AzZ3C4jQn/dNqAQ74/JXMM85uC96L+9FL22DOgcEv/RFF+OnNI7FKZxTxnIHZJ9QCSFF7PXoR1cQr8XOJ/Yy68XiXFlA7IwzoH+CtW8L4Aw7rS+xmWtt2ucYEn/ofljH9Zeqe1YYi4vca9jjtd8YkySuryAPq49QT98hXaJox9gTHaNnOFG+b3hauuxrXc3lwxcn1VDeirb696Eb7tYDQ+vUtjWZd5OOSFbAhm48eFKoi6Waxdfq2OFq/OXbUQ9xX6cRCdMELan0rVJ6A4QaRAfY0X/RLXmHHzj4/rIQ6E/EzTY0wGNmTkaiNu+rRwfHbbEMMGw3+k
*/