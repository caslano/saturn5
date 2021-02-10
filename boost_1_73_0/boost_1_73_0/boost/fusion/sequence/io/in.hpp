/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_IN_05042005_0120)
#define BOOST_IN_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <istream>
#include <boost/fusion/sequence/io/detail/in.hpp>
#include <boost/fusion/support/is_sequence.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::istream&
    in(std::istream& is, Sequence& seq)
    {
        detail::read_sequence(is, seq);
        return is;
    }

    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::istream&
            >::type
        operator>>(std::istream& is, Sequence& seq)
        {
            return fusion::in(is, seq);
        }
    }
    using operators::operator>>;
}}

#endif

/* in.hpp
0/djfW73gfP0cz69FMgPEtnYpnUUYwEDJ+ZkQrUuDC0wZJEdcOldXg6GJ+h9DQt2TYSDYtjvlo7nUkgjlT3V4IBM+JqamS6+wZSmLALa17CzKw9Kz56SzyXBPWz4QLUCh2UuqOqkez8+mw7cwXg8GttsCrJah5iLizYJE3o/AkWkY0DNbSLWCdWVWCxQJoTYrasArJcgzfImlROeXdGjCVBUFJUFCXr3sAwQh6q/En6jCh/lGxAYgKXYnRetuKlSsJZCTeotLXy3W4uWRNPiBDAwVLN2V1tIYk8i34LPCuPfcKWoMQcBlS3bP2x9BS8Y26X0MWvkycmxmrYlZCQQax0INWDEG890Ha2Xoev/BHFhtzRCzcHSEM6hvGciptgYALkRTlAZs+xICF41TAqp5oDi5NjTvljeY2nKvdtuzTx8lhNUTCDlFRA1+ulgpBoc07WEvBJg21sHylLA2aBD8YFtbn2N5WDByEri6+NdPskJd7utdVy0enEdB/kQHhomV6uRL/o3FU//qpjIXu4SuSkJNGgo1zqPUuwOvoOyZl9saVfb1My6hanGM/UQdH6gGxVeivtFu0UFIFDSb9qGyKqplM8DR897ps2Zm37joJ9AVi5uKhtDSmv6lZ/sL613dqSrPk6zgW4JnTxo
*/