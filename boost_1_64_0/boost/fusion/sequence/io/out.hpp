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
2o3wR8jQKDNSxfGE8QHWZheUnEXf7v371l9TzAB1RT8kQ2OWKIEbfm7TUspjor65mC5fzGutLWpha6bIrAe/0Tagd69R29DVfmKxNhYTQJBt++KpPbsTtMUL3lG+sSi7LxOCDBwv5ue8lmmih/Y/+I6ir9+YbMYuBJUHhxB18Q9XFNWwiMBF2p9tuQ9q1uocLVthh02tV9TIOlLT+Oj4Oo+RnGlj1sz8R/oJfgoPQnNifseFj7EQGjHIU0a0wkCE9KTwVyEn+1Yv7GzGbnLay2HeybcSYRUHEv0p2NAMvsIuDgjmSmNl3XVKhpg8K8Phk4EHR2pVbTk/TMJNjzHiXQl/FpTIx6vYSHNolHLG1bfrFq2H7v8Jc6gb6ENx6b9FHCTBqKz0c//XIOIc7iua8bmUKm6j6uVlIXlSa3B2kH5dTpTHCMoegqHSjvIok5GstpEQQWDDarOMsJuAsnlSkSCXkdJ6N35uHV4ZAZBpF0jNZ8cuSzelRG+gwd7ovhoreqwyymQaOI1II44UcR0WTdPNKyZgeph4MON44ghmi7ldRP6bU+KL0exSkw==
*/