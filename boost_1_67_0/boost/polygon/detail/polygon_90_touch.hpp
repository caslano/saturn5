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