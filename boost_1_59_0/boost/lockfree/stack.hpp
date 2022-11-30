//  Copyright (C) 2008-2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_STACK_HPP_INCLUDED
#define BOOST_LOCKFREE_STACK_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/core/allocator_access.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/integer_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>

#include <boost/lockfree/detail/atomic.hpp>
#include <boost/lockfree/detail/copy_payload.hpp>
#include <boost/lockfree/detail/freelist.hpp>
#include <boost/lockfree/detail/parameter.hpp>
#include <boost/lockfree/detail/tagged_ptr.hpp>

#include <boost/lockfree/lockfree_forward.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

typedef parameter::parameters<boost::parameter::optional<tag::allocator>,
                              boost::parameter::optional<tag::capacity>
                             > stack_signature;

}

/** The stack class provides a multi-writer/multi-reader stack, pushing and popping is lock-free,
 *  construction/destruction has to be synchronized. It uses a freelist for memory management,
 *  freed nodes are pushed to the freelist and not returned to the OS before the stack is destroyed.
 *
 *  \b Policies:
 *
 *  - \c boost::lockfree::fixed_sized<>, defaults to \c boost::lockfree::fixed_sized<false> <br>
 *    Can be used to completely disable dynamic memory allocations during push in order to ensure lockfree behavior.<br>
 *    If the data structure is configured as fixed-sized, the internal nodes are stored inside an array and they are addressed
 *    by array indexing. This limits the possible size of the stack to the number of elements that can be addressed by the index
 *    type (usually 2**16-2), but on platforms that lack double-width compare-and-exchange instructions, this is the best way
 *    to achieve lock-freedom.
 *
 *  - \c boost::lockfree::capacity<>, optional <br>
 *    If this template argument is passed to the options, the size of the stack is set at compile-time. <br>
 *    It this option implies \c fixed_sized<true>
 *
 *  - \c boost::lockfree::allocator<>, defaults to \c boost::lockfree::allocator<std::allocator<void>> <br>
 *    Specifies the allocator that is used for the internal freelist
 *
 *  \b Requirements:
 *  - T must have a copy constructor
 * */
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T, class A0, class A1, class A2>
#else
template <typename T, typename ...Options>
#endif
class stack
{
private:
#ifndef BOOST_DOXYGEN_INVOKED
    BOOST_STATIC_ASSERT(boost::is_copy_constructible<T>::value);

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    typedef typename detail::stack_signature::bind<A0, A1, A2>::type bound_args;
#else
    typedef typename detail::stack_signature::bind<Options...>::type bound_args;
#endif

    static const bool has_capacity = detail::extract_capacity<bound_args>::has_capacity;
    static const size_t capacity = detail::extract_capacity<bound_args>::capacity;
    static const bool fixed_sized = detail::extract_fixed_sized<bound_args>::value;
    static const bool node_based = !(has_capacity || fixed_sized);
    static const bool compile_time_sized = has_capacity;

    struct node
    {
        node(T const & val):
            v(val)
        {}

        typedef typename detail::select_tagged_handle<node, node_based>::handle_type handle_t;
        handle_t next;
        const T v;
    };

    typedef typename detail::extract_allocator<bound_args, node>::type node_allocator;
    typedef typename detail::select_freelist<node, node_allocator, compile_time_sized, fixed_sized, capacity>::type pool_t;
    typedef typename pool_t::tagged_node_handle tagged_node_handle;

    // check compile-time capacity
    BOOST_STATIC_ASSERT((mpl::if_c<has_capacity,
                                   mpl::bool_<capacity - 1 < boost::integer_traits<boost::uint16_t>::const_max>,
                                   mpl::true_
                                  >::type::value));

    struct implementation_defined
    {
        typedef node_allocator allocator;
        typedef std::size_t size_type;
    };

#endif

    BOOST_DELETED_FUNCTION(stack(stack const&))
    BOOST_DELETED_FUNCTION(stack& operator= (stack const&))

public:
    typedef T value_type;
    typedef typename implementation_defined::allocator allocator;
    typedef typename implementation_defined::size_type size_type;

