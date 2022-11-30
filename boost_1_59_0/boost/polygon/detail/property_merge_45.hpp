/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_PROPERTY_MERGE_45_HPP
#define BOOST_POLYGON_PROPERTY_MERGE_45_HPP
namespace boost { namespace polygon{

  template <typename Unit, typename property_type>
  struct polygon_45_property_merge {

    typedef point_data<Unit> Point;
    typedef typename coordinate_traits<Unit>::manhattan_area_type LongUnit;

    template <typename property_map>
    static inline void merge_property_maps(property_map& mp, const property_map& mp2, bool subtract = false) {
      polygon_45_touch<Unit>::merge_property_maps(mp, mp2, subtract);
    }

    class CountMerge {
    public:
      inline CountMerge() : counts() {}
      //inline CountMerge(int count) { counts[0] = counts[1] = count; }
      //inline CountMerge(int count1, int count2) { counts[0] = count1; counts[1] = count2; }
      inline CountMerge(const CountMerge& count) : counts(count.counts) {}
      inline bool operator==(const CountMerge& count) const { return counts == count.counts; }
      inline bool operator!=(const CountMerge& count) const { return !((*this) == count); }
      //inline CountMerge& operator=(int count) { counts[0] = counts[1] = count; return *this; }
      inline CountMerge& operator=(const CountMerge& count) { counts = count.counts; return *this; }
      inline int& operator[](property_type index) {
        std::vector<std::pair<int, int> >::iterator itr = lower_bound(counts.begin(), counts.end(), std::make_pair(index, int(0)));
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
      inline CountMerge& operator+=(const CountMerge& count){
        merge_property_maps(counts, count.counts, false);
        return *this;
      }
      inline CountMerge& operator-=(const CountMerge& count){
        merge_property_maps(counts, count.counts, true);
        return *this;
      }
      inline CountMerge operator+(const CountMerge& count) const {
        return CountMerge(*this)+=count;
      }
      inline CountMerge operator-(const CountMerge& count) const {
        return CountMerge(*this)-=count;
      }
      inline CountMerge invert() const {
        CountMerge retval;
        retval -= *this;
        return retval;
      }
      std::vector<std::pair<property_type, int> > counts;
    };

    //output is a std::map<std::set<property_type>, polygon_45_set_data<Unit> >
    struct merge_45_output_functor {
      template <typename cT>
      void operator()(cT& output, const CountMerge& count1, const CountMerge& count2,
                      const Point& pt, int rise, direction_1d end) {
        typedef typename cT::key_type keytype;
        keytype left;
        keytype right;
        int edgeType = end == LOW ? -1 : 1;
        for(typename std::vector<std::pair<property_type, int> >::const_iterator itr = count1.counts.begin();
            itr != count1.counts.end(); ++itr) {
          left.insert(left.end(), (*itr).first);
        }
        for(typename std::vector<std::pair<property_type, int> >::const_iterator itr = count2.counts.begin();
            itr != count2.counts.end(); ++itr) {
          right.insert(right.end(), (*itr).first);
        }
        if(left == right) return;
        if(!left.empty()) {
          //std::cout << pt.x() << " " << pt.y() << " " << rise << " " << edgeType << std::endl;
          output[left].insert_clean(typename boolean_op_45<Unit>::Vertex45(pt, rise, -edgeType));
        }
        if(!right.empty()) {
          //std::cout << pt.x() << " " << pt.y() << " " << rise << " " << -edgeType << std::endl;
          output[right].insert_clean(typename boolean_op_45<Unit>::Vertex45(pt, rise, edgeType));
        }
      }
    };

    typedef typename std::pair<Point,
                               typename boolean_op_45<Unit>::template Scan45CountT<CountMerge> > Vertex45Compact;
    typedef std::vector<Vertex45Compact> MergeSetData;

    struct lessVertex45Compact {
      bool operator()(const Vertex45Compact& l, const Vertex45Compact& r) {
        return l.first < r.first;
      }
    };

    template <typename output_type>
    static void performMerge(output_type& result, MergeSetData& tsd) {

      polygon_sort(tsd.begin(), tsd.end(), lessVertex45Compact());
      typedef std::vector<std::pair<Point, typename boolean_op_45<Unit>::template Scan45CountT<CountMerge> > > TSD;
      TSD tsd_;
      tsd_.reserve(tsd.size());
      for(typename MergeSetData::iterator itr = tsd.begin(); itr != tsd.end(); ) {
        typename MergeSetData::iterator itr2 = itr;
        ++itr2;
        for(; itr2 != tsd.end() && itr2->first == itr->first; ++itr2) {
          (itr->second) += (itr2->second); //accumulate
        }
        tsd_.push_back(std::make_pair(itr->first, itr->second));
        itr = itr2;
      }
      typename boolean_op_45<Unit>::template Scan45<CountMerge, merge_45_output_functor> scanline;
      for(typename TSD::iterator itr = tsd_.begin(); itr != tsd_.end(); ) {
        typename TSD::iterator itr2 = itr;
        ++itr2;
        while(itr2 != tsd_.end() && itr2->first.x() == itr->first.x()) {
          ++itr2;
        }
        scanline.scan(result, itr, itr2);
        itr = itr2;
      }
    }

    template <typename iT>
    static void populateMergeSetData(MergeSetData& tsd, iT begin, iT end, property_type property) {
      for( ; begin != end; ++begin) {
        Vertex45Compact vertex;
        vertex.first = typename Vertex45Compact::first_type(begin->pt.x() * 2, begin->pt.y() * 2);
        tsd.push_back(vertex);
        for(unsigned int i = 0; i < 4; ++i) {
          if(begin->count[i]) {
            tsd.back().second[i][property] += begin->count[i];
          }
        }
      }
    }

  };



}
}

#endif

/* property_merge_45.hpp
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
*/