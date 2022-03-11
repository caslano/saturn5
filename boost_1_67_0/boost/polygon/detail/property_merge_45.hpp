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