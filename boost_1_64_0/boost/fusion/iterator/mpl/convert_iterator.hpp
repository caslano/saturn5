/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_CONVERT_ITERATOR_05062005_1218)
#define FUSION_CONVERT_ITERATOR_05062005_1218

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/support/is_iterator.hpp>
#include <boost/mpl/if.hpp>
#include <boost/mpl/bool.hpp>

namespace boost { namespace fusion
{
    template <typename Iterator>
    struct mpl_iterator; // forward declaration

    //  Test T. If it is a fusion iterator, return a reference to it.
    //  else, assume it is an mpl iterator.

    template <typename T>
    struct convert_iterator
    {
        typedef typename
            mpl::if_<
                is_fusion_iterator<T>
              , T
              , mpl_iterator<T>
            >::type
        type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static T const&
        call(T const& x, mpl::true_)
        {
            return x;
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static mpl_iterator<T>
        call(T const& /*x*/, mpl::false_)
        {
            return mpl_iterator<T>();
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static typename
            mpl::if_<
                is_fusion_iterator<T>
              , T const&
              , mpl_iterator<T>
            >::type
        call(T const& x)
        {
            return call(x, is_fusion_iterator<T>());
        }
    };
}}

#endif

/* convert_iterator.hpp
UFtjzq38ygB5r4ZFVG4+WsKChdeNQncWHoo0kuQJ1lU+aaK817a95YE1AthgZ9772u8rP2bBkvlGPwNF4x6uowBz5pAEownkseFAKzOrXlw+Tn11c2MTCwhFdx6OOx8RB+bCEcfqiF4jD05YDkaCtcEmTetBeTit2AyNHr2O5cLJel2Tv1UuuNpHRPHXBc+pU92wZcHWSEs19Z1TGKnc5GAXHmqnY7Z3kgnD3CPL5P3av/ncOOHqVY5IdGz2HpKL01y9PKD9rN+bCw8FwxHtK+IuOBoTXtlYq7ai9+L/pYNXXVsbQBOhwYGJi90wkkjt2+7t7MBaW9pzduQZqG9cbeQvsXyc1rZ6N07ajdNaaB7vH3Nw9Dw6H3veobWWyFlDLkY0CDfpXP4fEu4E6qbqBvit8+lLNDzYGrD1jpJZ8ymt4BQ2LeQ6QvujtJ6b5Kxd7yvDgUjYztMGO/SlFA5k6bo3NKircR0ecSsxiv/RbKGYUP2zfLxVYbvoa2irDle3RAJaN3hHbJGJG6IuROgi4MyVcc+F5uWuqufKuOda5UymZPOUhOMoa9oaFPeF0PHIM99Zr64hXE0uH2zBMCPVTZWBcDgYFg6PYnPUXCSi2iemXdfx6Iav9ZWZMMoM08e7YKQAdWQR9LxV3VoIzvSAwipfOb4ADsuYPUfvixonZCdjjTrfjSrdrW/XXmHq1CcDFKymujUwfaqGpTYVaRjKHjDy3bgYqGC1jaFlwHTduEXf19TYEsjeq/Nyq6e+t7lOBJT9PKHva6GY41AOPdC1gPWUAW9rahKmjgxRc6JBTY3tWRT3Kl/0864OvC5P+PwoXp9i4LUuC7Y11Uk70rz2vKzoQBbZQwJnbykNw61rnx96xbxOZg31usZyYJiU4+ey1q/7h68YOFrDa9UcrxaAcwYSNmKG5cKpgwH6jMdnwnCyWbCGZ35twglLtHhDwJWOue63M10dR+LvmzBCVbsKr9b6eb4Jt2OI9qlxc96sJCr5pOuL1/LhuJHWYIvWx5CJg1DbInXBVS2G7lxgwO2t1awh5mqZxsz7W/V93nnO9WUwTIU1XRO+IeHK7EWDsjsDhrzwaxoWj0kY1tMaCbSY91VNVrBgcHlbyISFPnBgzeyjXdG073bD2EhOkMKWlA0UwIWnkYDh1zIFcJhG13Qf5sJxzrAoaJzvevNx+G3V+V4+nDpfw0P5cMis03m8C67jlZknJ9w4KKdYperij1yw1h/jWVUebj7PYjk4uTxL5sHzeZbJwcnlmfWxG57LM38OPJdn0Ty45pnyFW+aOEH8KdYitB+vyoXbHtLo4UYVHHbT81J+4MJifb1y9vzFhu/339/ZgC2YUzbX6C/NGGbA/MfPXnyorgm+MdZS+aWm1T+4qwEn6JAuN4Y1PD7VhOu8S9nxfAOezS20vz3VgBFPXM+WLHfBGolWOh9udsFCrmcqVpmwZrp6RFdjP4nzTLhKITXv39L8oDQKDlbxU93Xrg/KPkpc171mnZPQc7U11wTC7Zpk5qS5cFuT8Gem/VUNVfNLPdO5vzXMDfMCUz5qhpxbtg1tt20XGIK5nT153lY4wZCxZnqBuo7LjsA+Hacz+p5IOGueEdVPfEfB2lqX6etWWl3H1PT19A7nus0Yo/5TOtkqNVLfk2LPDgxt1Lo0TV1XWqh0eIGG2WHbVkIur1Tx61QFRwt1zE41G9fRQC41q72u0TC0TNER+6W67uRgzUqn9T04jlpu0zDrfAVztLJZ6dF7ih9mbrNSybog3M5ttE9KiIEaR2Wkeq8ZPYeT+4RVL2WngrlyH6WjJjxbtWl+aJiT92jbccGwN2BqTxqWm7doX69xXHmLOof9jQk=
*/