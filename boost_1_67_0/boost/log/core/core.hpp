/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   core/core.hpp
 * \author Andrey Semashev
 * \date   19.04.2007
 *
 * This header contains logging core class definition.
 */

#ifndef BOOST_LOG_CORE_CORE_HPP_INCLUDED_
#define BOOST_LOG_CORE_CORE_HPP_INCLUDED_

#include <utility>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/light_function.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_value_set.hpp>
#include <boost/log/expressions/filter.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

#ifndef BOOST_LOG_DOXYGEN_PASS

namespace sinks {

class sink;

} // namespace sinks

#endif // BOOST_LOG_DOXYGEN_PASS

class core;

typedef shared_ptr< core > core_ptr;

/*!
 * \brief Logging library core class
 *
 * The logging core is used to interconnect log sources and sinks. It also provides
 * a number of basic features, like global filtering and global and thread-specific attribute storage.
 *
 * The logging core is a singleton. Users can acquire the core instance by calling the static method <tt>get</tt>.
 */
class core
{
public:
    //! Exception handler function type
    typedef boost::log::aux::light_function< void () > exception_handler_type;

private:
    //! Implementation type
    struct implementation;
    friend struct implementation;

private:
    //! A pointer to the implementation
    implementation* m_impl;

private:
    //! \cond
    core();
    //! \endcond

public:
    /*!
     * Destructor. Destroys the core, releases any sinks and attributes that were registered.
     */
    ~core();

    /*!
     * \return The method returns a pointer to the logging core singleton instance.
     */
    BOOST_LOG_API static core_ptr get();

    /*!
     * The method enables or disables logging.
     *
     * Setting this status to \c false allows you to completely wipe out any logging activity, including
     * filtering and generation of attribute values. It is useful if you want to completely disable logging
     * in a running application. The state of logging does not alter any other properties of the logging
     * library, such as filters or sinks, so you can enable logging with the very same settings that you had
     * when the logging was disabled.
     * This feature may also be useful if you want to perform major changes to logging configuration and
     * don't want your application to block on opening or pushing a log record.
     *
     * By default logging is enabled.
     *
     * \param enabled The actual flag of logging activity.
     * \return The previous value of enabled/disabled logging flag
     */
    BOOST_LOG_API bool set_logging_enabled(bool enabled = true);
    /*!
     * The method allows to detect if logging is enabled. See the comment for \c set_logging_enabled.
     */
    BOOST_LOG_API bool get_logging_enabled() const;

    /*!
     * The method sets the global logging filter. The filter is applied to every log record that is processed.
     *
     * \param filter The filter function object to be installed.
     */
    BOOST_LOG_API void set_filter(filter const& filter);
    /*!
     * The method removes the global logging filter. All log records are passed to sinks without global filtering applied.
     */
    BOOST_LOG_API void reset_filter();

    /*!
     * The method adds a new sink. The sink is included into logging process immediately after being added and until being removed.
     * No sink can be added more than once at the same time. If the sink is already registered, the call is ignored.
     *
     * \param s The sink to be registered.
     */
    BOOST_LOG_API void add_sink(shared_ptr< sinks::sink > const& s);
    /*!
     * The method removes the sink from the output. The sink will not receive any log records after removal.
     * The call has no effect if the sink is not registered.
     *
     * \param s The sink to be unregistered.
     */
    BOOST_LOG_API void remove_sink(shared_ptr< sinks::sink > const& s);
    /*!
     * The method removes all registered sinks from the output. The sinks will not receive any log records after removal.
     */
    BOOST_LOG_API void remove_all_sinks();

    /*!
     * The method performs flush on all registered sinks.
     *
     * \note This method may take long time to complete as it may block until all sinks manage to process all buffered log records.
     *       The call will also block all logging attempts until the operation completes.
     */
    BOOST_LOG_API void flush();

    /*!
     * The method adds an attribute to the global attribute set. The attribute will be implicitly added to every log record.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    BOOST_LOG_API std::pair< attribute_set::iterator, bool > add_global_attribute(attribute_name const& name, attribute const& attr);
    /*!
     * The method removes an attribute from the global attribute set.
     *
     * \pre The attribute was added with the \c add_global_attribute call.
     * \post The attribute is no longer registered as a global attribute. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    BOOST_LOG_API void remove_global_attribute(attribute_set::iterator it);

    /*!
     * The method returns a copy of the complete set of currently registered global attributes.
     */
    BOOST_LOG_API attribute_set get_global_attributes() const;
    /*!
     * The method replaces the complete set of currently registered global attributes with the provided set.
     *
     * \note The method invalidates all iterators and references that may have been returned
     *       from the \c add_global_attribute method.
     *
     * \param attrs The set of attributes to be installed.
     */
    BOOST_LOG_API void set_global_attributes(attribute_set const& attrs);