    /**
     * \return true, if implementation is lock-free.
     *
     * \warning It only checks, if the top stack node and the freelist can be modified in a lock-free manner.
     *          On most platforms, the whole implementation is lock-free, if this is true. Using c++0x-style atomics,
     *          there is no possibility to provide a completely accurate implementation, because one would need to test
     *          every internal node, which is impossible if further nodes will be allocated from the operating system.
     *
     * */
    bool is_lock_free (void) const
    {
        return tos.is_lock_free() && pool.is_lock_free();
    }

    /** Construct a fixed-sized stack
     *
     *  \pre Must specify a capacity<> argument
     * */
    stack(void):
        pool(node_allocator(), capacity)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a fixed-sized stack with a custom allocator
     *
     *  \pre Must specify a capacity<> argument
     * */
    template <typename U>
    explicit stack(typename boost::allocator_rebind<node_allocator, U>::type const & alloc):
        pool(alloc, capacity)
    {
        BOOST_STATIC_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a fixed-sized stack with a custom allocator
     *
     *  \pre Must specify a capacity<> argument
     * */
    explicit stack(allocator const & alloc):
        pool(alloc, capacity)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    /** Construct a variable-sized stack
     *
     *  Allocate n nodes initially for the freelist
     *
     *  \pre Must \b not specify a capacity<> argument
     * */
    explicit stack(size_type n):
        pool(node_allocator(), n)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    /** Construct a variable-sized stack with a custom allocator
     *
     *  Allocate n nodes initially for the freelist
     *
     *  \pre Must \b not specify a capacity<> argument
     * */
    template <typename U>
    stack(size_type n, typename boost::allocator_rebind<node_allocator, U>::type const & alloc):
        pool(alloc, n)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        initialize();
    }

    /** Allocate n nodes for freelist
     *
     *  \pre  only valid if no capacity<> argument given
     *  \note thread-safe, may block if memory allocator blocks
     *
     * */
    void reserve(size_type n)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(!has_capacity);
        pool.template reserve<true>(n);
    }

    /** Allocate n nodes for freelist
     *
     *  \pre  only valid if no capacity<> argument given
     *  \note not thread-safe, may block if memory allocator blocks
     *
     * */
    void reserve_unsafe(size_type n)
    {
        // Don't use BOOST_STATIC_ASSERT() here since it will be evaluated when compiling
        // this function and this function may be compiled even when it isn't being used.
        BOOST_ASSERT(!has_capacity);
        pool.template reserve<false>(n);
    }

    /** Destroys stack, free all nodes from freelist.
     *
     *  \note not thread-safe
     *
     * */
    ~stack(void)
    {
        detail::consume_noop consume_functor;
        (void)consume_all(consume_functor);
    }

private:
#ifndef BOOST_DOXYGEN_INVOKED
    void initialize(void)
    {
        tos.store(tagged_node_handle(pool.null_handle(), 0));
    }

    void link_nodes_atomic(node * new_top_node, node * end_node)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_relaxed);
        for (;;) {
            tagged_node_handle new_tos (pool.get_handle(new_top_node), old_tos.get_tag());
            end_node->next = pool.get_handle(old_tos);

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }
    }

    void link_nodes_unsafe(node * new_top_node, node * end_node)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_relaxed);

        tagged_node_handle new_tos (pool.get_handle(new_top_node), old_tos.get_tag());
        end_node->next = pool.get_handle(old_tos);

        tos.store(new_tos, memory_order_relaxed);
    }

    template <bool Threadsafe, bool Bounded, typename ConstIterator>
    tuple<node*, node*> prepare_node_list(ConstIterator begin, ConstIterator end, ConstIterator & ret)
    {
        ConstIterator it = begin;
        node * end_node = pool.template construct<Threadsafe, Bounded>(*it++);
        if (end_node == NULL) {
            ret = begin;
            return make_tuple<node*, node*>(NULL, NULL);
        }

        node * new_top_node = end_node;
        end_node->next = NULL;

        BOOST_TRY {
            /* link nodes */
            for (; it != end; ++it) {
                node * newnode = pool.template construct<Threadsafe, Bounded>(*it);
                if (newnode == NULL)
                    break;
                newnode->next = new_top_node;
                new_top_node = newnode;
            }
        } BOOST_CATCH (...) {
            for (node * current_node = new_top_node; current_node != NULL;) {
                node * next = current_node->next;
                pool.template destruct<Threadsafe>(current_node);
                current_node = next;
            }
            BOOST_RETHROW;
        }
        BOOST_CATCH_END

        ret = it;
        return make_tuple(new_top_node, end_node);
    }
