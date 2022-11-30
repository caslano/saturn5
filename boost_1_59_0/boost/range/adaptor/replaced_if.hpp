// Boost.Range library
//
//  Copyright Neil Groves 2007. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_REPLACED_IF_IMPL_HPP_INCLUDED
#define BOOST_RANGE_ADAPTOR_REPLACED_IF_IMPL_HPP_INCLUDED

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
        template< class Pred, class Value >
        class replace_value_if
        {
        public:
            typedef const Value& result_type;
            typedef const Value& first_argument_type;

            // Rationale:
            // required to allow the iterator to be default constructible.
            replace_value_if()
            {
            }

            replace_value_if(const Pred& pred, const Value& to)
                : m_impl(data(pred, to))
            {
            }

            const Value& operator()(const Value& x) const
            {
                return m_impl->m_pred(x) ? m_impl->m_to : x;
            }

        private:
            struct data
            {
                data(const Pred& p, const Value& t)
                    : m_pred(p), m_to(t)
                {
                }

                Pred  m_pred;
                Value m_to;
            };
            boost::optional<data> m_impl;
        };

        template< class Pred, class R >
        class replaced_if_range :
            public boost::iterator_range<
                boost::transform_iterator<
                    replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_value<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > >
        {
        private:
            typedef replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_value<R>::type > Fn;

            typedef boost::iterator_range<
                boost::transform_iterator<
                    replace_value_if< Pred, BOOST_DEDUCED_TYPENAME range_value<R>::type >,
                    BOOST_DEDUCED_TYPENAME range_iterator<R>::type > > base_t;

        public:
            typedef BOOST_DEDUCED_TYPENAME range_value<R>::type value_type;

            replaced_if_range( R& r, const Pred& pred, value_type to )
                : base_t( make_transform_iterator( boost::begin(r), Fn(pred, to) ),
                          make_transform_iterator( boost::end(r), Fn(pred, to) ) )
            { }
        };

        template< class Pred, class T >
        class replace_if_holder
        {
        public:
            replace_if_holder( const Pred& pred, const T& to )
                : m_pred(pred), m_to(to)
            { }

            const Pred& pred() const { return m_pred; }
            const T& to() const { return m_to; }

        private:
            Pred m_pred;
            T m_to;
        };

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, SinglePassRange>
        operator|(SinglePassRange& r, const replace_if_holder<Pred, Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return replaced_if_range<Pred, SinglePassRange>(
                r, f.pred(), f.to());
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, const SinglePassRange>
        operator|(const SinglePassRange& r, const replace_if_holder<Pred, Value>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return replaced_if_range<Pred, const SinglePassRange>(
                r, f.pred(), f.to());
        }
    } // 'range_detail'

    using range_detail::replaced_if_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder2TU<range_detail::replace_if_holder>
                replaced_if =
                    range_detail::forwarder2TU<range_detail::replace_if_holder>();
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, SinglePassRange>
        replace_if(SinglePassRange& rng, Pred pred, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return range_detail::replaced_if_range<Pred, SinglePassRange>(
                rng, pred, to);
        }

        template< class Pred, class SinglePassRange, class Value >
        inline replaced_if_range<Pred, const SinglePassRange>
        replace_if(const SinglePassRange& rng, Pred pred, Value to)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return range_detail::replaced_if_range<Pred, const SinglePassRange>(
                rng, pred, to);
        }
    } // 'adaptors'

} // 'boost'

#endif // include guard

/* replaced_if.hpp
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
*/