/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga  2014-2014
//
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP
#define BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif

#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <cstddef>
#include <boost/intrusive/detail/std_fwd.hpp>
#include <boost/intrusive/detail/workaround.hpp>
#include <boost/move/detail/iterator_traits.hpp>
#include <boost/move/detail/meta_utils_core.hpp>

namespace boost{
namespace iterators{

struct incrementable_traversal_tag;
struct single_pass_traversal_tag;
struct forward_traversal_tag;
struct bidirectional_traversal_tag;
struct random_access_traversal_tag;

namespace detail{

template <class Category, class Traversal>
struct iterator_category_with_traversal;

} //namespace boost{
} //namespace iterators{
} //namespace detail{

namespace boost {
namespace intrusive {

using boost::movelib::iterator_traits;

////////////////////
//    iterator
////////////////////
template<class Category, class T, class Difference, class Pointer, class Reference>
struct iterator
{
   typedef Category     iterator_category;
   typedef T            value_type;
   typedef Difference   difference_type;
   typedef Pointer      pointer;
   typedef Reference    reference;
};

////////////////////////////////////////
//    iterator_[dis|en]able_if_boost_iterator
////////////////////////////////////////
template<class I>
struct is_boost_iterator
{
   static const bool value = false;
};

template<class Category, class Traversal>
struct is_boost_iterator< boost::iterators::detail::iterator_category_with_traversal<Category, Traversal> >
{
   static const bool value = true;
};

template<class I, class R = void>
struct iterator_enable_if_boost_iterator
   : ::boost::move_detail::enable_if_c
      < is_boost_iterator<typename boost::intrusive::iterator_traits<I>::iterator_category >::value
      , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag
////////////////////////////////////////
template<class I, class Tag, class R = void>
struct iterator_enable_if_tag
   : ::boost::move_detail::enable_if_c
      < ::boost::move_detail::is_same
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value
         , R>
{};

template<class I, class Tag, class R = void>
struct iterator_disable_if_tag
   : ::boost::move_detail::enable_if_c
      < !::boost::move_detail::is_same
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value
         , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag
////////////////////////////////////////
template<class I, class Tag, class Tag2, class R = void>
struct iterator_enable_if_convertible_tag
   : ::boost::move_detail::enable_if_c
      < ::boost::move_detail::is_same_or_convertible
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag
         >::value &&
        !::boost::move_detail::is_same_or_convertible
         < typename boost::intrusive::iterator_traits<I>::iterator_category 
         , Tag2
         >::value
         , R>
{};

////////////////////////////////////////
//    iterator_[dis|en]able_if_tag_difference_type
////////////////////////////////////////
template<class I, class Tag>
struct iterator_enable_if_tag_difference_type
   : iterator_enable_if_tag<I, Tag, typename boost::intrusive::iterator_traits<I>::difference_type>
{};

template<class I, class Tag>
struct iterator_disable_if_tag_difference_type
   : iterator_disable_if_tag<I, Tag, typename boost::intrusive::iterator_traits<I>::difference_type>
{};

////////////////////
//    advance
////////////////////

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::input_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
typename iterator_enable_if_tag<InputIt, std::forward_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::bidirectional_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   for (; 0 < n; --n)
      ++it;
   for (; n < 0; ++n)
      --it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag<InputIt, std::random_access_iterator_tag>::type
   iterator_advance(InputIt& it, Distance n)
{
   it += n;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::incrementable_traversal_tag&, const boost::iterators::single_pass_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::single_pass_traversal_tag &, const boost::iterators::forward_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::forward_traversal_tag&, const boost::iterators::bidirectional_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   while(n--)
      ++it;
}

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::bidirectional_traversal_tag&, const boost::iterators::random_access_traversal_tag&>::type
   iterator_advance(InputIt& it, Distance n)
{
   for (; 0 < n; --n)
      ++it;
   for (; n < 0; ++n)
      --it;
}

class fake{};

template<class InputIt, class Distance>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_convertible_tag
   <InputIt, const boost::iterators::random_access_traversal_tag&, const fake&>::type
   iterator_advance(InputIt& it, Distance n)
{
   it += n;
}

////////////////////
//    distance
////////////////////
template<class InputIt> inline
typename iterator_disable_if_tag_difference_type
   <InputIt, std::random_access_iterator_tag>::type
      iterator_distance(InputIt first, InputIt last)
{
   typename iterator_traits<InputIt>::difference_type off = 0;
   while(first != last){
      ++off;
      ++first;
   }
   return off;
}

template<class InputIt>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_enable_if_tag_difference_type
   <InputIt, std::random_access_iterator_tag>::type
      iterator_distance(InputIt first, InputIt last)
{
   typename iterator_traits<InputIt>::difference_type off = last - first;
   return off;
}

template<class I>
BOOST_INTRUSIVE_FORCEINLINE typename iterator_traits<I>::pointer iterator_arrow_result(const I &i)
{  return i.operator->();  }

template<class T>
BOOST_INTRUSIVE_FORCEINLINE T * iterator_arrow_result(T *p)
{  return p;   }

} //namespace intrusive
} //namespace boost

