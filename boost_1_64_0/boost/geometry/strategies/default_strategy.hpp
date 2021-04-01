// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2008-2013 Bruno Lalande, Paris, France.
// Copyright (c) 2007-2013 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2009-2013 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP
#define BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP


namespace boost { namespace geometry
{

// This is a strategy placeholder type, which is passed by the algorithm free
// functions to the multi-stage resolving process. It's resolved into an actual
// strategy type during the resolve_strategy stage, possibly depending on the
// input geometry type(s). This typically happens after the resolve_variant
// stage, as it needs to be based on concrete geometry types - as opposed to
// variant geometry types.

struct default_strategy {};

}} // namespace boost::geometry



#endif // BOOST_GEOMETRY_STRATEGIES_DEFAULT_STRATEGY_HPP

/* default_strategy.hpp
xa7LJsBScF159f1bMxqOpz7C7Qa+lqFRWoCxRISzqr72g+v81FlGWYpTTxkigFG9Z32zQdMy19GFJ6oG2xh1Z91RJmWtKS+Y6mxZgThrThFuWw15PCQkk/qqkvuYo6lxV1v6afvdv4bHPKl70q+u2u4xqVLGvQfVxHi0289csbEA0l0aNpr4AcIHddEF90gKMVrFSZO1AJW0CP825xWCvnvkvvpHvT/SW629+w6BUvbIrv9ARBHho1HAq4P9eBxWK/vXUsSw2gJ8IJT8eMZMwww09kbtXnPf9LpwvFpCVta81lbp+DPqAve6KGwuRs+poirF6OBw7YnLDlsQikXK+ac0MMMZj2zVpKf0udEfjvESm1WN0eHJle5ZEFwzjk4Esa10QJOGdFpQ2jx0ivc6breL/oSQDvcT5BPAEXsW7pGDqnPPrPpD874n+iJKidCDPFu8RAkLFg1zF4oRwTX8e0jB0uTUkORfez2tB90ZxX5u9GdFmv94U6CCf69BSYdaSH0kI5QJ2Gx++TiqX/AL+ZCle5sHKlfkZ5HpKF+9JuA8956BSa15gd34Sg==
*/