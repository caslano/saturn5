//  lock-free single-producer/single-consumer ringbuffer
//  this algorithm is implemented in various projects (linux kernel)
//
//  Copyright (C) 2009-2013 Tim Blechmann
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_LOCKFREE_SPSC_QUEUE_HPP_INCLUDED
#define BOOST_LOCKFREE_SPSC_QUEUE_HPP_INCLUDED

#include <algorithm>
#include <memory>

#include <boost/aligned_storage.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/utility.hpp>
#include <boost/next_prior.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/config.hpp> // for BOOST_LIKELY

#include <boost/type_traits/has_trivial_destructor.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/lockfree/detail/allocator_rebind_helper.hpp>
#include <boost/lockfree/detail/atomic.hpp>
#include <boost/lockfree/detail/copy_payload.hpp>
#include <boost/lockfree/detail/parameter.hpp>
#include <boost/lockfree/detail/prefix.hpp>

#include <boost/lockfree/lockfree_forward.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost    {
namespace lockfree {
namespace detail   {

typedef parameter::parameters<boost::parameter::optional<tag::capacity>,
                              boost::parameter::optional<tag::allocator>
                             > ringbuffer_signature;

template <typename T>
class ringbuffer_base
{
#ifndef BOOST_DOXYGEN_INVOKED
protected:
    typedef std::size_t size_t;
    static const int padding_size = BOOST_LOCKFREE_CACHELINE_BYTES - sizeof(size_t);
    atomic<size_t> write_index_;
    char padding1[padding_size]; /* force read_index and write_index to different cache lines */
    atomic<size_t> read_index_;

    BOOST_DELETED_FUNCTION(ringbuffer_base(ringbuffer_base const&))
    BOOST_DELETED_FUNCTION(ringbuffer_base& operator= (ringbuffer_base const&))

protected:
    ringbuffer_base(void):
        write_index_(0), read_index_(0)
    {}

    static size_t next_index(size_t arg, size_t max_size)
    {
        size_t ret = arg + 1;
        while (BOOST_UNLIKELY(ret >= max_size))
            ret -= max_size;
        return ret;
    }

    static size_t read_available(size_t write_index, size_t read_index, size_t max_size)
    {
        if (write_index >= read_index)
            return write_index - read_index;

        const size_t ret = write_index + max_size - read_index;
        return ret;
    }

    static size_t write_available(size_t write_index, size_t read_index, size_t max_size)
    {
        size_t ret = read_index - write_index - 1;
        if (write_index >= read_index)
            ret += max_size;
        return ret;
    }

    size_t read_available(size_t max_size) const
    {
        size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index  = read_index_.load(memory_order_relaxed);
        return read_available(write_index, read_index, max_size);
    }

    size_t write_available(size_t max_size) const
    {
        size_t write_index = write_index_.load(memory_order_relaxed);
        const size_t read_index  = read_index_.load(memory_order_acquire);
        return write_available(write_index, read_index, max_size);
    }

    bool push(T const & t, T * buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_relaxed);  // only written from push thread
        const size_t next = next_index(write_index, max_size);

        if (next == read_index_.load(memory_order_acquire))
            return false; /* ringbuffer is full */

        new (buffer + write_index) T(t); // copy-construct

        write_index_.store(next, memory_order_release);

        return true;
    }

    size_t push(const T * input_buffer, size_t input_count, T * internal_buffer, size_t max_size)
    {
        return push(input_buffer, input_buffer + input_count, internal_buffer, max_size) - input_buffer;
    }

    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end, T * internal_buffer, size_t max_size)
    {
        // FIXME: avoid std::distance

        const size_t write_index = write_index_.load(memory_order_relaxed);  // only written from push thread
        const size_t read_index  = read_index_.load(memory_order_acquire);
        const size_t avail = write_available(write_index, read_index, max_size);

        if (avail == 0)
            return begin;

        size_t input_count = std::distance(begin, end);
        input_count = (std::min)(input_count, avail);

        size_t new_write_index = write_index + input_count;

        const ConstIterator last = boost::next(begin, input_count);

        if (write_index + input_count > max_size) {
            /* copy data in two sections */
            const size_t count0 = max_size - write_index;
            const ConstIterator midpoint = boost::next(begin, count0);

            std::uninitialized_copy(begin, midpoint, internal_buffer + write_index);
            std::uninitialized_copy(midpoint, last, internal_buffer);
            new_write_index -= max_size;
        } else {
            std::uninitialized_copy(begin, last, internal_buffer + write_index);

            if (new_write_index == max_size)
                new_write_index = 0;
        }

        write_index_.store(new_write_index, memory_order_release);
        return last;
    }

