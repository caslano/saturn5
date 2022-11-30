/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_TOUCH_HPP
#define BOOST_POLYGON_POLYGON_90_TOUCH_HPP
namespace boost { namespace polygon{

  template <typename Unit>
  struct touch_90_operation {
    typedef interval_data<Unit> Interval;

    class TouchScanEvent {
    private:
      typedef std::map<Unit, std::set<int> > EventData;
      EventData eventData_;
    public:

      // The TouchScanEvent::iterator is a lazy algorithm that accumulates
      // polygon ids in a set as it is incremented through the
      // scan event data structure.
      // The iterator provides a forward iterator semantic only.
      class iterator {
      private:
        typename EventData::const_iterator itr_;
        std::pair<Interval, std::set<int> > ivlIds_;
        bool incremented_;
      public:
        inline iterator() : itr_(), ivlIds_(), incremented_(false) {}
        inline iterator(typename EventData::const_iterator itr,
                        Unit prevPos, Unit curPos, const std::set<int>& ivlIds) : itr_(itr), ivlIds_(), incremented_(false) {
          ivlIds_.second = ivlIds;
          ivlIds_.first = Interval(prevPos, curPos);
        }
        inline iterator(const iterator& that) : itr_(), ivlIds_(), incremented_(false) { (*this) = that; }
        inline iterator& operator=(const iterator& that) {
          itr_ = that.itr_;
          ivlIds_.first = that.ivlIds_.first;
          ivlIds_.second = that.ivlIds_.second;
          incremented_ = that.incremented_;
          return *this;
        }
        inline bool operator==(const iterator& that) { return itr_ == that.itr_; }
        inline bool operator!=(const iterator& that) { return itr_ != that.itr_; }
        inline iterator& operator++() {
          //std::cout << "increment\n";
          //std::cout << "state\n";
          //for(std::set<int>::iterator itr = ivlIds_.second.begin(); itr != ivlIds_.second.end(); ++itr) {
          //   std::cout << (*itr) << " ";
          //} std::cout << std::endl;
          //std::cout << "update\n";
          for(std::set<int>::const_iterator itr = (*itr_).second.begin();
              itr != (*itr_).second.end(); ++itr) {
            //std::cout << (*itr) <<  " ";
            std::set<int>::iterator lb = ivlIds_.second.find(*itr);
            if(lb != ivlIds_.second.end()) {
              ivlIds_.second.erase(lb);
            } else {
              ivlIds_.second.insert(*itr);
            }
          }
          //std::cout << std::endl;
          //std::cout << "new state\n";
          //for(std::set<int>::iterator itr = ivlIds_.second.begin(); itr != ivlIds_.second.end(); ++itr) {
          //   std::cout << (*itr) << " ";
          //} std::cout << std::endl;
          ++itr_;
          //ivlIds_.first = Interval(ivlIds_.first.get(HIGH), itr_->first);
          incremented_ = true;
          return *this;
        }
        inline const iterator operator++(int){
          iterator tmpItr(*this);
          ++(*this);
          return tmpItr;
        }
        inline std::pair<Interval, std::set<int> >& operator*() {
          if(incremented_) ivlIds_.first = Interval(ivlIds_.first.get(HIGH), itr_->first);
          incremented_ = false;
          if(ivlIds_.second.empty())(++(*this));
          if(incremented_) ivlIds_.first = Interval(ivlIds_.first.get(HIGH), itr_->first);
          incremented_ = false;
          return ivlIds_; }
      };

      inline TouchScanEvent() : eventData_() {}
      template<class iT>
      inline TouchScanEvent(iT begin, iT end) : eventData_() {
        for( ; begin != end; ++begin){
          insert(*begin);
        }
      }
      inline TouchScanEvent(const TouchScanEvent& that) : eventData_(that.eventData_) {}
      inline TouchScanEvent& operator=(const TouchScanEvent& that){
        eventData_ = that.eventData_;
        return *this;
      }

      //Insert an interval polygon id into the EventData
      inline void insert(const std::pair<Interval, int>& intervalId){
        insert(intervalId.first.low(), intervalId.second);
        insert(intervalId.first.high(), intervalId.second);
      }

