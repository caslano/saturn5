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
vmXqS0b0L8tyGEs8g+hQrQCnxen7MZ8BCl7yje1VR4v4AZkac77+0W7A8W1AMGLwH4fabYx8553HNeQTvgbtdlP44vzrCV/jo8R1UL3ZYEDStHpEILL1NXJjrJgiWAHM0NtoIOjLK+NiF5Sm+PKJXJL1mX/6RutFcmGqAjCLf1fKyDPHcMI0d9vyuBnmKhrL/Zq4TVzQXwkZvSPT81JhoI4VQ/gDoqbI8r+EE8MERP4i5IA4bKf5mYiL9pj8LpMf+AQhONX/q61QgNxcy/zWX+AZvYrGCEfgiqCvG+R3iXfv7MDywnXPDC+CMO6A0F65f6TFZXjlfen6NtO+7Sjaw2gBjO4Nh9CLZx4L3V3dccGQYQwB7YwkvoiCtpFahyVXU9uQv5QGEjAARGAouCri3tyZd3kFLIBMEJtY7t+B5E6RAmfa01Kd3/UbphmG0eDEsK/5Z1ByYf6eJ9S/vCVOJ8aswAFd+Y5wLnZzAug2XqdoniDDc5zvuA8lsCae+8VfwclmFlxhRakazXjikZk1ozGnyZ8qFgol/paPVQHRzZ+5UxRFTyC61eV7N4Gu20VF2ZJ+Mn7YnMVdjH/REjc1C1F81uFXB+He/9SQnnpQ5HffVzxVpJj768jMwbzM78qWBW3x1CQ+/ax2P7MP5JBfRzjohtuNuC3vjwc+xf9qdTfsth6JR6ZzO9nAYyeaH/NJnuGckQG4CyyhThv4
*/