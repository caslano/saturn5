/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   attribute_value.hpp
 * \author Andrey Semashev
 * \date   21.05.2010
 *
 * The header contains \c attribute_value class definition.
 */

#ifndef BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/move/core.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/value_extraction_fwd.hpp>
#include <boost/log/attributes/value_visitation_fwd.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief An attribute value class
 *
 * An attribute value is an object that contains a piece of data that represents an attribute state
 * at the point of the value acquisition. All major operations with log records, such as filtering and
 * formatting, involve attribute values contained in a single view. Most likely an attribute value is
 * implemented as a simple holder of some typed value. This holder implements the
 * \c attribute_value::implementation interface and acts as a pimpl for the \c attribute_value
 * object. The \c attribute_value class provides type dispatching support in order to allow
 * to extract the value from the holder.
 *
 * Normally, attributes and their values shall be designed in order to exclude as much interference as
 * reasonable. Such approach allows to have more than one attribute value simultaneously, which improves
 * scalability and allows to implement generating attributes.
 *
 * However, there are cases when this approach does not help to achieve the required level of independency
 * of attribute values and attribute itself from each other at a reasonable performance tradeoff.
 * For example, an attribute or its values may use thread-specific data, which is global and shared
 * between all the instances of the attribute/value. Passing such an attribute value to another thread
 * would be a disaster. To solve this the library defines an additional method for attribute values,
 * namely \c detach_from_thread. The \c attribute_value class forwards the call to its pimpl,
 * which is supposed to ensure that it no longer refers to any thread-specific data after the call.
 * The pimpl can create a new holder as a result of this method and return it to the \c attribute_value
 * wrapper, which will keep the returned reference for any further calls.
 * This method is called for all attribute values that are passed to another thread.
 */
class attribute_value
{
    BOOST_COPYABLE_AND_MOVABLE(attribute_value)

public:
    /*!
     * \brief A base class for an attribute value implementation
     *
     * All attribute value holders should derive from this interface.
     */
    struct BOOST_LOG_NO_VTABLE impl :
        public attribute::impl
    {
    public:
        /*!
         * The method dispatches the value to the given object.
         *
         * \param dispatcher The object that attempts to dispatch the stored value.
         * \return true if \a dispatcher was capable to consume the real attribute value type and false otherwise.
         */
        virtual bool dispatch(type_dispatcher& dispatcher) = 0;

        /*!
         * The method is called when the attribute value is passed to another thread (e.g.
         * in case of asynchronous logging). The value should ensure it properly owns all thread-specific data.
         *
         * \return An actual pointer to the attribute value. It may either point to this object or another.
         *         In the latter case the returned pointer replaces the pointer used by caller to invoke this
         *         method and is considered to be a functional equivalent to the previous pointer.
         */
        virtual intrusive_ptr< impl > detach_from_thread()
        {
            return this;
        }

        /*!
         * \return The attribute value that refers to self implementation.
         */
        virtual attribute_value get_value() { return attribute_value(this); }

        /*!
         * \return The attribute value type
         */
        virtual typeindex::type_index get_type() const { return typeindex::type_index(); }
    };

private:
    //! Pointer to the value implementation
    intrusive_ptr< impl > m_pImpl;

public:
    /*!
     * Default constructor. Creates an empty (absent) attribute value.
     */
    BOOST_DEFAULTED_FUNCTION(attribute_value(), {})

    /*!
     * Copy constructor
     */
    attribute_value(attribute_value const& that) BOOST_NOEXCEPT : m_pImpl(that.m_pImpl) {}

    /*!
     * Move constructor
     */
    attribute_value(BOOST_RV_REF(attribute_value) that) BOOST_NOEXCEPT { m_pImpl.swap(that.m_pImpl); }

    /*!
     * Initializing constructor. Creates an attribute value that refers to the specified holder.
     *
     * \param p A pointer to the attribute value holder.
     */
    explicit attribute_value(intrusive_ptr< impl > p) BOOST_NOEXCEPT { m_pImpl.swap(p); }

    /*!
     * Copy assignment
     */
    attribute_value& operator= (BOOST_COPY_ASSIGN_REF(attribute_value) that) BOOST_NOEXCEPT
    {
        m_pImpl = that.m_pImpl;
        return *this;
    }

    /*!
     * Move assignment
     */
    attribute_value& operator= (BOOST_RV_REF(attribute_value) that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
        return *this;
    }

    /*!
     * The operator checks if the attribute value is empty
     */
    BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()
    /*!
     * The operator checks if the attribute value is empty
     */
    bool operator! () const BOOST_NOEXCEPT { return !m_pImpl; }

