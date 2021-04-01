/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924
#define BOOST_ICL_CONCEPT_SET_VALUE_HPP_JOFA_100924

#include <boost/icl/type_traits/is_set.hpp>
#include <boost/icl/type_traits/codomain_type_of.hpp>

namespace boost{ namespace icl
{

//==============================================================================
//= AlgoUnifiers<Set>
//==============================================================================
template<class Type, class Iterator>
inline typename enable_if<is_set<Type>, const typename Type::key_type>::type&
key_value(Iterator it_)
{
    return *it_;
}

template<class Type>
inline typename enable_if<is_set<Type>, typename Type::value_type>::type
make_value(const typename Type::key_type& key_val, 
           const typename codomain_type_of<Type>::type& )
{
    return typename Type::value_type(key_val);
}


}} // namespace boost icl

#endif



/* set_value.hpp
+mrppaY04+3w7mdiRsVw5zvEHReVhcS58uC8nvS/D6dOd8HOQ8XAgNpF+ohAGUGBhX9HzfiOpAX/Mhl4p2fN5st9UWBsuhI1+eV9BLOkEc+0DWv9CF7oqC0GLxX/exmUMEyfB6U0XqWTBZgVG8Bovcy/t+uH2r27lsP7Z84SQs5Edid6U0a53phSpiVvmyUovk55lZSsUR4CiSf2VV6frHrKyxHNiXLU/pelyvOXPU8Cb3MB58cCKFayG7X0WlIqfTgo7vH16W+lfFu4bITwXXDaSLITDFc//rmoAbII7XOsj8F7thfRqyzslNsLYhqBw6KnrjMyZ3HwDuFQfKZuuKFBZ4L5wbk9jzPC9nfHqZ2rjpSxiiLnYF1m3jd3HkwsTnMPYXyEOn2VctLvAIiA/lZjSG5hpF19A0BWIyzl/ZitnZB9GK4Iuj38sCaJ4FpbHgvEYlYHugILs80rh7xZh9uszy4P9bkZMAYrVxv/Nb7Y3jrdyYwWuc7lL/B6+ceMEzkQ7ZJeMFxNg/Ws/Vmh121C9F4oglEvtSWc7HYXaVJXqbjjMBvW/BE3JA==
*/