/*-----------------------------------------------------------------------------+
Copyright (c) 2007-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007
#define BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007

#include <set>
#include <boost/config.hpp>
#include <boost/icl/type_traits/type_to_string.hpp>
#include <boost/icl/type_traits/is_set.hpp>


namespace boost{namespace icl
{

template <class Type>
struct is_set<std::set<Type> >
{ 
    typedef is_set<std::set<Type> > type;
    BOOST_STATIC_CONSTANT(bool, value = true); 
};


template <class Type>
struct type_to_string<std::set<Type> >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +">"; }
};

template <class Type>
struct type_to_string<std::set<Type, std::greater<Type> > >
{
    static std::string apply()
    { return "set<"+ type_to_string<Type>::apply() +" g>"; }
};

}} // namespace icl boost

#endif // BOOST_ICL_DETAIL_STD_SET_HPP_JOFA_101007


/* std_set.hpp
pqRhHy2oR4PELo1KR/8UPyj8n3aeQEkqrRCO6a4pPfHH9NHQwvOBtjOvfOiJk3HSNClsoLxU6yiTeQsyeYZUKES0tQtXq0AzsPDjmiL0YjeF9b0AkHzP8t5ufuvIkp5wHJVsmpjmTAEUQVO3rHoE5hMaoQr2lp+WBqERxOO63bal7FZqNqPy7IBWO/9snvGa1QTOrzmbTMxCUvmI9wMMVx3yPWqYAIkMAGfk4aFTZGLUYHdqOfva7bhrS11U5+JMVI+ZwAIAs5hkQyGz6wEGL9hs09SI7GgKxk3ZbNPgsz7C+/eDInFbKXYaJMqSom2VdTivXArmEQJebihkIyfEKsD9b8qyJzAvLeC5bvFOqdIrLu7NGcliPV++XCf8twzabgSIxSAD+xeKodtlm8gOyHNbNqSg0PhF4BBflq4rgmk05UxevhotiynZt3dqrLU277I5X2XEPJei/80d7CyFG/lG+BgbcMeMvp330oAPssOXRdcAlQ1mIV0CKONsKD4l26L517nf1ou2AjR76yK8VwYA+jmWBjgydWVM6l060BcmuReLnfchvtk2ww==
*/