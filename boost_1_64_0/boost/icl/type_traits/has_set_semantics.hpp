/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829
#define BOOST_ICL_TYPE_TRAITS_HAS_SET_SEMANTICS_HPP_JOFA_100829

#include <boost/mpl/or.hpp>
#include <boost/mpl/and.hpp>
#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/is_map.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct has_set_semantics
    { 
        typedef has_set_semantics<Type> type;
        BOOST_STATIC_CONSTANT(bool, 
            value = (mpl::or_< is_set<Type>
                             , mpl::and_< is_map<Type>
                                        , has_set_semantics
                                          <typename codomain_type_of<Type>::type > 
                                        > 
                             >::value)); 
    };

}} // namespace boost icl

#endif



/* has_set_semantics.hpp
lcLs0ASyc8H5U/PJYM8eYiMMXMFEM6HyV/rJUUTrg5h1Ib8BmnOtbRS3cpcIDW2tNuu3HidngV7lMvqFh/gdTZiFjvIvxZxQHDWJeUCAMCGEBr4I28N0CwZkQc6/aYQ1p0tmOOo+B8MRTIxlVUtdQls+zSwkhwKp3usMyycSdGN/1bN5mglTf02KeVqmvODsYdF61qP4+Ojn+hFu8xYPG8/UkgptdJ5TR0ge1ostrktNoEta4QlKN8iwJFwriAbkQFsNEoSN3sSgcCFM1yvWBrX1yO5zAAKO9z0AX25fSjPg/LljxAekHhX+Ezus7c6lrfwoATi3y20VF0ttS4gcvFFShRVKoi6v+xCH5+Jvpseujoi/xSdCzIBR+urLTw7GKTz9Sj68IuWxkw3Xa60SC8ACXYU5xtepRW2XKc3VpgTbN/tvm/PFT/0OrryZRRPxKR8JzfWDli0CyLL9vNnTl6v6ezx7MMub1VkMQd6xcaZaP7GG6brf/E5FEXDAklyiIZad22NrTkqenRvATLbbCpev6dRruAg6JppimjL5AEpEhL3YJ2TVqyolmQ==
*/