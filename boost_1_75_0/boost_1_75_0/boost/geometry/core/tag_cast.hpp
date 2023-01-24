// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_CORE_TAG_CAST_HPP
#define BOOST_GEOMETRY_CORE_TAG_CAST_HPP


#include <boost/mpl/if.hpp>
#include <boost/type_traits/is_base_of.hpp>

namespace boost { namespace geometry
{

/*!
\brief Metafunction defining a type being either the specified tag, or one
    of the specified basetags if the type inherits from them.
\details Tags can inherit each other. A multi_point inherits, for example,
    both the multi_tag and the pointlike_tag. Often behaviour can be shared
    between different geometry types. A tag, found by the metafunction tag,
    can be casted to a more basic tag, and then dispatched by that tag.
\ingroup core
\tparam Tag The tag to be casted to one of the base tags
\tparam BaseTag First base tag
\tparam BaseTag2 Optional second base tag
\tparam BaseTag3 Optional third base tag
\tparam BaseTag4 Optional fourth base tag
\tparam BaseTag5 Optional fifth base tag
\tparam BaseTag6 Optional sixth base tag
\tparam BaseTag7 Optional seventh base tag

\qbk{[include reference/core/tag_cast.qbk]}
*/
template
<
    typename Tag,
    typename BaseTag,
    typename BaseTag2 = void,
    typename BaseTag3 = void,
    typename BaseTag4 = void,
    typename BaseTag5 = void,
    typename BaseTag6 = void,
    typename BaseTag7 = void
>
struct tag_cast
{
    typedef typename boost::mpl::if_
        <
          typename boost::is_base_of<BaseTag, Tag>::type,
          BaseTag,
          // Try next one in line:
          typename tag_cast
            <
                Tag, BaseTag2, BaseTag3, BaseTag4,
                BaseTag5, BaseTag6, BaseTag7, void
            >::type
        >::type type;
};

#ifndef DOXYGEN_NO_SPECIALIZATIONS

// Specialization for last one
template <typename Tag>
struct tag_cast<Tag, void, void, void, void, void, void, void>
{
    // If not found, take specified tag, so do not cast
    typedef Tag type;
};

#endif // DOXYGEN_NO_SPECIALIZATIONS


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_CORE_TAG_CAST_HPP

/* tag_cast.hpp
/3XlOdYGuydPvO6i58TZ82FH9RWYjfX6Drb5XL5uc1i7v8xsndZJisc29nLtjrZ/avPdsd+gY9T/Nl1gfRGt6wi0uTDsj/6Ocjyeev29yHQfwO7qqzAX29oH3zfY1/SvXaxOJjBb52yD9oNDsZ0MRl3E4VgdXcq1fzo2dNuG9vb/2HsTgJqz93/8fRWVNcuYLDMq+yhCgxmMkBShMRnrZElkxpJlbDESKkLZs4dQtqIQQgaNSXQRsoeMEC6qG8r5Pc85597ed6t385nP8v3/OzOP23mf9zmvc56zv89znuf8G9IRxmUcy+1OsbG5zxRdnapit2TzbpKq/Eh2v84jO6CNh/N8YJ/HsWcZ9Legh6xtYFtfn6mk9wlDoZ0tfZBHAqCt+d+BsFswRt7MJdOwvaXlkF+gvY2V5xC36aEl4ssBX9XPdr3Ko+POVt7n18IYuOIJto08shP+Lm07lIIffv0eufu+QC3LEAn52An52JatpOMfto2YFzD+7Y//xz+gQ/tri2XCPDx8m0N5gYR1gve2UqBt/vkunyw7EE/g3e3/ND7PQwcVX2dsjlbz1Wf1LjVf4Z1QoPIlp1bm/i+5v/k9uLhvwegMfw+uVtz3YMt/uTzPdwc6hTpZ4Zp/zd+Ji3eAyKPDZK0L3Teo1biVJG83tJ8reT6vFyHPk+l+A9PY7NqILOluRfNRkrzd8x3zCcl7prFnwTRwrwLl
*/