// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file support/map_type_by.hpp
/// \brief Metafunction to access the map view types of a bimap

#ifndef BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP
#define BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::support::map_type_by

\brief Metafunction to obtain the map view type of a bimap indexed by one of the sides.

The tag parameter can be either a user defined tag or \c member_at::{side}.
The returned type is signature-compatible with std::pair.

\code

template< class Tag, class Bimap >
struct map_type_by
{
    typedef typename Bimap::{side}_map_type type;
};

\endcode

See also member_at.
\ingroup bimap_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace support {

// Implementation of map type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    map_type_by,
    left_map,
    right_map
)



} // namespace support
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_SUPPORT_MAP_TYPE_BY_HPP


/* map_type_by.hpp
e73HRxrEBd7jmvldyb1G6+9V/D5R7VRhx6wnfJl+eyAJLdYTnqHrSM+CPWE+zIZz4ElwHpwI50P8k7YiX/2LVf9izHeAtK34h33XeshFan+M2nevhzwYfzvD42AWHAmHwFF6v2bTfyV9eeI+nd+PqvtFuv5xDZwAa+FkWAfPgvVwEVwK/fBSuBxeAVfDK3XO9UrYpHO6X9C53LvhGhhvt/NwKFwLh8Mb4Ei4Dp4LN8ACeDlcAJfDMng1rIDfh5Ifpp9I+pokPsfZ+QHt4x7snQZ/Agvhw7AMboM/gD+FO+DP4ZOwCb4Mn4T/gk/pXPCnYRf4a9gdNsMR8BmYB38Lz4O/g8vgs7AR/h4+DF+Hv4B/gY/CN2ATfBM+Ad+Gv4Z/hc3wHfgs3Aufh+/BF9X/P8GP4BvwY9iJAnMAdoOfwXT4T5gDD8NR8D9wMUymHNTBLnApTIE3QGeddP32hQnIoRbrpJ+j5fE82BEWQLM/gbrLQta3qBe71d0rMAb+CXaGr8Ke8DXYG76u/hUhW9W/asROk0Q4X/27Kj6wP8EqOBeuhuep+Xw1F6q5WM1laq5Qs8ZX392Jt97HHd/Fep9KOA9eAjV8vAM64dtjwqfu4gLuquBc6Ifnqfl8NRequVjNZWquULOGT98ldA32FuEboPcZCOfBoTA7xpJ1r3c9mUhljjniGtmHJgTmqh/Afsu1sA8gKfY618hYJHx9a2dN67inEq0DNk9gfjKS51q/eg2yBdG1qlmn2lmjeigyH9G1qMPWoM7C34SJzEdGsnKxD3PgeDgNca8/XadzvzchTcguZCvn9sHgutJDkflISfha0rqGtFk72r1utFkvejXiXgt6F2KNIZ4T3Ws9R17jec3E8HWdeyHu9ZsbEfe86UO2eWLY2sxmTeYGpBHJIZ2mIZXIGmQL0owcQJKfZi1m5Ayk6Ono/OjoceTjyx7/95vV/76Y7r/dz/pRf4t2w24bdXjfWf9PxtUm9KX9zHWuR1oDcKBr/YByjzUANy5rsQag+HZs1gFM8LX//drj/d3z/TpnlXwHzHvp4AvVr5VMqv73/q0bVsW2f52+L/s7LPBOoemt+VDUYj2+E/QdYhTsA0fD4XAMPBmOg6fCk+BaWNecaK1DxuaErrk3TZ9fwWfXfH028VzSte/czxRH9+cA4jwbTJtv2vpe0qaHt+Xbm6Ptb/SIHtEjekSP6BE9okf0iB7R4//riEOqvsTv/+qqMvlXWFvsPxZrAPKdL/Mrd8n8WQ1HoX2HikX1hCP4nd/HpSuwV7/zx7vmg6dn0c96qXu+uXpiueeEF/v9MtXYjGWrm35q9llx8u3aSdzcJPOgmbBeJ/0E2Jksc7cPiJtBZuz3irQj9xeEzvs24TDnuRfnzb1kvPYzuQ9rn6TY5ovU3MHyt5h/f1+MjmMhXZEzND1yA/0eoYlayBi/V5ro+Pl0cZeraRL0J8OsQbU/gxFt8qMG94k67p19FHEnDmFrPyapw06qQ9AYGoeq6pBotE2PQPcz9xifbn//jcd4s0d/SfvHoT36Vzz7b+4aYJ//4YO3/+rF315yaHnq9rThCZ9+zbtf53zpTzrtrW9sefHhHVVPfnBg5/Cxrxd6reflNQ/Aa5zYaz2s9o8He6zb5TEu7tUf5rXeltc8Bq/+Oa9x+vaPi3uMc3vMw/Bc70z727QNg+MjjG1naX9bP5gGs2EG7A8HwQFwDByoY3gFltZ3OEP8Q+BM9W+I7pU7VMf+hsNseAIcDHN1LHq0jkWPg2fAkyxnbEzqtNb1hBZjY7hpsDkRdoKT4OpYS8bCDjcntrpn7BbXvrFr2rB3R3v2js2Gup6TjKnlnXp0e8f2Ou0=
*/