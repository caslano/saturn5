
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMApublic ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTYpublic

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PUBLIC(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `public` (this can be
//               checked with `..._IS_PUBLIC` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PUBLIC(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PUBLIC_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* public.hpp
2FbQZHS3F8b9gzA+OLN0pMnwsZ8xKf+WnTw7MvnMasfrQbpfPLWmihNS8BPMp0GClbp12I9uTuF3O2G73uiJlWT+wB+vsEpfOHFEhe7oH5732aSnhf9rwv9VPWjOF8KWNLhDB4K34TRM7r1g/6qtZLUjNHVsm15F49had1M2tmOY6UckA5+RjIPaYpwsFzO4C6bLsbewGdD7JHWQPZrMuq1rRQPPUZQ7uJzdzKJ3szSybyUkhBTn1A/i8RiCaRzhS97bxeNUTRbR7edveAN8j/Bh8IWj1HufnfP+B1BLAwQKAAAACAAtZ0pSHRfs1fYFAABEDQAALgAJAGN1cmwtbWFzdGVyL2RvY3MvbGliY3VybC9vcHRzL0NVUkxPUFRfQ09PS0lFLjNVVAUAAbZIJGCtVlFv2zYQftevOHgPdQpVadIBXZummOs4ixrHMmy5XYAAAi1RFlea9EQqjrHuv++Okhw7LtY+1EEih+Tdfffdd0cFdx14/tM+XkDu4LufxP0m+MFnazQu9V88td82SJKvUP+g4R0+fyDUMTxafU2O4IesvkLXWSVNrHf0PUl+INwdgaQ/x2R8l9BXXKktG/u+Xm1KsSgsdPtHcPLmzW/wAk5fnr704YIpwSVMLVdzXi58eJe5ld8L9vAQ
*/