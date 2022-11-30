//  Copyright Neil Groves 2009. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//
// For more information, see http://www.boost.org/libs/range/
//
#ifndef BOOST_RANGE_ALGORITHM_SEARCH_N_HPP_INCLUDED
#define BOOST_RANGE_ALGORITHM_SEARCH_N_HPP_INCLUDED

#include <boost/concept_check.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/detail/range_return.hpp>
#include <boost/range/value_type.hpp>
#include <iterator>
#include <algorithm>

namespace boost
{

namespace range_detail
{
    // Rationale: search_n is implemented rather than delegate to
    // the standard library implementation because some standard
    // library implementations are broken eg. MSVC.

    // search_n forward iterator version
    template<typename ForwardIterator, typename Integer, typename Value>
    inline ForwardIterator
    search_n_impl(ForwardIterator first, ForwardIterator last, Integer count,
                  const Value& value, std::forward_iterator_tag)
    {
        first = std::find(first, last, value);
        while (first != last)
        {
            typename std::iterator_traits<ForwardIterator>::difference_type n = count;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 1 && *i==value)
            {
                ++i;
                --n;
            }
            if (n == 1)
                return first;
            if (i == last)
                return last;
            first = std::find(++i, last, value);
        }
        return last;
    }

    // search_n random-access iterator version
    template<typename RandomAccessIterator, typename Integer, typename Value>
    inline RandomAccessIterator
    search_n_impl(RandomAccessIterator first, RandomAccessIterator last,
                  Integer count, const Value& value,
                  std::random_access_iterator_tag)
    {
        typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_t;

        difference_t tail_size = last - first;
        const difference_t pattern_size = count;

        if (tail_size < pattern_size)
            return last;

        const difference_t skip_offset = pattern_size - 1;
        RandomAccessIterator look_ahead = first + skip_offset;
        tail_size -= pattern_size;

        while (1)
        {
            // look_ahead here is pointing to the last element of the
            // next possible match
            while (!(*look_ahead == value)) // skip loop...
            {
                if (tail_size < pattern_size)
                    return last; // no match
                look_ahead += pattern_size;
                tail_size -= pattern_size;
            }
            difference_t remainder = skip_offset;
            for (RandomAccessIterator back_track = look_ahead - 1;
                    *back_track == value; --back_track)
            {
                if (--remainder == 0)
                {
                    return look_ahead - skip_offset; // matched
                }
            }
            if (remainder > tail_size)
                return last; // no match
            look_ahead += remainder;
            tail_size -= remainder;
        }

        return last;
    }

    // search_n for forward iterators using a binary predicate
    // to determine a match
    template<typename ForwardIterator, typename Integer, typename Value,
             typename BinaryPredicate>
    inline ForwardIterator
    search_n_pred_impl(ForwardIterator first, ForwardIterator last,
                       Integer count, const Value& value,
                       BinaryPredicate pred, std::forward_iterator_tag)
    {
        typedef typename std::iterator_traits<ForwardIterator>::difference_type difference_t;

        while (first != last && !static_cast<bool>(pred(*first, value)))
            ++first;

        while (first != last)
        {
            difference_t n = count;
            ForwardIterator i = first;
            ++i;
            while (i != last && n != 1 && static_cast<bool>(pred(*i, value)))
            {
                ++i;
                --n;
            }
            if (n == 1)
                return first;
            if (i == last)
                return last;
            first = ++i;
            while (first != last && !static_cast<bool>(pred(*first, value)))
                ++first;
        }
        return last;
    }

    // search_n for random-access iterators using a binary predicate
    // to determine a match
    template<typename RandomAccessIterator, typename Integer,
             typename Value, typename BinaryPredicate>
    inline RandomAccessIterator
    search_n_pred_impl(RandomAccessIterator first, RandomAccessIterator last,
                       Integer count, const Value& value,
                       BinaryPredicate pred, std::random_access_iterator_tag)
    {
        typedef typename std::iterator_traits<RandomAccessIterator>::difference_type difference_t;

        difference_t tail_size = last - first;
        const difference_t pattern_size = count;

        if (tail_size < pattern_size)
            return last;

        const difference_t skip_offset = pattern_size - 1;
        RandomAccessIterator look_ahead = first + skip_offset;
        tail_size -= pattern_size;

        while (1)
        {
            // look_ahead points to the last element of the next
            // possible match
            while (!static_cast<bool>(pred(*look_ahead, value))) // skip loop
            {
                if (tail_size < pattern_size)
                    return last; // no match
                look_ahead += pattern_size;
                tail_size -= pattern_size;
            }
            difference_t remainder = skip_offset;
            for (RandomAccessIterator back_track = look_ahead - 1;
                    pred(*back_track, value); --back_track)
            {
                if (--remainder == 0)
                    return look_ahead -= skip_offset; // success
            }
            if (remainder > tail_size)
            {
                return last; // no match
            }
            look_ahead += remainder;
            tail_size -= remainder;
        }
    }

