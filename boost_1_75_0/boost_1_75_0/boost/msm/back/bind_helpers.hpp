// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_BIND_HELPERS_H
#define BOOST_MSM_BACK_BIND_HELPERS_H

#include <functional>

namespace boost { namespace msm { namespace back
{
    // helper to replace std::plus as the lack of implicit conversion makes it not usable in one of our bind
    template<class _Ty,class _Tz>
    struct plus2
    {
        typedef _Ty first_argument_type;
        typedef _Tz second_argument_type;
        typedef _Ty result_type;

        // functor for operator+
        _Ty operator()( _Ty _Left, _Tz _Right) const
        {
            // apply operator+ to operands
            return (_Left + _Right);
        }
    };
    // helper to dereference a pointer to a function pointer
    template <class T>
    struct deref 
    {
        typedef T& result_type;
        T& operator()(T*  f) const
        {
            return *f;
        }
    };
} } }//boost::msm::back
#endif //BOOST_MSM_BACK_BIND_HELPERS_H

/* bind_helpers.hpp
7clfSwOV6DORXkur5xD/3Mp3azCPf34fx+YcjdTJD6T1PnXN1oJ5qjVssdrvKt/Rlf5W+ZDhngCGSxc3MJYL6+3Ncnid2crIdP1lpntvZShMV96SmE6p50pAXXgPoWlHQLX6IPDeifdeDi5HYlfWLUeie/qVI1lecmTHilBA+qtFIDlyEwHVjxAmvB/QD759bnCYTCv8wVQiwZQMMJm6yzAVB5GNtctDgSk+IEz9F5H8J9Cs7/mVjbSapDv/kgxWPgrGDNFpEX9m4FkYX4KMgoQLKBE1kuVGVJqHBgr0t+dy7sBVqDSPQDcUbUcFz8AHycUaARFIKt0KMnFpO6eGV70CkXlIQyKTRFmGuN4sfu9s0IXWqEmaKyPHlbCRUusq4hCNZ882JDfIA7h8CH1+rVQa40zZXPIY43wY46+b66V9Xb5M7noHx/caGu3oRYH54eUXg9OOrrRu2umY4pd2BC/a+XZZKLRzJC4Q7VxLQHV7Fw/J7wbkhzUvBIfpjmX+YCqWYBIApmF3hWQrHPsqFJhiAsLU/W0E5gkC7dF3gvHDHyVXzg93f+WPH4rV/CBcAT/ckOjBD/n/CD88/2Uo/PDJtUH4Yd8CHN8IGu2/Fwa2C4rmqO2CcxlSxXIwwpbgfPETMgm8grh+WurHYcIH1s4HFqcJYHFBksEMKm1+Xweks/HKaPl5yoOX8HNPL5XGxNcKUGq2z48NZAV8
*/