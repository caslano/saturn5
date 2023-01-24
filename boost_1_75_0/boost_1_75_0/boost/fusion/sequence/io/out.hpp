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
5AnmvOMO19I3Z7+t7D4PvJiYctxtjqKwtpnjOlt4T+ryTLRlGIu29X8aThhYHk/PdicIzAjQtu5T0cwBxs1WJkjDZiuTq76zdWSEzewYmH7LnIpae4Uy+bEeccjTs2pHHIq6GkbKIrv9cGlf2MlXUElnditaJklSNuYc/kZtjcVrkmYoRMivpfPXwqLYO0u+0YxT6tmfYRc4f9OwJsOkljsrmFbyJPcUctsl97B+yvyr0RmmSbGW3peeYafTupNbuuTZ0ZbcvqzPkNsmuatQPLsk98q3aX1GcpemZyIk9+MgmrsxHt5W1m26h5KhlPFD/qsZD2/rNPNM3sy9Shg2gS9vGBaOdIDAMSpIycigICWDnfvS+qPkbtFXYb4huTMl97ZZaiYxG9zFmbQbM+ntnkk+IQyUSinpVKFrQok8IRMd4iOHYUJWKaHndBKCQDZc/zBKwjnaMFOrc38KhpwzI0Cdt3Kduqy0tE8faflAQA+17nfpodI2B3pqBn/q8dc6fVJufIZSvaN7jnnLY8rXqzOVxZ+Ovd3NJMzU7olcQ3HH1JduJwpdUwkwtZo3zjgJ1lIbva10oUUzKINMBpGbdbkpMxSZMm6GSh7NUGxAfWcoxrXuMxTbTdsZimxqPMPdmq+ZQkvNMRyhmIQ6Ot21k5sc31u4T4K3XWYdGTVdWYEcNF0xfvWartMq/E11mz1/mGsSr7+VK8+sr76Z
*/