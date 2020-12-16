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
3+EO++W3VLp16daJKSMXznceeH6yp+lHk6Vm8aazs5XJ8onqTOkO15o81rjDLe5wrXK5lLzDsXuCPTxVKR2dOUbLcjPHSgarmX/q5p+K+WfW/NPAP9Pmn6b5Z8H8k5p/Vs0/HfPPuvnntPmH4q26/x8DeIei/JT9ccT8czf3+Y7Z/2+a/Xtz869N9nme59I98SCR7slaqTp9x/KxE7NHs3QPswQgKWt+8tr41gY3wJ/LHOWKH9ZSBiLUrhUgaUn5CS5td/PSVi3NzsxMHa9M3rGEX3Q5kvvi774NH5IWkh0U7RKk+am5hUvL40RaikfLpVp5arZ+/I7HSmMtLKeZGro8XOsx7ncv8PJwvDRTKVenqjMzKg//j56UVY60srh0nBm3YS8d5VL9RLVePTFbVun4H8OfR9mdZIXgiO8wnuOfJz7Hn63NzZiNVNl892vZvNVtN6Q57jF6M7tBw800WV5NMuMq2RhOA6ix0CYrU3asv/ilvl4Y972xrteMMRe71DeIucLDDbPWP2X7dozHifl7PO+ZqU0tTFdg5zS7KyvNAY+xtFm/O/77UnbsocHB/v19M/6X58g3aW0Iync017APEpLbwQbzIQrPGAzZuPgD+nvtZH+QvV3h7PVv5c2pbsp5ai63zzQHxLvx6jtmbAnKJrO3nPzsASOX3bAps+tmslLW56+2HniO5jbu2zP5W5H+xPef8/fD8vvtzofvR+T3Tf5+U/n9x/z9ZvL7rc6P7zeX35/E328hv+/x91vK7ze7AL7fSn5/HH+/tSyD7+D7EbDFC+KbVwaP4u9eGXyDv3tlcMML4btXBhv83SuDr/D3m8s0Xu/C4+83xbcH49vN8G0X326Ob9e6yPjbLfDtLL7dEt8+i2+3wreJi46/3To55L4Nsm/DdbITVttr7XWzoMRv1WVjdnv9VGe9bW+hTlvL5hU6cwzG6vgFLmVsNrtQb3wcsLydrXnxTO72nQTz5ctY2UI1XJpxduXlSB4uyB/Cd72Yex0zv7Fh6nMVCNzGfU3Lwf8DQ9iFc30rV3t4nEWKPNzScmLtnUMy4dwe8YTvpyEc5NVbwHbhVxC+PXsQxn9HHT8II68puT83mie5SVy2g8SFeXeR5ula7U4LdX8dcZHlHJkrt1Mcn6sY6x8J635V5wtyE04aD0fVUz+nfCV3DeiFPFsBpUBZPSDQRxmGkT8k0Bn3a8TxCMilT9FfA9okJlMqF+az7G/gMAOs9IKdH+Z3W0G7C9P6Cp3W9Jwot9fnlFvYBt9JnGgEWC9EusJDTi789+bUX7ie9EHi1GY7kffQGWO+f4i+V+5SbxJ/wjXLrPw/gTwJvzAyJNOtDx+N8/V5hIH3MPF7E/cuyb2Nj67uv4bfse9eZvYg4kaBZL/7Yfx3iNMwP4kypsKZ+WU87xQ/5/03gX6HOvF73Xcq8BrgdFuS/c5fLMN7HYJ6eBXJ8zZsmjj+Ho8DmTZMcjDW3vx0XOCg176kemfyi7Nc9p/oHy9Jcs6Ezf9l8Rv43fGjse5enphw06r5fkV8542xJp6r0Hc0Zpe2a+i0meQj/9fNyz8YlKMcWoTmoD4V4/ID5vo6zzIcjMtaeUi3OB1ajFBsnm98UOuN1OHDB4NxAz+XfQaUBn6sm9F3tdnY/WaQuN+MF4Bde7jZfyi7EhA5sjLcSWbXqFGjRo0aNWq8rzHJaNRoqrqOruquy8yYjRrtdKZ7Mq0z3W13T5yIYjwQ71sRXDHICp6oeCCiECGIoELwgEW8kAUVr8UDFg/we/Ve/e+qUXezSSb1f/+7z//9xwOsM0DtWvtsq8z63Dxpt501Dk9JjHWOYHRP0q1zCNWbjBxlu0c71aE=
*/