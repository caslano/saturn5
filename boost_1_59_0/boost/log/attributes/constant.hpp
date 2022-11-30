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
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
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
        explicit impl(BOOST_RV_REF(value_type) value) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< value_type >::value) :
            base_type(boost::move(value))
        {
        }
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