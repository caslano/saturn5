// Boost.Range library
//
//  Copyright Neil Groves 2010. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_IRANGE_HPP_INCLUDED
#define BOOST_RANGE_IRANGE_HPP_INCLUDED

#include <boost/assert.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/range/iterator_range.hpp>

namespace boost
{
    namespace range_detail
    {
        // integer_iterator is an iterator over an integer sequence that
        // is bounded only by the limits of the underlying integer
        // representation.
        //
        // This is useful for implementing the irange(first, last)
        // function.
        //
        // Note:
        // This use of this iterator and irange is appreciably less
        // performant than the corresponding hand-written integer
        // loop on many compilers.
        template<typename Integer>
        class integer_iterator
            : public boost::iterator_facade<
                        integer_iterator<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    >
        {
            typedef boost::iterator_facade<
                        integer_iterator<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    > base_t;
        public:
            typedef typename base_t::value_type value_type;
            typedef typename base_t::difference_type difference_type;
            typedef typename base_t::reference reference;
            typedef std::random_access_iterator_tag iterator_category;

            integer_iterator() : m_value() {}
            explicit integer_iterator(value_type x) : m_value(x) {}

        private:
            void increment()
            {
                ++m_value;
            }

            void decrement()
            {
                --m_value;
            }

            void advance(difference_type offset)
            {
                m_value += offset;
            }

            difference_type distance_to(const integer_iterator& other) const
            {
                return is_signed<value_type>::value
                    ? (other.m_value - m_value)
                    : (other.m_value >= m_value)
                        ? static_cast<difference_type>(other.m_value - m_value)
                        : -static_cast<difference_type>(m_value - other.m_value);
            }

            bool equal(const integer_iterator& other) const
            {
                return m_value == other.m_value;
            }

            reference dereference() const
            {
                return m_value;
            }

            friend class ::boost::iterator_core_access;
            value_type m_value;
        };

        // integer_iterator_with_step is similar in nature to the
        // integer_iterator but provides the ability to 'move' in
        // a number of steps specified at construction time.
        //
        // The three variable implementation provides the best guarantees
        // of loop termination upon various combinations of input.
        //
        // While this design is less performant than some less
        // safe alternatives, the use of ranges and iterators to
        // perform counting will never be optimal anyhow, hence
        // if optimal performance is desired a hand-coded loop
        // is the solution.
        template<typename Integer>
        class integer_iterator_with_step
            : public boost::iterator_facade<
                        integer_iterator_with_step<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    >
        {
            typedef boost::iterator_facade<
                        integer_iterator_with_step<Integer>,
                        Integer,
                        boost::random_access_traversal_tag,
                        Integer,
                        std::ptrdiff_t
                    > base_t;
        public:
            typedef typename base_t::value_type value_type;
            typedef typename base_t::difference_type difference_type;
            typedef typename base_t::reference reference;
            typedef std::random_access_iterator_tag iterator_category;

            integer_iterator_with_step(value_type first, difference_type step, value_type step_size)
                : m_first(first)
                , m_step(step)
                , m_step_size(step_size)
            {
            }

        private:
            void increment()
            {
                ++m_step;
            }

            void decrement()
            {
                --m_step;
            }

            void advance(difference_type offset)
            {
                m_step += offset;
            }

            difference_type distance_to(const integer_iterator_with_step& other) const
            {
                return other.m_step - m_step;
            }

            bool equal(const integer_iterator_with_step& other) const
            {
                return m_step == other.m_step;
            }

            reference dereference() const
            {
                return m_first + (m_step * m_step_size);
            }

            friend class ::boost::iterator_core_access;
            value_type m_first;
            difference_type m_step;
            difference_type m_step_size;
        };

    } // namespace range_detail

    template<typename Integer>
    class integer_range
        : public iterator_range< range_detail::integer_iterator<Integer> >
    {
        typedef range_detail::integer_iterator<Integer> iterator_t;
        typedef iterator_range<iterator_t> base_t;
    public:
        integer_range(Integer first, Integer last)
            : base_t(iterator_t(first), iterator_t(last))
        {
        }
    };

    template<typename Integer>
    class strided_integer_range
    : public iterator_range< range_detail::integer_iterator_with_step<Integer> >
    {
        typedef range_detail::integer_iterator_with_step<Integer> iterator_t;
        typedef iterator_range<iterator_t> base_t;
    public:
        template<typename Iterator>
        strided_integer_range(Iterator first, Iterator last)
            : base_t(first, last)
        {
        }
    };

    template<typename Integer>
    integer_range<Integer>
    irange(Integer first, Integer last)
    {
        BOOST_ASSERT( first <= last );
        return integer_range<Integer>(first, last);
    }

    template<typename Integer, typename StepSize>
    strided_integer_range<Integer>
        irange(Integer first, Integer last, StepSize step_size)
    {
        BOOST_ASSERT( step_size != 0 );
        BOOST_ASSERT( (step_size > 0) ? (last >= first) : (last <= first) );

        typedef typename range_detail::integer_iterator_with_step<Integer> iterator_t;

        const std::ptrdiff_t sz = static_cast<std::ptrdiff_t>(step_size >= 0 ? step_size : -step_size);
        const Integer l = step_size >= 0 ? last : first;
        const Integer f = step_size >= 0 ? first : last;
        const std::ptrdiff_t num_steps = (l - f) / sz + ((l - f) % sz ? 1 : 0);
        BOOST_ASSERT(num_steps >= 0);

        return strided_integer_range<Integer>(
            iterator_t(first, 0, step_size),
            iterator_t(first, num_steps, step_size));
    }

    template<typename Integer>
    integer_range<Integer>
    irange(Integer last)
    {
        return integer_range<Integer>(static_cast<Integer>(0), last);
    }

} // namespace boost

#endif // include guard

/* irange.hpp
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
*/