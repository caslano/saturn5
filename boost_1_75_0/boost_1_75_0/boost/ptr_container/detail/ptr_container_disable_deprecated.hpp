#ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED
#define BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

// MS compatible compilers support #pragma once

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

//
//  boost/ptr_container/detail/ptr_container_disable_deprecated.hpp
//
//  Copyright 2015 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#include <boost/config.hpp>

#if defined( __GNUC__ ) && ( defined( __GXX_EXPERIMENTAL_CXX0X__ ) || ( __cplusplus >= 201103L ) ) && !defined(BOOST_NO_AUTO_PTR)

# if defined( BOOST_GCC )

#  if BOOST_GCC >= 40600
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# elif defined( __clang__ ) && defined( __has_warning )

#  if __has_warning( "-Wdeprecated-declarations" )
#   define BOOST_PTR_CONTAINER_DISABLE_DEPRECATED
#  endif

# endif

#endif

#endif // #ifndef BOOST_PTR_CONTAINER_DETAIL_PTR_CONTAINER_DISABLE_DEPRECATED_HPP_INCLUDED

/* ptr_container_disable_deprecated.hpp
htB6q5hzNTaug8g1961AUEi2CpGNXOiV60lj6a3iQTSO6a6SBitagF8UGxMWkZxzi5ONIDN1vbGi3kbFjYh1JitmPIGXk/QFwVoQVq6rTG+ueAUztif4rRHuQGZU+i+VBryes07UmmDpBreHV1KuWbsIOolmSgDXmKS/4hvv/Hi8urxzrDXKUpBa/eWxawqEoNgnjLcG2oS0ycLsdlHQSMgBz5wRLsl2zt4Og7H1p/lZHOA8nHPCfLq3de+EeW/syzFhzomyWrwzo4olMI5aNI7tznvmW/9xYm0jIv7sRuw3yHN8kfM6Z9ZkwGa23Pz7Kz/A+v9zE4CBs/62uv0ezMltOwau2oiwI21H5NnaGphELylBXEkyDMzG1eZLSJwE3buPtxFnknXTTBL9K0YR5mPWNUH2oc4dVU5c13IAFmi+diICGJAVaBLcTd6NhiftELBB9oL6pPsr7d/7QpKGyiBICyKSujxon5RmzgI5wyk5Iwz+h+oZsIAe6qf3+zfdUCajX+tdXu36p1CuvzLQ2Uh7kiI7vYMioILTioe4pM6x82f7PRoSKEpsX4uAKaeN2aAhEV+yk1hBwmQZzhcpROyw4f4iBSOU//mUkZWFt+xb5qIDmlIz0G0BHZdZkJgHCgGkCdFGhd425z1xebgUO6PUBrkLpKVYQf16dbyBd8M9G+r+aSNuMj/vvi32lY3qbah9ZW6wVgmeKW7Q
*/