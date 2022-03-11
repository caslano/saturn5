/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   record_view.hpp
 * \author Andrey Semashev
 * \date   09.03.2009
 *
 * This header contains a logging record view class definition.
 */

#ifndef BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_
#define BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/keyword_fwd.hpp>
#ifndef BOOST_LOG_NO_THREADS
#include <boost/detail/atomic_count.hpp>
#endif // BOOST_LOG_NO_THREADS
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS
class core;
class record;
#endif // BOOST_LOG_DOXYGEN_PASS

/*!
 * \brief Logging record view class
 *
 * The logging record encapsulates all information related to a single logging statement,
 * in particular, attribute values view and the log message string. The view is immutable,
 * it is implemented as a wrapper around a reference-counted implementation.
 */
class record_view
{
    BOOST_COPYABLE_AND_MOVABLE(record_view)

    friend class core;
    friend class record;

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Private data
    struct private_data;
    friend struct private_data;

    //! Publicly available record data
    struct public_data
    {
        //! Reference counter
#ifndef BOOST_LOG_NO_THREADS
        mutable boost::detail::atomic_count m_ref_counter;
#else
        mutable unsigned int m_ref_counter;
#endif // BOOST_LOG_NO_THREADS

        //! Attribute values view
        attribute_value_set m_attribute_values;

        //! Constructor from the attribute value set
        explicit public_data(BOOST_RV_REF(attribute_value_set) values) BOOST_NOEXCEPT :
            m_ref_counter(1),
            m_attribute_values(boost::move(values))
        {
        }

        //! Destructor
        BOOST_LOG_API static void destroy(const public_data* p) BOOST_NOEXCEPT;

    protected:
        ~public_data() {}

        BOOST_DELETED_FUNCTION(public_data(public_data const&))
        BOOST_DELETED_FUNCTION(public_data& operator= (public_data const&))

        friend void intrusive_ptr_add_ref(const public_data* p) BOOST_NOEXCEPT { ++p->m_ref_counter; }
        friend void intrusive_ptr_release(const public_data* p) BOOST_NOEXCEPT { if (--p->m_ref_counter == 0) public_data::destroy(p); }
    };

private:
    //! A pointer to the log record implementation
    intrusive_ptr< public_data > m_impl;

private:
    //  A private constructor, accessible from record
    explicit record_view(public_data* impl) BOOST_NOEXCEPT : m_impl(impl, false) {}

#endif // BOOST_LOG_DOXYGEN_PASS

public:
    /*!
     * Default constructor. Creates an empty record view that is equivalent to the invalid record handle.
     *
     * \post <tt>!*this == true</tt>
     */
    BOOST_CONSTEXPR record_view() BOOST_NOEXCEPT
#if !defined(BOOST_LOG_NO_CXX11_DEFAULTED_NOEXCEPT_FUNCTIONS) && !defined(BOOST_LOG_NO_CXX11_DEFAULTED_CONSTEXPR_CONSTRUCTORS)
        = default;
#else
    {}
#endif

    /*!
     * Copy constructor
     */
    record_view(record_view const& that) BOOST_NOEXCEPT : m_impl(that.m_impl) {}

    /*!
     * Move constructor. Source record contents unspecified after the operation.
     */
    record_view(BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Destructor. Destroys the record, releases any sinks and attribute values that were involved in processing this record.
     */
    ~record_view() BOOST_NOEXCEPT {}

    /*!
     * Copy assignment
     */
    record_view& operator= (BOOST_COPY_ASSIGN_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl = that.m_impl;
        return *this;
    }

    /*!
     * Move assignment. Source record contents unspecified after the operation.
     */
    record_view& operator= (BOOST_RV_REF(record_view) that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
        return *this;
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
     * Equality comparison
     *
     * \param that Comparand
     * \return \c true if both <tt>*this</tt> and \a that identify the same log record or both do not
     *         identify any record, \c false otherwise.
     */
    bool operator== (record_view const& that) const BOOST_NOEXCEPT
    {
        return m_impl == that.m_impl;
    }

    /*!
     * Inequality comparison
     *
     * \param that Comparand
     * \return <tt>!(*this == that)</tt>
     */
    bool operator!= (record_view const& that) const BOOST_NOEXCEPT
    {
        return !operator== (that);
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
    void swap(record_view& that) BOOST_NOEXCEPT
    {
        m_impl.swap(that.m_impl);
    }

    /*!
     * Resets the log record handle. If there are no other handles left, the log record is closed
     * and all resources referenced by the record are released.
     *
     * \post <tt>!*this == true</tt>
     */
    void reset() BOOST_NOEXCEPT
    {
        m_impl.reset();
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
};

/*!
 * A free-standing swap function overload for \c record_view
 */
inline void swap(record_view& left, record_view& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_RECORD_VIEW_HPP_INCLUDED_

/* record_view.hpp
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
*/