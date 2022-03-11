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