/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains definition of generic type dispatcher interfaces.
 */

#ifndef BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

#include <boost/type_index.hpp>
#include <boost/static_assert.hpp>
#include <boost/core/explicit_operator_bool.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A type dispatcher interface
 *
 * All type dispatchers support this interface. It is used to acquire the
 * visitor interface for the requested type.
 */
class type_dispatcher
{
public:

#ifndef BOOST_LOG_DOXYGEN_PASS

    //! The base class for type dispatcher callbacks
    class callback_base
    {
    protected:
        void* m_pVisitor;
        void* m_pTrampoline;

    public:
        explicit callback_base(void* visitor = 0, void* tramp = 0) BOOST_NOEXCEPT :
            m_pVisitor(visitor),
            m_pTrampoline(tramp)
        {
        }
        template< typename ValueT >
        explicit callback_base(void* visitor, void (*tramp)(void*, ValueT const&)) BOOST_NOEXCEPT :
            m_pVisitor(visitor)
        {
            typedef void (*trampoline_t)(void*, ValueT const&);
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_trampoline = tramp;
            m_pTrampoline = caster.as_pvoid;
        }

        template< typename VisitorT, typename T >
        static void trampoline(void* visitor, T const& value)
        {
            (*static_cast< VisitorT* >(visitor))(value);
        }
    };

    //! An interface to the callback for the concrete type visitor
    template< typename T >
    class callback :
        private callback_base
    {
    private:
        //! Type of the trampoline method
        typedef void (*trampoline_t)(void*, T const&);

    public:
        //! The type, which the visitor is able to consume
        typedef T supported_type;

    public:
        callback() BOOST_NOEXCEPT : callback_base()
        {
        }
        explicit callback(callback_base const& base) BOOST_NOEXCEPT : callback_base(base)
        {
        }

        void operator() (T const& value) const
        {
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_pvoid = this->m_pTrampoline;
            (caster.as_trampoline)(this->m_pVisitor, value);
        }

        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        bool operator! () const BOOST_NOEXCEPT { return (this->m_pVisitor == 0); }
    };

#else // BOOST_LOG_DOXYGEN_PASS

    /*!
     * This interface is used by type dispatchers to consume the dispatched value.
     */
    template< typename T >
    class callback
    {
    public:
        /*!
         * The operator invokes the visitor-specific logic with the given value
         *
         * \param value The dispatched value
         */
        void operator() (T const& value) const;

        /*!
         * The operator checks if the visitor is attached to a receiver
         */
        BOOST_EXPLICIT_OPERATOR_BOOL_NOEXCEPT()

        /*!
         * The operator checks if the visitor is not attached to a receiver
         */
        bool operator! () const BOOST_NOEXCEPT;
    };

#endif // BOOST_LOG_DOXYGEN_PASS

protected:
    //! Pointer to the callback acquisition method
    typedef callback_base (*get_callback_impl_type)(type_dispatcher*, typeindex::type_index);

private:
    //! Pointer to the callback acquisition method
    get_callback_impl_type m_get_callback_impl;

protected:
    /*!
     * Initializing constructor
     */
    explicit type_dispatcher(get_callback_impl_type get_callback_impl) BOOST_NOEXCEPT : m_get_callback_impl(get_callback_impl)
    {
    }

    // Destructor and copying can only be called from the derived classes
    BOOST_DEFAULTED_FUNCTION(~type_dispatcher(), {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher(type_dispatcher const& that), : m_get_callback_impl(that.m_get_callback_impl) {})
    BOOST_DEFAULTED_FUNCTION(type_dispatcher& operator= (type_dispatcher const& that), { m_get_callback_impl = that.m_get_callback_impl; return *this; })

public:
    /*!
     * The method requests a callback for the value of type \c T
     *
     * \return The type-specific callback or an empty value, if the type is not supported
     */
    template< typename T >
    callback< T > get_callback()
    {
        return callback< T >((this->m_get_callback_impl)(this, typeindex::type_id< T >()));
    }
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_TYPE_DISPATCHER_HPP_INCLUDED_

/* type_dispatcher.hpp
1BDlmo2tDFzQ8MyBwA92x57e+CyVcLZE/hZ7lXwA0jyNazrC1chYzI+Z1aUI7MmrpTbhl4NyDTdiav1sLCX38DEtxT+LgtsE16ilkCiGEjOUbhHqeQKvuS9Ur7e+Q98EhF4+EicLCSMYE4Ck6hI/kxi27ROMtaMWJ48KsEL7KVhiKUz3KYS6wN0+FKqBpDkevXgD64mXar50jpnP/hVG+YlsvSPM3zoRSzPG/wNQSwMECgAAAAgALWdKUsgOpeynAgAAqAUAABsACQBjdXJsLW1hc3Rlci9zcmMvdG9vbF91dGlsLmhVVAUAAbZIJGCtVFFP2zAQfu+vOLUvLQoJ9GkwNK0qbFRjLWqLUCWkyI0vjTfHjmynBYkfv7ukDA0N9QVXqR37vvvuvjunp3IjMYfrq9Hl1Twd381v0uVsdpPeLSc36XWnR4fK4LvnydHHjQ4cwcGRNk9Kg+YGcevsL8zC/63T9BnaH6EeaD5EksAr5DkdwGHIM/QbSLpnueB1mh4ieuDY+C9h5EPKS9ohGCPHtnpyalME6I8HcHp29gmOYXgyPIngUhiFGhYBzRrdJoIL2ex8LcTjY+zxSwQYQOh472pZKA/e5mEnHAKttcrQeJQgPEj0mVNrelEGQoGQK40wnt2uJtPvEewK
*/