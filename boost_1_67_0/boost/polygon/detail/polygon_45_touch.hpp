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