    template <typename Functor>
    bool consume_one(Functor & functor, T * buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index  = read_index_.load(memory_order_relaxed); // only written from pop thread
        if ( empty(write_index, read_index) )
            return false;

        T & object_to_consume = buffer[read_index];
        functor( object_to_consume );
        object_to_consume.~T();

        size_t next = next_index(read_index, max_size);
        read_index_.store(next, memory_order_release);
        return true;
    }

    template <typename Functor>
    bool consume_one(Functor const & functor, T * buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index  = read_index_.load(memory_order_relaxed); // only written from pop thread
        if ( empty(write_index, read_index) )
            return false;

        T & object_to_consume = buffer[read_index];
        functor( object_to_consume );
        object_to_consume.~T();

        size_t next = next_index(read_index, max_size);
        read_index_.store(next, memory_order_release);
        return true;
    }

    template <typename Functor>
    size_t consume_all (Functor const & functor, T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);

        if (avail == 0)
            return 0;

        const size_t output_count = avail;

        size_t new_read_index = read_index + output_count;

        if (read_index + output_count > max_size) {
            /* copy data in two sections */
            const size_t count0 = max_size - read_index;
            const size_t count1 = output_count - count0;

            run_functor_and_delete(internal_buffer + read_index, internal_buffer + max_size, functor);
            run_functor_and_delete(internal_buffer, internal_buffer + count1, functor);

            new_read_index -= max_size;
        } else {
            run_functor_and_delete(internal_buffer + read_index, internal_buffer + read_index + output_count, functor);

            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return output_count;
    }

    template <typename Functor>
    size_t consume_all (Functor & functor, T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);

        if (avail == 0)
            return 0;

        const size_t output_count = avail;

        size_t new_read_index = read_index + output_count;

        if (read_index + output_count > max_size) {
            /* copy data in two sections */
            const size_t count0 = max_size - read_index;
            const size_t count1 = output_count - count0;

            run_functor_and_delete(internal_buffer + read_index, internal_buffer + max_size, functor);
            run_functor_and_delete(internal_buffer, internal_buffer + count1, functor);

            new_read_index -= max_size;
        } else {
            run_functor_and_delete(internal_buffer + read_index, internal_buffer + read_index + output_count, functor);

            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return output_count;
    }

    size_t pop (T * output_buffer, size_t output_count, T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);

        if (avail == 0)
            return 0;

        output_count = (std::min)(output_count, avail);

        size_t new_read_index = read_index + output_count;

        if (read_index + output_count > max_size) {
            /* copy data in two sections */
            const size_t count0 = max_size - read_index;
            const size_t count1 = output_count - count0;

            copy_and_delete(internal_buffer + read_index, internal_buffer + max_size, output_buffer);
            copy_and_delete(internal_buffer, internal_buffer + count1, output_buffer + count0);

            new_read_index -= max_size;
        } else {
            copy_and_delete(internal_buffer + read_index, internal_buffer + read_index + output_count, output_buffer);
            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return output_count;
    }

    template <typename OutputIterator>
    size_t pop_to_output_iterator (OutputIterator it, T * internal_buffer, size_t max_size)
    {
        const size_t write_index = write_index_.load(memory_order_acquire);
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread

        const size_t avail = read_available(write_index, read_index, max_size);
        if (avail == 0)
            return 0;

        size_t new_read_index = read_index + avail;

        if (read_index + avail > max_size) {
            /* copy data in two sections */
            const size_t count0 = max_size - read_index;
            const size_t count1 = avail - count0;

            it = copy_and_delete(internal_buffer + read_index, internal_buffer + max_size, it);
            copy_and_delete(internal_buffer, internal_buffer + count1, it);

            new_read_index -= max_size;
        } else {
            copy_and_delete(internal_buffer + read_index, internal_buffer + read_index + avail, it);
            if (new_read_index == max_size)
                new_read_index = 0;
        }

        read_index_.store(new_read_index, memory_order_release);
        return avail;
    }

    const T& front(const T * internal_buffer) const
    {
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread
        return *(internal_buffer + read_index);
    }

