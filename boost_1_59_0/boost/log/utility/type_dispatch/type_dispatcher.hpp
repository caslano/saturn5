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
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
*/