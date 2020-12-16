/*=============================================================================
    Copyright (c) 2011 Eric Niebler

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED)
#define BOOST_FUSION_SEGMENTED_END_IMPL_HPP_INCLUDED

#include <boost/fusion/support/config.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/type_traits/add_const.hpp>
#include <boost/type_traits/remove_reference.hpp>
#include <boost/fusion/sequence/intrinsic_fwd.hpp>
#include <boost/fusion/container/list/cons_fwd.hpp>
#include <boost/fusion/support/is_segmented.hpp>

namespace boost { namespace fusion
{
    template <typename First, typename Last>
    struct iterator_range;
}}

namespace boost { namespace fusion { namespace detail
{
    //auto segmented_end_impl( seq, stack )
    //{
    //    assert(is_segmented(seq));
    //    auto it = end(segments(seq));
    //    return cons(iterator_range(it, it), stack);
    //}

    template <typename Sequence, typename Stack>
    struct segmented_end_impl
    {
        BOOST_MPL_ASSERT((traits::is_segmented<Sequence>));

        typedef
            typename result_of::end<
                typename remove_reference<
                    typename add_const<
                        typename result_of::segments<Sequence>::type
                    >::type
                >::type
            >::type
        end_type;

        typedef iterator_range<end_type, end_type>  pair_type;
        typedef cons<pair_type, Stack>              type;

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static pair_type make_pair(end_type end)
        {
            return pair_type(end, end);
        }

        BOOST_CONSTEXPR BOOST_FUSION_GPU_ENABLED
        static type call(Sequence & seq, Stack stack)
        {
            return type(
                make_pair(fusion::end(fusion::segments(seq))),
                stack);
        }
    };

}}}

#endif

/* segmented_end_impl.hpp
u6nN17fqepbwuqyMszjMy4TyYtJkhvMG8JG5PknCMs0i9Y4yYm2tHVXv6ap+RHhzlnE/dvMgVmWSeBO91VNLq+hv+zn0E6DvDOVnQZVARWzTTivm+FXCmzC3yCvHyzkbsI1X9Vf8E29rxSwvuJ8mlcPoFmxg/9hP+F0WJJmfBFHJ2luzll9FTPhCmKqcMvb9lHVt2RperPMi4U2YH3ix58M+a4Barv3OZ1v8YVmEUQhz/YBr9vY3v0D4SwbTVRJ4BRusTUcZ+M2/SGT4LHbCMuGFawlZQTuDNZxLWt8sT4vI5X5o8dKpyEE/9re38mtEYpeVspYG3OprewhfCnOBn0QZLMqDVOOtOAiM8EeschK3ykFQp8qc7sceTXhzViRFxPO4YoNV4jjOlIwzREbBktyJXIfH7N+otdV3w2/fkuFx7gRBmrHBqmb72xMZPovCxKs4TJK2+ga/Pfqdm7wezOVx6cdlGLL/pGpmQ59T33H3O2j/504CAygLiAy7/hib7TDhD1mURE4Weznhp4PHwfgpJm/JQierytytmKlpkuWdxPH+DtrvCp5ERezid7PcTGQsORzvLX6/DKqSpw4bZD4p+fGbv6PVbwLofQnPKT+dKK1v/g7a96M4hGqkCZVBJ0uc49/ROlcm4PMbc8LbNWHiHP/O9h6vKIX/G+s2u7T2HvsJf8iqBIYNfALWZY7ZWls54Q1YmDpO5vuZzdufU/OsOgsumrwPKHjk8SjwGTqDSvym6lvbJp6zLEmdIoalkHo2tO6zgYfsU4rM91LuMssVlvJdaJWVhuJ62QPfRWEQ99j5/v1lfELZmOqdPmXyHQ5FDBnXLwUbwfcwHxfgyVoVVnkQQydWGp9lmYMAbxjovHm1xZ/Ejs9zJ2vxy+zeIombPW8+uj9M4xflRVWWecLMUqdOm95/KAP74Lta+hbH9x03jhjcey0vKP2ZiJdBNkkM+yDh91lQBbzwQ5sd+6Be72LC68L+t8wyN+NwmNwUeTqAXyqwG0bUBRK+nCV+VaZeVJ/rhA4P+OSmvfkArXdHOWeInIrlVRrEeeEKOUQEtiaVhLkc5mkbJjzKnQrmIbUHnxLWHULDWQcPx7UjVH32XXTtSAs/SipfszfrXqsm61sb62vkzPb1d7X2AUERR9Cl0JpUzYGgNOjXGfBb/tUmP2d+wGO/DAvWTH2UCeCbGL/p3bQPVEnmwdqXNIyyE2z0YAVY7S208pNeevwwyQtWuH7hVDmw4se3bJv3vbudSyfKSu5WNdOmoXya0qdywYf7jYVWPp+wqGAWS5mcH7AHiUULvzm1j2akDgWLC+EjHnFLRm+hSSJGxOg+uNiSU/EwzvwyV3I2xSv1xc+mVDDKMBJSEM6XRI7DioIXkYh7q9Tq9OudRNuO7WGq7y+4E8D+i5GZZ2phraeU6bUU2ReZziVEyg9ZHORZFMNcpA27Rdj/ddoM+tyx594tP+GySLlfeQy/A7oLWzlFL5OyU5YURQYLqVDFA1oEpZUa+LXVnhpMUsgGxrVt9eE8SaLSSXIm+9MT+nAnukxqj7xDF2ndAy/IssQpmeh+aL4BDaE784bq/7sv0ryOsPLwJC0kK+XCe4NWeannVzl3gAnW6inwRSSDlZbHaHlxlPtlWjoNK2g6ZHJMsk/hF1t3HFka5LzKGHbKzo+Le8t1k79gvuOEYZQCd3PTKj4IjnH1jmdImYG4G8kLnwfo399k6jN3446r/DAIb8oC+BwFvCUjljgrC4atvyofv+nZ88Ok/CiJiySrMiID/Q2o7cMl2sZV5FY8gjX+9BzMArCjIEGnoJ1C1Y9JvQto5yRx3LLAPQH4mjZr4smlUyBEJj2wdfo=
*/