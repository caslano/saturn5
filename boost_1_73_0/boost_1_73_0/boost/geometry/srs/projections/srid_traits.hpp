// Boost.Geometry

// Copyright (c) 2017-2018, Oracle and/or its affiliates.
// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP
#define BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_BEG(AUTH, CODE) \
template<> \
struct AUTH##_traits<CODE> \
{ \
    typedef \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_MID() \
    parameters_type; \
    static inline parameters_type parameters() \
    { \
        return parameters_type \

#define BOOST_GEOMETRY_PROJECTIONS_DETAIL_SRID_TRAITS_END() \
        ; \
    } \
}; \


#endif // BOOST_GEOMETRY_PROJECTIONS_SRID_TRAITS_HPP


/* srid_traits.hpp
BgoCqgQROypvcBOA8BPQhYMNwoVN6NrjIEEYN5ZCCjTxSSLCXTRxpivABjXIewcoauNcMaq8HmzrwJ04UREH3HEI90SHC7PRMgfasyEwhCEdsZnDUY47gMl1N47vhAAs3RSAN9qxIjSGLIrg5mNZfJw9gd/twVV8DgycP97mK1wi9pwmiRutlssgRDVAPMLAUsN3BUDPXYBYttwYZjjOCsYSxxv7Wj4IMYvhLx+M/vlgaF20W3wgRU7Q9nj5wfifTJciep32Wl+ytOK6sbrc42D6yOwDfMX5ItOCl680mvT8wKIRNiKZVoi8GI36eWIqcwhSglQIoGJzuI38m+AAcGJosM28ivD+RlSQ58nS4UTx4eFhIhYql4gTzwM8YXG8gflX2ifJWqSBEY3TrevrBz03R4pIV3g+N9qdXtccDHq5fdoK/FexWBpE7eOH746PDZCKQfgii8HF6LLzZmnjOzdeOdKYBWKaGIRfsdSpaE3xWdCa2a5nBb7Fht/TDv5kmn1raHZbKAzBta7gmZn+1nGWFj5ZwjpWBYOvQVVgrvqdXqN1ktNZrnL34nWi7kZ4sQuRmcRkEBFBnpoHwF74UhNzGRyX/YBdI8B8theJwRLWhJkkZxYsxWrpBfYWl3+KZdkgKZUqByjCAn/c
*/