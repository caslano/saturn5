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
jLX9qBP7+GU7WBI/eET8KNOdCjJeGe3dZaNiY/y0wEQZfyOsoUS0sfPKx7OZVXSN9SS8x1Ry/YmUwjPylrWyKwonuTPxCbtSINq66JqCP6LT/z26J/yXSoV/pEB4Zzkv4xJ0GEl8QYR2KXDUt+iakxT/3PhAqsgcPhpJwBl0yqAS/fv++8zUlZcPnZvg8QZJAvmf3uupqUM+B3h79SdQTydVi+R/aaRk7uP6HBPn/v5CnbmxGuAyTMiFLwz0Pv2eUJeQxTZFXdyNmDF4IJAqBDbl/BhLHN8VkHyqKynl2Jl3FDs6nYTPYVHyyFECfH4l+rZ3VxfQvzKLYCCA5nBF/KslE9WhPI2UNAhwVJWBI8zkQwyO1NG48yZl5pit/YAR40IiRfUpVkZpla0S6fVQbjH9fU4d5e9673ipK7VFLssIccdW9Vzfj+y6REe8gmjbJNfK3tGK6b8GbqgHepCLgMotSGcePe3o4FXE1+pgzyYsZtzY2I44WOamc4QgW3kbYEXuAzDneUfZ0I2CL1X5juITL7TSi9762WbP47H0xHyE80spF0dbRn4ax/KMR9Vn6g7DyTO6maX6NW6862mf6YXpQBvn7CBp5tW79FvrlTnDUyVnBJ26ggvD2ZZhNet0QR77BtpVC7hDP2wruCkPWmTtI9h1p330+4Td5yfDbkPdMHYbofCCviht91KGwlv1xalf3Px7Z/l5aTeN
*/