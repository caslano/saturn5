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
jT98jqjv074kxzoz8v3Wsj3H5nPV2Cw0tm7Oozp8h8AupI/381+u9KVlqbhe9tYcfMO9SniseAZ1vILeJXhNjvUQew8p4WRJwnjfId7Xzyedef+EOy/3+7CZk3g95sE3YCzZ9QzK5WSnkeaw7oSTl+5udY+4MxP3ixCdb2yx4Q027kDwe0MYdyvCGxB3G8ICiN03uvAZ1O3diUDmLi1351RvZt0AfW6dfG8RuO6bb0U9vs0T586UP847EOediOO3Mdgy3gfP1HZeccFoT+dher98xyKeE5xv5LRaB70Pab8fadu1BfrbGOb599j5bXxgYEswX75XwsnE5hdNDIwnTPgBoc9L9A8N9A1PjmLu/YDQFJi3lCQcxilMjI4PTG4ZEUOYaC6/WOCl9J7WSrz9dAnNqamEiWFLG26UMcCWv2FK/23a3bcG4+6Gv963c7VHIeicH6J6+4inzS+t9bf5R1HvH1Nz9xOhnwd95h/OuUn3hnrbXvYDOzJt9s05s0Xdpi4GKGQkQ1eQDn2lR4c2MG1X86lAZ5G4bn36abU+/Ywabz8brrWAE3jsbf3Pkx50pdI3voBwgdNbbPpLS1z6V6v0r5Ew21FdSzygC3G7yXrcrTd53vgq4p2ZAh+U/d1U9huoDm+sjdN9mOi+RnQ3Ozr/XZwc+oDhfwvx/wbx/6bjb8PvUuG3q/BlFOZ6maB1OMvz9xSd4P13knlvJpqTlF/zcG+O0izG/pyMNbG9udvUuvu6GWKrPC1fDcYgiW2rjC6Z6/1Zp4/O9ehHsJHi+7N0/r4h4fTMNrmaGdAVKNvlBcALhH2b8pvzOFfv6ZCDWkkhoCkkWDrmezpNfqdPozuZ8kx0V/Npmdh5+Xo6J18f6dmLiPd69s9DPopTRNMV88/THM3rlcp3R5VHf6zB3H5HjnN7A9mTYa+D7cmGBvvsHGZlMI/eorO6N96BXIH7gD+t5fuAI5vP6DX0YXeksCRcq99zjL1/MZxYjf2VO2P7K1tG+oaGemVLo7d/cHT7wNi45bwHVPizjai2+74lm53i1Hm249PdNH7cUxu3z7lXwtqm6ZeYx34FWl7f/tqzBv1NLfsc9e/33lcb+hl1/iSWlbAPTvWeBGrvftJ5ryuXuFg/cVzWeR8QerZ/z1f1+DIJnwE9eGaio93edW9vM9cQRMjs87vm7dFMU7gm2pOmp42o7DixJ826Uxs6m5vUm2kPSd5GRwaHJ8zrZjulzY01qXljpncikPQsSK3P1sl42Dmt8fCf5VvAraXn0hohT/kWz4/GYDylbHmQjVJXJqrv+ereewHf1cZYGdR0r82tGyvtQt94O8N4ifW/8/Hs9QOt70mXoK0eyXEs4rsYqUQ2X1ED/Vpb7Vd66kGxMW14UHRsfp9oZMeOgeEJgYVjzGOxMSbT2GueEBJb1t7+ybGdwfaqBkb64F1YB3ntW/9BXk84nazwzzTO/FWNM0/W6ncKZyaehl7yeC3ZToLewPQ57ozFcfxu+Rg/S/CStuWn9xZmC47W+0KDs9HFbuwSmIwpOp8izyENeF2b2nN8m+fyJnj1LpnkrUDwJvwUyvqVlNNjn1J69MLF0JXA6y+l7tPvnRWB79Pl4Av8bkqHeRk6wcV4yW/Lq8yVU2h96YkOQHmTuhDp57uA8bt1FVGdoN5UnVQh71eX77kmMTBNX6v4CU0MXyd47PcAv/f9nvrFrh0eV2uSAwTH4+6RMu4O/0vG3WfiM8yNmXlqbM6n8TGkmad8tc33+Gor8Pi0WKD2Dacaf/U4XbiHbxWy/5SkW5qDuMU0f5gxuRRj8sGLcxuT7VqxfM87pYdG8oZzagnzGCF4yAjTJRNLBc5yqcc=
*/