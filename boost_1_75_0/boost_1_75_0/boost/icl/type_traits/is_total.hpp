/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_IS_TOTAL_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct is_total
    { 
        typedef is_total<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_total.hpp
hYKbX5Oo7AmqlZAI6JJPMxVs7fbOu3xalSHQ9mTARWGh1TW+3MwDVb7PPf2Dj8q2vB/iVFIhz3/3BRakp8lD3lUO94FHoKeOFX9czDizGbze90LF/sbuUoNhKp4dm0/bVt1uFF/TIoptKlm4K+BznrBnwKf3z823eXZRWupdvohu9twysa/nY2kcB75P6UskGAiVEVSu0JtQ67fGTm9EhBTs3zrQejtvhFd1b6CDP0MVhEyva0lbIqxSrEiC4n5is2Y8FbUwrftutiDbbHILZWvoIT6WfS+E+doW+/tn04LWUUEU4Qc64TzjUykbWq0inlW3i/n31oa2Koz5Df3aDww7Rg/zWC9nCTV1zu2/rgp2MX4HeRQLb5z+tY71qA31/YCUp82SnEf4tTMmkrGHLr0NUs1aG63srSrNICz1VLJsMLEPPKmQtZbNLbiktZEDjLFMa/BNudovUtngVj8J235RwyQvN6v2vdCnIcDNup7mrRYyDfJPWUkJYtkNdQ2573Ml1/lZnV2cBGYp4kx6X/1I+AX0Rp9CW4zXyFv/tL63S9c97VxSrv4UYZFS5E21H62Jkn+u/a06b1emo0kxwh9/RgwX4sfa7jHUeoD+stnuF0YQeHvhDKElyL/NyQLMj25jIYCbMolVY9tKIlST4Vqh22iYMCEC5enTEqiNYm2THBv0/BgGZca1i0oBGdbHUyNgne/hzLuhWkOg
*/