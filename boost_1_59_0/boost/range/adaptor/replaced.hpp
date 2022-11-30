// Boost.Range library
//
//  Copyright Neil Groves 2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_REPLACED_IMPL_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_REPLACED_IMPL_HPP_INCLUDED

#include <boost/config.hpp>
#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/value_type.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/optional/optional.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class Value >
        class replace_value
        {
        public:
            typedef const Value& result_type;
            typedef const Value& first_argument_type;

            // Rationale:
            // The default constructor is required to allow the transform
            // iterator to properly model the iterator concept.
            replace_value()
            {
            }

            replace_value(const Value& from, const Value& to)
                :   m_impl(data(from, to))
            {
            }

            const Value& operator()(const Value& x) const
            {
                return (x == m_impl->m_from) ? m_impl->m_to : x;
            }

        private:
            struct data
            {
                data(const Value& from, const Value& to)
                    : m_from(from)
                    , m_to(to)
                {
                }

                Value m_from;
                Value m_to;
            };
            boost::optional<data> m_impl;
        };

        template< class R >
        class replaced_range :
            public boost::iterator_range<
                boost::transform_iterator<
                    replace_value< BOOST_DEDUCED_TYPENAME range_value<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > >
        {
        private:
            typedef replace_value< BOOST_DEDUCED_TYPENAME range_value<R>::type > Fn;

            typedef boost::iterator_range<
                boost::transform_iterator<
                    replace_value< BOOST_DEDUCED_TYPENAME range_value<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > > base_t;

        public:
            typedef BOOST_DEDUCED_TYPENAME range_value<R>::type value_type;

            replaced_range( R& r, value_type from, value_type to )
                : base_t( make_transform_iterator( boost::begin(r), Fn(from, to) ),
                          make_transform_iterator( boost::end(r), Fn(from, to) ) )
            { }
        };

        template< class T >
        class replace_holder : public holder2<T>
        {
        public:
            replace_holder( const T& from, const T& to )
                : holder2<T>(from, to)
            { }
        private:
            // not assignable
            void operator=(const replace_holder&);
        };

        template< class SinglePassRange, class Value >
        inline replaced_range<SinglePassRange>
        operator|(SinglePassRange& r, const replace_holder<Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return replaced_range<SinglePassRange>(r, f.val1, f.val2);
        }

        template< class SinglePassRange, class Value >
        inline replaced_range<const SinglePassRange>
        operator|(const SinglePassRange& r, const replace_holder<Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return replaced_range<const SinglePassRange>(r, f.val1, f.val2);
        }
    } // 'range_detail'

    using range_detail::replaced_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder2<range_detail::replace_holder>
                replaced =
                    range_detail::forwarder2<range_detail::replace_holder>();
        }

        template< class SinglePassRange, class Value >
        inline replaced_range<SinglePassRange>
        replace(SinglePassRange& rng, Value from, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return replaced_range<SinglePassRange>(rng, from, to);
        }

        template< class SinglePassRange, class Value >
        inline replaced_range<const SinglePassRange>
        replace(const SinglePassRange& rng, Value from, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return replaced_range<const SinglePassRange>(rng, from ,to);
        }

    } // 'adaptors'
} // 'boost'

#endif // include guard

/* replaced.hpp
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
*/