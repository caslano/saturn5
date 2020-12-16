/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman
    Copyright (c) 2005-2006 Dan Marsden

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648)
#define BOOST_FUSION_IS_SEQUENCE_IMPL_27122005_1648

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion {

    struct boost_array_tag;

    namespace extension
    {
        template<typename Tag>
        struct is_sequence_impl;

        template<>
        struct is_sequence_impl<boost_array_tag>
        {
            template<typename Sequence>
            struct apply : mpl::true_ {};
        };
    }
}}

#endif

/* is_sequence_impl.hpp
A3ycjz215fARK3Ff2Bj+DNS0BjlfHDGPtWGOa1B+WcQ8CaVs+eW49qAZiF3409B8O5d16BtairgMP/YKXGOIs/BLoFE2f/gfodW2/ZXYd2idnSN836twbSNOwWNX49pG7MEnXINr254Lb7gW1zfiNHzA+ojZaHOAb4U22Nyuw95B6205/PCbseb23A3oo4A1X4t8bouYo74eMXej3IPvvhH3mI3hp30zYu5AHMAfgUp2LvD3fQv3O85NwYdDfWw/8DVQP8QF+Ivfxn2NON0RMTffjnsfsfOdiDn/u1hDxGX4XXfg2kZs7sQ1tQnXs+3nLjyv7gEjdn+EeUAe4iL8Vci1/XTiXobytv97I+Z6yLdt4C334XpA7MEfgrJ2LPgfH8A9ZcsfjJifhpiXzfOhiHnlp7gmEWc2Y91+hmcmYv+RiDnrUVy3tg28bxfWzc4X/r3HcX3aeCuen7/Emtj+4Uf/Cs9hmz/8+1CAuARf+xTmeAn2FN7318gPcQp+OzQEcRkeeQbPScQufGk31sq2h7/3WczXtoefAvW3beAroT6IA/j9UD/EJfiuz2EMxEn4MVAcsQ9/EMraNvCPbcO6IS7C34ByiJ3nI+bjL2DfEXvwe6GSbQ/Pv4i1tWO9iHJog80ZvkcZ15UdC74c6kFcgD8J3W3bwL2XsFa2HH7M77CGNoZHXsYe2XPhN0KmDfOF7/Z7XMO2HD4CugNxFr4E8uxc4Kf9Adc92pfgq/+I54A9F35qD557iD1405/wfEPswjdBjbY9/NOv4rqyMTz2GtohduBPQaMRJ1/HekeiJo84E42axVAasQ/fOxY1oxCn4SuhFOICPJ2IGs+OVR81MSeKvz/Afu0TNUfuFzVttv37ombL+6PGt/18IGpehTrtWPtHzTIoRFw+APEHo6YDcRFeOjBqiraf/lFzc3+wnSP8YwdFTcGe+6GoyULtdlz46IOjpsvOZUDUfBlKXopy+CYosOWHRM0JUAPKs/DIoVHTiDgFPwVK2PbwlVAP2gfwTVC3HRf+CmTQxvlI1AyCHMRp+HiobNccHkIplJfh6cOipsWOBf8JlLXl8E8NjJoc4gz8aqgJcRFeOyhq1tv28P4fj5p1Nv5E1Mw4Imo22jc/R0bN16G7EZfgtZ+NmjsQh0fDh0bNatvmc+jjGOyFLT8W/X8xah6w7eE/Oi5qNticj8f6QGnbP/xCKIM4gN8PNdv28MgJUePa+cKPgPI2Z/it0DbbP/xLmajpcxnmDt97eNS8jPIs/PvQq7Yf+H4nRs1TiD34OmgL4gL85yOipi/OTY2MmnOgfoiL8MNPipo44gx8DnQoYh9+OzQYcQgf3oI1QmxOxljQMMRlePNXomYo4iz8tVOiZohtcyraQw/b/YVHTsc1jHIXPjaL6wZxAf7+M6JmJOI0fA00yZbDa76KPbBzhK9zcQ3bnGdEza9mRs18m+csXGuzkf86jAt/HOq24+Zxvc3F+lyO3OCvLMK8EKcXR83vl+AcxO7ZUXNDK64f2/4C5Am12dzgz18YNUvRJrMsamZdhHVYhzYrouZpqD/ipB81e63EfWFzgB98MWK0z8Kjq7HXtn/4nmtwr9lx4euhOM4two9fi/VH7MFXtqEObZKX4pqHQpszfMRlyB9tXPhmqMuWw7uvxDVp46uQyzVgxEX4k1CH3Qt43bW4TxE78EFQYNcWPhHqtOsJvxkq2n2HPwu123VYHzWHQPNtzvAzoNF2LvDLoRmIC/BfQJNsDvB9r8OeIk7BT4FG2vbwldAQxAH8fmgY4hJ81+txndj5wo+BBtt1gy+GQnu9wW+HuhCH8AtuwN7bOcKfhZYhNu1R8yj0KmLnxqg=
*/