// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.

// This file was modified by Oracle on 2013, 2014, 2015, 2016, 2019.
// Modifications copyright (c) 2013-2019 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_RANGE_HPP
#define BOOST_GEOMETRY_UTIL_RANGE_HPP

#include <algorithm>
#include <iterator>

#include <boost/concept_check.hpp>
#include <boost/config.hpp>
#include <boost/core/addressof.hpp>
#include <boost/range/concepts.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/empty.hpp>
#include <boost/range/difference_type.hpp>
#include <boost/range/iterator.hpp>
#include <boost/range/rbegin.hpp>
#include <boost/range/reference.hpp>
#include <boost/range/size.hpp>
#include <boost/range/value_type.hpp>
#include <boost/type_traits/is_convertible.hpp>

#include <boost/geometry/core/assert.hpp>
#include <boost/geometry/core/mutable_range.hpp>

namespace boost { namespace geometry { namespace range {

namespace detail {

// NOTE: For SinglePassRanges pos could iterate over all elements until the i-th element was met.

template <typename RandomAccessRange>
struct pos
{
    typedef typename boost::range_iterator<RandomAccessRange>::type iterator;
    typedef typename boost::range_size<RandomAccessRange>::type size_type;
    typedef typename boost::range_difference<RandomAccessRange>::type difference_type;

    static inline iterator apply(RandomAccessRange & rng, size_type i)
    {
        BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<RandomAccessRange> ));
        return boost::begin(rng) + static_cast<difference_type>(i);
    }
};

} // namespace detail

/*!
\brief Short utility to conveniently return an iterator of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_iterator<RandomAccessRange const>::type
pos(RandomAccessRange const& rng,
    typename boost::range_size<RandomAccessRange const>::type i)
{
    BOOST_GEOMETRY_ASSERT(i <= boost::size(rng));
    return detail::pos<RandomAccessRange const>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an iterator of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_iterator<RandomAccessRange>::type
pos(RandomAccessRange & rng,
    typename boost::range_size<RandomAccessRange>::type i)
{
    BOOST_GEOMETRY_ASSERT(i <= boost::size(rng));
    return detail::pos<RandomAccessRange>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an element of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_reference<RandomAccessRange const>::type
at(RandomAccessRange const& rng,
   typename boost::range_size<RandomAccessRange const>::type i)
{
    BOOST_GEOMETRY_ASSERT(i < boost::size(rng));
    return * detail::pos<RandomAccessRange const>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return an element of a RandomAccessRange.
\ingroup utility
*/
template <typename RandomAccessRange>
inline typename boost::range_reference<RandomAccessRange>::type
at(RandomAccessRange & rng,
   typename boost::range_size<RandomAccessRange>::type i)
{
    BOOST_GEOMETRY_ASSERT(i < boost::size(rng));
    return * detail::pos<RandomAccessRange>::apply(rng, i);
}

/*!
\brief Short utility to conveniently return the front element of a Range.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_reference<Range const>::type
front(Range const& rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *boost::begin(rng);
}

/*!
\brief Short utility to conveniently return the front element of a Range.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_reference<Range>::type
front(Range & rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *boost::begin(rng);
}

// NOTE: For SinglePassRanges back() could iterate over all elements until the last element is met.

/*!
\brief Short utility to conveniently return the back element of a BidirectionalRange.
\ingroup utility
*/
template <typename BidirectionalRange>
inline typename boost::range_reference<BidirectionalRange const>::type
back(BidirectionalRange const& rng)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::BidirectionalRangeConcept<BidirectionalRange const> ));
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *(boost::rbegin(rng));
}

/*!
\brief Short utility to conveniently return the back element of a BidirectionalRange.
\ingroup utility
*/
template <typename BidirectionalRange>
inline typename boost::range_reference<BidirectionalRange>::type
back(BidirectionalRange & rng)
{
    BOOST_RANGE_CONCEPT_ASSERT((boost::BidirectionalRangeConcept<BidirectionalRange>));
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    return *(boost::rbegin(rng));
}


/*!
\brief Short utility to conveniently clear a mutable range.
       It uses traits::clear<>.
\ingroup utility
*/
template <typename Range>
inline void clear(Range & rng)
{
    // NOTE: this trait is probably not needed since it could be implemented using resize()
    geometry::traits::clear<Range>::apply(rng);
}

/*!
\brief Short utility to conveniently insert a new element at the end of a mutable range.
       It uses boost::geometry::traits::push_back<>.
\ingroup utility
*/
template <typename Range>
inline void push_back(Range & rng,
                      typename boost::range_value<Range>::type const& value)
{
    geometry::traits::push_back<Range>::apply(rng, value);
}

/*!
\brief Short utility to conveniently resize a mutable range.
       It uses boost::geometry::traits::resize<>.
\ingroup utility
*/
template <typename Range>
inline void resize(Range & rng,
                   typename boost::range_size<Range>::type new_size)
{
    geometry::traits::resize<Range>::apply(rng, new_size);
}