    T& front(T * internal_buffer)
    {
        const size_t read_index = read_index_.load(memory_order_relaxed); // only written from pop thread
        return *(internal_buffer + read_index);
    }
#endif


public:
    /** reset the ringbuffer
     *
     * \note Not thread-safe
     * */
    void reset(void)
    {
        if ( !boost::has_trivial_destructor<T>::value ) {
            // make sure to call all destructors!

            T dummy_element;
            while (pop(dummy_element))
            {}
        } else {
            write_index_.store(0, memory_order_relaxed);
            read_index_.store(0, memory_order_release);
        }
    }

    /** Check if the ringbuffer is empty
     *
     * \return true, if the ringbuffer is empty, false otherwise
     * \note Due to the concurrent nature of the ringbuffer the result may be inaccurate.
     * */
    bool empty(void)
    {
        return empty(write_index_.load(memory_order_relaxed), read_index_.load(memory_order_relaxed));
    }

    /**
     * \return true, if implementation is lock-free.
     *
     * */
    bool is_lock_free(void) const
    {
        return write_index_.is_lock_free() && read_index_.is_lock_free();
    }

private:
    bool empty(size_t write_index, size_t read_index)
    {
        return write_index == read_index;
    }

    template< class OutputIterator >
    OutputIterator copy_and_delete( T * first, T * last, OutputIterator out )
    {
        if (boost::has_trivial_destructor<T>::value) {
            return std::copy(first, last, out); // will use memcpy if possible
        } else {
            for (; first != last; ++first, ++out) {
                *out = *first;
                first->~T();
            }
            return out;
        }
    }

    template< class Functor >
    void run_functor_and_delete( T * first, T * last, Functor & functor )
    {
        for (; first != last; ++first) {
            functor(*first);
            first->~T();
        }
    }

    template< class Functor >
    void run_functor_and_delete( T * first, T * last, Functor const & functor )
    {
        for (; first != last; ++first) {
            functor(*first);
            first->~T();
        }
    }
};

template <typename T, std::size_t MaxSize>
class compile_time_sized_ringbuffer:
    public ringbuffer_base<T>
{
    typedef std::size_t size_type;
    static const std::size_t max_size = MaxSize + 1;

    typedef typename boost::aligned_storage<max_size * sizeof(T),
                                            boost::alignment_of<T>::value
                                           >::type storage_type;

    storage_type storage_;

    T * data()
    {
        return static_cast<T*>(storage_.address());
    }

    const T * data() const
    {
        return static_cast<const T*>(storage_.address());
    }

protected:
    size_type max_number_of_elements() const
    {
        return max_size;
    }

public:
    bool push(T const & t)
    {
        return ringbuffer_base<T>::push(t, data(), max_size);
    }

    template <typename Functor>
    bool consume_one(Functor & f)
    {
        return ringbuffer_base<T>::consume_one(f, data(), max_size);
    }

    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        return ringbuffer_base<T>::consume_one(f, data(), max_size);
    }

    template <typename Functor>
    size_type consume_all(Functor & f)
    {
        return ringbuffer_base<T>::consume_all(f, data(), max_size);
    }

    template <typename Functor>
    size_type consume_all(Functor const & f)
    {
        return ringbuffer_base<T>::consume_all(f, data(), max_size);
    }

    size_type push(T const * t, size_type size)
    {
        return ringbuffer_base<T>::push(t, size, data(), max_size);
    }

    template <size_type size>
    size_type push(T const (&t)[size])
    {
        return push(t, size);
    }

    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return ringbuffer_base<T>::push(begin, end, data(), max_size);
    }

    size_type pop(T * ret, size_type size)
    {
        return ringbuffer_base<T>::pop(ret, size, data(), max_size);
    }

    template <typename OutputIterator>
    size_type pop_to_output_iterator(OutputIterator it)
    {
        return ringbuffer_base<T>::pop_to_output_iterator(it, data(), max_size);
    }

    const T& front(void) const
    {
        return ringbuffer_base<T>::front(data());
    }

    T& front(void)
    {
        return ringbuffer_base<T>::front(data());
    }
};

