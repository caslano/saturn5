/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   dynamic_type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains implementation of the run-time type dispatcher.
 */

#ifndef BOOST_LOG_DYNAMIC_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_DYNAMIC_TYPE_DISPATCHER_HPP_INCLUDED_

#include <new>
#include <memory>
#include <map>
#include <boost/ref.hpp>
#include <boost/type_index.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

/*!
 * \brief A dynamic type dispatcher
 *
 * The type dispatcher can be used to pass objects of arbitrary types from one
 * component to another. With regard to the library, the type dispatcher
 * can be used to extract attribute values.
 *
 * The dynamic type dispatcher can be initialized in run time and, therefore,
 * can support different types, depending on runtime conditions. Each
 * supported type is associated with a functional object that will be called
 * when an object of the type is dispatched.
 */
class dynamic_type_dispatcher :
    public type_dispatcher
{
private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    template< typename T, typename VisitorT >
    class callback_impl :
        public callback_base
    {
    private:
        VisitorT m_Visitor;

    public:
        explicit callback_impl(VisitorT const& visitor) : m_Visitor(visitor)
        {
            this->m_pVisitor = (void*)boost::addressof(m_Visitor);
            typedef void (*trampoline_t)(void*, T const&);
            BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
            union
            {
                void* as_pvoid;
                trampoline_t as_trampoline;
            }
            caster;
            caster.as_trampoline = (trampoline_t)&callback_base::trampoline< VisitorT, T >;
            this->m_pTrampoline = caster.as_pvoid;
        }
    };
#endif // BOOST_LOG_DOXYGEN_PASS

    //! The dispatching map
    typedef std::map< typeindex::type_index, shared_ptr< callback_base > > dispatching_map;
    dispatching_map m_DispatchingMap;

public:
    /*!
     * Default constructor
     */
    dynamic_type_dispatcher() : type_dispatcher(&dynamic_type_dispatcher::get_callback)
    {
    }

    /*!
     * Copy constructor
     */
    dynamic_type_dispatcher(dynamic_type_dispatcher const& that) :
        type_dispatcher(static_cast< type_dispatcher const& >(that)),
        m_DispatchingMap(that.m_DispatchingMap)
    {
    }

    /*!
     * Copy assignment
     */
    dynamic_type_dispatcher& operator= (dynamic_type_dispatcher const& that)
    {
        m_DispatchingMap = that.m_DispatchingMap;
        return *this;
    }

    /*!
     * The method registers a new type
     *
     * \param visitor Function object that will be associated with the type \c T
     */
    template< typename T, typename VisitorT >
    void register_type(VisitorT const& visitor)
    {
        boost::shared_ptr< callback_base > p(
            boost::make_shared< callback_impl< T, VisitorT > >(boost::cref(visitor)));

        typeindex::type_index wrapper(typeindex::type_id< T >());
        m_DispatchingMap[wrapper].swap(p);
    }

    /*!
     * The method returns the number of registered types
     */
    dispatching_map::size_type registered_types_count() const
    {
        return m_DispatchingMap.size();
    }

private:
#ifndef BOOST_LOG_DOXYGEN_PASS
    static callback_base get_callback(type_dispatcher* p, typeindex::type_index type)
    {
        dynamic_type_dispatcher* const self = static_cast< dynamic_type_dispatcher* >(p);
        dispatching_map::iterator it = self->m_DispatchingMap.find(type);
        if (it != self->m_DispatchingMap.end())
            return *it->second;
        else
            return callback_base();
    }
#endif // BOOST_LOG_DOXYGEN_PASS
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_DYNAMIC_TYPE_DISPATCHER_HPP_INCLUDED_

/* dynamic_type_dispatcher.hpp
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
*/