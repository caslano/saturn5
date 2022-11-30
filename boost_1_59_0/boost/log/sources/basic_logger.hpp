/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   basic_logger.hpp
 * \author Andrey Semashev
 * \date   08.03.2007
 *
 * The header contains implementation of a base class for loggers. Convenience macros
 * for defining custom loggers are also provided.
 */

#ifndef BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_
#define BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_

#include <exception>
#include <utility>
#include <ostream>
#include <boost/assert.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/core/addressof.hpp>
#include <boost/type_traits/is_nothrow_swappable.hpp>
#include <boost/type_traits/is_nothrow_move_constructible.hpp>
#include <boost/preprocessor/facilities/empty.hpp>
#include <boost/preprocessor/facilities/identity.hpp>
#include <boost/preprocessor/seq/enum.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/parameter_tools.hpp>
#include <boost/log/attributes/attribute_set.hpp>
#include <boost/log/attributes/attribute_name.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/core/core.hpp>
#include <boost/log/core/record.hpp>
#include <boost/log/sources/features.hpp>
#include <boost/log/sources/threading_models.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace sources {

/*!
 * \brief Basic logger class
 *
 * The \c basic_logger class template serves as a base class for all loggers
 * provided by the library. It can also be used as a base for user-defined
 * loggers. The template parameters are:
 *
 * \li \c CharT - logging character type
 * \li \c FinalT - final type of the logger that eventually derives from
 *     the \c basic_logger. There may be other classes in the hierarchy
 *     between the final class and \c basic_logger.
 * \li \c ThreadingModelT - threading model policy. Must provide methods
 *     of the Boost.Thread locking concept used in \c basic_logger class
 *     and all its derivatives in the hierarchy up to the \c FinalT class.
 *     The \c basic_logger class itself requires methods of the
 *     SharedLockable concept. The threading model policy must also be
 *     default and copy-constructible and support member function \c swap.
 *     There are currently two policies provided: \c single_thread_model
 *     and \c multi_thread_model.
 *
 * The logger implements fundamental facilities of loggers, such as storing
 * source-specific attribute set and formatting log record messages. The basic
 * logger interacts with the logging core in order to apply filtering and
 * pass records to sinks.
 */
