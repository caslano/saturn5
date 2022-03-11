/* Copyright 2006-2014 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/flyweight for library home page.
 */

#ifndef BOOST_FLYWEIGHT_DETAIL_PP_PERFECT_FWD_HPP
#define BOOST_FLYWEIGHT_DETAIL_PP_PERFECT_FWD_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>

#if !defined(BOOST_NO_CXX11_RVALUE_REFERENCES)

#define BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body) \
name()body((FORWARD)(0))

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=1
#define BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body) \
template<typename T0> name(T0&& t0)body((FORWARD)(1))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=2
#define BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body) \
template<typename T0,typename T1> name(T0&& t0,T1&& t1)body((FORWARD)(2))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=3
#define BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body) \
template<typename T0,typename T1,typename T2> name(T0&& t0,T1&& t1,T2&& t2)body((FORWARD)(3))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=4
#define BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body) \
template<typename T0,typename T1,typename T2,typename T3> name(T0&& t0,T1&& t1,T2&& t2,T3&& t3)body((FORWARD)(4))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=5
#define BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body) \
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0&& t0,T1&& t1,T2&& t2,T3&& t3,T4&& t4)body((FORWARD)(5))
#endif

#else

/* no rvalue refs -> [const] Tn& overloads */

#define BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body) \
name()body((ENUM)(0))

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=1
#define BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body) \
template<typename T0> name(T0& t0)body((ENUM)(1))\
template<typename T0> name(const T0& t0)body((ENUM)(1))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=2
#define BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body) \
template<typename T0,typename T1> name(T0& t0,T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(T0& t0,const T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(const T0& t0,T1& t1)body((ENUM)(2))\
template<typename T0,typename T1> name(const T0& t0,const T1& t1)body((ENUM)(2))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=3
#define BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body) \
template<typename T0,typename T1,typename T2> name(T0& t0,T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,const T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(T0& t0,const T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,T1& t1,const T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,const T1& t1,T2& t2)body((ENUM)(3))\
template<typename T0,typename T1,typename T2> name(const T0& t0,const T1& t1,const T2& t2)body((ENUM)(3))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=4
#define BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body) \
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(T0& t0,const T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,T2& t2,const T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,const T2& t2,T3& t3)body((ENUM)(4))\
template<typename T0,typename T1,typename T2,typename T3> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3)body((ENUM)(4))
#endif

#if BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS>=5
#define BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body) \
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(T0& t0,const T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,T3& t3,const T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3,T4& t4)body((ENUM)(5))\
template<typename T0,typename T1,typename T2,typename T3,typename T4> name(const T0& t0,const T1& t1,const T2& t2,const T3& t3,const T4& t4)body((ENUM)(5))
#endif

#endif

#if   BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==0
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==1
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==2
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==3
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)
#elif BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==4
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body)
#else /* BOOST_FLYWEIGHT_LIMIT_PERFECT_FWD_ARGS==5 */
#define BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body) \
BOOST_FLYWEIGHT_PERFECT_FWD_1(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_2(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_3(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_4(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_5(name,body)
#endif

#define BOOST_FLYWEIGHT_PERFECT_FWD(name,body)           \
BOOST_FLYWEIGHT_PERFECT_FWD_0(name,body)                 \
BOOST_FLYWEIGHT_PERFECT_FWD_WITH_ARGS(name,body)

#endif

/* pp_perfect_fwd.hpp
xtegHugmGGMPc9f/hcFzQBeM7XMQrv9VEGGYQKy/939hYBlfm/dtHW8v0APCCeME//wEMiZP+J/5VwPZzoM6hPWEdzNvhhGE43W6IEXoEnjxqPEq8SUKK7hFZBLW8WyE2YIdgX9Axn+dQTHBrsNDeOH9l2WCYoGHnBihMeBYMAkITPjrshDtcCZsY7pzZvASRDaz/+tuVBOsMa3XKa4yv0UPeQ1GG/uAq2rCTgE98G2QFlST3EbbV99dkDofxHX8wCt5ww8OQEiYB8wGfAENQVvjXENn4qCjga/w1gEMJIzoGydkFbAKWAxo8CRMDSr6VRpgC8qGZ6Mcf1y3BcgvCZzdyr4WsA18G/G6/zV4BmDwAsDLE+8B/0UIPqgr5KqhQViQDsQGiYAdKBZUFoQry+odIYpgib8MGMB6cIDLc+Ge6eI5CUP6HgTQ/VEDaAIb/sf3QLW/PhBXVQ3Ug6pCrlwI4wJRQfjBn6HqtAFhYwOxBtUAc+gRjyGoB74GogR9j920A/GsG/9V5/PrUjBemFDcPy4QF+QN9FCZkhveCfnQebe2zxfuGacOkJQhV86E/P6foJ8wqzt9ocGDvDD/k5ropPikSP9ngu45XAfJgmxA2nBJKK/awbXArf631P8iqog5yeV/ImoTpYjdxjzwEQTrFw+iCeIY4u7/LpUJ+BUQW4QehIX5NjQSfGPuu8B1yn1yYNx4h2yrOYDMMGG71TU48df9b7tATajGAKeiAD6wJlgDtgntGJfFD+gqcl1mnx3QGvQGdz8fjCvG6omgHqgHlglCUnJgF/g9uAPWmN7qNsQ93RjQbhAgw2MDAFkCWGP8P0L9AG+UHoZL7vjGuW/cMQ/KRuI+DKQ6cPG+ZtyWyoAhEIpAUmFNuHhUSmkwS1DTs75qw044Ce34WEDEAQ4gsTx6rpAX2FloAlxfXXe91+m91uBZyDiklHC0q6GlffC/VNAi/HdtY6EiJv4SDaHhvssKf22PIoCWZY3iyYZiRSRUh7QjXjPZxFH2WrS9U1/BTg+LmPNwyH1gOuQXXvLCyL8g34+L9AV3MoJ7I5zllSgt/JRAT7doCx3tJR3z9OWkgL9clWTnxBPPA/kWkf0exqxC6CXl7EPoOfEXoPWVeCrRekxe79Re77e6q29VG1M771zq1Nvv2P96AqiqwbuwpH2zT6TstP2R1MyZPweTkiftd0cF0luvTnNLdp8xRTGvxr/vYL/jxZLaMYL4DkdStXMcDioAAiz903/PdtwdJRBRWd9SUr1mSl0pse1+K7MF5uQ0YD3eJ9nmtZZc/vrSmnDO45f2APrj7vMZU7z8pA/mI/zFLlhb9sN2avu0A9Jd+w3B4oWf0Y3PYu9jsd1gQe5sse0QLZ743Tj6ehOZUi35Q6lVsS7T48Q6c6iufiBD3jScfrmKbu4ko82bGLXx/TLTaWtLP31YnN7FkviTat4QeuI5V82zDdOC8aIH/+5+k5w3+6wH8u5t7xdyBB9wQxWOZEgM9wehzTwN9gXWejdnz6fNPLwOPIrOYWduCZuKZ5lyHu4a772f4oN0P9cNU+ada6FQUl5qiH81HiPMz7c/NdyPwRD/jHhBWpI/Lbx5uKhV6cPvZjtUbfTqosK4OrXlQVK+Ira5NeGbKf1Z0hZdadxniVpdPsHaaKrdet/VeIH2vz+lSHqkXECx/v7w8m1B82XrYLViP2spatQ2vgpeXr2fWX5d+5Dgl/KEOGMvf2Ze6G36ns0J+5nOIbCK+voMbSrEO88oyvyXK3K2Ah/n5MPNMyGy0ChJT9adY5VL4ZO35ffMM3UT/eWd9NhYtEPyJWpe5eLSX7h4EShuKdsBcbZXBFPminQ22mnwsdX0Bb/kK7bBnxh7FtlsWdT5ZzjBumMBv8zEd0Xa2d0SnnoSd/liWfdM//2Pwvt7jwZTDf2zFdcZd9nQipsHZNUqVNnJ/HNCT9sJmk/nTxwfDoVV/xdwD/NwgL0kOlGd7gZ0yD1XHh6x0i5O1LmWoYISQpOwSIQDZfvUQOuWjt0eDF0B2DeXRmRI7+El+BXi0q0uEfFSZGjCex6eA4ESnNQCjfeNIsgcPBLMj6YCOgwZXDXHqhXoOjIUMb7VwR6/t700cFJpkGu4yOsssmQeiQgKNdREppa7l6ouqbAt02eYvXs5/NG0ILcI3Cu9UFOdlZCk9By8ovJi4NWymq23OYIFhAMepaXxUkgCtQC3CI6i/O6GIV3QfaUA91DyvhNl+7qTsKT2HLxjsgTS63Xau8ICfpOwDq1SflHQ0i8prkDX8BaHGzQiLk24/CJmizALCux+V/VKxiQ3INsIeGK8iY2gEbc5loB1uzy8gkIL6OZsAfHwazVmytlfV4jZos6UN8DYO2r/gAGvQ9fwmgKyJC+AXE+NmvIGbp2oI2L5VYzqAppyHPQKccvQG6mg1oUs6RHkChGLAdt7Z3pJIQGg9S6wQyLiV4mXBPvryv9j9LmOd+781xEnYD76R0Y52AYuQUk6C4hNfVf015EsOgU+0CYwt0zdfB6YP1mYZh55rpQWYacIXw27fE04SQitHTDeg3JulLMBPRpGhKeQjtVLIFa1ILYRggUUi8eBI623j4H3SHl4RnWncM3CAFtxqvgUfEkswjChv5qHGDydU1bOYY5IBLmDMd4xicQ0NRUSINaJxIQI7mz5vvJNWACKIS+jRtHJIGTGgD3Bf6SUO9RuV+CDbxLeBOWNRGQf1AWYhQDoIkx/6yMgnG9CbCEdHXLAPYQZcBOWYaILcgSWR/uXPlT4jWPO0SjSpbrvBUIX5uhg2EXBlxlgb5QL76Ic2BUiyhBkWTYkl5xMqx0i0iM4XVgaqV3wlTYtfdIO+DoRtAGLoxH45uyBV7iY4Pjhz8r2Rpj432SP1VI5dVV1NwrGoHBYsejwcEjMBMSBcBrJDuZgKEkZIXBN0Pt5IsMMUtcMWELioPBwGuL/PrEk3A2NlzSxHFGAknsS0LIfPrYPoGb+p5kmasort6JGzq10cNSl++bpW/jkvDPnnbe0Qi6b6ynL+bxQeNt5uLSJLSlZIdL0UOWLT5H7vTQf1eeQRd1b7EJAH67YPYunQp9eK/AbNMmIs71xSIs28F6zLCL5UCISTeFrQBHj/SSPXO0vDBUfmPPwSTN+10U+uVqUfIEf9nEkvYXiI5wCirUI/bu5Qc1rAbrwDiRrfUqW1B3oFJpfyRPUE4yUz+nFWDZqbkj7vvS60+O0QiR9fKrOnakt2QR6WQR9AgwV24DOHZot2rtaWQQ/CYaSTWD7fuW6Vb5vsiXre+pYCGqmYc1rRgu4D/fiUOp4CKo2YKKOFrWyHXutqIZkHYt9agZ1b2HtsB4UqXpZb/ivSgCrrE2/SM9bLb5Dxxf3zZpG3VNsK7ADV/wqfl/jC2FF8t6ajzo61kn2bJWp0ANS/ErhVO1LZsU84QZoHq8ly1loyfNGkLpDcbKK8FlXS+IPU8oidGvf/1hnewT4jp9MP4MDynlY32Ij5H26/IqydCwVlT+ofZ++Ge90VoDKl64n9oUFsP7iK9TzlXLXgh8hb5AvWEBD9ZWQH7rUnfSdbL5vpxX7O0Ieqvlwq0LOv+e8T0SpO+o720sCS695BEEqusibvM+YZ9KJB4XInYibgk8NL+gjhqR9tDveS4wmn1M/mOJXjLuTVb9S3hhfUClHSW+CD1Fb/vcdYapv1U+wCcUrrCQ//4xX9rvU01oh6a4iPIEf8bIIPwy/EF+s40i/hZxhL1ipu4xX664fIFpHHe7wFwqFSOp9iNMfKFpHIS/4r1KFyJVhhHq/EjwhfqjiV/o7kkvl9YdTgC900PwKteQ9NJpzALZFEVQuK/fkaclTDmfu26teUMWVLaNI3UHcuVU8JdFXAGhH3c9uK/YjxSU7Iapv9U+Q9g4gS8Yj6Yqn4Iw2SdrE/R9C2hKekv8GICjXzGgDAwgdlzyFqLYL2CyFLPgVr0p48tcVyqDKv1BrwS2FjySXQoWoeNZnb8/jU1RylGipiujzv3Sa8++brOTzyYHX6VXigBdyJpgreEMeCZr096dDmyruq6xUiXzAr9TPZyCKbJPpK1vQrPaBrlbcnYloq3hKtTQohxGv2N134C0NjzyW1oVku4Q/aLfz47HJ6MvWwVjv5K5y58MErVK7yqwwkvYZ37hVaw+pK2IF9+s+MQAkmepoHqr0UW/FOpm+ajMMcuJRbzmga+U6WMT4/Y5qTEJtOfZ/JL8KbYK6SkxgRvjEj8gPaRH6+Irqf9z4j9BNyCKlh+oSZVkE39vO7wRhqyRv4SW6soijez+Vx9D2fYx77HdLiaSU3lE+kh2RH7Iko+JPkOfaQ5fHxvhw2h+Mo5V78IlJhUjW+5+62fHM094AEeM38aSHe/QJ+3xU6yNtSowy5Pb9XKK/mlarvYkJenuiZRGzkgjvXBYR6kWxL/p5qBfFAS8PDOqflSx3eoEZr4GP+1u/aO8qmm6/cUgTpAm26QF5erMQ98JEmjP5a1sWoBk2JeQHhzxryvZulkb9rXycpx8wZP7GdrliSvfuJyhrk4qQ54d2HPmTInyrF6LkLduDdwMPUBSHF/UDsTIq9YbYrhWW1kkcvP3GtzJK9aZ4ZwfkdhBu7Its+fviThLC/hac8/DPBNLpSj7585jb3hd60xBcetjLTx7584RboR+O1n4JbsS3OOXwy5FX3U7C22lrHurHkVd9iHnSOSsgFYR6EDYOsKo9jxQizQ8/FGFnMVHxpO5SlZ4aunPqKcmT9v0/CVuOsMKug5Q+kz8ROT3QjyP9zXn0+JP2a49AH4MY1E28yAvMBWV5KPijXyDit7tKf/FCWO3HZwV/C49p9CuHvwBRDseZID1v8A6fCuehzk6Orwrzkp3e+Ct9xmQFMk0pR97LScxuMqN9CM4Knw4S8TrPiitsH6WHMgEvML94o3LPMuN9bcXntJ/IK4h5muV1QQCak/IPvSYUt2HO0r1+1+2cQBXEBT5O8RI9lseXXZSLEMCdJXrhi/1Akp57mhXEBTyO86qeEoQM6c3SPNbH87WfID3yBzwS8CydchMCprNJsne3UnAV8jzO0brUzeF6tP+PjDP0m1SO68EBzMZicHPHUuD3HzkluHZhKfQGX2R+7YH60ZnTfir/P8rG/EfpYd+8gIU8lJ4uxW8HmvNt+/w3Fcopa3xOkDnQ+z8AZ07kiVd0sqsZ3EPw37CFK8Ke8Dnoj+aEPk7y1J4kAJGlMP8vgPEDp7LxfEGleDf6wlTHXuiFuI9/8j5/WRkFlKJ8ocR/B5lDvSPkk6N74AvrQ57xuxOf8gdmWNzRiNqHPhLz6J76gbDOH5+J2YeI+MojvMflk6/z5oogCBP3UkR+tyqg4OXoPQ7Hj91E7PECs9YPNcJ2oyD/8Pq4/+Aj5/LGGf8EmXO+K1KKTjUCHxHwUivqBQ5ZzZbWxXmo5f+gFK1cvbE8y/NUzscJ77ecMK9S8FjP+UGfuXjl9H2nm9O+S0rUbjxoPqLFp91ohr2cxOu1njif5gaK+M56dpUSddvNnszzw0V85sCdmhMCOIw5fpCIn5wYdz+wiNsc+oKuy7Xge2uJ4JdPrGd7nsz5WUHirhPp1RNe7Tk/mIilHPrK15u1SF+gBZwXb9Fhv1m2JXSBgtaTyt/fXi2VrwjFrwUn1r+PvVzLXhEiDnNqKyXgAXNl/74XJm4/wQEcG0Y95qmRP/+FU+apNiHjTqP2sJ9E7uYD7WM1wCNrhcT8RfLXby0AFQBXqQX0347idekHAexPrEDzV+qS/amJfMspVfkMe2R/vClPu1krNeJL2gf6mlVteuGpLuAtgijw0xd1n/VFu8pHtV/5EQLQzL8HhN+J3vUryq4584h5FocYvmrndoAirnLMVbPCMjBrfljfuYmQ9PjLCngXhyC/IE4RhPa7vrMi3xRQPN4R5nfAIt7eidAe8lFvlv2CG2T88MnAizHLf+AmDt4Nk/goh70eCQqr5vQFNOGLMat/aCdKH0koqQHaKz/wXsnfxP+9aIwfe0e/o31RfViT9kHe+Q1q5/WF/ICt9oPe+QviQqIJnozdV4RkvSV+KB4d4+8KfXF98BaHQL8oTg+IDsS/QLdnhWW9NX6o3kXGKJX4I9xAFodIv8xPweIVi3yhfUgWRf5+Oz8K/SeL6YFCvnrSz/OW5A9qwPqPrLBAwBI9N59vFSjo/qZGuyIqlPgyBTjcovZHS9Trvz5hPXAAxZ2y/1E8mW8Vlk266FVlJFiAPsVQof7FirT4oznsIUGdp69CC7woUvzN/YhYRDunr3gFnFSg9oOxhH6aqtL5K2L8vbeiRcAPcMcoRMad/ZRogX41WCER3mn+uAFUastdgaTm837CrGAeqSt0/YesvvhVqfN6a7RAyyLIv3rnTgTWgb8qrGDyyI/Pf2K+KYvQ5nYUaIGT9g/ef3azISzBHq0rRP0z0mp/8G9yhQC6soDwM+r8hliCPl1Rpf5VrJH3Uxv58w4HaAbsn9/v+wv2/5ot/v2UEff6Sov6SsCu7Cgx6mMkpCEUW5QGSWatFJMeC++3Xwu+aeuKewDMy8dRQsmO56jNPBUH3Jl/6N+N4yFrtU/phWRplnzcSQBO+5iPE3r/9Pxlz066fqHp/oO0MLvSOM8PFfHmCb9trBBZ9s32qCfxueIMyFGqb2G/X0el74hJKPGMJd+uSblnwopygIeGsh/EM5UP5vss0YHsV/Zq71xYYW5oNPsThKJveZwAJwiW/fnNAF/lSf4PtNU+3NfW6Q9cxPO7xCPgRPoW90PYtgYYclL4A261L/vV7e6HAAhQyq6TfPKaixvhHxDS+4vCu29mE9yKXoIPt3fMxyiFSJx3CAU+s2jR8qBosScEoxWcgzmcPNSBV0SpQkZ8U3gTAUOZPt/FtPBt0OL4kTBFPjvUvKmQaN4YydWHaKFH/pAMhmjiP3jHkfKYw+4nwrLuMeOn5FNoMDHIj2AKKHzG0B1gzqKNipE9kExqrCUFH4Y1Fqz4QvYB0UoxcXnm/TpIbCX5rYJi5SPi8855ZOsxZ+4YwgXddxSUeCOwSXISTewTgIykrR+iFPeDRb6KgX50E5IWiSZ8VwKIhAD5KP0HK/l0K97Cnif6m84iAt+Y/J0in1wMW/X0JrS9YCUthB2a9a89T+A3voS2gUrhaB65GFbj/A6MJVI09iMgRcOitS6PxPDeoSVk2PhCGxbKxN9Qk4wC5/2/LAuRfNBI+XCc69RxZE9zA5S8V91RTWMYMY6gJKrY+GIbltPC/vvFIXQgP08hqAVkzPffL47IGPk8DMF1YGOgd4DbpaJDThOJqv3rIb9gFFCKxZjfUSWoDZry/JCQN2LUkmTFcCZyBanwmQZW9ZnW59mF97vqMb2i5gO+TSmHYQtRPqhHkAEJiWnHE3qvShLYALdgz55S4D19KrQGH3Eixv4MXwjxdaGAQnSQeCooEcxe4O4mRPU7Rq8LATASkvAOGKuiKc0gNwrAcXxdO4EZ7kPuuD7opOs4k/O9cGezONRzlUR/dzQivvEk/LZfUT3hSO9xKm/5oIo5jLyxj7xGrJJK81ApomfzPtvrwU0JkvZHj1FW5XGs53sRijnsfNFNe+vhj+jzyH3NfOG/SEmPcS7mf5Ct9k+OT+blBQu664G+agFCQ1+gLxaAEOeOD6aYw9gX6YYeMOtq8AuEAkov0w/sjSbAJzYjH7hJ+6YP0u5+cJYw0bTufqDFrzFvpo/O8S19q5EvHmUROxn6/V74C8SYGyoXv4rbDHzRjtRHXJNSiRiXP7GfOY0h3muJHBc+OyLT55B7GV33eREiUo7ZVZqC2/cD62Fu7P8TlkSmxyu2uLF3QAFkrQBZdEO31xxtWQTOcavq1P9wd+B55HYZO4qOyEzLz3wR7DBSjpOfdNv8QiPr26VzznnkwS9e7jtMvWHf/m4EnnSkkZ4/uF7hL5aPrcJia9tfqzf+nEIxvE5D2LJh1qwoNcqFbvV6D4NwWuibZUcCrL/HkDKbiRyiSr79xtVsMTdLyn90G3RxgNwsPBxK2ZCvF+737GxRNwtjQr2aGW8lbWm8pXAgXiwP9v6ti7TpU/vPWoTc+rv+4qvkhUGwgthzXne+jXeF5KvlRUCwDtuDWYe5DXcF7SnrhoyzEt+TXpe+TXOFxV+JHURZh3JX4oaStyzdtbxi4SnMDjBvbrw1lf2iT3Fe53TX40agt8DYFb0i9hb1AtNboOtXb1bfM71i8pb1gtObr+lbaV7ZU7367S3sBaL3r6afvZl9z+WKqyt/y5+9OfM2xVX6a44yjCqsJiq4YzGfStalVEVrjv6LQdqs/IDQ2aBmKkT4EJFDBT5k8JCBQwc+jOQQMo3iYVeCE/lY+snPTGxc0aFJxU1/dIzRoQoXZnTc0aELF4FiIqJOQO6fs0h+FnzUEawG8aRhOexAmAlZFrn5wJkTehZRpWF7VYCgJgS1KW8WFc4ezRpo5ZGOBslJPxcnwfIkWJ0iXaBsA9hMsq1Djk3YgymEDmFqnygTsLYJhk0ib52umGFYdD9ZA4LYodMqmfoAfju02JEVZqJmDu48hTMhEkpNkvDub07UmpTBXWxO3Jpkkl2udIiVyb8OQVNhOEeUbZKxoZlHmG2isSHaRxxtsrFhG0cibcLofdkNiNcJww6tNAFeJlSb1ASB8hOWt1SceNeJzLv/GnCvUwVfo6uCIQ5lXquywBAmrF6zqgLCTPC89ZYHBxuQeggzd5E4MXooT/oLnfi8Jen8Rw+J3XVa+lAa4HKSrm6TLv1Lj5DdxcR2NdfA9FN4b7OiBx6YwOnH+NwV6cJqx5JvE3TA9JMr90zbwXvIVwaonfC8dWvC1I/AX0M3IWvHZW9l27H0UrV34drRtpM2dmnb8aBn4Sl5ufOv18BkZ+0sPJ4Fes1rSyO3n4AURenfNd11+CHlT2f7E9+J3KX88HOWEQaZ32Fuq3xFvnZIv0Td5fihZy/o+2HeGd0V+eH15+X7pN8lXyt8ofWW5QdXHplvI33Re2oqf0b/qPJD7MzNDlq/g72W+CLpregHsD9K35Z8/+4q1g8dcIeTOoBejFnJt9RRdSuKYc/baQNvjGY3jHXEO8Zm30U8IMe12gwchM1XnadIcgjOH+QZDCaBgznG8eWYGAssjMHlGBkLMY4hcshiRI1lD+0=
*/