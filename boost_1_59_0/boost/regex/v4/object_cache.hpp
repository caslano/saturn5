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
#include <boost/shared_ptr.hpp>
#include <map>
#include <list>
#include <stdexcept>
#include <string>
#ifdef BOOST_HAS_THREADS
#include <boost/regex/pending/static_mutex.hpp>
#endif

namespace boost{

template <class Key, class Object>
class object_cache
{
public:
   typedef std::pair< ::boost::shared_ptr<Object const>, Key const*> value_type;
   typedef std::list<value_type> list_type;
   typedef typename list_type::iterator list_iterator;
   typedef std::map<Key, list_iterator> map_type;
   typedef typename map_type::iterator map_iterator;
   typedef typename list_type::size_type size_type;
   static boost::shared_ptr<Object const> get(const Key& k, size_type l_max_cache_size);

private:
   static boost::shared_ptr<Object const> do_get(const Key& k, size_type l_max_cache_size);

   struct data
   {
      list_type   cont;
      map_type    index;
   };

   // Needed by compilers not implementing the resolution to DR45. For reference,
   // see http://www.open-std.org/JTC1/SC22/WG21/docs/cwg_defects.html#45.
   friend struct data;
};

#ifdef BOOST_MSVC
#pragma warning(push)
#pragma warning(disable: 4702)
#endif
template <class Key, class Object>
boost::shared_ptr<Object const> object_cache<Key, Object>::get(const Key& k, size_type l_max_cache_size)
{
#ifdef BOOST_HAS_THREADS
   static boost::static_mutex mut = BOOST_STATIC_MUTEX_INIT;
   boost::static_mutex::scoped_lock l(mut);
   if (l)
   {
      return do_get(k, l_max_cache_size);
   }
   //
   // what do we do if the lock fails?
   // for now just throw, but we should never really get here...
   //
   ::boost::throw_exception(std::runtime_error("Error in thread safety code: could not acquire a lock"));
#if defined(BOOST_NO_UNREACHABLE_RETURN_DETECTION) || defined(BOOST_NO_EXCEPTIONS)
   return boost::shared_ptr<Object>();
#endif
#else
   return do_get(k, l_max_cache_size);
#endif
}
#ifdef BOOST_MSVC
#pragma warning(pop)
#endif

template <class Key, class Object>
boost::shared_ptr<Object const> object_cache<Key, Object>::do_get(const Key& k, size_type l_max_cache_size)
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
   boost::shared_ptr<Object const> result(new Object(k));
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
         if(pos->first.unique())
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