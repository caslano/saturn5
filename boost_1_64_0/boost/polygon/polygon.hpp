/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_HPP
#define BOOST_POLYGON_POLYGON_HPP
#define BOOST_POLYGON_VERSION 014401

#include "isotropy.hpp"

//point
#include "point_data.hpp"
#include "point_traits.hpp"
#include "point_concept.hpp"

#include "transform.hpp"

//interval
#include "interval_data.hpp"
#include "interval_traits.hpp"
#include "interval_concept.hpp"

//rectangle
#include "rectangle_data.hpp"
#include "rectangle_traits.hpp"
#include "rectangle_concept.hpp"

//segment
#include "segment_data.hpp"
#include "segment_traits.hpp"
#include "segment_concept.hpp"

//algorithms needed by polygon types
#include "detail/iterator_points_to_compact.hpp"
#include "detail/iterator_compact_to_points.hpp"

//polygons
#include "polygon_45_data.hpp"
#include "polygon_data.hpp"
#include "polygon_90_data.hpp"
#include "polygon_90_with_holes_data.hpp"
#include "polygon_45_with_holes_data.hpp"
#include "polygon_with_holes_data.hpp"
#include "polygon_traits.hpp"

//manhattan boolean algorithms
#include "detail/boolean_op.hpp"
#include "detail/polygon_formation.hpp"
#include "detail/rectangle_formation.hpp"
#include "detail/max_cover.hpp"
#include "detail/property_merge.hpp"
#include "detail/polygon_90_touch.hpp"
#include "detail/iterator_geometry_to_set.hpp"

//45 boolean op algorithms
#include "detail/boolean_op_45.hpp"
#include "detail/polygon_45_formation.hpp"

//polygon set data types
#include "polygon_90_set_data.hpp"
//polygon set trait types
#include "polygon_90_set_traits.hpp"
//polygon set concepts
#include "polygon_90_set_concept.hpp"
//boolean operator syntax
#include "detail/polygon_90_set_view.hpp"

//45 boolean op algorithms
#include "detail/polygon_45_touch.hpp"
#include "detail/property_merge_45.hpp"
#include "polygon_45_set_data.hpp"
#include "polygon_45_set_traits.hpp"
#include "polygon_45_set_concept.hpp"
#include "detail/polygon_45_set_view.hpp"

//arbitrary polygon algorithms
#include "detail/polygon_arbitrary_formation.hpp"
#include "polygon_set_data.hpp"

//general scanline
#include "detail/scan_arbitrary.hpp"
#include "polygon_set_traits.hpp"
#include "detail/polygon_set_view.hpp"

#include "polygon_set_concept.hpp"

#include "segment_utils.hpp"

#endif

/* polygon.hpp
uzaWYVdHqcPUad+3DmtlGZZjHdbSMmymdZiax08hlmFt1fmdsQ5T57fbOkyd32rrsBaWYVOsw9Q8DOqwNu0tw7pahwVahvlYh7WzDOs9Uh2m5pszwjKsdVvLsBXWYWpdTbcOU5etj3WYWmZPdVgrtSzHH1eHqWXZaR2m5rvWOkzNd7Z1mJpvvHWYWqdDrcPUZWtvHaaWr4F1mFqnHuqwlmqdVghWh6nzixhuGdZCXbZ+1mHqstWzDlOXrfkwdZg6v1rWYWr5ylqHBbhJ38pvhlqGtTd9/0T9HljgPtimryUHBTAN85LjRIoMk32Vum9W3me16WGOm2XN116l/Oq+aBQzNcRa78G05XtKPENkf2CZ/hbTb2KY1J1mvynv55J92WVv9k2pyekpdtP7sTD/YFjVYJle3k0rfbdsxg1jXGX4LqUNynIelf2vHDRM0x+xfzekTF+aHdYJpmM7Uae/Lu8EjkyISzPKfbU9kr8yTO6rmeZhIP+SzONpvs/XzGO/srzKPDg50PZ7TNfcuzsk35Okb2OuJQ++U0abcgaSx0L+Jvsb9fhk6l8baZySEmVbhwbGVxpTvdHWOtzB+DHK+WFcjM24mxi3G+PIflU9HvlL30lL+8mx5BednJoYbnR4r9lVeWd+EjMpJ+Yox5vxzFc9DmTYnXMU/E4vyzHgVqjtMSEv1HpM2BHquF0tCXXcrpJCbberAer3QNP3Tur3dqbvTdTvbU3fq6nf25i+P6x+by3bpfo+zALPjbT3IUvKu8aXlabuxOUMyw6zrTvtcdTfhTrbEWtbZ01irXX2UKzjceVGjONx5bMYx+PKZuswdR89yTpMXQeDrMPUfW8ldVhrdX4LotVh6v49zjpM3X/2jXY8/rSwDlPzqKgOa6Uu209Rjsepk1GOx6ndUY7HqZVRjsep1CjH41T/KMfjVPsox+NUpSjH49RPBsfjlKc6rKWa72+R6jA13++sw9R8T0U6Hs8OWYep+e6yDlPzfTdC3XbUfN+wDlPzLR3huI39EC7DZBv7SL5btrFPw1zfZlw9lin7suvl+c6IP/PdnIec17t47FKmz6lojkUqyyUxB2yPXfn6xy6mN//IvAVSf6bx78nxhI7taaZtV/avZKXtlx/K39U+1NrfSYZKjr/TNzAsLF7dN6jv3lQ65CanF/zOce35+1GZ/0T5nZCMsxiWYp2/C9ch9H8naPdxgdKJyV+Wow7pZfLpmmjNJybKKD/2XM8rXZL2WHRe8hovv31Hk55Tlkk3r9AI3rXJNUPXf1+qMSrkWB/uqX1XtxznDbbX3iJTbMu4qrJ5xtPkeJmBOUr/eLsypkZNNL8JVDnMP+BzNe7SHz7F8bxP3SbS1d+x8ttSMywetW2ytLy/v5KsS2XgdfIL6m8tO88EGbgSGx8VOpn3w0a5vD61baeZ5LdG8ouT9Rkl+eUlq/m5+I7zUp6tUphC4pY4ewbppvK9lfk5nPrm8d0+87Ztz3e8HbfLbGW7TNGUKT3RcmG4wOW3eW9wFccYE3OV9quZd0pUVPyDbJPaa0YR6dE279hlB2TTRr185JxO6n0CaTXlyNaWI91+O3LlnI4yoVwncdJGJU6IXd2s8dGvm4CJapnYZsINf1XdqPEZqsr76KRu8kjbfVn/duXg+p5RiYDi2rlu4cqjjcEh7cFh+1bacLKpTPxOkufhDsj3cPleKlX9btPGr8syPiZ13V62u5RU7TImRcUkG+PCH3Abt7S1FF/ziO9Kfb4teeXq50VLi4qMf8A61daP9nnH6vLe/BekDM+RAmhbmf2sZeDd6Zp9WyxrmKPVA5RD+2xgrOzbLeu3jqxfS1llu7C5l5AjZd0k62Y=
*/