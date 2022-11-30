// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_FILTERED_HPP
#define BOOST_RANGE_ADAPTOR_FILTERED_HPP

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/detail/default_constructible_unary_fn.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/filter_iterator.hpp>

namespace boost
{
    namespace range_detail
    {
        template< class P, class R >
        struct filtered_range :
            boost::iterator_range<
                boost::filter_iterator<
                    typename default_constructible_unary_fn_gen<P, bool>::type,
                    typename range_iterator<R>::type
                >
            >
        {
        private:
            typedef boost::iterator_range<
                boost::filter_iterator<
                    typename default_constructible_unary_fn_gen<P, bool>::type,
                    typename range_iterator<R>::type
                >
            > base;
        public:
            typedef typename default_constructible_unary_fn_gen<P, bool>::type
                pred_t;

            filtered_range(P p, R& r)
            : base(make_filter_iterator(pred_t(p),
                                        boost::begin(r), boost::end(r)),
                   make_filter_iterator(pred_t(p),
                                        boost::end(r), boost::end(r)))
            { }
        };

        template< class T >
        struct filter_holder : holder<T>
        {
            filter_holder( T r ) : holder<T>(r)
            { }
        };

        template< class SinglePassRange, class Predicate >
        inline filtered_range<Predicate, SinglePassRange>
        operator|(SinglePassRange& r,
                  const filter_holder<Predicate>& f)
        {
            BOOST_RANGE_CONCEPT_ASSERT((SinglePassRangeConcept<SinglePassRange>));
            return filtered_range<Predicate, SinglePassRange>( f.val, r );
        }

        template< class SinglePassRange, class Predicate >
        inline filtered_range<Predicate, const SinglePassRange>
        operator|(const SinglePassRange& r,
                  const filter_holder<Predicate>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));
            return filtered_range<Predicate, const SinglePassRange>( f.val, r );
        }

    } // 'range_detail'

    // Unusual use of 'using' is intended to bring filter_range into the boost namespace
    // while leaving the mechanics of the '|' operator in range_detail and maintain
    // argument dependent lookup.
    // filter_range logically needs to be in the boost namespace to allow user of
    // the library to define the return type for filter()
    using range_detail::filtered_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::filter_holder>
                    filtered =
                       range_detail::forwarder<range_detail::filter_holder>();
        }

        template<class SinglePassRange, class Predicate>
        inline filtered_range<Predicate, SinglePassRange>
        filter(SinglePassRange& rng, Predicate filter_pred)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<SinglePassRange>));

            return range_detail::filtered_range<
                Predicate, SinglePassRange>( filter_pred, rng );
        }

        template<class SinglePassRange, class Predicate>
        inline filtered_range<Predicate, const SinglePassRange>
        filter(const SinglePassRange& rng, Predicate filter_pred)
        {
            BOOST_RANGE_CONCEPT_ASSERT((
                SinglePassRangeConcept<const SinglePassRange>));

            return range_detail::filtered_range<
                Predicate, const SinglePassRange>( filter_pred, rng );
        }
    } // 'adaptors'

}

#endif

/* filtered.hpp
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
*/