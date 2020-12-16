
// Copyright (C) 2009-2012 Lorenzo Caminiti
// Distributed under the Boost Software License, Version 1.0
// (see accompanying file LICENSE_1_0.txt or a copy at
// http://www.boost.org/LICENSE_1_0.txt)
// Home at http://www.boost.org/libs/local_function

#ifndef BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_HPP_
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_HPP_

// Boost.Preprocessor author P. Mensodines confirmed on an Boost email thread
// (subject ``check if a token is a keyword (was "BOOST_PP_IS_UNARY()")'')
// that it is OK to used `PP_IS_UNARY()` to check if tokens match predefined
// "keyword" as it is done by the macros below (even if `PP_IS_UNARY()` is
// technically only part of Boost.Preprocessor private API).
#include <boost/preprocessor/detail/is_unary.hpp>
#include <boost/preprocessor/cat.hpp>
#include <boost/preprocessor/control/iif.hpp>
#include <boost/preprocessor/tuple/eat.hpp>

// PRIVATE //

#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_(a, b) \
    BOOST_PP_IS_UNARY(BOOST_PP_CAT(a, b))

// PUBLIC //

// `checking_prefix ## tokens` expand to unary (e.g., `(1)`) iff `tokens` start
// with keyword to check.
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_FRONT( \
        tokens, checking_prefix) \
    BOOST_PP_IIF(BOOST_PP_IS_UNARY(tokens), \
        /* on MSVC this check works even if tokens already unary but on */ \
        /* C++03 (including GCC) this check on non-unary tokens gives */ \
        /* a concatenation error -- so return false is tokens is not unary */ \
        0 BOOST_PP_TUPLE_EAT(2) \
    , \
        BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_ \
    )(checking_prefix, tokens)

// `token ## checking_postfix` expand to unary (e.g., `(1)`) iff `token` is the
// keyword to check. This check only works if `token` is a single token, it
// will always expand to 0 if token is multiple tokens (e.g., `const *this`).
// This check will expand to 0 with no error if `token` starts with a
// non-alphanumeric symbol (e.g., `*this`).
#define BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_BACK( \
        token, checking_postfix) \
    BOOST_LOCAL_FUNCTION_DETAIL_PP_KEYWORD_FACILITY_IS_(token, checking_postfix)

#endif // #include guard


/* is.hpp
yAtPJ/12k/73gZOcasw3duJ7t6nz18AArc/V/TISF0BbfWTgFidN8ix8vXewhtM2Sj6kSa86y+RhXmAyebfKCOk5f2fK64lgWXmVnDWpyPHkWegt1/1cSmyKty/RPBP3SDQ4O3nyqL3xN8jTcd5m/NRQPGhmG/se2sgriidyLZ9r/RRP5Fp7T+f6emPPCKRwH9r7Tfu+RdZYSZ7pmm397ggoP54M24x512Ul1lslur4qIseOdq/pmY7IscyUaNnWIFq2WfUg/fst7qjtmF/PUPgZPwbeTjpFb6fa9YLz6LUUF5SUFOT71YLL6wOr3vaaeBYHLbKNNBLvc/j9Sv83x7HtNyK//nd3db2bI+/uNcb9S9qo1l0Ye3VPTryw2bX/g/H9xrqGdvG75kwDrpzOtb4HBFSRj5mwNex7lb5d8RrK64x7w1C69o9s4IUp8sk1Xzz2vcoZDIveq3yRsVf1+gcLTPhDQuXOfND9vvJ2WGbY7rXcGQ96PjeaMAsDxu6l2bhcP8fIZeP31aCt3zHRlHWb2Hi8PsfnJuyzFa5/WGr81PLWZKw09h+DA2h3Ebk0z1xrY8rgYMKoK+HJ8fNMPhp6cnyp7GVlflbxtKllcmyHce/M/FIVXYuU2xx6/nnORciWFm77PCD+mk30prVG07fHhexFsl+AOa+hicfImxFaEzFXsso150gm8Xe5flW9/fSrFr378/tV0sXO8a+XKMU01PMWb91n23ei1zgMlP1b2d+McQ9ujnY/cnPq/6VOdtHEgKtDfPbTw35qltr/D/VOmHzaD99dmtTJ/i10sl8M6BtP39lrYDfM4xLsDTRH2lxzAQdqTi0DHgdLNaeWqbncg2A2PBgOhYfBfHi45k5b6vzzVjr3vDWcBdtozqA9vAB2gPNgFrwMdoSXwy7wFqX7F3gkfA52hy9pbvBlzQ1+qLnBT+X/C9hbcwt9YMCdG4JV4QmwFhwA0+BAzS0Mgq3gYIgfM8d8OsyGM+Cp8Hw4DM6Fw+E1cBS8Do6G98Gx8Fk4Dr4IT5NOWA58FY6XTlgu3AonwG1wMvwXnAqruDqvsCYshg1gCWwBSzU36ATVV9d32hp4LGa36vMv0tm5G7aC98DesI7mvuuq3urBkXAl7oXwAVgKH4Sz4Sp4DVwNF8v/zfBv2G+Dj8A7dR1RYnRuXpIu0BvwWbhd5/h/qnP8g4FwPjAmHw1gPdgYviTdnn/ANnAt7AxfhUfB12BP+DrMhm/AYXAjnArfhvPhO/Aq+C5cBLfCh+AH8FG4Db4Oa7s6kMrPx8rPTuXnK+jqftUPhnW+DoGfwSPg57AD3Am7wC9gN/g17AW/gePgbjgefgsL4B44Ge518wn3wZvgv+DN0CHd22EA3gerwSdhKvwHrA7Xw3pqB5lB9ZfUp10De2MaaI64iXQym8IGsDnEOC2km3eQ2sfBsBs8RLpjN8NesKV0AltJd6w1HAvbwDzYVrpe7eAc2B7Og93hMng0XA57qF0cB9+BveC7sLd0vPpCyt4ZABvCgbAdPBEeDwfDU+EpcCjMhsPhqbAYDoUXwuHwYjgS3grHwtVwPHwa5sINMA9uggXwbTgRfg0nw9SgdBnhVNgSToNtYRFsD4thFiyBA+B0OBjOhKfDWW65wDlwNjwPzoNz+XcZvBBeBy+Fy+BlcLnsT8v+LLzczS+8Em6FV8F9cBH8CV4LD3J1omFLeBPMgkvgMfBmmO+2w1WpTvPVqU6/1anJ+dLkfOmvNl96Ju1pIebh1cm5zOQv+Uv+kr/kL/n7vX8pmKm/+fw/myOWFk0vnVToagH8Ih0A93z+EJne29JdG5E/fcqUWUYv4KIM7U2U7E8kf8lf8pc=
*/