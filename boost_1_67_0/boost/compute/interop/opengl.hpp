//---------------------------------------------------------------------------//
// Copyright (c) 2013-2014 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_INTEROP_OPENGL_HPP
#define BOOST_COMPUTE_INTEROP_OPENGL_HPP

/// \file
///
/// Meta-header to include all Boost.Compute OpenGL interop headers.

#include <boost/compute/interop/opengl/acquire.hpp>
#include <boost/compute/interop/opengl/context.hpp>
#include <boost/compute/interop/opengl/opengl_buffer.hpp>
#include <boost/compute/interop/opengl/opengl_renderbuffer.hpp>
#include <boost/compute/interop/opengl/opengl_texture.hpp>

#endif // BOOST_COMPUTE_INTEROP_OPENGL_HPP

/* opengl.hpp
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
*/