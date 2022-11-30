//  lock-free freelist
//
//  Copyright (C) 2008-2016 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_FREELIST_HPP_INCLUDED
#define BOOST_LOCKFREE_FREELIST_HPP_INCLUDED

#include <cstring>
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
            std::memset((void*)node, 0, sizeof(T));
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
            std::memset((void*)node, 0, sizeof(T));
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
                if (!Bounded) {
                    T *ptr = Alloc::allocate(1);
                    std::memset((void*)ptr, 0, sizeof(T));
                    return ptr;
                }
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
            if (!Bounded) {
                T *ptr = Alloc::allocate(1);
                std::memset((void*)ptr, 0, sizeof(T));
                return ptr;
            }
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
struct BOOST_ALIGNMENT(BOOST_LOCKFREE_CACHELINE_BYTES) compiletime_sized_freelist_storage
{
    // array-based freelists only support a 16bit address space.
    BOOST_STATIC_ASSERT(size < 65536);

    boost::array<char, size * sizeof(T) + 64> data;

    // unused ... only for API purposes
    template <typename Allocator>
    compiletime_sized_freelist_storage(Allocator const & /* alloc */, std::size_t /* count */)
    {
        data.fill(0);
    }

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
        std::memset((void*)nodes_, 0, sizeof(T) * count);
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