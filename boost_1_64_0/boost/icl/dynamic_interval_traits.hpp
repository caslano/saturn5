/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926
#define BOOST_ICL_DYNAMIC_INTERVAL_TRAITS_HPP_JOFA_100926

namespace boost{ namespace icl
{

class interval_bounds;
template<class DomainT> class bounded_value;


//------------------------------------------------------------------------------
//- Adapter class
//------------------------------------------------------------------------------
template<class Type>
struct dynamic_interval_traits
{
    typedef typename Type::domain_type    domain_type;
    typedef typename Type::domain_compare domain_compare;

    static Type construct(const domain_type& lo, const domain_type& up, interval_bounds bounds);
    static Type construct_bounded(const bounded_value<domain_type>& lo, 
                                  const bounded_value<domain_type>& up);
};


}} // namespace boost icl

#endif



/* dynamic_interval_traits.hpp
4m2yRn4RGp7LllsrjCOQc3oSh31zKtZ5nuh+excELYfGOk5Jx5o08s0p4tgy7WMxJ52WRJTRvCIXit+/I7CYAoxdmCvH3MmA8OFCz8rzdXOQ8VGEbDtxUNenwTZEKMlvGV5kZpadlVyBiZBcrAhxwxaBHIiVvfwD6glNcWw1su2nwaZeG4TWJbm9An/Si2f5dG+PmwoFcRVoRck7lpM3Ot0EDhXef5Surn4ilPL/cmh97/HLfcVo9VsOu3HxbnefsDmU5kciL866zFSsovu8lBF/aAkaOkmAMS1CB7E5Xn+EkYdEPl2LWl5A+GDxvZYUxX2qYEJzhx8l+ufqo+w/o5cdmLcOK3ZgR63y0muzjWOfn5RK2ayro4oGgXVhWrwW3jlcZEQVBt7bQtc3WQ1uGi7yvZ1pozPnuoM26/IPPuV98WW1l725OQuwa4C7qLJ/s4SaWjvFOcZYJQqYmml0CKN7iiz3aUZUq8NRzDUzMNY1PjS+roT6FzMK2F0OpZSDAl9waHe54YQFncOoRR5T+Uu++DlOtAPzmQud/mdICgJPg9HzM3j1exdj6w==
*/