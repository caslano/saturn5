
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_HPP_

#include <boost/local_function/aux_/symbol.hpp>

// PUBLIC //

// Actual type-name for specified symbol name.
#define BOOST_LOCAL_FUNCTION_AUX_TYPEOF_TYPE(name) \
    /* cannot prefix in front of name because it could start with non */ \
    /* alphanumeric symbols (e.g., & for binding by reference) */ \
    BOOST_LOCAL_FUNCTION_AUX_SYMBOL_POSTFIX( (name)(typeof_type) )

#endif // #include guard


/* typeof.hpp
nzXA64p3DZkDL0Lm4s8Zz2K8P8uXh8Zz7T/j2C8nzp1y4nzynfdXD8f1WOZ2cYdsE3f4VnEv3yLuxHvh3rZ+SD3/ZO7mn+Gb+Sd9I/+M3MA/l6zHn3u/kB4fLjS67t/Bv977a/C3CvfMtfJdeUR0C6W74BclD/dJ5P27c3Hbll4NVwq0P30HfG55f02P05e8mN5/Vy1ChO7E7d4QufyLzszsSHCOZY6RkGnpHVYFLgLtqXf+
*/