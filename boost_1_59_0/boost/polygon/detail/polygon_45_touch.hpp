/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_45_TOUCH_HPP
#define BOOST_POLYGON_POLYGON_45_TOUCH_HPP
namespace boost { namespace polygon{

  template <typename Unit>
  struct polygon_45_touch {

    typedef point_data<Unit> Point;
    typedef typename coordinate_traits<Unit>::manhattan_area_type LongUnit;

    template <typename property_map>
    static inline void merge_property_maps(property_map& mp, const property_map& mp2, bool subtract = false) {
      property_map newmp;
      newmp.reserve(mp.size() + mp2.size());
      std::size_t i = 0;
      std::size_t j = 0;
      while(i != mp.size() && j != mp2.size()) {
        if(mp[i].first < mp2[j].first) {
          newmp.push_back(mp[i]);
          ++i;
        } else if(mp[i].first > mp2[j].first) {
          newmp.push_back(mp2[j]);
          if(subtract) newmp.back().second *= -1;
          ++j;
        } else {
          int count = mp[i].second;
          if(subtract) count -= mp2[j].second;
          else count += mp2[j].second;
          if(count) {
            newmp.push_back(mp[i]);
            newmp.back().second = count;
          }
          ++i;
          ++j;
        }
      }
      while(i != mp.size()) {
        newmp.push_back(mp[i]);
        ++i;
      }
      while(j != mp2.size()) {
        newmp.push_back(mp2[j]);
        if(subtract) newmp.back().second *= -1;
        ++j;
      }
      mp.swap(newmp);
    }

    class CountTouch {
    public:
      inline CountTouch() : counts() {}
      //inline CountTouch(int count) { counts[0] = counts[1] = count; }
      //inline CountTouch(int count1, int count2) { counts[0] = count1; counts[1] = count2; }
      inline CountTouch(const CountTouch& count) : counts(count.counts) {}
      inline bool operator==(const CountTouch& count) const { return counts == count.counts; }
      inline bool operator!=(const CountTouch& count) const { return !((*this) == count); }
      //inline CountTouch& operator=(int count) { counts[0] = counts[1] = count; return *this; }
      inline CountTouch& operator=(const CountTouch& count) { counts = count.counts; return *this; }
      inline int& operator[](int index) {
        std::vector<std::pair<int, int> >::iterator itr =
            std::lower_bound(counts.begin(), counts.end(),
                             std::make_pair(index, int(0)));
        if(itr != counts.end() && itr->first == index) {
            return itr->second;
        }
        itr = counts.insert(itr, std::make_pair(index, int(0)));
        return itr->second;
      }
//       inline int operator[](int index) const {
//         std::vector<std::pair<int, int> >::const_iterator itr = counts.begin();
//         for( ; itr != counts.end() && itr->first <= index; ++itr) {
//           if(itr->first == index) {
//             return itr->second;
//           }
//         }
//         return 0;
//       }
      inline CountTouch& operator+=(const CountTouch& count){
        merge_property_maps(counts, count.counts, false);
        return *this;
      }
      inline CountTouch& operator-=(const CountTouch& count){
        merge_property_maps(counts, count.counts, true);
        return *this;
      }
      inline CountTouch operator+(const CountTouch& count) const {
        return CountTouch(*this)+=count;
      }
      inline CountTouch operator-(const CountTouch& count) const {
        return CountTouch(*this)-=count;
      }
      inline CountTouch invert() const {
        CountTouch retval;
        retval -= *this;
        return retval;
      }
      std::vector<std::pair<int, int> > counts;
    };

    typedef std::pair<std::pair<Unit, std::map<Unit, std::set<int> > >, std::map<int, std::set<int> > > map_graph_o;
    typedef std::pair<std::pair<Unit, std::map<Unit, std::set<int> > >, std::vector<std::set<int> > > vector_graph_o;

    template <typename cT>
    static void process_previous_x(cT& output) {
      std::map<Unit, std::set<int> >& y_prop_map = output.first.second;
      for(typename std::map<Unit, std::set<int> >::iterator itr = y_prop_map.begin();
          itr != y_prop_map.end(); ++itr) {
        for(std::set<int>::iterator inner_itr = itr->second.begin();
            inner_itr != itr->second.end(); ++inner_itr) {
          std::set<int>& output_edges = (*(output.second))[*inner_itr];
          std::set<int>::iterator inner_inner_itr = inner_itr;
          ++inner_inner_itr;
          for( ; inner_inner_itr != itr->second.end(); ++inner_inner_itr) {
            output_edges.insert(output_edges.end(), *inner_inner_itr);
            std::set<int>& output_edges_2 = (*(output.second))[*inner_inner_itr];
            output_edges_2.insert(output_edges_2.end(), *inner_itr);
          }
        }
      }
      y_prop_map.clear();
    }