      //Insert an position and polygon id into EventData
      inline void insert(Unit pos, int id) {
        typename EventData::iterator lb = eventData_.lower_bound(pos);
        if(lb != eventData_.end() && lb->first == pos) {
          std::set<int>& mr (lb->second);
          std::set<int>::iterator mri = mr.find(id);
          if(mri == mr.end()) {
            mr.insert(id);
          } else {
            mr.erase(id);
          }
        } else {
          lb = eventData_.insert(lb, std::pair<Unit, std::set<int> >(pos, std::set<int>()));
          (*lb).second.insert(id);
        }
      }

      //merge this scan event with that by inserting its data
      inline void insert(const TouchScanEvent& that){
        typename EventData::const_iterator itr;
        for(itr = that.eventData_.begin(); itr != that.eventData_.end(); ++itr) {
          eventData_[(*itr).first].insert(itr->second.begin(), itr->second.end());
        }
      }

      //Get the begin iterator over event data
      inline iterator begin() const {
        //std::cout << "begin\n";
        if(eventData_.empty()) return end();
        typename EventData::const_iterator itr = eventData_.begin();
        Unit pos = itr->first;
        const std::set<int>& idr = itr->second;
        ++itr;
        return iterator(itr, pos, itr->first, idr);
      }

      //Get the end iterator over event data
      inline iterator end() const { return iterator(eventData_.end(), 0, 0, std::set<int>()); }

      inline void clear() { eventData_.clear(); }

      inline Interval extents() const {
        if(eventData_.empty()) return Interval();
        return Interval((*(eventData_.begin())).first, (*(eventData_.rbegin())).first);
      }
    };

    //declaration of a map of scan events by coordinate value used to store all the
    //polygon data for a single layer input into the scanline algorithm
    typedef std::pair<std::map<Unit, TouchScanEvent>, std::map<Unit, TouchScanEvent> > TouchSetData;

    class TouchOp {
    public:
      typedef std::map<Unit, std::set<int> > ScanData;
      typedef std::pair<Unit, std::set<int> > ElementType;
    protected:
      ScanData scanData_;
      typename ScanData::iterator nextItr_;
    public:
      inline TouchOp () : scanData_(), nextItr_() { nextItr_ = scanData_.end(); }
      inline TouchOp (const TouchOp& that) : scanData_(that.scanData_), nextItr_() { nextItr_ = scanData_.begin(); }
      inline TouchOp& operator=(const TouchOp& that);

      //moves scanline forward
      inline void advanceScan() { nextItr_ = scanData_.begin(); }

