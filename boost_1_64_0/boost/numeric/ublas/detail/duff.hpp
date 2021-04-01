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
jxAPFpRCW0P0LpL90k9woyO+d+ad9mvnnS83X+gQ23HI9okZxA1QuqPnucvaFI/+ywSnDl9oni6EWQxR16SeYiABaD0IywCDnT3AFQD0+/tSAuSIeYsoQCkzWlokKF3pFVfWgRwN9TDr/cxKxG7uuiRZxSAdOixCd//xfBZof4/MQSZ2/Yq1/fR31La8NLk5CaSoc0ROpsDC6//ORIrRcJEylnkpeTh2vN1OfpfKXkJebNE9irQAJlHX/GEQH5ysxXDTXfaQ/p/1RWRsZUJ0cxpDXofFzf8V5gZB45ykNGLBQyh1mPswmZLeHe2RGkqp4MhjnKUYWbGzffXvnUoIo/ZtOApHPZbJREKaUTu8Ox/rQtkblCJxTGnt4QxPpEGLWmx80xfaIPr+UFxSR0EEKmoWRyQYErGsRXTGJr72uujKpHqjVm+kTLlaXMUiEQAAUszzMjNsiJ1zRIEjM71NGRnxZ//YZxn+tDbejivur1SOAkiRQs1k4PqS4a95nMJjTitHugRg6uZnMIdxqe8H0i83HF+vBqQwHnRP9XV5Uu6zwyPlwM5Tq0ie5A==
*/