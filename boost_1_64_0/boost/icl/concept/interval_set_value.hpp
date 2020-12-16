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
DFeH0oWn49lY3xE4eVyRDLWvIeHXeXyX7cXxizm8/HggLOYR2+G9EUPLZTBBZhPmLEzikheqyWLkMPpiNAxWGl5cS3oGRhx5zyItT9HwdAl+dGoc9Z0LJaueTmQ4eeFwXzvtTypgt9z1yHxWFEvWCaQfXXd5YX4emvTO8YW9B+mF6g34ZN6H0b9wbpxdR3fX/cOVZR6YtUqFy69OoTj97SRn85bk1GSRLGaJxh+DZGgoYDpTiLevs8OI4iPYcvIMtlpP4sViZ2ATtQebSzaSd/F3Gic0jmbE2OOaxTaa/eQQC7GVpZhQfRze4Uc3X2hjzHEZah2+hyc5W0HAOvizpWoU13qLGqZbU821aIRevYPqsVdYnqMxgqfe5sUS0tjv/YXUW8zJJ+ktmT6+Tjsv/eN7Z5jgpqUQHtVEUOdhZ9hWqlH00yMsbFcj7bRdQCXLBfdB1R3Pplwje/UOJiIdQ3NOFrPmV1OR1ZTFba63o7fmMbMTz6F3tyyg/zMIxbePQSVmCKkeG8XXLflCYTmN8DY/Q3uelWK6XTPlz3/IbMqccHjlVZLYOZmMw01ZrYs/XTpcTP+ODNDMd2txzuckjUh1Zzs2WGJcsynvXHlaMM++8ECXfXS5gphn5hr66KwOJpaEhSFXWJ/RWrz5Fs8u2C3Bn345trB7M0l/+w+7t6yBxOtDMJwjyIseb6IXbTNo1Rd//uHdUayZ0k77LhkgqsWMV/pdQ3hmN8+aeJpmHbyHmw5dELYPZrOiaxAzTYylKqyD2fzpvC/7O/ZGBOC1WS51nR+kcYes6IDOHR5h8JTW3cvhvXMVyW7naF5ouY0G34qSY7cu7G+94CWiGTCcpImsfbHkHmPJy3wuYEn3WT7vkBcOhS5jhyoC6HFiF8kNe0lPhruRwuhe/N7vzMYNuU0j3i0k0cL1ZOR+hJUHXIfRiFJ+XuCDEtWTuPIfb1RmV+BS+n584n2goE6SyFqL4SrqyJJ6yGsfgoxuTcSd7F+0rPQF7VinCVtJJfzur4V4UiycRueS2InvsL85mzS2LMLDzO3IulLCbGb70HCHHHhmXaOttp7k01gIkY5DNHfiHiQmKnEV9fX090k6mUU00MP+BtYi8N5rl6rzVK10OBetxZOfg7R8XA1erlxCbdMTmMLHJpQcaKOJK1opWu0V82kSJtUiO6z/4U8h1z7yn4mp9Df7E59+4T3VjDvHul5uxtRZVly87RWWf6+l3qWzcWHCBbquNRnzf1hwIcF8rZDqZHNq71F4kSIXG/ucemaqc//xEeh8JMwjcjQRc2oozbq8hEI6P8JF5TK2XJVn/h2BsDPtY9mjhLDiTDfez5GEWOFtljQlg8oE3HVeaSSl8ZuUeFQVuf/V86LVGgL+N4/VKL7A5rJulGUVI/P2bf5hAsOZRkcMpK/AJ2krvjEuEhpqyRB7PYrON7xAUE44lWeP4azgHin7ODLzByZISvODeYoj5htX0Zl/tuTma8SFf+vSFqU5rHZIAyw9U7BRwxjLp0WwNwm1ZLrpPC7PeETxkgFsccgDnNfcTDVzLAWczo40+9YiqWURG2aURuP3R/Kz5Yb0MN2XzamPorr9f9lPBw+sGG6JFfu+0JVlY2Ci2UBby//BoCoOfXWv2BFXhlmJLpgemUlL7ZQoSH4SbPPns6Xrd+DEG0Py9BMwdpkU1J1/AaH6Kpxe9RUp21O5e+hDpLvLsTV3JqD/7yMmv/gLPt9eAIkOe6gEX2Bmwh2oeWzLV0puxNzfpVTvehXRS6Vh5KGJNXJbWPOwLBysv06LnVZQUWgGvswIJn6/l31J+YKZtnf4/fkGsLXYxJ50HacnIssxixVibGok/RFwyds=
*/