
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
vPgtQSsyA73xEmbLHuTcChvD9Sy7SFcZXI8Xi/E8W0N6DuP5OpD9ms3PaOsFiRnAu9agJXEDommlwHKv+X4tifpCFdKXCD2ntWQWnW9HdS+iqhANKcVcypwXf6AiF6F2pFcZlY1ZNj1fzSfZLJ1HRBJZ8YAsbChRbI1wyIp8UNTcwDD3VYUmhn2IfXgeqgabPIaNFiUM6SCYkjt+9DVIQ2GQhw0HqcnC7kQHC4FcKLowhowaBdliNQ1Ztr4oQq7ITE4mdk52JEx713rHAseAtsZTnUm9W+5GQ/pq4+jNa/4EosPEw52YaFWJWxgWXR8c91HR4QUy/mqZDdb+AlBLAwQKAAAACAAtZ0pSosWX50gGAAAAFwAAHgAJAGN1cmwtbWFzdGVyL3NyYy90b29sX2NmZ2FibGUuY1VUBQABtkgkYK1Ye2/bNhD/35/i0AFDHLhxO3TDujTFvDzWYGkSxA66AAUIWjpbbCRRJSk/2nSffXeUHMeJTblAXTSSeb978Hi8h7u7P+7Tgl1o/Aj/X9CHnp7j0uhPGLn1aCHuoPpHXB/p2aSkC0uWO9GGZpY72PEsotbyht+FaFL0kW3jP13m/Cj4lVaIjTkPdTE3apw42Dlsw8vXr3+H5/DLi19eduBI5gpT6DvMh2jG
*/