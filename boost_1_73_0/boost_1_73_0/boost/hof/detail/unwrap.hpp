/*=============================================================================
    Copyright (c) 2014 Paul Fultz II
    unwrap.h
    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/

#ifndef BOOST_HOF_GUARD_UNWRAP_H
#define BOOST_HOF_GUARD_UNWRAP_H

#include <type_traits>
#include <functional>

namespace boost { namespace hof { namespace detail {

template <class T>
struct unwrap_reference
{
    typedef T type;
};
template <class T>
struct unwrap_reference<std::reference_wrapper<T>>
{
    typedef T& type;
};

}}} // namespace boost::hof

#endif

/* unwrap.hpp
WqHkJWSXFw0SIcRRuNjkSbbLG47HdB/H9a9qU5aFkGHKIrkRKOs45/soFLOnHwAj/wlOYE/7tiiPsoiLrLoi64k1DlAqqP6DGf35cO/OqJoeAhygL1S0qTFTXz7YE2P2Ct414SkDFER39lF9+eAF/gz8aVB/+RCYtmMGEGCsV4AQ5yTd9yej7tL1xITSb2TxYaT+1fjNeL5Z79OIuTnaSRyrJwX7Y8MFI6MwYWW1d6v3q9nZDlpCu76zKyMhVXJ1m84PAQPe4saEuPOgZ1WV4XcstiUWnp79qdUVd3SSm0LalZnirU4GXimcitQttdMWmDkN4yyrKip5pwxqc/YiiWykNWJzz+qu2eYTE4fahjP66Q+RR4APeC1Kll+SGF0yIQpx00CEWVGUmLwEnlYpoB6NmqoZEdXfm80brRCh6/GjWlINlyenwTKeM6xNZcl3P3dS0BG4rntrng6yIsbnoXPt+wQPQc6wGd6qQsWu5VN/0IYt5gWBjtQyoaN8Kun944cSlrE1y+X59VDrIehICUnVl50/ZY/jHl2pkXZv3kYwdObTN5Ls1cE/yJFTU4Dr11N9uHG0r3FGT3S4g7UYP3IZym1Ztw+t7WDt2nXk10ty04fQguVLuTrvT3ZLpgs80Zoa6ej7gsmoHT7U
*/