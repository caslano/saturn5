//
//  Copyright (c) 2000-2002
//  Joerg Walter, Mathias Koch
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
//  The authors gratefully acknowledge the support of
//  GeNeSys mbH & Co. KG in producing this work.
//

#ifndef _BOOST_UBLAS_DUFF_
#define _BOOST_UBLAS_DUFF_

#define DD_SWITCH(n, d, r, expr) \
    { \
        unsigned r = ((n) + (d) - 1) / (d); \
        switch ((n) % (d))  { \
        case 0: do { expr;
#define DD_CASE_I(i, expr) \
        case (i): expr;
#define DD_WHILE(r) \
            } while (-- (r) > 0); \
        } \
    }

#define DD_1T(n, d, r, expr) \
    DD_WHILE(r)
#define DD_2T(n, d, r, expr) \
    DD_CASE_I(1, expr) \
    DD_1T(n, d, r, expr)
#define DD_3T(n, d, r, expr) \
    DD_CASE_I(2, expr) \
    DD_2T(n, d, r, expr)
#define DD_4T(n, d, r, expr) \
    DD_CASE_I(3, expr) \
    DD_3T(n, d, r, expr)
#define DD_5T(n, d, r, expr) \
    DD_CASE_I(4, expr) \
    DD_4T(n, d, r, expr)
#define DD_6T(n, d, r, expr) \
    DD_CASE_I(5, expr) \
    DD_5T(n, d, r, expr)
#define DD_7T(n, d, r, expr) \
    DD_CASE_I(6, expr) \
    DD_6T(n, d, r, expr)
#define DD_8T(n, d, r, expr) \
    DD_CASE_I(7, expr) \
    DD_7T(n, d, r, expr)

#define DD(n, d, r, expr) \
    DD_SWITCH(n, d, r, expr) \
    DD_##d##T(n, d, r, expr)

#endif

/* duff.hpp
Sm54sYuOS2itsg3DlOFelNB/UjwGAXsO8HAsZp6aJDwdIllbHIB4oGPRqlbOJlBuQPYsmbpFMLf41t5rH1Hl/LoyKsXkmZsPqr7dynSogUm59LaORNiW2o5n4y2bFCRNZMG3+63W8Uwmw16TAwZpZ82WhVM0iUSkFsIatklMQy1gQ2mWuMn4AAN4MywX3b/Am6kuKuNe1Otyiwx/xpURNaouV7JeFICfTmO1IGEellvYsXoOsWybXJi/dWxyajZm3YzGVczGQTR0A8JCJjTpPHnf6pyaLWJKLFirkmaRzoe1wO5p0VWZUX+OZuQFEadzZ58MUurOBzKhLr/LDeTBeyHpj+NaEHoqqkV/vIC6YRprTwMMqrgIpwJXbRVdQ4Wv03UI3gyQBacKZami8ipXHHlF7ezMfJyzFp5ipaLUwyAAxuhNhiMHvxmb7fS6uNDZlnmBOJvGAjwFY5RQqq3QHuiJR200246FhYSL4Fm/XXeanbYxXz+UxvWyTvPCwu3dgMPWBs5Lyz7t9CwDqps4P9pNHK1qWC8WwOY4OfgA0et2bIQjR3bFvOxWnHr3GIuPJhhxfLqr7e9WyxvsK1229Xsf05hRFQkppGc5/W4xPflS+eOzFR68U6WrqBDk0ddlHumV/Hmp2zIHmDV8
*/