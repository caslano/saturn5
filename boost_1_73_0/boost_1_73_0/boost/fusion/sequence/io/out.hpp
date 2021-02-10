/*=============================================================================
    Copyright (c) 1999-2003 Jaakko Jarvi
    Copyright (c) 1999-2003 Jeremiah Willcock
    Copyright (c) 2001-2011 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying 
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
==============================================================================*/
#if !defined(BOOST_OUT_05042005_0120)
#define BOOST_OUT_05042005_0120

#include <boost/fusion/support/config.hpp>
#include <ostream>
#include <boost/fusion/sequence/io/detail/out.hpp>
#include <boost/fusion/support/is_sequence.hpp>
#include <boost/utility/enable_if.hpp>
#include <boost/mpl/or.hpp>

namespace boost { namespace fusion
{
    template <typename Sequence>
    inline std::ostream&
    out(std::ostream& os, Sequence& seq)
    {
        detail::print_sequence(os, seq);
        return os;
    }
    
    namespace operators
    {
        template <typename Sequence>
        inline typename
            boost::enable_if<
               fusion::traits::is_sequence<Sequence>
              , std::ostream&
            >::type
        operator<<(std::ostream& os, Sequence const& seq)
        {
            return fusion::out(os, seq);
        }
    }
    using operators::operator<<;
}}

#endif

/* out.hpp
Lc3VEl9c00zHqVau93Y0ng5O3LfXbr93fv6213/X3TRkeb/lL9lNUYOjkHsbqof7pWZ2DlFBWfWAPl+jTa2U8WpbTbhyq9cXDQebbNQP22rXBqtEvSIzr/F90VouPLzyozsW3CdWqb6ZY7q2NIl5M3HH22ykekmau8T7QTy6V+/hVECZ9m6YILeyIAg6uuwUZqpI1VekYg8/GMJICEggqwxSIII1RF7IyfavEJ7J1ZJeaQCXvUx3qyWPqH+NrUGezfG6j2oi00tJyRoe3TASQCkVuMN3PzyTDnI0zTb9akhddFiIiNSH81y9PTdXEdRVJWXQ9u4O9de9Tyd43tGXl/ByEUdcqeXdJJBClU8XAoAtNuJQC/AO6umhibDfpgJ2fNpnh//x/Y/gqATcgu8sIn2dArsPgIrxkthd6KkTMgPT4P0AspO8BwtomEVXy7SRud9WqsXcw8tbC424JVoYW6sZRkBMe9O3/c+Q68ZuA6UNTydNNvHiGax8OGUS0Dm4yQGgkOAFD2x5SnLKIhWrG2weooSjToeBPWssfwe1u5woFgT4H0x+9Iq4MF7oqGq/0PA/VjLL33qAZR4oIE3j7o6nEh1kQtqDleNxiz1gzVs3kR9gBpTU8RawJA2UFXLBIMAWsc/2UMM9ZYBC
*/