    struct touch_45_output_functor {
      template <typename cT>
      void operator()(cT& output, const CountTouch& count1, const CountTouch& count2,
                      const Point& pt, int , direction_1d ) {
        Unit& x = output.first.first;
        std::map<Unit, std::set<int> >& y_prop_map = output.first.second;
        if(pt.x() != x) process_previous_x(output);
        x = pt.x();
        std::set<int>& output_set = y_prop_map[pt.y()];
        for(std::vector<std::pair<int, int> >::const_iterator itr1 = count1.counts.begin();
            itr1 != count1.counts.end(); ++itr1) {
          if(itr1->second > 0) {
            output_set.insert(output_set.end(), itr1->first);
          }
        }
        for(std::vector<std::pair<int, int> >::const_iterator itr2 = count2.counts.begin();
            itr2 != count2.counts.end(); ++itr2) {
          if(itr2->second > 0) {
            output_set.insert(output_set.end(), itr2->first);
          }
        }
      }
    };
    typedef typename std::pair<Point,
                               typename boolean_op_45<Unit>::template Scan45CountT<CountTouch> > Vertex45Compact;
    typedef std::vector<Vertex45Compact> TouchSetData;

    struct lessVertex45Compact {
      bool operator()(const Vertex45Compact& l, const Vertex45Compact& r) {
        return l.first < r.first;
      }
    };

//     template <typename TSD>
//     static void print_tsd(TSD& tsd) {
//       for(std::size_t i = 0; i < tsd.size(); ++i) {
//         std::cout << tsd[i].first << ": ";
//         for(unsigned int r = 0; r < 4; ++r) {
//           std::cout << r << " { ";
//           for(std::vector<std::pair<int, int> >::iterator itr = tsd[i].second[r].counts.begin();
//               itr != tsd[i].second[r].counts.end(); ++itr) {
//             std::cout << itr->first << "," << itr->second << " ";
//           } std::cout << "} ";
//         }
//       } std::cout << std::endl;
//     }

//     template <typename T>
//     static void print_scanline(T& t) {
//       for(typename T::iterator itr = t.begin(); itr != t.end(); ++itr) {
//         std::cout << itr->x << "," << itr->y << " " << itr->rise << " ";
//         for(std::vector<std::pair<int, int> >::iterator itr2 = itr->count.counts.begin();
//             itr2 != itr->count.counts.end(); ++itr2) {
//           std::cout << itr2->first << ":" << itr2->second << " ";
//         } std::cout << std::endl;
//       }
//     }

    template <typename graph_type>
    static void performTouch(graph_type& graph, TouchSetData& tsd) {

      polygon_sort(tsd.begin(), tsd.end(), lessVertex45Compact());
      typedef std::vector<std::pair<Point, typename boolean_op_45<Unit>::template Scan45CountT<CountTouch> > > TSD;
      TSD tsd_;
      tsd_.reserve(tsd.size());
      for(typename TouchSetData::iterator itr = tsd.begin(); itr != tsd.end(); ) {
        typename TouchSetData::iterator itr2 = itr;
        ++itr2;
        for(; itr2 != tsd.end() && itr2->first == itr->first; ++itr2) {
          (itr->second) += (itr2->second); //accumulate
        }
        tsd_.push_back(std::make_pair(itr->first, itr->second));
        itr = itr2;
      }
      std::pair<std::pair<Unit, std::map<Unit, std::set<int> > >, graph_type*> output
        (std::make_pair(std::make_pair((std::numeric_limits<Unit>::max)(), std::map<Unit, std::set<int> >()), &graph));
      typename boolean_op_45<Unit>::template Scan45<CountTouch, touch_45_output_functor> scanline;
      for(typename TSD::iterator itr = tsd_.begin(); itr != tsd_.end(); ) {
        typename TSD::iterator itr2 = itr;
        ++itr2;
        while(itr2 != tsd_.end() && itr2->first.x() == itr->first.x()) {
          ++itr2;
        }
        scanline.scan(output, itr, itr2);
        itr = itr2;
      }
      process_previous_x(output);
    }

    template <typename iT>
    static void populateTouchSetData(TouchSetData& tsd, iT begin, iT end, int nodeCount) {
      for( ; begin != end; ++begin) {
        Vertex45Compact vertex;
        vertex.first = typename Vertex45Compact::first_type(begin->pt.x() * 2, begin->pt.y() * 2);
        tsd.push_back(vertex);
        for(unsigned int i = 0; i < 4; ++i) {
          if(begin->count[i]) {
            tsd.back().second[i][nodeCount] += begin->count[i];
          }
        }
      }
    }

  };


}
}
#endif

/* polygon_45_touch.hpp
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
*/