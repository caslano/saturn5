// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_PUT_HPP_INCLUDED
#define BOOST_IOSTREAMS_PUT_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif

#include <boost/iostreams/write.hpp>

#endif // #ifndef BOOST_IOSTREAMS_PUT_HPP_INCLUDED

/* put.hpp
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
*/