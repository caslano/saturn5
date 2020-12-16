// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2012-2014 Barend Gehrels, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP
#define BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP


#include <boost/core/ignore_unused.hpp>

#include <boost/geometry/strategies/buffer.hpp>
#include <boost/geometry/util/math.hpp>


namespace boost { namespace geometry
{

namespace strategy { namespace buffer
{


/*!
\brief Let the buffer algorithm create buffers with same distances
\ingroup strategies
\tparam NumericType \tparam_numeric
\details This strategy can be used as DistanceStrategy for the buffer algorithm.
    It can be applied for all geometries. It uses one distance for left and
    for right.
    If the distance is negative and used with a (multi)polygon or ring, the
    geometry will shrink (deflate) instead of expand (inflate).

\qbk{
[heading Example]
[buffer_distance_symmetric]
[heading Output]
[$img/strategies/buffer_distance_symmetric.png]
[heading See also]
\* [link geometry.reference.algorithms.buffer.buffer_7_with_strategies buffer (with strategies)]
\* [link geometry.reference.strategies.strategy_buffer_distance_asymmetric distance_asymmetric]
}
 */
template<typename NumericType>
class distance_symmetric
{
public :
    //! \brief Constructs the strategy, a distance must be specified
    //! \param distance The distance (or radius) of the buffer
    explicit inline distance_symmetric(NumericType const& distance)
        : m_distance(distance)
    {}

#ifndef DOXYGEN_SHOULD_SKIP_THIS
    //! Returns the distance-value
    template <typename Point>
    inline NumericType apply(Point const& , Point const& ,
                buffer_side_selector )  const
    {
        return negative() ? geometry::math::abs(m_distance) : m_distance;
    }

    //! Used internally, returns -1 for deflate, 1 for inflate
    inline int factor() const
    {
        return negative() ? -1 : 1;
    }

    //! Returns true if distance is negative (aka deflate)
    inline bool negative() const
    {
        return m_distance < 0;
    }

    //! Returns the max distance distance up to the buffer will reach
    template <typename JoinStrategy, typename EndStrategy>
    inline NumericType max_distance(JoinStrategy const& join_strategy,
            EndStrategy const& end_strategy) const
    {
        boost::ignore_unused(join_strategy, end_strategy);

        NumericType const dist = geometry::math::abs(m_distance);
        return (std::max)(join_strategy.max_distance(dist),
                          end_strategy.max_distance(dist));
    }


    //! Returns the distance at which the input is simplified before the buffer process
    inline NumericType simplify_distance() const
    {
        return geometry::math::abs(m_distance) / 1000.0;
    }
#endif // DOXYGEN_SHOULD_SKIP_THIS

private :
    NumericType m_distance;
};


}} // namespace strategy::buffer


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_AGNOSTIC_BUFFER_DISTANCE_SYMMETRIC_HPP

/* buffer_distance_symmetric.hpp
X5q7DUSxm+D9r/ekGDs8l/ZvYJyxa2/05Dc3sU40BrjNLawTjQG++FbGuRAb/hCcXEgf4X7zGTdtC64HNYXECb8B5pHeAre/jbHCjsBDwGwtD18CqrDr4QdAjfYF/hTMwJbbPdkLTMMugs9QG/918HZ3sM4LSYd7LvTkG+3jIk/evptjh/TYPZ489gjHVCFtNdKvx1mT2PXwquc5XrCbmzy5+yXGEDv+Mu2CZTomyzz5+hVP3seOv8oYgDUa/2usB9BRy8Mt4E0tv5yxBG21LfiMf9Bf7MjrlH3Dk5XaX/iQN+kX6bVw01scv9jRtz2+58v+oGMLFzV78qSOCfw1WKr+3/Vkwj89WaRzBx/+oSf3a38/8uQp8IiOM/ztCuZCx+RjT34AVer/E0/KwHztC3wlOFn9w9evZI40zs8Yny8oo3MHv9TCHGndLz2ZDu7XcYOf/o7YsMOrPTkKLNX+wot+JAbt1xpP7gPLtC9w/5/oeyExw3v+zFhpbPDL4H1sWevJrmCRtgWXgwUH0Ra8DMzBboG78W6vHrsIDgYCMg27Fv4+GJAa7NJQQHrnBaQBO9wmIGVgsZaBa/IDUoUtW1IG1GHH4JvBNxonfNJWAZnZh3UF/wE0UaYR/hQs17pbB2QvsERjgMeBZvUPPwpqqdsE/wi6aQxtA7I7aIsdhY8Fa3Ss4EtAV+0j/BzoiN0Mb90uID2wI/AQENJ+wVPAQG0Lvhn0xm6AXwTDtS689TYBKde68JFgqNaFp4OTsevgB8Eh2E3wl6BR+7VtQP64XUCKiL++Q4DzREAW9KEuPGmHgBRjN+4YkCe6BqQAO7wT/kAEOw6ftHNAVmtf4LN/HZAWHZ/dA/Jxd3ypnz2IYc+ArNB24df2Ckh30iM9AnLg3gHJx66Ft9onIGH1Ca8CMS2zL75BFDsaDci9oFTHGT6mZ0BGaHm4Yb+AVGIX9WZODgxIoZYppN5BAYljx+DxYKq2BS8Ec7Rf8LugHrsF3qUPa0Pbgqv60feD8TkAHwrsWrgJFB5MebhoIOOAXQo/AqZiN8PRQawH7DjcOAiNHR7MuIHumg7fCYqwG+Fbi4lf2xoSkN+DEdoW/BcQw26CA0fQd/UDl4EG7QtcOZQYDiEeeOej8I8dhdsczVioT/gUsELbhb8Hy7Ejx+IHtGhb8M1gOT4b4BdBI3YzvAosxpZhrH+wRMcZHjcM/xrDMOqCJq0LvwHCOj5w++OYP51HuN9xxKBzAZ8J8ilTBz8MRPsIfwkKsGV4QPYYTmw6v/C3oEFj/i31TgT0Mfw72jyJuthFJwfk1yW0peMPjyplftU//Ho5c6rxVDCuo6mj/YWfn0hb1I1UB+STBDFjl9YE5Poa+kiZBnjIOewJWnc6c3Uu60TnGp4JFmPXwwdewPGiY3thQOaCRq0L7z+TGNQn/AGo15gvCsjVYAF2I3zPxfRL5w6ecgk+sevhvFn40djg4WA5dhy+AzRrXbj3pYyn+oeXgRZsuYzj8XLGQcvAlXWMz6H4hENXMG7YETgGCg6lLnwFiGgZ+GXQHbsZ7ngl6xY7Cl8NCg+lX3CnqxgLTYdrZnOMYIev5hi/Br+HUBeuu5ax1hjgr0GxxjaH4xeUYsfmBuS7ecSn8d8QkPk3cnxpmZuoB6Zqf+HHQFR9wqfUU562auHpNzNf2E3wmFuYU8rUwe1uZe50/cOHg0JtCz4TFGkZuMN82qBuEdz7NuJRn/CTtxO/js8drGEwU+drAfsYqNW5uJO98y76pn7gZhCnvCwMyLBFxKzjA78K5ugYwj+BevV5d0AOBQuwY/BR9+Jf44c/A3XqpyEgA0Ctzgt8A2g7AJ/wKrCmv76HYk8=
*/