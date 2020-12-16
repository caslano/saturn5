// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP
#define BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP

#include <boost/range.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/iterator_categories.hpp>



namespace boost { namespace geometry
{

/*!
\brief Iterator which iterates through a range, but adds first element at end of the range
\tparam Range range on which this class is based on
\ingroup iterators
\note It's const iterator treating the Range as one containing non-mutable elements.
        For both "closing_iterator<Range> and "closing_iterator<Range const>
        const reference is always returned when dereferenced.
\note This class is normally used from "closeable_view" if Close==true
*/
template <typename Range>
struct closing_iterator
    : public boost::iterator_facade
    <
        closing_iterator<Range>,
        typename boost::range_value<Range>::type const,
        boost::random_access_traversal_tag,
        typename boost::range_reference<Range const>::type,
        typename boost::range_difference<Range>::type
    >
{
private:
    typedef boost::iterator_facade
        <
            closing_iterator<Range>,
            typename boost::range_value<Range>::type const,
            boost::random_access_traversal_tag,
            typename boost::range_reference<Range const>::type,
            typename boost::range_difference<Range>::type
        > base_type;

public:
    typedef typename base_type::reference reference;
    typedef typename base_type::difference_type difference_type;

    /// Constructor including the range it is based on
    explicit inline closing_iterator(Range& range)
        : m_range(&range)
        , m_iterator(boost::begin(range))
        , m_end(boost::end(range))
        , m_size(static_cast<difference_type>(boost::size(range)))
        , m_index(0)
    {}

    /// Constructor to indicate the end of a range
    explicit inline closing_iterator(Range& range, bool)
        : m_range(&range)
        , m_iterator(boost::end(range))
        , m_end(boost::end(range))
        , m_size(static_cast<difference_type>(boost::size(range)))
        , m_index((m_size == 0) ? 0 : m_size + 1)
    {}

    /// Default constructor
    explicit inline closing_iterator()
        : m_range(NULL)
        , m_size(0)
        , m_index(0)
    {}

private:
    friend class boost::iterator_core_access;

    inline reference dereference() const
    {
        return *m_iterator;
    }

    inline difference_type distance_to(closing_iterator<Range> const& other) const
    {
        return other.m_index - this->m_index;
    }

    inline bool equal(closing_iterator<Range> const& other) const
    {
        return this->m_range == other.m_range
            && this->m_index == other.m_index;
    }

    inline void increment()
    {
        if (++m_index < m_size)
        {
            ++m_iterator;
        }
        else
        {
            update_iterator();
        }
    }

    inline void decrement()
    {
        if (m_index-- < m_size)
        {
            --m_iterator;
        }
        else
        {
            update_iterator();
        }
    }

    inline void advance(difference_type n)
    {
        if (m_index < m_size && m_index + n < m_size)
        {
            m_index += n;
            m_iterator += n;
        }
        else
        {
            m_index += n;
            update_iterator();
        }
    }

    inline void update_iterator()
    {
        this->m_iterator = m_index <= m_size
            ? boost::begin(*m_range) + (m_index % m_size)
            : boost::end(*m_range)
            ;
    }

    Range* m_range;
    typename boost::range_iterator<Range>::type m_iterator;
    typename boost::range_iterator<Range>::type m_end;
    difference_type m_size;
    difference_type m_index;
};


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_CLOSING_ITERATOR_HPP

/* closing_iterator.hpp
r7JFlSUV1Khr3iR8R/3d/SeVfS3zaE7vYlx0Colce9HtQhtW9quon6CxCCNy8t1yQ+ucekuFK+KsZ1rd6671nexRYb6NPWwswNRZPxL9HIQpsa59W1zQ5qL12RxS8mlH7UMx6vioeox6BPR4rX4+zGazPZTY6x25iqKqxRWu9S7hE46p3drbZ43kp7O0zxMwh8hPtSM/arDT7e/6RrQ/exqnBS2PLAnQCvMRadQ60+AaWuX9W/1xXsJmyTXX+le0voeHSpqmk/JvLmP/s8HY12e/I69Kd4Hrtdl/9GszvjHXpsr0tH37u7nk5aAzL4vL3funhE111c30hvJPaXS9ueWVPbr85AyitKPDZnpzbHkVXYYueZWwvrp51f4+WVO29WfG8ip9Dt1vrecfc1ni64z/nnXGNkHT/cuKnwzZMupHq4bOe/uZmzyj34+vM36T1xkHGTK3lrlLvmM/OW6yztgRZsFOsI3YTfl8TI3IF4h8EI6uc642A/aGLWF/2A4Oh1nwdNgWToTt9LqfzAPhhBjrfiWy7lcGm8FLYHO4QPK5EOaIvQesggPgcjhYwp8KF8Gh4n+G+I8Xf6kf5mXu9dNT6qeXpNsbthG7dQ5b5kAy98qvcw67r6yXngK7wQHwJDgQ9oRT4Sh4KsyHw2ERzIMlcAKcC4fASngmXA7HwEvgWLhG4tkEJ8LNcAS8EY6CP4Sj9blemXPIvTG/zrnelVLvl0Pcseh6krkEYWPUU1epp27wBHgSbC92+Y6k3PtpE0re+R3JNZLulRLPd2AG3ABbwqtgK7Hr89QNlOMciW+6lGOGPq8p91KYquSc5zXPF7mZInchTIQF0v5m6fLIfQ60iVGeayWejRLPddAPvwtT4fVSTzfAA77GrT/HXGt2X2eW9eX/3Npy/XVlzBpvo9aW660rH+c15aauJx/B5DZiDfmbtHZ8PNeN66wZ6/VivVYcc534+K0RO9aH/wPnGCJrw3m035mYKkwNZhfmWczbmAQOo+ZgTsPMWBtfO47/4r/4L/6L/+K/+C/+i//iv/jP+v0n3v8vLKkqXVxceVz2/LdIM7Tu3Fx5/59oQa0P/slciy7S38fiM39l6GYtsLJgGEdd2+9qhNNubqECsqZfPwr1xb467y62u+QjJ5oPkT56+u0k/YOtdPqOhEk3Wn5v7HRzbeny/nVZSUXTy1+dLek7o5BsOHVdb3LJR140H8v6FPRt8rWwv/c85JJGvjONRtezPf/TfLHjLnTG3eS6tF+r3S5plDvScNRQo+LX31RLiB1/tSN+ibiJeS93ibvGHrfUTlPyHon/iEv8W634o32wCfmPtOOt6WZabt3Y2Y/L/bHzUavz0fhr3y6SfkjSdybsLL9Lunt1ulK5x1D+nOaSfsxu7OwHMwOx87Ff54PL3Kfp18LeTh9ySeOgI43G17M9/22CseM+5Ii76XVpT6PaJQ1jli2Nvl+tjl5zSSPVkcax1VFeosu9yhH3sdVRpD1vdUkjV6ehh7omjdd9I/3FJf48W/zHMg7NSHK5x+h49TDXpHyPjNzDXOIvnKXP1RXM4ktMxN/ke2Uv6e95bcw0Y0Xlfv+uTna5N0Xz1dT7t9qfclJkDGoreZJoXPKj278RcrmXRfPT2Hu9ykdHyYfRypEPWwac9VHjkn5NNP2mzgcc9bG1teTDEY37/SEr7HJ/jOanKXOH8fb7Q+EJ0bzEuDKO67LZJR+10Xw0do7huC45mdE8OBKvUw85KS73yWj6TZmHOOphb1Y0DzGuiKN91LrkY7+VD+Jo8n3S0T4KM8y8xIpGMlOnv+Q2c7mn6vw0+p7quC6FKfZ8uI8fe13SP6TTb/J911EfB1M=
*/