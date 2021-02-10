// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2016-2018 Oracle and/or its affiliates.
// Contributed and/or modified by Vissarion Fisikopoulos, on behalf of Oracle
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP
#define BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP

#include <boost/mpl/assert.hpp>

namespace boost { namespace geometry
{


namespace strategy { namespace envelope { namespace services
{

/*!
\brief Traits class binding a default envelope strategy to a coordinate system
\ingroup util
\tparam Tag tag of geometry
\tparam CSTag tag of coordinate system
\tparam CalculationType \tparam_calculation
*/
template <typename Tag, typename CSTag, typename CalculationType = void>
struct default_strategy
{
    BOOST_MPL_ASSERT_MSG
        (
            false, NOT_IMPLEMENTED_FOR_THIS_TYPE
            , (types<Tag, CSTag>)
        );
};

}}} // namespace strategy::envelope::services


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_STRATEGIES_ENVELOPE_HPP


/* envelope.hpp
itubRRCFGiXFnVpHHJBxPR5lgcIkUDLFn2F8LY0jloOMp/D1WFuQePy8nkovouvy4LmQzVmTsNQmxHx+qG14OGfWjXO/xGZNVtsycylMjN63YpmW68LDgk9FMo6RiedZIBZAe79BgtCeJEhMrU2pQstSwu4fge3TNAXyBdbV02BbmWqgpGDqszqyLKhgxFNkgdPUiPMvD5KXJQzOEEoBlewmi+L5UDy0IridyjwvzyaXikF4tKWsNJBlZkXWZTOCT8q85Bq+JufWC7aeiN+qgK7Mc3FAjsfVFE82sf//Gunut69CxyqnCVfXyCY1VDWuPNGGUB8LX2Oe7/mn3ef7y9V40YLXWS4WbSI5SQcKKbUvOf+MkRsbWKyML56xawgWI6qxT6kWPaWOWkhbc+gR6pr+Ys6jPOcDUqTp9OheCJoYIRszKRJBD3HoD3u7njhcQea+x6kZzwteWR5Wtsa2hTSA6IAvkr3sMUxujkU+oE14PkAyQNUNyJYqEcAWOtKPTg7e1SOhlFMQxxFxyljhtjA/zenEzwwkcIsepQMc94bdd4UjtAXp7+GxWgOLKA4czhBEMDnSm1qEHFPd/6q5Xu21Fja+edOGpmgZtde1DAVrMoCANYPTbVLhemOEOvNm0AcVVBlDkowTGHBG
*/