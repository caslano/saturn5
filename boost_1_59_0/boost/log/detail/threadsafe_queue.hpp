/*
 *          Copyright Andrey Semashev 2007 - 2021.
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
#include <boost/atomic/atomic.hpp>
#include <boost/move/core.hpp>
#include <boost/move/utility_core.hpp>
#include <boost/type_traits/alignment_of.hpp>
#include <boost/type_traits/aligned_storage.hpp>
#include <boost/log/utility/use_std_allocator.hpp>
#include <boost/log/detail/allocator_traits.hpp>
#include <boost/log/detail/header.hpp>

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace aux {

//! Base class for the thread-safe queue implementation
class threadsafe_queue_impl
{
public:
    struct node_base
    {
        boost::atomic< node_base* > next;
    };

protected:
    threadsafe_queue_impl();
    ~threadsafe_queue_impl();

public:
    static BOOST_LOG_API threadsafe_queue_impl* create(node_base* first_node);
    static BOOST_LOG_API void destroy(threadsafe_queue_impl* impl) BOOST_NOEXCEPT;

    static BOOST_LOG_API node_base* reset_last_node(threadsafe_queue_impl* impl) BOOST_NOEXCEPT;
    static BOOST_LOG_API bool unsafe_empty(const threadsafe_queue_impl* impl) BOOST_NOEXCEPT;
    static BOOST_LOG_API void push(threadsafe_queue_impl* impl, node_base* p);
    static BOOST_LOG_API bool try_pop(threadsafe_queue_impl* impl, node_base*& node_to_free, node_base*& node_with_value);

    // Copying and assignment is prohibited
    BOOST_DELETED_FUNCTION(threadsafe_queue_impl(threadsafe_queue_impl const&))
    BOOST_DELETED_FUNCTION(threadsafe_queue_impl& operator= (threadsafe_queue_impl const&))
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
template< typename T, typename AllocatorT = use_std_allocator >
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
        if (BOOST_LIKELY(!!p))
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
            while (try_pop(value)) {}
        }

        // Remove the last dummy node
        node* p = static_cast< node* >(threadsafe_queue_impl::reset_last_node(m_pImpl));
        alloc_traits::destroy(get_allocator(), p);
        alloc_traits::deallocate(get_allocator(), p, 1);

        threadsafe_queue_impl::destroy(m_pImpl);
    }

    /*!
     * Checks if the queue is empty. Not thread-safe, the returned result may not be actual.
     */
    bool unsafe_empty() const BOOST_NOEXCEPT { return threadsafe_queue_impl::unsafe_empty(m_pImpl); }

    /*!
     * Puts a new element to the end of the queue. Thread-safe, can be called
     * concurrently by several threads, and concurrently with the \c pop operation.
     */
    void push(const_reference value)
    {
        node* p = alloc_traits::allocate(get_allocator(), 1);
        if (BOOST_LIKELY(!!p))
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
            threadsafe_queue_impl::push(m_pImpl, p);
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
        if (threadsafe_queue_impl::try_pop(m_pImpl, dealloc, destr))
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