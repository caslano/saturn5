/*
Copyright 2014 Glen Joseph Fernandes
(glenjofe@gmail.com)

Distributed under the Boost Software License, Version 1.0.
(http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef BOOST_ALIGN_DETAIL_ALIGN_CXX11_HPP
#define BOOST_ALIGN_DETAIL_ALIGN_CXX11_HPP

#include <memory>

namespace boost {
namespace alignment {

using std::align;

} /* alignment */
} /* boost */

#endif

/* align_cxx11.hpp
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
*/