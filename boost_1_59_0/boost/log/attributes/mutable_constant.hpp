/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   mutable_constant.hpp
 * \author Andrey Semashev
 * \date   06.11.2007
 *
 * The header contains implementation of a mutable constant attribute.
 */

#ifndef BOOST_LOG_ATTRIBUTES_MUTABLE_CONSTANT_HPP_INCLUDED_
#define BOOST_LOG_ATTRIBUTES_MUTABLE_CONSTANT_HPP_INCLUDED_

#include <boost/static_assert.hpp>
#include <boost/smart_ptr/intrusive_ptr.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/is_void.hpp>
#include <boost/type_traits/conditional.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/locks.hpp>
#include <boost/log/attributes/attribute.hpp>
#include <boost/log/attributes/attribute_cast.hpp>
#include <boost/log/attributes/attribute_value_impl.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace attributes {

/*!
 * \brief A class of an attribute that holds a single constant value with ability to change it
 *
 * The mutable_constant attribute stores a single value of type, specified as the first template argument.
 * This value is returned on each attribute value acquisition.
 *
 * The attribute also allows to modify the stored value, even if the attribute is registered in an attribute set.
 * In order to ensure thread safety of such modifications the \c mutable_constant class is also parametrized
 * with three additional template arguments: mutex type, scoped write and scoped read lock types. If not specified,
 * the lock types are automatically deduced based on the mutex type.
 *
 * The implementation may avoid using these types to actually create and use the mutex, if a more efficient synchronization method is
 * available (such as atomic operations on the value type). By default no synchronization is done.
 */
#ifdef BOOST_LOG_DOXYGEN_PASS
template< typename T, typename MutexT = void, typename ScopedWriteLockT = auto, typename ScopedReadLockT = auto >
#else // BOOST_LOG_DOXYGEN_PASS
template<
    typename T,
    typename MutexT = void,
    typename ScopedWriteLockT =
#ifndef BOOST_LOG_NO_THREADS
        typename boost::conditional<
            boost::log::aux::is_exclusively_lockable< MutexT >::value,
            boost::log::aux::exclusive_lock_guard< MutexT >,
            void
        >::type,
#else
        void,
#endif // BOOST_LOG_NO_THREADS
    typename ScopedReadLockT =
#ifndef BOOST_LOG_NO_THREADS
        typename boost::conditional<
            boost::log::aux::is_shared_lockable< MutexT >::value,
            boost::log::aux::shared_lock_guard< MutexT >,
            ScopedWriteLockT
        >::type
#else
        ScopedWriteLockT
#endif // BOOST_LOG_NO_THREADS
#endif // BOOST_LOG_DOXYGEN_PASS
>
class mutable_constant :
    public attribute
{
public:
    //! The attribute value type
    typedef T value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute::impl
    {
    private:
        //! Mutex type
        typedef MutexT mutex_type;
        //! Shared lock type
        typedef ScopedReadLockT scoped_read_lock;
        //! Exclusive lock type
        typedef ScopedWriteLockT scoped_write_lock;
        BOOST_STATIC_ASSERT_MSG(!(is_void< mutex_type >::value || is_void< scoped_read_lock >::value || is_void< scoped_write_lock >::value), "Boost.Log: Mutex and both lock types either must not be void or must all be void");
        //! Attribute value wrapper
        typedef attribute_value_impl< value_type > attr_value;

    private:
        //! Thread protection mutex
        mutable mutex_type m_Mutex;
        //! Pointer to the actual attribute value
        intrusive_ptr< attr_value > m_Value;

    public:
        /*!
         * Initializing constructor
         */
        explicit impl(value_type const& value) : m_Value(new attr_value(value))
        {
        }
        /*!
         * Initializing constructor
         */
        explicit impl(BOOST_RV_REF(value_type) value) : m_Value(new attr_value(boost::move(value)))
        {
        }

        attribute_value get_value()
        {
            scoped_read_lock lock(m_Mutex);
            return attribute_value(m_Value);
        }

        void set(value_type const& value)
        {
            intrusive_ptr< attr_value > p = new attr_value(value);
            scoped_write_lock lock(m_Mutex);
            m_Value.swap(p);
        }

        void set(BOOST_RV_REF(value_type) value)
        {
            intrusive_ptr< attr_value > p = new attr_value(boost::move(value));
            scoped_write_lock lock(m_Mutex);
            m_Value.swap(p);
        }

        value_type get() const
        {
            scoped_read_lock lock(m_Mutex);
            return m_Value->get();
        }
    };

public:
    /*!
     * Constructor with the stored value initialization
     */
    explicit mutable_constant(value_type const& value) : attribute(new impl(value))
    {
    }
    /*!
     * Constructor with the stored value initialization
     */
    explicit mutable_constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value)))
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit mutable_constant(cast_source const& source) : attribute(source.as< impl >())
    {
    }

    /*!
     * The method sets a new attribute value. The implementation exclusively locks the mutex in order
     * to protect the value assignment.
     */
    void set(value_type const& value)
    {
        get_impl()->set(value);
    }

    /*!
     * The method sets a new attribute value.
     */
    void set(BOOST_RV_REF(value_type) value)
    {
        get_impl()->set(boost::move(value));
    }

    /*!
     * The method acquires the current attribute value. The implementation non-exclusively locks the mutex in order
     * to protect the value acquisition.
     */
    value_type get() const
    {
        return get_impl()->get();
    }

