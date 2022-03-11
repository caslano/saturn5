// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_RANGE_SEGMENT_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_DETAIL_SEGMENT_ITERATOR_RANGE_SEGMENT_ITERATOR_HPP

#include <boost/mpl/assert.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/range.hpp>

#include <boost/geometry/core/closure.hpp>
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
            = boost::is_convertible<other_iterator_type, iterator_type>::value;

        BOOST_MPL_ASSERT_MSG((are_conv), NOT_CONVERTIBLE, (types<OtherRange>));
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