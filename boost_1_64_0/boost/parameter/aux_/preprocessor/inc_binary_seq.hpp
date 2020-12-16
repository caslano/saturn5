// Copyright Cromwell D. Enage 2013.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PREPROCESSOR_INC_BINARY_SEQ_HPP
#define BOOST_PARAMETER_AUX_PREPROCESSOR_INC_BINARY_SEQ_HPP

#include <boost/preprocessor/seq/push_back.hpp>

// This macro keeps the rest of the sequence if carry == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_0(seq, element) \
    (BOOST_PP_SEQ_PUSH_BACK(seq, element), 0)
/**/

#include <boost/preprocessor/control/iif.hpp>

// This macro updates the rest of the sequence if carry == 1.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_1(seq, element) \
    (BOOST_PP_SEQ_PUSH_BACK(seq, BOOST_PP_IIF(element, 0, 1)), element)
/**/

#include <boost/preprocessor/tuple/elem.hpp>
#include <boost/preprocessor/cat.hpp>

// This macro maintains a tuple (seq, carry), where seq is the intermediate
// result and carry is a flag that will unset upon finding an element == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_OP(s, result_tuple, element) \
    BOOST_PP_CAT( \
        BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_ \
      , BOOST_PP_TUPLE_ELEM(2, 1, result_tuple) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, result_tuple), element)
/**/

// This macro keeps the sequence at its original length if carry == 0.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_0(seq) seq
/**/

// This macro appends a zero to seq if carry == 1.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_1(seq) \
    BOOST_PP_SEQ_PUSH_BACK(seq, 0)
/**/

// This macro takes in the tuple (seq, carry), with carry indicating whether
// or not seq originally contained all 1s.  If so, then seq now contains all
// 0s, and this macro pushes an extra 0 before expanding to the new sequence.
// Otherwise, this macro expands to seq as is.
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL(seq_and_carry) \
    BOOST_PP_CAT( \
        BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL_ \
      , BOOST_PP_TUPLE_ELEM(2, 1, seq_and_carry) \
    )(BOOST_PP_TUPLE_ELEM(2, 0, seq_and_carry))
/**/

#include <boost/preprocessor/seq/seq.hpp>
#include <boost/preprocessor/seq/fold_left.hpp>

// This macro treats the specified sequence of 1s and 0s like a binary number
// in reverse and expands to a sequence representing the next value up.
// However, if the input sequence contains all 1s, then the output sequence
// will contain one more element but all 0s.
//
// Examples:
// seq = (1)(0)(1)(0) --> return (0)(1)(1)(0)
// seq = (1)(1)(1)(0) --> return (0)(0)(0)(1)
// seq = (1)(1)(1)(1) --> return (0)(0)(0)(0)(0)
#define BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ(seq) \
    BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_IMPL( \
        BOOST_PP_SEQ_FOLD_LEFT( \
            BOOST_PARAMETER_AUX_PP_INC_BINARY_SEQ_OP \
          , (BOOST_PP_SEQ_NIL, 1) \
          , seq \
        ) \
    )
/**/

#endif  // include guard


/* inc_binary_seq.hpp
h93hx+F4+Ak4ET6g+nbC6fBBeC3cBSvhp+Ft8CH4DvgIvAN+Ft6pxyNTWBfgrbImwI513sy6AJl1Af4n1wXY+9SbuzbAXtrSEVw2N2dluLm4ZtwTuKO4bG7WBuOm4dbgtuNacSdweRsyawBkfplf5pf5ZX6ZX+aX+f0nfm/C9/8yj0e/0Tgr3///utCy9zYbrLeRi3R/gyrcBb15RphrzrGShGgSdGuzFOZXRXR47G8LPPa3BbF9op6UOG/nS8qANR3nNJ9F9Rh77dUvWbqowZ6TUnRLODxPv+fU+WrGvOIfifx11rlon4CLzT9esJzE2Hp+LfHG2HPanjmNb3KKdH4J+eU4ll9zP7lW/Za/RsdmluP6E3/SLW1tHvnio2LBkqoFyxLmb9k2nCFy861hnGW85bhfErqTl0UhnCpxllgX67fxDmWBnuRlcZeE93Iti1kSfgPvnX28qw0kloW9f9ItEo8vBbC47IGk5fGbsDvL5TJc525N0m+7r9C1MKbDSuIfjJRL/byG+lXzLxo5n7pvfDt82zBzrYrf3aJzmkgG51fZA2ZZqJ/H1DHc1DHm7WG/FY72N2W7iB8TIGPfr8rvayI/G+v5xL8g2h7F/yb8Pfa3quFf1wr8tV30E53Vw4H97auMo4ksOwbjV6R+N4rf160K/NchVWCc6xoJu0r8uqnfHvHLER3d1W+X+NXgm0P9zZG8XrTqEgnbIWF3mekalpiuqRKng+gsVL+jYqNRnnn4/9PySvwuer4vSvwqsUuR+v1B4i+1buTITO9kieu30xSe83y9+O2X+udPYT0P+RZW64jOPVM/yjxhTpnz3Cj3uWbOc6bSn4N2tuaIsd82/gU/aP3I8qW/3bfsaOdlDXNDu9zmiKU/x8p5Tln6c7uc5465z8lynkvlPtfMee6e+xw957lj7nMDnecAus81c55Tlv5cMOe5eOnPTXtF3vfrdR0u0vljubi12ojGy4qXsXlil8L+cAo8F06Fw+E0+DZ4NZwEL4eXqf/16j8TzoA3wCvgzfBKOF/DX4HN0WsbrNH0mPt4DdL3/WWangs0PUNgGbwYjoSj4Xg4Bk6AwzR9wzVdI+B0DZ8BR8JZKl+l8ssh4TqfSvt8vS61Jsyn6qzz6bqofCH8HSyCr8EeMIhcMcyH/WEX2BMOgiVwJCyFk2AfOF3jWW/ye4lJI71n9G7irfBeYt+lnsy7icy7ibP+buLNfC8xmncLC3GbM+8Y2v35cfPfoOf/WvnkRx75z/iZ/3eFXIP0+fNK3YOhMAI0UQfCa6/dJM85teEvm3T9uIS1LhzXW1M5j/3cfGte+9/f6P1x4toVdhqXaNW7WIUuwm0jbq2RRl0TLmHNFHlAs59HaVOu3zahy36W8om8LNHh+NylcR3XIgjbr1HCB9k2uCMFGxSZe7TbaY89J/jC/pom0zZHdPzgap3zcBXus6SpVW0j1aZi0dKahaRP1znENitd1stTOY+zHXWM4ecSZ5Tz+Ewb24QX0YitOXFCwjva36EfkeMhVh5+MZlFK1aR4KjMdyVON/uZ+Dty7HXWod///kP8Ctpd5yFa98J26ap2kfEBh7Iw7d7kb9tuZobXU7k5zu40nNTsPvTm0283dtoT1mMbn6XfamjdaMFtD7ftuDQuramvku9yE9Np2/+YxM+y29FMOe7llA90O66LY+uqkHC/Pc60RI7vsapJ+Ur8HepUok7dKzv2ffoyCb+L0Sof42eBxLpnfy8+W+J9yAry/524DTinMad8eJ/E7UuqSuy10WrFbw2pvMyaz//LLG+7axo5lFG7a/Uc0nLroIrCh48Tt3SuWW7I1c1rWFGXWv0qnZveun9mes0=
*/