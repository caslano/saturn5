// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_FRONT_EUML_ITERATION_H
#define BOOST_MSM_FRONT_EUML_ITERATION_H

#include <algorithm>
#include <numeric>
#include <boost/msm/front/euml/common.hpp>

namespace boost { namespace msm { namespace front { namespace euml
{

BOOST_MSM_EUML_FUNCTION(ForEach_ , std::for_each , for_each_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )
BOOST_MSM_EUML_FUNCTION(Accumulate_ , std::accumulate , accumulate_ , RESULT_TYPE_PARAM3 , RESULT_TYPE2_PARAM3 )

}}}}

#endif //BOOST_MSM_FRONT_EUML_ITERATION_H

/* iteration.hpp
/sNXISYvADgNRZWgasRdzu4dYaq0jFbqtzontYIj0z5aM9ScxoWqT7XyClqCc9QJt7sEEgMJjgln4Y3HI2mvBYpEmP9ZxMYWR698QdxgcfSLE87sEVrsMN+w3eTuDyZs8VMkEq+7U88D5cG1UgzeA1jWcPa/kZrL5M3BljvDDLOWL3P1YkokdqqWnF+G4lTyhBi1tMGoVTQs7zkmROH0FDvSbzLrCOtERouyjBvANjWxl1lfaCmPf4QenUPax+PpcNXTP/Flp3jsyZwZ8PPMAfnR+VqaMaM7gwqHczx85eSLJHzGbEcbSfajJMhXE/hVX3WvrMyjuv/ETCvzJeqVeXJi/LQD1+Jv2U1LE7U78WcL/vP4Tmnp/kt67sBOunF+F/48RYeju7zXy+X1h/u+VVuLsPXUc//X77oA+6sKViGH2bIYKTGrDBci3mBPkxl9Y3kkmqqx9t9DsSM/Fnx3X3H4twewJwdxAErWKADgJiy1FyIcug8r0ZHoeBFPmZLfIoaZgrTS5TUoU1Xktj6RnB1jzWamcKYkHiqdD70F6zpdJrBH4K6pODsmJfsaawoR553vhUtUIGrFB65xZ8bbs68BYukokSHJF4U82GzxFtaYKeWhfKvRtBztRGzryJ+MC+VXGgvgzB6UD0Gqp/Cqyf5QvndjZnG2tCR2M16JpyS1yzQgCeR70Wb7W4rfLrnVy6wD1lghpVUBnDRk
*/