#endif

public:
    /** Pushes object t to the stack.
     *
     * \post object will be pushed to the stack, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *                    from the OS. This may not be lock-free.
     * \throws if memory allocator throws
     * */
    bool push(T const & v)
    {
        return do_push<false>(v);
    }

    /** Pushes object t to the stack.
     *
     * \post object will be pushed to the stack, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Thread-safe and non-blocking. If internal memory pool is exhausted, the push operation will fail
     * */
    bool bounded_push(T const & v)
    {
        return do_push<true>(v);
    }

#ifndef BOOST_DOXYGEN_INVOKED
private:
    template <bool Bounded>
    bool do_push(T const & v)
    {
        node * newnode = pool.template construct<true, Bounded>(v);
        if (newnode == 0)
            return false;

        link_nodes_atomic(newnode, newnode);
        return true;
    }

    template <bool Bounded, typename ConstIterator>
    ConstIterator do_push(ConstIterator begin, ConstIterator end)
    {
        node * new_top_node;
        node * end_node;
        ConstIterator ret;

        tie(new_top_node, end_node) = prepare_node_list<true, Bounded>(begin, end, ret);
        if (new_top_node)
            link_nodes_atomic(new_top_node, end_node);

        return ret;
    }

public:
#endif

    /** Pushes as many objects from the range [begin, end) as freelist node can be allocated.
     *
     * \return iterator to the first element, which has not been pushed
     *
     * \note Operation is applied atomically
     * \note Thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *                    from the OS. This may not be lock-free.
     * \throws if memory allocator throws
     */
    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return do_push<false, ConstIterator>(begin, end);
    }

    /** Pushes as many objects from the range [begin, end) as freelist node can be allocated.
     *
     * \return iterator to the first element, which has not been pushed
     *
     * \note Operation is applied atomically
     * \note Thread-safe and non-blocking. If internal memory pool is exhausted, the push operation will fail
     * \throws if memory allocator throws
     */
    template <typename ConstIterator>
    ConstIterator bounded_push(ConstIterator begin, ConstIterator end)
    {
        return do_push<true, ConstIterator>(begin, end);
    }


    /** Pushes object t to the stack.
     *
     * \post object will be pushed to the stack, if internal node can be allocated
     * \returns true, if the push operation is successful.
     *
     * \note Not thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *       from the OS. This may not be lock-free.
     * \throws if memory allocator throws
     * */
    bool unsynchronized_push(T const & v)
    {
        node * newnode = pool.template construct<false, false>(v);
        if (newnode == 0)
            return false;

        link_nodes_unsafe(newnode, newnode);
        return true;
    }

    /** Pushes as many objects from the range [begin, end) as freelist node can be allocated.
     *
     * \return iterator to the first element, which has not been pushed
     *
     * \note Not thread-safe. If internal memory pool is exhausted and the memory pool is not fixed-sized, a new node will be allocated
     *       from the OS. This may not be lock-free.
     * \throws if memory allocator throws
     */
    template <typename ConstIterator>
    ConstIterator unsynchronized_push(ConstIterator begin, ConstIterator end)
    {
        node * new_top_node;
        node * end_node;
        ConstIterator ret;

        tie(new_top_node, end_node) = prepare_node_list<false, false>(begin, end, ret);
        if (new_top_node)
            link_nodes_unsafe(new_top_node, end_node);

        return ret;
    }


    /** Pops object from stack.
     *
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if stack was empty.
     *
     * \note Thread-safe and non-blocking
     *
     * */
    bool pop(T & ret)
    {
        return pop<T>(ret);
    }

    /** Pops object from stack.
     *
     * \pre type T must be convertible to U
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if stack was empty.
     *
     * \note Thread-safe and non-blocking
     *
     * */
    template <typename U>
    bool pop(U & ret)
    {
        BOOST_STATIC_ASSERT((boost::is_convertible<T, U>::value));
        detail::consume_via_copy<U> consumer(ret);

        return consume_one(consumer);
    }


    /** Pops object from stack.
     *
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if stack was empty.
     *
     * \note Not thread-safe, but non-blocking
     *
     * */
    bool unsynchronized_pop(T & ret)
    {
        return unsynchronized_pop<T>(ret);
    }

    /** Pops object from stack.
     *
     * \pre type T must be convertible to U
     * \post if pop operation is successful, object will be copied to ret.
     * \returns true, if the pop operation is successful, false if stack was empty.
     *
     * \note Not thread-safe, but non-blocking
     *
     * */
    template <typename U>
    bool unsynchronized_pop(U & ret)
    {
        BOOST_STATIC_ASSERT((boost::is_convertible<T, U>::value));
        tagged_node_handle old_tos = tos.load(detail::memory_order_relaxed);
        node * old_tos_pointer = pool.get_pointer(old_tos);

        if (!pool.get_pointer(old_tos))
            return false;

        node * new_tos_ptr = pool.get_pointer(old_tos_pointer->next);
        tagged_node_handle new_tos(pool.get_handle(new_tos_ptr), old_tos.get_next_tag());

        tos.store(new_tos, memory_order_relaxed);
        detail::copy_payload(old_tos_pointer->v, ret);
        pool.template destruct<false>(old_tos);
        return true;
    }

    /** consumes one element via a functor
     *
     *  pops one element from the stack and applies the functor on this object
     *
     * \returns true, if one element was consumed
     *
     * \note Thread-safe and non-blocking, if functor is thread-safe and non-blocking
     * */
    template <typename Functor>
    bool consume_one(Functor & f)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return false;

            tagged_node_handle new_tos(old_tos_pointer->next, old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos)) {
                f(old_tos_pointer->v);
                pool.template destruct<true>(old_tos);
                return true;
            }
        }
    }

    /// \copydoc boost::lockfree::stack::consume_one(Functor & rhs)
    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return false;

            tagged_node_handle new_tos(old_tos_pointer->next, old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos)) {
                f(old_tos_pointer->v);
                pool.template destruct<true>(old_tos);
                return true;
            }
        }
    }

    /** consumes all elements via a functor
     *
     * sequentially pops all elements from the stack and applies the functor on each object
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

    /// \copydoc boost::lockfree::stack::consume_all(Functor & rhs)
    template <typename Functor>
    size_t consume_all(Functor const & f)
    {
        size_t element_count = 0;
        while (consume_one(f))
            element_count += 1;

        return element_count;
    }

    /** consumes all elements via a functor
     *
     * atomically pops all elements from the stack and applies the functor on each object
     *
     * \returns number of elements that are consumed
     *
     * \note Thread-safe and non-blocking, if functor is thread-safe and non-blocking
     * */
    template <typename Functor>
    size_t consume_all_atomic(Functor & f)
    {
        size_t element_count = 0;
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return 0;

            tagged_node_handle new_tos(pool.null_handle(), old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }

        tagged_node_handle nodes_to_consume = old_tos;

        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_to_consume);
            f(node_pointer->v);
            element_count += 1;

            node * next_node = pool.get_pointer(node_pointer->next);

            if (!next_node) {
                pool.template destruct<true>(nodes_to_consume);
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_to_consume.get_next_tag());
            pool.template destruct<true>(nodes_to_consume);
            nodes_to_consume = next;
        }

        return element_count;
    }

    /// \copydoc boost::lockfree::stack::consume_all_atomic(Functor & rhs)
    template <typename Functor>
    size_t consume_all_atomic(Functor const & f)
    {
        size_t element_count = 0;
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return 0;

            tagged_node_handle new_tos(pool.null_handle(), old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }

        tagged_node_handle nodes_to_consume = old_tos;

        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_to_consume);
            f(node_pointer->v);
            element_count += 1;

            node * next_node = pool.get_pointer(node_pointer->next);

            if (!next_node) {
                pool.template destruct<true>(nodes_to_consume);
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_to_consume.get_next_tag());
            pool.template destruct<true>(nodes_to_consume);
            nodes_to_consume = next;
        }

        return element_count;
    }

    /** consumes all elements via a functor
     *
     * atomically pops all elements from the stack and applies the functor on each object in reversed order
     *
     * \returns number of elements that are consumed
     *
     * \note Thread-safe and non-blocking, if functor is thread-safe and non-blocking
     * */
    template <typename Functor>
    size_t consume_all_atomic_reversed(Functor & f)
    {
        size_t element_count = 0;
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return 0;

            tagged_node_handle new_tos(pool.null_handle(), old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }

        tagged_node_handle nodes_to_consume = old_tos;

        node * last_node_pointer = NULL;
        tagged_node_handle nodes_in_reversed_order;
        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_to_consume);
            node * next_node    = pool.get_pointer(node_pointer->next);

            node_pointer->next  = pool.get_handle(last_node_pointer);
            last_node_pointer   = node_pointer;

            if (!next_node) {
                nodes_in_reversed_order = nodes_to_consume;
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_to_consume.get_next_tag());
            nodes_to_consume = next;
        }

        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_in_reversed_order);
            f(node_pointer->v);
            element_count += 1;

            node * next_node = pool.get_pointer(node_pointer->next);

            if (!next_node) {
                pool.template destruct<true>(nodes_in_reversed_order);
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_in_reversed_order.get_next_tag());
            pool.template destruct<true>(nodes_in_reversed_order);
            nodes_in_reversed_order = next;
        }

        return element_count;
    }

    /// \copydoc boost::lockfree::stack::consume_all_atomic_reversed(Functor & rhs)
    template <typename Functor>
    size_t consume_all_atomic_reversed(Functor const & f)
    {
        size_t element_count = 0;
        tagged_node_handle old_tos = tos.load(detail::memory_order_consume);

        for (;;) {
            node * old_tos_pointer = pool.get_pointer(old_tos);
            if (!old_tos_pointer)
                return 0;

            tagged_node_handle new_tos(pool.null_handle(), old_tos.get_next_tag());

            if (tos.compare_exchange_weak(old_tos, new_tos))
                break;
        }

        tagged_node_handle nodes_to_consume = old_tos;

        node * last_node_pointer = NULL;
        tagged_node_handle nodes_in_reversed_order;
        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_to_consume);
            node * next_node    = pool.get_pointer(node_pointer->next);

            node_pointer->next  = pool.get_handle(last_node_pointer);
            last_node_pointer   = node_pointer;

            if (!next_node) {
                nodes_in_reversed_order = nodes_to_consume;
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_to_consume.get_next_tag());
            nodes_to_consume = next;
        }

        for(;;) {
            node * node_pointer = pool.get_pointer(nodes_in_reversed_order);
            f(node_pointer->v);
            element_count += 1;

            node * next_node = pool.get_pointer(node_pointer->next);

            if (!next_node) {
                pool.template destruct<true>(nodes_in_reversed_order);
                break;
            }

            tagged_node_handle next(pool.get_handle(next_node), nodes_in_reversed_order.get_next_tag());
            pool.template destruct<true>(nodes_in_reversed_order);
            nodes_in_reversed_order = next;
        }

        return element_count;
    }
    /**
     * \return true, if stack is empty.
     *
     * \note It only guarantees that at some point during the execution of the function the stack has been empty.
     *       It is rarely practical to use this value in program logic, because the stack can be modified by other threads.
     * */
    bool empty(void) const
    {
        return pool.get_pointer(tos.load()) == NULL;
    }

private:
#ifndef BOOST_DOXYGEN_INVOKED
    detail::atomic<tagged_node_handle> tos;

    static const int padding_size = BOOST_LOCKFREE_CACHELINE_BYTES - sizeof(tagged_node_handle);
    char padding[padding_size];

    pool_t pool;
#endif
};

} /* namespace lockfree */
} /* namespace boost */

#endif /* BOOST_LOCKFREE_STACK_HPP_INCLUDED */

/* stack.hpp
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
*/