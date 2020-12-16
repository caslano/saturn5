/*=============================================================================
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(FUSION_END_IMPL_07162005_1028)
#define FUSION_END_IMPL_07162005_1028

#include <boost/fusion/support/config.hpp>
#include <boost/fusion/view/transform_view/transform_view_fwd.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename F>
    struct transform_view_iterator;

    template <typename First1, typename First2, typename F>
    struct transform_view_iterator2;

    namespace extension
    {
        template <typename Tag>
        struct end_impl;

        // Unary Version
        template <>
        struct end_impl<transform_view_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last_type last_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator<last_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last(), s.f);
                }
            };
        };

        // Binary Version
        template <>
        struct end_impl<transform_view2_tag>
        {
            template <typename Sequence>
            struct apply
            {
                typedef typename Sequence::last1_type last1_type;
                typedef typename Sequence::last2_type last2_type;
                typedef typename Sequence::transform_type transform_type;
                typedef transform_view_iterator2<last1_type, last2_type, transform_type> type;

                BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
                static type
                call(Sequence& s)
                {
                    return type(s.last1(), s.last2(), s.f);
                }
            };
        };
    }
}}

#endif



/* end_impl.hpp
OzscR3Y8RgeRnR0OOmZ21iM7O46R/Xyecl1d9/f88dwvz/v1Hdfn+v5+93CXhounkgXD5JxrKrbnfcbBZB9azF/emiwZJvveesl9Z84F5iZsxNsEjUzbYmzrj/yyjcwLJvvgMHDXjwLrpwXD6Hz20aK0ZOsLVchSYXSPhGntlnk0JsuAVRL2yuEAXSuallI4Z1+tslbk8u3TZGEw6hFMa3fTfzdZDMxPWLG9f9chS4VZCRsdWzGJLF2xRmeKHi6wCC1T7KWfhqeis/9eIPPfynvJtwF7L64rsCgtGEbj+mPOqs9vnSVLhdHzCkyr4jr3E1k6rJKwWpYlTcnewejzHpg270LTsWR5sCLCBi4bc41MQyfNxZxHf8spRmYNk3NO6DGgEZkOZirscbfHsWROyrgujYuWJtMr46q9nhBG5q7YqJIWHmReipWzONOFrKxibw92bEXmA7MQ9W0v/9WdehsIo++YDYRl7ih7nUxL5Xt5vg0uY+1CpoM5Czvr3foumT+sorDX5bfPoTNhgFHfB+FMjJ/920HaZ6awcIxzDrlymcx/O7+WyrfVR7Icac5AGP39w2DMWebXgaXI4nbQ79QusOFlQxPJcmGjhGX0cl/E43byvSffan2qe5osE0Z/FzkE1nLGOV+y9F20XoFlObfwIfPfjfWE9fn+sDKPg9F6MO1mkegZfM72aFrQz/WGovbkxZ7/kBmEDYNZhvc6VmCVtQwY3ZeGa1W0udePtSPT9iLrn3uJgK3bc6E4WRiMnnNg2oul+5+QxcBshd0zN00nS4B1FnNOPp1qU2AGLQ9GZ2KEFq0tmdGE74P+aZrmZVNQgwE12TT5NIDqyz1VWEMk5vG2KBdTYH01rwxN8y9WMC5KG6A9LFpnHFnChcJxo2DLPeZ78GdyMDpL0XjcEDpjOFkGjF5LwbR1h9KekeXAXIVNfL7mO5l5pqa5CKu0rdxnMh+YTtiPOLeTZIEwR2E9/BzXkIXCLIUtHbSxMVm4Ygccm68li1HW69vmx26yBJiVsBr7nCqSJSk2bn21WLJUmI2wSx65eZwnTOZ5x3XtNc4TZi3GdW05uhlZljJurC6pHFm2ksukNe/cyPKUvbxxdWvCfbio9MF/313uA8xZ2MKhTSeRBcGsZWarvvzgPsBkngf7zptIZlCs59TFIWTxsBIys1P6DLJkWElhdVsfjOXMlDnf1ihZh3OB2cvaa17Xcy4wS2GfAm77ci6XjMdp/Tz+JPOCyfWG/HGe1wuAuQlrsXrncs4FJvMMifQYTBajzGlZZgyfiQSYgzD7jW24hmSYnTwvTu4XydJhrnIvyx+O51xgTsJ+O9RkMudySTmDK8Obcy6XjTP7uGPMajInmDyfK6p5/sWZwczFuGtuRY6S+cNshVXd8SGILFBZb8jdBp5kwTAbYas+BdQiC1PWO7HD4wKZQRnnMy2Ez1kcTOZ5cuF7W7JEmOzR8dC80WSpyrjbD2vU5fMJk314tHAD9y8HJrPeOztqNfdBmVO/p8N1Mt0VTfMQ1nballdkATB5XtLnbrTizGByzuE2vo3IwmG2srdHngSSxSh2aOKgFnzdwmSewQE7vnFmMJlZpEcHziUVZiWs0y3/vWTpMJlLhMeMcLJMmIuwxNjoW2S5Sn0Vdv53E5n5VeMzr6tcvBSZF0zmeX5/cjJZEIyeG0drWL9qwFbOBeb708bgsVJZL14vVYyLwWNczoFKZNkw+t7vWA1z+ie4k8Vd4znzreavDXeTpcHo9fw4PD46dyeOa4fR37+Px+OyUxbnuL7rhT8fEIs/Pw+dMYXXy+J95lvD3hurcA1Z/Lon307tOmsg093AmRDjuq+pU5rXgzU=
*/