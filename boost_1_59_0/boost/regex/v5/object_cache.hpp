/*
 *
 * Copyright (c) 2004
 * John Maddock
 *
 * Use, modification and distribution are subject to the 
 * Boost Software License, Version 1.0. (See accompanying file 
 * LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 */

 /*
  *   LOCATION:    see http://www.boost.org for most recent version.
  *   FILE         object_cache.hpp
  *   VERSION      see <boost/version.hpp>
  *   DESCRIPTION: Implements a generic object cache.
  */

#ifndef BOOST_REGEX_OBJECT_CACHE_HPP
#define BOOST_REGEX_OBJECT_CACHE_HPP

#include <boost/regex/config.hpp>
#include <memory>
#include <map>
#include <list>
#include <stdexcept>
#include <string>
#ifdef BOOST_HAS_THREADS
#include <mutex>
#endif

namespace boost{

template <class Key, class Object>
class object_cache
{
public:
   typedef std::pair< ::std::shared_ptr<Object const>, Key const*> value_type;
   typedef std::list<value_type> list_type;
   typedef typename list_type::iterator list_iterator;
   typedef std::map<Key, list_iterator> map_type;
   typedef typename map_type::iterator map_iterator;
   typedef typename list_type::size_type size_type;
   static std::shared_ptr<Object const> get(const Key& k, size_type l_max_cache_size);

private:
   static std::shared_ptr<Object const> do_get(const Key& k, size_type l_max_cache_size);

   struct data
   {
      list_type   cont;
      map_type    index;
   };

   // Needed by compilers not implementing the resolution to DR45. For reference,
   // see http://www.open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#45.
   friend struct data;
};

#ifdef BOOST_REGEX_MSVC
#pragma warning(push)
#pragma warning(disable: 4702)
#endif
template <class Key, class Object>
std::shared_ptr<Object const> object_cache<Key, Object>::get(const Key& k, size_type l_max_cache_size)
{
#ifdef BOOST_HAS_THREADS
   static std::mutex mut;
   std::lock_guard<std::mutex> l(mut);
   return do_get(k, l_max_cache_size);
#else
   return do_get(k, l_max_cache_size);
#endif
}
#ifdef BOOST_REGEX_MSVC
#pragma warning(pop)
#endif

template <class Key, class Object>
std::shared_ptr<Object const> object_cache<Key, Object>::do_get(const Key& k, size_type l_max_cache_size)
{
   typedef typename object_cache<Key, Object>::data object_data;
   typedef typename map_type::size_type map_size_type;
   static object_data s_data;

   //
   // see if the object is already in the cache:
   //
   map_iterator mpos = s_data.index.find(k);
   if(mpos != s_data.index.end())
   {
      //
      // Eureka! 
      // We have a cached item, bump it up the list and return it:
      //
      if(--(s_data.cont.end()) != mpos->second)
      {
         // splice out the item we want to move:
         list_type temp;
         temp.splice(temp.end(), s_data.cont, mpos->second);
         // and now place it at the end of the list:
         s_data.cont.splice(s_data.cont.end(), temp, temp.begin());
         BOOST_REGEX_ASSERT(*(s_data.cont.back().second) == k);
         // update index with new position:
         mpos->second = --(s_data.cont.end());
         BOOST_REGEX_ASSERT(&(mpos->first) == mpos->second->second);
         BOOST_REGEX_ASSERT(&(mpos->first) == s_data.cont.back().second);
      }
      return s_data.cont.back().first;
   }
   //
   // if we get here then the item is not in the cache,
   // so create it:
   //
   std::shared_ptr<Object const> result(new Object(k));
   //
   // Add it to the list, and index it:
   //
   s_data.cont.push_back(value_type(result, static_cast<Key const*>(0)));
   s_data.index.insert(std::make_pair(k, --(s_data.cont.end())));
   s_data.cont.back().second = &(s_data.index.find(k)->first);
   map_size_type s = s_data.index.size();
   BOOST_REGEX_ASSERT(s_data.index[k]->first.get() == result.get());
   BOOST_REGEX_ASSERT(&(s_data.index.find(k)->first) == s_data.cont.back().second);
   BOOST_REGEX_ASSERT(s_data.index.find(k)->first == k);
   if(s > l_max_cache_size)
   {
      //
      // We have too many items in the list, so we need to start
      // popping them off the back of the list, but only if they're
      // being held uniquely by us:
      //
      list_iterator pos = s_data.cont.begin();
      list_iterator last = s_data.cont.end();
      while((pos != last) && (s > l_max_cache_size))
      {
         if(pos->first.use_count() == 1)
         {
            list_iterator condemmed(pos);
            ++pos;
            // now remove the items from our containers, 
            // then order has to be as follows:
            BOOST_REGEX_ASSERT(s_data.index.find(*(condemmed->second)) != s_data.index.end());
            s_data.index.erase(*(condemmed->second));
            s_data.cont.erase(condemmed); 
            --s;
         }
         else
            ++pos;
      }
      BOOST_REGEX_ASSERT(s_data.index[k]->first.get() == result.get());
      BOOST_REGEX_ASSERT(&(s_data.index.find(k)->first) == s_data.cont.back().second);
      BOOST_REGEX_ASSERT(s_data.index.find(k)->first == k);
   }
   return result;
}

}

#endif

/* object_cache.hpp
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
*/