// Boost.Geometry (aka GGL, Generic Geometry Library)

// Copyright (c) 2014, Oracle and/or its affiliates.

// Contributed and/or modified by Menelaos Karavelas, on behalf of Oracle

// Licensed under the Boost Software License version 1.0.
// http://www.boost.org/users/license.html

#ifndef BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP
#define BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP


namespace boost { namespace geometry
{


// free function to test if an iterator range has a single element
template <typename Iterator>
inline bool has_one_element(Iterator first, Iterator beyond)
{
    return first != beyond && ++first == beyond;
}


}} // namespace boost::geometry


#endif // BOOST_GEOMETRY_ITERATORS_HAS_ONE_ELEMENT_HPP

/* has_one_element.hpp
2tcS+nuiZQdNi461gaA0PkxJmiMD+ColH5Z3GyyTo8UWXleRCKe93CsCfr5MucIk741KnmpAUnSTkp4Nk/xGnf7MmnKv85wcA4RVlNdLihUtVpzloM7NsOUyFrwd+Zfg7M7lNfQIDxlTthZAWj4md7BGbJWG0CbuCH94sC6x8Breu2tojB2jI1MGqo0kpyzh9ZylMRo0fqmzMWQqXLblJBVr3KLyy332Eor2iOyecnqIER0gij3N36FfatWnJCYwNyk0zLakA7TAbsQBJlrZ/zz4doky1vaN0ZHeZinwsyO35F0UNNDSrwo4b59ArWlsU+URhW3TeXrb7MYjJ0ZC3OzpV8Rtp4jK7K07wpsCDP3XIcFfM96Gdae3sw1WkGx6sTQeFwhteOUOVUkHhkOJBp04H3jtDdpGla1tnAjTLwDc3b6A+DrESQY4ef5IpujiUMnXmbt4j1+x+JNXomQvImyEDcyoDdYO2Ui3mJGnEyCIHgeo3Mi48TZXKT7chj5g4ckF158aN7vhGocIPivPWOUqhmok4dV0LGVzxJKmQFqE+UZze+wS8SwI2w==
*/