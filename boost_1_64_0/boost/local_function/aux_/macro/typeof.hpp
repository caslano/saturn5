
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
siHfl9q3CjHIV8b9EQrnkfBlu6NjyQq+FEBB0YmhQLHsSqk29LjOYcEUrERiqfoVQuo3ozIk4CAomFmsY/5jbjMmArUZUdo0FveBOAlrn82van4JTcxV0/E3HF2JXrDSnpNVekxEqEqmJo+nbX1GufZgH7oQ4Gq20/FCUyWfkKBFC1Fu5bXT+HGabVGvQ3+NM7Cb7S4mRRD5sLjo+wXLoyRf3TBLdAPkoyN7AtrlRV6W4X2Ps70ZNlGvgG+DvxapMlviQlHI2Fo38q1qTeZqI2IBOi4CFNQGOPJ/7t7MlbXhit2nzmkPS18OaaEuOgmXak75EV4KqWL98WedReLU6AyxUUsxhiUDBM0lQAfSVypOmeW6VBcfdsShlpWm8jKjlu08fsarOfKpDYETkSf8Fca8vBRzyPYlyzk6jBwCsGrbWfHZ6ElXDYXqOtCXoS0TrSe8kmI/q7SrWrhnkaf+I5HaMFeZNkSRBbaOPrkkGyHOI7KrwMHz+f46kXuMJGupZ+Xl530NcVFSmt+UDiRU6s4VjxEw0biPDcfo0DySnM1c6YoIq/ZQ1uVNPA==
*/