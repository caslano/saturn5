// Boost.Range library
//
//  Copyright Neil Groves 2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ADAPTOR_STRIDED_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_STRIDED_HPP_INCLUDED

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <iterator>

namespace boost
{
    namespace range_detail
    {
        // strided_iterator for wrapping a forward traversal iterator
        template<class BaseIterator, class Category>
        class strided_iterator
            : public iterator_facade<
                strided_iterator<BaseIterator, Category>
                , typename iterator_value<BaseIterator>::type
                , forward_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            >
        {
            friend class ::boost::iterator_core_access;

            typedef iterator_facade<
                strided_iterator<BaseIterator, Category>
                , typename iterator_value<BaseIterator>::type
                , forward_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            > super_t;

        public:
            typedef typename super_t::difference_type difference_type;
            typedef typename super_t::reference reference;
            typedef BaseIterator base_iterator;
            typedef std::forward_iterator_tag iterator_category;

            strided_iterator()
                : m_it()
                , m_last()
                , m_stride()
            {
            }

            strided_iterator(base_iterator   it,
                             base_iterator   last,
                             difference_type stride)
                : m_it(it)
                , m_last(last)
                , m_stride(stride)
            {
            }

            template<class OtherIterator>
            strided_iterator(
                const strided_iterator<OtherIterator, Category>& other,
                typename enable_if_convertible<
                    OtherIterator,
                    base_iterator
                >::type* = 0
            )
                : m_it(other.base())
                , m_last(other.base_end())
                , m_stride(other.get_stride())
            {
            }

            base_iterator base() const
            {
                return m_it;
            }

            base_iterator base_end() const
            {
                return m_last;
            }

            difference_type get_stride() const
            {
                return m_stride;
            }

        private:
            void increment()
            {
                for (difference_type i = 0;
                        (m_it != m_last) && (i < m_stride); ++i)
                {
                    ++m_it;
                }
            }

            reference dereference() const
            {
                return *m_it;
            }

            template<class OtherIterator>
            bool equal(
                const strided_iterator<OtherIterator, Category>& other,
                typename enable_if_convertible<
                    OtherIterator,
                    base_iterator
                >::type* = 0) const
            {
                return m_it == other.m_it;
            }

            base_iterator m_it;
            base_iterator m_last;
            difference_type m_stride;
        };

        // strided_iterator for wrapping a bidirectional iterator
        template<class BaseIterator>
        class strided_iterator<BaseIterator, bidirectional_traversal_tag>
            : public iterator_facade<
                strided_iterator<BaseIterator, bidirectional_traversal_tag>
                , typename iterator_value<BaseIterator>::type
                , bidirectional_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            >
        {
            friend class ::boost::iterator_core_access;

            typedef iterator_facade<
                strided_iterator<BaseIterator, bidirectional_traversal_tag>
                , typename iterator_value<BaseIterator>::type
                , bidirectional_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            > super_t;
        public:
            typedef typename super_t::difference_type difference_type;
            typedef typename super_t::reference reference;
            typedef BaseIterator base_iterator;
            typedef typename boost::make_unsigned<difference_type>::type
                        size_type;
            typedef std::bidirectional_iterator_tag iterator_category;

            strided_iterator()
                : m_it()
                , m_offset()
                , m_index()
                , m_stride()
            {
            }

            strided_iterator(base_iterator   it,
                             size_type       index,
                             difference_type stride)
                : m_it(it)
                , m_offset()
                , m_index(index)
                , m_stride(stride)
            {
                if (stride && ((m_index % stride) != 0))
                    m_index += (stride - (m_index % stride));
            }

            template<class OtherIterator>
            strided_iterator(
                const strided_iterator<
                    OtherIterator,
                    bidirectional_traversal_tag
                >& other,
                typename enable_if_convertible<
                    OtherIterator,
                    base_iterator
                >::type* = 0
            )
                : m_it(other.base())
                , m_offset(other.get_offset())
                , m_index(other.get_index())
                , m_stride(other.get_stride())
            {
            }

            base_iterator base() const
            {
                return m_it;
            }

            difference_type get_offset() const
            {
                return m_offset;
            }

            size_type get_index() const
            {
                return m_index;
            }

            difference_type get_stride() const
            {
                return m_stride;
            }

        private:
            void increment()
            {
                m_offset += m_stride;
            }

            void decrement()
            {
                m_offset -= m_stride;
            }

            reference dereference() const
            {
                update();
                return *m_it;
            }

            void update() const
            {
                std::advance(m_it, m_offset);
                m_index += m_offset;
                m_offset = 0;
            }

            template<class OtherIterator>
            bool equal(
                const strided_iterator<
                    OtherIterator,
                    bidirectional_traversal_tag
                >& other,
                typename enable_if_convertible<
                    OtherIterator,
                    base_iterator
                >::type* = 0) const
            {
                return (m_index + m_offset) ==
                            (other.get_index() + other.get_offset());
            }

            mutable base_iterator m_it;
            mutable difference_type m_offset;
            mutable size_type m_index;
            difference_type m_stride;
        };

