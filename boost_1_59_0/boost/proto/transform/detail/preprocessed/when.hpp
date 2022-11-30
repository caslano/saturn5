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
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
*/