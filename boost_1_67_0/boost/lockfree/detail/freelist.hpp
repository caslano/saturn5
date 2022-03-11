//  lock-free freelist
//
//  Copyright (C) 2008-2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_FREELIST_HPP_INCLUDED
#define BOOST_LOCKFREE_FREELIST_HPP_INCLUDED

#include <limits>
#include <memory>

#include <boost/array.hpp>
#include <boost/config.hpp>
#include <boost/cstdint.hpp>
#include <boost/noncopyable.hpp>
#include <boost/static_assert.hpp>

#include <boost/align/align_up.hpp>
#include <boost/align/aligned_allocator_adaptor.hpp>

#include <boost/lockfree/detail/atomic.hpp>
#include <boost/lockfree/detail/parameter.hpp>
#include <boost/lockfree/detail/tagged_ptr.hpp>

#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable: 4100) // unreferenced formal parameter
#pragma warning(disable: 4127) // conditional expression is constant
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

template <typename T,
          typename Alloc = std::allocator<T>
         >
class freelist_stack:
    Alloc
{
    struct freelist_node
    {
        tagged_ptr<freelist_node> next;
    };

    typedef tagged_ptr<freelist_node> tagged_node_ptr;

public:
    typedef T *           index_t;
    typedef tagged_ptr<T> tagged_node_handle;

    template <typename Allocator>
    freelist_stack (Allocator const & alloc, std::size_t n = 0):
        Alloc(alloc),
        pool_(tagged_node_ptr(NULL))
    {
        for (std::size_t i = 0; i != n; ++i) {
            T * node = Alloc::allocate(1);
#ifdef BOOST_LOCKFREE_FREELIST_INIT_RUNS_DTOR
            destruct<false>(node);
#else
            deallocate<false>(node);
#endif
        }
    }

    template <bool ThreadSafe>
    void reserve (std::size_t count)
    {
        for (std::size_t i = 0; i != count; ++i) {
            T * node = Alloc::allocate(1);
            deallocate<ThreadSafe>(node);
        }
    }

    template <bool ThreadSafe, bool Bounded>
    T * construct (void)
    {
        T * node = allocate<ThreadSafe, Bounded>();
        if (node)
            new(node) T();
        return node;
    }

    template <bool ThreadSafe, bool Bounded, typename ArgumentType>
    T * construct (ArgumentType const & arg)
    {
        T * node = allocate<ThreadSafe, Bounded>();
        if (node)
            new(node) T(arg);
        return node;
    }

    template <bool ThreadSafe, bool Bounded, typename ArgumentType1, typename ArgumentType2>
    T * construct (ArgumentType1 const & arg1, ArgumentType2 const & arg2)
    {
        T * node = allocate<ThreadSafe, Bounded>();
        if (node)
            new(node) T(arg1, arg2);
        return node;
    }

    template <bool ThreadSafe>
    void destruct (tagged_node_handle const & tagged_ptr)
    {
        T * n = tagged_ptr.get_ptr();
        n->~T();
        deallocate<ThreadSafe>(n);
    }

    template <bool ThreadSafe>
    void destruct (T * n)
    {
        n->~T();
        deallocate<ThreadSafe>(n);
    }

    ~freelist_stack(void)
    {
        tagged_node_ptr current = pool_.load();

        while (current) {
            freelist_node * current_ptr = current.get_ptr();
            if (current_ptr)
                current = current_ptr->next;
            Alloc::deallocate((T*)current_ptr, 1);
        }
    }

    bool is_lock_free(void) const
    {
        return pool_.is_lock_free();
    }

    T * get_handle(T * pointer) const
    {
        return pointer;
    }

    T * get_handle(tagged_node_handle const & handle) const
    {
        return get_pointer(handle);
    }

    T * get_pointer(tagged_node_handle const & tptr) const
    {
        return tptr.get_ptr();
    }

    T * get_pointer(T * pointer) const
    {
        return pointer;
    }

    T * null_handle(void) const
    {
        return NULL;
    }

protected: // allow use from subclasses
    template <bool ThreadSafe, bool Bounded>
    T * allocate (void)
    {
        if (ThreadSafe)
            return allocate_impl<Bounded>();
        else
            return allocate_impl_unsafe<Bounded>();
    }

private:
    template <bool Bounded>
    T * allocate_impl (void)
    {
        tagged_node_ptr old_pool = pool_.load(memory_order_consume);

        for(;;) {
            if (!old_pool.get_ptr()) {
                if (!Bounded)
                    return Alloc::allocate(1);
                else
                    return 0;
            }

            freelist_node * new_pool_ptr = old_pool->next.get_ptr();
            tagged_node_ptr new_pool (new_pool_ptr, old_pool.get_next_tag());

            if (pool_.compare_exchange_weak(old_pool, new_pool)) {
                void * ptr = old_pool.get_ptr();
                return reinterpret_cast<T*>(ptr);
            }
        }
    }

    template <bool Bounded>
    T * allocate_impl_unsafe (void)
    {
        tagged_node_ptr old_pool = pool_.load(memory_order_relaxed);

        if (!old_pool.get_ptr()) {
            if (!Bounded)
                return Alloc::allocate(1);
            else
                return 0;
        }

        freelist_node * new_pool_ptr = old_pool->next.get_ptr();
        tagged_node_ptr new_pool (new_pool_ptr, old_pool.get_next_tag());

        pool_.store(new_pool, memory_order_relaxed);
        void * ptr = old_pool.get_ptr();
        return reinterpret_cast<T*>(ptr);
    }

protected:
    template <bool ThreadSafe>
    void deallocate (T * n)
    {
        if (ThreadSafe)
            deallocate_impl(n);
        else
            deallocate_impl_unsafe(n);
    }

private:
    void deallocate_impl (T * n)
    {
        void * node = n;
        tagged_node_ptr old_pool = pool_.load(memory_order_consume);
        freelist_node * new_pool_ptr = reinterpret_cast<freelist_node*>(node);

        for(;;) {
            tagged_node_ptr new_pool (new_pool_ptr, old_pool.get_tag());
            new_pool->next.set_ptr(old_pool.get_ptr());

            if (pool_.compare_exchange_weak(old_pool, new_pool))
                return;
        }
    }

    void deallocate_impl_unsafe (T * n)
    {
        void * node = n;
        tagged_node_ptr old_pool = pool_.load(memory_order_relaxed);
        freelist_node * new_pool_ptr = reinterpret_cast<freelist_node*>(node);

        tagged_node_ptr new_pool (new_pool_ptr, old_pool.get_tag());
        new_pool->next.set_ptr(old_pool.get_ptr());

        pool_.store(new_pool, memory_order_relaxed);
    }

    atomic<tagged_node_ptr> pool_;
};