template< typename CharT, typename FinalT, typename ThreadingModelT >
class basic_logger :
    public ThreadingModelT
{
    typedef basic_logger this_type;
    BOOST_COPYABLE_AND_MOVABLE_ALT(this_type)

public:
    //! Character type
    typedef CharT char_type;
    //! Final logger type
    typedef FinalT final_type;
    //! Threading model type
    typedef ThreadingModelT threading_model;

#if !defined(BOOST_LOG_NO_THREADS)
    //! Lock requirement for the swap_unlocked method
    typedef boost::log::aux::multiple_unique_lock2< threading_model, threading_model > swap_lock;
    //! Lock requirement for the add_attribute_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > add_attribute_lock;
    //! Lock requirement for the remove_attribute_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > remove_attribute_lock;
    //! Lock requirement for the remove_all_attributes_unlocked method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > remove_all_attributes_lock;
    //! Lock requirement for the get_attributes method
    typedef boost::log::aux::shared_lock_guard< const threading_model > get_attributes_lock;
    //! Lock requirement for the open_record_unlocked method
    typedef boost::log::aux::shared_lock_guard< threading_model > open_record_lock;
    //! Lock requirement for the set_attributes method
    typedef boost::log::aux::exclusive_lock_guard< threading_model > set_attributes_lock;
#else
    typedef no_lock< threading_model > swap_lock;
    typedef no_lock< threading_model > add_attribute_lock;
    typedef no_lock< threading_model > remove_attribute_lock;
    typedef no_lock< threading_model > remove_all_attributes_lock;
    typedef no_lock< const threading_model > get_attributes_lock;
    typedef no_lock< threading_model > open_record_lock;
    typedef no_lock< threading_model > set_attributes_lock;
#endif

    //! Lock requirement for the push_record_unlocked method
    typedef no_lock< threading_model > push_record_lock;

private:
    //! A pointer to the logging system
    core_ptr m_pCore;

    //! Logger-specific attribute set
    attribute_set m_Attributes;

public:
    /*!
     * Constructor. Initializes internal data structures of the basic logger class,
     * acquires reference to the logging core.
     */
    basic_logger() :
        threading_model(),
        m_pCore(core::get())
    {
    }
    /*!
     * Copy constructor. Copies all attributes from the source logger.
     *
     * \note Not thread-safe. The source logger must be locked in the final class before copying.
     *
     * \param that Source logger
     */
    basic_logger(basic_logger const& that) :
        threading_model(static_cast< threading_model const& >(that)),
        m_pCore(that.m_pCore),
        m_Attributes(that.m_Attributes)
    {
    }
    /*!
     * Move constructor. Moves all attributes from the source logger.
     *
     * \note Not thread-safe. The source logger must be locked in the final class before copying.
     *
     * \param that Source logger
     */
    basic_logger(BOOST_RV_REF(basic_logger) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< threading_model >::value &&
                                                                    boost::is_nothrow_move_constructible< core_ptr >::value &&
                                                                    boost::is_nothrow_move_constructible< attribute_set >::value) :
        threading_model(boost::move(static_cast< threading_model& >(that))),
        m_pCore(boost::move(that.m_pCore)),
        m_Attributes(boost::move(that.m_Attributes))
    {
    }
    /*!
     * Constructor with named arguments. The constructor ignores all arguments. The result of
     * construction is equivalent to default construction.
     */
    template< typename ArgsT >
    explicit basic_logger(ArgsT const&) :
        threading_model(),
        m_pCore(core::get())
    {
    }

protected:
    /*!
     * An accessor to the logging system pointer
     */
    core_ptr const& core() const { return m_pCore; }
    /*!
     * An accessor to the logger attributes
     */
    attribute_set& attributes() { return m_Attributes; }
    /*!
     * An accessor to the logger attributes
     */
    attribute_set const& attributes() const { return m_Attributes; }
    /*!
     * An accessor to the threading model base
     */
    threading_model& get_threading_model() BOOST_NOEXCEPT { return *this; }
    /*!
     * An accessor to the threading model base
     */
    threading_model const& get_threading_model() const BOOST_NOEXCEPT { return *this; }
    /*!
     * An accessor to the final logger
     */
    final_type* final_this() BOOST_NOEXCEPT
    {
        BOOST_LOG_ASSUME(this != NULL);
        return static_cast< final_type* >(this);
    }
    /*!
     * An accessor to the final logger
     */
    final_type const* final_this() const BOOST_NOEXCEPT
    {
        BOOST_LOG_ASSUME(this != NULL);
        return static_cast< final_type const* >(this);
    }

    /*!
     * Unlocked \c swap
     */
    void swap_unlocked(basic_logger& that)
    {
        get_threading_model().swap(that.get_threading_model());
        m_Attributes.swap(that.m_Attributes);
    }

    /*!
     * Unlocked \c add_attribute
     */
    std::pair< attribute_set::iterator, bool > add_attribute_unlocked(attribute_name const& name, attribute const& attr)
    {
        return m_Attributes.insert(name, attr);
    }

    /*!
     * Unlocked \c remove_attribute
     */
    void remove_attribute_unlocked(attribute_set::iterator it)
    {
        m_Attributes.erase(it);
    }

    /*!
     * Unlocked \c remove_all_attributes
     */
    void remove_all_attributes_unlocked()
    {
        m_Attributes.clear();
    }

    /*!
     * Unlocked \c open_record
     */
    record open_record_unlocked()
    {
        return m_pCore->open_record(m_Attributes);
    }
    /*!
     * Unlocked \c open_record
     */
    template< typename ArgsT >
    record open_record_unlocked(ArgsT const&)
    {
        return m_pCore->open_record(m_Attributes);
    }

    /*!
     * Unlocked \c push_record
     */
    void push_record_unlocked(BOOST_RV_REF(record) rec)
    {
        m_pCore->push_record(boost::move(rec));
    }

    /*!
     * Unlocked \c get_attributes
     */
    attribute_set get_attributes_unlocked() const
    {
        return m_Attributes;
    }

    /*!
     * Unlocked \c set_attributes
     */
    void set_attributes_unlocked(attribute_set const& attrs)
    {
        m_Attributes = attrs;
    }

    //! Assignment is closed (should be implemented through copy and swap in the final class)
    BOOST_DELETED_FUNCTION(basic_logger& operator= (basic_logger const&))
};

/*!
 * Free-standing swap for all loggers
 */
template< typename CharT, typename FinalT, typename ThreadingModelT >
inline void swap(
    basic_logger< CharT, FinalT, ThreadingModelT >& left,
    basic_logger< CharT, FinalT, ThreadingModelT >& right) BOOST_NOEXCEPT_IF(boost::is_nothrow_swappable< FinalT >::value)
{
    static_cast< FinalT& >(left).swap(static_cast< FinalT& >(right));
}

