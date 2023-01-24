/*-----------------------------------------------------------------------------+    
Copyright (c) 2010-2010: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915
#define BOOST_ICL_TYPE_TRAITS_ON_ABSORBTION_HPP_JOFA_100915

namespace boost{ namespace icl
{

template<class Type, class Combiner, bool absorbs_identities>
struct on_absorbtion;

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, false>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;

    static bool is_absorbable(const codomain_type&){ return false; }
};

template<class Type, class Combiner>
struct on_absorbtion<Type, Combiner, true>
{
    typedef on_absorbtion type;
    typedef typename Type::codomain_type codomain_type;
    typedef typename Type::codomain_combine codomain_combine;

    static bool is_absorbable(const codomain_type& co_value)
    {
        return co_value == Combiner::identity_element();
    }
};

}} // namespace boost icl

#endif



/* on_absorbtion.hpp
EqQAeo4vYw5t9I83fb7+ZbbhxGzw3NwhZpsd/hvUDCmLOb48aVabzQbarVApL4RGaDBYBgl1P1nBD9LtAQATfbPFCH5BrMXSfHqM4yYcjubLbh3NSwvybnXgVfPhWMVv7OgE/VWBAIo5lR3HvacOdPIBNhN8+TfW/SqkcEoaKuMDDLO9/sfmoa+0Cy+qZdXKdZ1qtd/KX2YES4iJCwB4rpLPJ34ve5/LstM1JF5E6l1qcGc9ZwxYUVZPuJlznSj0/m1Jd11pPBV9i3j10rV544x7VY1YlnnBMZwMXyj/7+aLEv8aL/K7PHsTr5GrvVsJ4ta0x/456K+CWGr6ec8IZysOK/4wy2zcYBng5PFIXaZ8808vl8+uGpXh65NI6c69xH/k56jkZ6u/Kw+wsQm/t4pNi/ZuvHjP1tTfevL6WFOkcnfbs4/fYAyGGbvX3vSd135w51RdafRjXxe25Dp0nfC+zOR4mwlZHGe1MCmal22c0gr5LF2t9p8u6G6ROCRdAgB/NzZTCvy1GHUfOQfl1lrM+MXZLenUjALokkfda87bYEo45SogZ6YhNeHX0bNx5e3QY+YOTYR0/xtvNspbu28GxI5fBONwwkFfaAndvvNkj42hGib8eOvmSDXHz1IlgRzO6zeeeLIfsL3/fg/4dd8js/T61wtrSe3aDu4e91YUu1HvhtKIFQZ3fJlyOIa0ALdGmGRGpaC5euv9
*/