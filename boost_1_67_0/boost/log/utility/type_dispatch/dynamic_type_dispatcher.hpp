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