      //proceses the given interval and std::set<int> data
      //the output data structre is a graph, the indicies in the vector correspond to graph nodes,
      //the integers in the set are vector indicies and are the nodes with which that node shares an edge
      template <typename graphT>
      inline void processInterval(graphT& outputContainer, Interval ivl, const std::set<int>& ids, bool leadingEdge) {
        //print();
        typename ScanData::iterator lowItr = lookup_(ivl.low());
        typename ScanData::iterator highItr = lookup_(ivl.high());
        //std::cout << "Interval: " << ivl << std::endl;
        //for(std::set<int>::const_iterator itr = ids.begin(); itr != ids.end(); ++itr)
        //   std::cout << (*itr) << " ";
        //std::cout << std::endl;
        //add interval to scan data if it is past the end
        if(lowItr == scanData_.end()) {
          //std::cout << "case0" << std::endl;
          lowItr = insert_(ivl.low(), ids);
          evaluateBorder_(outputContainer, ids, ids);
          highItr = insert_(ivl.high(), std::set<int>());
          return;
        }
        //ensure that highItr points to the end of the ivl
        if(highItr == scanData_.end() || (*highItr).first > ivl.high()) {
          //std::cout << "case1" << std::endl;
          //std::cout << highItr->first << std::endl;
          std::set<int> value = std::set<int>();
          if(highItr != scanData_.begin()) {
            --highItr;
            //std::cout << highItr->first << std::endl;
            //std::cout << "high set size " << highItr->second.size() << std::endl;
            value = highItr->second;
          }
          nextItr_ = highItr;
          highItr = insert_(ivl.high(), value);
        } else {
          //evaluate border with next higher interval
          //std::cout << "case1a" << std::endl;
          if(leadingEdge)evaluateBorder_(outputContainer, highItr->second, ids);
        }
        //split the low interval if needed
        if(lowItr->first > ivl.low()) {
          //std::cout << "case2" << std::endl;
          if(lowItr != scanData_.begin()) {
            //std::cout << "case3" << std::endl;
            --lowItr;
            nextItr_ = lowItr;
            //std::cout << lowItr->first << " " << lowItr->second.size() << std::endl;
            lowItr = insert_(ivl.low(), lowItr->second);
          } else {
            //std::cout << "case4" << std::endl;
            nextItr_ = lowItr;
            lowItr = insert_(ivl.low(), std::set<int>());
          }
        } else {
          //evaluate border with next higher interval
          //std::cout << "case2a" << std::endl;
          typename ScanData::iterator nextLowerItr = lowItr;
          if(leadingEdge && nextLowerItr != scanData_.begin()){
            --nextLowerItr;
            evaluateBorder_(outputContainer, nextLowerItr->second, ids);
          }
        }
        //std::cout << "low: " << lowItr->first << " high: " << highItr->first << std::endl;
        //print();
        //process scan data intersecting interval
        for(typename ScanData::iterator itr = lowItr; itr != highItr; ){
          //std::cout << "case5" << std::endl;
          //std::cout << itr->first << std::endl;
          std::set<int>& beforeIds = itr->second;
          ++itr;
          evaluateInterval_(outputContainer, beforeIds, ids, leadingEdge);
        }
        //print();
        //merge the bottom interval with the one below if they have the same count
        if(lowItr != scanData_.begin()){
          //std::cout << "case6" << std::endl;
          typename ScanData::iterator belowLowItr = lowItr;
          --belowLowItr;
          if(belowLowItr->second == lowItr->second) {
            //std::cout << "case7" << std::endl;
            scanData_.erase(lowItr);
          }
        }
        //merge the top interval with the one above if they have the same count
        if(highItr != scanData_.begin()) {
          //std::cout << "case8" << std::endl;
          typename ScanData::iterator beforeHighItr = highItr;
          --beforeHighItr;
          if(beforeHighItr->second == highItr->second) {
            //std::cout << "case9" << std::endl;
            scanData_.erase(highItr);
            highItr = beforeHighItr;
            ++highItr;
          }
        }
        //print();
        nextItr_ = highItr;
      }

//       inline void print() const {
//         for(typename ScanData::const_iterator itr = scanData_.begin(); itr != scanData_.end(); ++itr) {
//           std::cout << itr->first << ": ";
//           for(std::set<int>::const_iterator sitr = itr->second.begin();
//               sitr != itr->second.end(); ++sitr){
//             std::cout << *sitr << " ";
//           }
//           std::cout << std::endl;
//         }
//       }

    private:
      inline typename ScanData::iterator lookup_(Unit pos){
        if(nextItr_ != scanData_.end() && nextItr_->first >= pos) {
          return nextItr_;
        }
        return nextItr_ = scanData_.lower_bound(pos);
      }

      inline typename ScanData::iterator insert_(Unit pos, const std::set<int>& ids){
        //std::cout << "inserting " << ids.size() << " ids at: " << pos << std::endl;
        return nextItr_ = scanData_.insert(nextItr_, std::pair<Unit, std::set<int> >(pos, ids));
      }

