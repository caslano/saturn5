// Boost.Geometry

// Copyright (c) 2015 Oracle and/or its affiliates.

// Contributed and/or modified by Adam Wulkiewicz, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_UTIL_CONDITION_HPP
#define BOOST_GEOMETRY_UTIL_CONDITION_HPP


#include <boost/config.hpp>


// The macro defined in this file allows to suppress the MSVC
// compiler warning C4127: conditional expression is constant

#ifdef BOOST_MSVC

// NOTE: The code commented out below contains an alternative implementation
// of a macro using a free function. It was left here in case if in the future
// version of MSVC for the code currently used in the macro implementation
// the warning was generated.

//#ifndef DOXYGEN_NO_DETAIL
//namespace boost { namespace geometry { namespace detail {
//BOOST_FORCEINLINE bool condition(bool const b) { return b; }
//}}} // boost::geometry::detail
//#endif // DOXYGEN_NO_DETAIL
//#define BOOST_GEOMETRY_CONDITION(CONDITION) boost::geometry::detail::condition(CONDITION)

#define BOOST_GEOMETRY_CONDITION(CONDITION) ((void)0, (CONDITION))

#else

#define BOOST_GEOMETRY_CONDITION(CONDITION) (CONDITION)

#endif


#endif // BOOST_GEOMETRY_UTIL_CONDITION_HPP

/* condition.hpp
/Un7J7D9lnqIRIx5Vu7tJAwuJZUuSrvauJhf5ZwrynoauFv09HPh56spjVhtzXrB3tjMnkChmHVy7rlC5mQD1sHmtXc1Rc9njLstZP4Y7IIeG5tJDypkjjRCZidXzTDHZf0c7FFu7CIlE0trM3lSn0WSiWg8931Mxn9uQlvvdM1HcBxDvQ8X9Q72xi7scJZM9LWjKjJ8+1hNUePpansdGFEMGtU4meQw2IHJ+NfgHzIQn2FfR9p/HQ0bYjtbt6jV3mc88bdFn+8Gv8Be90z68RIhdzPeZQ65WyjoOx2pYJQ92eKkWPYwpf0b8lHnkJ/KXW95PHtd8vynGOJSD8DnkF3UfSfYQ5ba2VEWW6ASIXML7Kkddd84qGNuN/Kx3VKXfBRqTnG5LwPR7uqoZvW8uLPLShX6N0MdSPs/8HftcePzvG9Eu6tOgG1v80x7Y9L/E9ygQ2Y1rkOUKIufvvT/TBpPHzgAn2Ockf6fYFc7yjyikuOlakR9V1WO+Fzy/LNjIP8AeeAeaxeAf4grn9fOuiIFO+seJ3sw2t588G9w4XO3vYq08XSJY6wLJ5JT+l/0HHbmUn7kYZgjD6E0WUuxvGel/BmM9Uuc7HiRPuBS7Tew+JXI8y+Qh+1c8wCrsUzu1/Ky/WexznL0PdhiMM05ZP2D77fzGW1BpP1vK+Y7djajPYiMfwt20JVNgQkZdBky/uWx8Pc374GOD2orepaxVsa/BLd7oZVLWgwWrvR/boNfgU3eeop93sykQ5Hxv8FebmWzx7yW8S+n4LxJFz5Zuqsc7xcZ/wjsna1stvjO0v51KmzaFzq5LYw+/h3glljlZY3hK/Xfx2EPxIVNowmLTlbu/4G9j5NtzCTU3MdgFOw1p+EsV3c2S8wSwT4N7AvNc7cyY8kwMckT48pgUzoesV1d2JrFKGeZTwN7pgtbU8Nz2lb0gT3aXN9BbZ/FKHIOexLBzpyAWBY9Dra2A1HOoQuV/s9g1y5yZbPtu8j9jxPhG+jko7nlni33P8Be31nuLGUu9z9OwhnZTpn18ubsY8vAbnOy2epa2j+ejH1lS3nz7GUKeV8Dc+13zEx1UMbSilPg62xlD8pYOh/sPCt7UMbS4KmwFzG3sVJ975itT0v/N7C3s7B59q3FGDrqNNhqWJjl1ePKavTTdGNqvDHTlHuZBX8e+ENc+NFW4Bnru/h0xO5Y6OCzrUOE7HPB3tAp+6Csw4rPgH2ck8+6FpLxv8D/2slnWw/5hexnGk/3LnRls7Y9Wf/Iw5wuRx5Y10ey/tsRX9BZ/qxrJCk/+F+61wFMdnLP94ux7yzoWd3lZ+2DUv+DPERkGdTUUDAy47AjBtnl+SdnQ++02MxV1WYlFkqDzlH30v4f/Bu6bHwdnfv3nRhztjsHeq8lJi7FL9E1ytE463h/A9gNJrYebM+QGTnIPV/Gv5uO8yBMbU2PmZTiq29p/w/2QjOb7PIMMs/5ciWizs81nm6Sc/fKseWVZaj2dAzHNLCdO7i9KAPk4+yllnywna22n9D1ngcfdCvXcAa3iq83R/IOZ9ljkvEfkZ/CJdb8NFBBpBnmmrL9nw89ieSWKmQzRpu5xM1Q+AUGPahfyAz2OBNbWE7VT0E2mHx/hot+MAPnrb5jyYPhfpSItypM5zrI8Q/8oU5+Ib3z6mNRsiBjiOks6/8C4+l4pwu/MZXgPOdsJtiV1vpnm+NJ/4cLoYdeauWGQ3GFey95JthNpvIeW1M1UXd4Q5PnOm9alHveRVjjCPmDFC9Pb2/HNHJy28FducfK5ToLSMb/7ID+ol9ei2Usx/xmGNgZsJdLNm9cvK/BG/6O5Okty19YPErx+1l8kwU7djHOb7Y=
*/