    /*!
     * The method adds an attribute to the thread-specific attribute set. The attribute will be implicitly added to
     * every log record made in the current thread.
     *
     * \note In single-threaded build the effect is the same as adding the attribute globally. This, however, does
     *       not imply that iterators to thread-specific and global attributes are interchangeable.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    BOOST_LOG_API std::pair< attribute_set::iterator, bool > add_thread_attribute(attribute_name const& name, attribute const& attr);
    /*!
     * The method removes an attribute from the thread-specific attribute set.
     *
     * \pre The attribute was added with the \c add_thread_attribute call.
     * \post The attribute is no longer registered as a thread-specific attribute. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    BOOST_LOG_API void remove_thread_attribute(attribute_set::iterator it);

    /*!
     * The method returns a copy of the complete set of currently registered thread-specific attributes.
     */
    BOOST_LOG_API attribute_set get_thread_attributes() const;
    /*!
     * The method replaces the complete set of currently registered thread-specific attributes with the provided set.
     *
     * \note The method invalidates all iterators and references that may have been returned
     *       from the \c add_thread_attribute method.
     *
     * \param attrs The set of attributes to be installed.
     */
    BOOST_LOG_API void set_thread_attributes(attribute_set const& attrs);

    /*!
     * The method sets exception handler function. The function will be called with no arguments
     * in case if an exception occurs during either \c open_record or \c push_record method
     * execution. Since exception handler is called from a \c catch statement, the exception
     * can be rethrown in order to determine its type.
     *
     * By default no handler is installed, thus any exception is propagated as usual.
     *
     * \sa See also: <tt>utility/exception_handler.hpp</tt>
     * \param handler Exception handling function
     *
     * \note The exception handler can be invoked in several threads concurrently.
     *       Thread interruptions are not affected by exception handlers.
     */
    BOOST_LOG_API void set_exception_handler(exception_handler_type const& handler);

    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attributes to be attached to the record to be opened.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_LOG_API record open_record(attribute_set const& source_attributes);
    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attribute values to be attached to the record to be opened.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_LOG_API record open_record(attribute_value_set const& source_attributes);
    /*!
     * The method attempts to open a new record to be written. While attempting to open a log record all filtering is applied.
     * A successfully opened record can be pushed further to sinks by calling the \c push_record method or simply destroyed by
     * destroying the returned object.
     *
     * More than one open records are allowed, such records exist independently. All attribute values are acquired during opening
     * the record and do not interact between records.
     *
     * The returned records can be copied, however, they must not be passed between different threads.
     *
     * \param source_attributes The set of source-specific attribute values to be attached to the record to be opened. The contents
     *                          of this container are unspecified after this call.
     * \return A valid log record if the record is opened, an invalid record object if not (e.g. because it didn't pass filtering).
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws, or some system resource limitation is reached.
     */
    BOOST_FORCEINLINE record open_record(BOOST_RV_REF(attribute_value_set) source_attributes)
    {
        return open_record_move(static_cast< attribute_value_set& >(source_attributes));
    }

    /*!
     * The method pushes the record to sinks. The record is moved from in the process.
     *
     * \pre <tt>!!rec == true</tt>
     * \post <tt>!rec == true</tt>
     * \param rec A previously successfully opened log record.
     *
     * \b Throws: If an exception handler is installed, only throws if the handler throws. Otherwise may
     *            throw if one of the sinks throws.
     */
    BOOST_FORCEINLINE void push_record(BOOST_RV_REF(record) rec)
    {
        push_record_move(static_cast< record& >(rec));
    }

    BOOST_DELETED_FUNCTION(core(core const&))
    BOOST_DELETED_FUNCTION(core& operator= (core const&))

#ifndef BOOST_LOG_DOXYGEN_PASS
private:
    //! Opens log record. This function is mostly needed to maintain ABI stable between C++03 and C++11.
    BOOST_LOG_API record open_record_move(attribute_value_set& source_attributes);
    //! The method pushes the record to sinks.
    BOOST_LOG_API void push_record_move(record& rec);
#endif // BOOST_LOG_DOXYGEN_PASS
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_CORE_CORE_HPP_INCLUDED_

/* core.hpp
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
*/