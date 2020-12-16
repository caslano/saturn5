//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_CONCEPTS_COLOR_HPP
#define BOOST_GIL_CONCEPTS_COLOR_HPP

#include <boost/gil/concepts/concept_check.hpp>

#include <type_traits>

#if defined(BOOST_CLANG)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-pragmas"
#pragma clang diagnostic ignored "-Wunused-local-typedefs"
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#endif

namespace boost { namespace gil {

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Color space type concept
/// \code
/// concept ColorSpaceConcept<MPLRandomAccessSequence CS>
/// {
///    // Boost.MP11-compatible list, whose elements are color tags.
/// };
/// \endcode
template <typename CS>
struct ColorSpaceConcept
{
    void constraints()
    {
        // Boost.MP11-compatible list, whose elements are color tags

        // TODO: Is this incomplete?
    }
};

// Models ColorSpaceConcept
template <typename CS1, typename CS2>
struct color_spaces_are_compatible : std::is_same<CS1, CS2> {};

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Two color spaces are compatible if they are the same
/// \code
/// concept ColorSpacesCompatibleConcept<ColorSpaceConcept CS1, ColorSpaceConcept CS2>
/// {
///     where SameType<CS1, CS2>;
/// };
/// \endcode
template <typename CS1, typename CS2>
struct ColorSpacesCompatibleConcept
{
    void constraints()
    {
        static_assert(color_spaces_are_compatible<CS1, CS2>::value, "");
    }
};

/// \ingroup ColorSpaceAndLayoutConcept
/// \brief Channel mapping concept
/// \code
/// concept ChannelMappingConcept<MPLRandomAccessSequence CM>
/// {
///     // Boost.MP11-compatible list, whose elements
///     // model MPLIntegralConstant representing a permutation
/// };
/// \endcode
template <typename CM>
struct ChannelMappingConcept
{
    void constraints()
    {
        // Boost.MP11-compatible list, whose elements model
        // MPLIntegralConstant representing a permutation.

        // TODO: Is this incomplete?
    }
};

}} // namespace boost::gil

#if defined(BOOST_CLANG)
#pragma clang diagnostic pop
#endif

#if defined(BOOST_GCC) && (BOOST_GCC >= 40900)
#pragma GCC diagnostic pop
#endif

#endif

/* color.hpp
L3vyvPodQ0617suYUqetq1Pq9LmQJXjj1YnLS/uqE2ZM4xrvTuQQ5v1XgWEiYT7PuzO/q5qdOuiHCvvvrMCjLmTKMmtfA65jR5P4EYlPl6emg+wSb7uLxCdrGmZ7f4KP7+UzfkF48e7kXYG7+p+4e3gaY1F4pzCV7S/k86mUehLOfovgtzx7we3UvMHOEtvbgP1DhgsGc2KLb2Y4Ymb+XH6zDMeSq9O+J8JG4RuI29enaVuU8gNj8AjfcbcwtWugtjvK9ckJb50JPxBy1HtvE1gKcG5/DDF/LIRwLQXDOffWUO5yPdifSXT35boXpmcNV/093rg+B7m2DW3Slxcst+sKrAW2/GuAqZRgleHPyWv17/3poUwhFczTa/ANInkHHv2DvgSCfOxREjm24ci5/o5eo4cpRWBBiP53i8UFSdpoWmyMAsTYOLRIczSO8gxf2mM/Uo1J8tgeuIaaVbjtF0Hb/fXZHbudMNxXifuf+f1Mq/7Od6P1mvoc/Z3vRmv9gd9x3bzO77B36e/BmSV+v/9K/V2Pjbc38/Eq9d3v49RdT58T6qWT6iWx5FAplx0cUmrWRUZ3vUPAyfYXCwNDpVR6MDmQLeKlZKUljkwdrE1P9qdGQ5lHVlKmeh8udNeAp9jM2LF7VQQnvXMonVcPkA1yH+CWJY08lRUT1yFHTiE5WMTu5mAxmwrP7y8LOXhLXJW6OTdRD06Uev0XcA1Drnr3LkgXGjiguuFsW+lymL+6yd/OVS4nOn/xcywe82fSfoOTHnilKeL+PHYB+yoHg4T1mzhn5+KKsj/p8ByBVZPPo0153rBJf4eT/uL2Lvil8fpMXBlHBusHhZD2wrhm7fKy6tHEdWhxyBEvmvKdsVmJEw7xmsD5sipwvrEp2pqqB+tpWf8Ret1qMGKY/LUvbR4G8JSJ+6wr2z/SuId3y3Afz8KRMrbfM05YTFt8KF2bbOqGO7YqiouLXuXpmSnsXGLgYxttXR7Bxb1qLPDLODs+YWTWomRW63WoN0H0iN+MFR1Oeegn1rFMU+Muj11OsJ+cE81XjQDwHrajCF4HxsNhpFfxTDnvdspRD7EzBm9106de4wVu8lp04tGKfi1o+qp0wvLzHFn6oWlds97lfA90VRRPS67PYIgeZl3HV7pcdbplT3UEsRtnHKasz7Y63B3pgWz3rlIxMZDoD+yCUzP16fBdgXn5tZmpGnzRoH3zTVenPNwwwSuyfrUyXd68YUYrtekx+lm8Ycl8/PIMlrjjOH4xLs+uts4Xz0Y/cSzbEyKeaL43Zrin5iqrYH4eoy+wOeUGh+grwVOxTPstc8qvTuBqpxqbJgx/w5x53csy5Vt58/E7mCaWz+m50hR0pBp1gjnlw3apy55+StwyGoT+kGZfGWVZtkbxrEOMsAOO1aX9LR4tW1XSqEkv3KZFccYny6P4C70Lo1NdzPGZaJkohLC8jkWnFZmHyMnLZ2pinDsQKY+P4odvVUbz9AYDZ5dh2Q+OzBmGY+4w39mek4/RN1iHkX+sKV/WS8g/Pie/A9InKio9nAOa81UdlgxvrDlPLQBZHoea8tDw9Uwuy+PqOfl8U5/8o3PyO5TFvLxP8A/Pzad86sbN+ar9sd2vEW2aOmjw+vwew9m5OIqjxJAD22YUx397l5y2yLgweYJzoal3tz/kCoW+7UU/RTDgT3lCBz3RhOtvhEFvMrwbonn+ikrytrnjEXVt2vKDfijKI3xF38saOcfFXA236aigcODZmxdvxDs8+K7ADB30zyr0oq68V2X/cblq4g+2XiFTNxdR/2cd/o6g03dhKhmFw44a9fhoXsLw1pr6dXjJ8vhI6YCXMPipKHzGS7CuonA=
*/