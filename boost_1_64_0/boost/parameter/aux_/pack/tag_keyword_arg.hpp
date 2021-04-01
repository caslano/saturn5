// Copyright David Abrahams, Daniel Wallin 2003.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP
#define BOOST_PARAMETER_AUX_PACK_TAG_KEYWORD_ARG_HPP

#include <boost/parameter/aux_/tag.hpp>
#include <boost/parameter/config.hpp>

namespace boost { namespace parameter { namespace aux {

    struct tag_keyword_arg
    {
        template <typename K, typename T>
        struct apply
        {
            typedef typename ::boost::parameter::aux::tag<K,T>::type type;
        };

#if defined(BOOST_PARAMETER_CAN_USE_MP11)
        template <typename K, typename T>
        using fn = typename ::boost::parameter::aux::tag<K,T>::type;
#endif
    };
}}} // namespace boost::parameter::aux

#endif  // include guard


/* tag_keyword_arg.hpp
grl2nzlbLl9Fi4ssXPj7nZKd4fSlZQtz0/U9z8dv5EDofVzCwX0ddEeEIxIOCpiBM2Z2h1IBGiJTo5Zs+KuYlEk/DwEpX2H9BnNTdG59YMnaEiBtssFUAcqBttPqvpGFEANerEcVlFRz4FMx6tzzYYOPOHVO1i+GAPLmnvUzIwnJ/NMZeA5XplLiGyHsslmI5g/eR8vKatSag2IhBbvNxaXwLEZvqv4cMWKBzgiwM8gRPLLJZqrYZJ+5THb1T3Cl5Sbzt8lYX+beVVfMcz02gY5lcBnXFBGK2wKfxwEedfdX7Q62yxaUHEGfWvoBKx7gk53teDuUEfsJvUHdCnllUEi5IEz9bwcK3F54MbSgZ0Jufq3LXimaKL0nkuhxtcijgkhB32n1hpejPnNJc4DnIlT74nbZjvuwCCf86WFCQPtsDq+qOib3ONsBV3cqcnrl3ixhUQxLWrMwHPNshGk7DAEINQjxTMotSWQxU5ki/z3dWd1BrNDn+6yupsZeTHjkDdGtwYG1hwAC9XgYGW5ynt/+sB5FcIdgzWks3gSMih3ILVVQVM4fFrORTg==
*/