/*!
\brief Short utility to conveniently remove an element from the back of a mutable range.
       It uses resize().
\ingroup utility
*/
template <typename Range>
inline void pop_back(Range & rng)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    range::resize(rng, boost::size(rng) - 1);
}

namespace detail {

#ifndef BOOST_NO_CXX11_RVALUE_REFERENCES

template <typename It,
          typename OutIt,
          bool UseMove = boost::is_convertible
                            <
                                typename std::iterator_traits<It>::value_type &&,
                                typename std::iterator_traits<OutIt>::value_type
                            >::value>
struct copy_or_move_impl
{
    static inline OutIt apply(It first, It last, OutIt out)
    {
        return std::move(first, last, out);
    }
};

template <typename It, typename OutIt>
struct copy_or_move_impl<It, OutIt, false>
{
    static inline OutIt apply(It first, It last, OutIt out)
    {
        return std::copy(first, last, out);
    }
};

template <typename It, typename OutIt>
inline OutIt copy_or_move(It first, It last, OutIt out)
{
    return copy_or_move_impl<It, OutIt>::apply(first, last, out);
}

#else

template <typename It, typename OutIt>
inline OutIt copy_or_move(It first, It last, OutIt out)
{
    return std::copy(first, last, out);
}

#endif

} // namespace detail

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::copy() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range>::type it)
{
    BOOST_GEOMETRY_ASSERT(!boost::empty(rng));
    BOOST_GEOMETRY_ASSERT(it != boost::end(rng));

    typename boost::range_difference<Range>::type const
        d = std::distance(boost::begin(rng), it);

    typename boost::range_iterator<Range>::type
        next = it;
    ++next;

    detail::copy_or_move(next, boost::end(rng), it);
    range::resize(rng, boost::size(rng) - 1);

    // NOTE: In general this should be sufficient:
    //    return it;
    // But in MSVC using the returned iterator causes
    // assertion failures when iterator debugging is enabled
    // Furthermore the code below should work in the case if resize()
    // invalidates iterators when the container is resized down.
    return boost::begin(rng) + d;
}

/*!
\brief Short utility to conveniently remove an element from a mutable range.
       It uses std::copy() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range const>::type cit)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        it = boost::begin(rng)
                + std::distance(boost::const_begin(rng), cit);

    return range::erase(rng, it);
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::copy() and resize(). Version taking mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range>::type first,
      typename boost::range_iterator<Range>::type last)
{
    typename boost::range_difference<Range>::type const
        diff = std::distance(first, last);
    BOOST_GEOMETRY_ASSERT(diff >= 0);

    std::size_t const count = static_cast<std::size_t>(diff);
    BOOST_GEOMETRY_ASSERT(count <= boost::size(rng));
    
    if ( count > 0 )
    {
        typename boost::range_difference<Range>::type const
            d = std::distance(boost::begin(rng), first);

        detail::copy_or_move(last, boost::end(rng), first);
        range::resize(rng, boost::size(rng) - count);

        // NOTE: In general this should be sufficient:
        //    return first;
        // But in MSVC using the returned iterator causes
        // assertion failures when iterator debugging is enabled
        // Furthermore the code below should work in the case if resize()
        // invalidates iterators when the container is resized down.
        return boost::begin(rng) + d;
    }

    return first;
}

/*!
\brief Short utility to conveniently remove a range of elements from a mutable range.
       It uses std::copy() and resize(). Version taking non-mutable iterators.
\ingroup utility
*/
template <typename Range>
inline typename boost::range_iterator<Range>::type
erase(Range & rng,
      typename boost::range_iterator<Range const>::type cfirst,
      typename boost::range_iterator<Range const>::type clast)
{
    BOOST_RANGE_CONCEPT_ASSERT(( boost::RandomAccessRangeConcept<Range> ));

    typename boost::range_iterator<Range>::type
        first = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), cfirst);
    typename boost::range_iterator<Range>::type
        last = boost::begin(rng)
                    + std::distance(boost::const_begin(rng), clast);

    return range::erase(rng, first, last);
}

// back_inserter

template <class Container>
class back_insert_iterator
{
public:
    typedef std::output_iterator_tag iterator_category;
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    typedef Container container_type;

    explicit back_insert_iterator(Container & c)
        : container(boost::addressof(c))
    {}

    back_insert_iterator & operator=(typename Container::value_type const& value)
    {
        range::push_back(*container, value);
        return *this;
    }

    back_insert_iterator & operator* ()
    {
        return *this;
    }

    back_insert_iterator & operator++ ()
    {
        return *this;
    }

    back_insert_iterator operator++(int)
    {
        return *this;
    }

private:
    Container * container;
};

template <typename Range>
inline back_insert_iterator<Range> back_inserter(Range & rng)
{
    return back_insert_iterator<Range>(rng);
}

}}} // namespace boost::geometry::range

#endif // BOOST_GEOMETRY_UTIL_RANGE_HPP

/* range.hpp
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
*/