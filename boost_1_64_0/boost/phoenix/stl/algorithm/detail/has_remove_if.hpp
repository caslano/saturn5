// Copyright 2005 Daniel Wallin.
// Copyright 2005 Joel de Guzman.
//
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
//
// Modeled after range_ex, Copyright 2004 Eric Niebler
///////////////////////////////////////////////////////////////////////////////
//
// has_remove_if.hpp
//
/////////////////////////////////////////////////////////////////////////////

#if defined(_MSC_VER)
#pragma once
#endif

#ifndef BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004
#define BOOST_PHOENIX_HAS_REMOVE_IF_EN_14_12_2004

#include "./is_std_list.hpp"

namespace boost
{
    // Specialize this for user-defined types
    template<typename T>
    struct has_remove_if
        : is_std_list<T>
    {
    };
}

#endif

/* has_remove_if.hpp
XXZMplU51Z5/3/mfa8+yDWzas4en9LOX8uZid8pr3KUpL10oGfHFNCKXC2ODWMoWpDoOqVdUVxmjQT3f1OlmUnYK82pJ7GFkRictVRB2+4CMgWfqzxCCS9HUlmL/VkY5VJ97XSo52yfK3S9vj2vb0FT2M1IG+jlxGkY3G6mjvXbb7Yhs14lsWNNyx2U5+zo7wXzdOpP8zvH/Yyi/abysWIZHSJ1prsvDslx6ztR4JZYs8zpPyrhkynzLKiXW/RIL/dJKy1nMtJFp8lDa6kGZl8KAvYZMc5+X2rvNvxH3CrHtvxYr4/SNkOPWUFIf3lP8jmWb2Z2nuNDuZJwF7fmgTr9Q9f4Q4a09P+xnakd7LTHd+nNDifW2nRtaylbbR+rbTeobx3PwvaCUrfznha3e0+4TUq7bdly7UXn3Snnfk225hzTAdC78nqW8N3dOKOUr9zmhMn5nde054SBTnPsscd78+aDEelvOBy3lyL1Lv31F7reU4+bOBTPe//e3Mfvyqo9f3hLwAtluj5CGmI5f71vKW/7zQCmXU+eBlvZe5KsdW+PLIK4HHLDEc3PngDdqQ3JO6NQ5YF/LZ4Cf9hxwGHUY9oEl5ltz/ue4ndjWYRd/uYdY2nBPacMxSjzlP/ebdPA/136l7m3GjsgOkHGmpKy1cLip/RInZbU5T0pPsp4uOHOMDJLy6Z3ved/gfM8Xc2zOQ8ylryWfh9V91f9PxuPi/xE6fVV0zl+kv3cMgRkp83dMB3wo/bRV/e3VdVwi82RsHZt6Ox6oPWe+h8xjD9nXG0MlJppGCKDHdrJ17M6Q21Bvsg9az7cp70zKeoRYRxGfkdiA+eb2IvUb76jMpuUbsuxh0iLmfSDL+8u55a8cV1iejyzbMQtSZRuekTaYkjDdIEML8V6Wl/bZlGCnGszbRurXZmwVXxnPbrYcy2aRfFkm8rB9HWdlTi991ABdtF39PFSNsaRTH9Qn8ocO4MRtfWYI01SR+T0h8lyGhDTzdG3VuEdBUi9627KkrPN36v4EmXlTB72ZTjwsdW/72TydPDX1Viz1VkeOp6GkIPI/rFtvxoTMLINL45E7W28+cnyy1BvvY9pUbTeuN3X//FwZn69I9rWdeK9p4Y9V4xaYB/C+4THJUoarMn5MWZ+tqapjg/q8TR1bB9mREyW2eBzFvMhPbWIzLepybDf63pIq7SQvmPjJcy/TC035auLm2xrz7I9ha2pK3wjp+zoE72M9F46Uxn7Dz9ywG3zWhR9z+B3Z/nuPfM6pP/vkc83uc65E53POsu0ayzHH1IaMCVlZM5KUYcPjKUymZcyOWvI9t42f5n2l9dmFOlhN3Zw1bd+j1rE5zkleiQl2v3HJ/y+W534wGIapniueH+7CWA0Vzw8v3xgdjsbcOO9vmu9d+/T5xxqd6vx6Ue9VtXw+jvv3PD+8fyW5pocxOs9hdpN7uiqjJ1bBhlgVm+Id2A3vRLnXS67NkS/JaHevVxTv88H2GIAdMAo74hDshMOxKyZhNzRid8zCGDSPhSDXyOS3X6PdWAjVJB8vDEQfDMW7MAJ9JV8/ydcfR2ANnIxBOB+DcRHWxHyshUsxFAuxLr6N9fBdDMOjWB+PYzj+jA3wMjbCa9gYQ4i7CdbCu7EFNsOOGIF9sAX2x5ZIuXmOtFwnw4NSv764WMr9FzfpU4IB+Aa2xM3YFrdiL9yG43E7TsS3MB134Dzcifm4C1fi27gad+ObuAffxXdwP+5F8/aXa2OYpbP9/ynxXcIAvIwt8RccgL/iELyKE/AapmEJZuDvKNuf61aOt/8+yWc/BuIBDMWDGIEfYhQekvw+whH4CU7GT3E+HsFFeBTz8RguxeM=
*/