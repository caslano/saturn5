// Copyright (c) 2006, 2007 Julio M. Merino Vidal
// Copyright (c) 2008 Ilya Sokolov, Boris Schaeling
// Copyright (c) 2009 Boris Schaeling
// Copyright (c) 2010 Felipe Tanus, Boris Schaeling
// Copyright (c) 2011, 2012 Jeff Flinn, Boris Schaeling
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROCESS_POSIX_SHELL_PATH_HPP
#define BOOST_PROCESS_POSIX_SHELL_PATH_HPP

#include <boost/process/detail/config.hpp>
#include <boost/system/error_code.hpp>
#include <boost/filesystem/path.hpp>

namespace boost { namespace process { namespace detail { namespace posix {

inline boost::filesystem::path shell_path()
{
    return "/bin/sh";
}

inline boost::filesystem::path shell_path(std::error_code &ec)
{
    ec.clear();
    return "/bin/sh";
}

}}}}

#endif

/* shell_path.hpp
Cr8DFWdBxQy7whorj5ln7rad31HJ4+Ph4yHCabo1YJd+1gcpGOE54dWHaY29W1spxnHFg9CbOgvqk4h9VyewurcuT55R4tNoNPzyaYKVJydnTr/6joQvmmbO/962a5njLpJioIz1b9fTIU6dxFxK3IRC0a/djVddhUkF8Yz0sole5jzN6B62rVU5IypHUbnW5/rbvHqc2+UHHiF1OOhYTwizeh2dppXwkT0s3DtccZuRP0hfsL2v8pJk7BUCZLDN/d7qFXW12aNvDGv8Yd9epLe/4MUciCuebGj+2SrhyX6FzuHGAi4A53wSDgB1qiFRkDD+YzXkCwL9d/wbSsiXoEus8yJR9zTjQiRDatU0/t8HuY7loORPzSyqHcHNDVTxp+gxG3/zwmjCb0WD+crymghQyl2ACWLYQB43FZoFOSU5Ra4k42GL+mhfJoyIGH6ruQiiOrSrMINmY/9KigkLImvSltg9rFjn9mtSufoKmvhhLrkZK28GmP3kfKzrWe+RPdXcDYvb+qjcn1YCsrZOIcFNY2B7Uu2l4Z8k8OpyZFPauo9h1/EtdWTMfp2Qkq9YKtqAkqCTMVJe9XoV5+8OmNs/HLCyVUHiYO5r/2NnBo3E+POC4xjm8wf5w7yb4xvBSYp3Bo77efHQiNmlZqYeJ09DR0gcmftwPIUMTtcr1rppvFwyt/mdMiP7w/g0/3md4XWwnSHXRXHdyxTu
*/