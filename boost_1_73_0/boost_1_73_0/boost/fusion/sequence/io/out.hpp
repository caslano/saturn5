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
mgqXRA4/5BooCuVSYa44F9ZNOqcrrmoJKsdbVraT57kwR+C5nG1akm5LHLvAbkwnc7bjiLysCFzCQrxIOyQJJmkJyeQmN2zkI1myrfKqyXOTsqRFsnjioDo2NylpMsoalF09Z6uuzUWYEUeUVFWyiJNMF//FmbItKKKh00wxGnJIdRXb1gWDi3FDqiArsiZZ3KS70URZp7umo6iqzXtHFs3NaJIsObbhBoYxWhU107BM/wijuUM5i5dlQ9O5yY0=
*/