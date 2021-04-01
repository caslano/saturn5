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
3UMxDO7BOla5HOduqjFanPovQAJ3w473t8rtWU7679b+KstGdfIIeSvmZMuHJKJoZ3Jqp9MRYtFMWYCf0QMUlfJR3Mbs/LXldbYicwRl4NiLvmwwK5AvYkglS6Wu21zswK5166VSFGqGDqdH8EOwDoE2osusmdQ8JFfSWBQCwc9L1VseyLWrD0cABnDa7Ghaa/e2po7Mal2b3FhRmG+bdGvxE7cTyjIpWzhIzHyWr18+pxEvLBIiBU81W4QzhBATbuZkgirmzJ0cMISWnG8hxWjEesKPaRAWf3I9cCLaqiwMidJVYRgrBtW/WcpUi9aBawakz43P/wQCVLyKT+73iv5rw//a/aY8in/TfbS0sStFA+Dv2DLUU6A6Rd3ynv0x9Lyv4t0aupnqTDmS/b7+pVjaQWjs8He73vCZMQ7RCS1ApiFBUaMhdHKeO32+Ivk0jPxceEXmj1DOlRjzUo67xhC3rs0qwHRxKq5xmItyyi8BbSuugThK+b7qY0LmUA15QfzujJm44NbdIu1KU8OgKi6skT3bAkC+R8EQY8k5NsfxCFIfIWZeKXksCw==
*/