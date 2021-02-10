/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   constant.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains implementation of a constant attribute.
 */

#ifndef BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/embedded_string_type.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that holds a single constant value
 *
 * The constant is a simplest and one of the most frequently used types of attributes.
 * It stores a constant value, which it eventually returns as its value each time
 * requested.
 */
template< typename T >
class constant :
    public attribute
{
public:
    //! Attribute value type
    typedef T value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute_value_impl< value_type >
    {
        //! Base type
        typedef attribute_value_impl< value_type > base_type;

    public:
        /*!
         * Constructor with the stored value initialization
         */
        explicit impl(value_type const& value) : base_type(value) {}
        /*!
         * Constructor with the stored value initialization
         */
        explicit impl(BOOST_RV_REF(value_type) value) : base_type(boost::move(value)) {}
    };

public:
    /*!
     * Constructor with the stored value initialization
     */
    explicit constant(value_type const& value) : attribute(new impl(value)) {}
    /*!
     * Constructor with the stored value initialization
     */
    explicit constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value))) {}
    /*!
     * Constructor for casting support
     */
    explicit constant(cast_source const& source) : attribute(source.as< impl >())
    {
    }

    /*!
     * \return Reference to the contained value.
     */
    value_type const& get() const
    {
        return static_cast< impl* >(this->get_impl())->get();
    }
};

/*!
 * The function constructs a \c constant attribute containing the provided value.
 * The function automatically converts C string arguments to \c std::basic_string objects.
 */
template< typename T >
inline constant<
    typename boost::log::aux::make_embedded_string_type<
        typename remove_reference< T >::type
    >::type
> make_constant(BOOST_FWD_REF(T) val)
{
    typedef typename boost::log::aux::make_embedded_string_type<
        typename remove_reference< T >::type
    >::type value_type;
    return constant< value_type >(boost::forward< T >(val));
}

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_CONSTANT_HPP_INCLUDED_

/* constant.hpp
+wKGMwyLiH86isZxGrHuUefFYTfYOzs9/CU4OT046u/fe/QAp5Nls5xl1ymb5nFajtfWgcHpEEWpYAY+FJYbCxXRMIhTkAXCZ30zHJ+jyPm+GQTT/Nz3RZZeRXnp+QYnsYwnvt7GWT6BFVH4vjuPSvgqnHi+uogSlDfPN0kMgxpnnm8mURkmcXrp+6o49/VF2C+Sqf+rIgIm+ToL49Ri9iSajKLBDKEZzN1lFE35+gd9cNjp9ZmEhGmDZmOYevam9/K4d+8zxoQcnPW6wc+dfv/xzr3PohQWcCUir6KyV+ZrID0bV2GyjkvrP+ztPcbi8doD/Hh9XXzA2DiPIvnhc/EZ/5PtsqOzw0P+4QfZfg17xOamOjbbwT+j2VTAyl6h8YrEtG43ZaATS1AH7KRz2nkTHB0Hb7pvKtQfUJcm0drW+r170MEMNqzDLD3vXWSgPP8DQCBsRcmGF2HOHoBwge54jpwtCCANJxGqPVgJyFELGr99zhA6gS5d4CidTQgHY53TV0DaUXeDEXxRgr5rh9AsYqB1WJrBzsEGMOlRKBrzNi+Ojw9Fm3A4jKYlzDRrt9Os/TuiewcrFmbuRm/S65/SHgJN8uiPWQz6CBVamJ/PJlFa6qD7B4egFN5062BBqRazMEluASltUDRE
*/