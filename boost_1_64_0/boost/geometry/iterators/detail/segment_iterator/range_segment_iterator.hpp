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
E827TTRfNtE86UTzuRPPo33XrivqtAP3pZoxypQvnOd3Vwx93LQiGJOM0Rg9ffPifMQ0G6OXG9JcIdgGDoF2LoTuq9B93jF0D2tuxaPwDLgTjoaPwanwl3A2fBxeAH8FL4JPQnfuzF65f5Pc986d+bPmarwKczUXaBx8HRbCv0rnbbn/N1gJ98Ma+Ba80rku/+h7BPy+j3+ekn9+K//shcPh7+FV8A/wJs2F/abmwN4mexpbTR+31z+xY6v/pblW/4Z94XtwJHwfjocH4TnwQzgXfgTDMCWVBgBMh46O+oThXB+dNtiLsB08XsddYHvYF3aAA+GxcBQ8Do6V/RmwI9TYc/XNOm2Sfc3mkOxRuvkDTIXPwg7wj7ArfA6eqLH2em76NBM/9y2ao/Ntxft3YBb8rsJrKxwE74YjdXwW3Awn6rxJ72nqn1N/Y0SnLJLe05SuNLfrVTgUvg7PhH+FBfANOBW+Cedp7t1F8O/wGvgP+BX4T/hN+Da8Hb4D74Lvwh/BA/AR+G/4U/ge3AUPwl/BD+Fv4UfwJZjG878Kj4EHYHt4EGbA1BTiC3aCnWBn2BF213EfeDzsD0+Ag2AXOAp2hWNhN1gAe8BCeCKcDk+Cs+HJ8AJ4ClwCe8NG2Beugv3gF+Fp8MswG34d9oe3wdPhFjgA3gsHwgfhYLgD5sLH4VC4Gw6He+AI+Dw8E74KR8E34Bi4H54F34Fj4UcwH5KmQ+NgZzgedocFsB+cCEfCSXA8nAwnw0J4PpwOF8IZsBbOhI1wDvwsnAe/BOfDtfB8+E14IbwdXgS/D0vgb+Bi+AKsgPthJXwHLoGpaZTH8DhYDTvDctgLhmE/WAqHwEvhMNgA82EjnAKXwdnwMngBbIJlcDlcAi+H9fAz8DNwBfwCXAmvgtfDtfBGeAO8CW6E6+Em+HWoORvqU8Ku8qd3zsYkjbUvVP4+B3aH58I+cCocAIuUr6YpX02HE+EMOBMWw/PgLFgOZ8MaOBeuhvPgdY67qifUFwTX+NQTwzWnaIT0z4S5cBScAUdLdwKM3HMWXATPhpfCfLhC1zUGW30ypC3pecdg/yjFKee2wzPhgyqH7lc45tu+A9O/Ye6n/CLdO/efj05PeDE8DZbA/rAUDoIL4VhYpvJoETwXVsAwvAReD6vgN2AN/DZcCr8Ha+FmWKfyqB5uhw3wx/Ay+Bi8HD4JPwP3wCvgH+Fn4SvwSrgProLvwKvgv+A1MB2/rIat4bXwePgl2A2ugT3gl+Fp8CtwAFwLB8Eb4Gh4I8yHt8AZ8JvwXHir4iHLvmeSNxWOvfjdWeH4bYXjdxSO31U43q5w3KRwvEPhuEXh+AOF4w/hl+Hv4Nfh7+F3NZdsG/yNyvFn4H3wCbgT/krh92v4G7hb5fiP4LPwPvgnuB3+Bd4PX4cPwjfhQ/AA/DE8CHcoHH8Kj4U74YnwMXiy5gL2hy/AkfBFhdte79yywdG5u9nN5mZ2SXXSazfYEXaFxenOvOUxmL3fSE08ZyBujoDv/ID/67kBH3wj9X92foDP3ID/qXkBGTenfjo3IIC5AVmE4woYPzcg4byAI54TcDjzAYbyHEWYJsw6zHbMXkzoltRQN8xITDGmArMSsx6zDbPrlk/H6H/69+nfp3+f/v2//qVjumj8f1XlwrK65bUNS6cVDCqvqgoNYsx+G6etq79jfcfsFxVOn8pFxhykOmshy/Zbm9Npn7bmJSWvsmT2hDklRYWz5zjfhgPX3CfbqXdJszKvvGT+sJwzS6aPmzYxWM1B0ixP0fqscZoT58+ZOH124Yzps0MB+7e3tJ+R9oHbm2kHrHe69IpU1W/z+nXGhNnFJbMmzi4uLAjan24=
*/