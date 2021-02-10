/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_INTERVAL_SET_VALUE_HPP_JOFA_100924

#include <boost/utility/enable_if.hpp>
#include <boost/icl/type_traits/is_interval_container.hpp>
#include <boost/icl/concept/interval.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_interval_set<Type>, typename Type::codomain_type>::type
co_value(Iterator value_)
{ 
    typedef typename Type::codomain_type codomain_type;
    return icl::is_empty(*value_)? codomain_type() : (*value_).lower(); 
}

}} // namespace boost icl

#endif



/* interval_set_value.hpp
PMyO9plsCHtUPef1XrBNoeDi/PwvmOHl4nwKH3hRwYqU2zUVm95BjC6TkvFKgzWSTnFW6v0UtjxjOV7RiT+4gIxJJdi6UVqejjjP1QNBITkOkmrf5k8jai5pF3+8ra+8UZBTqsOqfVvvYSMIzmk21c7sWKZzTGebdpqsMZRdYvQOVFyxtMvTlrc+6u2H6poSgYnSTgFaspPkuHEgCpbxJzt0wI3gNgw+ugtnASM7wu8jsP1F+5B9F98EISzcaO7Z7ioC2/MArULbj10n0lif3PgGM+DaDtEkQCvEO2L7c+9u4frXraG7uvVcZDkCQLDUGCsnnN/gHfvK9dz4S0u/dGPfiSILMcAPwPno+DFENxrnRNmVA55rX3kOLINQQ9n+F4hunblre1PUHTrzeIoQ/Sc0mQd+5Pxzh3D4DCzslX2thYSt6eFr69iNHUcB8oboXnTnxdqNZRiswAsirRzuIgc57NjW1hhDlBxN0c5BgaHW3a0Iex67ga8NkDoOba3Dd64999rx5462DVqDOAjxwbvoYDAFO3QjTRrcxRoHAYIWFmF8pwNto6/jgVpaFU6IgVjZLfDy+9k4zL6GOv9z9qEpZ3oZ/PbBOk3+9wb/DmQR1tx+dcADVk1SwYZ2ix019fUyyZiA95CPTwrC
*/