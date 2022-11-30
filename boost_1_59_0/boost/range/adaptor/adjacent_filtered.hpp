// Boost.Range library
//
//  Copyright Thorsten Ottosen, Neil Groves 2006 - 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/range/
//

#ifndef BOOST_RANGE_ADAPTOR_ADJACENT_FILTER_IMPL_HPP
#define BOOST_RANGE_ADAPTOR_ADJACENT_FILTER_IMPL_HPP

#include <boost/config.hpp>
#ifdef BOOST_MSVC
#pragma warning( push )
#pragma warning( disable : 4355 )
#endif

#include <boost/range/adaptor/argument_fwd.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/iterator/iterator_adaptor.hpp>
#include <boost/next_prior.hpp>


namespace boost
{
    namespace range_detail
    {
        template< class Iter, class Pred, bool default_pass >
        class skip_iterator
          : public boost::iterator_adaptor<
                    skip_iterator<Iter,Pred,default_pass>,
                    Iter,
                    BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type,
                    boost::forward_traversal_tag,
                    BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference,
                    BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type
                >
          , private Pred
        {
        private:
            typedef boost::iterator_adaptor<
                        skip_iterator<Iter,Pred,default_pass>,
                        Iter,
                        BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::value_type,
                        boost::forward_traversal_tag,
                        BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::reference,
                        BOOST_DEDUCED_TYPENAME std::iterator_traits<Iter>::difference_type
                    > base_t;

        public:
            typedef Pred pred_t;
            typedef Iter iter_t;

            skip_iterator() : m_last() {}

            skip_iterator(iter_t it, iter_t last, const Pred& pred)
                : base_t(it)
                , pred_t(pred)
                , m_last(last)
            {
            }

            template<class OtherIter>
            skip_iterator( const skip_iterator<OtherIter, pred_t, default_pass>& other )
            : base_t(other.base())
            , pred_t(other)
            , m_last(other.m_last)
            {
            }

            void increment()
            {
                iter_t& it = this->base_reference();
                BOOST_ASSERT( it != m_last );
                pred_t& bi_pred = *this;
                iter_t prev = it;
                ++it;
                if (it != m_last)
                {
                    if (default_pass)
                    {
                        while (it != m_last && !bi_pred(*prev, *it))
                        {
                            ++it;
                            ++prev;
                        }
                    }
                    else
                    {
                        for (; it != m_last; ++it, ++prev)
                        {
                            if (bi_pred(*prev, *it))
                            {
                                break;
                            }
                        }
                    }
                }
            }

            iter_t m_last;
        };

        template< class P, class R, bool default_pass >
        struct adjacent_filtered_range
            : iterator_range< skip_iterator<
                                BOOST_DEDUCED_TYPENAME range_iterator<R>::type,
                                P,
                                default_pass
                            >
                        >
        {
        private:
            typedef skip_iterator<
                        BOOST_DEDUCED_TYPENAME range_iterator<R>::type,
                        P,
                        default_pass
                     >
                skip_iter;

            typedef iterator_range<skip_iter>
                base_range;

            typedef BOOST_DEDUCED_TYPENAME range_iterator<R>::type raw_iterator;

        public:
            adjacent_filtered_range( const P& p, R& r )
            : base_range(skip_iter(boost::begin(r), boost::end(r), p),
                         skip_iter(boost::end(r), boost::end(r), p))
            {
            }
        };

        template< class T >
        struct adjacent_holder : holder<T>
        {
            adjacent_holder( T r ) : holder<T>(r)
            { }
        };

        template< class T >
        struct adjacent_excl_holder : holder<T>
        {
            adjacent_excl_holder( T r ) : holder<T>(r)
            { }
        };

        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, ForwardRng, true>
        operator|( ForwardRng& r,
                   const adjacent_holder<BinPredicate>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRng>));

            return adjacent_filtered_range<BinPredicate, ForwardRng, true>( f.val, r );
        }

        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, const ForwardRng, true>
        operator|( const ForwardRng& r,
                   const adjacent_holder<BinPredicate>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRng>));

            return adjacent_filtered_range<BinPredicate,
                                           const ForwardRng, true>( f.val, r );
        }

        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, ForwardRng, false>
        operator|( ForwardRng& r,
                   const adjacent_excl_holder<BinPredicate>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRng>));
            return adjacent_filtered_range<BinPredicate, ForwardRng, false>( f.val, r );
        }

        template< class ForwardRng, class BinPredicate >
        inline adjacent_filtered_range<BinPredicate, const ForwardRng, false>
        operator|( const ForwardRng& r,
                   const adjacent_excl_holder<BinPredicate>& f )
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRng>));
            return adjacent_filtered_range<BinPredicate,
                                           const ForwardRng, false>( f.val, r );
        }

    } // 'range_detail'

    // Bring adjacent_filter_range into the boost namespace so that users of
    // this library may specify the return type of the '|' operator and
    // adjacent_filter()
    using range_detail::adjacent_filtered_range;

    namespace adaptors
    {
        namespace
        {
            const range_detail::forwarder<range_detail::adjacent_holder>
                adjacent_filtered =
                   range_detail::forwarder<range_detail::adjacent_holder>();

            const range_detail::forwarder<range_detail::adjacent_excl_holder>
                adjacent_filtered_excl =
                    range_detail::forwarder<range_detail::adjacent_excl_holder>();
        }

        template<class ForwardRng, class BinPredicate>
        inline adjacent_filtered_range<BinPredicate, ForwardRng, true>
        adjacent_filter(ForwardRng& rng, BinPredicate filter_pred)
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRng>));
            return adjacent_filtered_range<BinPredicate, ForwardRng, true>(filter_pred, rng);
        }

        template<class ForwardRng, class BinPredicate>
        inline adjacent_filtered_range<BinPredicate, const ForwardRng, true>
        adjacent_filter(const ForwardRng& rng, BinPredicate filter_pred)
        {
            BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRng>));
            return adjacent_filtered_range<BinPredicate, const ForwardRng, true>(filter_pred, rng);
        }

    } // 'adaptors'

}

#ifdef BOOST_MSVC
#pragma warning( pop )
#endif

#endif

/* adjacent_filtered.hpp
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
*/