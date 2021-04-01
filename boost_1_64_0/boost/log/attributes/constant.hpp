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
ynjEU4rIYL28JovIpd1KUmlgmay4VpXLsqc3LAzF1Fovt5cnz9zfgCZeMFtWSzoywTPrzvSx9vc23aT1A4iAxUhUIGmgFSn2V/BtC7VewU1RpHIYP0PlqbFS7/YydMcqwBbcE05GbzqJc5zZSbQoEhEvkgldJZrPrC7Rt74cnQmdKLEGSYc1nJFyuaKIozjLCR0lUQvlIdnclS+7RUlmMMGuEtRfyzexaVvq4TqXQ/r6+f05o7ikdX/y2c8In4VV1/6+VtemOu1W/fXGYTeGYgrODyTtFx2s/1mqmw16OV9yuc6e9I61pjzPeHBJ9bZN1tKChOvIARu9UtoKN6j/O/nOWZOdS+MvlKbwu2tzDFxsExSF9jfyHdIQW6FbEk76pdoljceNpGLNAW9Dcj9ViI5a0LgmaJzVPlFxLq/4FZWn786kBLeZXCV0KoGHMwBZibKagZu1PDzphZ8TsBwhb0pBYw2KYqJMaQhfYYtpPQ8gqj5nmALEkMZTFT0JZG2yYbkjBi4L7Mg4n/UWkhJk5KPtBPmoUBn2ow/gYlcRVyCLkvFzjq+P5bbhBw==
*/