/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_BOOLEAN_OP_HPP
#define BOOST_POLYGON_BOOLEAN_OP_HPP
namespace boost { namespace polygon{
namespace boolean_op {

  //BooleanOp is the generic boolean operation scanline algorithm that provides
  //all the simple boolean set operations on manhattan data.  By templatizing
  //the intersection count of the input and algorithm internals it is extensible
  //to multi-layer scans, properties and other advanced scanline operations above
  //and beyond simple booleans.
  //T must cast to int
  template <class T, typename Unit>
  class BooleanOp {
  public:
    typedef std::map<Unit, T> ScanData;
    typedef std::pair<Unit, T> ElementType;
  protected:
    ScanData scanData_;
    typename ScanData::iterator nextItr_;
    T nullT_;
  public:
    inline BooleanOp () : scanData_(), nextItr_(), nullT_() { nextItr_ = scanData_.end(); nullT_ = 0; }
    inline BooleanOp (T nullT) : scanData_(), nextItr_(), nullT_(nullT) { nextItr_ = scanData_.end(); }
    inline BooleanOp (const BooleanOp& that) : scanData_(that.scanData_), nextItr_(),
                                               nullT_(that.nullT_) { nextItr_ = scanData_.begin(); }
    inline BooleanOp& operator=(const BooleanOp& that);

    //moves scanline forward
    inline void advanceScan() { nextItr_ = scanData_.begin(); }

    //proceses the given interval and T data
    //appends output edges to cT
    template <class cT>
    inline void processInterval(cT& outputContainer, interval_data<Unit> ivl, T deltaCount);

  private:
    inline typename ScanData::iterator lookup_(Unit pos){
      if(nextItr_ != scanData_.end() && nextItr_->first >= pos) {
        return nextItr_;
      }
      return nextItr_ = scanData_.lower_bound(pos);
    }
    inline typename ScanData::iterator insert_(Unit pos, T count){
      return nextItr_ = scanData_.insert(nextItr_, ElementType(pos, count));
    }
    template <class cT>
    inline void evaluateInterval_(cT& outputContainer, interval_data<Unit> ivl, T beforeCount, T afterCount);
  };

  class BinaryAnd {
  public:
    inline BinaryAnd() {}
    inline bool operator()(int a, int b) { return (a > 0) & (b > 0); }
  };
  class BinaryOr {
  public:
    inline BinaryOr() {}
    inline bool operator()(int a, int b) { return (a > 0) | (b > 0); }
  };
  class BinaryNot {
  public:
    inline BinaryNot() {}
    inline bool operator()(int a, int b) { return (a > 0) & !(b > 0); }
  };
  class BinaryXor {
  public:
    inline BinaryXor() {}
    inline bool operator()(int a, int b) { return (a > 0) ^ (b > 0); }
  };

  //BinaryCount is an array of two deltaCounts coming from two different layers
  //of scan event data.  It is the merged count of the two suitable for consumption
  //as the template argument of the BooleanOp algorithm because BinaryCount casts to int.
  //T is a binary functor object that evaluates the array of counts and returns a logical
  //result of some operation on those values.
  //BinaryCount supports many of the operators that work with int, particularly the
  //binary operators, but cannot support less than or increment.
  template <class T>
  class BinaryCount {
  public:
    inline BinaryCount()
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { counts_[0] = counts_[1] = 0; }
    // constructs from two integers
    inline BinaryCount(int countL, int countR)
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { counts_[0] = countL, counts_[1] = countR; }
    inline BinaryCount& operator=(int count) { counts_[0] = count, counts_[1] = count; return *this; }
    inline BinaryCount& operator=(const BinaryCount& that);
    inline BinaryCount(const BinaryCount& that)
#ifndef BOOST_POLYGON_MSVC
      : counts_()
#endif
    { *this = that; }
    inline bool operator==(const BinaryCount& that) const;
    inline bool operator!=(const BinaryCount& that) const { return !((*this) == that);}
    inline BinaryCount& operator+=(const BinaryCount& that);
    inline BinaryCount& operator-=(const BinaryCount& that);
    inline BinaryCount operator+(const BinaryCount& that) const;
    inline BinaryCount operator-(const BinaryCount& that) const;
    inline BinaryCount operator-() const;
    inline int& operator[](bool index) { return counts_[index]; }