/*!
 * \brief A composite logger that inherits a number of features
 *
 * The composite logger is a helper class that simplifies feature composition into the final logger.
 * The user's logger class is expected to derive from the composite logger class, instantiated with
 * the character type, the user's logger class, the threading model and the list of the required features.
 * The former three parameters are passed to the \c basic_logger class template. The feature list
 * must be an MPL type sequence, where each element is a unary MPL metafunction class, that upon
 * applying on its argument results in a logging feature class that derives from the argument.
 * Every logger feature provided by the library can participate in the feature list.
 */
template< typename CharT, typename FinalT, typename ThreadingModelT, typename FeaturesT >
class basic_composite_logger :
    public boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, ThreadingModelT >,
        FeaturesT
    >::type
{
private:
    //! Base type (the hierarchy of features)
    typedef typename boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, ThreadingModelT >,
        FeaturesT
    >::type base_type;

protected:
    //! The composite logger type (for use in the user's logger class)
    typedef basic_composite_logger logger_base;
    BOOST_COPYABLE_AND_MOVABLE_ALT(logger_base)

public:
    //! Threading model being used
    typedef typename base_type::threading_model threading_model;

    //! Lock requirement for the swap_unlocked method
    typedef typename base_type::swap_lock swap_lock;

#if !defined(BOOST_LOG_NO_THREADS)

public:
    /*!
     * Default constructor (default-constructs all features)
     */
    basic_composite_logger() {}
    /*!
     * Copy constructor
     */
    basic_composite_logger(basic_composite_logger const& that) :
        base_type
        ((
            boost::log::aux::shared_lock_guard< const threading_model >(that.get_threading_model()),
            static_cast< base_type const& >(that)
        ))
    {
    }
    /*!
     * Move constructor
     */
    basic_composite_logger(BOOST_RV_REF(logger_base) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< base_type >::value) :
        base_type(boost::move(static_cast< base_type& >(that)))
    {
    }
    /*!
     * Constructor with named parameters
     */
    template< typename ArgsT >
    explicit basic_composite_logger(ArgsT const& args) : base_type(args)
    {
    }

    /*!
     * The method adds an attribute to the source-specific attribute set. The attribute will be implicitly added to
     * every log record made with the current logger.
     *
     * \param name The attribute name.
     * \param attr The attribute factory.
     * \return A pair of values. If the second member is \c true, then the attribute is added and the first member points to the
     *         attribute. Otherwise the attribute was not added and the first member points to the attribute that prevents
     *         addition.
     */
    std::pair< attribute_set::iterator, bool > add_attribute(attribute_name const& name, attribute const& attr)
    {
        typename base_type::add_attribute_lock lock(base_type::get_threading_model());
        return base_type::add_attribute_unlocked(name, attr);
    }
    /*!
     * The method removes an attribute from the source-specific attribute set.
     *
     * \pre The attribute was added with the add_attribute call for this instance of the logger.
     * \post The attribute is no longer registered as a source-specific attribute for this logger. The iterator is invalidated after removal.
     *
     * \param it Iterator to the previously added attribute.
     */
    void remove_attribute(attribute_set::iterator it)
    {
        typename base_type::remove_attribute_lock lock(base_type::get_threading_model());
        base_type::remove_attribute_unlocked(it);
    }

    /*!
     * The method removes all attributes from the logger. All iterators and references to the removed attributes are invalidated.
     */
    void remove_all_attributes()
    {
        typename base_type::remove_all_attributes_lock lock(base_type::get_threading_model());
        base_type::remove_all_attributes_unlocked();
    }

    /*!
     * The method retrieves a copy of a set with all attributes from the logger.
     *
     * \return The copy of the attribute set. Attributes are shallow-copied.
     */
    attribute_set get_attributes() const
    {
        typename base_type::get_attributes_lock lock(base_type::get_threading_model());
        return base_type::get_attributes_unlocked();
    }

    /*!
     * The method installs the whole attribute set into the logger. All iterators and references to elements of
     * the previous set are invalidated. Iterators to the \a attrs set are not valid to be used with the logger (that is,
     * the logger owns a copy of \a attrs after completion).
     *
     * \param attrs The set of attributes to install into the logger. Attributes are shallow-copied.
     */
    void set_attributes(attribute_set const& attrs)
    {
        typename base_type::set_attributes_lock lock(base_type::get_threading_model());
        base_type::set_attributes_unlocked(attrs);
    }

    /*!
     * The method opens a new log record in the logging core.
     *
     * \return A valid record handle if the logging record is opened successfully, an invalid handle otherwise.
     */
    record open_record()
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
        {
            typename base_type::open_record_lock lock(base_type::get_threading_model());
            return base_type::open_record_unlocked(boost::log::aux::empty_arg_list());
        }
        else
            return record();
    }
    /*!
     * The method opens a new log record in the logging core.
     *
     * \param args A set of additional named arguments. The parameter is ignored.
     * \return A valid record handle if the logging record is opened successfully, an invalid handle otherwise.
     */
    template< typename ArgsT >
    record open_record(ArgsT const& args)
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
        {
            typename base_type::open_record_lock lock(base_type::get_threading_model());
            return base_type::open_record_unlocked(args);
        }
        else
            return record();
    }
    /*!
     * The method pushes the constructed message to the logging core
     *
     * \param rec The log record with the formatted message
     */
    void push_record(BOOST_RV_REF(record) rec)
    {
        typename base_type::push_record_lock lock(base_type::get_threading_model());
        base_type::push_record_unlocked(boost::move(rec));
    }
    /*!
     * Thread-safe implementation of swap
     */
    void swap(basic_composite_logger& that)
    {
        swap_lock lock(base_type::get_threading_model(), that.get_threading_model());
        base_type::swap_unlocked(static_cast< base_type& >(that));
    }

