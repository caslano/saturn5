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
oUIGYqgWR2UVJ0h9sYGk2KyAfHqdg/OgsSek7RMZdiaMYHR5l2ctzFInbWFGXyd4QrqiHnxsyqbj17O16hSz8K/O8JLZObXkQ/roIf2xyCbhBQm8neWS1BetcOiS5ULZECDgZ1k0c2hh52UsIIF8/lbq4QAWk8A9Gvmk2+WchfpkT3nXUr08eD4MrMoirLWx8qf+3euW6s0UdT//aI7l7HSZxvdtIRwNSSnF5Ur9d1x3jIIiAwt7l1ZP1H0lw5lktoysvKJsBUKTYTuh7hMvheur7iWZCLAJxYJKUx68EQmCuPs2PxWZBafuF54G4ShywgkqqmRBtm5jVXYiY+LfnBKDt4AQfTzBvK+GBF7AvK66JhenjOMp7Tp81A8UtXoA3FvrO3IVPRAP1UYX/tF3Rkc5W1rylNR69ZEg456NorskKn8vMIHhywfJ3Q9PDratv1X5chjc2Snyqqvo44F0aPEB/Yh74lqNBdbFFT+q9Pmo8GQbnXFybyMPoXfion4/DTyzqu8LNvYF/mzzun9iYBLkjWVwm8cnd6ZPPth6oU1E/32B0yC1/sn+B6rRChJ+lzahp30t5CdGMq2AIg24OC3pwKtAgZKnxF9fMX6h4BitV7dOf4DW7gicg55Nz1NMOaf2sIXcgLr1XLykWv9s9KsTog60KMN534vyoKw8ZN7r+hP6qzPcbRUq/vbgrSzIfQOMy0i/CUx6mIFO
*/