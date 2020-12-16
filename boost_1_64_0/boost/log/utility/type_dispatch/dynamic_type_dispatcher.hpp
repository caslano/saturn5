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
HleKfzMtXq13l/x23a72Nm0Pa+jD5lj2jvjHGbJxJ+PcY1j1xq98v3pYrWXdjYNUP33zFbQV36Y+prKm1ixlWY+UcG19lTXjses4Nr4z4n+F1hCpulBLspc341Dpy9L1KA0W/8bK8u9TRfnnVir/rTVQ/nF+9Vw52y9V79f53kdV7+P52l8NfB8y0P1VX/t+h2Xf9ddvrXynW53n6z64q3/I8Udyn/O9X6reBw58PzbQfVT1PrCP/eca3C/1tX9r3OvlfmkEqKLSPcvWlPlsAwwHtjX0GXE+y+9GRSX9EYXkm857trfxvups8heDUsg/ifzngeaZ7iG7/TLINwHo9s8HxlKvSVPq/biU7l2p36Q3cCIwVeL23IfPA6YxXDrvC0+g+0S6G/pJmK4oRXl0Zb4u4z3cK0zlEeunPG4n3x0sj7uYr3mm+7Ol5G8q/FbZ2/bk70D+FMrgduR+didgE2Bnc/1sUaVHfQ96EdNzr1k/DPl7Cb9VP8xV5O9PPR1DgFHUC5RIvUBJdG8IvAZ4IfUEdQAOAnajvqCeEo76F/Txld+Pikr6F1L53uFsByOBjYCj2B5u4D3o0cDWwDHAzsCxfM84YB+Gu5L38fvyN3QsyR53fkj0/8Xd4V/KXvci1Ndq0E7QaVCYK1pLBnUDjQDlu4J74cEn+ASf4BN8gk/wCT7BJ/gEn+ATfP67np/p/B9Yc+f//azn/4jbc/7/ZQvNsG9wsY/z/5Qt3vN/YRXzLFWfAZllAAb7kAGI5XkDYg1YBiB2i3MZgNgtzmUAYrf8Z2QAYn3IAFRsMsrIrwzA3zc5kwFAfH5lAMI2Vy0DULHJuQxAxSbnMgAM61MGoMXm/24ZgA2sw8tZhz14nrxhs1GHShmAerr9UAl3qS87u4jH2jaXxwZq/9QqI3DSh4xAmbfNBSQjULbJuYxA2SbnMgJlm/5zMgLrOCB21/W7s07z/8XeuQB4NeVx/P4fM00zU02v6Sk9Ri/p/Y6EIimSJHmkx0ylmhnNjB6szTu0GQlJKJIQklBS8g6tDaHF7hbWZrHatFjrsZ//7/+99///z/9OTVj7mj+nz9zfedzzuueee87vnBMr0/3qCMw1t4198kzhKB9e6207pBfHn3k72+zbeGlfXoH9U/anT7C4HH2CVbFyPyB9glXPVFyfYNUzP48+wQIdUn+lnsUrVLedWBqlT+B/LlQtc3eeU4UUtuJtOMz/bHjC89craKJ2OcXsp9ozXQ/TEzPcqWZnd6V5/g/xwpTM/xxZ1YnjzL4N4aUlPy8+/tWOevP3p5v9YbitFudGbZzq7CBz05I1cGmWP02jbrx4H4K95RflmOJE298Xs+2MGPQZflw7XLjfM2Wj7pqaLD+h3J/VVMKj6ss8It2GrKe9cpdug3+5dzB3v6K8Upx+hDDJCfn3P57213FoorWNdc1+lXMI/47GTGf2dD53qWX5J//EsoczywtXcj+9B+8939zsb3HqEosTieN0/7OECce/XcnWeWVHmv2FTgdSOpKwkuqK0jHX3HXFPrmuZLt1xdycQV05mPnFdN/6cpy5meVbX563+vLDzxirud8zxhLqy/+1LkaN9wPI73x7a6MXLhv2q+kH3bTiVwP2fl6pi1FRXYyOz5Wvi9FRc9+dpIvROV73YB9z/ffI30rN9a/RXP8q+S9V37g8XYzrpYtxo/zdJF2M5ZqDX6i59ztgN8m7w0XSxbhFuhiLpYtxFxwtd+doD/2xkudJvgee4/ZJ1efdLb3X4e5Dq3gdI12M/orfIO2JPkDxOha2lG7CYdJF6C13yj/1Af3z7zHl31rl33rd53H5H+r2s2Av+a8Sp//WTf57wnrSGak=
*/