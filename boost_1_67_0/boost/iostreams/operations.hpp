// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED
#define BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/operations_fwd.hpp>
#include <boost/iostreams/close.hpp>
#include <boost/iostreams/flush.hpp>
#include <boost/iostreams/imbue.hpp>
#include <boost/iostreams/input_sequence.hpp>
#include <boost/iostreams/optimal_buffer_size.hpp>
#include <boost/iostreams/output_sequence.hpp>
#include <boost/iostreams/read.hpp>
#include <boost/iostreams/seek.hpp>
#include <boost/iostreams/write.hpp>

#endif // #ifndef BOOST_IOSTREAMS_OPERATIONS_HPP_INCLUDED

/* operations.hpp
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
*/