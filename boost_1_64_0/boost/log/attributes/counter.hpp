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
/JFxX69PJC2SrqrIVklXe7kf7ACjYBfYCHaFrWE3OAB2h0PgUDgU9oETYF/4C9gPLof94XrR2wAHwc1wMNwCh8CtYr8NdoRHYBI8psxlvuaSdXyyRjEPtkTmyvz/IdIXAjdKOWyC0XIdK9cJcDMcBB+R8vgEDoO/lH7tMZgNH4dz4Va4AO6ES+GT8D64C26GT0t/9gx8Bu6B++CzUg774XF4EP4FvgS/hEfgP+DLMJA0HIWV4DEYAU/AmvBVWBe+BpvBUzAJvg77wjdgf/g2HAffhRPgGTgJvgenwvdhLvwALoBn4VL4CbwHvgC3wo/gU7AAHoAfw+Pwj/BV0df9Wkfdjnz2k1cwzBY91oopvSTkgpQbceN5BzqwGpwJB8DZcBKcB+fAX8C1cCHcAhfBbXA53AtXwMNwJTwKV8PT8H74GVwDr8IH4Q9wHSxjzhNhObge1ocbYBO4EbaAm2AXuBneBB+ByXALHAMfh2PhNpgOt8PJcAecCp+A98CdcBV8Eq6Bu+E2+BTcC5+GB+Ae+DzcB7+AL8Cv4SH4HTwMy5KPL8JQ+BIMgy/DSHgUxsBjsDX8DewET8Au8LewP3wVDoGvw9HwAJwAfw0z4Ry4CObDh+Bb8En4NtwD34EH4Gn4MnwXvgJnwVflmvLnvlXW9ID7pfy7IEHyPYnLcjb8FdgKXoOJ8HvYFf4DDoIu/LsdBsA7YCDMgmXgLFgW/gKWk/v38nANDIU7YEX4LAyDB2FleAJWgW/AqvB9GAE/glFSb+rC72EDSByMhrAibASrwBtgNGwGG8IW8AbYEraFrWAHGA/7wwR4C2wDR8P2cBzsAGfDTnAB7AwXwy7wftgVroPd4Q7YAz4Le8KDsDc8AvvBAjgAXoID4TdwEAwgzwfDIHgzDIHDYAQcDmNhJmwO74Dt4STYEY6EPeAo2AeOhjfDMXA4TIM54n62uF8k7pfDbynHe+Va+g9Zp0JeX2e8Hqv1fI/Xy/R6CfoCh/v5RTJeL4GV4VIYCZfBOHiPjA8PwLamH3AgXCnjwr0wB66Cs0QvD66GS+D9cLmYX4LJeh0A01OJT1mkp8SnpTzvbQXVeyNYH7aGDWEbGXcTYFt1Lc9zXfKuXd7750FTL0n60z8RfkX4ucznv5J5xmWZv38NJ8IrcAq8Cu+C12Sc+x7eC3+AD0AX4T4GA+B2GAR3w7LwZVgOvg7Lw7dhRXgGhsECWAmeg+HwIqwMv4YRMMRFmcIwWA3WgNEwBtaEtWEt2AHGws6wLhwC68HbYH2YAhvCTPiFed8BG3O9HjaBu+AN8DnYFJ6AzaCex/fS9cvnOHYGKRC9MpLv0cgp0cuUedMUGAqnwsYwCzaDK2FLOB12hzPgaDgbpsA5MA/eCdfAuXCDuNsI58FH4Xz4HPwF/B1cKPm9CF6AiyVdS+EVcf8dvAd+D5fDf8AVMNiFvejn6XePxMnh+e5wSd8IGAnHynwwVeaDaTIfHA+HwnQ4DGbAkWI+Co6BM+BtME/M5wYyJ09wf3M7vE15IxEZgSxDfH0v4yB2Z5C1HTCHddryTWtkIrISaYBuLg9O9vC39XsaIxYEWL6pgdujP+93NYY1C/xJv61xkvT5+r5GzLF/zzc2zhKm9TsbScc839pAF7vQduWLfHPjEOm+BpPRzT5Wsu9vNGhX/kd/g2ME0tX8u135f9u3ONLxexGyFTmCnEWuIdHtqcvICCQP2YQcQgqQconljThkDLISOYicR6JvpDyRMchc5AnkNGJ04NvryABkMrIS2YecQa4h0R1xh4xF5iNbkCPIOaRcEu0B6YtMRlYiu5FTyIWk0u+IlP5Kfz/H7+c5/59FrhN/mu//LaptFJ4=
*/