    template<typename ForwardIterator, typename Integer, typename Value>
    inline ForwardIterator
    search_n_impl(ForwardIterator first, ForwardIterator last,
                  Integer count, const Value& value)
    {
        BOOST_RANGE_CONCEPT_ASSERT((ForwardIteratorConcept<ForwardIterator>));
        BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept<Value>));
        BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept<typename std::iterator_traits<ForwardIterator>::value_type>));
        //BOOST_RANGE_CONCEPT_ASSERT((EqualityComparableConcept2<typename std::iterator_traits<ForwardIterator>::value_type, Value>));

        typedef typename std::iterator_traits<ForwardIterator>::iterator_category cat_t;

        if (count <= 0)
            return first;
        if (count == 1)
            return std::find(first, last, value);
        return range_detail::search_n_impl(first, last, count, value, cat_t());
    }

    template<typename ForwardIterator, typename Integer, typename Value,
             typename BinaryPredicate>
    inline ForwardIterator
    search_n_pred_impl(ForwardIterator first, ForwardIterator last,
                       Integer count, const Value& value,
                       BinaryPredicate pred)
    {
        BOOST_RANGE_CONCEPT_ASSERT((ForwardIteratorConcept<ForwardIterator>));
        BOOST_RANGE_CONCEPT_ASSERT((
            BinaryPredicateConcept<
                BinaryPredicate,
                typename std::iterator_traits<ForwardIterator>::value_type,
                Value>
            ));

        typedef typename std::iterator_traits<ForwardIterator>::iterator_category cat_t;

        if (count <= 0)
            return first;
        if (count == 1)
        {
            while (first != last && !static_cast<bool>(pred(*first, value)))
                ++first;
            return first;
        }
        return range_detail::search_n_pred_impl(first, last, count,
                                                value, pred, cat_t());
    }
} // namespace range_detail

namespace range {

/// \brief template function search
///
/// range-based version of the search std algorithm
///
/// \pre ForwardRange is a model of the ForwardRangeConcept
/// \pre Integer is an integral type
/// \pre Value is a model of the EqualityComparableConcept
/// \pre ForwardRange's value type is a model of the EqualityComparableConcept
/// \pre Object's of ForwardRange's value type can be compared for equality with Objects of type Value
template< class ForwardRange, class Integer, class Value >
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
search_n(ForwardRange& rng, Integer count, const Value& value)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return range_detail::search_n_impl(boost::begin(rng),boost::end(rng), count, value);
}

/// \overload
template< class ForwardRange, class Integer, class Value >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
search_n(const ForwardRange& rng, Integer count, const Value& value)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRange>));
    return range_detail::search_n_impl(boost::begin(rng), boost::end(rng), count, value);
}

/// \overload
template< class ForwardRange, class Integer, class Value,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<ForwardRange>::type
search_n(ForwardRange& rng, Integer count, const Value& value,
         BinaryPredicate binary_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        BOOST_DEDUCED_TYPENAME range_value<ForwardRange>::type, const Value&>));
    return range_detail::search_n_pred_impl(boost::begin(rng), boost::end(rng),
        count, value, binary_pred);
}

/// \overload
template< class ForwardRange, class Integer, class Value,
          class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_iterator<const ForwardRange>::type
search_n(const ForwardRange& rng, Integer count, const Value& value,
         BinaryPredicate binary_pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        BOOST_DEDUCED_TYPENAME range_value<const ForwardRange>::type, const Value&>));
    return range_detail::search_n_pred_impl(boost::begin(rng), boost::end(rng),
        count, value, binary_pred);
}

// range_return overloads

/// \overload
template< range_return_value re, class ForwardRange, class Integer,
          class Value >
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
search_n(ForwardRange& rng, Integer count, const Value& value)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    return range_return<ForwardRange,re>::
        pack(range_detail::search_n_impl(boost::begin(rng),boost::end(rng),
                           count, value),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Integer,
          class Value >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
search_n(const ForwardRange& rng, Integer count, const Value& value)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRange>));
    return range_return<const ForwardRange,re>::
        pack(range_detail::search_n_impl(boost::begin(rng), boost::end(rng),
                           count, value),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Integer,
          class Value, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<ForwardRange,re>::type
search_n(ForwardRange& rng, Integer count, const Value& value,
         BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        BOOST_DEDUCED_TYPENAME range_value<ForwardRange>::type,
        const Value&>));
    return range_return<ForwardRange,re>::
        pack(range_detail::search_n_pred_impl(boost::begin(rng),
                                              boost::end(rng),
                           count, value, pred),
             rng);
}

/// \overload
template< range_return_value re, class ForwardRange, class Integer,
          class Value, class BinaryPredicate >
inline BOOST_DEDUCED_TYPENAME range_return<const ForwardRange,re>::type
search_n(const ForwardRange& rng, Integer count, const Value& value,
         BinaryPredicate pred)
{
    BOOST_RANGE_CONCEPT_ASSERT((ForwardRangeConcept<const ForwardRange>));
    BOOST_RANGE_CONCEPT_ASSERT((BinaryPredicateConcept<BinaryPredicate,
        BOOST_DEDUCED_TYPENAME range_value<const ForwardRange>::type,
        const Value&>));
    return range_return<const ForwardRange,re>::
        pack(range_detail::search_n_pred_impl(boost::begin(rng),
                                              boost::end(rng),
                           count, value, pred),
             rng);
}

    } // namespace range
    using range::search_n;
} // namespace boost

#endif // include guard

/* search_n.hpp
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
*/