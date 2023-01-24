/*-----------------------------------------------------------------------------+    
Copyright (c) 2008-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901
#define BOOST_ICL_TYPE_TRAITS_IS_INTERVAL_JOINER_HPP_JOFA_100901

#include <boost/config.hpp>

namespace boost{ namespace icl
{
    template <class Type> struct is_interval_joiner
    { 
        typedef is_interval_joiner<Type> type;
        BOOST_STATIC_CONSTANT(bool, value = false); 
    };

}} // namespace boost icl

#endif



/* is_interval_joiner.hpp
BJJqfLaHsCZ7FW4Oh6p8/KiS3aEdeYUsVrRMIL0uwv4rthuCTABFWpLhvFRL27M+eEVSAc/AaGYY+d6+IwJXWtk550eKsO+UasqjFWSPMRBbS2kFPNtDG1kn9KsCH1VTbjLn/psFlUGQhDlPDi2UCr+0wEULfc/DeHBeGlf9Ulc87lRcgprtN+GBogRdlThBNmE2BxyHt+komoEpTvX9sjxE9YyvadInjyYWj+robj82a5/VhQCm+F1kr2vHUEsNNqtOgc7Wir6smxnyA2rAYlbAcwe0Gl7t0GT7MWfYEeF3fjl7fthpIpDUiv6C3ZySWcQMqndD5i/Ca8eqp/a3J0L7wGp27Gh8+lb91L6B9ErDPyJXSLvBLOZ1d2UQf0KrIDzWpHH2fG0VD1HVEs9I1WBjvsdHMgzCE1VfALPFLH7tC3rZyxMCO5STu1Swlj6L6mxTnM1R3eFsmKUA0bg81U651txuGYBfUl3KPVPZ+gLNnCcDjqndWmwGf7HS4iPTX4B1N70OYd+Tapx547lFh+pSnHxG6/rkl+qP1KXNi/rlXy63TV6cfjzQoZfgtCm4NO92SKKeEfgT7A5JG76+h5O0qPL33MX1Ym+yur02rstYFWcGz2ZFHto0gGNKZr6kn0+UE6GLfjf5UNh5jSGakY17MER4K3fuE4uAjZFM9WQSt7akbPXkg7/KHsimDs/epViIRzV0r9RaggnQ
*/