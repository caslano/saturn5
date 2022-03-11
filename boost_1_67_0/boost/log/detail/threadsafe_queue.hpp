/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   threadsafe_queue.hpp
 * \author Andrey Semashev
 * \date   05.11.2010
 *
 * \brief  This header is the Boost.Log library implementation, see the library documentation
 *         at http://www.boost.org/doc/libs/release/libs/log/doc/html/index.html.
 */

#ifndef BOOST_LOG_DETAIL_THREADSAFE_QUEUE_HPP_INCLUDED_
#define BOOST_LOG_DETAIL_THREADSAFE_QUEUE_HPP_INCLUDED_

#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

#ifndef BOOST_LOG_NO_THREADS

#include <new>
#include <memory>
#include <cstddef>
#include <boost/aligned_storage.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/type_with_alignment.hpp>
#include <boost/log/detail/allocator_traits.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Base class for the thread-safe queue implementation
struct threadsafe_queue_impl
{
    struct BOOST_LOG_MAY_ALIAS pointer_storage
    {
        union
        {
            void* data[2];
            type_with_alignment< 2 * sizeof(void*) >::type alignment;
        };
    };

    struct node_base
    {
        pointer_storage next;
    };

    static BOOST_LOG_API threadsafe_queue_impl* create(node_base* first_node);

    static BOOST_LOG_API void* operator new (std::size_t size);
    static BOOST_LOG_API void operator delete (void* p, std::size_t);

    virtual ~threadsafe_queue_impl() {}
    virtual node_base* reset_last_node() = 0;
    virtual bool unsafe_empty() = 0;
    virtual void push(node_base* p) = 0;
    virtual bool try_pop(node_base*& node_to_free, node_base*& node_with_value) = 0;
};

//! Thread-safe queue node type
template< typename T >
struct threadsafe_queue_node :
    public threadsafe_queue_impl::node_base
{
    typedef typename aligned_storage< sizeof(T), alignment_of< T >::value >::type storage_type;
    storage_type storage;

    BOOST_DEFAULTED_FUNCTION(threadsafe_queue_node(), {})
    explicit threadsafe_queue_node(T const& val) { new (storage.address()) T(val); }
    T& value() BOOST_NOEXCEPT { return *static_cast< T* >(storage.address()); }
    void destroy() BOOST_NOEXCEPT { static_cast< T* >(storage.address())->~T(); }

    // Copying and assignment is prohibited
    BOOST_DELETED_FUNCTION(threadsafe_queue_node(threadsafe_queue_node const&))
    BOOST_DELETED_FUNCTION(threadsafe_queue_node& operator= (threadsafe_queue_node const&))
};

/*!
 * \brief An unbounded thread-safe queue
 *
 * The implementation is based on algorithms published in the "Simple, Fast,
 * and Practical Non-Blocking and Blocking Concurrent Queue Algorithms" article
 * in PODC96 by Maged M. Michael and Michael L. Scott. Pseudocode is available here:
 * http://www.cs.rochester.edu/research/synchronization/pseudocode/queues.html
 *
 * The implementation provides thread-safe \c push and \c try_pop operations, as well as
 * a thread-unsafe \c empty operation. The queue imposes the following requirements
 * on the element type:
 *
 * \li Default constructible, the default constructor must not throw.
 * \li Copy constructible.
 * \li Movable (i.e. there should be an efficient move assignment for this type).
 *
 * The last requirement is not mandatory but is crucial for decent performance.
 */
