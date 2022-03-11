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
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
*/