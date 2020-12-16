/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044)
#define BOOST_FUSION_CATEGORY_OF_IMPL_27122005_1044

#include <boost/fusion/support/config.hpp>
#include <boost/config/no_tr1/utility.hpp>

namespace boost { namespace fusion { 

    struct boost_array_tag;
    struct random_access_traversal_tag;

    namespace extension
    {
        template<typename T>
        struct category_of_impl;

        template<>
        struct category_of_impl<boost_array_tag>
        {
            template<typename T>
            struct apply
            {
                typedef random_access_traversal_tag type;
            };
        };
    }
}}

#endif

/* category_of_impl.hpp
82X9OHIXOUfuIY/XfG4VnkDW749OJDeyfhZZv585m5xm/WJyjjyJ7JPzZP3+5hzNl/WTyfr9zrPInayfS+4mLxHGdSN8NrmBPEXzJ7uaL3keOUOeT3bJC8geeSG5jTyVrJ83fJ6uH+tbNX/yNHJpzLtfr70TR/h1WccSPfEN8QZ6Iz0tvtPR3SHlPXTndvEkPUVvpusxmhwlu+QaskfeneyT9yC3kx1ykbwnuYu8L7l8+z95vaTqGivPk+/q8164BcznY4VzyqFwq3JG2rcrJ4WLwjiEQ+WynN9dPV+4Rzkr7NxBLgk3KrvCzcqBcFa5IOwpe8Jtyg7zVfalvkN4+0Oeh5X6TtaPJZfJ48iJO4XHk5PkieQm8mhyhjyGnCNPJnvks8ht5CnkAnmC5keeRO6+85+8Ht6p4/syfua8/eX9wLnievhLhbOtWv7mxz70dFHeV/j0Ej21Sdyjh/TkXeIuvUh3fiCepRfo5m7xDD2gl7X8h2xPd+5h//SQnvqReVvr3rSZ+3SvrEPyvjdfj+KPpLxw3/5vq//OzW/tOnB+/vb6/aufD+xamccWvR+Fm5Uzwi1Vrq9wTtkRblUuSPs25axwu7Ir3FE9P1HhUDkpXK62F3YeJ3tyfmOVpT6t7AvnlIvCvnJBuEM5EO4SxiHcU+1Pxmt4ovrzDBlfuSj1aeVQOKdcEvaV09J/Qbks9SGYz9sKdys7wmZr9fks+SinOP8qS31OOS3cqpwRDpSzMp+OKkt9WD1f6ruVXeZTInvMRxiHtE8p+1KfUQ6Yn3JB2FMuCrcph8IF5aT03wnm+wHJT7kkbJ6svr+R/JRL0l9aOSP1LcqhsKtc5voJb3/I813Wk/XnkAvk0eQieRZZ//+OaeQu1o8hl8mLyM4vhc8mN5I9cpo8lZwhzybnyPPIHnkx2SdPJ7eTZ2j+5HGaLzmn+ZLnk/Xvfc4lJ35V/XmA7Ad5PDlFXkJuIS/Q/MkLya3kCZoveSK5gzyJ3E2eSXaeEp5M1t9PnqPry/o8OU2eoszf93M1X9bPJbtPvbXn9ruHHBugm/+KW48Y+OY/316Y3K5c4wzLi79+s3Xv/TreXyDtQrZbskO72A7tSmy3eId28R3aldlu6Q7tarZrh+NpvY+3P2r1fQDbOWy3cYd2dTu0a2S7r+/QLrHDuE1P6/Pp33v4Cw+QedObPznwLd0Xuj999z+k4nJO7370k/Lez5O4mp//0FfKdR8b2S5N130bRm6h6z6NJk+i677kya103Yc2ckFcPvfrLRwdbB/uML9uskluP78Gciq5/fyaydnk9vPLk1vpNZovuZDcfn5Fcpjcfn4lclm89/+rP0DYOeDtzfudPoJNH5T8xHc6HJZnN33wLV13eniDZF7dhw3g/rD8I1Lew3LdnzaWt9Njus/khoEDttufkOUpluv+lFieZnmtJnQY91nKe+9v5plneb1eL2yfou+i1wu55bB/zb45H5B+S58Qb27i9UZvOELco3fTM0eK+8exXvpBB6x/j3gH3e/Hdp8WLx5Ad7h+hzAPrk+Z7QzZHM73t8eTh7DfXXjePuKuthtM/yjHIZdYn/qYuMt+kp8XD1ieOprzSNOP4X5+hu0Ppe/F9WL+zroPyf7SS3Q/c8jbup7f6iHXdO9RXnagPBe+yHURl4NtY3/FpeXSvqzthm3fPrZD++JF0t5hu8Yd2scpPbIrpH0T22V2aF/T2543iLTPsl1efLvX3b9mn+1b2a6N3vv6u/2RuVjat7Ndh/h2r8N/zS7bF9ku3KF9Pc/RI7VS2pfYrmfYv2bfdzh6v885XMbbk9wm3Hukd/lg5TY9keVZ4ayyI9yqnBQugPl+sMI=
*/