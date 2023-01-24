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
QEtDs+lntxB4p5CD8hNjN9uZ7Q/BY6pI/kebCPwZKUzhEZWXgyJ4pa4YqVEY1hp3Ym3J0ePjz5BYjQuZJr6w2Id5JC0cJwMyTqoCyhNhkX8qKEjpwS5eiHx5EGaVEudlTXj/y1pl0bOMd1ev4AcTlOLR3Am/pcaj9kIjeHK0MMEp4eHZ7eeDsWQ0/MZtQUFTL0F//AA7dsm9e1eUG+bd9RWxfbyA066tGLtfuF4fJNDvBdFNb/ju1azWbHhTIXdmg84OnZd+C6aWo8E/mlbaxq7bj+rL11radwRPD3PlG1AuVZROI6Hp62ppd6Yt2+ZnvRDe3dWtn2oixwBM+HoOQz4yyFN7o2/HJJp3FbkX3zDyFIxa/weDZyboJjgmWCYEbm19qO2fSwjYUVlDS/t5NpgKXhior7TFOigiQCthd3oWGPWEBhizaOoF+O14Bniz6I4hmAUvDXBW8PlQj0KuByECcj9t+zhiTEMozlFW8O7LWl5uqDRgt0NrHoQHnfttLXCm8L2ybExtHw15d9vBqsGYFwK8PQMJ6LaUct1E+6gyIWjHaP6hElIYp+gSBBGhQSFn0eTvUPaVLme48+qFF+q8MHyj0gU4XuGwUfO/nvPvisJ81UaSdK0gptysoI+FqxvfDDsvN46P0AHZz7egvheMOu24deG3ht0Tt7RB7LlxTVfJeNPsMxvB5yzS9GVsoRz+itO/FOtUEp9d
*/