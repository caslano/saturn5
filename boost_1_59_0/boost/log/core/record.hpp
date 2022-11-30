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
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
*/