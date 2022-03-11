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