class
BOOST_ALIGNMENT( 4 ) // workaround for bugs in MSVC
tagged_index
{
public:
    typedef boost::uint16_t tag_t;
    typedef boost::uint16_t index_t;

    /** uninitialized constructor */
    tagged_index(void) BOOST_NOEXCEPT //: index(0), tag(0)
    {}

    /** copy constructor */
#ifdef BOOST_NO_CXX11_DEFAULTED_FUNCTIONS
    tagged_index(tagged_index const & rhs):
        index(rhs.index), tag(rhs.tag)
    {}
#else
    tagged_index(tagged_index const & rhs) = default;
#endif

    explicit tagged_index(index_t i, tag_t t = 0):
        index(i), tag(t)
    {}

    /** index access */
    /* @{ */
    index_t get_index() const
    {
        return index;
    }

    void set_index(index_t i)
    {
        index = i;
    }
    /* @} */

    /** tag access */
    /* @{ */
    tag_t get_tag() const
    {
        return tag;
    }

    tag_t get_next_tag() const
    {
        tag_t next = (get_tag() + 1u) & (std::numeric_limits<tag_t>::max)();
        return next;
    }

    void set_tag(tag_t t)
    {
        tag = t;
    }
    /* @} */

    bool operator==(tagged_index const & rhs) const
    {
        return (index == rhs.index) && (tag == rhs.tag);
    }

    bool operator!=(tagged_index const & rhs) const
    {
        return !operator==(rhs);
    }

protected:
    index_t index;
    tag_t tag;
};

template <typename T,
          std::size_t size>
struct compiletime_sized_freelist_storage
{
    // array-based freelists only support a 16bit address space.
    BOOST_STATIC_ASSERT(size < 65536);

    boost::array<char, size * sizeof(T) + 64> data;

    // unused ... only for API purposes
    template <typename Allocator>
    compiletime_sized_freelist_storage(Allocator const & /* alloc */, std::size_t /* count */)
    {}

