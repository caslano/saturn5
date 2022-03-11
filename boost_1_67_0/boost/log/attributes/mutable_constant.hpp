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