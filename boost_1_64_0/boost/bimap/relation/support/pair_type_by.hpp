// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file relation/support/pair_type_by.hpp
/// \brief pair_type_by<tag,relation> metafunction

#ifndef BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP
#define BOOST_BIMAP_RELATION_SUPPORT_PAIR_TYPE_BY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/relation/detail/metadata_access_builder.hpp>

/** \struct boost::bimaps::relation::support::pair_type_by

\brief Metafunction to obtain the view type indexed by one of the sides.

\code

template< class Tag, class Relation >
struct pair_type_by
{
        typedef {signature-compatible with std::pair} type;
};

\endcode

See also member_at, pair_by().
\ingroup relation_group
                                                                    **/

namespace boost {
namespace bimaps {
namespace relation {
namespace support {

// Implementation of pair type by metafunction

BOOST_BIMAP_SYMMETRIC_METADATA_ACCESS_BUILDER
(
    pair_type_by,
    left_pair,
    right_pair
)

} // namespace support
} // namespace relation
} // namespace bimaps
} // namespace boost


#endif // BOOST_BIMAP_RELATION_SUPPORT_PAIR_BY_TYPE_HPP


/* pair_type_by.hpp
ONMX7oiGS44RbraGmwOTYLEvnLknONylGm6uhrvMFy6jkXClGm6+hrvcP5+OhqvVcH7dWhdd07ir6ozzVGfcHU5WXdtU2A/OgL3hEngGXCb7vTVU6/U84/Q8/jVUz1bd6HA9z7lQdN2quzwHjtD9Gp8+h7jHMeIbrfGN0fjGaXznw6FwLByp+zX/aOOD82+i5l+h5t8kX7iNjYSbquEu1HAX+edl0nA5MeZXyk7QeYxgO3garE/kWh/5z9ZFxueCOPX6yP+G9WP/n/SRldTJTUg9cgTJe5Q6itQi25ADSOpjLc3Qx+L6yfgW3+JbfItv8S2+xbf4Ft/iW3yLb/9G/f/yk7f+/6JcY8f38tks21bt49qAPOnqND4vff5lgytKwnMAyNj23ZFr/6u/M6zO6mlxTzcDVXdXKzqrqiq/vupR8VNjBukaZ1NsPF0lTKboQXStMh0rtkuOrzaDVcdVbsN0t+t4GG8MnaSl1c2iI/SND1seMQbydxI+C/dYGb/1VXEvletMkk7sKjk2gl/fkmMLPXsEEllOPn683fH1am1U57FbdDLzvTF3olPTvGFfgdDdp9euY28LxJ+mXcMmZUjYiLHaO1Q3X6a65XnIXs5ZKvlQVzG4LPJePhN5L9Xf6bqGtR1/Z+9btRyfYHryV++bhsmUMH/I0DzW8XV5xj/O2VuHMgs+JeHSbX5ekcv9aO/ZdxQcJz+L4DO+/Cy262NrmtmXB/+QIfui1ratVCXevVxDJ3gTfJ743gzn1XI3rwLHtKs/b61O5xbXfZ3TMO80n/Cv5VvXSPq7uNc5rXRtT8qaXYdpusTV2VlvOpi7zZma/xzYJGv/m1wzk31jZR39V8XvI2aC7LNxMegQrbVvrHqi+Fsp6evp3Q+7PuO5cvwCJ4XW7OucoY3s13Pi7sp9SnFD6VqAS+F8WHJ8mwK7ZhFxRaxRVBQ5tjf6Puq9Fv1HSnR5L9CuOrpuTRY8JyFU3o9ssvcwVnm36xNnbXb97UVLvkrvazhsLym/nFfrgrZh3v1Uf91Nrt7/dhJX14SJhn5S5AknAb/2fgz2h8291fXbTt2OWSzujtLWrDaUFYlruuOfSyRT681zcuyvjPM7S+uSY/4i4ftKmXAT+ZL4WeIMxU/knCNeHWwH0yVcN5Mt7nA6njeJZqN5zLQwvrJp0/6FW7U8aLlJkXMddWbyd4v7y/Qxtzj97bU9If7bazsedl+De5jJ1vT+ReIY7pxlRpm1Zr2JKKODvfXAvi3+SpyjpC3Tvx5YVZVrJSP5V+5en/jrmRDZ9nhzLPSX42Npx1rJnCBVtAXvtNA5URLr9qUnt09vVfeQXV/40Xbe/CjZ6j8jVef4aFF3JD05N2qOj37qbyP+lki86wrSUlKyElu7U6OkJ7VJ6ZhYlTIvPSvPaBto65bUqwb11JbZIsm/04xbT7NlX/R986dzTzidyevOTU9MjUpnuF5foefW+kyavba4sNG2OLkd5c/Wa62vEW1zua3TWofYVxVZp+2aiRlpxujaAZwbart84DZ/nfYvpRrYRmuYXvbd5Ki4f202kEcB7TRhdK1qbaffE/dvzWbjRNYHbau3btG6rOe8XNyttS13TIG47zY9TFv0p+fEaqPt8/WPcq4HzGQzUfd54QkbXSa0Dp4pfq43F5hsW8+u3BJ+lxlm56qoynXvb9PXy3bv7Ytb7L0Nnh/E12Y3fM7mt9b5AxLQR8MPiewlwg/6gtzP5YMrvOfsi3IPqyRizU/1N8g+N0vF/XPHe7esWGbbVuu/v7jn4L5M3G/b555jItfDvkSOv+XY9YXF3a/hmvb2fs+U4z9xfO+INq275Vhru4ZxnbgraYc/Y3I=
*/