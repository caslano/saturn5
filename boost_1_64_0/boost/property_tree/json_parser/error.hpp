// ----------------------------------------------------------------------------
// Copyright (C) 2002-2006 Marcin Kalicinski
//
// Distributed under the Boost Software License, Version 1.0. 
// (See accompanying file LICENSE_1_0.txt or copy at 
// http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see www.boost.org
// ----------------------------------------------------------------------------
#ifndef BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED
#define BOOST_PROPERTY_TREE_DETAIL_JSON_PARSER_ERROR_HPP_INCLUDED

#include <boost/property_tree/detail/file_parser_error.hpp>
#include <string>

namespace boost { namespace property_tree { namespace json_parser
{

    //! Json parser error
    class json_parser_error: public file_parser_error
    {
    public:
        json_parser_error(const std::string &message, 
                          const std::string &filename, 
                          unsigned long line): 
            file_parser_error(message, filename, line)
        { 
        }
    };

} } }

#endif

/* error.hpp
lHWvxS6T1DGgBG7toOMD+fhqK1t8AkcTy8hd+MSUAIcsSqLxb8b+9SG6uDynLpSKA716Znaj0pLL3WClV3Vuf09RZ5zJUV0e1Cy1Q4MHuxutImHHZsB1tzLfvJtCzTwY15SKuz1RKs3h79i7bun9GtvGWibJ+NUNea6oLWFzNcGzfuRMRqSzNiVcz/u2wPxigYsTt1enkiowUAPuxMkZtQwKKgmb3kUt5W+iUsxvkj1Cd3vqrDtuChlpyBVIBOBfm0M3AEiAFJiN7kOJ2Vc0yA21cI2cXXmZ7IDPSNy9Gytw7gfJaPjHKniDkrxB9vnn0UYKUG0VxyZ2y2ZpMeP8gMIujDokW+aRi0GfA2rjZxYUnk+gF5WyJG7NxigxkVI/HpnyqXbfdy6n9cW8ObGD54H0xy+MAS+yKQbAKXjUQK1l9phXetN+OqAzAbZpbNGO2I+sGW9WI36qdi2VYGEnuoJnJB1ofMzG/I10GbqthGMKKDwlgsy1Ks2Jc3NrppDBempV1S1eTUvKnC/i4PSRj+8/P1Lg/5DsGlKOzhkQKBElyAYvFO5iPU9FNA==
*/