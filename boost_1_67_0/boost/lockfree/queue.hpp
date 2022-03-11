//  lock-free queue from
//  Michael, M. M. and Scott, M. L.,
//  "simple, fast and practical non-blocking and blocking concurrent queue algorithms"
//
//  Copyright (C) 2008-2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_FIFO_HPP_INCLUDED
#define BOOST_LOCKFREE_FIFO_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/config.hpp> // for BOOST_LIKELY & BOOST_ALIGNMENT

#include <boost/lockfree/detail/allocator_rebind_helper.hpp>
#include <boost/lockfree/detail/atomic.hpp>
#include <boost/lockfree/detail/copy_payload.hpp>
#include <boost/lockfree/detail/freelist.hpp>
#include <boost/lockfree/detail/parameter.hpp>
#include <boost/lockfree/detail/tagged_ptr.hpp>

#include <boost/lockfree/lockfree_forward.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif


#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4324) // structure was padded due to __declspec(align())
#endif

#if defined(BOOST_INTEL) && (BOOST_INTEL_CXX_VERSION > 1000)
#pragma warning(push)
#pragma warning(disable:488) // template parameter unused in declaring parameter types, 
                             // gets erronously triggered the queue constructor which
                             // takes an allocator of another type and rebinds it
#endif



namespace boost    {
namespace lockfree {
namespace detail   {

typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::capacity>
                             > queue_signature;

} /* namespace detail */


/** The queue class provides a multi-writer/multi-reader queue, pushing and popping is lock-free,
 *  construction/destruction has to be synchronized. It uses a freelist for memory management,
 *  freed nodes are pushed to the freelist and not returned to the OS before the queue is destroyed.
 *
 *  \b Policies:
 *  - \ref boost::lockfree::fixed_sized, defaults to \c boost::lockfree::fixed_sized<false> \n
 *    Can be used to completely disable dynamic memory allocations during push in order to ensure lockfree behavior. \n
 *    If the data structure is configured as fixed-sized, the internal nodes are stored inside an array and they are addressed
 *    by array indexing. This limits the possible size of the queue to the number of elements that can be addressed by the index
 *    type (usually 2**16-2), but on platforms that lack double-width compare-and-exchange instructions, this is the best way
 *    to achieve lock-freedom.
 *
 *  - \ref boost::lockfree::capacity, optional \n
 *    If this template argument is passed to the options, the size of the queue is set at compile-time.\n
 *    This option implies \c fixed_sized<true>
 *
 *  - \ref boost::lockfree::allocator, defaults to \c boost::lockfree::allocator<std::allocator<void>> \n
 *    Specifies the allocator that is used for the internal freelist
 *
 *  \b Requirements:
 *   - T must have a copy constructor
 *   - T must have a trivial assignment operator
 *   - T must have a trivial destructor
 *
 * */
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T, class A0, class A1, class A2>
#else
template <typename T, typename ...Options>
#endif
class queue
{
private:
#ifndef BOOST_DOXYGEN_INVOKED

#ifdef BOOST_HAS_TRIVIAL_DESTRUCTOR
    BOOST_STATIC_ASSERT((boost::has_trivial_destructor<T>::value));
#endif

#ifdef BOOST_HAS_TRIVIAL_ASSIGN
    BOOST_STATIC_ASSERT((boost::has_trivial_assign<T>::value));
#endif

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    typedef typename detail::queue_signature::bind<A0, A1, A2>::type bound_args;
#else
    typedef typename detail::queue_signature::bind<Options...>::type bound_args;
#endif

    static const bool has_capacity = detail::extract_capacity<bound_args>::has_capacity;
    static const size_t capacity = detail::extract_capacity<bound_args>::capacity + 1; // the queue uses one dummy node
    static const bool fixed_sized = detail::extract_fixed_sized<bound_args>::value;
    static const bool node_based = !(has_capacity || fixed_sized);
    static const bool compile_time_sized = has_capacity;

