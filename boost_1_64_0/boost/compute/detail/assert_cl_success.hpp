//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP
#define BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

#include <boost/assert.hpp>

#if defined(BOOST_DISABLE_ASSERTS) || defined(NDEBUG)
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    function
#else
#define BOOST_COMPUTE_ASSERT_CL_SUCCESS(function) \
    BOOST_ASSERT(function == CL_SUCCESS)
#endif

#endif // BOOST_COMPUTE_DETAIL_ASSERT_CL_SUCCESS_HPP

/* assert_cl_success.hpp
Bt2Ude1gJq4nzkhH93+cfK2NuM0CP2m8x+sD4ohx/NEe4mY+v+Df6Gy/U881k+fOxu4XYwcYf89a7ttFxFntzAP67BrPsW/uPeKYK+kXYb6Y8B++ydiPqazTu4jbF6JDVqMnuhnxLu+NfJk+7uuIe8m/bFaQX+8mX6tF130VHWbE6JtkHV6J/TPjB/24L9j3tWbWLfUj5yx0pAiu+zvykwfog3Yx7BDz/wRx7UPUg1YRZ25jXtdzvKex17cR92Pv7Z9hPX+FHv0MdbQDVthT+gdKqX8Th8WTz6xFl8rIt+U+E6dfw+dMwk7MZD5Mw56E85ygIOarG88ZIx4zOaIf/4/4Yj56JHWjpB34Xer7u6fg56kDhsaga2HnzdOZD1XkKXWs3/eJA1gPrqzbbvYrxnZz/CjqtcQPB/8i70sk/iVfDjHqN7vpD7NCR7yM+tUr7MtAX0lPpC/mFuKTz9GBnIlbjf0I7G8OjMJ/YXfsD9pSZ8ZP4a/MH6F3oSd47cKvsC5S6av1XMxzzQPQn5vYvzgJf/oTeSVxY4YT+Qp9US3t6Cocp+UmjrvImvPh59NZN8yLlhHqD7OpN35Iv41R76YOuP4N4vNUG/w58+Y96mUvEEc9jV2qJk9iPSV9zv0tpK5r4vc4/2byZJ93eY4Q66DHlnjvUXRk5lf3VOyjFe8Lc2W+3EncarJknxzrnPcxO/6JvuWN/f0P9d1U8hcL7Oh0C/Rm+pau4bjBxAcO6LTz8Ns38j6STuYrel5pJOOSin6yHjvAuPlYsp/fDX/zMXrBLxzvauzFOXRu9JC+a+gP9UD3/wC7Rv3JmX2bw97kjY9j/2fSb7uN+Uq+nZg/hb4hdPED2Avm26HH0YPpZz9EvFNpRZ1rF8dFh4wtNVHnIE+7lD7OI8zjs/jP2ayzLuz3E/iFbOpc/2bd3WhHXoWO87M18Rc6YSX+agr3h/6HgDHypFLyvftsqYcTvz+Dff4cv74fvZj5G8D8GyO+yVhI/FOG37En7jhBPLmY+f8D+s4eW+Ix6rZPk1/zXLIk9h8mEo822zPPArBb7EcK4Pya70EHPY1/QU+qP0Y+NQ0/h94Za7zP5l7iDOLsQOZR3lVG/MR7Bv4ib7wF3dF4H/9W7NUa4hDyhrXuxEthxNsfTXx/1eXokW+jA6L/p6PPDTgTjxKfNtcZ+8rIE9A/EpnnjSn8/TzyrRLikiL0EeLWxGBr9qczD04xT9GHvUPN1Mc4zmvYafpzAu5Cl6Xv6vgs9NojHOc68pS3iSPRe9p+w+86WPF+GPxxNTq6sX8hjPEJwS/cynyJxK8+hp1IIT8PJW7Fr+yNZ30SX6bOwj8tYD4wnn3kH8Xoe85TWL/56B3XoZehK3iM83zYXfgv9PdDT2I/PzHTF0C/oRXreS+6COvfr4m4pIG61TTyFfyjDXF4Is+bTfwWv+3Ifk70cOdh6lA25M/Y6eZXpqKT836FENb5PnRnnlPSY+gAwfTPEBekXsd9IA4zv4M+eAv9vVsYt1z0KfK8ROIm+8+5b2u4/8+hm+ynjupGfXIDcSj+2JP10+NE3IR+2U1+7xhJHsZ6abuEOOZR4uyp/BzHdXwdu/4aehF94jlPkB99xvgHY0dsqNOd5rmRg/T1NKLfLMJekFf6of95n2CcG/CzzfRR/szxGO9YO/I41oujM/MuBDv4N7qQJ/t8md82k4irv8Ifv4WeXYlubKKfj3xiFXrj8CkTepUJO0deHUd/QSD57Q+sF3Tk5l3ELWfYN5TGejlk9Ifx3MpRxqOX+Ocs+nk86+Ml9mMuYj68Q7x2OzrSfdT/z5KH78Y+f4Q9y0Nfb+H9KXfRBzmVP8usqAtZsv8=
*/