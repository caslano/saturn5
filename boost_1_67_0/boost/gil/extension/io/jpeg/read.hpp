//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_JPEG_READ_HPP
#define BOOST_GIL_EXTENSION_IO_JPEG_READ_HPP

#define BOOST_GIL_EXTENSION_IO_JPEG_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/extension/io/jpeg/tags.hpp>
#include <boost/gil/extension/io/jpeg/detail/read.hpp>
#include <boost/gil/extension/io/jpeg/detail/scanline_read.hpp>
#include <boost/gil/extension/io/jpeg/detail/supported_types.hpp>

#include <boost/gil/io/get_reader.hpp>
#include <boost/gil/io/make_backend.hpp>
#include <boost/gil/io/make_dynamic_image_reader.hpp>
#include <boost/gil/io/make_reader.hpp>
#include <boost/gil/io/make_scanline_reader.hpp>
#include <boost/gil/io/read_and_convert_image.hpp>
#include <boost/gil/io/read_and_convert_view.hpp>
#include <boost/gil/io/read_image.hpp>
#include <boost/gil/io/read_image_info.hpp>
#include <boost/gil/io/read_view.hpp>
#include <boost/gil/io/scanline_read_iterator.hpp>

#endif

/* read.hpp
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
*/