    struct BOOST_ALIGNMENT(BOOST_LOCKFREE_CACHELINE_BYTES) node
    {
        typedef typename detail::select_tagged_handle<node, node_based>::tagged_handle_type tagged_node_handle;
        typedef typename detail::select_tagged_handle<node, node_based>::handle_type handle_type;

        node(T const & v, handle_type null_handle):
            next(tagged_node_handle(null_handle, 0)), data(v)
        {
            /* increment tag to avoid ABA problem */
            tagged_node_handle old_next = next.load(memory_order_relaxed);
            tagged_node_handle new_next (null_handle, old_next.get_next_tag());
            next.store(new_next, memory_order_release);
        }

        node (handle_type null_handle):
            next(tagged_node_handle(null_handle, 0))
        {}

        node(void)
        {}

        atomic<tagged_node_handle> next;
        T data;
    };

    typedef typename detail::extract_allocator<bound_args, node>::type node_allocator;
    typedef typename detail::select_freelist<node, node_allocator, compile_time_sized, fixed_sized, capacity>::type pool_t;
    typedef typename pool_t::tagged_node_handle tagged_node_handle;
    typedef typename detail::select_tagged_handle<node, node_based>::handle_type handle_type;

    void initialize(void)
    {
        node * n = pool.template construct<true, false>(pool.null_handle());
        tagged_node_handle dummy_node(pool.get_handle(n), 0);
        head_.store(dummy_node, memory_order_relaxed);
        tail_.store(dummy_node, memory_order_release);
    }

    struct implementation_defined
    {
        typedef node_allocator allocator;
        typedef std::size_t size_type;
    };

#endif

    BOOST_DELETED_FUNCTION(queue(queue const&))
    BOOST_DELETED_FUNCTION(queue& operator= (queue const&))

public:
    typedef T value_type;
    typedef typename implementation_defined::allocator allocator;
    typedef typename implementation_defined::size_type size_type;

    /**
     * \return true, if implementation is lock-free.
     *
     * \warning It only checks, if the queue head and tail nodes and the freelist can be modified in a lock-free manner.
     *       On most platforms, the whole implementation is lock-free, if this is true. Using c++0x-style atomics, there is
     *       no possibility to provide a completely accurate implementation, because one would need to test every internal
     *       node, which is impossible if further nodes will be allocated from the operating system.
     * */
    bool is_lock_free (void) const
    {
        return head_.is_lock_free() && tail_.is_lock_free() && pool.is_lock_free();
    }

    //! Construct queue
    // @{
    queue(void):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    template <typename U>
    explicit queue(typename detail::allocator_rebind_helper<node_allocator, U>::type const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, capacity)
    {
        BOOST_STATIC_ASSERT(has_capacity);
        initialize();
    }

    explicit queue(allocator const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }
    // @}

    //! Construct queue, allocate n nodes for the freelist.
    // @{
    explicit queue(size_type n):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), n + 1)
    {
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    template <typename U>
    queue(size_type n, typename detail::allocator_rebind_helper<node_allocator, U>::type const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, n + 1)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        initialize();
    }
    // @}

    /** \copydoc boost::lockfree::stack::reserve
     * */
    void reserve(size_type n)
    {
        pool.template reserve<true>(n);
    }

    /** \copydoc boost::lockfree::stack::reserve_unsafe
     * */
    void reserve_unsafe(size_type n)
    {
        pool.template reserve<false>(n);
    }

    /** Destroys queue, free all nodes from freelist.
     * */
    ~queue(void)
    {
        T dummy;
        while(unsynchronized_pop(dummy))
        {}

        pool.template destruct<false>(head_.load(memory_order_relaxed));
    }

    /** Check if the queue is empty
     *
     * \return true, if the queue is empty, false otherwise
     * \note The result is only accurate, if no other thread modifies the queue. Therefore it is rarely practical to use this
     *       value in program logic.
     * */
    bool empty(void) const
    {
        return pool.get_handle(head_.load()) == pool.get_handle(tail_.load());
    }

