// Copyright 2008 Christophe Henry
// henry UNDERSCORE christophe AT hotmail DOT com
// This is an extended version of the state machine available in the boost::mpl library
// Distributed under the same license as the original.
// Copyright for the original version:
// Copyright 2005 David Abrahams and Aleksey Gurtovoy. Distributed
// under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP
#define BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

#include <boost/mpl/bool.hpp>

namespace boost { namespace msm { namespace back
{
struct favor_runtime_speed 
{
    typedef int compile_policy;
    typedef ::boost::mpl::true_ add_forwarding_rows;
};

}}}// boost::msm::back
#endif // BOOST_MSM_BACK_DEFAULT_COMPILE_POLICY_HPP

/* default_compile_policy.hpp
qHNm2vP9WXzeW+c29zAlhwOiwW/xxRbkNPZtw9TLxGjsexPK34axHRJn6FvKe/qdtrz9ufIOJArZ+JsFYIitP8rTX4O8RZ5eViRm8vRHrOkhcXnK7N8flGSeDPDNPvd5BeKtnhTYPXTEox6p7s+KEZ5+MkYXLcZp3t/e2z27N39vtzQ3U7dzyxutP1EHskAhjpfFOFdy1Yae2b84x8E+RTw0Ku9Snoe/YkHNCEOaz4t5JGTK
*/