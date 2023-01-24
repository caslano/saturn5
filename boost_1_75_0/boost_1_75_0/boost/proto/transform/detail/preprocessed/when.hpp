    ///////////////////////////////////////////////////////////////////////////////
    /// \file when.hpp
    /// Definition of when transform.
    //
    //  Copyright 2008 Eric Niebler. Distributed under the Boost
    //  Software License, Version 1.0. (See accompanying file
    //  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R >
    struct when<Grammar, R()>
      : detail::when_impl<Grammar, R, R()>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0>
    struct when<Grammar, R(A0)>
      : detail::when_impl<Grammar, R, R(A0)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0>
    struct when<Grammar, R(A0...)>
      : detail::when_impl<Grammar, R, R(A0...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1>
    struct when<Grammar, R(A0 , A1)>
      : detail::when_impl<Grammar, R, R(A0 , A1)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1>
    struct when<Grammar, R(A0 , A1...)>
      : detail::when_impl<Grammar, R, R(A0 , A1...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2>
    struct when<Grammar, R(A0 , A1 , A2)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2>
    struct when<Grammar, R(A0 , A1 , A2...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3>
    struct when<Grammar, R(A0 , A1 , A2 , A3)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3>
    struct when<Grammar, R(A0 , A1 , A2 , A3...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8...)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9)>
    {};
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    template<typename Grammar, typename R , typename A0 , typename A1 , typename A2 , typename A3 , typename A4 , typename A5 , typename A6 , typename A7 , typename A8 , typename A9>
    struct when<Grammar, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)>
      : detail::when_impl<Grammar, R, R(A0 , A1 , A2 , A3 , A4 , A5 , A6 , A7 , A8 , A9...)>
    {};

/* when.hpp
U+Q9x5yvu/Q9DEMqd4R0A8R2mwti22m14ZmASpvFYhufwlsaXbv9B5w98KXfvokHQxfF2tC5LOLSfyqwBZEv+JpB8zI58IYL+X5n5+J6kjwdCQk+uGv64x8A3PisMc3HFxiWq614KR9bDzY/OGxZ4oKsVbKBKp3ASuejXR+jlAplPM7HthHyxrjTQSAzzI3OXfQsqznRgOChNFsPz0VHTLI0VX173c2zzDbfdhuiOV4KKRKPd0c7x+g7ji0C8ZLJnORQZvgQL0b5xCo/R4shSWV7HxlPH+J5VU/bDRwvdSrFUkM/r+3WMsjEZptB/8r69bpE44P9ihhXfiD4G1kd3kW3/5K1TtTq+xM85Xe/VbopPHvIW8jOwqycQ7Xtq6flFm3Z/W2//Tw0jUuhbqKCcRG6qCCaUKtPrYAxK+jdxB8Pj3RpdQWJk8EaJ6rak+YtG2NnDOFLiilTaIx1EtIkqInk7H1/bw9WZIBH2R87lFi4cvu9VzIOD3zpbjZGoFpbMlvPXZt8RGY/M4enwyz90hdIVQpLeNRvPonFeRBbrbsrtg3ktAfCteBaW1E8+U5e2FVkIh1eHPx0WdNsNbgThSUzvMIfPpWsxDdaJMFme1uYfPLnLqQczL4RWOguvQDNT1r4CFaWyLVvnYeHPmfP3HPjGug+UIKR4k0T4s3MWEZ1YYq2ykGmPe9fK0+qTpe8Cs+AzcBoO2SaXsXn
*/