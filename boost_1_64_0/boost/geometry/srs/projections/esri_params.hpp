// Boost.Geometry

// Copyright (c) 2017, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP
#define BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP


#include <string>

#include <boost/geometry/srs/spheroid.hpp>


namespace boost { namespace geometry
{
    
namespace srs
{


struct esri
{
    explicit esri(int c)
        : code(c)
    {}

    int code;
};


template <int Code>
struct static_esri
{
    static const int code = Code;
};


} // namespace srs


}} // namespace boost::geometry

#endif // BOOST_GEOMETRY_SRS_PROJECTIONS_ESRI_PARAMS_HPP

/* esri_params.hpp
tQx/mXwO776STa5rfE+dKNmF5oU34/2PzMCs2d4+a3BOkDkx69SyzyQ890jrzNpf2RV5kcZN2PjLFO8ByerYpwwqY/xcmIyvpVvzsO94NiXjMTj12RsqLFCyGlk3a+I5hIyvs3ZXizF4/pRsueXdajhbpTmr1fGZiT4j4/EdWZXf+HN0pTkzx/n9JSxDmvN757XRwkzvGHvQgt5peQ/qyHTMeO86aYxzkcbx56zqZHpmewul9RLmpzFnZzJrZp1n/fDB8yCZPbPyB2qGCJshjft7ampz8f4ecceYT0slJOTMnq3thMVkz8ls0LHid4QlZc/JLLFknYvCUskMzB6HVx0rzPyues6sN/NMhBnI+Jymk9J+CatOxtdZ/9iyRGEdyPTMblksaSQsWJrTv0SH3cJmkLkwm3AptJmwnWTmzBwqpv5L2IHstXBLSFst7IZ0vS73mloISydzZXav/eOywuzvqa+H9zEyJzIdM/QSmTuZC7fpFnuQF2ncwJFHVwnrQ8brsCqjhp+wiZLViEyzF7ZMstm+92OQMzIe+1vPKqeFxZPxnP1Kypwo7JE0p239nYeFZUpzhuyefV6YLkU9zuPghxjsvxRjPgsoivp9LIWc2aEalW7jnM+ek9mdMYteYI+RWTPzXzVrobBQbvxeRX8tSzHWQcfeubJtE5k5s5eZkfOE7cxeC7PVrdzrCDtDpmeWYp5WS9gjycp9auoqLEuyrbq7h4Tp76uvN6XpAVzPg8yF2b5dbQcJ60zGYkCusy2QzIlZHu8q9YSFkvG1DN/1pImwtWTWzEwmlvYXFi2tc0ixmXphCZJ5XuvriLxIcy57fai9sE8aMWRpmOkD9ZxJ0b2PI59kBmazr9iY/baQYV4PMGfO71LG8xJZYw1rqWEdNCxAw/po2GANG6lhEzVsBpmOGe6pZMsku6uPbSdsE5k9M9PhFdYLiyVzYdYp/93twlLJ9MzuJUUfFKY8pPox+/umboEwezK+lv6T9lcU5iKN+za0cT1hnmR8ndsOz24vzE8a92BnjUGoAxnP2cCnyweiDtKcj7NKlEE+JWu183JPYWulOdOHVsQ6N0lrOX6xxSVhMdI49DxZvHS9tdcLugpLlsxj+oPBwjKk6w1a53JPmOkjta3c3/66MD2ZE7MXgbWwFk/J7mZWDhDWWZpz4gQzB+Tz0Z/jGylZhZk6jJv4SKOvNWy+tBbcH8gipXG495NFaawzmozneuNlv7XCEsh0zIz3HKqRxjofaYzL0BiXqRGf7rF6ncZ3bRPF5THG5fzeeIwj8yTTwdhnh2S+khnXmVfp/Ni4zkL8c8zsObLXwsxkVFeMG0umZ7bWKy2PsGUac67VsE2Ij4zFl20xLAYy9l48LDiBzZn9u74xJ1mShiVr2CMNS9ewDA3L1DDlyZ/NXMOsNUyvYQYNc9UwDw3zJLNnhj1G5idZz/7rvgoLInNitq1c44rCwsh0zHjdIzQsSmOd0RoWI825qZ2dI/qMTM8sq+llb2GpkpVd3n4gavtUo7YaZq1heg0zaJirhnlIZjxbqbZkPC+1qq8ZIMyXjNfvuFX+eNRWMr908xKorXS90hWW5RO2WBqnO+m8GPUjs2bmc216XmFnpDlxPyJLlMbF+p+/hv1OxuuX5jAiSFiWZF7nXtdHHVLVeRlcf2En5JqM93yx+b6Iz0eywylrGgjrLM1pPK8pn2Q8PtzjyIKlcRsKPMsQFkrGY2j0vpeJsLWSDe0UvQj7gYznzPND+mPkUxp3+R/n5TgjJXPz8ukozPSZek4T14uLkU/JQgp0qCrMnYznbMzmJsHCGktW6/3S48ICpDlv+DnDgsn4OjOLxNgKmy/Nee8=
*/