template <typename T, typename Alloc>
class runtime_sized_ringbuffer:
    public ringbuffer_base<T>,
    private Alloc
{
    typedef std::size_t size_type;
    size_type max_elements_;
#ifdef BOOST_NO_CXX11_ALLOCATOR
    typedef typename Alloc::pointer pointer;
#else
    typedef std::allocator_traits<Alloc> allocator_traits;
    typedef typename allocator_traits::pointer pointer;
#endif
    pointer array_;

protected:
    size_type max_number_of_elements() const
    {
        return max_elements_;
    }

public:
    explicit runtime_sized_ringbuffer(size_type max_elements):
        max_elements_(max_elements + 1)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        array_ = Alloc::allocate(max_elements_);
#else
        Alloc& alloc = *this;
        array_ = allocator_traits::allocate(alloc, max_elements_);
#endif
    }

    template <typename U>
    runtime_sized_ringbuffer(typename detail::allocator_rebind_helper<Alloc, U>::type const & alloc, size_type max_elements):
        Alloc(alloc), max_elements_(max_elements + 1)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        array_ = Alloc::allocate(max_elements_);
#else
        Alloc& allocator = *this;
        array_ = allocator_traits::allocate(allocator, max_elements_);
#endif
    }

    runtime_sized_ringbuffer(Alloc const & alloc, size_type max_elements):
        Alloc(alloc), max_elements_(max_elements + 1)
    {
#ifdef BOOST_NO_CXX11_ALLOCATOR
        array_ = Alloc::allocate(max_elements_);
#else
        Alloc& allocator = *this;
        array_ = allocator_traits::allocate(allocator, max_elements_);
#endif
    }

    ~runtime_sized_ringbuffer(void)
    {
        // destroy all remaining items
        T out;
        while (pop(&out, 1)) {}

#ifdef BOOST_NO_CXX11_ALLOCATOR
        Alloc::deallocate(array_, max_elements_);
#else
        Alloc& allocator = *this;
        allocator_traits::deallocate(allocator, array_, max_elements_);
#endif
    }

    bool push(T const & t)
    {
        return ringbuffer_base<T>::push(t, &*array_, max_elements_);
    }

    template <typename Functor>
    bool consume_one(Functor & f)
    {
        return ringbuffer_base<T>::consume_one(f, &*array_, max_elements_);
    }

    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        return ringbuffer_base<T>::consume_one(f, &*array_, max_elements_);
    }

    template <typename Functor>
    size_type consume_all(Functor & f)
    {
        return ringbuffer_base<T>::consume_all(f, &*array_, max_elements_);
    }

    template <typename Functor>
    size_type consume_all(Functor const & f)
    {
        return ringbuffer_base<T>::consume_all(f, &*array_, max_elements_);
    }

    size_type push(T const * t, size_type size)
    {
        return ringbuffer_base<T>::push(t, size, &*array_, max_elements_);
    }

    template <size_type size>
    size_type push(T const (&t)[size])
    {
        return push(t, size);
    }

    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return ringbuffer_base<T>::push(begin, end, &*array_, max_elements_);
    }

    size_type pop(T * ret, size_type size)
    {
        return ringbuffer_base<T>::pop(ret, size, &*array_, max_elements_);
    }

    template <typename OutputIterator>
    size_type pop_to_output_iterator(OutputIterator it)
    {
        return ringbuffer_base<T>::pop_to_output_iterator(it, &*array_, max_elements_);
    }

    const T& front(void) const
    {
        return ringbuffer_base<T>::front(&*array_);
    }

    T& front(void)
    {
        return ringbuffer_base<T>::front(&*array_);
    }
};

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T, typename A0, typename A1>
#else
template <typename T, typename ...Options>
#endif
struct make_ringbuffer
{
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    typedef typename ringbuffer_signature::bind<A0, A1>::type bound_args;
#else
    typedef typename ringbuffer_signature::bind<Options...>::type bound_args;
#endif

    typedef extract_capacity<bound_args> extract_capacity_t;

    static const bool runtime_sized = !extract_capacity_t::has_capacity;
    static const size_t capacity    =  extract_capacity_t::capacity;

    typedef extract_allocator<bound_args, T> extract_allocator_t;
    typedef typename extract_allocator_t::type allocator;

    // allocator argument is only sane, for run-time sized ringbuffers
    BOOST_STATIC_ASSERT((mpl::if_<mpl::bool_<!runtime_sized>,
                                  mpl::bool_<!extract_allocator_t::has_allocator>,
                                  mpl::true_
                                 >::type::value));

    typedef typename mpl::if_c<runtime_sized,
                               runtime_sized_ringbuffer<T, allocator>,
                               compile_time_sized_ringbuffer<T, capacity>
                              >::type ringbuffer_type;
};


} /* namespace detail */