      template <typename graphT>
      inline void evaluateInterval_(graphT& outputContainer, std::set<int>& ids,
                                    const std::set<int>& changingIds, bool leadingEdge) {
        for(std::set<int>::const_iterator ciditr = changingIds.begin(); ciditr != changingIds.end(); ++ciditr){
          //std::cout << "evaluateInterval " << (*ciditr) << std::endl;
          evaluateId_(outputContainer, ids, *ciditr, leadingEdge);
        }
      }
      template <typename graphT>
      inline void evaluateBorder_(graphT& outputContainer, const std::set<int>& ids, const std::set<int>& changingIds) {
        for(std::set<int>::const_iterator ciditr = changingIds.begin(); ciditr != changingIds.end(); ++ciditr){
          //std::cout << "evaluateBorder " << (*ciditr) << std::endl;
          evaluateBorderId_(outputContainer, ids, *ciditr);
        }
      }
      template <typename graphT>
      inline void evaluateBorderId_(graphT& outputContainer, const std::set<int>& ids, int changingId) {
        for(std::set<int>::const_iterator scanItr = ids.begin(); scanItr != ids.end(); ++scanItr) {
          //std::cout << "create edge: " << changingId << " " << *scanItr << std::endl;
          if(changingId != *scanItr){
            outputContainer[changingId].insert(*scanItr);
            outputContainer[*scanItr].insert(changingId);
          }
        }
      }
      template <typename graphT>
      inline void evaluateId_(graphT& outputContainer, std::set<int>& ids, int changingId, bool leadingEdge) {
        //std::cout << "changingId: " << changingId << std::endl;
        //for( std::set<int>::iterator itr = ids.begin(); itr != ids.end(); ++itr){
        //   std::cout << *itr << " ";
        //}std::cout << std::endl;
        std::set<int>::iterator lb = ids.lower_bound(changingId);
        if(lb == ids.end() || (*lb) != changingId) {
          if(leadingEdge) {
            //std::cout << "insert\n";
            //insert and add to output
            for(std::set<int>::iterator scanItr = ids.begin(); scanItr != ids.end(); ++scanItr) {
              //std::cout << "create edge: " << changingId << " " << *scanItr << std::endl;
              if(changingId != *scanItr){
                outputContainer[changingId].insert(*scanItr);
                outputContainer[*scanItr].insert(changingId);
              }
            }
            ids.insert(changingId);
          }
        } else {
          if(!leadingEdge){
            //std::cout << "erase\n";
            ids.erase(lb);
          }
        }
      }
    };

    template <typename graphT>
    static inline void processEvent(graphT& outputContainer, TouchOp& op, const TouchScanEvent& data, bool leadingEdge) {
      for(typename TouchScanEvent::iterator itr = data.begin(); itr != data.end(); ++itr) {
        //std::cout << "processInterval" << std::endl;
        op.processInterval(outputContainer, (*itr).first, (*itr).second, leadingEdge);
      }
    }

    template <typename graphT>
    static inline void performTouch(graphT& outputContainer, const TouchSetData& data) {
      typename std::map<Unit, TouchScanEvent>::const_iterator leftItr = data.first.begin();
      typename std::map<Unit, TouchScanEvent>::const_iterator rightItr = data.second.begin();
      typename std::map<Unit, TouchScanEvent>::const_iterator leftEnd = data.first.end();
      typename std::map<Unit, TouchScanEvent>::const_iterator rightEnd = data.second.end();
      TouchOp op;
      while(leftItr != leftEnd || rightItr != rightEnd) {
        //std::cout << "loop" << std::endl;
        op.advanceScan();
        //rightItr cannont be at end if leftItr is not at end
        if(leftItr != leftEnd && rightItr != rightEnd &&
           leftItr->first <= rightItr->first) {
          //std::cout << "case1" << std::endl;
          //std::cout << leftItr ->first << std::endl;
          processEvent(outputContainer, op, leftItr->second, true);
          ++leftItr;
        } else {
          //std::cout << "case2" << std::endl;
          //std::cout << rightItr ->first << std::endl;
          processEvent(outputContainer, op, rightItr->second, false);
          ++rightItr;
        }
      }
    }

    template <class iT>
    static inline void populateTouchSetData(TouchSetData& data, iT beginData, iT endData, int id) {
      Unit prevPos = ((std::numeric_limits<Unit>::max)());
      Unit prevY = prevPos;
      int count = 0;
      for(iT itr = beginData; itr != endData; ++itr) {
        Unit pos = (*itr).first;
        if(pos != prevPos) {
          prevPos = pos;
          prevY = (*itr).second.first;
          count = (*itr).second.second;
          continue;
        }
        Unit y = (*itr).second.first;
        if(count != 0 && y != prevY) {
          std::pair<Interval, int> element(Interval(prevY, y), id);
          if(count > 0) {
            data.first[pos].insert(element);
          } else {
            data.second[pos].insert(element);
          }
        }
        prevY = y;
        count += (*itr).second.second;
      }
    }

    static inline void populateTouchSetData(TouchSetData& data, const std::vector<std::pair<Unit, std::pair<Unit, int> > >& inputData, int id) {
      populateTouchSetData(data, inputData.begin(), inputData.end(), id);
    }

  };
}
}
#endif

/* polygon_90_touch.hpp
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
*/