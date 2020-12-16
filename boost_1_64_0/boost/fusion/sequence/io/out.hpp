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
m3dhaH6NjyGGdEek3+cWhK5qjGV8ltI7YwruvSXBkJiCL6U0K2bg7ltJOukGtG2f14WhbYv3SDbObttz3TiotZY1trsLg5sDHSumE0e/wZ7b1JiNdQSIHZvu32+s6ZsgeW0FVjB8/rzbNs831+CpsT+++I8hWBdPrM6e2liDI9OB/QcnkXa5RZu67hDSrlDawf2Th/V+nNKu23//g0ib+CehTe5/gJa5j9IOHZjUdWGUdvjAAw7iefq4oslozZDE+cADjBjr6zZ9asign7XpB827iquvJPrtqHSryuFM1MHSIf+JYIs48oVNARPvYmGHXmVifc7dzI04E21iYccJtvI9Pw1jl4m2tbATBOtFVVZlrsfEN7Kwuwm2KMMkzHnOxLe2sHsoNo29zI8LJvoMYkv1Ldv3FFGSpk5yzfFD5P4Nvv+NbvqDm3X2U6R19FOkdfRTpHX0U6TZ/RRldvVTpHX3U0Eb2E+R3tlPkT64n4p966cOAv8zxb61zodWr7G3NfZNf6nXRm9ueX7WMfcxTx4mNNfcJz1jhNDml5fg9qMx8ELM5VGCgTnptDICwzI+O0YwW2b5+Q5C2zbLj3cqWpMdbtaZhfCds+WQWX4b4yJG34FcT2JktIO6hcQCUke8N/RK4wp3yrADPEX2D+8QGL1/EOsWxkH6i5iXm/d4rLmmvZHStkXb3Ay+2fvhm109L8ZJNnXgYLNv/uftYY8cO/DvJkHorVQbws+fh4Fy3eFJs/22h/Xz2XAJzlGa9juTJi5OGz68t0LasfUF2IJiWVcVTdTK4HnjqH7eLuv8mKapsvCsucOgzYigoSJqpeY9Y9BVXTCG7U5B6y/OCdqJ+oYL6HONpSTQVf7CF9T5C2eXN9Y2oVZN+/79zjBvvLxu34NTh5r2vdW96vaFf9vt+6dhQTnYbl98brevptntizS7fZEGtaLti8/bZT1jTNPa7ftzg9bVvss7NL3dvv5OoIn2BZrVvvLcN3uPus3qBrutcT/1RyHzgKqpbsszw0gTNcV6/hifm7XU9VwcQbqspd4bPXAUaKKeB+xa3syo0x9q/uZ8unhPqHcQ+LNZ8LDZaS8O/GN5IO+Trw/79VrQgYOHZ0/Se7ffD9dcaydPCGJvVaxJsr0R87sG05s/gQAi47cNff7fyfiNxJyYR0Ddb1eETcszRL+dnlb332LS7PfAgunx8M7m3Ao/v27kLPSkDNTrDyMN5eOaMIK0fq+e1OW5Hdru6LQzWwQzceVDXlyRm715Rt7v6rBAHX/AdQegXHDD68k7P7RVHyEYuWL1REGA1PuEw8+gOU+qqOJZFgTXuk/Y6M/BPoG26690ucLsi8Rt2zus6OtwhSxi5sD/aqxxx2Zh6nVDorDuMCjbd1RO5vD4mnPzqLrf3aj7L626wWHy9MHrzLY9Pww4u36IvKOcE/ds3B7mRBEICkqSbuxm/S8/nbZ9HqV54uTXrEtS9b+VUf9fiHrJmN+ozx9Rz7EOOsfAqKD1VkWe01nhT3rA0MmPCdrg+p9r1b9IiryIwmu+v1f1v5dR/59j/WV0f28mmJGJ7k2/ASgYsPqdbLSu53FSz4yJiL9+5l5zDl1sZ5gb7g5KsriWJy5Te8o3Avd5P7P6j7CrOjDLYSq5L/aff4ubXTl18oDcY6GNG+DxXTXU0B+NUUxLHLbFRKstOAyYtKi8/74t9Df7qShXRkzFNW+YPAdNtz7z7nmqqIPoU+tiOlrpbS7CezRj5nU/uiWMmd7p9YYm5kaY4utI58tiRSqVjKeZ71GwPHbczOX/9djHmFdPa8UZSPIwqLKIARA/0wrmOD6CduavM+61p1wvCdIijVk9kuSh7JTCLps=
*/