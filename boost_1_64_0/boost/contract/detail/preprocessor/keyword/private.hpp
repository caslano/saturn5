
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMAprivate ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTYprivate

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_PRIVATE(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `private` (this can be
//               checked with `..._IS_PRIVATE` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_PRIVATE(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_PRIVATE_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* private.hpp
EhNq72smVnEe3Q71ZuDV8m0K7kIc8vFU45QWKf4A1ncPlmwbPcshiDLDYU0Ud2F1lDd/l1UDWu+QOjyhFxNZPL7k8zLJyrQKL5vAUOgAlB2BTVcvubKsuufda2ydDZqJSO+bkRhpY+5JgR9eW9kdpMdhGoF0YwZ2PxluNzRgKAoaNyX6QQ83TMVm0P2TMw8RbP/W8CxeaqeBGJLkFf2UKHBR9Jm2WmHn19nu9f63YbqkUdGiKdamXd+93GimoVVbaSdDvr7InC6dpI1Fx0SYrDoyU5TrjDH9WVlZ+OwZ9SiFO6XPhxIEx/zmjAXIvo4rcFw1P2Vk7V6GspfVYTPVTDBnT5AFFASbW47QpcD8VVgfftA3Lwy8ki9uth0KWib5zR5gsp7JNxa29ERaQUff63bhcBK0TetAgZPOcNprm/1dcvTVNUxqtMp5eqZpyRk7j+FulwTh4FWU5TRr8fS23qFkTbgPa7IsTqkGIysj0QL8kgXtzF3BHeSMFUxB6yf8CF+WO3KdiD8nzeYr5WmE8q/vdp6mK2nyQuK5B7diizVZT5ful0txfkpmuQ==
*/