    //cast to int operator evaluates data using T binary functor
    inline operator int() const { return T()(counts_[0], counts_[1]); }
  private:
    int counts_[2];
  };

  class UnaryCount {
  public:
    inline UnaryCount() : count_(0) {}
    // constructs from two integers
    inline explicit UnaryCount(int count) : count_(count) {}
    inline UnaryCount& operator=(int count) { count_ = count; return *this; }
    inline UnaryCount& operator=(const UnaryCount& that) { count_ = that.count_; return *this; }
    inline UnaryCount(const UnaryCount& that) : count_(that.count_) {}
    inline bool operator==(const UnaryCount& that) const { return count_ == that.count_; }
    inline bool operator!=(const UnaryCount& that) const { return !((*this) == that);}
    inline UnaryCount& operator+=(const UnaryCount& that) { count_ += that.count_; return *this; }
    inline UnaryCount& operator-=(const UnaryCount& that) { count_ -= that.count_; return *this; }
    inline UnaryCount operator+(const UnaryCount& that) const { UnaryCount tmp(*this); tmp += that; return tmp; }
    inline UnaryCount operator-(const UnaryCount& that) const { UnaryCount tmp(*this); tmp -= that; return tmp; }
    inline UnaryCount operator-() const { UnaryCount tmp; return tmp - *this; }

    //cast to int operator evaluates data using T binary functor
    inline operator int() const { return count_ % 2; }
  private:
    int count_;
  };

  template <class T, typename Unit>
  inline BooleanOp<T, Unit>& BooleanOp<T, Unit>::operator=(const BooleanOp& that) {
    scanData_ = that.scanData_;
    nextItr_ = scanData_.begin();
    nullT_ = that.nullT_;
    return *this;
  }

  //appends output edges to cT
  template <class T, typename Unit>
  template <class cT>
  inline void BooleanOp<T, Unit>::processInterval(cT& outputContainer, interval_data<Unit> ivl, T deltaCount) {
    typename ScanData::iterator lowItr = lookup_(ivl.low());
    typename ScanData::iterator highItr = lookup_(ivl.high());
    //add interval to scan data if it is past the end
    if(lowItr == scanData_.end()) {
      lowItr = insert_(ivl.low(), deltaCount);
      highItr = insert_(ivl.high(), nullT_);
      evaluateInterval_(outputContainer, ivl, nullT_, deltaCount);
      return;
    }
    //ensure that highItr points to the end of the ivl
    if(highItr == scanData_.end() || (*highItr).first > ivl.high()) {
      T value = nullT_;
      if(highItr != scanData_.begin()) {
        --highItr;
        value = highItr->second;
      }
      nextItr_ = highItr;
      highItr = insert_(ivl.high(), value);
    }
    //split the low interval if needed
    if(lowItr->first > ivl.low()) {
      if(lowItr != scanData_.begin()) {
        --lowItr;
        nextItr_ = lowItr;
        lowItr = insert_(ivl.low(), lowItr->second);
      } else {
        nextItr_ = lowItr;
        lowItr = insert_(ivl.low(), nullT_);
      }
    }
    //process scan data intersecting interval
    for(typename ScanData::iterator itr = lowItr; itr != highItr; ){
      T beforeCount = itr->second;
      T afterCount = itr->second += deltaCount;
      Unit low = itr->first;
      ++itr;
      Unit high = itr->first;
      evaluateInterval_(outputContainer, interval_data<Unit>(low, high), beforeCount, afterCount);
    }
    //merge the bottom interval with the one below if they have the same count
    if(lowItr != scanData_.begin()){
      typename ScanData::iterator belowLowItr = lowItr;
      --belowLowItr;
      if(belowLowItr->second == lowItr->second) {
        scanData_.erase(lowItr);
      }
    }
    //merge the top interval with the one above if they have the same count
    if(highItr != scanData_.begin()) {
      typename ScanData::iterator beforeHighItr = highItr;
      --beforeHighItr;
      if(beforeHighItr->second == highItr->second) {
        scanData_.erase(highItr);
        highItr = beforeHighItr;
        ++highItr;
      }
    }
    nextItr_ = highItr;
  }