    /** Pushes object t to the queue.
     *
     * \post object will be pushed to the queue, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *                    from the OS. This may not be lock-free.
     * */
    bool push(T const & t)
    {
        return do_push<false>(t);
    }

    /** Pushes object t to the queue.
     *
     * \post object will be pushed to the queue, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Thread-safe and non-blocking. If internal memory pool is exhausted, operation will fail
     * \throws if memory allocator throws
     * */
    bool bounded_push(T const & t)
    {
        return do_push<true>(t);
    }


private:
#ifndef BOOST_DOXYGEN_INVOKED
    template <bool Bounded>
    bool do_push(T const & t)
    {
        node * n = pool.template construct<true, Bounded>(t, pool.null_handle());
        handle_type node_handle = pool.get_handle(n);

        if (n == NULL)
            return false;

        for (;;) {
            tagged_node_handle tail = tail_.load(memory_order_acquire);
            node * tail_node = pool.get_pointer(tail);
            tagged_node_handle next = tail_node->next.load(memory_order_acquire);
            node * next_ptr = pool.get_pointer(next);

            tagged_node_handle tail2 = tail_.load(memory_order_acquire);
            if (BOOST_LIKELY(tail == tail2)) {
                if (next_ptr == 0) {
                    tagged_node_handle new_tail_next(node_handle, next.get_next_tag());
                    if ( tail_node->next.compare_exchange_weak(next, new_tail_next) ) {
                        tagged_node_handle new_tail(node_handle, tail.get_next_tag());
                        tail_.compare_exchange_strong(tail, new_tail);
                        return true;
                    }
                }
                else {
                    tagged_node_handle new_tail(pool.get_handle(next_ptr), tail.get_next_tag());
                    tail_.compare_exchange_strong(tail, new_tail);
                }
            }
        }
    }
#endif

public:

    /** Pushes object t to the queue.
     *
     * \post object will be pushed to the queue, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Not Thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *       from the OS. This may not be lock-free.
     * \throws if memory allocator throws
     * */
    bool unsynchronized_push(T const & t)
    {
        node * n = pool.template construct<false, false>(t, pool.null_handle());

        if (n == NULL)
            return false;

        for (;;) {
            tagged_node_handle tail = tail_.load(memory_order_relaxed);
            tagged_node_handle next = tail->next.load(memory_order_relaxed);
            node * next_ptr = next.get_ptr();

            if (next_ptr == 0) {
                tail->next.store(tagged_node_handle(n, next.get_next_tag()), memory_order_relaxed);
                tail_.store(tagged_node_handle(n, tail.get_next_tag()), memory_order_relaxed);
                return true;
            }
            else
                tail_.store(tagged_node_handle(next_ptr, tail.get_next_tag()), memory_order_relaxed);
        }
    }

    /** Pops object from queue.
     *
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if queue was empty.
     *
     * \note Thread-safe and non-blocking
     * */
    bool pop (T & ret)
    {
        return pop<T>(ret);
    }

    /** Pops object from queue.
     *
     * \pre type U must be constructible by T and copyable, or T must be convertible to U
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if queue was empty.
     *
     * \note Thread-safe and non-blocking
     * */
    template <typename U>
    bool pop (U & ret)
    {
        for (;;) {
            tagged_node_handle head = head_.load(memory_order_acquire);
            node * head_ptr = pool.get_pointer(head);

            tagged_node_handle tail = tail_.load(memory_order_acquire);
            tagged_node_handle next = head_ptr->next.load(memory_order_acquire);
            node * next_ptr = pool.get_pointer(next);

            tagged_node_handle head2 = head_.load(memory_order_acquire);
            if (BOOST_LIKELY(head == head2)) {
                if (pool.get_handle(head) == pool.get_handle(tail)) {
                    if (next_ptr == 0)
                        return false;

                    tagged_node_handle new_tail(pool.get_handle(next), tail.get_next_tag());
                    tail_.compare_exchange_strong(tail, new_tail);

                } else {
                    if (next_ptr == 0)
                        /* this check is not part of the original algorithm as published by michael and scott
                         *
                         * however we reuse the tagged_ptr part for the freelist and clear the next part during node
                         * allocation. we can observe a null-pointer here.
                         * */
                        continue;
                    detail::copy_payload(next_ptr->data, ret);

                    tagged_node_handle new_head(pool.get_handle(next), head.get_next_tag());
                    if (head_.compare_exchange_weak(head, new_head)) {
                        pool.template destruct<true>(head);
                        return true;
                    }
                }
            }
        }
    }

