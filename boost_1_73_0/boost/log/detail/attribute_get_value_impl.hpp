/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_get_value_impl.hpp
 * \author Andrey Semashev
 * \date   04.08.2012
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

inline attribute_value attribute::get_value() const
{
    return m_pImpl->get_value();
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DETAIL_ATTRIBUTE_GET_VALUE_IMPL_HPP_INCLUDED_

/* attribute_get_value_impl.hpp
qLlKiKY0Ek3qjTf6/Ce0NXDcCNkE0Y3GI2XHDqAhgp7NdDjO1IsyYBpOscsyHuEOFd8ZveOoD3CpugtCM9LCLvGMDY2WmPEZyrGzlnH3f4PX52jNC04YaSB/bIGMp842hCIX7AHex/3OCnyM8L+NjyG//JhjGJ5JFHhZlLtgQRSroy3GoaUR2xEW8RmWUToSo7dpKAsCzogI3hiMIEVzbS/dF6V7JSCuhK5hlCuTD3Dt+fhq
*/