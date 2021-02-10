/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_BEGIN_IMPL_09272006_0719)
#define BOOST_FUSION_BEGIN_IMPL_09272006_0719

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/adapted/boost_tuple/boost_tuple_iterator.hpp>

namespace boost { namespace fusion 
{
    struct boost_tuple_tag;

    namespace extension
    {
        template<typename T>
        struct begin_impl;

        template <>
        struct begin_impl<boost_tuple_tag>
        {
            template <typename Sequence>
            struct apply 
            {
                typedef boost_tuple_iterator<Sequence> type;
    
                BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& v)
                {
                    return type(v);
                }
            };
        };
    }
}}

#endif

/* begin_impl.hpp
YjTfSP5DlW65yTmM59E0CJM0mcbePDlPk0U4gQOw94/hc8s1tw9tsCu20s2HI/fgyN3DDf0vpUTep5Iq3Wb8IqMkBo3PYeZ9mVgvRl7uYmMV4B6QFk/MFcuI9kRGqFLk0vjHi1kQxn5s/cR4VrU5hROdsCNg+cEysTOB+0/r2NJPYKdEalTIkJdqQCqWpIEddV/T7d9MvtNJPI78MPGDmRUShJ9ALRhXmhioBeBtVe1qejBOdJd1v/lVry2CldOm01L/oFfiilqaSt3JBmI9P7oLcVvXotGRe1tklR1Hoe1aluuHgLcW+u3i+tyXIgYUIroWKB5d/a1o8qfoFkgonRmlkNOC8W6mRGfj93vvDzshNeKG4cSBdataUj0NwApYCVWCNDZmxhBLIpAaDpo1VCECRurQV+qYobRupepGiu47hrSWhf+0LfN4EmnObB1sL4vQlPOCVejF8WUQnXZWVs84hEgjT2pUS19rLrBELlRXJnbwmtLagD80rhEoeyCF7jDWpfSmHo99UB0TwdJw61j8ZwUI6jXcokgNjPvugdsz58ybTxNrVRF+bXbCKEiCcTCNLa+qDBY4BajBV4lMVB3DJ396X8LpxHJ5YXWUNfr6/X+EZpypLSQoK7b05jb8bcFzvuuNR57j4oA9
*/