    T * nodes(void) const
    {
        char * data_pointer = const_cast<char*>(data.data());
        return reinterpret_cast<T*>( boost::alignment::align_up( data_pointer, BOOST_LOCKFREE_CACHELINE_BYTES ) );
    }

    std::size_t node_count(void) const
    {
        return size;
    }
};

template <typename T,
          typename Alloc = std::allocator<T> >
struct runtime_sized_freelist_storage:
    boost::alignment::aligned_allocator_adaptor<Alloc, BOOST_LOCKFREE_CACHELINE_BYTES >
{
    typedef boost::alignment::aligned_allocator_adaptor<Alloc, BOOST_LOCKFREE_CACHELINE_BYTES > allocator_type;
    T * nodes_;
    std::size_t node_count_;

    template <typename Allocator>
    runtime_sized_freelist_storage(Allocator const & alloc, std::size_t count):
        allocator_type(alloc), node_count_(count)
    {
        if (count > 65535)
            boost::throw_exception(std::runtime_error("boost.lockfree: freelist size is limited to a maximum of 65535 objects"));
        nodes_ = allocator_type::allocate(count);
    }

    ~runtime_sized_freelist_storage(void)
    {
        allocator_type::deallocate(nodes_, node_count_);
    }

    T * nodes(void) const
    {
        return nodes_;
    }

    std::size_t node_count(void) const
    {
        return node_count_;
    }
};


template <typename T,
          typename NodeStorage = runtime_sized_freelist_storage<T>
         >