  template <class T, typename Unit>
  template <class cT>
  inline void BooleanOp<T, Unit>::evaluateInterval_(cT& outputContainer, interval_data<Unit> ivl,
                                              T beforeCount, T afterCount) {
    bool before = (int)beforeCount > 0;
    bool after = (int)afterCount > 0;
    int value =  (!before & after) - (before & !after);
    if(value) {
      outputContainer.insert(outputContainer.end(), std::pair<interval_data<Unit>, int>(ivl, value));
    }
  }

  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator=(const BinaryCount<T>& that) {
    counts_[0] = that.counts_[0];
    counts_[1] = that.counts_[1];
    return *this;
  }
  template <class T>
  inline bool BinaryCount<T>::operator==(const BinaryCount<T>& that) const {
    return counts_[0] == that.counts_[0] &&
      counts_[1] == that.counts_[1];
  }
  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator+=(const BinaryCount<T>& that) {
    counts_[0] += that.counts_[0];
    counts_[1] += that.counts_[1];
    return *this;
  }
  template <class T>
  inline BinaryCount<T>& BinaryCount<T>::operator-=(const BinaryCount<T>& that) {
    counts_[0] += that.counts_[0];
    counts_[1] += that.counts_[1];
    return *this;
  }
  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator+(const BinaryCount<T>& that) const {
    BinaryCount retVal(*this);
    retVal += that;
    return retVal;
  }
  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator-(const BinaryCount<T>& that) const {
    BinaryCount retVal(*this);
    retVal -= that;
    return retVal;
  }
  template <class T>
  inline BinaryCount<T> BinaryCount<T>::operator-() const {
    return BinaryCount<T>() - *this;
  }