protected:
    /*!
     * Assignment for the final class. Threadsafe, provides strong exception guarantee.
     */
    FinalT& assign(FinalT const& that)
    {
        BOOST_LOG_ASSUME(this != NULL);
        if (static_cast< FinalT* >(this) != boost::addressof(that))
        {
            // We'll have to explicitly create the copy in order to make sure it's unlocked when we attempt to lock *this
            FinalT tmp(that);
            boost::log::aux::exclusive_lock_guard< threading_model > lock(base_type::get_threading_model());
            base_type::swap_unlocked(tmp);
        }
        return static_cast< FinalT& >(*this);
    }
};

//! An optimized composite logger version with no multithreading support
template< typename CharT, typename FinalT, typename FeaturesT >
class basic_composite_logger< CharT, FinalT, single_thread_model, FeaturesT > :
    public boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, single_thread_model >,
        FeaturesT
    >::type
{
private:
    typedef typename boost::log::sources::aux::inherit_features<
        basic_logger< CharT, FinalT, single_thread_model >,
        FeaturesT
    >::type base_type;

protected:
    typedef basic_composite_logger logger_base;
    BOOST_COPYABLE_AND_MOVABLE_ALT(logger_base)

public:
    typedef typename base_type::threading_model threading_model;

#endif // !defined(BOOST_LOG_NO_THREADS)

public:
    basic_composite_logger() {}
    basic_composite_logger(basic_composite_logger const& that) :
        base_type(static_cast< base_type const& >(that))
    {
    }
    basic_composite_logger(BOOST_RV_REF(logger_base) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< base_type >::value) :
        base_type(boost::move(static_cast< base_type& >(that)))
    {
    }
    template< typename ArgsT >
    explicit basic_composite_logger(ArgsT const& args) : base_type(args)
    {
    }

    std::pair< attribute_set::iterator, bool > add_attribute(attribute_name const& name, attribute const& attr)
    {
        return base_type::add_attribute_unlocked(name, attr);
    }
    void remove_attribute(attribute_set::iterator it)
    {
        base_type::remove_attribute_unlocked(it);
    }
    void remove_all_attributes()
    {
        base_type::remove_all_attributes_unlocked();
    }
    attribute_set get_attributes() const
    {
        return base_type::get_attributes_unlocked();
    }
    void set_attributes(attribute_set const& attrs)
    {
        base_type::set_attributes_unlocked(attrs);
    }
    record open_record()
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
            return base_type::open_record_unlocked(boost::log::aux::empty_arg_list());
        else
            return record();
    }
    template< typename ArgsT >
    record open_record(ArgsT const& args)
    {
        // Perform a quick check first
        if (this->core()->get_logging_enabled())
            return base_type::open_record_unlocked(args);
        else
            return record();
    }
    void push_record(BOOST_RV_REF(record) rec)
    {
        base_type::push_record_unlocked(boost::move(rec));
    }
    void swap(basic_composite_logger& that)
    {
        base_type::swap_unlocked(static_cast< base_type& >(that));
    }

protected:
    FinalT& assign(FinalT that)
    {
        base_type::swap_unlocked(that);
        return static_cast< FinalT& >(*this);
    }
};


#ifndef BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, typename_keyword)\
    public:\
        BOOST_DEFAULTED_FUNCTION(class_type(), {})\
        class_type(class_type const& that) : class_type::logger_base(\
            static_cast< typename_keyword() class_type::logger_base const& >(that)) {}\
        class_type(BOOST_RV_REF(class_type) that) BOOST_NOEXCEPT_IF(boost::is_nothrow_move_constructible< typename_keyword() class_type::logger_base >::value) : class_type::logger_base(\
            ::boost::move(static_cast< typename_keyword() class_type::logger_base& >(that))) {}\
        BOOST_LOG_PARAMETRIZED_CONSTRUCTORS_FORWARD(class_type, class_type::logger_base)\

