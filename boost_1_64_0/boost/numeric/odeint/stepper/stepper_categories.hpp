/*
 [auto_generated]
 boost/numeric/odeint/stepper/stepper_categories.hpp

 [begin_description]
 Definition of all stepper categories.
 [end_description]

 Copyright 2010-2011 Mario Mulansky
 Copyright 2010-2012 Karsten Ahnert

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

#include <boost/type_traits/integral_constant.hpp>

namespace boost {
namespace numeric {
namespace odeint {


/*
 * Tags to specify stepper types
 *
 * These tags are used by integrate() to choose which integration method is used
 */

struct stepper_tag {};
// struct explicit_stepper_tag : stepper_tag {};
// struct implicit_stepper_tag : stepper_tag {};


struct error_stepper_tag : stepper_tag {};
struct explicit_error_stepper_tag : error_stepper_tag {};
struct explicit_error_stepper_fsal_tag : error_stepper_tag {};

struct controlled_stepper_tag {};
struct explicit_controlled_stepper_tag : controlled_stepper_tag {};
struct explicit_controlled_stepper_fsal_tag : controlled_stepper_tag {};

struct dense_output_stepper_tag {};


template< class tag > struct base_tag ;
template< > struct base_tag< stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_tag > { typedef stepper_tag type; };
template< > struct base_tag< explicit_error_stepper_fsal_tag > { typedef stepper_tag type; };

template< > struct base_tag< controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_tag > { typedef controlled_stepper_tag type; };
template< > struct base_tag< explicit_controlled_stepper_fsal_tag > { typedef controlled_stepper_tag type; };

template< > struct base_tag< dense_output_stepper_tag > { typedef dense_output_stepper_tag type; };


} // odeint
} // numeric
} // boost


#endif // BOOST_NUMERIC_ODEINT_STEPPER_STEPPER_CATEGORIES_HPP_INCLUDED

/* stepper_categories.hpp
Ak7RF5yiGzivdVNSViSV83vdLD2rbVa41LnCxb4qXHRY4WJfFS72VeFiXxUu+qpw0U2Fiy1VuOirwgt9VT6TrPyJxfSsbEVf689qS1NUPcCpep2i6BVOqTOcUmc4pX5wXoxjlfWrjCxso1B98t1nredUpZ5wSj3hlHra3AfST0wbanNHJHedySn6gFP0AafoA87b9s4rTMuguVXf8chZ9TBN0QOcogc4RQ9wSv3glPrBKfWD86K9y0o9eZ7SKSkZU/gGVV5JKutALj7yqd/Vc7iXssu4xFdwSlleYm7kZk87FT1+SltfeL/1Pa2rlbVFOGVtEU5ZW4RT1hbhlLVFOGVtEU5ZW4TzQre8vZ5WllfKCyjF2eXm/naZ5uraH3X7sh2bu9jQdMWG4BQbglNsyOa+GEK90eXNAk7xu3CKfuEU/cIp+oVT9Aun6BdO0S+col84Ze0WTlmntbmvXer2HdxrcNNNecraLZyydgunrN3a3I9S3hRTnrKeC6es58Ip67lwSv+1uV9c6vEI6fweEIwxNieGqukMJ6esD8MpPsLiEry1Y3nCt2nT0/JSWWjlexGFRWanLjEtW+3XnzlsW7WxaxQbg1NsDE6xMTjFxuAUG4NTbAzOlz6clVdaVpKZ4V7Pb5V61hxKmz9ofRduhhITwSn9Gk7p13BKv7a52uQRTh5RjjzqOTmlr8MpfR1OaQc4pR3glHaAU9oBTmkHOKUd4JS+bnMNnPVQ4kI4xSfAKbGizTV2kdfUhWvmwrUaaum+NNLm2kjuVgfXV7b5ZMe9F0tus1P3cOvgJjm4KyV3gYObI7l8p/4kN9PBbZV5LDA5xd/BKf4OTvF3NrdN6mCKQ95jkrvW5BQfaHNPyHQDHelek+Ub6uD2ynTXmZziP+EU/2lz70h5nc17FZ9qc+/KPG4y0yl+0ebekzqVNqT4yhnerWeUsuCfmVZQVuTuK7o2P9t4P1PxC3CKX4BT/ILNHRlqjVeoEk71ATMVHwCn+AA4xQfAKT4ATvEBcIoPgFN8AJziA+CU/g6n9Hc4pb/DKTEAnNIn4JQ+Aaf0CZurCLDm6z+aeShxAZyyvgGnrMnAKX0HTrF/OMX+4ZR1HzjF/m3uI2kHKwWcYy2o1kNCtDI5pU/AKfYP58V4eeo8g18QAPlpnoLKbvD7PhBz1j5wrdIH4JQ+AKf0ATjF3uEUe4dT7B1OsXc4xd7hFHuHU+wdTrF3OMXe4RR7h1PsHU6xdzjF3uEUe4dT7B1OsXc4xbbhFJuFU2wWTrFZOMU+4RS7g1PtDs77uaY5f/Wk5XmmZhafISb1nNX2ZslyeCQ3aQCcYo9wij3a3MmhVv0/0OAUG4VT/LTN/QOu8zbmmQ4uUN77jqMsTSXXbCCcYvNwis3DKTYPp9g8nGLzcIrNwyk2D6fYPJxi83CKfcMptgyn2DKcYstwii3DKb4bTrFvm7tK6rSDQ6c/yThvbDc4xcfb3Bx572LzXsXvwyl9yOZ+lXk0d+hFDLO4lianPBODU/ofnNL/4JQxA07pk3DKmAGnPD+AU/ounNJ34byImWTfPXV0GS+WNT/bPHK2Ytdwil3DKXYNp9g1nGLXcIpdw3kxLjrXwpg5l00qcVsLWntW3zRH8UNwih+CU3yOzXXArp7Dv9wjbK6j5N5zcOdLrr5mc3+R3HCTU3wTnOKb4BTfBKf4JjilDeGUNoRT2hBOaUM4pQ3hlDaEU3wTnOKb4BTfBKf4JjjFN8EpvglO8U02F4qe521h10STU/wVnOKv4BTfBKeMZXCKv4JT/BWc4q/gFJ8Dp8SVcIofglP8EJzih2wuTNraNodtDJDcYw5umOQmmvcqvglO8U1wPsQ=
*/