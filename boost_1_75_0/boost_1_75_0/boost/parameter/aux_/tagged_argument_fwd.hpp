// Copyright Daniel Wallin, David Abrahams 2005.
// Copyright Cromwell D. Enage 2017.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP
#define BOOST_PARAMETER_TAGGED_ARGUMENT_FWD_HPP

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    class tagged_argument;
}}} // namespace boost::parameter::aux

#include <boost/parameter/config.hpp>

#if defined(BOOST_PARAMETER_HAS_PERFECT_FORWARDING)

namespace boost { namespace parameter { namespace aux {

    template <typename Keyword, typename Arg>
    struct tagged_argument_rref;
}}} // namespace boost::parameter::aux

#endif

#if defined(BOOST_PARAMETER_CAN_USE_MP11)

namespace boost { namespace parameter { namespace aux {

    template <typename TaggedArg>
    struct tagged_argument_list_of_1;
}}} // namespace boost::parameter::aux

#endif
#endif  // include guard


/* tagged_argument_fwd.hpp
2tNlZ41mZydYVzyFbT0rlAmYJB308OaxJHZ3Aa9ohR0O7iLgxVkZEycvH6uLrfexjUU3fzAq+n04Z4yAdHXVdHmokJXp4pSIf0ddHqheru+6u6J/fjSmr/xz4xhP+04rqDr9AbdmjvbTGV4qvMgpQVuvDuMZ/j3kNNXw5DMgMqRfqb/w6QpIyb0IatEvDUCYZkqx5w6Vj3BzdPIK90yW1rAgr2KnkmM7/KpxFdKMqFbcitZ8lnKM7JatU8JU/DjxHGI8/JHL9Q3Pek1PlyKVO117zsDc1HlmXe3FqmIl/wChfaicS+iYWaOzaGEu7oHLxlSSEcxmaOooo/ZOO6bfwuMl7h2kwKj1cJArWNXZpVqX9vxiRCXHB2yfUbd6mnA/n4cvwL7H4lpseBiTsoxxqydn/odJbRVPJWuObg7OkpMu9U2AD7U6bPT6PiMJJfMuhd/21xihMJxqQrb5RMd4p6EWXKzlWVzgw7x+dgNONF1paiumUpxy9DSwkBaDzzvzF07YyxFiJuOjWVnXZr2lISr6hOykaLw4Yhp05Th0zzngW8MfdI/Sg9KXiwyAWOIcBHMD6tN/b4jqX/7g5hRvv77vajuVaK2u4DAAjgJhMqfmZRta7SYujkduEcsvUscL+GWYFV1sTFJJBVeaaqmFehdCmL1XTuS6a0A/AzPj21Fj112/2FBeT3ui/oQomPlM9sEalhyuhto3+Kcw
*/