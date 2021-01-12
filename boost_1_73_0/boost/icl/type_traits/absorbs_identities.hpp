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
YwtnguMRxJDpfuK6ai9mpfqRAImvG62AieVy/L8E+316HemIJ4dLwjp+1/N75XTsmgsbZuA7NoxZJFih8ZXO8GwB6Kv7eYnuzEM0z7wSDcPsjJYNsRERPipVIp8VETJedNRLwyvK/Jq0bhixkO+6RlBbxD5hpC3tn0gycvsBRn70hJbFUg5SxLDsgDZ8A399Ekd6IHHVT9B+UitOQ9GAj9cPlUByKIujqG7xO5aek1gnEbU7
*/