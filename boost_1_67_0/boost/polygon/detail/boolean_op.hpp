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