// (C) Copyright 2008 CodeRage, LLC (turkanis at coderage dot com)
// (C) Copyright 2005-2007 Jonathan Turkanis
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt.)

// See http://www.boost.org/libs/iostreams for documentation.

#ifndef BOOST_IOSTREAMS_DETAIL_DEFAULT_ARG_HPP_INCLUDED
#define BOOST_IOSTREAMS_DETAIL_DEFAULT_ARG_HPP_INCLUDED

#if defined(_MSC_VER)
# pragma once
#endif            

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

// Obsolete. Remove.
#define BOOST_IOSTREAMS_DEFAULT_ARG(arg) arg

#endif // #ifndef BOOST_IOSTREAMS_DETAIL_DEFAULT_ARG_HPP_INCLUDED

/* default_arg.hpp
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
*/