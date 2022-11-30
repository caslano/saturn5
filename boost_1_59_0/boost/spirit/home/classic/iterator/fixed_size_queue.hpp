/*=============================================================================
    Copyright (c) 2001, Daniel C. Nuffer
    Copyright (c) 2003, Hartmut Kaiser
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#ifndef BOOST_SPIRIT_CLASSIC_ITERATOR_FIXED_SIZE_QUEUE_HPP
#define BOOST_SPIRIT_CLASSIC_ITERATOR_FIXED_SIZE_QUEUE_HPP

#include <cstddef>
#include <cstdlib>
#include <iterator>

#include <boost/spirit/home/classic/namespace.hpp>
#include <boost/spirit/home/classic/core/assert.hpp> // for BOOST_SPIRIT_ASSERT

// FIXES for broken compilers
#include <boost/config.hpp>
#include <boost/iterator_adaptors.hpp>

#define BOOST_SPIRIT_ASSERT_FSQ_SIZE \
    BOOST_SPIRIT_ASSERT(((m_tail + N + 1) - m_head) % (N+1) == m_size % (N+1)) \
    /**/

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

///////////////////////////////////////////////////////////////////////////////
namespace impl {

#if !defined(BOOST_ITERATOR_ADAPTORS_VERSION) || \
    BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200
#error "Please use at least Boost V1.31.0 while compiling the fixed_size_queue class!"
#else // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

template <typename QueueT, typename T, typename PointerT>
class fsq_iterator
:   public boost::iterator_adaptor<
        fsq_iterator<QueueT, T, PointerT>, 
        PointerT,
        T,
        std::random_access_iterator_tag
    >
{
public:
    typedef typename QueueT::position_t position;
    typedef boost::iterator_adaptor<
            fsq_iterator<QueueT, T, PointerT>, PointerT, T,
            std::random_access_iterator_tag
        > base_t;

    fsq_iterator() {}
    fsq_iterator(position const &p_) : p(p_) {}
    
    position const &get_position() const { return p; }
    
private:
    friend class boost::iterator_core_access;
    
    typename base_t::reference dereference() const
    {
        return p.self->m_queue[p.pos];
    }

    void increment()
    {
        ++p.pos;
        if (p.pos == QueueT::MAX_SIZE+1)
            p.pos = 0;
    }

    void decrement()
    {
        if (p.pos == 0)
            p.pos = QueueT::MAX_SIZE;
        else
            --p.pos;
    }

    template <
        typename OtherDerivedT, typename OtherIteratorT, 
        typename V, typename C, typename R, typename D
    >   
    bool equal(iterator_adaptor<OtherDerivedT, OtherIteratorT, V, C, R, D> 
        const &x) const
    {
        position const &rhs_pos = 
            static_cast<OtherDerivedT const &>(x).get_position();
        return (p.self == rhs_pos.self) && (p.pos == rhs_pos.pos);
    }

    template <
        typename OtherDerivedT, typename OtherIteratorT, 
        typename V, typename C, typename R, typename D
    >   
    typename base_t::difference_type distance_to(
        iterator_adaptor<OtherDerivedT, OtherIteratorT, V, C, R, D> 
        const &x) const
    {
        typedef typename base_t::difference_type diff_t;

        position const &p2 = 
            static_cast<OtherDerivedT const &>(x).get_position();
        std::size_t pos1 = p.pos;
        std::size_t pos2 = p2.pos;

        // Undefined behaviour if the iterators come from different
        //  containers
        BOOST_SPIRIT_ASSERT(p.self == p2.self);

        if (pos1 < p.self->m_head)
            pos1 += QueueT::MAX_SIZE;
        if (pos2 < p2.self->m_head)
            pos2 += QueueT::MAX_SIZE;

        if (pos2 > pos1)
            return diff_t(pos2 - pos1);
        else
            return -diff_t(pos1 - pos2);
    }

    void advance(typename base_t::difference_type n)
    {
        // Notice that we don't care values of n that can
        //  wrap around more than one time, since it would
        //  be undefined behaviour anyway (going outside
        //  the begin/end range). Negative wrapping is a bit
        //  cumbersome because we don't want to case p.pos
        //  to signed.
        if (n < 0)
        {
            n = -n;
            if (p.pos < (std::size_t)n)
                p.pos = QueueT::MAX_SIZE+1 - (n - p.pos);
            else
                p.pos -= n;
        }
        else
        {
            p.pos += n;
            if (p.pos >= QueueT::MAX_SIZE+1)
                p.pos -= QueueT::MAX_SIZE+1;
        }
    }
    
private:
    position p;
};

#endif // BOOST_ITERATOR_ADAPTORS_VERSION < 0x0200

///////////////////////////////////////////////////////////////////////////////
} /* namespace impl */

