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
w/KNcptRjT1RgEFtlyeGILJ/fW10KcOa0ZgMe1Pg389eN/VcVzns9aNYv58jy6h/92KGqey+oD2MBlx106h7Djtt/mMH8XSpYAs5yn51lS5Qsj/XmyvAmTBZeOSvgo/6IqlKg/QmJwuC0McgeNm/ir3gO2KJzemGq+WxRJDkZCmZpOJ1UkQTxz/JmCoXnO1oaQ6huiWhnmH8usoJ7CWB13/anm3LcGjIyowHBuIilHYxAw+Csl8PvfU3iNOUN2FW3xwlR3B4YP2/cSkXnWqY13/ysWOdid1fuspTYVaYKBFtgGTgjyTKBOb4v8VZ3jpP5YyarO6WeBH174UT6lcfVULvr+WBJasJcPK5X3TBKE3XmATv2M43lS6GvNG+hE472T0PKr307hwTzq7T/Y1AmTnpCluMX+InRxbBsXgcWELaQvPZMRJvuiCU0Jq4GQLxA36IBXStxPnkvbLNe0BgZZ8v53lpmMNqiyr7GNIbHBIeKPcfH+8ONVa3OVmkTyoZKLH35LzIGdS5d0Dz9m1kysSnIVm/WH8Q2R++ECUTcYAqlWdO5Obrl6glQepl5ifhvU/uNvs4ciy/UM5NUDLG+Ob4ZCoI29HFq26MgklaJ9IyRSM9t88dr/+DGUr7z4UQgQIwAP7LEDtjKZo/PpmKP3o4afn+KeCSeNPYqMAfykCxD1R8JPjXToMVIdYUHOY1MXfRZsYUSmX3ehfj
*/