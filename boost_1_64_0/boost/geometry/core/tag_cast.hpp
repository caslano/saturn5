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
K4en9QUT5zmgEpfGvj+B7hZ3qUJ8DkF9P02ScINKn0BN5FRCOSY6YhcvsEbH1z2yCjHN1zsji8BTOcC+7d+CPZOvhDbKYyBv3qeM1NT5bSVSTPJhBx+v1km5AI4xkoaDFcAp9sii2X0DekdfLC+a42su3OAP1Q6c7pgMs06sHRB1KP+Wni5G/iv2ifZEMJaCDo+4FpZWNPywEAVGbrG0ULVG/VKUYNhHfjmsLqH0mkPsTMe6fTwXcNK+Ur+2hy5vjUvhDg0QXZQof265BwMYsXrSGBU8Oi2oHmjw1u9n7KBAuQRuxyTlNc/ASoJcKGmM65527lYKj0eyiLcYJO9UP7aqAjMZXJrda8bam2DW1tgz6ThAsi7Xo7R5RkuOS0BF1iHivxlDvm7UuzCkvtW/r8n447vNLpi0zNlPDGZQm81qQ2cTbhWonRPYowxASxOmY2Uj2ML2thWcWIwbLKjYViQCOzU72/rgfTUCQV7wyqhz/u3ZtqApBnNkNTlTlbGyveqvmN9sz1xs2Dii+1wXm2qeDZFKisaNCM2Xr2GzemYxsRa3pKoJujvNHw==
*/