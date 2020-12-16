//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_CL_HPP
#define BOOST_COMPUTE_CL_HPP

#include <boost/compute/detail/cl_versions.hpp>

#if defined(__APPLE__)
#include <OpenCL/cl.h>
#else
#include <CL/cl.h>
#endif

// select what OpenCL core API versions to use
#if defined(CL_VERSION_1_0)
#  define BOOST_COMPUTE_CL_VERSION_1_0
#endif
#if defined(CL_VERSION_1_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 101
#    define BOOST_COMPUTE_CL_VERSION_1_1
#  endif
#endif
#if defined(CL_VERSION_1_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 102
#    define BOOST_COMPUTE_CL_VERSION_1_2
#  endif
#endif
#if defined(CL_VERSION_2_0)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 200
#    define BOOST_COMPUTE_CL_VERSION_2_0
#  endif
#endif
#if defined(CL_VERSION_2_1)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 201
#    define BOOST_COMPUTE_CL_VERSION_2_1
#  endif
#endif
#if defined(CL_VERSION_2_2)
#  if !defined(BOOST_COMPUTE_MAX_CL_VERSION) || BOOST_COMPUTE_MAX_CL_VERSION >= 202
#    define BOOST_COMPUTE_CL_VERSION_2_2
#  endif
#endif

#endif // BOOST_COMPUTE_CL_HPP

/* cl.hpp
YBT9+/I+fl/Fdxd56u+7fIrnvqXAXsArgV55t4v3TTaQd6fTH/JQyp93Ag720w+Mon5gDDCLfpAzgQX0bVLE65Q38puG8WMgb0yhXLov/QOnUn/VH5hB/8W7AgfSD+wg2X5+V4BJBv02mvLX3YDxwBzgu5Z/139c3re1ZH1lSTalEXQ5aC3osyRLPmcFK1jBCv+HEAk6tgfX/66j66sbhQSgq74AelYGUJuoiHXSmdY66T+zTvq3r4fWWvPwbWoe3tk5uBWsYAUrWMEKVrCCFazQU6Gn1//qPlax/P+Xrf9rrPW/tf631v/W+t9a/1vBClawghWsYAUrWOFfHLrd/3/tqJmN5cfOqtkKOn/1bL89VUNHbIrHrH63rD3KDx5XUl5feUy52811+qEaW/2KMPoyoO11ImhEKu7/WthfezOQ/r+2h+31cGHnPos2117eAdLW+qgQzvnbkbbWyEv1n6vzKfgq6xTDG7YDrUHFmv3qVO2mfb+ZDziee7AO97aI/hBG7uI+bXm54YF9kJmKe/zKg48x2cbaENqoLSMrIrCMkar/Lk8ZFdnV5d5yRB/vou9j8g3w+PSK9/iRV6TPLn26XVHTayprmV7FdO0zOjqu/fp7n9EufEZef14oH3FRvriWL1C9hjL92r3FoN2jkJ/Ds/egOrtCtttgbJGP7Vog2n10g1u225cufZ93oF3D/dqF/BEX+Uub/zXhZjIQM5lGx2UUHT3nsqMyJROZm4lMzEwGZSbz2XqyptGXinJvvv29x3tnVT765tktO8Q9AkPu86PU6ztuiD3ziCEfjv3+wZx7+swrrsK3KFK9fsshJ5S1RZ9340mrElrXr7hgraIUiPrk/ZQxbNqPC85YPWlGStt25yw0k92ZySrNZHpmskczWaWZ7K7jsi+3aO+ilVe+9vHTWVknPz21sfrcFW3w9yOuu1PP+uHkKUtnnLbz9GvicnptUhSPzwp+n/kOVoVpfVYAtb4yyBdjwGfX8LWEmN/mEPnwDgflc0d4ZHhrg8jx8pJtQoYXOx9ypzx86UGrQC2gd0GqXC9yb8ixQGvukDI+Kd8rwfUa0Bb8vhi4GrQeFLcLygQ6gLFjgaAc/M4HzgQZyQIX4fpykFcmuB6/t4By90G5oC24tgCoygkXAzM08sLViK8FnYnfm4CrgJH5qDNwHSgzXy9LLEQ8A1gBXAyaht+rgBVAN6gFv98E6eWMIFzrPw6kyhqB00CrV3hkj43jwHdHoAxyMa43g5arMkhgCzBlPH4D84FtwArgItBy0Dr1Guh3XI8dBSoID5BPLtbIKDMLfHLK/ALwgLbg9893+GSWCwp858xejN+rQGX47VyJ9gLXId4GiitEeXeiLriWCcxBvAzkBl0FegiklXW+i/gWUNwEj9wzA1gKUuWfLuDFoLtBPlko+BBvAxnJRBMnolxQEchfPlozEbygZtB6UAqutQHzNDJTZZJHbtofmAtygppAy0DaM3TvRvxn4LsqgvxlqYlF4VKWmoffM0FuUBPiFwObQUt2w3W8P42gi0HNoPXJ1h4HK1jBClbomfV/veuo6q6f/zeY6//WhcJf+IRpUwvGlU4on1q637gCSgEEz2zwlDb58xSTxSMnOEBzVt8SAzlBqrp+bRPrOL+ChLRArOf26Ktbz4G/87IC5CXWa7ozc8KNZQWtRvUSK//QZQaOpgCZgSzXbSAz6JeKe74yKlc48O+w7MBbVqzBGnqAaqcRWFYxu170/T76vgd/5/t+H03fSz8PEcZ932RQL3RgyP3eHKTf2wz6YqDqs96gTNHtXej3tsjAsgapcqGvpMxG/5zZ72k6GQb5TWU3TDeX3SC987KbtE4=
*/