        // strided_iterator implementation for wrapping a random access iterator
        template<class BaseIterator>
        class strided_iterator<BaseIterator, random_access_traversal_tag>
            : public iterator_facade<
                strided_iterator<BaseIterator, random_access_traversal_tag>
                , typename iterator_value<BaseIterator>::type
                , random_access_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            >
        {
            friend class ::boost::iterator_core_access;

            typedef iterator_facade<
                strided_iterator<BaseIterator, random_access_traversal_tag>
                , typename iterator_value<BaseIterator>::type
                , random_access_traversal_tag
                , typename iterator_reference<BaseIterator>::type
                , typename iterator_difference<BaseIterator>::type
            > super_t;
        public:
            typedef typename super_t::difference_type difference_type;
            typedef typename super_t::reference reference;
            typedef BaseIterator base_iterator;
            typedef std::random_access_iterator_tag iterator_category;

            strided_iterator()
                : m_it()
                , m_first()
                , m_index(0)
                , m_stride()
            {
            }

            strided_iterator(
                base_iterator   first,
                base_iterator   it,
                difference_type stride
            )
                : m_it(it)
                , m_first(first)
                , m_index(stride ? (it - first) : difference_type())
                , m_stride(stride)
            {
                if (stride && ((m_index % stride) != 0))
                    m_index += (stride - (m_index % stride));
            }

            template<class OtherIterator>
            strided_iterator(
                const strided_iterator<
                    OtherIterator,
                    random_access_traversal_tag
                >& other,
                typename enable_if_convertible<
                    OtherIterator,
                    base_iterator
                >::type* = 0
            )
                : m_it(other.base())
                , m_first(other.base_begin())
                , m_index(other.get_index())
                , m_stride(other.get_stride())
            {
            }

            base_iterator base_begin() const
            {
                return m_first;
            }

            base_iterator base() const
            {
                return m_it;
            }

            difference_type get_stride() const
            {
                return m_stride;
            }

            difference_type get_index() const
            {
                return m_index;
            }

        private:
            void increment()
            {
                m_index += m_stride;
            }

            void decrement()
            {
                m_index -= m_stride;
            }

            void advance(difference_type offset)
            {
                m_index += (m_stride * offset);
            }

            // Implementation detail: only update the actual underlying iterator
            // at the point of dereference. This is done so that the increment
            // and decrement can overshoot the valid sequence as is required
            // by striding. Since we can do all comparisons just with the index
            // simply, and all dereferences must be within the valid range.
            void update() const
            {
                m_it = m_first + m_index;
            }

            template<class OtherIterator>
            difference_type distance_to(
                const strided_iterator<
                    OtherIterator,
                    random_access_traversal_tag
                >& other,
                typename enable_if_convertible<
                            OtherIterator, base_iterator>::type* = 0) const
            {
                BOOST_ASSERT((other.m_index - m_index) % m_stride == difference_type());
                return (other.m_index - m_index) / m_stride;
            }

            template<class OtherIterator>
            bool equal(
                const strided_iterator<
                    OtherIterator,
                    random_access_traversal_tag
                >& other,
                typename enable_if_convertible<
                            OtherIterator, base_iterator>::type* = 0) const
            {
                return m_index == other.m_index;
            }

            reference dereference() const
            {
                update();
                return *m_it;
            }

        private:
            mutable base_iterator m_it;
            base_iterator m_first;
            difference_type m_index;
            difference_type m_stride;
        };

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            forward_traversal_tag
        >
        make_begin_strided_iterator(
            Rng& rng,
            Difference stride,
            forward_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<Rng>::type,
                forward_traversal_tag
            >(boost::begin(rng), boost::end(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            forward_traversal_tag
        >
        make_begin_strided_iterator(
            const Rng& rng,
            Difference stride,
            forward_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<const Rng>::type,
                forward_traversal_tag
            >(boost::begin(rng), boost::end(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            forward_traversal_tag
        >
        make_end_strided_iterator(
            Rng& rng,
            Difference stride,
            forward_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<Rng>::type,
                forward_traversal_tag
            >(boost::end(rng), boost::end(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            forward_traversal_tag
        >
        make_end_strided_iterator(
            const Rng& rng,
            Difference stride,
            forward_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<const Rng>::type,
                forward_traversal_tag
            >(boost::end(rng), boost::end(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            bidirectional_traversal_tag
        >
        make_begin_strided_iterator(
            Rng& rng,
            Difference stride,
            bidirectional_traversal_tag)
        {
            typedef typename range_difference<Rng>::type difference_type;

            return strided_iterator<
                typename range_iterator<Rng>::type,
                bidirectional_traversal_tag
            >(boost::begin(rng), difference_type(), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            bidirectional_traversal_tag
        >
        make_begin_strided_iterator(
            const Rng& rng,
            Difference stride,
            bidirectional_traversal_tag)
        {
            typedef typename range_difference<const Rng>::type difference_type;

            return strided_iterator<
                typename range_iterator<const Rng>::type,
                bidirectional_traversal_tag
            >(boost::begin(rng), difference_type(), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            bidirectional_traversal_tag
        >
        make_end_strided_iterator(
            Rng& rng,
            Difference stride,
            bidirectional_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<Rng>::type,
                bidirectional_traversal_tag
            >(boost::end(rng), boost::size(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            bidirectional_traversal_tag
        >
        make_end_strided_iterator(
            const Rng& rng,
            Difference stride,
            bidirectional_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<const Rng>::type,
                bidirectional_traversal_tag
            >(boost::end(rng), boost::size(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            random_access_traversal_tag
        >
        make_begin_strided_iterator(
            Rng& rng,
            Difference stride,
            random_access_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<Rng>::type,
                random_access_traversal_tag
            >(boost::begin(rng), boost::begin(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            random_access_traversal_tag
        >
        make_begin_strided_iterator(
            const Rng& rng,
            Difference stride,
            random_access_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<const Rng>::type,
                random_access_traversal_tag
            >(boost::begin(rng), boost::begin(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<Rng>::type,
            random_access_traversal_tag
        >
        make_end_strided_iterator(
            Rng& rng,
            Difference stride,
            random_access_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<Rng>::type,
                random_access_traversal_tag
            >(boost::begin(rng), boost::end(rng), stride);
        }

        template<class Rng, class Difference> inline
        strided_iterator<
            typename range_iterator<const Rng>::type,
            random_access_traversal_tag
        >
        make_end_strided_iterator(
            const Rng& rng,
            Difference stride,
            random_access_traversal_tag)
        {
            return strided_iterator<
                typename range_iterator<const Rng>::type,
                random_access_traversal_tag
            >(boost::begin(rng), boost::end(rng), stride);
        }

        template<
            class Rng,
            class Category =
                typename iterators::pure_iterator_traversal<
                    typename range_iterator<Rng>::type
                >::type
        >
        class strided_range
            : public iterator_range<
                range_detail::strided_iterator<
                    typename range_iterator<Rng>::type,
                    Category
                >
            >
        {
            typedef range_detail::strided_iterator<
                typename range_iterator<Rng>::type,
                Category
            > iter_type;
            typedef iterator_range<iter_type> super_t;
        public:
            template<class Difference>
            strided_range(Difference stride, Rng& rng)
                : super_t(
                    range_detail::make_begin_strided_iterator(
                        rng, stride,
                        typename iterator_traversal<
                            typename range_iterator<Rng>::type
                        >::type()),
                    range_detail::make_end_strided_iterator(
                        rng, stride,
                        typename iterator_traversal<
                            typename range_iterator<Rng>::type
                        >::type()))
            {
                BOOST_ASSERT( stride >= 0 );
            }
        };

        template<class Difference>
        class strided_holder : public holder<Difference>
        {
        public:
            explicit strided_holder(Difference value)
                : holder<Difference>(value)
            {
            }
        };

        template<class Rng, class Difference>
        inline strided_range<Rng>
        operator|(Rng& rng, const strided_holder<Difference>& stride)
        {
            return strided_range<Rng>(stride.val, rng);
        }

        template<class Rng, class Difference>
        inline strided_range<const Rng>
        operator|(const Rng& rng, const strided_holder<Difference>& stride)
        {
            return strided_range<const Rng>(stride.val, rng);
        }

    } // namespace range_detail

    using range_detail::strided_range;

    namespace adaptors
    {

        namespace
        {
            const range_detail::forwarder<range_detail::strided_holder>
                strided = range_detail::forwarder<
                            range_detail::strided_holder>();
        }

        template<class Range, class Difference>
        inline strided_range<Range>
        stride(Range& rng, Difference step)
        {
            return strided_range<Range>(step, rng);
        }

        template<class Range, class Difference>
        inline strided_range<const Range>
        stride(const Range& rng, Difference step)
        {
            return strided_range<const Range>(step, rng);
        }

    } // namespace 'adaptors'
} // namespace 'boost'

#endif

/* strided.hpp
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
*/