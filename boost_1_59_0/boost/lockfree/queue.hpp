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
#include <boost/core/allocator_access.hpp>
#include <boost/type_traits/has_trivial_assign.hpp>
#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/config.hpp> // for BOOST_LIKELY & BOOST_ALIGNMENT

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
            data(v)
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

    /** Construct a fixed-sized queue
     *
     *  \pre Must specify a capacity<> argument
     * */
    queue(void):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), capacity)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a fixed-sized queue with a custom allocator
     *
     *  \pre Must specify a capacity<> argument
     * */
    template <typename U>
    explicit queue(typename boost::allocator_rebind<node_allocator, U>::type const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, capacity)
    {
        BOOST_STATIC_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a fixed-sized queue with a custom allocator
     *
     *  \pre Must specify a capacity<> argument
     * */
    explicit queue(allocator const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, capacity)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a variable-sized queue
     *
     *  Allocate n nodes initially for the freelist
     *
     *  \pre Must \b not specify a capacity<> argument
     * */
    explicit queue(size_type n):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(node_allocator(), n + 1)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    /** Construct a variable-sized queue with a custom allocator
     *
     *  Allocate n nodes initially for the freelist
     *
     *  \pre Must \b not specify a capacity<> argument
     * */
    template <typename U>
    queue(size_type n, typename boost::allocator_rebind<node_allocator, U>::type const & alloc):
        head_(tagged_node_handle(0, 0)),
        tail_(tagged_node_handle(0, 0)),
        pool(alloc, n + 1)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        initialize();
    }

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