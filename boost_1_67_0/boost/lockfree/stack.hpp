//  Copyright (C) 2008-2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_STACK_HPP_INCLUDED
#define BOOST_LOCKFREE_STACK_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/checked_delete.hpp>
#include <boost/core/no_exceptions_support.hpp>
#include <boost/integer_traits.hpp>
#include <boost/static_assert.hpp>
#include <boost/tuple/tuple.hpp>
#include <boost/type_traits/is_copy_constructible.hpp>

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

    //! Construct stack
    // @{
    stack(void):
        pool(node_allocator(), capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }

    template <typename U>
    explicit stack(typename detail::allocator_rebind_helper<node_allocator, U>::type const & alloc):
        pool(alloc, capacity)
    {
        BOOST_STATIC_ASSERT(has_capacity);
        initialize();
    }

    explicit stack(allocator const & alloc):
        pool(alloc, capacity)
    {
        BOOST_ASSERT(has_capacity);
        initialize();
    }
    // @}

    //! Construct stack, allocate n nodes for the freelist.
    // @{
    explicit stack(size_type n):
        pool(node_allocator(), n)
    {
        BOOST_ASSERT(!has_capacity);
        initialize();
    }

    template <typename U>
    stack(size_type n, typename detail::allocator_rebind_helper<node_allocator, U>::type const & alloc):
        pool(alloc, n)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
        initialize();
    }
    // @}

    /** Allocate n nodes for freelist
     *
     *  \pre  only valid if no capacity<> argument given
     *  \note thread-safe, may block if memory allocator blocks
     *
     * */
    void reserve(size_type n)
    {
        BOOST_STATIC_ASSERT(!has_capacity);
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
        BOOST_STATIC_ASSERT(!has_capacity);
        pool.template reserve<false>(n);
    }

    /** Destroys stack, free all nodes from freelist.
     *
     *  \note not thread-safe
     *
     * */
    ~stack(void)
    {
        T dummy;
        while(unsynchronized_pop(dummy))
        {}
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
        end_node->next = pool.get_pointer(old_tos);

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