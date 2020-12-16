// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP
#define BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP


#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

/*!
\brief \brief_macro{linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING, linestring} The
    linestring may contain template parameters, which must be specified then.
\param Linestring \param_macro_type{linestring}

\qbk{
[heading Example]
[register_linestring]
[register_linestring_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<> struct tag<Linestring> { typedef linestring_tag type; }; \
}}}


/*!
\brief \brief_macro{templated linestring}
\ingroup register
\details \details_macro{BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED, templated linestring}
    \details_macro_templated{linestring, point}
\param Linestring \param_macro_type{linestring (without template parameters)}

\qbk{
[heading Example]
[register_linestring_templated]
[register_linestring_templated_output]
}
*/
#define BOOST_GEOMETRY_REGISTER_LINESTRING_TEMPLATED(Linestring) \
namespace boost { namespace geometry { namespace traits {  \
    template<typename P> struct tag< Linestring<P> > { typedef linestring_tag type; }; \
}}}


#endif // BOOST_GEOMETRY_GEOMETRIES_REGISTER_LINESTRING_HPP

/* linestring.hpp
A9tOLVf8NS8fpy/t/iAwThSpCXIzkxOeiAqEx/85h4M852u7jQ54jikWki5Dg/Q52Ddl4nhS0DKBnf++TPDMcmWC55QtE+a9xLoW5eP1jd22l4kXxSFknPL8ysKgIGUh738oC0PL9aPIIcpCQcvycbk6jTY6IC6BbebstHLxwf4F20zM//s2c3ban7eZvXTcfE4PybmZh9SAc6DcC6bxyZ/RklPhp06ZPkFewXCBLK9grrDvZJ4mY4Rg56G/LW6HWRpX9auO331ueDFhkthPQzom5kMsvzOiTTrMeQczQuuskxwS+UpXU/VvMM8m91nPLX0HMQY7F7qXpESeN84KDM90PdeZOifmfS3nvpEXGDs+h9pqzkv+87sX7XF21Lt+a9ghzqHv5eyl1E2Uj2qZesh5//VuuXzQ5WGyI/fy3ClMaUKsW6vb21RmB+V7tpxgytTTKRWZU5YLs+nL+qvDZDxLheFwmL2+9p4TZucmgRm5rKsVzNadOEHCqm7qm7tv7hL5O3bduIOOrfsZN3XMPZF3iHyC95+W/50M5j3PSjH/1FVF773JNn5k+J9Pbsrli2L2hJ/Zlebs8oj3ZW2Y1GjOelYN1We2L/q5uGnKjotUKON+/qaY8vmJ+FvZnNv/vcgtVbZc74gc7XeXwlViNhK7e8TsKZfsd6XM5DAjPE2AYj09Y8PiYj39YsPCnPfijBNFyTsetb8M+2ds+9E5sR4yza99CbhboRvlvXtyxdbWgs3TzdxE7WT73U+RyFz4ShyvHWF/x5Q/Jf9ql9E7Uaona5MuSU/eK1b3yVll5LFGDryTZ7e+SN6k737uQm3EpAT7WjZzZvvVJf6ZHKIeqZtLzP6D8yLPl3L5WIKUsUIafS2Xjv0mIg9EPidygdjf4LMvDZZzd8EvYr5Ay6TjvlFgmdR3up0P22b1VGanhMgRZi/EShq0Zy78jo2+IvT7NOKDLPERvYnobRA9DTNpPkGeSdomBK7BnGrve8AAvY8sy+lLxP5CXpU7CR7w+s0suuMk6B0Gb4n7alaMZe78Vj9r+92znTcz37lLQtP1qNipYrmtcN3bp/b8vgn8QOzUsSpZlnlntqO0nRe2TSz9/VkF2n57vWTzByHXsgL3MnbSs9/0jOtxcCRlOftDTbOA61m4uT1nWqj2Xt00MPG/RuT2VkttS/b5yp6WU8d+XXM/b4HIPa1Ltc0tKH/niLq5yNwNcZXIvazOLm+pG799CIONm6uYI1ws7+mniRl2ffsHpsmnufxy6gsHp2H/Mb/+fYrTv0t52Cf+Hfczz8e8NE+vF/OOVmu9w2h0dcl3tpOJNfS6Sdl/ROylWQn0uC3I+xh9T90x0cdnKQct+P0cfB61C+X1mcGKlIPAOoYsdWyfrz6Z+lVQ5j6EaUZP76FQf4gHeiYeAeVogW4g76/lqJOWo4wjIcrR1CmUpKDlSN1kmnKULXJiqHKk9puaMjFA5GpWR5c3VDlSNxeZstdV5EZWX2IVohypm3mu7qXlKGQZuV/s7g5ZRkaK+S0uyojqMXIQvfmu2ozKUk17MXWWfVN2TvZsrvzCfy07fcVubUvbDFNuWqD+nmLKiKi7KnRXN+vhH5s24/9WdtID+l7/uASWn2Pd9H5g+7xyOALa5Wf3xyHKzxW02sHbIXXTxoxZzojczhNQdjSffhKz7h4tS+q2Zahyo+aXijwM+Q+RW3vKlBnTV/+mz9Z3Nuq+g+TvrVIufOcHTJg7fSaC3qHrvydqZo7ccqNmWWpWx7lfSc0SNe7Nj9r+NyPd48w7gyGiVw/3EWafktxllOrMXSZMKSgsbf+mf2Lb3+Qu02eZ8eKLYj5IzJMS9R4lDd9E9Xs=
*/