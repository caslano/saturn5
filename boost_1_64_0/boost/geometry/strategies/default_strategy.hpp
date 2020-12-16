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
kKSH4k5yNaCJ5KxucpRbIJ0p3rcGKXY1KUpN3CeFz3Um7o2NiuGDyPFQF29/VN14AOGFPat/G8/TK/XhWRzGtNM7l6cYCpaRI4VaaF9dRY1sITRqTsMakAWDwUKRjz3HSxbkcXiqMVEG3e083zKfvxfBc1yxpXQnSPdh8YeOxLgQTYFYb0fKsu5ssmhmmMHBSTC4hQWDV/z1hkwP/x2gv5yGTE8/+htKf+Po7/m0SZvP0KQUnbzoVluJcfLUG315ha+2t2uWUC6zBB/WZ3MtpQs3d9ltev6bdGOOa4vSkFArvEGW6LMbutHjqzXBvI6UeiPcfu7BTuSQw9oNmY+QOzgkLpLGmlVdzFaohVXP7myESVa7FodHuxaHyTu3xbJGXOwuSnvc1NrJ7hy2x0mt7a81xTKX2ssKRySfZxRyMXZfEo+TMrXD59cdaaO5fhDRGXKLUa0cUaqVV9mqlQ1n3DC3DAvBsMpv4SKWV4i6k3GQ4BG3ubNszcsV4vSNC9TR4IetBJ5z7HFIrFpXKp7HahOAhCdKWlb7wJGy7rAg5ppTrq/5kKMsX+Al6hoRmvjD7Sw0UcKr8HOM0MSS84gmn4g5SEGLbcZCscpWsS3XVn2h8KxlrZnRSG9XynTtBXYxq8TpoZnsJLn6qeTqVOSq1J2rt86lXN3HqS6XiEfNlhNIQzjmeomZkyrmwxQzdin55s6Jx0t4T01EcLBtE+954k6vvDLroEU6xlEkYQYRO6q5x4axMxo/pgG/c2wrv2ULPMEt8gauv83yyN7Q7ed4POpmaG5JR46/eqRNyq2fEcul3Sse12oHD9StnPpmp49btXRxgrtHuYdtsZG+0vlI1RcmvYewCI3kY8qRu04WVrnrOqnl2VN2GPRyPdXh7EqjRtdHmHzzgezkWbm3vq76zRAYwfr6g4poH7/pOfk+L4SuzcEXyHNezBFNGY52lSGF3KcUYob77pyk3rRS9ZLHO3tddzjLhFMVcKNNH+y53oaxCdGxbOpR//383kSTsBO75Wu2DHQKDmq9zHrDGDXzTN1sLc0I9o4NYJ9hyT75Ma4NI2HoUDHrraaKiU6tF3H1Qg7M60aHStV3P0bnxARk6I31oQEVXi9cK+dDxdl7eNdgdJgfjlp55CZ9NCgS1425iUD6lgdnyvUGcrZjEM9FxpJVlPVyWFsHP7f52HS7tea4WquTyyvNdHD4MvpJxRgusG8A+dmnKbpj/3r7jY796z+pl1LEfMalxSwxUSts7G0en48X08YXEZr5aGwHhPZbgv1cZxUTRKVKJQ/4xpd0lu3rff2v4Pd/Ei+Mg9SAsolP1rPJ4tHR+gAyVKJr2CEtdVqAb6kgoZ9DyjPYST+z7CBSWg2nFPRnNn1GAaf+7UbLI0JjVm0nFYxexIsdEFBy1He5JFjScplICbzUbOnjEY0rvRTgtWlaNfLp17SJ5EBqfniqTd/9De6NPmGkFuupcpW9bVefL1Iibq/6PD1w7N7J+Us9Vy9iBWEQp8ET5GlCeBKBmukUD4zN5xshY4LsQIjqQu3zqMMHzJkvkUjN3Y22SE0F5834DkY8fe3ICnJz3EjS6HUOdhCMzdfpTHKkE7D5Pa0Wz2FG8xca92AOc9pyM4eZbuYw0al665+n93LvCPVETEPrEsR2GeX1iJ4/O1zjnj+IZmJ930XN8Wyl3gQeTfV23eVrtzpxi5UgJMs7fc3SgQLJsttdEZmqBK8mW9t8HT+P3L5869ilifs5+C7VuN9TTaZzlNCQX1qpeAbEsWZC8grSSBNV3wSZnLJX4xAakpg1XdAHU+CCpoCk4CbmXoAZAZ9FQiz+KxFNkphCLAxOjSZSJHffDJCLXHo=
*/