/*=============================================================================
    Copyright (c) 2014 Kohei Takahashi

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#ifndef FUSION_TUPLE_TIE_14122014_0115
#define FUSION_TUPLE_TIE_14122014_0115

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/tuple/tuple_fwd.hpp>

///////////////////////////////////////////////////////////////////////////////
// With no variadics, we will use the C++03 version
///////////////////////////////////////////////////////////////////////////////
#if !defined(BOOST_FUSION_HAS_VARIADIC_TUPLE)
# include <boost/fusion/tuple/detail/tuple_tie.hpp>
#else

///////////////////////////////////////////////////////////////////////////////
// C++11 interface
///////////////////////////////////////////////////////////////////////////////
#include <boost/fusion/tuple/tuple.hpp>

namespace boost { namespace fusion
{
    template <typename ...T>
    BOOST_FUSION_GPU_ENABLED
    inline tuple<T&...>
    tie(T&... arg)
    {
        return tuple<T&...>(arg...);
    }
}}

#endif
#endif


/* tuple_tie.hpp
HjsxoisLM7f0S16lbbMjbSXR5bE0TJwiLdMuH4QpM+aAqyb/8dgpIs5jdR6N7mWNTBwPWJYlRe5HTZqamn+Cq4FhCQPPEzBozQZjWIfT+j5H9eWuV5RFKc+IVfpi7eeJPoe5aez4oR926ZPvwmpVq82FYVh+PyB5yrMicIWT4vFBzNNAj6dJnubMK1POvcLvGpstwmymXIL7d04Ptlv7FAdpvUsjL8r9PJCp3WVtfynQ+xQmL+fMK0ScZm7UtsHI79oQ8/4tYcrJmPTsjvBKHGwYXhTTf4bYnbMwiQM3zaJ23tP0t95DoLr9JBWZ5zeDKvSwhu4rJN0BKwM/S50kv0U9g5KUVhhrguYYK2dZ6gV+HhqDLCPhgfZhlu5Q1vEwyW6h27V13zTl5CwoufDDJDQGXJhw1N17ENWd5Nxx4vBWurnWjftVppznFSLIU4/nMtnEV2F+M0tv5LupmxXlLfR6tt4R0ZunmcudJJdJpn4L3wsienPmx24ee+6t0luMl5fgXqVG71VTzkIQBXFY8LAa62CCDb0/sPRGUez5WX7HenuHTL1F6PmidIJq7IMJNuZdB008j0Gv40VOLG6h91QEJQzNnJwT9UxZ83mi1svVUhIGiOM8szxE23LuFE4cOEG7L+psywzjpU05OYtE6jqhX7IBvBeHL/dZef2+Q1afkQdFWXKvrbu7LeNd74fsNaUoSgv5+mj9MvbOlvnk4Ejrv27pD/w0i2PO2/rvvT1/dmOCvBdd+EHhx55+Y8q8BxDT3nsw1R0HHvfD4la6ua17xpRTsNgL4T+uX53y1Gqane/M0p1mDqgP3Vvo9mzdI1NOxqLYjTnPSibXDqGbxRc7SbsmuiMWpGEW+n52C91nlldlsTdl/rUHW/FmZRBmhVdWm1aDLetatBG2b0t/xqPC4X5+a/0u0f8vop+zIhFFLtMB57nhQeONCwO9gUv9+MGHUP2e4+R5dBvqZcmbd1w/hI6PM4eX3CkDUudpu9vE/pvwliz0/TgtvahrbE1bvbU/S+QULPU4z93SZ7ATp/Z3jLgjO7TtkXoct7cHJ1T6fXituj8cw+rvcBtph/ebtKW1jZ313mOBNinnx2883JvobZ57bV9eArixA4iNbdj7z/V8heRzwZK4jOIoL9jJOfh3tvpzcwQvl43XpAedg/9mzp+crRYtgQTRceRclilvLvP8QMQiYzL+jAdrO7qeDx7WO/CgXz4T8ubrcnwx3uiDoDEQ9Peb35Xf18j3X8H3sz+W3+FjTZDft+VY4UKvN9XbGLyhvzFckd0KfP814MtfyO9LK5DL6ttv5LffK52bvVrub58pz+vLb8Cr5Er+/Q/6HXx3PM/3+oUb96pvz3h6rwe/9XMn8yX/Y+HbBwE3fp361A9ekvPT/fOwvnx+Z2O5on+sRZe7vQ39ix300V2a/qSqLk6A/5yQmpdWwEYVkyi/P7Kms0lNPzceLMFtw/2G9z8t2uASkIH+FEVfnLbpaxs9g/5nmy71G/R37bHp4w3Ttkfv1XR4DBnquPz2hJr2Z4tWJ21s8h/drzEXBtszfblvhbRPIk06k+1Vk693H6RtzELRmrQfIA3rDNK8+yJtuDK7RtJyg9DAWIP2ofuZNJoHMwc0DXhmqb6fEBpc7GnQfvcATRu30nDPAzUNeCyZCwcNWm3nw+ryWniQpPXB/0GeHT8GPNX3q+q7ait95THWR1jGa4coTd6ibdaRIw+W9NrHHOuvbIJ3N+kfMumzbfq/TPpxpKNtKw+RdHmFel8ZoepQTfu2oq2t9rGxtuV7D7UxqpGijKtt+nBjDH7ZkPHChxFMXXkaO6616VsDcOfwxm7v6TVGPLyFgds=
*/