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