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
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
*/