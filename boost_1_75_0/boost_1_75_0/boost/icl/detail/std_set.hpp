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
A7WxscuX1322VOjeqn0L2TgC/ooW/NJGHX4Ud1vY8hqPaeKvRXf8bZSZBbecQlCEuc5WfjDKtOOaZQM0wfDOuSXAy5aZ6WVq1GDKc5UwzsCxt3lq9i3fvcYNZIZrL/swrmuet7vdUvYUOM/37h0AaXxDF+8OuU4J+uu1jH+jkS7LvI/5CaqnhwGm2Mk/hUM9AwQIn8RdWp8V/Efj9WcFxIbepwSfh5tXwImB5/nB+SygTqP840seob/EPUtzNTpmT6dYHln+sipYREeVGLykJZFuxoiH2e7Eayp9T4Xe2O/cHf/yKB+DlE3Bq7P+jXww2fJteSECLm20vuzddGc4YlhrqsoPqfX1QpT89oPzpUOq2HEacGGSIx+jD5tWyu9I2XOX/LPviEXzRAc24BTHlXRXbxv++GkXppoV5xW0SCR//xWsGsmAg2dexHFfP/pZfL/J5733rl+dksyOfdf6fhXOUkXvaG+CauGvav6ROiObrdj2VUmRKdFcNwxlg0+PtzC4UUfaCz8fHCT5fkdK8vcxhZ+nJ4x2fiCzz6No/UlPUI0UP/VcXTZdvtUIVywopyPsm4TzP5GqbkmFBXIcPpXnIFWI8ZIOFqn34UU155Q2y1X7Jj82O4SOMBnc4knv+1y5eIy2jsMssUiKvTQjzMih4uApClBdaKZ3m24AyZdA+KNtOlI81FbQmDtLKPMTvWMaQNYeZT0Xch3u
*/