/*-----------------------------------------------------------------------------+
Copyright (c) 2010-2011: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_TYPE_TRAITS_INFINITY_HPP_JOFA_100322
#define BOOST_ICL_TYPE_TRAITS_INFINITY_HPP_JOFA_100322

#include <string>
#include <boost/static_assert.hpp>
#include <boost/icl/type_traits/is_numeric.hpp>
#include <boost/icl/type_traits/rep_type_of.hpp>
#include <boost/icl/type_traits/size_type_of.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/if.hpp>

namespace boost{ namespace icl
{

template<class Type> struct has_std_infinity
{
    typedef has_std_infinity type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (     is_numeric<Type>::value
                   && std::numeric_limits<Type>::has_infinity
                )
       );
};

template<class Type> struct has_max_infinity
{
    typedef has_max_infinity type;
    BOOST_STATIC_CONSTANT(bool, 
        value = (     is_numeric<Type>::value
                   && ! std::numeric_limits<Type>::has_infinity
                )
       );
};

//------------------------------------------------------------------------------
template <class Type, bool has_std_inf=false, bool has_std_max=false> 
struct get_numeric_infinity;

template <class Type, bool has_std_max> 
struct get_numeric_infinity<Type, true, has_std_max>
{
    typedef get_numeric_infinity type;
    static Type value()
    {
        return (std::numeric_limits<Type>::infinity)();
    }
};

template <class Type> 
struct get_numeric_infinity<Type, false, true>
{
    typedef get_numeric_infinity type;
    static Type value()
    {
        return (std::numeric_limits<Type>::max)();
    }
};

template <class Type> 
struct get_numeric_infinity<Type, false, false>
{
    typedef get_numeric_infinity type;
    static Type value()
    {
        return Type();
    }
};

template <class Type> 
struct numeric_infinity
{
    typedef numeric_infinity type;
    static Type value()
    {
        return get_numeric_infinity< Type
                                   , has_std_infinity<Type>::value
                                   , has_max_infinity<Type>::value >::value();
    }
};


//------------------------------------------------------------------------------
template<class Type, bool has_numeric_inf, bool has_repr_inf, bool has_size, bool has_diff>
struct get_infinity;

template<class Type, bool has_repr_inf, bool has_size, bool has_diff>
struct get_infinity<Type, true, has_repr_inf, has_size, has_diff>
{
    typedef get_infinity type;

    static Type value()
    {
        return  numeric_infinity<Type>::value();
    }
};

template<class Type, bool has_size, bool has_diff>
struct get_infinity<Type, false, true, has_size, has_diff>
{
    typedef get_infinity type;

    static Type value()
    {
        return Type(numeric_infinity<typename Type::rep>::value());
    }
};

template<class Type, bool has_diff>
struct get_infinity<Type, false, false, true, has_diff>
{
    typedef get_infinity type;
    typedef typename Type::size_type size_type;

    static Type value()
    {
        return Type(numeric_infinity<size_type>::value());
    }
};

template<class Type>
struct get_infinity<Type, false, false, false, true>
{
    typedef get_infinity type;
    typedef typename Type::difference_type difference_type;

    static Type value()
    {
        return identity_element<difference_type>::value();
    }
};

template<class Type>
struct get_infinity<Type, false, false, false, false>
{
    typedef get_infinity type;

    static Type value()
    {
        return identity_element<Type>::value();
    }
};

template <class Type> struct infinity
{
    typedef infinity type;

    static Type value()
    {
        return
            get_infinity< Type
                        , is_numeric<Type>::value
                        , has_rep_type<Type>::value
                        , has_size_type<Type>::value
                        , has_difference_type<Type>::value
                        >::value();
    }
};

template <> 
struct infinity<std::string>
{
    typedef infinity type;

    static std::string value()
    {
        return std::string();
    }
};

}} // namespace boost icl

#endif



/* infinity.hpp
fCm2lj4nnybfjRXNKIldr/1wjl9/rI6W+vFTvhrbRDf48VOefz7bmT7vx0+//th8ulH721XyVdgmWqbrs9i3A1Z8QUnsC/Jl8rFYHd0kv83Xg22im+Wr5aGZvDak5fJv+P2OLaUvyjfIN2HWl7RfPSZvxaxb5D+WF81iu9EK+Tbf3zDrVvnLvj0x6zb5G/J6zLpd/kf5Msxa6e9HLtHzAmZ92d+PyFsx6yu6XT3k+bN53NEd8nJ5FWatkg+SV2PWnVr/cPlMzPqqfIx8CWbdpf35OPlarIVWy0+WB3N4z0F3y0+XL+d4W4t/LfTxUxO2hu7x1xW6fAu2274nny4f28B+QvfKG+TrsK30dfml8tCFPG/SfdoOV/vtxVbRWl1+qXwrZt2v/fyL8thcnvfpG/IV8lrM+qaOM7fLV2LWOvlX5TuwonklsQe0fe6V12DWt+QPyBdhG+jb8u/Kd2GxRl5Tyn8gH4XV04Ohj59WYM30Hc0DPKXLt2EVF5XEHtLt+pFvH2wdbdDj+sd+/bE+F5fEvqvj7U/9+mPW93R9tsmXYdbD/r7A93OslTZq+++UF13C9qFHdH+9KR+NWd+XfyBvxKxH5Tnztd9iVrO8s3wVZv1A3lO+AbMek/eXb8esx+VD5PnzedzRJj2uR8qrMOsJ+Th5LWY9KT9Jvgizfiivka/FrM3yqfIdmPWUfLa8/FIed/Qj+aXyKZj1tHyRfAVmbZHfKN+EWT+W3ybfjVnPyO+WV1zG/kM/ka+TT8asFvnDfnsx61n5k357Meun8md9+2PWzxLO1/LYAvZ/2ip/VT4Ws34uf0s+E7N+If9QvhKzfinPv1TbAbO2ybvJ8xdyv9Ov5H3lozDr1/KD5Asx6zn5cPlqzNouP0rehlnPy0+QV17O8w69II/Lp2DWi/Ja+UrMapVfIG/BrN/IL5aHrmCulF6SXyUfjlkvy5fKGzFrh/wW+XrMekX+VXkrZv1Wfr+8+EpeD9Cr8g3yaszaKX9cvgyzXpM/4/cXZv1O/iv5Hsx6Xb5Dvm10j5i1S/4Hv3/H9IhZv/fXn/JJmPWGPOcybQfM+oM8Jl+JWW3y3vJmzHpTfoB8J2a9JR8qjx3ZI2a9LR8tH45Zu+UT5FMw6x35qfJSnn+td+VnyZdwWes9eb18LWbtkc+Tt2DWH+VXyENHsaT35Z+VV2HWB/Ll8nrM2iu/w7cbZn0o/7p8K2Z9JH9QHoztEbP+JG/27YNZoXDSn5bXYQ0U1n9L9wv5QsyKhJPP1y/IV2BWVP6Kbx/MCuS7/P7FrBz52/JtmJUrf1/ehll58vAC3a6jWTfly/PlpZhVIO8sr8SsQnkP+VjM6iAvk9dgVpG8Qt6AWR21fQbLV2JWJ/mh8s2Y1Vn+CXkbZsXkx/j1H8f1py7yE+XDMaur/DR5NWZ1k58pX4hZxfKp8jWY1V1+gV9PzOohnyffg1kl8gXy0cf0iFml8mv892JWT/n1/nsxq5f8ZnlVMa8HqLf8dr9fMKuP/C75ZKyOyuT3yedjVl/5t+VLMKuf/GG/vzCrXP64fC1m7Sd/Wr4Rs/aX/0zegln95c/Jd2FWhfxleX53nh9pgPx1v9+xSjpA/rZvB6yaDpR/IK/FZtJAeXShtj+2iA6Sd5AvxaxB8m7y1Zg1WN5b3oxZlfL+8u2YNcT3f/kezDrY9395cQ+ev+gQ3//lAzGryvd/+XjMGur7v7wOs4b5/i9fhFmH+v4vX4VZw33/l2/ErMN8/5dvxawRvv/L2zBrpO//8qISXofTKN///XZh1uG+/8tHYdYRvv/LJ2LWJ/AC2//ltZg1Wr5a3oRZY+T3+/2IWUfKvyPfjFlHyR+V78A=
*/