  template <class T, typename Unit, typename iterator_type_1, typename iterator_type_2>
  inline void applyBooleanBinaryOp(std::vector<std::pair<Unit, std::pair<Unit, int> > >& output,
                                   //const std::vector<std::pair<Unit, std::pair<Unit, int> > >& input1,
                                   //const std::vector<std::pair<Unit, std::pair<Unit, int> > >& input2,
                                   iterator_type_1 itr1, iterator_type_1 itr1_end,
                                   iterator_type_2 itr2, iterator_type_2 itr2_end,
                                   T defaultCount) {
    BooleanOp<T, Unit> boolean(defaultCount);
    //typename std::vector<std::pair<Unit, std::pair<Unit, int> > >::const_iterator itr1 = input1.begin();
    //typename std::vector<std::pair<Unit, std::pair<Unit, int> > >::const_iterator itr2 = input2.begin();
    std::vector<std::pair<interval_data<Unit>, int> > container;
    //output.reserve((std::max)(input1.size(), input2.size()));

    //consider eliminating dependecy on limits with bool flag for initial state
    Unit UnitMax = (std::numeric_limits<Unit>::max)();
    Unit prevCoord = UnitMax;
    Unit prevPosition = UnitMax;
    T count(defaultCount);
    //define the starting point
    if(itr1 != itr1_end) {
      prevCoord = (*itr1).first;
      prevPosition = (*itr1).second.first;
      count[0] += (*itr1).second.second;
    }
    if(itr2 != itr2_end) {
      if((*itr2).first < prevCoord ||
         ((*itr2).first == prevCoord && (*itr2).second.first < prevPosition)) {
        prevCoord = (*itr2).first;
        prevPosition = (*itr2).second.first;
        count = defaultCount;
        count[1] += (*itr2).second.second;
        ++itr2;
      } else if((*itr2).first == prevCoord && (*itr2).second.first == prevPosition) {
        count[1] += (*itr2).second.second;
        ++itr2;
        if(itr1 != itr1_end) ++itr1;
      } else {
        if(itr1 != itr1_end) ++itr1;
      }
    } else {
      if(itr1 != itr1_end) ++itr1;
    }

    while(itr1 != itr1_end || itr2 != itr2_end) {
      Unit curCoord = UnitMax;
      Unit curPosition = UnitMax;
      T curCount(defaultCount);
      if(itr1 != itr1_end) {
        curCoord = (*itr1).first;
        curPosition = (*itr1).second.first;
        curCount[0] += (*itr1).second.second;
      }
      if(itr2 != itr2_end) {
        if((*itr2).first < curCoord ||
           ((*itr2).first == curCoord && (*itr2).second.first < curPosition)) {
          curCoord = (*itr2).first;
          curPosition = (*itr2).second.first;
          curCount = defaultCount;
          curCount[1] += (*itr2).second.second;
          ++itr2;
        } else if((*itr2).first == curCoord && (*itr2).second.first == curPosition) {
          curCount[1] += (*itr2).second.second;
          ++itr2;
          if(itr1 != itr1_end) ++itr1;
        } else {
          if(itr1 != itr1_end) ++itr1;
        }
      } else {
        ++itr1;
      }

      if(prevCoord != curCoord) {
        boolean.advanceScan();
        prevCoord = curCoord;
        prevPosition = curPosition;
        count = curCount;
        continue;
      }
      if(curPosition != prevPosition && count != defaultCount) {
        interval_data<Unit> ivl(prevPosition, curPosition);
        container.clear();
        boolean.processInterval(container, ivl, count);
        for(std::size_t i = 0; i < container.size(); ++i) {
          std::pair<interval_data<Unit>, int>& element = container[i];
          if(!output.empty() && output.back().first == prevCoord &&
             output.back().second.first == element.first.low() &&
             output.back().second.second == element.second * -1) {
            output.pop_back();
          } else {
            output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevCoord, std::pair<Unit, int>(element.first.low(),
                                                                                                    element.second)));
          }
          output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevCoord, std::pair<Unit, int>(element.first.high(),
                                                                                                  element.second * -1)));
        }
      }
      prevPosition = curPosition;
      count += curCount;
    }
  }

  template <class T, typename Unit>
  inline void applyBooleanBinaryOp(std::vector<std::pair<Unit, std::pair<Unit, int> > >& inputOutput,
                                   const std::vector<std::pair<Unit, std::pair<Unit, int> > >& input2,
                                   T defaultCount) {
    std::vector<std::pair<Unit, std::pair<Unit, int> > > output;
    applyBooleanBinaryOp(output, inputOutput, input2, defaultCount);
    if(output.size() < inputOutput.size() / 2) {
      inputOutput = std::vector<std::pair<Unit, std::pair<Unit, int> > >();
    } else {
      inputOutput.clear();
    }
    inputOutput.insert(inputOutput.end(), output.begin(), output.end());
  }

  template <typename count_type = int>
  struct default_arg_workaround {
    template <typename Unit>
    static inline void applyBooleanOr(std::vector<std::pair<Unit, std::pair<Unit, int> > >& input) {
      BooleanOp<count_type, Unit> booleanOr;
      std::vector<std::pair<interval_data<Unit>, int> > container;
      std::vector<std::pair<Unit, std::pair<Unit, int> > > output;
      output.reserve(input.size());
      //consider eliminating dependecy on limits with bool flag for initial state
      Unit UnitMax = (std::numeric_limits<Unit>::max)();
      Unit prevPos = UnitMax;
      Unit prevY = UnitMax;
      int count = 0;
      for(typename std::vector<std::pair<Unit, std::pair<Unit, int> > >::iterator itr = input.begin();
          itr != input.end(); ++itr) {
        Unit pos = (*itr).first;
        Unit y = (*itr).second.first;
        if(pos != prevPos) {
          booleanOr.advanceScan();
          prevPos = pos;
          prevY = y;
          count = (*itr).second.second;
          continue;
        }
        if(y != prevY && count != 0) {
          interval_data<Unit> ivl(prevY, y);
          container.clear();
          booleanOr.processInterval(container, ivl, count_type(count));
          for(std::size_t i = 0; i < container.size(); ++i) {
            std::pair<interval_data<Unit>, int>& element = container[i];
            if(!output.empty() && output.back().first == prevPos &&
               output.back().second.first == element.first.low() &&
               output.back().second.second == element.second * -1) {
              output.pop_back();
            } else {
              output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevPos, std::pair<Unit, int>(element.first.low(),
                                                                                                    element.second)));
            }
            output.push_back(std::pair<Unit, std::pair<Unit, int> >(prevPos, std::pair<Unit, int>(element.first.high(),
                                                                                                  element.second * -1)));
          }
        }
        prevY = y;
        count += (*itr).second.second;
      }
      if(output.size() < input.size() / 2) {
        input = std::vector<std::pair<Unit, std::pair<Unit, int> > >();
      } else {
      input.clear();
      }
      input.insert(input.end(), output.begin(), output.end());
    }
  };

}

}

}
#endif

/* boolean_op.hpp
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
*/