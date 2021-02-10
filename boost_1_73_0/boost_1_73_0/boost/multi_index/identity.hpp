/* Copyright 2003-2015 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_IDENTITY_HPP
#define BOOST_MULTI_INDEX_IDENTITY_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/mpl/if.hpp>
#include <boost/multi_index/identity_fwd.hpp>
#include <boost/type_traits/is_const.hpp>
#include <boost/type_traits/remove_const.hpp>
#include <boost/utility/enable_if.hpp>

#if !defined(BOOST_NO_SFINAE)
#include <boost/type_traits/is_convertible.hpp>
#endif

namespace boost{

template<class Type> class reference_wrapper; /* fwd decl. */

namespace multi_index{

namespace detail{

/* identity is a do-nothing key extractor that returns the [const] Type&
 * object passed.
 * Additionally, identity is overloaded to support referece_wrappers
 * of Type and "chained pointers" to Type's. By chained pointer to Type we
 * mean a  type  P such that, given a p of type P
 *   *...n...*x is convertible to Type&, for some n>=1.
 * Examples of chained pointers are raw and smart pointers, iterators and
 * arbitrary combinations of these (vg. Type** or unique_ptr<Type*>.)
 */

template<typename Type>
struct const_identity_base
{
  typedef Type result_type;

  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<is_convertible<const ChainedPtr&,Type&>,Type&>::type
#else
  Type&
#endif 
  
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(
    const reference_wrapper<typename remove_const<Type>::type>& x

#if BOOST_WORKAROUND(BOOST_MSVC,==1310)
/* http://lists.boost.org/Archives/boost/2015/10/226135.php */
    ,int=0
#endif

  )const
  { 
    return x.get();
  }
};

template<typename Type>
struct non_const_identity_base
{
  typedef Type result_type;

  /* templatized for pointer-like types */
  
  template<typename ChainedPtr>

#if !defined(BOOST_NO_SFINAE)
  typename disable_if<
    is_convertible<const ChainedPtr&,const Type&>,Type&>::type
#else
  Type&
#endif 
    
  operator()(const ChainedPtr& x)const
  {
    return operator()(*x);
  }

  const Type& operator()(const Type& x)const
  {
    return x;
  }

  Type& operator()(Type& x)const
  {
    return x;
  }

  const Type& operator()(const reference_wrapper<const Type>& x)const
  { 
    return x.get();
  }

  Type& operator()(const reference_wrapper<Type>& x)const
  { 
    return x.get();
  }
};

} /* namespace multi_index::detail */

template<class Type>
struct identity:
  mpl::if_c<
    is_const<Type>::value,
    detail::const_identity_base<Type>,detail::non_const_identity_base<Type>
  >::type
{
};

} /* namespace multi_index */

} /* namespace boost */

#endif

/* identity.hpp
AbGIpAYxRW7ETrjSiLfUXORNFM1AMzlXCEHCo0wJiB4jnkUTFBNpSLVeqA+tVryUGWreSkSsWnG19Waq5+Uu7lGDefQCYqFBC1gqVgeiq8NcJHxKbzQFTi6Wk4yrtL5WBQXlSUtIUCzLEArZOFOFygz80jJ1ooIFass1vZTIFUl6SsV8ixBNiCDTpcxRDJoAaRKBBq7DMk+YNLRm05WE0prGtEdcstY1AZGjJnBm++D5ZzCJFFd1+OIFt4NxAF/s0cjuB/cw+Ax2/x6x7ry+g/7mKEkCe15IplCyBD5fZJwlRuDf91j2OBj07Ds3HAwDb9D34RNMhWR8lkMulE54Hluolb9gMXoFxBI1yeNsmTAMFJ0qQDVLW6PV0NSSZZHGWCI7vj3XYhEqGSdc1ogGkYq5yZJnCc3WiQ7Dd4mG0ylGEO5bVdgmXGHCMpHPiI6sn/GJjOQLIk0Yx2mMNMlynb0AYWqjiWaKLE/OUCySMbl1wmhfmxCrbJibtFwIpfgEcaJMsihBPHRlrnSUZet0Ui+IPC+8vrW7VmUV9D4KIhmUA/9Q6EOMnjzKVnajuFH7lmghyz73jOVMRrQbnDNpFcYin/JZMzVAe3oQyjbEilExvVwgH5lImPg6mwgpxRNLzo5qhUZUlVo8b2jJ
*/