protected:
    /*!
     * \returns Pointer to the factory implementation
     */
    impl* get_impl() const
    {
        return static_cast< impl* >(attribute::get_impl());
    }
};


/*!
 * \brief Specialization for unlocked case
 *
 * This version of attribute does not perform thread synchronization to access the stored value.
 */
template< typename T >
class mutable_constant< T, void, void, void > :
    public attribute
{
public:
    //! The attribute value type
    typedef T value_type;

protected:
    //! Factory implementation
    class BOOST_SYMBOL_VISIBLE impl :
        public attribute::impl
    {
    private:
        //! Attribute value wrapper
        typedef attribute_value_impl< value_type > attr_value;

    private:
        //! The actual value
        intrusive_ptr< attr_value > m_Value;

    public:
        /*!
         * Initializing constructor
         */
        explicit impl(value_type const& value) : m_Value(new attr_value(value))
        {
        }
        /*!
         * Initializing constructor
         */
        explicit impl(BOOST_RV_REF(value_type) value) : m_Value(new attr_value(boost::move(value)))
        {
        }

        attribute_value get_value()
        {
            return attribute_value(m_Value);
        }

        void set(value_type const& value)
        {
            m_Value = new attr_value(value);
        }
        void set(BOOST_RV_REF(value_type) value)
        {
            m_Value = new attr_value(boost::move(value));
        }

        value_type get() const
        {
            return m_Value->get();
        }
    };

public:
    /*!
     * Constructor with the stored value initialization
     */
    explicit mutable_constant(value_type const& value) : attribute(new impl(value))
    {
    }
    /*!
     * Constructor with the stored value initialization
     */
    explicit mutable_constant(BOOST_RV_REF(value_type) value) : attribute(new impl(boost::move(value)))
    {
    }
    /*!
     * Constructor for casting support
     */
    explicit mutable_constant(cast_source const& source) : attribute(source.as< impl >())
    {
    }

    /*!
     * The method sets a new attribute value.
     */
    void set(value_type const& value)
    {
        get_impl()->set(value);
    }

    /*!
     * The method sets a new attribute value.
     */
    void set(BOOST_RV_REF(value_type) value)
    {
        get_impl()->set(boost::move(value));
    }

    /*!
     * The method acquires the current attribute value.
     */
    value_type get() const
    {
        return get_impl()->get();
    }

protected:
    /*!
     * \returns Pointer to the factory implementation
     */
    impl* get_impl() const
    {
        return static_cast< impl* >(attribute::get_impl());
    }
};

} // namespace attributes

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_ATTRIBUTES_MUTABLE_CONSTANT_HPP_INCLUDED_

/* mutable_constant.hpp
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
*/