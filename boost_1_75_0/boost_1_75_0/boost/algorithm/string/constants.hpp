//  Boost string_algo library constants.hpp header file  ---------------------------//

//  Copyright Pavol Droba 2002-2003.
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/ for updates, documentation, and revision history.

#ifndef BOOST_STRING_CONSTANTS_HPP
#define BOOST_STRING_CONSTANTS_HPP

namespace boost {
    namespace algorithm {

    //! Token compression mode 
    /*!
        Specifies token compression mode for the token_finder.
    */
    enum token_compress_mode_type
    {
        token_compress_on,    //!< Compress adjacent tokens
        token_compress_off  //!< Do not compress adjacent tokens
    };
    
    } // namespace algorithm

    // pull the names to the boost namespace
    using algorithm::token_compress_on;
    using algorithm::token_compress_off;

} // namespace boost

#endif  // BOOST_STRING_CONSTANTS_HPP


/* constants.hpp
HZInMsv85Prhl1cXOwCSJvhCBAG2PDFoH9gZiKLHquXQz57yDrGNd+aa3Kegxxj0OzjJqRXS/aS5fvR2i/t2YXnMw+R4hd9A3IIPy1Ml6osWTv939jLh2U95d/M786L2OotjL70FChgiPgbWhLmgLh3JmWtuiO83tcVyCi+USbMMu0Sa3V8QhkFD/iascahkHZuW8fOIgTXmY7zErefPX5pTMpUgNE+5wFE7KkSkp+MWHhPt7E1LECYDzw5+fHn9dKaqUhx12hNTFiHHSeTAriKNUmNzlqYAfoSTr/N3PbeEfenBYvqfdbvD+J66plWT1zIY1hSxP9aO9XFU09fNXHc0Qb1YGxOD61Ldtm8lAaWLPAp55SelxmNn4xwq6yck037QJhyNF4Ur4J2TxHHAz/lj6DnNeM30WZnwIkOd78KNZy4Dd+PBJjSBXxuFvcQI8i/vemnluqOHDv6qC0o/dEZMB2hb42cA0NgCFMzWYxRG+SnqrjVA6emsOltc01Zduk6MeaUG4E80X72OobTpv5eeGhMjD1AZ57H6TVsDgR3XyfJ9Hz6+AHXRhO6YgP6EdTLaCTzk83/xWm5MIC180+YiE+8zy0nOzHXL8pcw+mzVxC110fVytmv+Sf3ey+EQzgABHg7es9OjwUM0KNAdMToDoOK+FOacw5j6I+KaHO/MH9fJnpRIPAr+88fdZqHzFfd0SyipMRaCHcLw
*/