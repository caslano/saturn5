// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014-2020, Oracle and/or its affiliates.
// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_RANGE_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_RANGE_SEGMENT_ITERATOR_HPP


#include <type_traits>

#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range/begin.hpp>
#include <boost/range/end.hpp>
#include <boost/range/size.hpp>

#include <boost/geometry/core/closure.hpp>
#include <boost/geometry/core/static_assert.hpp>
#include <boost/geometry/iterators/closing_iterator.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace segment_iterator
{


template <typename Range, closure_selector Closure = closure<Range>::value>
struct range_iterator_type
{
    typedef typename boost::range_iterator<Range>::type type;
};

template <typename Range>
struct range_iterator_type<Range, open>
{
    typedef closing_iterator<Range> type;
};



template <typename Range, closure_selector Closure = closure<Range>::value>
struct range_iterator_begin
{
    static inline typename range_iterator_type<Range, Closure>::type
    apply(Range& range)
    {
        return boost::begin(range);
    }
};

template <typename Range>
struct range_iterator_begin<Range, open>
{
    static inline typename range_iterator_type<Range, open>::type
    apply(Range& range)
    {
        return closing_iterator<Range>(range);
    }
};



template <typename Range, closure_selector Closure = closure<Range>::value>
struct range_iterator_end
{
    static inline typename range_iterator_type<Range, Closure>::type
    apply(Range& range)
    {
        return boost::end(range);
    }
};

template <typename Range>
struct range_iterator_end<Range, open>
{
    static inline typename range_iterator_type<Range, open>::type
    apply(Range& range)
    {
        return closing_iterator<Range>(range, true);
    }
};






template <typename Range, typename Value, typename Reference = Value>
class range_segment_iterator
    : public boost::iterator_facade
        <
            range_segment_iterator<Range, Value, Reference>,
            Value,
            boost::bidirectional_traversal_tag,
            Reference
        >
{
    static inline bool has_less_than_two_elements(Range const& r)
    {
        return boost::size(r) < ((closure<Range>::value == open) ? 1u : 2u);
    }

public:
    typedef typename range_iterator_type<Range>::type iterator_type;

    // default constructor
    range_segment_iterator()
        : m_it(), m_has_less_than_two_elements(false)
    {}

    // for begin
    range_segment_iterator(Range& r)
        : m_it(range_iterator_begin<Range>::apply(r))
        , m_has_less_than_two_elements(has_less_than_two_elements(r))
    {}

    // for end
    range_segment_iterator(Range& r, bool)
        : m_it(range_iterator_end<Range>::apply(r))
        , m_has_less_than_two_elements(has_less_than_two_elements(r))
    {
        if (! m_has_less_than_two_elements)
        {
            // the range consists of at least two items
            --m_it;
        }
    }

    template
    <
        typename OtherRange,
        typename OtherValue,
        typename OtherReference
    >
    range_segment_iterator(range_segment_iterator
                           <
                               OtherRange,
                               OtherValue,
                               OtherReference
                           > const& other)
        : m_it(other.m_it)
    {
        typedef typename range_segment_iterator
            <
                OtherRange, OtherValue, OtherReference
            >::iterator_type other_iterator_type;

        static const bool are_conv
            = std::is_convertible<other_iterator_type, iterator_type>::value;

        BOOST_GEOMETRY_STATIC_ASSERT((are_conv),
            "Other iterator has to be convertible to member iterator.",
            OtherRange);
    }

private:
    friend class boost::iterator_core_access;

    template <typename Rng, typename V, typename R>
    friend class range_segment_iterator;

    inline Reference dereference() const
    {
        if (m_has_less_than_two_elements)
        {
            return Reference(*m_it, *m_it);
        }

        iterator_type next(m_it);
        ++next;
        return Reference(*m_it, *next);
    }

    template
    <
        typename OtherRange,
        typename OtherValue,
        typename OtherReference
    >
    inline bool equal(range_segment_iterator
                      <
                          OtherRange,
                          OtherValue,
                          OtherReference
                      > const& other) const
    {
        return m_it == other.m_it;
    }

    inline void increment()
    {
        ++m_it;
    }

    inline void decrement()
    {
        --m_it;
    }

private:
    iterator_type m_it;
    bool m_has_less_than_two_elements;
};


}} // namespace detail::segment_iterator
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_RANGE_SEGMENT_ITERATOR_HPP

/* range_segment_iterator.hpp
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
*/