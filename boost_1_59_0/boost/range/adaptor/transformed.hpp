// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_TRANSFORMED_HPP
#define BOOST_RANGE_ADAPTOR_TRANSFORMED_HPP

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/detail/default_constructible_unary_fn.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/utility/result_of.hpp>

namespace boost
{
    namespace range_detail
    {
        // A type generator to produce the transform_iterator type conditionally
        // including a wrapped predicate as appropriate.
        template<typename P, typename It>
        struct transform_iterator_gen
        {
            typedef transform_iterator<
                typename default_constructible_unary_fn_gen<
                    P,
                    typename transform_iterator<P, It>::reference
                >::type,
                It
            > type;
        };

        template< class F, class R >
        struct transformed_range :
            public boost::iterator_range<
                typename transform_iterator_gen<
                    F, typename range_iterator<R>::type>::type>
        {
        private:
            typedef typename transform_iterator_gen<
                F, typename range_iterator<R>::type>::type transform_iter_t;

            typedef boost::iterator_range<transform_iter_t> base;

        public:
            typedef typename default_constructible_unary_fn_gen<
                F,
                typename transform_iterator<
                    F,
                    typename range_iterator<R>::type
                >::reference
            >::type transform_fn_type;

            typedef R source_range_type;

            transformed_range(transform_fn_type f, R& r)
                : base(transform_iter_t(boost::begin(r), f),
                       transform_iter_t(boost::end(r), f))
            {
            }
        };

        template< class T >
        struct transform_holder : holder<T>
        {
            transform_holder( T r ) : holder<T>(r)
            {
            }
        };

        template< class SinglePassRange, class UnaryFunction >
        inline transformed_range<UnaryFunction,SinglePassRange>
        operator|( SinglePassRange& r,
                   const transform_holder<UnaryFunction>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return transformed_range<UnaryFunction,SinglePassRange>( f.val, r );
        }

        template< class SinglePassRange, class UnaryFunction >
        inline transformed_range<UnaryFunction, const SinglePassRange>
        operator|( const SinglePassRange& r,
                   const transform_holder<UnaryFunction>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

           return transformed_range<UnaryFunction, const SinglePassRange>(
               f.val, r);
        }

    } // 'range_detail'

    using range_detail::transformed_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::transform_holder>
                    transformed =
                      range_detail::forwarder<range_detail::transform_holder>();
        }

        template<class UnaryFunction, class SinglePassRange>
        inline transformed_range<UnaryFunction, SinglePassRange>
        transform(SinglePassRange& rng, UnaryFunction fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return transformed_range<UnaryFunction, SinglePassRange>(fn, rng);
        }

        template<class UnaryFunction, class SinglePassRange>
        inline transformed_range<UnaryFunction, const SinglePassRange>
        transform(const SinglePassRange& rng, UnaryFunction fn)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return transformed_range<UnaryFunction, const SinglePassRange>(
                fn, rng);
        }
    } // 'adaptors'

}

#endif

/* transformed.hpp
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
*/