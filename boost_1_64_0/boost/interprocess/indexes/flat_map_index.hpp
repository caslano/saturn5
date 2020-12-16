//////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztanaga 2005-2012. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/interprocess for documentation.
//
//////////////////////////////////////////////////////////////////////////////
#ifndef BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP
#define BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP

#ifndef BOOST_CONFIG_HPP
#  include <boost/config.hpp>
#endif
#
#if defined(BOOST_HAS_PRAGMA_ONCE)
#  pragma once
#endif

#include <boost/interprocess/detail/config_begin.hpp>
#include <boost/interprocess/detail/workaround.hpp>

// interprocess
#include <boost/interprocess/containers/flat_map.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
// intrusive/detail
#include <boost/intrusive/detail/minimal_pair_header.hpp>         //std::pair
#include <boost/intrusive/detail/minimal_less_equal_header.hpp>   //std::less


//!\file
//!Describes index adaptor of boost::map container, to use it
//!as name/shared memory index

//[flat_map_index
namespace boost { namespace interprocess {

#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Helper class to define typedefs from IndexTraits
template <class MapConfig>
struct flat_map_index_aux
{
   typedef typename MapConfig::key_type            key_type;
   typedef typename MapConfig::mapped_type         mapped_type;
   typedef typename MapConfig::
      segment_manager_base                   segment_manager_base;
   typedef std::less<key_type>                     key_less;
   typedef std::pair<key_type, mapped_type>        value_type;
   typedef allocator<value_type
                    ,segment_manager_base>   allocator_type;
   typedef flat_map<key_type,  mapped_type,
                    key_less, allocator_type>      index_t;
};

#endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

//!Index type based in flat_map. Just derives from flat_map and
//!defines the interface needed by managed memory segments.
template <class MapConfig>
class flat_map_index
   //Derive class from flat_map specialization
   : public flat_map_index_aux<MapConfig>::index_t
{
   #if !defined(BOOST_INTERPROCESS_DOXYGEN_INVOKED)
   typedef flat_map_index_aux<MapConfig>  index_aux;
   typedef typename index_aux::index_t    base_type;
   typedef typename index_aux::
      segment_manager_base          segment_manager_base;
   #endif   //#ifndef BOOST_INTERPROCESS_DOXYGEN_INVOKED

   public:
   //!Constructor. Takes a pointer to the segment manager. Can throw
   flat_map_index(segment_manager_base *segment_mngr)
      : base_type(typename index_aux::key_less(),
                  typename index_aux::allocator_type(segment_mngr))
   {}

   //!This reserves memory to optimize the insertion of n elements in the index
   void reserve(typename segment_manager_base::size_type n)
   {  base_type::reserve(n);  }

   //!This frees all unnecessary memory
   void shrink_to_fit()
   {  base_type::shrink_to_fit();   }
};

}}   //namespace boost { namespace interprocess
//]
#include <boost/interprocess/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTERPROCESS_FLAT_MAP_INDEX_HPP

/* flat_map_index.hpp
2eWjPIQ6y6g2/GIK31kOFa8qz/VV9bVlpYUy23TlUcVN7QFZ7wDPJDucZKASpeatecj5/CDOCnS2lRHkua1syHzsbCsTxfY2TaaV2zQ2s6XJ3nYdH8P3sQs+0CYuC0f8y0JVNbVe2raLZfIq8c9EjQmXZviKjRdm09CTjdGvOcW11n6ptuQd4itHWxKmX9+NC9SGqX6+H8UlVba1VtwuQ16M068Bx7Xdzgl/TxDfZDrNoF0bjgu+nSNeLlfJcqxB8Q8V68EU30uonIVa8c80wsEdC3PlRo6TQsQ4gXhSyE1ICzfdYC7a07VoCyaO4fY0ktrTDuFdPa6I8OjQsPCo0HB3sXtwOAYBoHBuUttqT9+Lk20iRrA87+WwSRPZgzXfWE2bqnQDX4+T/dUYdt/VGff/ivbWN2fKGCcjtZLLxAquY43xfnXsGpx0KymqKW1jjHAnuVmEVdhQXZ2Cn22PCboBnyW+BGd9Yj/09UnVya3Ek4c3sVzO+kN+tF1/YoA3EV8Zxuims/6QP9r6o86OkX0h9d2aOqXcU1pYJ7FGlbVvk30aeCOte3UWcFu9MIj2+t9dxnzt+Gm+ICbdBC9wDPDWOMQ3gcoYtmZ9Pbqhzh/KeYiVl8nE28/8VF+22C/T2qM21TyO4vYi2c92lil2q9/vZf1Ass9FCz/d2u8NNP85RbxdrPlPZHea/9jnrRynUcTrMR8wsq01gWNkNk3t95L7cLbnb47rLdHO+dKMBMmv9j0oay3/55F9AeTM/sm0m12gE7YN/dgwtLuZ45DfE+X+b+hU93T35aJxDe3mLse2QjSa2a7x+GzAj85RNIZQ66YB13ofpnDuEeUjUNi03ntmPOrvBF7v7dh4n2O9l3n2TeD1Xk+NY703jnmawDOd/LnCE+oxnGu+zJeEtM6kMfv6vsLsBNwlwCydzVrqL/ioF+dV/kSek7oan/J0CMdWfOA5aVd20wA32TKNL7ScjybiO8ywzT/p92W+vfjgz3PazneIehHL9UK/R6/0ozInKb3dMNbbLQHvTip/jRUjagun5M29tDBr7oI5WblT8rMyZd9whvR2V5XVlVeXBtCdYT9M/7Vtq/zuIruuznqq3DnOHvnK9j6yH6s/d8R1+WHimYU0qTMlV/ifbQrifISvXRVpjfVLa2f7+SPbfumWyfr8jEq05+esuflZM7Jyg85L6V6flzGJAfMS7lrPy5TEtvMyPtGZlynB5+Xs9uel7E/WTpEebOb3bjbxPmAj56V39Sh5qB2baPa9wNWjDP+2mvhj9GOVRMfeoGjmdXmpeNU6ZprhN2Z8guznYVzUTbintTs/3ksNv7HPr4h3AvGdsfPxfjf3Z8Q3RPVHim8k8XHYfyM+GW4z+HxtTQG3JVFBnGWh9XiZdy33KavYjNLE5y3TfGZnlBnSyG2OMhvhM2tWZoi7bIeGsaxPTpURug1k8lzwRXGmvIdP1mMKS4r99UBw38IqlZ/XEV8XjYzZDyU3/OIxEOddFtmXoPdONjK19cjuRyiVsfraGpj34joymuw3Gm4x2wGNAZWBHONS5Rf3G3IveVF08GeOSCac/q62fRw1TvMAQ0meFE9bvRqVJT0tQUbTeximrFdNKq8D1SuaqfflsmkmUdthpiHfF4NuBj0MOm0M18kB/uvqmqqn/yD7NGf+K7fUTsXGwQxxESd7ZNmaRmUgCvQHilN/IxFmCWxWRWYNRizqxxgQ+EnupB+SJPf9+sIsns2yyOyPxDkZtBS0G20k/KR40t4s8cxHaqOMNJCMg0nhDe0pzzTEURyk2ULibwI9R7zUIlm8LjKLt5m5hXsaWyZY7l8H568of5r86vhiLjvJ/vPQIPQ=
*/