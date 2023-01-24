
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
phrzEEvteXU2Ssfx0cHZmIQEK2cV0fm5uWn/qowEc3dtGVdLmSPz8sxrXZvKcjBKzJRipuJs89pslGLaXFsxDkqCYhE2uvPO6pJifoZKGBU2arHpiYn51poyCVPJI+Y5Ed5iZakx85I7CPVN5UWxhnwMYu31NfMhV7UvqbBSejqbGoop7SadH2xv11Vn26qb4G6pK8Owdj4jxN1ztLfX00Zb3jPG2XR+aWnJ00Fe0NNSSdSzt71p3k9XyVN+N6nn9MS4Z2tV2bzhkd2eQaYqnioMpJ6jg70LhpJ8Ys6G6mKpfg5iNpJHFmryMjzlmSk9y5JiPCdGRxdiEpLQOMWt6svyrLTZqEGXawfIIL8xlRGFkKvqoLKbEDvY3opVYduKnZuexlalJmC9tSWxCc5XsRlB7lgV5rVYSxVJ7FVRVmyMgynWQZ4P29vahI2w1MW6q4tj/XTlsfLoGeqs1NiJ8XGsOjMptrWqCOkzY6+Kc2FzQryxhkd2YHub6rEJSUlYFQZC7NLcHFZ+ByGaz3bM58+fWcrQ3FkqSbJMjA6KLc1NY6oyksS8tWXEbGSOgAqah6vibGK6aA4i0Ly6I/uro3FclTwilhPhJ2bKx4DprK8RU2elFJNnWAvjvb1in5ENLZXEzYNM1cXGB3vFEhKSwF1FXKypLA+jy0aNyypiX4DLF7pfokr4D9px3x059QftuP+PRf/L9fft38Pz
*/