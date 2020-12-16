// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/is_tagged.hpp
/// \brief type_traits extension

#ifndef BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/mpl/bool.hpp>
#include <boost/bimap/tags/tagged.hpp>

/** \struct boost::bimaps::tags::support::is_tagged
\brief Type trait to check if a type is tagged.

\code
template< class Type >
struct is_tagged
{
    typedef {mpl::true_/mpl::false_} type;
};
\endcode

See also tagged.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// is_tagged metafunction

template< class Type >
struct is_tagged :
    ::boost::mpl::false_ {};

template< class Type, class Tag >
struct is_tagged< tagged< Type, Tag > > :
    ::boost::mpl::true_ {};

} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_IS_TAGGED_HPP


/* is_tagged.hpp
vkXoOM5NHUf7+RLS4hOj9YtCbNmEW0WYfZhgv1hHvyBIQP+Tuh/FPCfxphY4HSOyX9gmqKNosOqTWY1pTX+5VsqVIv2l5Di6p5ZG6S/VnKP+tb+ozr/S0L7xoEff6JQY+f3KM3vZA9z0DZHC9hjL0jey8Ov6ZqWGzWp2bO6mTxYl8M6tPf5ShqT52us4U7eGhODYbJ+a4hqbGf/i2MyUvLUNjM0W6Gd06tp7HH7mrNC6nmjsobpIx+py8gNMD+U2W5Za/Jtvo9jiucuq1njOneq/QMbFHOybxf5TdHe6dU+dt6Z2bZ2OvWCY/ka/3NViP0CrJYbrVTHjbYP4ucTqpXpJSkw8vY1u2tvF3s2lUwf1nQ1rjW7pDvAm2w+5Sw7EwzkNpzreM3QuqKfZguE6wcvFz6/QRfdw4By2XXLuJs5dQFyTpI2uknNPefa3vvSprvTzj5O4jmSJPusrU5MT/b70xMS0zglMHDl0rU7dtV+hb8f9HRrVUad18jdJqzSi/DJ3aDoFyTp3VLnmjtTIfqt66iRPa1o5ZxyQdFNOuB87eqWkn4TplVK9yhqW9uGcaR/PcfBa2Dhof3bAvlPtp4bZi43dGSfuD9FegxEZesyOXvg7O3ScqAJ0z2vWd8X/KmuBc83SOLJcerk1FkcPgfrJNOPgfrE3WOfy3+u6Yrd9URvaPiWg09w3OTWPZo/PoYu1bWv0iMr14Wva/tkapjRF+0sO2vpn2Z0l+V+a43589olfT1S3rPYDrRsjHx/Z5i+eHX2uK1J9/3diutrumK/ShiXnhLYho4t7UsuzDS8Q/xfxzCVV2zAYRy+vuQ73UF2aNWL/nDW2mblupfi5mutfnM51wXi6NdvmfvrqrLTAnOHrm8jNR2Iyxk/Lmzb/elag3VOcOcW01SWSRh+j9+m3Yk+XNg/Gf2ma9o+lzc8nzvzVurnkgXNOvL/o/UfEXFIXMpd495+fnaP9J+y+ZH87S44t2n+uxtxC/8k91/Qf/U6E53USv6H9YLzYq2ljdz8I/c7YGPHT2fQl4jB9IEP0Z1etWlFTZfrnTHGfZw3R/lliwgx03ceuqHHrqT5D3JfSp+NM3pH+DNSJxrtD/GSY56qvdbb7EKRtV7dA35vq3opoK0e/m5TbXB8oG+ekbCHj+LBqXV6n7XAW5tZenA9rh+Os99R/vtHxlrxYvp/mWu8to/Q6Bxv/eea6myD+SyLawegPFfex2gbB8L097gm8dZqPkni6yD3qAfrg69yX/kbXCRPTEgPrR3Xrmh68R+3qSz+J68d/SN47/kvX9sD6kTo14zakjT2v4TmLQ6/hw9W+LWx8VmeorKX2i42Y2+kXjYvD+sXyOq8+gd/Q8XkzdvxYE0jHWVMSgatubhI/6aafEEez4/OuxRHjU8P09Vxn3rP4+OPzT/gx41PWfidvfAbWclJur/Fp9JrTTeRoq5GnYe6gHYqWmHaQjy5pjwt2NilXP2kT+4xpEw3XtsXfVeon+Zc4QuaNYSqENk2zOMYul339D8tXTaDo+g2TyLVlnfjPda79anf6VHV5veZ/pnHvYeaN1WLPd8ZjK6+N50v49BbrHL4urD1HmjbWfDKmNi6Jfs/UvbMqZsS01TrbgZ89gTqbE7q55tanqelJHal/Yimw0iL20+S7Ry4/XbiPCv9uwcjmy6l6QyP7LemE7EG8q+X8alg5d2O3j1u0b2zB3EXfSC8LLydjILKcZmz3F/8XuPekNI4s862t7WJv77lH1bfMtUel4b33qEx8nnPHcHFfb/aocmnTseT92cBeEmsCX0+WBKhKsELqPXIfqXXzSGR7RO4JbS2LvgdUqt8p6IHJUC60r/HaHmY=
*/