#endif // BOOST_LOG_DOXYGEN_PASS

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, BOOST_PP_EMPTY)

#define BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_TEMPLATE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_IMPL(class_type, BOOST_PP_IDENTITY(typename))

#define BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT(class_type)\
    public:\
        class_type& operator= (BOOST_COPY_ASSIGN_REF(class_type) that)\
        {\
            return class_type::logger_base::assign(static_cast< class_type const& >(that));\
        }\
        class_type& operator= (BOOST_RV_REF(class_type) that)\
        {\
            BOOST_LOG_EXPR_IF_MT(::boost::log::aux::exclusive_lock_guard< class_type::threading_model > lock(this->get_threading_model());)\
            this->swap_unlocked(that);\
            return *this;\
        }

#define BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT_TEMPLATE(class_type)\
    public:\
        class_type& operator= (BOOST_COPY_ASSIGN_REF(class_type) that)\
        {\
            return class_type::logger_base::assign(static_cast< class_type const& >(that));\
        }\
        class_type& operator= (BOOST_RV_REF(class_type) that)\
        {\
            BOOST_LOG_EXPR_IF_MT(::boost::log::aux::exclusive_lock_guard< typename class_type::threading_model > lock(this->get_threading_model());)\
            this->swap_unlocked(that);\
            return *this;\
        }

#define BOOST_LOG_FORWARD_LOGGER_MEMBERS(class_type)\
    BOOST_COPYABLE_AND_MOVABLE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS(class_type)\
    BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT(class_type)

#define BOOST_LOG_FORWARD_LOGGER_MEMBERS_TEMPLATE(class_type)\
    BOOST_COPYABLE_AND_MOVABLE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_CONSTRUCTORS_TEMPLATE(class_type)\
    BOOST_LOG_FORWARD_LOGGER_ASSIGNMENT_TEMPLATE(class_type)

} // namespace sources

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

/*!
 *  \brief The macro declares a logger class that inherits a number of base classes
 *
 *  \param type_name The name of the logger class to declare
 *  \param char_type The character type of the logger. Either char or wchar_t expected.
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 *  \param threading A threading model class
 */
#define BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char_type, base_seq, threading)\
    class type_name :\
        public ::boost::log::sources::basic_composite_logger<\
            char_type,\
            type_name,\
            threading,\
            ::boost::log::sources::features< BOOST_PP_SEQ_ENUM(base_seq) >\
        >\
    {\
        BOOST_LOG_FORWARD_LOGGER_MEMBERS(type_name)\
    }



#ifdef BOOST_LOG_USE_CHAR

/*!
 *  \brief The macro declares a narrow-char logger class that inherits a number of base classes
 *
 *  Equivalent to BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, single_thread_model)
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_LOGGER(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, ::boost::log::sources::single_thread_model)

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 *  \brief The macro declares a narrow-char thread-safe logger class that inherits a number of base classes
 *
 *  Equivalent to <tt>BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq, multi_thread_model< shared_mutex >)</tt>
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_LOGGER_MT(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, char, base_seq,\
        ::boost::log::sources::multi_thread_model< ::boost::shared_mutex >)

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_CHAR

#ifdef BOOST_LOG_USE_WCHAR_T

/*!
 *  \brief The macro declares a wide-char logger class that inherits a number of base classes
 *
 *  Equivalent to BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, single_thread_model)
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_WLOGGER(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, ::boost::log::sources::single_thread_model)

#if !defined(BOOST_LOG_NO_THREADS)

/*!
 *  \brief The macro declares a wide-char thread-safe logger class that inherits a number of base classes
 *
 *  Equivalent to <tt>BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq, multi_thread_model< shared_mutex >)</tt>
 *
 *  \param type_name The name of the logger class to declare
 *  \param base_seq A Boost.Preprocessor sequence of type identifiers of the base classes templates
 */
#define BOOST_LOG_DECLARE_WLOGGER_MT(type_name, base_seq)\
    BOOST_LOG_DECLARE_LOGGER_TYPE(type_name, wchar_t, base_seq,\
        ::boost::log::sources::multi_thread_model< ::boost::shared_mutex >)

#endif // !defined(BOOST_LOG_NO_THREADS)
#endif // BOOST_LOG_USE_WCHAR_T

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_SOURCES_BASIC_LOGGER_HPP_INCLUDED_

/* basic_logger.hpp
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
*/