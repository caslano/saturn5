//
// Copyright 2010 Kenneth Riddile
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
#ifndef BOOST_GIL_EXTENSION_IO_TARGA_HPP
#define BOOST_GIL_EXTENSION_IO_TARGA_HPP

#include <boost/gil/extension/io/targa/read.hpp>
#include <boost/gil/extension/io/targa/write.hpp>

#endif

/* targa.hpp
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
*/