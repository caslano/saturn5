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