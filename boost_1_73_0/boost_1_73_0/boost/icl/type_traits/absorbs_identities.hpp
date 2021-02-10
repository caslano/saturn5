/*-----------------------------------------------------------------------------+
Copyright (c) 2008-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004
#define BOOST_ICL_TYPE_TRAITS_ABSORBS_IDENTITIES_HPP_JOFA_081004

namespace boost{ namespace icl
{
    template <class Type> struct absorbs_identities
    {
        typedef absorbs_identities<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* absorbs_identities.hpp
Eo2UhgKf9mdsqKg0GorZu9WMO93sGPkjxVnBs6yyUYGQjA49N5YXAZpoLhMGg1806ksr30t+CdFHGDWMbM+LAAWEAuMJwZD3CTyvP6Z60cCkFzQYA0iIFdb1XZSExR65YuCa+2pBK0BCjK+un7aHfKK4MesHnl6ObbfqIOyrfUqGhSCAahxE8z6jTOQrnli8OOLVvkLD8WjlwHMgUJ3PKtFCYOWEtscifcAcxXY8j9hAgn6EkB9YbTmA8UzcGYTJgNZTNSb0VMNyWOJ1sMRFLMDgNdBQsRSoOVmLnJMSntO18JyW8Awe1kKE2aEZpqeZk5ptdjc+KDKz/nVtnNtpWg2/UnDFelJoaUXifkJpTcn9eyvWlYWX1pZe6CetrzgmX7FaSTFp7aUhf4YINEJKH7NL5kWgQBwGnvV0RutMDDiKrORV6qeELed86hV1J/CW+Tob8yiQfELzVRyocFJpSSAJnBvyUtzOJsmWDhwbhA6OCuscGNqWT7WefZPzx5fw7IwUsKUQb94UvrL8EZQgZI7t+hF1vVOWoxFnIiKa0pPleiSYJB16Feyzc2iwTL2edP11MrMH95hfDpjYAaLvbsyjxYRoUBUfLLh0AoFXe4Q5LmhWx4EznNMBhQ2+fB4HUzt2B5j1ooiK+fAY
*/