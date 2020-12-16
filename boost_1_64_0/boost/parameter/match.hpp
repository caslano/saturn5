// Copyright David Abrahams 2005.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_MATCH_DWA2005714_HPP
#define BOOST_PARAMETER_MATCH_DWA2005714_HPP

#include <boost/parameter/config.hpp>

#if BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x564))
#include <boost/parameter/aux_/void.hpp>
#include <boost/preprocessor/arithmetic/sub.hpp>
#include <boost/preprocessor/facilities/intercept.hpp>
#include <boost/preprocessor/repetition/enum_trailing_params.hpp>
#include <boost/preprocessor/seq/size.hpp>

#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    BOOST_PP_ENUM_TRAILING_PARAMS(                                           \
        BOOST_PP_SUB(                                                        \
            BOOST_PARAMETER_MAX_ARITY                                        \
          , BOOST_PP_SEQ_SIZE(ArgTypes)                                      \
        )                                                                    \
      , ::boost::parameter::void_ BOOST_PP_INTERCEPT                         \
    )
/**/
#else
#define BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)
#endif 

#include <boost/parameter/aux_/preprocessor/seq_enum.hpp>

//
// Generates, e.g.
//
//    typename dfs_params::match<A1,A2>::type name = dfs_params()
//
// with workarounds for Borland compatibility.
//
#define BOOST_PARAMETER_MATCH(ParameterSpec, ArgTypes, name)                 \
    typename ParameterSpec::match<                                           \
        BOOST_PARAMETER_SEQ_ENUM(ArgTypes)                                   \
        BOOST_PARAMETER_MATCH_DEFAULTS(ArgTypes)                             \
    >::type name = ParameterSpec()
/**/

#endif  // include guard


/* match.hpp
XRmgZ72zTVLPDWQTnfK7E8KoWX2js0dZ3usse8u/es5g3MTl5DUuJ6VCXprjVZaTuUSznMpJd7i56nKCsJyXk9LdzstJ6e7//3LSYY9UTiRbvOB50X4JPKHbGtALvYvddOrzJIr3+NxLh3CqV1bkc2oX7JFsivy9Z7la5tVKmdMzR40qzJnEmwFV8q/xI//qWsh/WJZf/v6z3DJOZfkr1fJzPQ08vq+soayybF1XGoRfwrkZBybh91umbLyzXtptaY4DN8WI+WWVfAjDul+X53PVdVCm5/6s6BMIO/Ua0YSIvOxOz0HKeorw5Pt+RHjcz1PsGVDJYCwPlmXoSzThij0EijiZn+MUYVwMOlCp9vyKMCLEt+qxYi9WM/I7qO3SQiX/cWLMkEL+b2gLtGR+hzlGevcS4lpgpgv/eEwvrb3fS3StIVUEyhT0K3hfB0241hUldxBm3Z/FGBDzldTfNvzfktbLFRVnFpcUyd8Q3ieaFlojPtsxxNf8Hp/BSfRoRvDhPFuT5glQ3qTvBJZvB9Cv6NOb/Xyp/CTivVv09bkcSDxxJo+U34ny2W+WfJTneMpXWvq3XL9T3hZ1iId7qOdYh+pk7i7l7ZrXbdPWr15Vtd7YxWVrsL7+XZarOIU+7jpZvws+0e4dJzriVNVl0HrPXZQ4OmdW3QYe1585LrldKPuX/W61NKQvQ0qfao+rk7QiDEvfIWey2m6BtoZ55dXGU/iWtvolg/kazr9Uzr9SS/pogsnHXRf3EO0V6v6RLT8pJGGjVsDf5z4e+Ml7rYv4bJkHap3PJIOXHkpXq+/PqPDSg/P7Myrert79GRWWsnxLDdbY+7k/Q6Qz92X7uH1YEv6845XOau3hB6/I40NEO8mTry7HoPVOZ08H6fR3PiriwzvEZynX618xAhjqghzAIcB/Ip3Jcjot+18jFfNj7Yi+j+t6df+fw3NZx/Dim1kr8h/oSlfeG8T8XE5+Iy1gSoBW8VW1mWlEU6CloD1uAb3B9tP4fDZcR3ZzwDuLzk8KvG/Ypz793F1/6lU+W4ftxGi+J6R8r6xPvhMnXW+f1Wd2HST6TKUuEZZY47wZ+bcGcQ5HHFGuJpF1IltFdok8H8ucmzYyy86D8EsEbQroZsDNwXNw38h2IIqoC3+T7h3eX23SrmbaqLA2kXUjWxK5lVZ35rth1ZgrU53lkLvWIJzA36zz4Z6HT9q73rrDEVN8D7eiPLL+hhNPrnazej0BwrT2LTlEdX0EvaUvyfTyPG0CsIDoBqJdVPeDORxhq8fRHJGz+SBFebTcW8lpsN5baZFVmquAAYDDv8M89v8Q7kZ9/Ya3ztEOqM8BOU50e7UZ6jOGEI6ynyL09SP5v4mZ9WCV3sGvbBeF3fia/Pdrs5RrAQQ/lf+8tfo+WuMbRXCc+EBh+z4Ry7RPrjPXcYXR+2b8fi+HERWcEVkHwYQYwfgM5ysznOBses+yYF8ly9JHLYscZ1/QzsW74NKnIi+IHBQWHhyO+livnqrNp32yzOcBXxnxlYE+OFL0AS10C0y6O4hMs9KZzwUO7KaTviPPn/jsZyRvsO93HImHyvfkcslLzkcF7meAT5SjUf7vIAZtNe7aZ1pTP70ctNO+9DPKHfjOfdNW5m00AszmgLO4H5a8T9aPvK9cPf/SkuhbqXSGsKznhhYVF6p1Blr/98r2g798LvBUPJt7w1sir+M2mutbUmp9r6xSv6K/hzRY99ZuUrfZi710yff9cKPtq4+/bJ/vdhvhiXbbg/TmbXLWbh8DbfdNztptnTZ30/+m3b7WnLfaYhAWcbtdCBeq9yHLvfQH1Uln7YrlKep2pRXx5mtXK9tvDpvb70TqT5o=
*/