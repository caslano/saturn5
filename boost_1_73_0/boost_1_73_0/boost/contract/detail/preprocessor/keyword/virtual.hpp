
#ifndef BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_HPP_

// Copyright (C) 2008-2018 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0 (see accompanying
// file LICENSE_1_0.txt or a copy at http://www.boost.org/LICENSE_1_0.txt).
// See: http://www.boost.org/doc/libs/release/libs/contract/doc/html/index.html

#include <boost/contract/detail/preprocessor/keyword/utility/is.hpp>
#include <boost/preprocessor/cat.hpp>

/* PRIVATE */

// Must expand to a single comma `,` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMAvirtual ,

// Must expand to empty `` (not local macros, do not #undefine).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTYvirtual

/* PUBLIC */

// Precondition: tokens must start with a token concatenable to a macro name
//               (e.g., a literal or integral token).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_IS_VIRTUAL(tokens) \
    BOOST_CONTRACT_DETAIL_PP_KEYWORD_UTILITY_IS( \
            BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_COMMA, tokens)

// Precondition: tokens must start with `virtual` (this can be
//               checked with `..._IS_VIRTUAL` macro above).
#define BOOST_CONTRACT_DETAIL_PP_KEYWORD_REMOVE_VIRTUAL(tokens) \
    BOOST_PP_CAT(BOOST_CONTRACT_DETAIL_PP_KEYWORD_VIRTUAL_CAT_TO_EMPTY, tokens)

#endif // #include guard


/* virtual.hpp
GP7eB26ByWDPYVwIA0bnds1KDvhdipQrwzNgBjJu0lLM8R+hwBYcciE59KPxbTj6w4d1IdKi8bPRFZhCVzKDgt1zKHnKxX3tZsVKCzpHD+g/E8aiz8oKrQIMz8HycmkaNwSCSaOB3TMh2RzDMQuFtSvz9vg4rUqJmRxnOjXHaUtFUNjlk6xuEc2SbUCvLFgNleE+0HkfljoTOT2RIlxcVXMpTOE/wsKAKjvWJRguZeMOTQU3dQocpg1bPp2EFaIXlh5GK0PR1oVe7h1EWhtHeVUqDIe04LlMI/E+VCrjpTvviGijNCw7yr9TskfsGWiFqKDTm0I47cCcGWF8+BzGV9Eshs+9yaQ3im8huoTe6Lbxdx2OLlAbAqOWwB9WJTeIogSxXEnBs73gP7XTvSC+gv5sMozGcdKPoutwAK+gc/IaPlYKVX3yawc6Usyp7PA6ePU6eIkL9F/CmdkkhlsqMP6ilgy6m17BqHcz8J74vHuBxbRYRYW9YR3DV3E8xmbSXwSHgjOsgLOe3o6i8TScer8Ilcoq4/COwtXCK957znOqcf0pii7twPMCJSFRGfsIUHwFK+F56gIenblYF4NpfxKO4zAaeWOGlDNYaYEQSxIHA1VJ+YIkIRSjylKN1aLpJ7bkuBVAaGEtpIQ5
*/