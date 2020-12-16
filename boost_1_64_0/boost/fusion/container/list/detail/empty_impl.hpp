/*=============================================================================
    Copyright (c) 2007 Tobias Schwinger

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEQUENCE_EMPTY_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/type_traits/is_convertible.hpp>
#include <boost/fusion/container/list/nil.hpp>

namespace boost { namespace fusion
{
    struct cons_tag;

    struct nil_;

    template <typename Car, typename Cdr>
    struct cons;

    namespace extension
    {
        template <typename Tag>
        struct empty_impl;

        template <>
        struct empty_impl<cons_tag>
        {
            template <typename Sequence>
            struct apply
                : boost::is_convertible<Sequence, nil_>
            {};
        };
    }
}}

#endif

/* empty_impl.hpp
Rqef+zgmz1TcN/IudXvXlEt+h8iaxgBkmVLH39TOL5vQ6v1M62yMamNa29S8JxveKxFKZUi6XZB+yD1KeZunH5+aVP/3inNPFDDTQdtzv0908Jd7fQByLx8Cv62tQzbPtpwdyR7bKZmNvd+d+41zjpZzYqVOvTW98ZM61T8b+bLnvhvSVtZ43oeudjNdm+F9YNwXrcRkfF7atTXXp9BMnya+Iw6lS6XokiTPbrw8uyVmuuRkHeZnlxTEzzVWTYXK83jMd9rzaHweZP9+mjzbU5Ei5V78zpgHtYWamJQU2IDf2VdV/dXGrSHNrZLmMWJ3sw28nzTLzdLknN+G/K5tdjvXt4PoIef6GvQoln3+KxHFYxmyCj1ifjDRYwo73EUP7xZ16+Hbovb5vJQXa5517U1DGeVodb5B/awOh6ttvMpjCdfOMXeSr+olaZjswdTnzUf22UdKvYYinxK3749meaMB1YB63WysV+15qJA0R8p7LQRZ44/eJmmqjRb1jXbouhUbCvLusqsdmtQkh38Hl/+UtMSp2TbR01srWyU14zstrr2055G28uyuU/pEHvR0mD9pmF0OXRlpeq71V/202PRlV22i03qut+0316lxz4Wqj/ZcPCj6EJNBlwLZsx8l9TgWKeHaQI+68GJroi4Piy7EpP0uPSJ+0qUy1GFwh9o6lnJ9oScdk5LVDndj67C76PmYQyeJTTUGo+m7wfCdW/2a6LuJ6/d51jcrdWZy8+iqxORQVdN1o/47t9/8pSeYl23MAQ+6Jmc0Z9kSm6tsuxvLVr6bws+asXz9OtZ+fp4kTIm5zo7YG6lvR6O+SkzGdkFHiUDKbzTyDNdWedBF2neN0sWt7BwxudX1U/rv3Op63onmuob+5EFXTNgkpk9NbkjfR69vL6O+EptTY53Oxu8N5RvQyU1nuT+LPOmcnTq1sfq6lS8xuXTtqLs35TtD2e420bOca20/16Enzb2mPkfPuvQhNuM76jnDdzbje79zbX1f4voET/rO5O0x5aom6Srl6ojJ7b59Qf8dn/V9qOgu5vdAed26xmdxlgX/Nkrnk011lhg1m2NyT5hd4/bstepa+z37CuF8D9aZB+qtcfdHL+P9ocUmqmvv2gq3721u7eYi0TtR9plOUNIhTL6Z3nSiG9Ln0fehjX0etXknbV9DvgxlGuRdu3/4qvLM/WKiW3bzte2WqH5aZIbnqtxEp9eVejbVqXnadneofkpERl2SusmZCnLPDUG2Ke97U12aqW2n+qkRac92ifhJ085Qh52619bxTeX+MtWx+dp2haqfROb2LrpH/517/Zro+5Y//qb6Nk/bTnTVN+00XR/Ufec+nmPvYV62tl/NdG2+tp1DXyLzWLZa085Qtr/3qP3svKPcr6b6Nk+7zqGrGpFBl2IfGTuUsjsV2YEuCaa6NE+7zqGLIyL3el6q+869nuN6mutaZKpr09t1Rn2NzTqjvlpCxnp211fuyypTfZvWputi0NXVpOvouh/F31im63vV1vE9dPT9zUzH5mvPrVT9JDK3Z2e1/ju391LcSbX1fV+5X031bZ72nKNMHRG5368rdN/Z3NpzPr7m9V9kqmvztudEZ7PmHPHKPWFyjfszV+lb+926S7mHTfPQfO05x/2hRVarL7XW+L3BBmJab5dNXR9pT3+o3NO/ozPBws6Jn5SdnJg1OSVeTbQhbbnV/vJ+0rXldjnOvEvMTsbPYEcUs4BuNvb2im7jZQwzGnmVf/IduikNBwa4hw1x6uR9CFt2viZj5UDWIBOVW/qlJ4u9MRLzgb/Cj8nTPkf6qRlK60i1Tl7/uX73eao43RyRzPMb28DGefPkHPELNo6vq2M=
*/