    /*!
     * The method returns the type information of the stored value of the attribute.
     * The returned type info wrapper may be empty if the attribute value is empty or
     * the information cannot be provided. If the returned value is not empty, the type
     * can be used for value extraction.
     */
    typeindex::type_index get_type() const
    {
        if (m_pImpl.get())
            return m_pImpl->get_type();
        else
            return typeindex::type_index();
    }

    /*!
     * The method is called when the attribute value is passed to another thread (e.g.
     * in case of asynchronous logging). The value should ensure it properly owns all thread-specific data.
     *
     * \post The attribute value no longer refers to any thread-specific resources.
     */
    void detach_from_thread()
    {
        if (m_pImpl.get())
            m_pImpl->detach_from_thread().swap(m_pImpl);
    }

    /*!
     * The method dispatches the value to the given object. This method is a low level interface for
     * attribute value visitation and extraction. For typical usage these interfaces may be more convenient.
     *
     * \param dispatcher The object that attempts to dispatch the stored value.
     * \return \c true if the value is not empty and the \a dispatcher was capable to consume
     *         the real attribute value type and \c false otherwise.
     */
    bool dispatch(type_dispatcher& dispatcher) const
    {
        if (m_pImpl.get())
            return m_pImpl->dispatch(dispatcher);
        else
            return false;
    }

#if !defined(BOOST_LOG_DOXYGEN_PASS)
#if !defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
#define BOOST_LOG_AUX_VOID_DEFAULT = void
#else
#define BOOST_LOG_AUX_VOID_DEFAULT
#endif
#endif // !defined(BOOST_LOG_DOXYGEN_PASS)

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns an empty value. See description of the \c result_of::extract
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract< T, TagT >::type extract() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise an exception is thrown. See description of the \c result_of::extract_or_throw
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract_or_throw< T, TagT >::type extract_or_throw() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT >
    typename result_of::extract_or_default< T, T, TagT >::type extract_or_default(T const& def_value) const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename TagT BOOST_LOG_AUX_VOID_DEFAULT, typename DefaultT >
    typename result_of::extract_or_default< T, DefaultT, TagT >::type extract_or_default(DefaultT const& def_value) const;

#if defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)
    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns an empty value. See description of the \c result_of::extract
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract< T >::type extract() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise an exception is thrown. See description of the \c result_of::extract_or_throw
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract_or_throw< T >::type extract_or_throw() const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T >
    typename result_of::extract_or_default< T, T >::type extract_or_default(T const& def_value) const;

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence. If extraction fails, the default value is returned.
     *
     * \note Include <tt>value_extraction.hpp</tt> prior to using this method.
     *
     * \param def_value Default value.
     *
     * \return The extracted value, if the attribute value is not empty and the value is the same
     *         as specified. Otherwise returns the default value. See description of the \c result_of::extract_or_default
     *         metafunction for information on the nature of the result value.
     */
    template< typename T, typename DefaultT >
    typename result_of::extract_or_default< T, DefaultT >::type extract_or_default(DefaultT const& def_value) const;
#endif // defined(BOOST_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS)

#undef BOOST_LOG_AUX_VOID_DEFAULT

    /*!
     * The method attempts to extract the stored value, assuming the value has the specified type,
     * and pass it to the \a visitor function object.
     * One can specify either a single type or an MPL type sequence, in which case the stored value
     * is checked against every type in the sequence.
     *
     * \note Include <tt>value_visitation.hpp</tt> prior to using this method.
     *
     * \param visitor A function object that will be invoked on the extracted attribute value.
     *                The visitor should be capable to be called with a single argument of
     *                any type of the specified types in \c T.
     *
     * \return The result of visitation.
     */
    template< typename T, typename VisitorT >
    visitation_result visit(VisitorT visitor) const;

    /*!
     * The method swaps two attribute values
     */
    void swap(attribute_value& that) BOOST_NOEXCEPT
    {
        m_pImpl.swap(that.m_pImpl);
    }
};

/*!
 * The function swaps two attribute values
 */
inline void swap(attribute_value& left, attribute_value& right) BOOST_NOEXCEPT
{
    left.swap(right);
}

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>
#if defined(BOOST_LOG_ATTRIBUTES_ATTRIBUTE_HPP_INCLUDED_)
#include <boost/log/detail/attribute_get_value_impl.hpp>
#endif

#endif // BOOST_LOG_ATTRIBUTE_VALUE_HPP_INCLUDED_

/* attribute_value.hpp
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
*/