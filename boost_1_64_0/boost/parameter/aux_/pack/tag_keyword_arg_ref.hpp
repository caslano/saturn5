// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_REF_HPP

#include <boost/parameter/aux_/unwrap_cv_reference.hpp>
#include <boost/parameter/aux_/tagged_argument.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <
        typename Keyword
      , typename ActualArg
#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
      , typename = typename ::boost::parameter::aux
        ::is_cv_reference_wrapper<ActualArg>::type
#endif
    >
    struct tag_ref
    {
        typedef ::boost::parameter::aux::tagged_argument<
            Keyword
          , typename ::boost::parameter::aux
            ::unwrap_cv_reference<ActualArg>::type
        > type;
    };
}}} // namespace boost::parameter::aux_

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))

#include <boost/mpl/bool.hpp>

namespace boost { namespace parameter { namespace aux { 

    template <typename Keyword, typename ActualArg>
    struct tag_ref<Keyword,ActualArg,::boost::mpl::false_>
    {
        typedef ::boost::parameter::aux
        ::tagged_argument<Keyword,ActualArg> type;
    };
}}} // namespace boost::parameter::aux_

#endif  // Borland workarounds needed.

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg_ref
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag_ref<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag_ref<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg_ref.hpp
gyL9OuIlOgSWpFlGz3eSvh7iGdJ3i6lDXOt27Lzpn316p6yBJ/bpP7CvHK80Prxvs2Ftx3+835oA4kZ9h5e1vlx5sXsuQ7yESfZdI6DxVbd/2fPG0sS/gdrJR+yBA34HD+8Tdcpeh7Kne/dJumWM0IOeGHTPdbExHVU+vcvKR2v+wPLpHVs+5hpPlDCH+8pH45szq0allF/Xe3mu/bhw24gruze7Ltc+rey1s0MFc1EWCUVcv1kHM/v2mGdManq2Z++eScqsw5khYXzPciB++dbR+MtA1zi4eUbs7W4dH0PHxu0HqWPj9vLpkCCc0SGRQsQdcQfWFbHsdldXxCLCl8b9tTo2chPKyiaD9rHRXzacnVCiZ+bFlI/GtTVcTPmYcLLuOp7SJ5TVsbEO94YJB5bbJo/cNhMnI+HP6dgoiZJdiY+OjdlVYujYuL0COjYIG1PHBn4xdWzcHlt3BPGM7oh85NC3ir9+iBTce1f5a3VsbE6MoWNjSQV1bCyJLSfSiq1jY0lsORHPyGkucpib6K9jozvuszF+MhyE+4zEv17HxoKqMXRsLDkIHRvEialjY4m7H38LhRlW9dDp2FhULYaOjSUV0LFB2Jg6NvbTDnLxi6ljw3PNi7jeQdX+Oh0b7avH0LGx5E/o2FhilUvPxP50bAxIiqFjY8lB6NggTkwdG0vKqWNjSTl1bJTz2v+sjo25yWXlU98ZJ2PLh7Eytow2xZYRaUaPn/4yig7nLyM3nPRXOHROPjgdG36yK/HKLnqc1GfQyZr6Pv12/5ueQ1Qakl2us6Cbvt9o1/CcQWT2xX8mYb+z19gBzuKI1zN/wmnUNterblFnVfP+xM6eUePcZ9kFSwlDaTxnVZt9iyeJXylvJ4/rHl1OR73DcbvViiPcRFJx0m4q8di+WFwwbqznOXeZxO9jzg++X+LW9eRVYN6hEh0/JNVY7AhG4n5gj+REi0R7Hvr7a6Jj3bu+mc59LMu8s/KKxuXkGzn8INf8peyNbCiN1Nl95Z79+q34f2avsIPWx3aC9zxnU5aRkveiA5bFufYGjXT/9pjsIu866+PkegrZDVslRjrXaDpl6qdgrFM/WgeLJE5VqyPvR9Wd+5zE78DcqeYuzDJMGypzMNd7N3/fk+aEO/Baaues91CZrOyR2QVUXdlzmOp723y0zNmXNDMU3/o5JfJdM0MH6BsCrDuFU2ALZDXsTk9bLxo/LievuNinvZt3x6sl/OCAT/+gabn1YHvqgfYg+7ZukTBDAmF5Xi72pv7j353R90ve2Jws2b4ndZgOSyXML/Y7nCrwFatqDrPj0BjQhDj443PTstBe3yZctVOGEsrwucSpLuc2tgid68hVu23lHvyde+pE3j7Sta18rflkoNH+PDs96p5RHRN3yXuk0QcQkLxrWvER+4rNbj/3XFuJV9/eah0RM7+o+8ec4XyjhOsT2GBXsUq5djvQxOh92Cr5V/WcWZZd6NXpMUj8h3NHNOCU5Ua+8Yabc5fdc/xqeM9L1/TS4Vq5jr9RE0GrP60vcg9/yZgiTWMqaRzH/VMDe2aqOX+X/Z9mD4LhvQhoDe7LYRH8GHOf3ktzy30OYHyth5d59n5ivydkH6HNKeYZvrRj7KYdR539J3KRsFONm7lWuR+3Sf2wr7NRyP7pXSH7Udid+7Oj3p/z9EV3B/dlK/g6bEp9L71b7s+xWTLVRtpOuua+xNGj++M5CdvT3mhN8Bu/NS3k4c6h5IXq7wQ53/BN8V8dONLuYy8IVDXjxp33iC4O02e/JuHuCNxjXWVNCDT3vXdNXp79S5b/mbAa1tznehY1U5J+Z11Gpa1jpOyqMXqOpLyNzN7+X8UeGps=
*/