/** The spsc_queue class provides a single-writer/single-reader fifo queue, pushing and popping is wait-free.
 *
 *  \b Policies:
 *  - \c boost::lockfree::capacity<>, optional <br>
 *    If this template argument is passed to the options, the size of the ringbuffer is set at compile-time.
 *
 *  - \c boost::lockfree::allocator<>, defaults to \c boost::lockfree::allocator<std::allocator<T>> <br>
 *    Specifies the allocator that is used to allocate the ringbuffer. This option is only valid, if the ringbuffer is configured
 *    to be sized at run-time
 *
 *  \b Requirements:
 *  - T must have a default constructor
 *  - T must be copyable
 * */
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
template <typename T, class A0, class A1>
#else
template <typename T, typename ...Options>
#endif
class spsc_queue:
#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    public detail::make_ringbuffer<T, A0, A1>::ringbuffer_type
#else
    public detail::make_ringbuffer<T, Options...>::ringbuffer_type
#endif
{
private:

#ifndef BOOST_DOXYGEN_INVOKED

#ifdef BOOST_NO_CXX11_VARIADIC_TEMPLATES
    typedef typename detail::make_ringbuffer<T, A0, A1>::ringbuffer_type base_type;
    static const bool runtime_sized = detail::make_ringbuffer<T, A0, A1>::runtime_sized;
    typedef typename detail::make_ringbuffer<T, A0, A1>::allocator allocator_arg;
#else
    typedef typename detail::make_ringbuffer<T, Options...>::ringbuffer_type base_type;
    static const bool runtime_sized = detail::make_ringbuffer<T, Options...>::runtime_sized;
    typedef typename detail::make_ringbuffer<T, Options...>::allocator allocator_arg;
#endif


    struct implementation_defined
    {
        typedef allocator_arg allocator;
        typedef std::size_t size_type;
    };
#endif

public:
    typedef T value_type;
    typedef typename implementation_defined::allocator allocator;
    typedef typename implementation_defined::size_type size_type;

    /** Constructs a spsc_queue
     *
     *  \pre spsc_queue must be configured to be sized at compile-time
     */
    // @{
    spsc_queue(void)
    {
        BOOST_ASSERT(!runtime_sized);
    }

    template <typename U>
    explicit spsc_queue(typename detail::allocator_rebind_helper<allocator, U>::type const &)
    {
        // just for API compatibility: we don't actually need an allocator
        BOOST_STATIC_ASSERT(!runtime_sized);
    }

    explicit spsc_queue(allocator const &)
    {
        // just for API compatibility: we don't actually need an allocator
        BOOST_ASSERT(!runtime_sized);
    }
    // @}


    /** Constructs a spsc_queue for element_count elements
     *
     *  \pre spsc_queue must be configured to be sized at run-time
     */
    // @{
    explicit spsc_queue(size_type element_count):
        base_type(element_count)
    {
        BOOST_ASSERT(runtime_sized);
    }

    template <typename U>
    spsc_queue(size_type element_count, typename detail::allocator_rebind_helper<allocator, U>::type const & alloc):
        base_type(alloc, element_count)
    {
        BOOST_STATIC_ASSERT(runtime_sized);
    }

    spsc_queue(size_type element_count, allocator_arg const & alloc):
        base_type(alloc, element_count)
    {
        BOOST_ASSERT(runtime_sized);
    }
    // @}

    /** Pushes object t to the ringbuffer.
     *
     * \pre only one thread is allowed to push data to the spsc_queue
     * \post object will be pushed to the spsc_queue, unless it is full.
     * \return true, if the push operation is successful.
     *
     * \note Thread-safe and wait-free
     * */
    bool push(T const & t)
    {
        return base_type::push(t);
    }

    /** Pops one object from ringbuffer.
     *
     * \pre only one thread is allowed to pop data to the spsc_queue
     * \post if ringbuffer is not empty, object will be discarded.
     * \return true, if the pop operation is successful, false if ringbuffer was empty.
     *
     * \note Thread-safe and wait-free
     */
    bool pop ()
    {
        detail::consume_noop consume_functor;
        return consume_one( consume_functor );
    }

    /** Pops one object from ringbuffer.
     *
     * \pre only one thread is allowed to pop data to the spsc_queue
     * \post if ringbuffer is not empty, object will be copied to ret.
     * \return true, if the pop operation is successful, false if ringbuffer was empty.
     *
     * \note Thread-safe and wait-free
     */
    template <typename U>
    typename boost::enable_if<typename is_convertible<T, U>::type, bool>::type
    pop (U & ret)
    {
        detail::consume_via_copy<U> consume_functor(ret);
        return consume_one( consume_functor );
    }

    /** Pushes as many objects from the array t as there is space.
     *
     * \pre only one thread is allowed to push data to the spsc_queue
     * \return number of pushed items
     *
     * \note Thread-safe and wait-free
     */
    size_type push(T const * t, size_type size)
    {
        return base_type::push(t, size);
    }

    /** Pushes as many objects from the array t as there is space available.
     *
     * \pre only one thread is allowed to push data to the spsc_queue
     * \return number of pushed items
     *
     * \note Thread-safe and wait-free
     */
    template <size_type size>
    size_type push(T const (&t)[size])
    {
        return push(t, size);
    }

    /** Pushes as many objects from the range [begin, end) as there is space .
     *
     * \pre only one thread is allowed to push data to the spsc_queue
     * \return iterator to the first element, which has not been pushed
     *
     * \note Thread-safe and wait-free
     */
    template <typename ConstIterator>
    ConstIterator push(ConstIterator begin, ConstIterator end)
    {
        return base_type::push(begin, end);
    }

    /** Pops a maximum of size objects from ringbuffer.
     *
     * \pre only one thread is allowed to pop data to the spsc_queue
     * \return number of popped items
     *
     * \note Thread-safe and wait-free
     * */
    size_type pop(T * ret, size_type size)
    {
        return base_type::pop(ret, size);
    }

    /** Pops a maximum of size objects from spsc_queue.
     *
     * \pre only one thread is allowed to pop data to the spsc_queue
     * \return number of popped items
     *
     * \note Thread-safe and wait-free
     * */
    template <size_type size>
    size_type pop(T (&ret)[size])
    {
        return pop(ret, size);
    }

    /** Pops objects to the output iterator it
     *
     * \pre only one thread is allowed to pop data to the spsc_queue
     * \return number of popped items
     *
     * \note Thread-safe and wait-free
     * */
    template <typename OutputIterator>
    typename boost::disable_if<typename is_convertible<T, OutputIterator>::type, size_type>::type
    pop(OutputIterator it)
    {
        return base_type::pop_to_output_iterator(it);
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
        return base_type::consume_one(f);
    }

    /// \copydoc boost::lockfree::spsc_queue::consume_one(Functor & rhs)
    template <typename Functor>
    bool consume_one(Functor const & f)
    {
        return base_type::consume_one(f);
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
    size_type consume_all(Functor & f)
    {
        return base_type::consume_all(f);
    }

    /// \copydoc boost::lockfree::spsc_queue::consume_all(Functor & rhs)
    template <typename Functor>
    size_type consume_all(Functor const & f)
    {
        return base_type::consume_all(f);
    }

    /** get number of elements that are available for read
     *
     * \return number of available elements that can be popped from the spsc_queue
     *
     * \note Thread-safe and wait-free, should only be called from the consumer thread
     * */
    size_type read_available() const
    {
        return base_type::read_available(base_type::max_number_of_elements());
    }

    /** get write space to write elements
     *
     * \return number of elements that can be pushed to the spsc_queue
     *
     * \note Thread-safe and wait-free, should only be called from the producer thread
     * */
    size_type write_available() const
    {
        return base_type::write_available(base_type::max_number_of_elements());
    }

    /** get reference to element in the front of the queue
     *
     * Availability of front element can be checked using read_available().
     *
     * \pre only a consuming thread is allowed to check front element
     * \pre read_available() > 0. If ringbuffer is empty, it's undefined behaviour to invoke this method.
     * \return reference to the first element in the queue
     *
     * \note Thread-safe and wait-free
     */
    const T& front() const
    {
        BOOST_ASSERT(read_available() > 0);
        return base_type::front();
    }

    /// \copydoc boost::lockfree::spsc_queue::front() const
    T& front()
    {
        BOOST_ASSERT(read_available() > 0);
        return base_type::front();
    }

    /** reset the ringbuffer
     *
     * \note Not thread-safe
     * */
    void reset(void)
    {
        if ( !boost::has_trivial_destructor<T>::value ) {
            // make sure to call all destructors!

            T dummy_element;
            while (pop(dummy_element))
            {}
        } else {
            base_type::write_index_.store(0, memory_order_relaxed);
            base_type::read_index_.store(0, memory_order_release);
        }
   }
};

} /* namespace lockfree */
} /* namespace boost */


#endif /* BOOST_LOCKFREE_SPSC_QUEUE_HPP_INCLUDED */

/* spsc_queue.hpp
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
*/