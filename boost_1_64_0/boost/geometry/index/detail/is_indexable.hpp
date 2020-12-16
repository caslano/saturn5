// Boost.Geometry Index
//
// Copyright (c) 2011-2015 Adam Wulkiewicz, Lodz, Poland.
//
// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP
#define BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

#include <boost/geometry/core/tag.hpp>
#include <boost/geometry/core/tags.hpp>

namespace boost { namespace geometry { namespace index { namespace detail {

template
<
    typename Geometry,
    typename Tag = typename geometry::tag<Geometry>::type
>
struct is_indexable
{
    static const bool value = false;
};

template <typename Point>
struct is_indexable<Point, geometry::point_tag>
{
    static const bool value = true;
};

template <typename Box>
struct is_indexable<Box, geometry::box_tag>
{
    static const bool value = true;
};

template <typename Segment>
struct is_indexable<Segment, geometry::segment_tag>
{
    static const bool value = true;
};

}}}} // namespave boost::geometry::index::detail

#endif // BOOST_GEOMETRY_INDEX_DETAIL_IS_INDEXABLE_HPP

/* is_indexable.hpp
usJmsBvsA3vAs2FfGc8mw8GwF1R3Y8LJsA+cLu7M5x2q5nkr5HmXyvMuk+eVy/PWyvNWyfNWy/PWyPOukOfhTsu11LXucg2/6nljYDQcC+NEb/bT5eK/qUM/PVHa3yRpz5OlPU+V9pwq7XkKjBRzM9zNEm60Q7jnSrj9JNz+Eu5ACfc8CXeA5BPmWv7sknCHOcifMMnfJrAbjIA9YLTkczM4SPRyh6WsCaduSXj6Dku5sy8GDoZt4RDYGabAHnAoHA+HwVlwOJwDRwT2l+vc+8te0m/0hvVhH/G3DlUp/l4Sf03gCvEXK/kSBxNF30b0U2A8zIAJMB92gMthK3gpbA1vhklwC2wLH4Ht4E54FnzW8KfLU9b0whYO5XmXlOfdUp5bpDy3SnneI/35fRLfrRLuZtQhCTda5I5RDzdIuE/gLg7ugN3hTpgKn4TT4FNwGXwGroDPwk3wOXgvfB3ugLvhM/AFuAv+Hn4IX4FH4IvwKNwHj4t5kBf//vSzztQ9/Q9K+h+S9FdK+rdL+h+W9D8q6cdc178iCfdih/rHO3t5B9gEqnclmYeJgrNgU3g+TIIFMBqWwOZQz1+s94Ufg6pABc5fMLek3SVrd/Z5DuaatLvUWoZXVEt3FbV0V1kLdztQ+8XdW5KOaLhNuUKPu5bwZdgJvgrPg6/BEfAPMBW+DjPhG3AJ3A+LRF8G/wgvEf1lol8N34RXw7fgdfAv8HZ4AP4O/hXeBw/CJ+Df4HPw7zqdsnZH0llepRzG6HLgd03t3CX53fGzusvwBNRvcTffoX6fkPr7L3gu9Mj4xAsnG1o4AwbDWUov9TtI1mHIOhDCVTJ8gpyz3o56GgO7wHZwK+wKe8BBsCecCHvBmbAPzIZ94YXwHHgRPBeugv3gGtgfXgHPg1fDAfBaOBBeBwfBm+BgeDMcAjfBFHgnHArvhsPgPXA4fBCOgJVwJHwEjoI74Wj4FBwDn4Fj4T44Dr4Mx8M3YAb8K1wA34XXwC/gtbA+eVMBI+F1MA5eD1vCbNgZ5sCBMBeOgUtgJsyHy2ABXA2L4G/ghfC3sBjeD0uN+MJl8Fl4KXwFroF/gFfAw3Ad/BZeCb+Hl8N4ymwlbANXwU5wIhwHJ8GpcDI8H94I58ObYQ68Ba6Hm+AGeCu8Cd4O74eb4XZ4B3wO3gn3wi3wz/AeeBDeBz+DW0W+eYJkrYasITHq1yA5m9r4PYu7XvB52Be+DKfDV2AJfBNeCt+BW+AheC98H24TfSX8O3xBzP8GP4J/h4fh5/BjKb9PYDj8DEbDz2FH+AU8G/4TDoFfwwz4LSyHP8Bfwx/hDTAYeXArDIH3wEbwCdgU/h7Gwj/BlvAHeBasT14kw47wNcLpDTPRnwuz4FCYDYfDPJgKC+FMWAQvgOfAbDgA5sPBcBtMgXvgUPgWHAm/hKPgT3A0DA6m3sNoOB7Gw8kwCU6BveBUOA1Og5lwBsyFs2AZnAdXwQvgNTANXg8z4APwL0Y9gcXoH4clUL2/6G/+tA2pB4ac2iP1oNgj83IwBS6FY+FF8ClYLncfr4TH4Gr4M1wD6xntAjaGa2E0/DVMhFfBtvBq2BlWwGR4HTwXXg+Hwt/CifAGOBNuhAvgzTAbboIl8FZ4ObwNroN3wA3wTvgAvAs+Du+Fu+F98B24FX4AK+FR+DA8AR+BoZTP4/As+BTsBZ+G4+AzcBrcDdPgC/ByuBeugS/BCvgyrISvwcfgH+FO+Cd4CP4ZfggPw/rBtAcYAT+BTeGnsBt8G/aBB+B58G9wFHwXpsH3YCb8UI+fZW0AjEPd5LWOn2OCKBcYB5vCWGh+B6sUf8XSnwV+B3tb5pUOwGT4LhwI34Oj4SE=
*/