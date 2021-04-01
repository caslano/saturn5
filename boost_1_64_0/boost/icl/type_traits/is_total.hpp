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
/DBbubGrtzICGpiuM3ghLvO72gCKCOjTbMf7JQ9mwy25NYiWqBc9f6puO2dY1y3tqH+eoqvXwwOAicdkgROogSKD1MfUzHaVjjICq/UCgx8zT4yyTc4egg0PlJD8T29AT/k1lcdbDZ0CrIdUbaw9f8nxoqg4sUyc6GKD1IRiUS31Jn5B3uvV6PxW+jcDXvUu8xjaKWc3hHZOeEh2PvHFV1NoAMOxSMDg6QWSykAuiGSqXDvU4u7L5OGfvwoobns4wodiAAQBzxEXR6OulejbU4b2RDxNNg8XQ4GC8IYnTz8UtG6z795rhw/Bd+fVxsd6gUkQmqOb1scQTCgklC0pGTV1TVB1XghQutkFFkaLrBY5jLXfQIQDO6pzk7fQ2zh9gETlb9M1jeV5NKs2YKQz3UQq4fBEICKTSUc/eBqyT8lNFkc/A9/B3LYOfrhnjc9qGOvKGXjgzxiUxkeGnB5ffOmZWpfON1BTs8QwQdfkrTGC9z44du3T+gJeiRXH96DEKpKutofz05LgYtbsYPM4ulC8NGAugyDwUwYDQxlRinam81ch9ZHPp4G6dg==
*/