#endif //BOOST_INTRUSIVE_DETAIL_ITERATOR_HPP

/* iterator.hpp
jJ/+PdMsPJ9xZB/Uk6nvKeE1wsGWR3WFMGXk2osltNspkfu/5XHrGmGVMQE+XSP8J9saYR2bGYvb6MeynhpKwsexMz49B9qncYDp22PRtRz18TlZyiY6JfIK/TSG7mj5imz+RfocuK7OPu4XnOrI7yYdL2+ErvfG/Xr7WBMuaZLjfn3CccXXrWbhWe70598Zdv8P5CR3b8aMOaSz3pu+3q+V62WYT4K2MYb0Hd+vseMIaRLfr8YartXCV8V6ioB1XFE5+oyKv4d3yvUh6svWpv9rLM+frCSeoYn0foDqfXt6mm3R09x29LTAqqfRepk2KVzgFrV1XgVd633zX2bXS32mJ3wGHiPpqtjfLGjTVeR27hlYfNm+6STpbDpp0z94O69/xZd1/LyI0TXSJPLptD/H4Lf7dNqfYfAn8um0Pr/gb//59ZBcD/rPnjUS7q1hZhslHDCfZb4//rR/s3cm8FEVZwDfTRbIBYSQhIgiIRwCcoRLQFGDnHIGiBIQTUISIRJIJIEGRQ0VKypSrFpR0cYbFRUrtaioaQtKW2zRYqUWaVS80aLFq6Xa//v2ey+zu2+TDWCPXxMd/jvzvvnmePPmHTPzjRybw5UTJfeqE+j/dozTe1Uv51Yl96pVhG/D+e9V/d3tWaiOg+Pse1WedasKuVfpddrg/Snmf+Q61fmnrvNV08PMV+3mMl/VfG4vneCRv8n2t1nc89acOP/1Xs7VXelfluUx1g1x1YdbY2S0oSX23rCu17Ij6/rtMAnuk+Mnu17PZtyxxPUYcy3q1DZ2egTfAvx1Q3mMd8Il9r6sGpYQ+u4oaZBugI3mVoudb2ABfepereMWOJtXI5Mp8tUVC6zvuDNypp89ZZx8rV60pLQUEaPdN/RdJ31C8D5IKyeGpvcT0stySY+3VqnDO6T+KxaEnUu6OPBb08EI8mTXsaU7RXWb9bJ8Umg+b0U22yWfbN6iM6f97bBvI/lFh9P3XSHvmlbsC5csKnRviypvzKOOvHx9tXxmP0GahDlpBuyzMX9yaLmvQUe+W7kZeI20zPkh+6iUV7qODxuyTn/ZhPPplDf4O4qmZ5Y1Z0poWe8ifrlLWZcWlC7hBEfUHssXR/5NVWXrv8s3oaxG2w07r/EQzIoKb4vc3dZ5OJvdTbddPvFHVviy7z34xx+d+NItH+3/8oM2y5+6+djt5+xuCz6cTfljZ3Pc3SZ7eBvr7rbvw9usd7fJHt6Wvbut/GNnw/0LXafPn4wTyfQKZF82fu80fr9k/P59/W95pqrS/e9+o7/n4nbob8vt1t+dyOOz+vsVtc+ebdvtg5tVvhVutOZtIheuF06CGXAK7Kb+y9R/ufqfUL/qxX5beL1DVO8pqneY6sWPXvyqFz968aveTNu+Feylek37y39XO8r/gD3VXrcd76DGO8kl3i813q9gD/iCs1e32vKBbTWeuVf3973+eFdCH1wJ28AfGPnNyguf332a7l80v295DLvmGi/TS7wgu+YF6O8Mi2A/WAxPhfNgLpwPF8IS+D1YqvW5EK6AV8C1cBG8C5bB+2A5fA5WwD/CSvg6XArfhd+Dn8Iq+DlcBr3k7xKYAJfDNHiFlr9cMqt7i2n543FFWo7+av89E3aAA+HxcBAcBAfDoXCI2pU/BebBoXAuPA0Wqp3/C9VvpbsFV63pXqbpJuM2arqH9Lx9DmPULn86/BJ2hXHo6ab2+QfCGPwTYCycrMenQB/MUf85asc/X+34z4PfwFLdT6AMeOHFKr9Ywy/R8OUSbrS7uf78D3Bpd6O03kbDVDgWZsJxGj/fchp/lsY39w+YJuXHD+PgObATPBd2gTPhcJgLR8Dz4enwPG1f+J0=
*/