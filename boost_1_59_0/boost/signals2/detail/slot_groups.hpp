// Boost.Signals2 library

// Copyright Frank Mori Hess 2007-2008.
// Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// For more information, see http://www.boost.org

#ifndef BOOST_SIGNALS2_SLOT_GROUPS_HPP
#define BOOST_SIGNALS2_SLOT_GROUPS_HPP

#include <boost/signals2/connection.hpp>
#include <boost/optional.hpp>
#include <list>
#include <map>
#include <utility>

namespace boost {
  namespace signals2 {
    namespace detail {
      enum slot_meta_group {front_ungrouped_slots, grouped_slots, back_ungrouped_slots};
      template<typename Group>
      struct group_key
      {
        typedef std::pair<enum slot_meta_group, boost::optional<Group> > type;
      };
      template<typename Group, typename GroupCompare>
      class group_key_less
      {
      public:
        group_key_less()
        {}
        group_key_less(const GroupCompare &group_compare): _group_compare(group_compare)
        {}
        bool operator ()(const typename group_key<Group>::type &key1, const typename group_key<Group>::type &key2) const
        {
          if(key1.first != key2.first) return key1.first < key2.first;
          if(key1.first != grouped_slots) return false;
          return _group_compare(key1.second.get(), key2.second.get());
        }
      private:
        GroupCompare _group_compare;
      };
      template<typename Group, typename GroupCompare, typename ValueType>
      class grouped_list
      {
      public:
        typedef group_key_less<Group, GroupCompare> group_key_compare_type;
      private:
        typedef std::list<ValueType> list_type;
        typedef std::map
          <
            typename group_key<Group>::type,
            typename list_type::iterator,
            group_key_compare_type
          > map_type;
        typedef typename map_type::iterator map_iterator;
        typedef typename map_type::const_iterator const_map_iterator;
      public:
        typedef typename list_type::iterator iterator;
        typedef typename list_type::const_iterator const_iterator;
        typedef typename group_key<Group>::type group_key_type;

        grouped_list(const group_key_compare_type &group_key_compare):
          _group_key_compare(group_key_compare)
        {}
        grouped_list(const grouped_list &other): _list(other._list),
          _group_map(other._group_map), _group_key_compare(other._group_key_compare)
        {
          // fix up _group_map
          typename map_type::const_iterator other_map_it;
          typename list_type::iterator this_list_it = _list.begin();
          typename map_type::iterator this_map_it = _group_map.begin();
          for(other_map_it = other._group_map.begin();
            other_map_it != other._group_map.end();
            ++other_map_it, ++this_map_it)
          {
            BOOST_ASSERT(this_map_it != _group_map.end());
            this_map_it->second = this_list_it;
            typename list_type::const_iterator other_list_it = other.get_list_iterator(other_map_it);
            typename map_type::const_iterator other_next_map_it = other_map_it;
            ++other_next_map_it;
            typename list_type::const_iterator other_next_list_it = other.get_list_iterator(other_next_map_it);
            while(other_list_it != other_next_list_it)
            {
              ++other_list_it;
              ++this_list_it;
            }
          }
        }
        iterator begin()
        {
          return _list.begin();
        }
        iterator end()
        {
          return _list.end();
        }
        iterator lower_bound(const group_key_type &key)
        {
          map_iterator map_it = _group_map.lower_bound(key);
          return get_list_iterator(map_it);
        }
        iterator upper_bound(const group_key_type &key)
        {
          map_iterator map_it = _group_map.upper_bound(key);
          return get_list_iterator(map_it);
        }
        void push_front(const group_key_type &key, const ValueType &value)
        {
          map_iterator map_it;
          if(key.first == front_ungrouped_slots)
          {// optimization
            map_it = _group_map.begin();
          }else
          {
            map_it = _group_map.lower_bound(key);
          }
          m_insert(map_it, key, value);
        }
        void push_back(const group_key_type &key, const ValueType &value)
        {
          map_iterator map_it;
          if(key.first == back_ungrouped_slots)
          {// optimization
            map_it = _group_map.end();
          }else
          {
            map_it = _group_map.upper_bound(key);
          }
          m_insert(map_it, key, value);
        }
        void erase(const group_key_type &key)
        {
          map_iterator map_it = _group_map.lower_bound(key);
          iterator begin_list_it = get_list_iterator(map_it);
          iterator end_list_it = upper_bound(key);
          if(begin_list_it != end_list_it)
          {
            _list.erase(begin_list_it, end_list_it);
            _group_map.erase(map_it);
          }
        }
        iterator erase(const group_key_type &key, const iterator &it)
        {
          BOOST_ASSERT(it != _list.end());
          map_iterator map_it = _group_map.lower_bound(key);
          BOOST_ASSERT(map_it != _group_map.end());
          BOOST_ASSERT(weakly_equivalent(map_it->first, key));
          if(map_it->second == it)
          {
            iterator next = it;
            ++next;
            // if next is in same group
            if(next != upper_bound(key))
            {
              _group_map[key] = next;
            }else
            {
              _group_map.erase(map_it);
            }
          }
          return _list.erase(it);
        }
        void clear()
        {
          _list.clear();
          _group_map.clear();
        }
      private:
        /* Suppress default assignment operator, since it has the wrong semantics. */
        grouped_list& operator=(const grouped_list &other);

        bool weakly_equivalent(const group_key_type &arg1, const group_key_type &arg2)
        {
          if(_group_key_compare(arg1, arg2)) return false;
          if(_group_key_compare(arg2, arg1)) return false;
          return true;
        }
        void m_insert(const map_iterator &map_it, const group_key_type &key, const ValueType &value)
        {
          iterator list_it = get_list_iterator(map_it);
          iterator new_it = _list.insert(list_it, value);
          if(map_it != _group_map.end() && weakly_equivalent(key, map_it->first))
          {
            _group_map.erase(map_it);
          }
          map_iterator lower_bound_it = _group_map.lower_bound(key);
          if(lower_bound_it == _group_map.end() ||
            weakly_equivalent(lower_bound_it->first, key) == false)
          {
            /* doing the following instead of just
              _group_map[key] = new_it;
              to avoid bogus error when enabling checked iterators with g++ */
            _group_map.insert(typename map_type::value_type(key, new_it));
          }
        }
        iterator get_list_iterator(const const_map_iterator &map_it)
        {
          iterator list_it;
          if(map_it == _group_map.end())
          {
            list_it = _list.end();
          }else
          {
            list_it = map_it->second;
          }
          return list_it;
        }
        const_iterator get_list_iterator(const const_map_iterator &map_it) const
        {
          const_iterator list_it;
          if(map_it == _group_map.end())
          {
            list_it = _list.end();
          }else
          {
            list_it = map_it->second;
          }
          return list_it;
        }

        list_type _list;
        // holds iterators to first list item in each group
        map_type _group_map;
        group_key_compare_type _group_key_compare;
      };
    } // end namespace detail
    enum connect_position { at_back, at_front };
  } // end namespace signals2
} // end namespace boost

#endif // BOOST_SIGNALS2_SLOT_GROUPS_HPP

/* slot_groups.hpp
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
*/