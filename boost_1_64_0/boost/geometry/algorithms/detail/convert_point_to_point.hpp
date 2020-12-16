// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2007-2012 Barend Gehrels, Amsterdam, the Netherlands.
// Copyright (c) 2008-2012 Bruno Lalande, Paris, France.
// Copyright (c) 2009-2012 Mateusz Loskot, London, UK.

// Parts of Boost.Geometry are redesigned from Geodan's Geographic Library
// (geolib/GGL), copyright (c) 1995-2010 Geodan, Amsterdam, the Netherlands.

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP
#define BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP

// Note: extracted from "convert.hpp" to avoid circular references convert/append

#include <cstddef>

#include <boost/numeric/conversion/cast.hpp>
#include <boost/geometry/core/access.hpp>
#include <boost/geometry/core/coordinate_dimension.hpp>
#include <boost/geometry/core/coordinate_type.hpp>


namespace boost { namespace geometry
{

#ifndef DOXYGEN_NO_DETAIL
namespace detail { namespace conversion
{


template <typename Source, typename Destination, std::size_t Dimension, std::size_t DimensionCount>
struct point_to_point
{
    static inline void apply(Source const& source, Destination& destination)
    {
        typedef typename coordinate_type<Destination>::type coordinate_type;

        set<Dimension>(destination, boost::numeric_cast<coordinate_type>(get<Dimension>(source)));
        point_to_point<Source, Destination, Dimension + 1, DimensionCount>::apply(source, destination);
    }
};

template <typename Source, typename Destination, std::size_t DimensionCount>
struct point_to_point<Source, Destination, DimensionCount, DimensionCount>
{
    static inline void apply(Source const& , Destination& )
    {}
};


template <typename Source, typename Destination>
inline void convert_point_to_point(Source const& source, Destination& destination)
{
    point_to_point<Source, Destination, 0, dimension<Destination>::value>::apply(source, destination);
}



}} // namespace detail::conversion
#endif // DOXYGEN_NO_DETAIL

}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_ALGORITHMS_DETAIL_CONVERT_POINT_TO_POINT_HPP

/* convert_point_to_point.hpp
n3AmqGHq6LdQHzHzInxXt3xjt6/Xv7eR16XF+2lZN24fzGX7k6eMiLGBWtueZcYK6c04ccx4di1uWJ5/EecoLjXjPjvuDd+vt9jcZbkRMPBpHn1OCW0o8Tep9nsMW2Nh7kp0/zzTOnmeCbIMejiLg7PIj4p2JeVR8uKycr5XpuDcTmhOw+LPG2suSE+DiPv6f2HlyfTw3KIL28kT+2YkhykPeHvqMYLtYWU3/JCBLg5zn+wXBeeZDK6ZDrLC+QHuD/8GtN+GnFlHkxBnvVx7QTDMQon5WoKZ7FovK88tETyVTmaTfTRNIeciCU4SYC80223MwO3R2+Bu91+bds3HB4/H7RiVYMbMTPlhP+4TcoxaIL8d4TerQ+8m7GnWgwlmTzCTWQZ1KuOyAhnK3NyZm3gj2jmYE/5taIxlGrb4iDM4/CYJ5J3kJDfPU5f583y+gl9T83wuNTfGK8U8nzjH9pTxBxa2JZ5OUhsKmX4v5zrHsNORkG4GI3QzGNJNmeU5aKWg4ne4gJcTHLsQmT4GXPfcNOkN87HPhPRmOgW+3vCbZJsj3/0asz6UlP5B9PueE2P/3wj4C2p8+yL6W89jPPBH7u9ymHEfV/33P6Ov9TJ4mjjiJ+mojgZpvyLwXmU8vA+q5HpdpfU3IcfzSsa/iz7k86JPmsI90m/58eD7qhrj/APh1+UYCfTgz/3I5zFe0+OUd8Q45XXIQOMI3MMfHkOUTHPhvaX80IkMky8Qeae7guQ4UuxF+5lND2lOC48jJ03Ls380yuZgRztPC8psl2nBnSKUFvyZ90okz8j6j3PT0+R8NstO9qdlnuDtTmFDUwoa+k0yBbZTPg3r6ph7qZBxKI+9Kl0cdUgCu0JZSN1PRVoxwWO3aXzHuY2bNlp2qtvu+2lNWPY9CBd4sMUAV+LtSXjSL5ZM4HeNyD6D8ykzxF+9Z35vyD5D5TGn7HcW8Pahv9J+sp6y0wj72Q/hk4lAvsd0MuQeNzmQewZ4zcBvoqG/Qd5nQO79Ic8BwrYwB0L/8IaakEu/BXcQ6OeqcjmYwoQb+SbEPIrz+Z5aFv2uzyGi7OTbP5rXgmlc10Wa0fukF6pyPoPyJ8N7l4TDlcE4m+TML8OR06LetIo+b3g05yvQqdTrTPCsg16XTIt+o8JT+moQfFMoP8YTsjYRnuaVUmXarPTkkV0p3kwneR9DdLA/rmcz4Z+z9DGNqDfLiYbf3oSsdfAHbUKvmp/W67HGtxLuzhG4dQXfJNvZ6yxAWzEG7UqlKwryezGaF+U/mg8peA0RIu9ct+FDWRd7huYlOtvqj6FNF000Qm5oMJtEvKNozFeCMd8J0yyW7Rq7Q+hyGkLD3V0p/t1hru11fbt53kTDc+KJ00hKxTFn+z4KRqyi26PVnXUNNF6y7RF+++ursPGQD6a6eE1oDfoUfxFS9EtPaU6sH9RwssTE8p5NnSRTPJsR69UTLXxlf6phvRe83TSUWhUf6U+mW0h8x6N3mu2rbmmIZ/rSCXelp4EvInhZSWZL52ZqoYc7ee1qDtZY+yje/3dJSXR+0ffhtkj2feJEj3i+T1vGrxfxszD/JuMTKn5vFb9B1KeZbIdIS83fDsP/jKBs5sn+b5F2YOhT0n8hvQ8S7GT6pM9JC79EstmxV1b5pSxkyoEn8mrLtifg5ywDuJsi0i+PaMe2yPSBM0PhnAqep2meop8p8T8MmWYq+c+QfQS9PkLwjwDvoxHpPB+RztnR5cr+RpbrOeD9cckbdK9G8D4P+OdLnQNf2+cFwP2k7AuwPNFt56eUji5DP+/T4PG50JxAgl5AwJoYzwkkGcZ12uKJ89COLnRmutLBaPO4J+YAkiG6Wgo=
*/