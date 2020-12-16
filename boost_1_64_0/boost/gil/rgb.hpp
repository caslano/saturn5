//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_RGB_HPP
#define BOOST_GIL_RGB_HPP

#include <boost/gil/metafunctions.hpp>
#include <boost/gil/planar_pixel_iterator.hpp>
#include <boost/gil/detail/mp11.hpp>

#include <cstddef>
#include <type_traits>

namespace boost { namespace gil {

/// \addtogroup ColorNameModel
/// \{

/// \brief Red
struct red_t {};

/// \brief Green
struct green_t {};

/// \brief Blue
struct blue_t {};
/// \}

/// \ingroup ColorSpaceModel
using rgb_t = mp11::mp_list<red_t, green_t, blue_t>;

/// \ingroup LayoutModel
using rgb_layout_t = layout<rgb_t>;

/// \ingroup LayoutModel
using bgr_layout_t = layout<rgb_t, mp11::mp_list_c<int, 2, 1, 0>>;

/// \ingroup ImageViewConstructors
/// \brief from raw RGB planar data
template <typename IC>
inline
auto planar_rgb_view(
    std::size_t width, std::size_t height,
    IC r, IC g, IC b,
    std::ptrdiff_t rowsize_in_bytes)
    -> typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t> >::view_t
{
    using view_t = typename type_from_x_iterator<planar_pixel_iterator<IC, rgb_t>>::view_t;

    return view_t(
        width, height,
        typename view_t::locator(
            planar_pixel_iterator<IC, rgb_t>(r, g, b),
            rowsize_in_bytes));
}

}}  // namespace boost::gil

#endif

/* rgb.hpp
4N2YYyHzMYcDfB6GBUxgmS/H/NYc7qlVikdDnOPdAjnhljzxcIjDnmhL6yPRBm4x1X7Yg4/ywgNF3zZTfJ1lYIENiE/nmIDN4bpiXyQt8JOPOz4I9vECFi8ncWgPJ36O07tGxmGfVgQFDNJ4bbNV6WG9WB63DTFuOeSL2toZq/YFctzOyW+DfFNU8NSp4yh/Xq3kpjmHfQq+LIMwlNhSDnT0EexFCZskKL6EOz3JzXMIlmL/X6rqtUPEQ4mxuLtNTuC6xr9i/AvPok9+9gma+gXlHFf4ZdiaPK5Mjw8p4gD8wS71x99bm5Irrg7VoBPfYbrqnuhhlhne///2Bw0HNzwMy9D+z649PPki89wWftrnu8oraB/sWtd/Z9tRLXdtsdOlYzs7u+DawIRts4K29fLurQ5D221FW28su49ru/PY9jq4hxDOPXob2vONjcbtVa/Zw1zbTdR2MyXiOv3artudYUweQTDGWuHWFztHrTGp83pA83MGuMdOwKHXlTWbnRtwA82VP94CcNCN7KCJ7F+zswOM94cBBj2MhcRX0XR2GONTF27pYCjfzBrsPKvN8B75UlVTMIXHoJ///6a/rbnIQfV30R+CSOCFiUgASEULvG+LhAEI5Ol1xzOu/jI6WiOf4pexfqIGftVV1pSmPLgfV9f7vOznouin9fCOhRM0NP9vP2Qb5/0ctz6KaYPSbp0X7okxodw2vSEBnr8XQl9JkqRlCCeGM+vJdNYLGggF8CEBmQ5ldQVCrfbP+BeHb6y7bduCkENAxP943j6Z3o9eLnAiaEaVCeMR5xjYUjg3SZwaYnkQpmUnHJ3I7AVwoo6OSVv/kZdLXwswZgwUoO72x6cf746XAR1nzFGJnyn8poB3e9pj47MmsbmP1TmBn3sQegM4t4cH0h/Hao9iPFQfaQ2XPFOVkovpPoY5/Trv43hTwp/ZrpvnPPckHJGeS/fACZJDOPyJsoA0GNk0X/CJiZ8fV2RBB2hIcgjHafGsgpfH3KZuf17+3DjAt7ZN9aIei3B+z3FqvFeG8I3KqxEnXCU6tD4Fb7ifyigv2xFF+/b8S8CnMUolmzoZ4E+sDvC0V5+kco/4GZJE+YnTVE70OuMJJ2uesMLhCS4oDP3cfo3veTy8NSke9+NquR8wPfZjO31yHI79GM1PDanLr/L/ox8hM5g1LovUaWiiBsI4WYY47OU1IQ8ZTAskIo+bLkbbBYc9nhjE2BrYOaTpgslanxF9B1mVWK8Hj6C57PJlDvsUTAICstJePlySXX4g+oXZqwpqVMXmqrhH/i9iLIw1CKTISt6pZGFuRy4shidaykG3JvZEhNdWW5ngyQ7p6FOPOyxe10SMjWlqCP/uyLIoqwxl9G0ROAXS/BvY/axudzDO7BTnLWp8jGiYOz1PIZFvC8c53vqWu6g7mQ6mc1jgoFxdDM/TYMBZFQNHPvmn5B0U4AiGZEuKlaKVDniexMsCTBGcggiP6Ck8I/FMjZWLNDpO4TqY3imJFyKXAp69K4Y3TW9+StxLOIvhyJqVpOBpghTrJfFMACk+CwrC0wQpRoDjtTgza7CJOz2EJIignnVGkM518luUuElmXUqihnA5UX0nfE+ssTivQbltnIHggG/8qRzT1IorhVPZJmh5lLv9lPRzTDAVCZ5vR43zqGmrFx198sox3Q2dYX/lfTwlSGzeqdaubz8a6Bm6I+S6tmpPnMcdo1YcGeCPDmNx63V+1kR5W/s1PA4tLw3sO/ybnv1UvCHv2bPghdaPeGO3dxO2BZQRN87raS7Wdq3kBxF0rbPLAO9r9wVe9/bACo7u2XB09wfAPQxwXwfc323/DM6V5+zf6ADzfXB+Y4Q=
*/