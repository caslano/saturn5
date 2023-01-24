// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2003-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED 

#if defined(_MSC_VER)
# pragma once
#endif                    

#define BOOST_IOSTREAMS_PUSH_PARAMS() \
    , std::streamsize buffer_size = -1 , std::streamsize pback_size = -1 \
    /**/

#define BOOST_IOSTREAMS_PUSH_ARGS() , buffer_size, pback_size     

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_PUSH_PARAMS_HPP_INCLUDED

/* push_params.hpp
I245+XLYeWIYlfWPsSpmRaurIn3ZSa5Jqh7TCDj4vryUpIQ29eWKJhv7UzBSFV48bficc6ha0Fts/5lw1A/7XVhMbMgO8Oxj61uDDTKM+n1v91Q2rV+f3NIrub1VIK0t49gym1aHKldjPCmvZ5UZwZWFR6SJ0CnSCYyCRVtYIM/bifTle7EHTmOH+q13Bz4cN+BylKWuIloLSsfKP491F5DpIbWf+rcxdv2Yzi1C5pH2o8tZ3pg5T/DyrjdYuIgLyFL5asGpUN0x03ty2i6GfLEa4ColU4CCbrTewmxnqtFiVF7+EM1KOYEpi7po/q4HSXGMKh23Zh5iuVTbUtEfo32eUdmkiqml2Fiq16Jfc48FfeasUHV7CalVrIF7WSvq0ChPhFUU1l6P0sa8Jwk7PR5EaPlyIR+cqPBGb5+J/RbQeLty8eRT3PAn2ZMdizZlBknHax96LfdMePYA+8jJb6+BbcoJCzRqD4lzlRvH0Mi6ytfTZ+l/iqZjppNbBu2/+THeKLv2/OjVLHSLlnZE/cysav1Ve84YKnCBUq9iXkrrmLzOd/hhwKCjvi8g4fqSnhPeYz7fK7usW7kaXAydqV2cPxU76f1euqfTmCGrtzOVfCLWg0mA5m9F+1w4TV4hOsLwOx7uRlR+WuoMOdGqGcvbVoIYqdcblrekojzIpwi1fD5kqz//WtMs+FrrMUAkcVHqm/9aKZjxdwGt
*/