//
// Copyright 2007-2008 Christian Henning
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TIFF_READ_HPP
#define BOOST_GIL_EXTENSION_IO_TIFF_READ_HPP

#define BOOST_GIL_EXTENSION_IO_TIFF_READ_ENABLED // TODO: Document, explain, review

#include <boost/gil/extension/io/tiff/tags.hpp>
#include <boost/gil/extension/io/tiff/detail/read.hpp>
#include <boost/gil/extension/io/tiff/detail/scanline_read.hpp>
#include <boost/gil/extension/io/tiff/detail/supported_types.hpp>

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