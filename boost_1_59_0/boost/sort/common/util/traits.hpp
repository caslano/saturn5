//----------------------------------------------------------------------------
/// @file traits.hpp
/// @brief this file contains the metaprogramming classes  compare_iter and
///         enable_if_not_integral
/// @author Copyright(c) 2016 Francisco Jose Tapia (fjtapia@gmail.com )\n
///         Distributed under the Boost Software License, Version 1.0.\n
///         ( See accompanying file LICENSE_1_0.txt or copy at
///           http://www.boost.org/LICENSE_1_0.txt  )
/// @version 0.1
///
//-----------------------------------------------------------------------------
#ifndef __BOOST_SORT_COMMON_UTIL_TRAITS_HPP
#define __BOOST_SORT_COMMON_UTIL_TRAITS_HPP

#include <functional>
#include <iterator>
#include <type_traits>

namespace boost
{
namespace sort
{
namespace common
{
namespace util
{
//----------------------------------------------------------------------------
//                  USING SENTENCES
//----------------------------------------------------------------------------
using std::iterator_traits;

//
//---------------------------------------------------------------------------
/// @class value_iter
/// @brief From the iterator, obtain the type pointed by it
/// @remarks The main utility of this, is simplify the default template
///          parameter of comparison
//---------------------------------------------------------------------------
template<class iter_t>
using value_iter = typename iterator_traits< iter_t >::value_type;
//
//---------------------------------------------------------------------------
/// @class compare_iter
/// @brief From the iterator, received as template parameter, obtain the type
///        of the object pointed by the iterator, and with this define the
///        std::less with this type obtained
/// @remarks The main utility of this, is simplify the default template
///          parameter of comparison
//---------------------------------------------------------------------------
template<class iter_t>
using compare_iter =  std::less< value_iter< iter_t > >;

//
//---------------------------------------------------------------------------
/// @class enable_if_not_integral
/// @brief This is a SFINAE class for to detect if the third parameter in the
///        invocation of the parallel sorting algorithms is an integer
///        representing the number of threads to use or is a comparison object
/// @remarks
//---------------------------------------------------------------------------
template<class T>
using enable_if_not_integral =
      typename std::enable_if< !std::is_integral< T >::value >::type;
//
//---------------------------------------------------------------------------
/// @class enable_if_integral
/// @brief This is a SFINAE class for to detect if the third parameter in the
///        invocation of the parallel sorting algorithms is an integer
///        representing the number of threads to use or is a comparison object
/// @remarks
//---------------------------------------------------------------------------
template<class T>
using enable_if_integral =
      typename std::enable_if< std::is_integral< T >::value >::type;

//
//---------------------------------------------------------------------------
/// @class enable_if_string
/// @brief This is a SFINAE class for to detect if the parameter is a
///        std::string for to apply specialized parameters in the invocation
///        of the block_indirect_sort algorithm
/// @remarks
//---------------------------------------------------------------------------
template<class T>
using enable_if_string =
      typename std::enable_if< std::is_same< T, std::string >::value >::type;

//
//---------------------------------------------------------------------------
/// @class enable_if_not_string
/// @brief This is a SFINAE class for to detect if the parameter is a
///        std::string for to apply specialized parameters in the invocation
///        of the block_indirect_sort algorithm
/// @remarks
//---------------------------------------------------------------------------
template<class T>
using enable_if_not_string =
      typename std::enable_if<! std::is_same< T, std::string >::value >::type;

//
//---------------------------------------------------------------------------
/// @class constructor
/// @brief create a functor with the constructor of a class for to be invoked
///        from a bind or a lambda
/// @remarks
//---------------------------------------------------------------------------
template<class T>
struct constructor
{
    template<class ... Args>
    void operator()(Args && ... args)
    {
        T(std::forward<Args> (args) ...);
    };
};
//
//****************************************************************************
};// End namespace util
};// End namespace common
};// End namespace sort
};// End namespace boost
//****************************************************************************
#endif

/* traits.hpp
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
*/