class fixed_size_freelist:
    NodeStorage
{
    struct freelist_node
    {
        tagged_index next;
    };

    void initialize(void)
    {
        T * nodes = NodeStorage::nodes();
        for (std::size_t i = 0; i != NodeStorage::node_count(); ++i) {
            tagged_index * next_index = reinterpret_cast<tagged_index*>(nodes + i);
            next_index->set_index(null_handle());

#ifdef BOOST_LOCKFREE_FREELIST_INIT_RUNS_DTOR
            destruct<false>(nodes + i);
#else
            deallocate<false>(static_cast<index_t>(i));
#endif
        }
    }

public:
    typedef tagged_index tagged_node_handle;
    typedef tagged_index::index_t index_t;

    template <typename Allocator>
    fixed_size_freelist (Allocator const & alloc, std::size_t count):
        NodeStorage(alloc, count),
        pool_(tagged_index(static_cast<index_t>(count), 0))
    {
        initialize();
    }

    fixed_size_freelist (void):
        pool_(tagged_index(NodeStorage::node_count(), 0))
    {
        initialize();
    }

    template <bool ThreadSafe, bool Bounded>
    T * construct (void)
    {
        index_t node_index = allocate<ThreadSafe>();
        if (node_index == null_handle())
            return NULL;

        T * node = NodeStorage::nodes() + node_index;
        new(node) T();
        return node;
    }

    template <bool ThreadSafe, bool Bounded, typename ArgumentType>
    T * construct (ArgumentType const & arg)
    {
        index_t node_index = allocate<ThreadSafe>();
        if (node_index == null_handle())
            return NULL;

        T * node = NodeStorage::nodes() + node_index;
        new(node) T(arg);
        return node;
    }

    template <bool ThreadSafe, bool Bounded, typename ArgumentType1, typename ArgumentType2>
    T * construct (ArgumentType1 const & arg1, ArgumentType2 const & arg2)
    {
        index_t node_index = allocate<ThreadSafe>();
        if (node_index == null_handle())
            return NULL;

        T * node = NodeStorage::nodes() + node_index;
        new(node) T(arg1, arg2);
        return node;
    }

    template <bool ThreadSafe>
    void destruct (tagged_node_handle tagged_index)
    {
        index_t index = tagged_index.get_index();
        T * n = NodeStorage::nodes() + index;
        (void)n; // silence msvc warning
        n->~T();
        deallocate<ThreadSafe>(index);
    }

    template <bool ThreadSafe>
    void destruct (T * n)
    {
        n->~T();
        deallocate<ThreadSafe>(static_cast<index_t>(n - NodeStorage::nodes()));
    }

    bool is_lock_free(void) const
    {
        return pool_.is_lock_free();
    }

    index_t null_handle(void) const
    {
        return static_cast<index_t>(NodeStorage::node_count());
    }

    index_t get_handle(T * pointer) const
    {
        if (pointer == NULL)
            return null_handle();
        else
            return static_cast<index_t>(pointer - NodeStorage::nodes());
    }

    index_t get_handle(tagged_node_handle const & handle) const
    {
        return handle.get_index();
    }

    T * get_pointer(tagged_node_handle const & tptr) const
    {
        return get_pointer(tptr.get_index());
    }

    T * get_pointer(index_t index) const
    {
        if (index == null_handle())
            return 0;
        else
            return NodeStorage::nodes() + index;
    }

    T * get_pointer(T * ptr) const
    {
        return ptr;
    }

protected: // allow use from subclasses
    template <bool ThreadSafe>
    index_t allocate (void)
    {
        if (ThreadSafe)
            return allocate_impl();
        else
            return allocate_impl_unsafe();
    }

private:
    index_t allocate_impl (void)
    {
        tagged_index old_pool = pool_.load(memory_order_consume);

        for(;;) {
            index_t index = old_pool.get_index();
            if (index == null_handle())
                return index;

            T * old_node = NodeStorage::nodes() + index;
            tagged_index * next_index = reinterpret_cast<tagged_index*>(old_node);

            tagged_index new_pool(next_index->get_index(), old_pool.get_next_tag());

            if (pool_.compare_exchange_weak(old_pool, new_pool))
                return old_pool.get_index();
        }
    }

    index_t allocate_impl_unsafe (void)
    {
        tagged_index old_pool = pool_.load(memory_order_consume);

        index_t index = old_pool.get_index();
        if (index == null_handle())
            return index;

        T * old_node = NodeStorage::nodes() + index;
        tagged_index * next_index = reinterpret_cast<tagged_index*>(old_node);

        tagged_index new_pool(next_index->get_index(), old_pool.get_next_tag());

        pool_.store(new_pool, memory_order_relaxed);
        return old_pool.get_index();
    }

    template <bool ThreadSafe>
    void deallocate (index_t index)
    {
        if (ThreadSafe)
            deallocate_impl(index);
        else
            deallocate_impl_unsafe(index);
    }

    void deallocate_impl (index_t index)
    {
        freelist_node * new_pool_node = reinterpret_cast<freelist_node*>(NodeStorage::nodes() + index);
        tagged_index old_pool = pool_.load(memory_order_consume);

        for(;;) {
            tagged_index new_pool (index, old_pool.get_tag());
            new_pool_node->next.set_index(old_pool.get_index());

            if (pool_.compare_exchange_weak(old_pool, new_pool))
                return;
        }
    }

    void deallocate_impl_unsafe (index_t index)
    {
        freelist_node * new_pool_node = reinterpret_cast<freelist_node*>(NodeStorage::nodes() + index);
        tagged_index old_pool = pool_.load(memory_order_consume);

        tagged_index new_pool (index, old_pool.get_tag());
        new_pool_node->next.set_index(old_pool.get_index());

        pool_.store(new_pool);
    }

    atomic<tagged_index> pool_;
};

template <typename T,
          typename Alloc,
          bool IsCompileTimeSized,
          bool IsFixedSize,
          std::size_t Capacity
          >
struct select_freelist
{
    typedef typename mpl::if_c<IsCompileTimeSized,
                               compiletime_sized_freelist_storage<T, Capacity>,
                               runtime_sized_freelist_storage<T, Alloc>
                              >::type fixed_sized_storage_type;

    typedef typename mpl::if_c<IsCompileTimeSized || IsFixedSize,
                               fixed_size_freelist<T, fixed_sized_storage_type>,
                               freelist_stack<T, Alloc>
                              >::type type;
};

template <typename T, bool IsNodeBased>
struct select_tagged_handle
{
    typedef typename mpl::if_c<IsNodeBased,
                               tagged_ptr<T>,
                               tagged_index
                              >::type tagged_handle_type;

    typedef typename mpl::if_c<IsNodeBased,
                               T*,
                               typename tagged_index::index_t
                              >::type handle_type;
};


} /* namespace detail */
} /* namespace lockfree */
} /* namespace boost */

#if defined(_MSC_VER)
#pragma warning(pop)
#endif


#endif /* BOOST_LOCKFREE_FREELIST_HPP_INCLUDED */

/* freelist.hpp
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
*/