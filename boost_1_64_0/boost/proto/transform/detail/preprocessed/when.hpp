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
lMjVa+yoEij1L/cgnccjlkc2mLMjfstAaIQIqrq4Dg28GhVf4S4awuinKba7+NkNlQQN/VSW1k60TpQQHyebnMklr9R+KwIwHtv5jLonMX/t6YTlmpz6I1pR2FisIn3Hw3O74OcFiTBKeSR97GuGag63XTi0TAAq65m6ueMPo/nLPN0JDRCW9FRR5cjmDq43yMwDgdoz0mj4gXsDxZgXhF/Rhqh934Gfutu2z2u8yJ0m7dgqwA63fhBpIfqGXv59TGonYP0ro4dftjx1TRIMkOQ9atuZkuTPE7f5yNnH/AdOK52OmNDzyQw9lFe4BPkiYU8Z4upq6OeCXPs4b91yDtIvppV1U2lp7MAd+VYv24s0xew4M5Ui5GV05ilB9JcNYPdmaNvQ8UCPM9gEwK+oEApy9/1HVBnCHMwEMRrNzHUfKGRe0slybfxeacDaFgg7qPE18LMk/b3iYOjgQHRsu5ZyzsiHKc3iDOzfo9pSDfAKZnjQPWKqo1aZAutHl0JX+vCgayHALLmibfNongQS9MEyiwQKxCB/JgwnQTpV6hvDcDWDXh24OIbaXQ==
*/