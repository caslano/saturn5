// Boost.Bimap
//
// Copyright (c) 2006-2007 Matias Capeletto
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

/// \file tags/support/tag_of.hpp
/// \brief Safe way to acces the tag of a type

#ifndef BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP
#define BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#include <boost/bimap/tags/tagged.hpp>
#include <boost/bimap/detail/debug/static_error.hpp>

/** \struct boost::bimaps::tags::support::tag_of
\brief Metafunction to obtain the tag of a type.

\code
template< class TaggedType >
struct tag_of
{
    typedef {Tag} type;
};
\endcode

If the type is not tagged you will get a compile timer error with the following message:

\verbatim
USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, TaggedType
\endverbatim

See also tagged, value_type_of.
                                                                                **/

#ifndef BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

namespace boost {
namespace bimaps {
namespace tags {
namespace support {


// tag_of metafunction

template< class Type >
struct tag_of
{
    BOOST_BIMAP_STATIC_ERROR( USING_TAG_OF_WITH_AN_UNTAGGED_TYPE, (Type) );
};

template< class Type, class Tag >
struct tag_of< tagged< Type, Tag > >
{
    typedef Tag type;
};


} // namespace support
} // namespace tags
} // namespace bimaps
} // namespace boost

#endif // BOOST_BIMAP_DOXYGEN_WILL_NOT_PROCESS_THE_FOLLOWING_LINES

#endif // BOOST_BIMAP_TAGS_SUPPORT_TAG_OF_HPP


/* tag_of.hpp
TlCdqUUwA06Eg+EkOBROgyPhVDhG7RPUrv1C92wZ61H6xWDVpTsMDoSnwelwOJwJx8BFcCT8AhwFvwRHwy3qrvWqe5yUNUq9Pqb1+mOYAX+i/WS/q13Sl3qHf1LDH9DwP9fwT2n4RkyRht+n4dvCBg2freXsAXNgDhwLe8Lx8FQ4B/bW8p4Cl+r5lbAf/BzMh9fB/nAPLIDfUX/vy/jXfSi4SvORAs/F6Ltt0p4fajn+BAvhRzpvxsUF+slfdf78GNph/waXqPt50HKlt0/TuzNKen789YIJsC9M1XZur+XtDEtgppa3I6yHneCX1X2rumt/1T0O+mCU/vq0lu+XWr5DWr5ntHzP6zh4Do5W+3ixO/EfbSb+tzX+Ixr/HzT+dzT+9zX+9zR+7MSP3cSva2T47Sjxv6zzy2GdX17V+eU1nV/e1PnldfgV+Ft4q57X+Fknel839+IvHT4AO8MHYTb8HsyF39d54yG9vjwMp8IfuXQsN2n8AzR+t47l83WeWAm7wVXa31fDPmJ34jmo8eRFiWe2zjtzYCYs0fjmwVx4hul/ugYBC6P0v7NUx/DZsKt9HvaAi2F/uAQOgsvhKLgMToIVcCqsgjPUHRFdkd9tTsa36ek2Iuc7rCC6DO8xaMvr5mKGYaLJ5iKXa2Ryj6whDET21i13a+Rtd0GVs42Qsc3HLMA4+jFD5WmRpRUZ2gJMuNzsHZh9mEMY5GNVFvb4+ixVDtYt/6qyr0bmVWRdN0K3TOshjDU0VGZ1qW0uR9ekI6uKnGqkfGpXjEsWVeVQQ2VOP8I4cqaOfGkjpgmzl3Y7iDmC8f8S3Y6YKZhKzKWYbZi9mJcwH2O6H2pjjcQswDRgtmEexDyHOYbp9EwbqxBTjKnGbHomJqsaO2JH7IgdsSN2xI7YETtiR+yIHZ/W8anJ//MB/5Mh/5+D/P9m+z3PAlv+X94Y4O2tsjWkXVtTb4n7tbgfPTXEffnamoqGetUN8Issy7yLviou5P1lzpM/NoGWBnQDTJ0/P/CmSTAmMmNHY95je4RYHhXTcr2BuXFezzxbrzfQ4xmg5zO6H8kzxgefTPjj/Zf85Y1rPvrdtvUdXhvj9azP61ml17NZr2eerf+eaGBfX9tB22d92LesinXfcSbsAWfBgfp8YRQs0X3GeXAPrHuZb1JgzD6Uaw+qWPaYIveXFuieku4hyf7RHrNXFLovVKl7Pscw7v0d9nZ078a9Z4PR/Rn2ZiL2Zfa8HNsbiR2xI3bEjtgRO2JH7IgdsSN2nNzjU1v/I7J8stb/l9vrez5UHB9Y3zdcVFcVlBV33C8Pdb9wRc1Q3kUR9zszWYPL/kGYhDlHtrrXifuZ0+cMHaKugb2D72ZZRp5hk+4dJAcg7yY22nsTs13yDBKFdVzZdPf79q97xHvUFa8psNWyuIdY7SXuJtWF2F09dMO8m8G/ORK3vcWxqqpm6GDOuGSuOGuZ9+LVb3dxXyuxEETdJT1xz2omX7lGfijZkeEjDa0HzetO1QE4QutjONxAPRQG8lpBh1vDC/2rV1fVNNR7y/mq/zZBGTp+19HOvJtv3HLiStgluMsqxbG7upGCuL1pzUC+qtyay3tu8aKXawt1+JCP94Bs+ZslSN90TM1P7Z9an5ju86NQw8e7Nu60TD62S3xjVX7Lid/HG1opRjboAvG/Av83iHuRlSl24x97Ee+yThP5ngGan1Lq6gd2fhq/bosDpU5NvSwxLZCddvIvMk9S/lclztnNlTlq3n4v/qY1m7ecFupjCJFL5pwdiHxyri6k725MCAReobIeS1R+yJoo/YERUVbBRmBDleWpKwK/oXqyMsU+X2Uu3TJEjlxGgfgZwXs=
*/