template< typename T, typename AllocatorT = std::allocator< void > >
class threadsafe_queue :
    private boost::log::aux::rebind_alloc< AllocatorT, threadsafe_queue_node< T > >::type
{
private:
    typedef threadsafe_queue_node< T > node;

public:
    typedef typename boost::log::aux::rebind_alloc< AllocatorT, node >::type allocator_type;
    typedef T value_type;
    typedef T& reference;
    typedef T const& const_reference;
    typedef T* pointer;
    typedef T const* const_pointer;
    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

private:
    typedef boost::log::aux::allocator_traits< allocator_type > alloc_traits;

    //! A simple scope guard to automate memory reclaiming
    struct auto_deallocate;
    friend struct auto_deallocate;
    struct auto_deallocate
    {
        auto_deallocate(allocator_type* alloc, node* dealloc, node* destr) BOOST_NOEXCEPT :
            m_pAllocator(alloc),
            m_pDeallocate(dealloc),
            m_pDestroy(destr)
        {
        }
        ~auto_deallocate() BOOST_NOEXCEPT
        {
            alloc_traits::destroy(*m_pAllocator, m_pDeallocate);
            alloc_traits::deallocate(*m_pAllocator, m_pDeallocate, 1);
            m_pDestroy->destroy();
        }

    private:
        allocator_type* m_pAllocator;
        node* m_pDeallocate;
        node* m_pDestroy;
    };

public:
    /*!
     * Default constructor, creates an empty queue. Unlike most containers,
     * the constructor requires memory allocation.
     *
     * \throw std::bad_alloc if there is not sufficient memory
     */
    threadsafe_queue(allocator_type const& alloc = allocator_type()) :
        allocator_type(alloc)
    {
        node* p = alloc_traits::allocate(get_allocator(), 1);
        if (p)
        {
            try
            {
                alloc_traits::construct(get_allocator(), p);
                try
                {
                    m_pImpl = threadsafe_queue_impl::create(p);
                }
                catch (...)
                {
                    alloc_traits::destroy(get_allocator(), p);
                    throw;
                }
            }
            catch (...)
            {
                alloc_traits::deallocate(get_allocator(), p, 1);
                throw;
            }
        }
        else
            throw std::bad_alloc();
    }
    /*!
     * Destructor
     */
    ~threadsafe_queue() BOOST_NOEXCEPT
    {
        // Clear the queue
        if (!unsafe_empty())
        {
            value_type value;
            while (try_pop(value));
        }

        // Remove the last dummy node
        node* p = static_cast< node* >(m_pImpl->reset_last_node());
        alloc_traits::destroy(get_allocator(), p);
        alloc_traits::deallocate(get_allocator(), p, 1);

        delete m_pImpl;
    }

    /*!
     * Checks if the queue is empty. Not thread-safe, the returned result may not be actual.
     */
    bool unsafe_empty() const { return m_pImpl->unsafe_empty(); }

    /*!
     * Puts a new element to the end of the queue. Thread-safe, can be called
     * concurrently by several threads, and concurrently with the \c pop operation.
     */
    void push(const_reference value)
    {
        node* p = alloc_traits::allocate(get_allocator(), 1);
        if (p)
        {
            try
            {
                alloc_traits::construct(get_allocator(), p, value);
            }
            catch (...)
            {
                alloc_traits::deallocate(get_allocator(), p, 1);
                throw;
            }
            m_pImpl->push(p);
        }
        else
            throw std::bad_alloc();
    }

    /*!
     * Attempts to pop an element from the beginning of the queue. Thread-safe, can
     * be called concurrently with the \c push operation. Should not be called by
     * several threads concurrently.
     */
    bool try_pop(reference value)
    {
        threadsafe_queue_impl::node_base *dealloc, *destr;
        if (m_pImpl->try_pop(dealloc, destr))
        {
            node* p = static_cast< node* >(destr);
            auto_deallocate guard(static_cast< allocator_type* >(this), static_cast< node* >(dealloc), p);
            value = boost::move(p->value());
            return true;
        }
        else
            return false;
    }

    // Copying and assignment is prohibited
    BOOST_DELETED_FUNCTION(threadsafe_queue(threadsafe_queue const&))
    BOOST_DELETED_FUNCTION(threadsafe_queue& operator= (threadsafe_queue const&))

private:
    //! Returns the allocator instance
    allocator_type& get_allocator() BOOST_NOEXCEPT { return *static_cast< allocator_type* >(this); }

private:
    //! Pointer to the implementation
    threadsafe_queue_impl* m_pImpl;
};

} // namespace aux

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#include <boost/log/detail/footer.hpp>

#endif // BOOST_LOG_NO_THREADS

#endif // BOOST_LOG_DETAIL_THREADSAFE_QUEUE_HPP_INCLUDED_

/* threadsafe_queue.hpp
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
*/