    /** Pops object from queue.
     *
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if queue was empty.
     *
     * \note Not thread-safe, but non-blocking
     *
     * */
    bool unsynchronized_pop (T & ret)
    {
        return unsynchronized_pop<T>(ret);
    }

    /** Pops object from queue.
     *
     * \pre type U must be constructible by T and copyable, or T must be convertible to U
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if queue was empty.
     *
     * \note Not thread-safe, but non-blocking
     *
     * */
    template <typename U>
    bool unsynchronized_pop (U & ret)
    {
        for (;;) {
            tagged_node_handle head = head_.load(memory_order_relaxed);
            node * head_ptr = pool.get_pointer(head);
            tagged_node_handle tail = tail_.load(memory_order_relaxed);
            tagged_node_handle next = head_ptr->next.load(memory_order_relaxed);
            node * next_ptr = pool.get_pointer(next);

            if (pool.get_handle(head) == pool.get_handle(tail)) {
                if (next_ptr == 0)
                    return false;

                tagged_node_handle new_tail(pool.get_handle(next), tail.get_next_tag());
                tail_.store(new_tail);
            } else {
                if (next_ptr == 0)
                    /* this check is not part of the original algorithm as published by michael and scott
                     *
                     * however we reuse the tagged_ptr part for the freelist and clear the next part during node
                     * allocation. we can observe a null-pointer here.
                     * */
                    continue;
                detail::copy_payload(next_ptr->data, ret);
                tagged_node_handle new_head(pool.get_handle(next), head.get_next_tag());
                head_.store(new_head);
                pool.template destruct<false>(head);
                return true;
            }
        }
    }

    /** consumes one element via a functor
     *
     *  pops one element from the queue and applies the functor on this object
     *
     * \returns true, if one element was consumed
     *
     * \note Thread-safe and non-blocking, if functor is thread-safe and non-blocking
     * */
    template <typename Functor>
    bool consume_one(Functor & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    /// \copydoc boost::lockfree::queue::consume_one(Functor & rhs)
    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        T element;
        bool success = pop(element);
        if (success)
            f(element);

        return success;
    }

    /** consumes all elements via a functor
     *
     * sequentially pops all elements from the queue and applies the functor on each object
     *
     * \returns number of elements that are consumed
     *
     * \note Thread-safe and non-blocking, if functor is thread-safe and non-blocking
     * */
    template <typename Functor>
    size_t consume_all(Functor & f)
    {
        size_t element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }

    /// \copydoc boost::lockfree::queue::consume_all(Functor & rhs)
    template <typename Functor>
    size_t consume_all(Functor const & f)
    {
        size_t element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }

private:
#ifndef BOOST_DOXYGEN_INVOKED
    atomic<tagged_node_handle> head_;
    static const int padding_size = BOOST_LOCKFREE_CACHELINE_BYTES - sizeof(tagged_node_handle);
    char padding1[padding_size];
    atomic<tagged_node_handle> tail_;
    char padding2[padding_size];

    pool_t pool;
#endif
};

} /* namespace lockfree */
} /* namespace boost */

#if defined(BOOST_INTEL) && (BOOST_INTEL_CXX_VERSION > 1000)
#pragma warning(pop)
#endif

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#endif /* BOOST_LOCKFREE_FIFO_HPP_INCLUDED */

/* queue.hpp
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
*/