template <typename T, std::size_t N>
class fixed_size_queue
{
private:
    struct position
    {
        fixed_size_queue* self;
        std::size_t pos;

        position() : self(0), pos(0) {}

        // The const_cast here is just to avoid to have two different
        //  position structures for the const and non-const case.
        // The const semantic is guaranteed by the iterator itself
        position(const fixed_size_queue* s, std::size_t p)
            : self(const_cast<fixed_size_queue*>(s)), pos(p)
        {}
    };

public:
    // Declare the iterators
    typedef impl::fsq_iterator<fixed_size_queue<T, N>, T, T*> iterator;
    typedef impl::fsq_iterator<fixed_size_queue<T, N>, T const, T const*> 
        const_iterator;
    typedef position position_t;

    friend class impl::fsq_iterator<fixed_size_queue<T, N>, T, T*>;
    friend class impl::fsq_iterator<fixed_size_queue<T, N>, T const, T const*>;
    
    fixed_size_queue();
    fixed_size_queue(const fixed_size_queue& x);
    fixed_size_queue& operator=(const fixed_size_queue& x);
    ~fixed_size_queue();

    void push_back(const T& e);
    void push_front(const T& e);
    void serve(T& e);
    void pop_front();

    bool empty() const
    {
        return m_size == 0;
    }

    bool full() const
    {
        return m_size == N;
    }

    iterator begin()
    {
        return iterator(position(this, m_head));
    }

    const_iterator begin() const
    {
        return const_iterator(position(this, m_head));
    }

    iterator end()
    {
        return iterator(position(this, m_tail));
    }

    const_iterator end() const
    {
        return const_iterator(position(this, m_tail));
    }

    std::size_t size() const
    {
        return m_size;
    }

    T& front()
    {
        return m_queue[m_head];
    }

    const T& front() const
    {
        return m_queue[m_head];
    }

private:
    // Redefine the template parameters to avoid using partial template
    //  specialization on the iterator policy to extract N.
    BOOST_STATIC_CONSTANT(std::size_t, MAX_SIZE = N);

    std::size_t m_head;
    std::size_t m_tail;
    std::size_t m_size;
    T m_queue[N+1];
};

template <typename T, std::size_t N>
inline
fixed_size_queue<T, N>::fixed_size_queue()
    : m_head(0)
    , m_tail(0)
    , m_size(0)
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}

template <typename T, std::size_t N>
inline
fixed_size_queue<T, N>::fixed_size_queue(const fixed_size_queue& x)
    : m_head(x.m_head)
    , m_tail(x.m_tail)
    , m_size(x.m_size)
{
    copy(x.begin(), x.end(), begin());
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}

template <typename T, std::size_t N>
inline fixed_size_queue<T, N>&
fixed_size_queue<T, N>::operator=(const fixed_size_queue& x)
{
    if (this != &x)
    {
        m_head = x.m_head;
        m_tail = x.m_tail;
        m_size = x.m_size;
        copy(x.begin(), x.end(), begin());
    }
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);

    return *this;
}

template <typename T, std::size_t N>
inline
fixed_size_queue<T, N>::~fixed_size_queue()
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}

template <typename T, std::size_t N>
inline void
fixed_size_queue<T, N>::push_back(const T& e)
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);

    BOOST_SPIRIT_ASSERT(!full());

    m_queue[m_tail] = e;
    ++m_size;
    ++m_tail;
    if (m_tail == N+1)
        m_tail = 0;


    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}

template <typename T, std::size_t N>
inline void
fixed_size_queue<T, N>::push_front(const T& e)
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);

    BOOST_SPIRIT_ASSERT(!full());

    if (m_head == 0)
        m_head = N;
    else
        --m_head;

    m_queue[m_head] = e;
    ++m_size;

    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}


template <typename T, std::size_t N>
inline void
fixed_size_queue<T, N>::serve(T& e)
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);

    e = m_queue[m_head];
    pop_front();
}



template <typename T, std::size_t N>
inline void
fixed_size_queue<T, N>::pop_front()
{
    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);

    ++m_head;
    if (m_head == N+1)
        m_head = 0;
    --m_size;

    BOOST_SPIRIT_ASSERT(m_size <= N+1);
    BOOST_SPIRIT_ASSERT_FSQ_SIZE;
    BOOST_SPIRIT_ASSERT(m_head <= N+1);
    BOOST_SPIRIT_ASSERT(m_tail <= N+1);
}

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#undef BOOST_SPIRIT_ASSERT_FSQ_SIZE

#endif

/* fixed_size_queue.hpp
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
*/