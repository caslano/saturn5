
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_HPP_

#include <boost/local_function/aux_/preprocessor/traits/decl_/index.hpp>
#include <boost/preprocessor/tuple/elem.hpp>

// PUBLIC //

// Expand: `[ERROR_message_text] EMPTY`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    BOOST_PP_TUPLE_ELEM(BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_MAX, \
            BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_INDEX_ERROR, decl_traits)

// Expand: `[ERROR_message_text]`, EMPTY iff no pp-parsing error.
#define BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR_MSG(decl_traits) \
    BOOST_LOCAL_FUNCTION_AUX_PP_DECL_TRAITS_ERROR(decl_traits) \
    (/* expand EMPTY */)

#endif // #include guard


/* decl_error.hpp
l9pMXHIGteUF47Q3xgPG8w+AQHWXWC+EELpEndh8uFovkVuM7ocMELukMrcnG2RtrGUI0Y6cd7FIHN2yrploPWtZ3u91JIOJBsHSNz7U4VHla/SqKBSmjL5An+tHAwrjbpqBswgPneH93V6KphjUtTII8psqnyrJ4F3qNlQSstKyrEy6DBUNViihLjpluUso0Hj7aalDXLzaANitRqOPawcC522HPOJ5oY1oG+cNz7eSCh6kgjLJ+EkIvJIggioqtdPH1KR+a4eEtHoL7cPAjUms2Kz0aH3kjVDvQe+cMgBGDOXkZzTMOzUAuDGW4Xfl8H9lc3OOYbQXwLt6bL0eQ+D8l6+3miCoGINAuq1u9G6sJoMR8nmcXuWhXlkuUvrwTbefxla6cHMzZIXXHGFQD26F6IJC5rQMJF8sBX3n01OR+o9T2iJ23ELn+Bn/tO6qTdYVwR9zvQpkYxnR6P8S+UMr/vYZvMGF6A5bduydfNd1d5ksca9/VX0cjPz2ldtTDXXA5VrOWERycDYGmnbdd261JmenW7x+j5v2PVtVjL93cOGklk4WWx+44g==
*/