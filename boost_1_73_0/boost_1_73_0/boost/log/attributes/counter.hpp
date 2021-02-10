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
6uADbWHP7314jnwNy3goeOMwGZYKaKLi93e7xAtAtcr5vIqwcXpesGtQnrCXgC4uLwA9cgVZHA4Biu97D9JMzongcJnx6Uc6ac8jsv7TevB9a4O1QE+1NvwGQMWjDxu8xRNsMUqLdjy9etIOR6PcbOu2eKq1eNqoRYgtcpj1bNJGVtrU6dMh2wywTXQ+8jbwYnmBLbJwVl7stAcRbG4L6RpiC5i5FEy5NqrWbFbqbdwWezT27KKNPJZgc1uMCEc8hQ2y8M2K2+Kl4m8KIjAOh9GicUTUIi5wr2lH0+LKQiQXk4QfS/gkya7bsAfmKNuAr81Fx4bv0ly4/Xr7Fz8o6thkFawnUMlJfBlxZQ1GyySEP2ghIwSZP23+K5o9WX55z+g+TEqwAs8vAEgfJNouaOSA8UYLFs0XTQEB3fuSkzDCKw//XU6eY4syd3iut7Al9RW2SafpvDWnc/NC4WiHxTCOm6yG19gmTGqR2Diw01YSg0XZzsPSHYw78vd8LUzIhItG3hY6hn/zUbSjdAh2cHruG4UOf8ll7jwqSu8YbPiEuBqdZ2XsG4ADPyH4Mpk05NAbCd++HtStSx0eOd9Cg3hYLxk6fEYzlt6iPlrQvzBVNNOEephiD9dk8SzimDBlqNkf2GxcTtvDPALO
*/