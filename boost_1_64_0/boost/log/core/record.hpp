/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

#include <boost/move/core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#include <boost/log/core/record_view.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

class core;

/*!
 * \brief Logging record class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The record can be updated before pushing
 * for further processing to the logging core.
 */
class record
{
    BOOST_MOVABLE_BUT_NOT_COPYABLE(record)

    friend class core;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    typedef record_view::public_data public_data;

private:
    //! A pointer to the log record implementation
    public_data* m_impl;

private:
    //  A private constructor, accessible from core
    BOOST_CONSTEXPR explicit record(public_data* impl) BOOST_NOEXCEPT : m_impl(impl) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record() BOOST_NOEXCEPT : m_impl(NULL) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record(BOOST_RV_REF(record) that) BOOST_NOEXCEPT : m_impl(that.m_impl)
    {
        that.m_impl = NULL;
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record() BOOST_NOEXCEPT
    {
        reset();
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record& operator= (BOOST_RV_REF(record) that) BOOST_NOEXCEPT
    {
        swap(static_cast< record& >(that));
        return *this;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set& attribute_values() BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * \return A reference to the set of attribute values attached to this record
     *
     * \pre <tt>!!*this</tt>
     */
    attribute_value_set const& attribute_values() const BOOST_NOEXCEPT
    {
        return m_impl->m_attribute_values;
    }

    /*!
     * Conversion to an unspecified boolean type
     *
     * \return \c true, if the <tt>*this</tt> identifies a log record, \c false, if the <tt>*this</tt> is not valid
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

    /*!
     * Inverted conversion to an unspecified boolean type
     *
     * \return \c false, if the <tt>*this</tt> identifies a log record, \c true, if the <tt>*this</tt> is not valid
     */
    bool operator! () const BOOST_NOEXCEPT
    {
        return !m_impl;
    }

    /*!
     * Swaps two handles
     *
     * \param that Another record to swap with
     * <b>Throws:</b> Nothing
     */
    void swap(record& that) BOOST_NOEXCEPT
    {
        public_data* p = m_impl;
        m_impl = that.m_impl;
        that.m_impl = p;
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        if (m_impl)
        {
            public_data::destroy(m_impl);
            m_impl = NULL;
        }
    }

    /*!
     * Attribute value lookup.
     *
     * \param name Attribute name.
     * \return An \c attribute_value, non-empty if it is found, empty otherwise.
     */
    attribute_value_set::mapped_type operator[] (attribute_value_set::key_type name) const
    {
        return m_impl->m_attribute_values[name];
    }

    /*!
     * Attribute value lookup.
     *
     * \param keyword Attribute keyword.
     * \return A \c value_ref with extracted attribute value if it is found, empty \c value_ref otherwise.
     */
    template< typename DescriptorT, template< typename > class ActorT >
    typename result_of::extract< typename expressions::attribute_keyword< DescriptorT, ActorT >::value_type, DescriptorT >::type
    operator[] (expressions::attribute_keyword< DescriptorT, ActorT > const& keyword) const
    {
        return m_impl->m_attribute_values[keyword];
    }

    /*!
     * The function ensures that the log record does not depend on any thread-specific data. Then the record contents
     * are used to construct a \c record_view which is returned from the function. The record is no longer valid after the call.
     *
     * \pre <tt>!!*this</tt>
     * \post <tt>!*this</tt>
     * \returns The record view that contains all attribute values from the original record.
     */
    BOOST_LOG_API record_view lock();
};

/*!
 * A free-standing swap function overload for \c record
 */
inline void swap(record& left, record& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_HPP_INCLUDED_

/* record.hpp
/TB5LGa0f/B0V48ILNiAPrixWZFudKbF+Rwv+/uoI0DhzcdlyNPbjd5EHrtoT9KocyKJ4zCujGO3uzTcthM9o9xCj/m0L3jgTaGX3NRwsZ/k1EqqoQWA1MvlmxruVJYJ7l8/z7QC4K8rUM9crMeP8LRXqdofuVgez0kA5liJzWHH2t52D1qCnyrbFfnoSuxY7CNSd5PY1KFAFOkP7hhTBMgaY0hM34f3U6j/J1gx/4piBWXjbizyCPbNTdl5wSEjTpoF7zODsMcE30prBKTpZ7t22ABHZZU66ur2lipE/01H6MR5R7MG1W9JmrwAMnM17oUjXAOhJPazKaXLYYqWHU5PVXjz/LmGrvxhuH/5zwPM8l1tC9su0eyTxNNHvSgIfnb1vacUcnSjo4aQ0iNhZu5DQCaJZEGaHurqBm8+o8Bnc66p3ZHx5RIRG8sMdru5v9JkQxSvI1bqOzXHeuXHm2TOnuILwmEOw+VGlJE/r1J7ompfIk0drFk1vX1S/4xEO0xn7jYx48ili145i7C2AZDgPiSWE5MQBHJc/t7AyzjLuL1QqFCofqVgSw==
*/