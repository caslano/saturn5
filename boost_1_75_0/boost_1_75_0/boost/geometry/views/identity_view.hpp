// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP
#define BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP


#include <boost/range.hpp>


namespace boost { namespace geometry
{

// Silence warning C4512: assignment operator could not be generated
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4512)
#endif

/*!
\brief View on a range, not modifying anything
\tparam Range original range
\ingroup views
*/
template <typename Range>
struct identity_view
{
    typedef typename boost::range_iterator<Range const>::type const_iterator;
    typedef typename boost::range_iterator<Range>::type iterator;

    explicit inline identity_view(Range& r)
        : m_range(r)
    {}

    inline const_iterator begin() const { return boost::begin(m_range); }
    inline const_iterator end() const { return boost::end(m_range); }

    inline iterator begin() { return boost::begin(m_range); }
    inline iterator end() { return boost::end(m_range); }
private :
    Range& m_range;
};

#if defined(_MSC_VER)
#pragma warning(pop)
#endif

}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_VIEWS_IDENTITY_VIEW_HPP

/* identity_view.hpp
44ezsHShmDU+LCsT0K6S7F1oXMXUFVOlrq49ueglyF2MzBUyPV9zB4GvRNNew8WM4LnzUp3LoSW4lVe798iuB9tCo0b6M9ekxdErOQLPtpHzRJhZ/pqO0BWvYC3n/Zd8lcfPEnf5pAbrfYsprJCdsY4DA0GIk4T4R5eyA1WPhB16UJvcnVlkOSNAg6cowH4Llhl+TSC+XGrvvpBR8avy14IlvcFYpACIjwH9zVEeS3KudDyGIXGKQPOzNPkUZv/oWVyh86mMTMRoLkT0Rh0LrqJRA4mU06S2MWqUXP3u8GUkZcuoNNqgsqJkeL82jb2Lp2Fqpjvgq1tB9V/0Bfpph24wSM1g0zHzIiD87SfH3dvVZRQPglH8fB3HjcuEckzN2CsS10QaaSVaKxYmpMIdsdiASh1NOdHqXe7NKSuSe5kYcpqxfHzCXc25y/3jI+AzcjygJ+CwFOXON/ERi/1Hec5m60V17HQbKkdyrNGtoYm3ENVo055pXTZ7mCEH2WjZg6UyTmln0d5SZrrm/k/DcbIrD8P77H0fjvOWmYw+7QcGkIdKliwiMzhTVxIitirGolHj57Tu1iG83zJhMMb+UyetUEj3qLLlpXSWfeWj/oucGvG+BfuzF77puDWYKbefpC5f+jwHN7qtjJdkJeBNBmMJytt9t407+k5cP+XReP8GvDcQTXoQ4riEMbShsIQO23R53k2QGazuhTEh
*/