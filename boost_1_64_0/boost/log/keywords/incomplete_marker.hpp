/*
 *          Copyright Andrey Semashev 2007 - 2015.
 * Distributed under the Boost Software License, Version 1.0.
 *    (See accompanying file LICENSE_1_0.txt or copy at
 *          http://www.boost.org/LICENSE_1_0.txt)
 */
/*!
 * \file   keywords/incomplete_marker.hpp
 * \author Andrey Semashev
 * \date   15.03.2014
 *
 * The header contains the \c incomplete_marker keyword declaration.
 */

#ifndef BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_
#define BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

#include <boost/parameter/keyword.hpp>
#include <boost/log/detail/config.hpp>

#ifdef BOOST_HAS_PRAGMA_ONCE
#pragma once
#endif

namespace boost {

BOOST_LOG_OPEN_NAMESPACE

namespace keywords {

//! The keyword for passing incomplete marker for the list of scopes to the \c named_scope formatter
BOOST_PARAMETER_KEYWORD(tag, incomplete_marker)

} // namespace keywords

BOOST_LOG_CLOSE_NAMESPACE // namespace log

} // namespace boost

#endif // BOOST_LOG_KEYWORDS_INCOMPLETE_MARKER_HPP_INCLUDED_

/* incomplete_marker.hpp
7CU6vTxZ9KzJRodwHOfY5rCpvSqNekZ9vxGe1YKxy0le/gRuQp5o5b/Pm+LeRw1vIuNaBkrdbmZ55J6P8g++59P54FJXzfMc9Q03U99MH/axzpsP7cOkfMUtxaXNpfnmCmrZ4Cb5TRnYeuY9V4W5vvrzH3fJG/Fv8iywje5TIwYvIrHIC8jIbNzvMm306iWziuVKG2n/iF/T/gZK/6hN3L2PNPoyXzXd1pKu0Fzv3pXjFdY5hD6D2F+DlCPe8LXO6SnaaRv7SPzcazXk+n8O/yfQYhYg37MSHPVIb0T0XM3hh+LvYauHrsuyTK+vA6lfDTm+lgi93sorLYjrQvb/Dq9owX5rLzOVWcLanylc+ltTn0gfbib/Aq51q9ND56L91v4+ttHMkw376YeJzZLf+2qbH7zx1Oc17zNzfgPn965qHRrvMXadiyDeOv1f7+VrjLuGp/dFNc9tRvfU59ad5zK3+Vr3uc0MiAxN+378V0WQdp3cHFG5VW2MfG5z1cZTn9u8r3/tc5uPw7To8PMHH5X5br+95o1ffPvZbcdX/KBN8yfXXB4bfh6i+7zC8PP+3Ocbhp9P95xlu1cPuzB9eee1a15IG7S2QdU3H/FeXeLZ8mfXrjnZfsrz3ysZ+5Obf/r4Xp7hn/Dg/to1m5t/9mXcnxre32Ra+z/Om1j3+X3u8/jCzytcFW2733fJz2Ma3vzVY+12vNWu8z1jB/MNQ/SPrsnY2H33opM3HNvy7I1b2jwq431xL9638ObPqjv94o11w9O7fZD9Yvh5ke7zH8PNKww/j3Jdtujn3j3yyCNFfcq67Xv9k69vZcDqHRLPh+/dOmJlTPQ3w+b0f2TR+/1nUR/FvfVbcxKKZoxb+fsGNxdndsm9n3tImUe59UdzJ+2I+cu7zz/Q8du71q9+gPk44n7y0Etxd373hrLz3/58VuHlHarCz7v8VtxHXTCn5QdTjndrUJxedX3fE+TDeJnHGvVAYbvM734+oOWJlk2aPT37nfDzPd3nvdZ9HuvnMkZZfvL8X44esD4w2/KMZrZ1LK6OReD+HjkQNBb3hzrmeR2MhbfDRLhe50TdCdN1LlJbeAfsre7nwHLYT/ePwWrf92j4oJ6vlX4Dkbs2Pd9SPd8yPd9ymAKv0vNerXMGSnSM9Qo933d0jPU1cKjOuTpf51yN07lWk2Apf5fBG+AsnXtVCFfCK+EquALeBG+AN+tcne/B2+Bq+COIm8x1XKNzmm6FD8AfwK2y7x/rW6XpfkzTbcb66hydeJ0j0RhWazo+hVN0zsM0nfNwNfxC43VC5xJ9Cb+vczlu17kcD+pcju3wG41Hsfl2RzvWeCQg+RqPFpr/LWED2Apmwtawo84l6KRzEnrCDB0T3lbHgrfT/G4Px6u+jp3W72f0Q3pe59jpx/W8FXren2g+PAmT4BMwWfZ1TLcH0fA+1PA6IH08/rltNs/V8AZpOgZrOi7XdORo/Rmq9XQYHKRjckdAROrNSHgRHKX15nw4G47WejNG681YS8cww+/C8fBGyWvqj2Nu3IWw3DcnTuNzL8yFW+BEuA1Ogo+r3tOq9wy8CO6Ck2ElvBi+qnPufqVz7varv3fV3x/gVHhY9nVukO97in7HORA0N6grejbJI8nHbjBTdL352At2glmwu+z75xxs1nBnarjOOQczNNw8DXeWhjsHdoFXwK6wAGbpnMB+cB4cqcdHwflaPoXwMnW/HC6AM3Rf46Pv/zmXS3w2aXzugfKuGibB+2E7+ADsDLdrvCgjqfdbde7nQxqPbXCS6l0EH9F2+2OYp+7H4D7zPlze30t8miO7EUvnZifAZTAFLoe9dc51X51DOwB+R+fgXAs=
*/