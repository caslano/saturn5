/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   counter.hpp
 * \author Andrey Semashev
 * \date   01.05.2007
 *
 * The header contains implementation of the counter attribute.
 */

#ifndef BOOST_LOG_ATTRIBUTES_COUNTER_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_COUNTER_HPP_INCLUDED_

#include <boost/static_assert.hpp>
#include <boost/type_traits/is_integral.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/memory_order.hpp>
#include <boost/atomic/atomic.hpp>
#endif // BOOST_LOG_NO_THREADS
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that counts an integral value
 *
 * This attribute acts as a counter - it returns a monotonously
 * changing value each time requested. The attribute value type can be specified
 * as a template parameter. The type must be an integral type.
 */
template< typename T >
class counter :
    public attribute
{
    BOOST_STATIC_ASSERT_MSG(is_integral< T >::value, "Boost.Log: Only integral types are supported by the counter attribute");

public:
    //! A counter value type
    typedef T value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute::impl
    {
    private:
#ifndef BOOST_LOG_NO_THREADS
        boost::atomic< value_type > m_counter;
#else
        value_type m_counter;
#endif
        const value_type m_step;

    public:
        impl(value_type initial, value_type step) BOOST_NOEXCEPT :
            m_counter(initial), m_step(step)
        {
        }

        attribute_value get_value()
        {
#ifndef BOOST_LOG_NO_THREADS
            value_type value = m_counter.fetch_add(m_step, boost::memory_order_relaxed);
#else
            value_type value = m_counter;
            m_counter += m_step;
#endif
            return make_attribute_value(value);
        }
    };

public:
    /*!
     * Constructor
     *
     * \param initial Initial value of the counter
     * \param step Changing step of the counter. Each value acquired from the attribute
     *        will be greater than the previous one by this amount.
     */
    explicit counter(value_type initial = (value_type)0, value_type step = (value_type)1) :
        attribute(new impl(initial, step))
    {
    }

    /*!
     * Constructor for casting support
     */
    explicit counter(cast_source const& source) :
        attribute(source.as< impl >())
    {
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_COUNTER_HPP_INCLUDED_

/* counter.hpp
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
*/