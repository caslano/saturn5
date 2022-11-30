/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   static_type_dispatcher.hpp
 * \author Andrey Semashev
 * \date   15.04.2007
 *
 * The header contains implementation of a compile-time type dispatcher.
 */

#ifndef BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_
#define BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_

#include <cstddef>
#include <utility>
#include <iterator>
#include <algorithm>
#include <boost/array.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_index.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/core/addressof.hpp>
#include <boost/log/detail/config.hpp>
#include <boost/log/utility/once_block.hpp>
#include <boost/log/utility/type_dispatch/type_dispatcher.hpp>
#include <boost/log/detail/header.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Ordering predicate for type dispatching map
struct dispatching_map_order
{
    typedef bool result_type;
    typedef std::pair< typeindex::type_index, void* > first_argument_type, second_argument_type;
    result_type operator() (first_argument_type const& left, second_argument_type const& right) const
    {
        return (left.first < right.first);
    }
};

//! Dispatching map filler
template< typename VisitorT >
struct dispatching_map_initializer
{
    template< typename IteratorT >
    static BOOST_FORCEINLINE void init(IteratorT*, IteratorT*, std::pair< typeindex::type_index, void* >*)
    {
    }

    template< typename BeginIteratorT, typename EndIteratorT >
    static BOOST_FORCEINLINE void init(BeginIteratorT*, EndIteratorT* end, std::pair< typeindex::type_index, void* >* p)
    {
        typedef typename mpl::deref< BeginIteratorT >::type type;
        do_init(static_cast< type* >(0), p);

        typedef typename mpl::next< BeginIteratorT >::type next_iterator_type;
        init(static_cast< next_iterator_type* >(0), end, p + 1);
    }

private:
    template< typename T >
    static BOOST_FORCEINLINE void do_init(T*, std::pair< typeindex::type_index, void* >* p)
    {
        p->first = typeindex::type_id< T >();

        typedef void (*trampoline_t)(void*, T const&);
        BOOST_STATIC_ASSERT_MSG(sizeof(trampoline_t) == sizeof(void*), "Boost.Log: Unsupported platform, the size of a function pointer differs from the size of a pointer");
        union
        {
            void* as_pvoid;
            trampoline_t as_trampoline;
        }
        caster;
        caster.as_trampoline = (trampoline_t)&type_dispatcher::callback_base::trampoline< VisitorT, T >;
        p->second = caster.as_pvoid;
    }
};

//! A base class for a dispatcher that supports a sequence of types
class type_sequence_dispatcher_base :
    public type_dispatcher
{
private:
    //! Dispatching map element type
    typedef std::pair< typeindex::type_index, void* > dispatching_map_element_type;

private:
    //! Dispatching map
    const dispatching_map_element_type* m_dispatching_map_begin;
    //! Dispatching map size
    std::size_t m_dispatching_map_size;
    //! Pointer to the receiver function
    void* m_visitor;

protected:
    //! Initializing constructor
    type_sequence_dispatcher_base(const dispatching_map_element_type* disp_map, std::size_t disp_map_size, void* visitor) BOOST_NOEXCEPT :
        type_dispatcher(&type_sequence_dispatcher_base::get_callback),
        m_dispatching_map_begin(disp_map),
        m_dispatching_map_size(disp_map_size),
        m_visitor(visitor)
    {
    }

private:
    //! The get_callback method implementation
    static callback_base get_callback(type_dispatcher* p, typeindex::type_index type)
    {
        type_sequence_dispatcher_base* const self = static_cast< type_sequence_dispatcher_base* >(p);
        const dispatching_map_element_type* begin = self->m_dispatching_map_begin;
        const dispatching_map_element_type* end = begin + self->m_dispatching_map_size;
        const dispatching_map_element_type* it = std::lower_bound
        (
            begin,
            end,
            dispatching_map_element_type(type, (void*)0),
            dispatching_map_order()
        );

        if (it != end && it->first == type)
            return callback_base(self->m_visitor, it->second);
        else
            return callback_base();
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher_base(type_sequence_dispatcher_base const&))
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher_base& operator= (type_sequence_dispatcher_base const&))
};

