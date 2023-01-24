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
w5bI6ufKep2BNtCU3nPwkWH3ZQ1w5HC3Glu4QRLDjZNg1fvPMMW4dvyySlpEUTFLAcLBSyQw4oSMYZLAyAxJnk+3IPn8OEiSG/TYy38x0REnrB1GooO6BkmP+Vlw6wuQj6eLAuRx7UKVpqzmoBM4SBC6OHMwVMXBT3mMgwTBt/gcvCBxkFBbI8JitG1n/lbjrv7bA7cFH6M2nWxMUYa80ovc1rNRN57qPjkn5YryMiLGlMJS2zgXrOenThFkwZR0qVA2+sy8pAivOHIzqVFtjnoMtjqyawqaMTQ2QjuGRmroGEeIho5zdNLQCQ5bX4WefYgl37CvTuGGmdKUqt8vpubK6oydzjWIef89g5hVeYwO1RHyNlOybJD7ZDSz61GDdJIIM9VS7t41Md1RTXzDVBPftsf0Jr4RZie+b7hP+inVE5xgEK3VKFoorWEL5Lbm8P2pUKM7etUQnNvhu4PUTZP1klkaL2ZgeFXjxQb5CI0X02r699GpL3NjT/e/DJsEU72nzHcrk4xa3S95xawXaml+BtEmGUWbTHYZyyRW9v4W6Pl+vXNVtM1RTUMHOjw0tN1xv5eaDnNc19ARjgsaOspxtPffMo36WXNcUHkx6bjguOBuXm6k7S+981+1c6Ppvs0oWqi+R7N0bJ+BprT6i7cNGptqOlXnHCszplt1PuLgbrH8pMv9HI1dvfrYc1Ve0izQsf6wQzails8S
*/