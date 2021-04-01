//
// Copyright 2005-2007 Adobe Systems Incorporated
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_DYNAMIC_STEP_HPP
#define BOOST_GIL_DYNAMIC_STEP_HPP

#include <boost/gil/concepts/dynamic_step.hpp>

namespace boost { namespace gil {

/// Base template for types that model HasDynamicXStepTypeConcept.
template <typename IteratorOrLocatorOrView>
struct dynamic_x_step_type;

/// Base template for types that model HasDynamicYStepTypeConcept.
template <typename LocatorOrView>
struct dynamic_y_step_type;

/// Base template for types that model both, HasDynamicXStepTypeConcept and HasDynamicYStepTypeConcept.
///
/// \todo TODO: Is Locator allowed or practical to occur?
template <typename View>
struct dynamic_xy_step_type;

}}  // namespace boost::gil

#endif

/* dynamic_step.hpp
IRF8ElxajqQpw8On50spQRl7uYiiIxFCOZidlSXA77uyRa3diP99qkeoUiXnrOHwv9T95Dp1wcMDVilKolCLYfR54jx2YEzfuX4PpQqT2h7ibMta8dP90zeAYBF+Q+q3s1JqR9W3nUvr5mEYIubQ10MNxfc2ZvyLXGs2D0GGk+U8oYDtK9MfoCf2PCRvlhc39yJxKKMZKYodIDD61IL0PWWD/eFRxw+rVrofNHd2nzm4Nz3mCzbLmtWxWEbBD3k1jkM3UaQfCJKw/HPEeIQE4tZoCPiyUmBQSv9FsaJbmi8NcOXPtsZjMkJ05ENV90iTbHGwuZwS/kty77WloxSCZkC6NEk6XgRBB/shl0ex0gqsI0U4WB79VGugFG0Yx4hOYrZG1Yn0zJTSowAmAaMBGTSTR9kBLtEIhCzqgMulu9jJM3RsupPCdDdRDUVUumMQblodj4anMVOroTFMbPnfMF8/p/9p/Z++CoFVb/q3WjHXsMPl6k5Jc/UnHcAX7uoQ/eOyigcP4XpYctla0rxl9XxYKaLO9/OytdXIjrkY3Q42uwWvGLwGF1Xt4A==
*/