//! A dispatcher that supports a sequence of types
template< typename TypeSequenceT >
class type_sequence_dispatcher :
    public type_sequence_dispatcher_base
{
public:
    //! Type sequence of the supported types
    typedef TypeSequenceT supported_types;

private:
    //! The dispatching map
    typedef array<
        std::pair< typeindex::type_index, void* >,
        mpl::size< supported_types >::value
    > dispatching_map;

public:
    /*!
     * Constructor. Initializes the dispatcher internals.
     */
    template< typename VisitorT >
    explicit type_sequence_dispatcher(VisitorT& visitor) :
        type_sequence_dispatcher_base(get_dispatching_map< VisitorT >().data(), dispatching_map::static_size, (void*)boost::addressof(visitor))
    {
    }

private:
    //! The method returns the dispatching map instance
    template< typename VisitorT >
    static dispatching_map const& get_dispatching_map()
    {
        static const dispatching_map* pinstance = NULL;

        BOOST_LOG_ONCE_BLOCK()
        {
            static dispatching_map instance;
            typename dispatching_map::value_type* p = &*instance.begin();

            typedef typename mpl::begin< supported_types >::type begin_iterator_type;
            typedef typename mpl::end< supported_types >::type end_iterator_type;
            typedef dispatching_map_initializer< VisitorT > initializer;
            initializer::init(static_cast< begin_iterator_type* >(0), static_cast< end_iterator_type* >(0), p);

            std::sort(instance.begin(), instance.end(), dispatching_map_order());

            pinstance = &instance;
        }

        return *pinstance;
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher(type_sequence_dispatcher const&))
    BOOST_DELETED_FUNCTION(type_sequence_dispatcher& operator= (type_sequence_dispatcher const&))
};

//! A base class for a single-type dispatcher
class single_type_dispatcher_base :
    public type_dispatcher
{
private:
    //! The type to match against
    typeindex::type_index m_type;
    //! A callback for the supported type
    callback_base m_callback;

protected:
    //! Initializing constructor
    single_type_dispatcher_base(typeindex::type_index type, callback_base const& cb) BOOST_NOEXCEPT :
        type_dispatcher(&single_type_dispatcher_base::get_callback),
        m_type(type),
        m_callback(cb)
    {
    }

private:
    //! The get_callback method implementation
    static callback_base get_callback(type_dispatcher* p, typeindex::type_index type)
    {
        single_type_dispatcher_base* const self = static_cast< single_type_dispatcher_base* >(p);
        if (type == self->m_type)
            return self->m_callback;
        else
            return callback_base();
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(single_type_dispatcher_base(single_type_dispatcher_base const&))
    BOOST_DELETED_FUNCTION(single_type_dispatcher_base& operator= (single_type_dispatcher_base const&))
};

//! A simple dispatcher that only supports one type
template< typename T >
class single_type_dispatcher :
    public single_type_dispatcher_base
{
private:
    typedef void (*trampoline_t)(void*, T const&);

public:
    //! Constructor
    template< typename VisitorT >
    explicit single_type_dispatcher(VisitorT& visitor) BOOST_NOEXCEPT :
        single_type_dispatcher_base(typeindex::type_id< T >(), callback_base((void*)boost::addressof(visitor), (trampoline_t)&callback_base::trampoline< VisitorT, T >))
    {
    }

    //  Copying and assignment closed
    BOOST_DELETED_FUNCTION(single_type_dispatcher(single_type_dispatcher const&))
    BOOST_DELETED_FUNCTION(single_type_dispatcher& operator= (single_type_dispatcher const&))
};

} // namespace aux

/*!
 * \brief A static type dispatcher class
 *
 * The type dispatcher can be used to pass objects of arbitrary types from one
 * component to another. With regard to the library, the type dispatcher
 * can be used to extract attribute values.
 *
 * Static type dispatchers allow to specify one or several supported types at compile
 * time.
 */
template< typename T >
class static_type_dispatcher
#ifndef BOOST_LOG_DOXYGEN_PASS
    :
    public mpl::if_<
        mpl::is_sequence< T >,
        boost::log::aux::type_sequence_dispatcher< T >,
        boost::log::aux::single_type_dispatcher< T >
    >::type
#endif
{
private:
    //! Base type
    typedef typename mpl::if_<
        mpl::is_sequence< T >,
        boost::log::aux::type_sequence_dispatcher< T >,
        boost::log::aux::single_type_dispatcher< T >
    >::type base_type;

public:
    /*!
     * Constructor. Initializes the dispatcher internals.
     *
     * The \a receiver object is not copied inside the dispatcher, but references to
     * it may be kept by the dispatcher after construction. The receiver object must remain
     * valid until the dispatcher is destroyed.
     *
     * \param receiver Unary function object that will be called on a dispatched value. The receiver
     *                 must be callable with an argument of any of the supported types of the dispatcher.
     */
    template< typename ReceiverT >
    explicit static_type_dispatcher(ReceiverT& receiver) :
        base_type(receiver)
    {
    }

    //  Copying and assignment prohibited
    BOOST_DELETED_FUNCTION(static_type_dispatcher(static_type_dispatcher const&))
    BOOST_DELETED_FUNCTION(static_type_dispatcher& operator= (static_type_dispatcher const&))
};

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_STATIC_TYPE_DISPATCHER_HPP_INCLUDED_

/* static_type_dispatcher.hpp
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
*/