// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_DETAIL_ANY_ITERATOR_BUFFER_HPP_INCLUDED
#define BOOST_RANGE_DETAIL_ANY_ITERATOR_BUFFER_HPP_INCLUDED

#include <boost/array.hpp>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>
#include <boost/noncopyable.hpp>

namespace boost
{
    template<std::size_t StackBufferSize>
    class any_iterator_buffer
        : noncopyable
    {
        BOOST_STATIC_ASSERT(( StackBufferSize > 0 ));
    public:
        any_iterator_buffer()
            : m_ptr()
        {
        }

        ~any_iterator_buffer()
        {
            delete [] m_ptr;
        }

        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( !m_ptr );
            if (bytes <= StackBufferSize)
                return m_buffer.data();

            m_ptr = new char[bytes];
            return m_ptr;
        }

        void deallocate()
        {
            delete [] m_ptr;
            m_ptr = 0;
        }

    private:
        // Rationale:
        // Do not use inheritance from noncopyable because this causes
        // the concepts to erroneous detect the derived any_iterator
        // as noncopyable.
        any_iterator_buffer(const any_iterator_buffer&);
        void operator=(const any_iterator_buffer&);

        char* m_ptr;
        boost::array<char, StackBufferSize> m_buffer;
    };

    class any_iterator_heap_only_buffer
        : noncopyable
    {
    public:
        any_iterator_heap_only_buffer()
            : m_ptr()
        {
        }

        ~any_iterator_heap_only_buffer()
        {
            delete [] m_ptr;
        }

        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( !m_ptr );
            m_ptr = new char[bytes];
            return m_ptr;
        }

        void deallocate()
        {
            delete [] m_ptr;
            m_ptr = 0;
        }

    private:
        char* m_ptr;
    };

    template<std::size_t StackBufferSize>
    class any_iterator_stack_only_buffer
    {
        BOOST_STATIC_ASSERT(( StackBufferSize > 0 ));
    public:
        void* allocate(std::size_t bytes)
        {
            BOOST_ASSERT( bytes <= m_buffer.size() );
            return m_buffer.data();
        }

        void deallocate()
        {
        }

    private:
        boost::array<char, StackBufferSize> m_buffer;
    };

    typedef any_iterator_buffer<64> any_iterator_default_buffer;
} // namespace boost

#endif // include guard

/* any_iterator_buffer.hpp
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
*/