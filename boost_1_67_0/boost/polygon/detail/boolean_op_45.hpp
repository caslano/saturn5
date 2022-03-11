/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_BOOLEAN_OP_45_HPP
#define BOOST_POLYGON_BOOLEAN_OP_45_HPP
namespace boost { namespace polygon{

  template <typename Unit>
  struct boolean_op_45 {
    typedef point_data<Unit> Point;
    typedef typename coordinate_traits<Unit>::manhattan_area_type LongUnit;

    class Count2 {
    public:
      inline Count2()
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = counts[1] = 0; }
      //inline Count2(int count) { counts[0] = counts[1] = count; }
      inline Count2(int count1, int count2)
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = count1; counts[1] = count2; }
      inline Count2(const Count2& count)
#ifndef BOOST_POLYGON_MSVC
      : counts()
#endif
      { counts[0] = count.counts[0]; counts[1] = count.counts[1]; }
      inline bool operator==(const Count2& count) const { return counts[0] == count.counts[0] && counts[1] == count.counts[1]; }
      inline bool operator!=(const Count2& count) const { return !((*this) == count); }
      inline Count2& operator=(int count) { counts[0] = counts[1] = count; return *this; }
      inline Count2& operator=(const Count2& count) { counts[0] = count.counts[0]; counts[1] = count.counts[1]; return *this; }
      inline int& operator[](bool index) { return counts[index]; }
      inline int operator[](bool index) const {return counts[index]; }
      inline Count2& operator+=(const Count2& count){
        counts[0] += count[0];
        counts[1] += count[1];
        return *this;
      }
      inline Count2& operator-=(const Count2& count){
        counts[0] -= count[0];
        counts[1] -= count[1];
        return *this;
      }
      inline Count2 operator+(const Count2& count) const {
        return Count2(*this)+=count;
      }
      inline Count2 operator-(const Count2& count) const {
        return Count2(*this)-=count;
      }
      inline Count2 invert() const {
        return Count2(-counts[0], -counts[1]);
      }
    private:
      int counts[2];
    };

    class Count1 {
    public:
      inline Count1() : count_(0) { }
      inline Count1(int count) : count_(count) { }
      inline Count1(const Count1& count) : count_(count.count_) { }
      inline bool operator==(const Count1& count) const { return count_ == count.count_; }
      inline bool operator!=(const Count1& count) const { return !((*this) == count); }
      inline Count1& operator=(int count) { count_ = count; return *this; }
      inline Count1& operator=(const Count1& count) { count_ = count.count_; return *this; }
      inline Count1& operator+=(const Count1& count){
        count_ += count.count_;
        return *this;
      }
      inline Count1& operator-=(const Count1& count){
        count_ -= count.count_;
        return *this;
      }
      inline Count1 operator+(const Count1& count) const {
        return Count1(*this)+=count;
      }
      inline Count1 operator-(const Count1& count) const {
        return Count1(*this)-=count;
      }
      inline Count1 invert() const {
        return Count1(-count_);
      }
      int count_;
    };

    //     inline std::ostream& operator<< (std::ostream& o, const Count2& c) {
    //       o << c[0] << " " << c[1];
    //       return o;
    //     }

    template <typename CountType>
    class Scan45ElementT {
    public:
      Unit x;
      Unit y;
      int rise; //-1, 0, +1
      mutable CountType count;
      inline Scan45ElementT() : x(), y(), rise(), count() {}
      inline Scan45ElementT(Unit xIn, Unit yIn, int riseIn, CountType countIn = CountType()) :
        x(xIn), y(yIn), rise(riseIn), count(countIn) {}
      inline Scan45ElementT(const Scan45ElementT& that) :
        x(that.x), y(that.y), rise(that.rise), count(that.count) {}
      inline Scan45ElementT& operator=(const Scan45ElementT& that) {
        x = that.x; y = that.y; rise = that.rise; count = that.count;
        return *this;
      }
      inline Unit evalAtX(Unit xIn) const {
        return y + rise * (xIn - x);
      }

      inline bool cross(Point& crossPoint, const Scan45ElementT& edge, Unit currentX) const {
        Unit y1 = evalAtX(currentX);
        Unit y2 = edge.evalAtX(currentX);
        int rise1 = rise;
        int rise2 = edge.rise;
        if(rise > edge.rise){
          if(y1 > y2) return false;
        } else if(rise < edge.rise){
          if(y2 > y1) return false;
          std::swap(y1, y2);
          std::swap(rise1, rise2);
        } else { return false; }
        if(rise1 == 1) {
          if(rise2 == 0) {
            crossPoint = Point(currentX + y2 - y1, y2);
          } else {
            //rise2 == -1
            Unit delta = (y2 - y1)/2;
            crossPoint = Point(currentX + delta, y1 + delta);
          }
        } else {
          //rise1 == 0 and rise2 == -1
          crossPoint = Point(currentX + y2 - y1, y1);
        }
        return true;
      }
    };

    typedef Scan45ElementT<Count2> Scan45Element;

    //     inline std::ostream& operator<< (std::ostream& o, const Scan45Element& c) {
    //       o << c.x << " " << c.y << " " << c.rise << " " << c.count;
    //       return o;
    //     }

    class lessScan45ElementRise {
    public:
      typedef Scan45Element first_argument_type;
      typedef Scan45Element second_argument_type;
      typedef bool result_type;
      inline lessScan45ElementRise() {} //default constructor is only constructor
      inline bool operator () (Scan45Element elm1, Scan45Element elm2) const {
        return elm1.rise < elm2.rise;
      }
    };

    template <typename CountType>
    class lessScan45Element {
    private:
      Unit *x_; //x value at which to apply comparison
      int *justBefore_;
    public:
      inline lessScan45Element() : x_(0), justBefore_(0) {}
      inline lessScan45Element(Unit *x, int *justBefore) : x_(x), justBefore_(justBefore) {}
      inline lessScan45Element(const lessScan45Element& that) : x_(that.x_), justBefore_(that.justBefore_) {}
      inline lessScan45Element& operator=(const lessScan45Element& that) { x_ = that.x_; justBefore_ = that.justBefore_; return *this; }
      inline bool operator () (const Scan45ElementT<CountType>& elm1,
                               const Scan45ElementT<CountType>& elm2) const {
        Unit y1 = elm1.evalAtX(*x_);
        Unit y2 = elm2.evalAtX(*x_);
        if(y1 < y2) return true;
        if(y1 == y2) {
          //if justBefore is true we invert the result of the comparison of slopes
          if(*justBefore_) {
            return elm1.rise > elm2.rise;
          } else {
            return elm1.rise < elm2.rise;
          }
        }
        return false;
      }
    };

    template <typename CountType>
    class Scan45CountT {
    public:
      inline Scan45CountT() : counts() {} //counts[0] = counts[1] = counts[2] = counts[3] = 0; }
      inline Scan45CountT(CountType count) : counts() { counts[0] = counts[1] = counts[2] = counts[3] = count; }
      inline Scan45CountT(const CountType& count1, const CountType& count2, const CountType& count3,
                          const CountType& count4) : counts() {
        counts[0] = count1;
        counts[1] = count2;
        counts[2] = count3;
        counts[3] = count4;
      }
      inline Scan45CountT(const Scan45CountT& count) : counts() {
        (*this) = count;
      }
      inline bool operator==(const Scan45CountT& count) const {
        for(unsigned int i = 0; i < 4; ++i) {
          if(counts[i] != count.counts[i]) return false;
        }
        return true;
      }
      inline bool operator!=(const Scan45CountT& count) const { return !((*this) == count); }
      inline Scan45CountT& operator=(CountType count) {
        counts[0] = counts[1] = counts[2] = counts[3] = count; return *this; }
      inline Scan45CountT& operator=(const Scan45CountT& count) {
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] = count.counts[i];
        }
        return *this;
      }
      inline CountType& operator[](int index) { return counts[index]; }
      inline CountType operator[](int index) const {return counts[index]; }
      inline Scan45CountT& operator+=(const Scan45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] += count.counts[i];
        }
        return *this;
      }
      inline Scan45CountT& operator-=(const Scan45CountT& count){
        for(unsigned int i = 0; i < 4; ++i) {
          counts[i] -= count.counts[i];
        }
        return *this;
      }
      inline Scan45CountT operator+(const Scan45CountT& count) const {
        return Scan45CountT(*this)+=count;
      }
      inline Scan45CountT operator-(const Scan45CountT& count) const {
        return Scan45CountT(*this)-=count;
      }
      inline Scan45CountT invert() const {
        return Scan45CountT(CountType())-=(*this);
      }
      inline Scan45CountT& operator+=(const Scan45ElementT<CountType>& element){
        counts[element.rise+1] += element.count; return *this;
      }
    private:
      CountType counts[4];
    };

    typedef Scan45CountT<Count2> Scan45Count;

    //     inline std::ostream& operator<< (std::ostream& o, const Scan45Count& c) {
    //       o << c[0] << ", " << c[1] << ", ";
    //       o << c[2] << ", " << c[3];
    //       return o;
    //     }


    //     inline std::ostream& operator<< (std::ostream& o, const Scan45Vertex& c) {
    //       o << c.first << ": " << c.second;
    //       return o;
    //     }


    //vetex45 is sortable
    template <typename ct>
    class Vertex45T {
    public:
      Point pt;
      int rise; // 1, 0 or -1
      ct count; //dxdydTheta
      inline Vertex45T() : pt(), rise(), count() {}
      inline Vertex45T(const Point& point, int riseIn, ct countIn) : pt(point), rise(riseIn), count(countIn) {}
      inline Vertex45T(const Vertex45T& vertex) : pt(vertex.pt), rise(vertex.rise), count(vertex.count) {}
      inline Vertex45T& operator=(const Vertex45T& vertex){
        pt = vertex.pt; rise = vertex.rise; count = vertex.count; return *this; }
      inline bool operator==(const Vertex45T& vertex) const {
        return pt == vertex.pt && rise == vertex.rise && count == vertex.count; }
      inline bool operator!=(const Vertex45T& vertex) const { return !((*this) == vertex); }
      inline bool operator<(const Vertex45T& vertex) const {
        if(pt.x() < vertex.pt.x()) return true;
        if(pt.x() == vertex.pt.x()) {
          if(pt.y() < vertex.pt.y()) return true;
          if(pt.y() == vertex.pt.y()) { return rise < vertex.rise; }
        }
        return false;
      }
      inline bool operator>(const Vertex45T& vertex) const { return vertex < (*this); }
      inline bool operator<=(const Vertex45T& vertex) const { return !((*this) > vertex); }
      inline bool operator>=(const Vertex45T& vertex) const { return !((*this) < vertex); }
      inline Unit evalAtX(Unit xIn) const { return pt.y() + rise * (xIn - pt.x()); }
    };

    typedef Vertex45T<int> Vertex45;

    //     inline std::ostream& operator<< (std::ostream& o, const Vertex45& c) {
    //       o << c.pt << " " << c.rise << " " << c.count;
    //       return o;
    //     }

    //when scanning Vertex45 for polygon formation we need a scanline comparator functor
    class lessVertex45 {
    private:
      Unit *x_; //x value at which to apply comparison
      int *justBefore_;
    public:
      inline lessVertex45() : x_(0), justBefore_() {}

      inline lessVertex45(Unit *x, int *justBefore) : x_(x), justBefore_(justBefore) {}

      inline lessVertex45(const lessVertex45& that) : x_(that.x_), justBefore_(that.justBefore_) {}

      inline lessVertex45& operator=(const lessVertex45& that) { x_ = that.x_; justBefore_ = that.justBefore_; return *this; }

      template <typename ct>
      inline bool operator () (const Vertex45T<ct>& elm1, const Vertex45T<ct>& elm2) const {
        Unit y1 = elm1.evalAtX(*x_);
        Unit y2 = elm2.evalAtX(*x_);
        if(y1 < y2) return true;
        if(y1 == y2) {
          //if justBefore is true we invert the result of the comparison of slopes
          if(*justBefore_) {
            return elm1.rise > elm2.rise;
          } else {
            return elm1.rise < elm2.rise;
          }
        }
        return false;
      }
    };

    // 0 right to left
    // 1 upper right to lower left
    // 2 high to low
    // 3 upper left to lower right
    // 4 left to right
    // 5 lower left to upper right
    // 6 low to high
    // 7 lower right to upper left
    static inline int classifyEdge45(const Point& prevPt, const Point& nextPt) {
      if(prevPt.x() == nextPt.x()) {
        //2 or 6
        return predicated_value(prevPt.y() < nextPt.y(), 6, 2);
      }
      if(prevPt.y() == nextPt.y()) {
        //0 or 4
        return predicated_value(prevPt.x() < nextPt.x(), 4, 0);
      }
      if(prevPt.x() < nextPt.x()) {
        //3 or 5
        return predicated_value(prevPt.y() < nextPt.y(), 5, 3);
      }
      //prevPt.x() > nextPt.y()
      //1 or 7
      return predicated_value(prevPt.y() < nextPt.y(), 7, 1);
    }

    template <int op, typename CountType>
    static int applyLogic(CountType count1, CountType count2){
      bool l1 = applyLogic<op>(count1);
      bool l2 = applyLogic<op>(count2);
      if(l1 && !l2)
        return -1; //was true before and became false like a trailing edge
      if(!l1 && l2)
        return 1; //was false before and became true like a leading edge
      return 0; //no change in logic between the two counts
    }
    template <int op>
    static bool applyLogic(Count2 count) {
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op == 0) { //apply or
        return count[0] > 0 || count[1] > 0;
      } else if(op == 1) { //apply and
        return count[0] > 0 && count[1] > 0;
      } else if(op == 2) { //apply not
        return count[0] > 0 && !(count[1] > 0);
      } else if(op == 3) { //apply xor
        return (count[0] > 0) ^ (count[1] > 0);
      } else
        return false;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

    template <int op>
    struct boolean_op_45_output_functor {
      template <typename cT>
      void operator()(cT& output, const Count2& count1, const Count2& count2,
                      const Point& pt, int rise, direction_1d end) {
        int edgeType = applyLogic<op>(count1, count2);
        if(edgeType) {
          int multiplier = end == LOW ? -1 : 1;
          //std::cout << "cross logic: " << edgeType << "\n";
          output.insert(output.end(), Vertex45(pt, rise, edgeType * multiplier));
          //std::cout << "write out: " << crossPoint << " " << Point(eraseItrs[i]->x, eraseItrs[i]->y) << "\n";
        }
      }
    };

    template <int op>
    static bool applyLogic(Count1 count) {
#ifdef BOOST_POLYGON_MSVC
#pragma warning (push)
#pragma warning (disable: 4127)
#endif
      if(op == 0) { //apply or
        return count.count_ > 0;
      } else if(op == 1) { //apply and
        return count.count_ > 1;
      } else if(op == 3) { //apply xor
        return (count.count_ % 2) != 0;
      } else
        return false;
#ifdef BOOST_POLYGON_MSVC
#pragma warning (pop)
#endif
    }

    template <int op>
    struct unary_op_45_output_functor {
      template <typename cT>
      void operator()(cT& output, const Count1& count1, const Count1& count2,
                      const Point& pt, int rise, direction_1d end) {
        int edgeType = applyLogic<op>(count1, count2);
        if(edgeType) {
          int multiplier = end == LOW ? -1 : 1;
          //std::cout << "cross logic: " << edgeType << "\n";
          output.insert(output.end(), Vertex45(pt, rise, edgeType * multiplier));
          //std::cout << "write out: " << crossPoint << " " << Point(eraseItrs[i]->x, eraseItrs[i]->y) << "\n";
        }
      }
    };

    class lessScan45Vertex {
    public:
      inline lessScan45Vertex() {} //default constructor is only constructor
      template <typename Scan45Vertex>
      inline bool operator () (const Scan45Vertex& v1, const Scan45Vertex& v2) const {
        return (v1.first.x() < v2.first.x()) || (v1.first.x() == v2.first.x() && v1.first.y() < v2.first.y());
      }
    };
    template <typename S45V>
    static inline void sortScan45Vector(S45V& vec) {
      polygon_sort(vec.begin(), vec.end(), lessScan45Vertex());
    }

    template <typename CountType, typename output_functor>
    class Scan45 {
    public:
      typedef Scan45CountT<CountType> Scan45Count;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;

      //index is the index into the vertex
      static inline Scan45Element getElement(const Scan45Vertex& vertex, int index) {
        return Scan45Element(vertex.first.x(), vertex.first.y(), index - 1, vertex.second[index]);
      }

      class lessScan45Point {
      public:
      typedef Point first_argument_type;
      typedef Point second_argument_type;
      typedef bool result_type;
        inline lessScan45Point() {} //default constructor is only constructor
        inline bool operator () (const Point& v1, const Point& v2) const {
          return (v1.x() < v2.x()) || (v1.x() == v2.x() && v1.y() < v2.y());
        }
      };

      typedef std::vector<Scan45Vertex> Scan45Vector;

      //definitions
      typedef std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> > Scan45Data;
      typedef typename Scan45Data::iterator iterator;
      typedef typename Scan45Data::const_iterator const_iterator;
      typedef std::set<Point, lessScan45Point> CrossQueue;

      //data
      Scan45Data scanData_;
      CrossQueue crossQueue_;
      Scan45Vector crossVector_;
      Unit x_;
      int justBefore_;
    public:
      inline Scan45() : scanData_(), crossQueue_(), crossVector_(),
                        x_((std::numeric_limits<Unit>::min)()), justBefore_(false) {
        lessScan45Element<CountType>  lessElm(&x_, &justBefore_);
        scanData_ = std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> >(lessElm);
      }
      inline Scan45(const Scan45& that) : scanData_(), crossQueue_(), crossVector_(),
                                          x_((std::numeric_limits<Unit>::min)()), justBefore_(false) {
        (*this) = that; }
      inline Scan45& operator=(const Scan45& that) {
        x_ = that.x_;
        justBefore_ = that.justBefore_;
        crossQueue_ = that.crossQueue_;
        crossVector_ = that.crossVector_;
        lessScan45Element<CountType>  lessElm(&x_, &justBefore_);
        scanData_ = std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> >(lessElm);
        for(const_iterator itr = that.scanData_.begin(); itr != that.scanData_.end(); ++itr){
          scanData_.insert(scanData_.end(), *itr);
        }
        return *this;
      }

      //cT is an output container of Vertex45
      //iT is an iterator over Scan45Vertex elements
      template <class cT, class iT>
      void scan(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "1\n";
        while(inputBegin != inputEnd) {
          //std::cout << "2\n";
          //std::cout << "x_ = " << x_ << "\n";
          //std::cout << "scan line size: " << scanData_.size() << "\n";
          //for(iterator iter = scanData_.begin();
          //     iter != scanData_.end(); ++iter) {
          //   std::cout << "scan element\n";
          //   std::cout << *iter << " " << iter->evalAtX(x_) << "\n";
          // }
          // std::cout << "cross queue size: " << crossQueue_.size() << "\n";
          // std::cout << "cross vector size: " << crossVector_.size() << "\n";
          //for(CrossQueue::iterator cqitr = crossQueue_.begin(); cqitr != crossQueue_.end(); ++cqitr) {
          //   std::cout << *cqitr << " ";
          //} std::cout << "\n";
          Unit nextX = (*inputBegin).first.x();
          if(!crossVector_.empty() && crossVector_[0].first.x() < nextX) nextX = crossVector_[0].first.x();
          if(nextX != x_) {
            //std::cout << "3\n";
            //we need to move to the next scanline stop
            //we need to process end events then cross events
            //process end events
            if(!crossQueue_.empty() &&
               (*crossQueue_.begin()).x() < nextX) {
              //std::cout << "4\n";
              nextX = (std::min)(nextX, (*crossQueue_.begin()).x());
            }
            //std::cout << "6\n";
            justBefore_ = true;
            x_ = nextX;
            advance_(output);
            justBefore_ = false;
            if(!crossVector_.empty() &&
               nextX == (*inputBegin).first.x()) {
              inputBegin = mergeCross_(inputBegin, inputEnd);
            }
            processEvent_(output, crossVector_.begin(), crossVector_.end());
            crossVector_.clear();
          } else {
            //std::cout << "7\n";
            //our scanline has progressed to the event that is next in the queue
            inputBegin = processEvent_(output, inputBegin, inputEnd);
          }
        }
        //std::cout << "done scanning\n";
      }

    private:
      //functions

      template <class cT>
      inline void advance_(cT& output) {
        //process all cross points on the cross queue at the current x_
        //std::cout << "advance_\n";
        std::vector<iterator> eraseVec;
        while(!crossQueue_.empty() &&
              (*crossQueue_.begin()).x() == x_){
          //std::cout << "loop\n";
          //pop point off the cross queue
          Point crossPoint = *(crossQueue_.begin());
          //std::cout << crossPoint << "\n";
          //for(iterator iter = scanData_.begin();
          //    iter != scanData_.end(); ++iter) {
          //  std::cout << "scan element\n";
          //  std::cout << *iter << " " << iter->evalAtX(x_) << "\n";
          //}
          crossQueue_.erase(crossQueue_.begin());
          Scan45Vertex vertex(crossPoint, Scan45Count());
          iterator lowIter = lookUp_(vertex.first.y());
          //std::cout << "searching at: " << vertex.first.y() << "\n";
          //if(lowIter == scanData_.end()) std::cout << "could not find\n";
          //else std::cout << "found: " << *lowIter << "\n";
          if(lowIter == scanData_.end() ||
             lowIter->evalAtX(x_) != vertex.first.y()) {
            //   std::cout << "skipping\n";
            //there weren't any edges at this potential cross point
            continue;
          }
          CountType countBelow;
          iterator searchDownItr = lowIter;
          while(searchDownItr != scanData_.begin()
                && searchDownItr->evalAtX(x_) == vertex.first.y()) {
            //get count from below
            --searchDownItr;
            countBelow = searchDownItr->count;
          }
          //std::cout << "Below Count: " << countBelow << "\n";
          Scan45Count count(countBelow);
          std::size_t numEdges = 0;
          iterator eraseItrs[3];
          while(lowIter != scanData_.end() &&
                lowIter->evalAtX(x_) == vertex.first.y()) {
            for(int index = lowIter->rise +1; index >= 0; --index)
              count[index] = lowIter->count;
            //std::cout << count << "\n";
            eraseItrs[numEdges] = lowIter;
            ++numEdges;
            ++lowIter;
          }
          if(numEdges == 1) {
            //look for the next crossing point and continue
            //std::cout << "found only one edge\n";
            findCross_(eraseItrs[0]);
            continue;
          }
          //before we erase the elements we need to decide if they should be written out
          CountType currentCount = countBelow;
          for(std::size_t i = 0; i < numEdges; ++i) {
            output_functor f;
            f(output, currentCount, eraseItrs[i]->count, crossPoint, eraseItrs[i]->rise, LOW);
            currentCount = eraseItrs[i]->count;
          }
          //schedule erase of the elements
          for(std::size_t i = 0; i < numEdges; ++i) {
            eraseVec.push_back(eraseItrs[i]);
          }

          //take the derivative wrt theta of the count at the crossing point
          vertex.second[2] = count[2] - countBelow;
          vertex.second[1] = count[1] - count[2];
          vertex.second[0] = count[0] - count[1];
          //add the point, deriviative pair into the cross vector
          //std::cout << "LOOK HERE!\n";
          //std::cout << count << "\n";
          //std::cout << vertex << "\n";
          crossVector_.push_back(vertex);
        }
        //erase crossing elements
        std::vector<iterator> searchVec;
        for(std::size_t i = 0; i < eraseVec.size(); ++i) {
          if(eraseVec[i] != scanData_.begin()) {
            iterator searchItr = eraseVec[i];
            --searchItr;
            if(searchVec.empty() ||
               searchVec.back() != searchItr)
              searchVec.push_back(searchItr);
          }
          scanData_.erase(eraseVec[i]);
        }
        for(std::size_t i = 0; i < searchVec.size(); ++i) {
          findCross_(searchVec[i]);
        }
      }

      template <class iT>
      inline iT mergeCross_(iT inputBegin, iT inputEnd) {
        Scan45Vector vec;
        swap(vec, crossVector_);
        iT mergeEnd = inputBegin;
        std::size_t mergeCount = 0;
        while(mergeEnd != inputEnd &&
              (*mergeEnd).first.x() == x_) {
          ++mergeCount;
          ++mergeEnd;
        }
        crossVector_.reserve((std::max)(vec.capacity(), vec.size() + mergeCount));
        for(std::size_t i = 0; i < vec.size(); ++i){
          while(inputBegin != mergeEnd &&
                (*inputBegin).first.y() < vec[i].first.y()) {
            crossVector_.push_back(*inputBegin);
            ++inputBegin;
          }
          crossVector_.push_back(vec[i]);
        }
        while(inputBegin != mergeEnd){
          crossVector_.push_back(*inputBegin);
          ++inputBegin;
        }
        return inputBegin;
      }

      template <class cT, class iT>
      inline iT processEvent_(cT& output, iT inputBegin, iT inputEnd) {
        //std::cout << "processEvent_\n";
        CountType verticalCount = CountType();
        Point prevPoint;
        iterator prevIter = scanData_.end();
        while(inputBegin != inputEnd &&
              (*inputBegin).first.x() == x_) {
          //std::cout << (*inputBegin) << "\n";
          //std::cout << "loop\n";
          Scan45Vertex vertex = *inputBegin;
          //std::cout << vertex.first << "\n";
          //if vertical count propigating up fake a null event at the next element
          if(verticalCount != CountType() && (prevIter != scanData_.end() &&
                                              prevIter->evalAtX(x_) < vertex.first.y())) {
            //std::cout << "faking null event\n";
            vertex = Scan45Vertex(Point(x_, prevIter->evalAtX(x_)), Scan45Count());
          } else {
            ++inputBegin;
            //std::cout << "after increment\n";
            //accumulate overlapping changes in Scan45Count
            while(inputBegin != inputEnd &&
                  (*inputBegin).first.x() == x_ &&
                  (*inputBegin).first.y() == vertex.first.y()) {
              //std::cout << "accumulate\n";
              vertex.second += (*inputBegin).second;
              ++inputBegin;
            }
          }
          //std::cout << vertex.second << "\n";
          //integrate vertex
          CountType currentCount = verticalCount;// + vertex.second[0];
          for(unsigned int i = 0; i < 3; ++i) {
            vertex.second[i] = currentCount += vertex.second[i];
          }
          //std::cout << vertex.second << "\n";
          //vertex represents the change in state at this point

          //get counts at current vertex
          CountType countBelow;
          iterator lowIter = lookUp_(vertex.first.y());
          if(lowIter != scanData_.begin()) {
            //get count from below
            --lowIter;
            countBelow = lowIter->count;
            ++lowIter;
          }
          //std::cout << "Count Below: " << countBelow[0] << " " << countBelow[1] << "\n";
          //std::cout << "vertical count: " << verticalCount[0] << " " << verticalCount[1] << "\n";
          Scan45Count countAt(countBelow - verticalCount);
          //check if the vertical edge should be written out
          if(verticalCount != CountType()) {
            output_functor f;
            f(output, countBelow - verticalCount, countBelow, prevPoint, 2, HIGH);
            f(output, countBelow - verticalCount, countBelow, vertex.first, 2, LOW);
          }
          currentCount = countBelow - verticalCount;
          while(lowIter != scanData_.end() &&
                lowIter->evalAtX(x_) == vertex.first.y()) {
            for(unsigned int i = lowIter->rise + 1; i < 3; ++i) {
              countAt[i] = lowIter->count;
            }
            Point lp(lowIter->x, lowIter->y);
            if(lp != vertex.first) {
              output_functor f;
              f(output, currentCount, lowIter->count, vertex.first, lowIter->rise, LOW);
            }
            currentCount = lowIter->count;
            iterator nextIter = lowIter;
            ++nextIter;
            //std::cout << "erase\n";
            scanData_.erase(lowIter);
            if(nextIter != scanData_.end())
              findCross_(nextIter);
            lowIter = nextIter;
          }
          verticalCount += vertex.second[3];
          prevPoint = vertex.first;
          //std::cout << "new vertical count: " << verticalCount[0] << " " << verticalCount[1] << "\n";
          prevIter = lowIter;
          //count represents the current state at this point
          //std::cout << vertex.second << "\n";
          //std::cout << countAt << "\n";
          //std::cout << "ADD\n";
          vertex.second += countAt;
          //std::cout << vertex.second << "\n";

          //add elements to the scanline
          for(int i = 0; i < 3; ++i) {
            if(vertex.second[i] != countBelow) {
              //std::cout << "insert: " << vertex.first.x() << " " << vertex.first.y() << " " << i-1 <<
              //  " " << vertex.second[i][0] << " " << vertex.second[i][1] << "\n";
              iterator insertIter = scanData_.insert(scanData_.end(),
                                                     Scan45ElementT<CountType>(vertex.first.x(),
                                                                               vertex.first.y(),
                                                                               i - 1, vertex.second[i]));
              findCross_(insertIter);
              output_functor f;
              f(output, countBelow, vertex.second[i], vertex.first, i - 1, HIGH);
            }
            countBelow = vertex.second[i];
          }
        }
        //std::cout << "end processEvent\n";
        return inputBegin;
      }

      //iter1 is horizontal
      inline void scheduleCross0_(iterator iter1, iterator iter2) {
        //std::cout << "0, ";
        Unit y1 = iter1->evalAtX(x_);
        Unit y2 = iter2->evalAtX(x_);
        LongUnit delta = local_abs(LongUnit(y1) - LongUnit(y2));
        if(delta + static_cast<LongUnit>(x_) <= (std::numeric_limits<Unit>::max)())
          crossQueue_.insert(crossQueue_.end(), Point(x_ + static_cast<Unit>(delta), y1));
        //std::cout <<  Point(x_ + delta, y1);
      }

      //neither iter is horizontal
      inline void scheduleCross1_(iterator iter1, iterator iter2) {
        //std::cout << "1, ";
        Unit y1 = iter1->evalAtX(x_);
        Unit y2 = iter2->evalAtX(x_);
        //std::cout << y1 << " " << y2 << ": ";
        //note that half the delta cannot exceed the positive inter range
        LongUnit delta = y1;
        delta -= y2;
        Unit UnitMax = (std::numeric_limits<Unit>::max)();
        if((delta & 1) == 1) {
          //delta is odd, division by 2 will result in integer trunctaion
          if(delta == 1) {
            //the cross point is not on the integer grid and cannot be represented
            //we must throw an exception
            std::string msg = "GTL 45 Boolean error, precision insufficient to represent edge intersection coordinate value.";
            throw(msg);
          } else {
            //note that result of this subtraction is always positive because itr1 is above itr2 in scanline
            LongUnit halfDelta2 = (LongUnit)((((LongUnit)y1) - y2)/2);
            //note that halfDelta2 has been truncated
            if(halfDelta2 + x_ <= UnitMax && halfDelta2 + y2 <= UnitMax) {
              crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta2), y2+static_cast<Unit>(halfDelta2)));
              crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta2), y2+static_cast<Unit>(halfDelta2)+1));
            }
          }
        } else {
          LongUnit halfDelta = (LongUnit)((((LongUnit)y1) - y2)/2);
          if(halfDelta + x_ <= UnitMax && halfDelta + y2 <= UnitMax)
            crossQueue_.insert(crossQueue_.end(), Point(x_+static_cast<Unit>(halfDelta), y2+static_cast<Unit>(halfDelta)));
          //std::cout << Point(x_+halfDelta, y2+halfDelta);
        }
      }

      inline void findCross_(iterator iter) {
        //std::cout << "find cross ";
        iterator iteratorBelow = iter;
        iterator iteratorAbove = iter;
        if(iter != scanData_.begin() && iter->rise < 1) {
          --iteratorBelow;
          if(iter->rise == 0){
            if(iteratorBelow->rise == 1) {
              scheduleCross0_(iter, iteratorBelow);
            }
          } else {
            //iter->rise == -1
            if(iteratorBelow->rise == 1) {
              scheduleCross1_(iter, iteratorBelow);
            } else if(iteratorBelow->rise == 0) {
              scheduleCross0_(iteratorBelow, iter);
            }
          }
        }
        ++iteratorAbove;
        if(iteratorAbove != scanData_.end() && iter->rise > -1) {
          if(iter->rise == 0) {
            if(iteratorAbove->rise == -1) {
              scheduleCross0_(iter, iteratorAbove);
            }
          } else {
            //iter->rise == 1
            if(iteratorAbove->rise == -1) {
              scheduleCross1_(iteratorAbove, iter);
            } else if(iteratorAbove->rise == 0) {
              scheduleCross0_(iteratorAbove, iter);
            }
          }
        }
        //std::cout << "\n";
      }

      inline iterator lookUp_(Unit y){
        //if just before then we need to look from 1 not -1
        return scanData_.lower_bound(Scan45ElementT<CountType>(x_, y, -1+2*justBefore_));
      }
    };

    //template <typename CountType>
    //static inline void print45Data(const std::set<Scan45ElementT<CountType>,
    //                               lessScan45Element<CountType> >& data) {
    //  typename std::set<Scan45ElementT<CountType>, lessScan45Element<CountType> >::const_iterator iter;
    //  for(iter = data.begin(); iter != data.end(); ++iter) {
    //    std::cout << iter->x << " " << iter->y << " " << iter->rise << "\n";
    //  }
    //}

    template <typename streamtype>
    static inline bool testScan45Data(streamtype& stdcout) {
      Unit x = 0;
      int justBefore = false;
      lessScan45Element<Count2> lessElm(&x, &justBefore);
      std::set<Scan45ElementT<Count2>, lessScan45Element<Count2> > testData(lessElm);
      //Unit size = testData.size();
      typedef std::set<Scan45ElementT<Count2>, lessScan45Element<Count2> > Scan45Data;
      typename Scan45Data::iterator itr10 = testData.insert(testData.end(), Scan45Element(0, 10, 1));
      typename Scan45Data::iterator itr20 = testData.insert(testData.end(), Scan45Element(0, 20, 1));
      typename Scan45Data::iterator itr30 = testData.insert(testData.end(), Scan45Element(0, 30, -1));
      typename Scan45Data::iterator itr40 = testData.insert(testData.end(), Scan45Element(0, 40, -1));
      typename Scan45Data::iterator itrA = testData.lower_bound(Scan45Element(0, 29, -1));
      typename Scan45Data::iterator itr1 = testData.lower_bound(Scan45Element(0, 10, -1));
      x = 4;
      //now at 14 24 26 36
      typename Scan45Data::iterator itrB = testData.lower_bound(Scan45Element(4, 29, -1));
      typename Scan45Data::iterator itr2 = testData.lower_bound(Scan45Element(4, 14, -1));
      if(itr1 != itr2) stdcout << "test1 failed\n";
      if(itrA == itrB) stdcout << "test2 failed\n";
      //remove crossing elements
      testData.erase(itr20);
      testData.erase(itr30);
      x = 5;
      itr20 = testData.insert(testData.end(), Scan45Element(0, 20, 1));
      itr30 = testData.insert(testData.end(), Scan45Element(0, 30, -1));
      //now at 15 25 25 35
      typename Scan45Data::iterator itr = testData.begin();
      if(itr != itr10) stdcout << "test3 failed\n";
      ++itr;
      if(itr != itr30) stdcout << "test4 failed\n";
      ++itr;
      if(itr != itr20) stdcout << "test5 failed\n";
      ++itr;
      if(itr != itr40) stdcout << "test6 failed\n";
      stdcout << "done testing Scan45Data\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45Rect(stream_type& stdcout) {
      stdcout << "testing Scan45Rect\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 0 1
      // result == 0 0 2 1
      // result == 0 10 2 -1
      // result == 0 10 0 -1
      // result == 10 0 0 -1
      // result == 10 0 2 -1
      // result == 10 10 2 1
      // result == 10 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 0, 1));
      reference.push_back(Vertex45(Point(0, 0), 2, 1));
      reference.push_back(Vertex45(Point(0, 10), 2, -1));
      reference.push_back(Vertex45(Point(0, 10), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 2, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //std::cout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //std::cout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45Rect\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45P1(stream_type& stdcout) {
      stdcout << "testing Scan45P1\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), Count2(0, 0), ncount, ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), Count2(0, 0), ncount, ncount)));
      vertices.push_back(Scan45Vertex(Point(10,20), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 1 1
      // result == 0 0 2 1
      // result == 0 10 2 -1
      // result == 0 10 1 -1
      // result == 10 10 1 -1
      // result == 10 10 2 -1
      // result == 10 20 2 1
      // result == 10 20 1 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 1, 1));
      reference.push_back(Vertex45(Point(0, 0), 2, 1));
      reference.push_back(Vertex45(Point(0, 10), 2, -1));
      reference.push_back(Vertex45(Point(0, 10), 1, -1));
      reference.push_back(Vertex45(Point(10, 10), 1, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, -1));
      reference.push_back(Vertex45(Point(10, 20), 2, 1));
      reference.push_back(Vertex45(Point(10, 20), 1, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //std::cout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //std::cout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45P1\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45P2(stream_type& stdcout) {
      stdcout << "testing Scan45P2\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, count, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), ncount, count, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(20,10), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 8
      // result == 0 0 0 1
      // result == 0 0 1 -1
      // result == 10 0 0 -1
      // result == 10 0 1 1
      // result == 10 10 1 1
      // result == 10 10 0 -1
      // result == 20 10 1 -1
      // result == 20 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(0, 0), 0, 1));
      reference.push_back(Vertex45(Point(0, 0), 1, -1));
      reference.push_back(Vertex45(Point(10, 0), 0, -1));
      reference.push_back(Vertex45(Point(10, 0), 1, 1));
      reference.push_back(Vertex45(Point(10, 10), 1, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, -1));
      reference.push_back(Vertex45(Point(20, 10), 1, -1));
      reference.push_back(Vertex45(Point(20, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //stdcout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //stdcout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45P2\n";
      return true;
    }

    template <typename streamtype>
    static inline bool testScan45And(streamtype& stdcout) {
      stdcout << "testing Scan45And\n";
      Scan45<Count2, boolean_op_45_output_functor<1> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,10), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(10,10), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(2,2), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(2,12), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,2), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,12), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      //result size == 8
      //result == 2 2 0 1
      //result == 2 2 2 1
      //result == 2 10 2 -1
      //result == 2 10 0 -1
      //result == 10 2 0 -1
      //result == 10 2 2 -1
      //result == 10 10 2 1
      //result == 10 10 0 1
      std::vector<Vertex45> reference;
      reference.push_back(Vertex45(Point(2, 2), 0, 1));
      reference.push_back(Vertex45(Point(2, 2), 2, 1));
      reference.push_back(Vertex45(Point(2, 10), 2, -1));
      reference.push_back(Vertex45(Point(2, 10), 0, -1));
      reference.push_back(Vertex45(Point(10, 2), 0, -1));
      reference.push_back(Vertex45(Point(10, 2), 2, -1));
      reference.push_back(Vertex45(Point(10, 10), 2, 1));
      reference.push_back(Vertex45(Point(10, 10), 0, 1));
      if(result != reference) {
        stdcout << "result size == " << result.size() << "\n";
        for(std::size_t i = 0; i < result.size(); ++i) {
          //stdcout << "result == " << result[i]<< "\n";
        }
        stdcout << "reference size == " << reference.size() << "\n";
        for(std::size_t i = 0; i < reference.size(); ++i) {
          //stdcout << "reference == " << reference[i]<< "\n";
        }
        return false;
      }
      stdcout << "done testing Scan45And\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45Star1(stream_type& stdcout) {
      stdcout << "testing Scan45Star1\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(8,16), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(12,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(4,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(4,16), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 24
      // result == 0 8 -1 1
      // result == 0 8 1 -1
      // result == 4 0 1 1
      // result == 4 0 2 1
      // result == 4 4 2 -1
      // result == 4 4 -1 -1
      // result == 4 12 1 1
      // result == 4 12 2 1
      // result == 4 16 2 -1
      // result == 4 16 -1 -1
      // result == 6 2 1 -1
      // result == 6 14 -1 1
      // result == 6 2 -1 1
      // result == 6 14 1 -1
      // result == 8 0 -1 -1
      // result == 8 0 2 -1
      // result == 8 4 2 1
      // result == 8 4 1 1
      // result == 8 12 -1 -1
      // result == 8 12 2 -1
      // result == 8 16 2 1
      // result == 8 16 1 1
      // result == 12 8 1 -1
      // result == 12 8 -1 1
      if(result.size() != 24) {
        //stdcout << "result size == " << result.size() << "\n";
        //stdcout << "reference size == " << 24 << "\n";
        return false;
      }
      stdcout << "done testing Scan45Star1\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45Star2(stream_type& stdcout) {
      stdcout << "testing Scan45Star2\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 24
      // result == 0 4 0 1
      // result == 0 4 1 -1
      // result == 0 8 -1 1
      // result == 0 8 0 -1
      // result == 2 6 1 1
      // result == 2 6 -1 -1
      // result == 4 4 0 -1
      // result == 4 8 0 1
      // result == 4 4 -1 1
      // result == 4 8 1 -1
      // result == 8 0 -1 -1
      // result == 8 0 1 1
      // result == 8 12 1 1
      // result == 8 12 -1 -1
      // result == 12 4 1 -1
      // result == 12 8 -1 1
      // result == 12 4 0 1
      // result == 12 8 0 -1
      // result == 14 6 -1 -1
      // result == 14 6 1 1
      // result == 16 4 0 -1
      // result == 16 4 -1 1
      // result == 16 8 1 -1
      // result == 16 8 0 1
      if(result.size() != 24) {
        //std::cout << "result size == " << result.size() << "\n";
        //std::cout << "reference size == " << 24 << "\n";
        return false;
      }
      stdcout << "done testing Scan45Star2\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45Star3(stream_type& stdcout) {
      stdcout << "testing Scan45Star3\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(8,16), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));

      vertices.push_back(Scan45Vertex(Point(6,0), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(6,14), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,0), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(12,14), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(12,8), Scan45Count(count, Count2(0, 0), ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(4,0), Scan45Count(Count2(0, 0), Count2(0, 0), count, count)));
      vertices.push_back(Scan45Vertex(Point(4,16), Scan45Count(ncount, Count2(0, 0), Count2(0, 0), ncount)));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 28
      // result == 0 8 -1 1
      // result == 0 8 1 -1
      // result == 4 0 1 1
      // result == 4 0 2 1
      // result == 4 4 2 -1
      // result == 4 4 -1 -1
      // result == 4 12 1 1
      // result == 4 12 2 1
      // result == 4 16 2 -1
      // result == 4 16 -1 -1
      // result == 6 2 1 -1
      // result == 6 14 -1 1
      // result == 6 0 0 1
      // result == 6 0 2 1
      // result == 6 2 2 -1
      // result == 6 14 1 -1
      // result == 8 0 0 -1
      // result == 8 0 0 1
      // result == 8 14 0 -1
      // result == 8 14 2 -1
      // result == 8 16 2 1
      // result == 8 16 1 1
      // result == 12 0 0 -1
      // result == 12 0 2 -1
      // result == 12 8 2 1
      // result == 12 8 2 -1
      // result == 12 14 2 1
      // result == 12 14 0 1
      if(result.size() != 28) {
        //std::cout << "result size == " << result.size() << "\n";
        //std::cout << "reference size == " << 28 << "\n";
        return false;
      }

      stdcout << "done testing Scan45Star3\n";
      return true;
    }


    template <typename stream_type>
    static inline bool testScan45Star4(stream_type& stdcout) {
      stdcout << "testing Scan45Star4\n";
      Scan45<Count2, boolean_op_45_output_functor<0> > scan45;
      std::vector<Vertex45 > result;
      typedef std::pair<Point, Scan45Count> Scan45Vertex;
      std::vector<Scan45Vertex> vertices;
      //is a Rectnagle(0, 0, 10, 10);
      Count2 count(1, 0);
      Count2 ncount(-1, 0);
      vertices.push_back(Scan45Vertex(Point(0,4), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,4), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,12), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));

      vertices.push_back(Scan45Vertex(Point(0,6), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      vertices.push_back(Scan45Vertex(Point(0,12), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(16,6), Scan45Count(Count2(0, 0), ncount, Count2(0, 0), ncount)));
      vertices.push_back(Scan45Vertex(Point(16,12), Scan45Count(Count2(0, 0), count, Count2(0, 0), count)));
      count = Count2(0, 1);
      ncount = count.invert();
      vertices.push_back(Scan45Vertex(Point(0,8), Scan45Count(count, ncount, Count2(0, 0), Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(16,8), Scan45Count(Count2(0, 0), count, ncount, Count2(0, 0))));
      vertices.push_back(Scan45Vertex(Point(8,0), Scan45Count(ncount, Count2(0, 0), count, Count2(0, 0))));
      sortScan45Vector(vertices);
      stdcout << "scanning\n";
      scan45.scan(result, vertices.begin(), vertices.end());
      stdcout << "done scanning\n";
      // result size == 28
      // result == 0 4 0 1
      // result == 0 4 1 -1
      // result == 0 6 0 1
      // result == 0 6 2 1
      // result == 0 8 2 -1
      // result == 0 8 2 1
      // result == 0 12 2 -1
      // result == 0 12 0 -1
      // result == 2 6 1 1
      // result == 2 6 0 -1
      // result == 4 4 0 -1
      // result == 4 4 -1 1
      // result == 8 12 0 1
      // result == 8 0 -1 -1
      // result == 8 0 1 1
      // result == 8 12 0 -1
      // result == 12 4 1 -1
      // result == 12 4 0 1
      // result == 14 6 -1 -1
      // result == 14 6 0 1
      // result == 16 4 0 -1
      // result == 16 4 -1 1
      // result == 16 6 0 -1
      // result == 16 6 2 -1
      // result == 16 8 2 1
      // result == 16 8 2 -1
      // result == 16 12 2 1
      // result == 16 12 0 1
      if(result.size() != 28) {
        //stdcout << "result size == " << result.size() << "\n";
        //stdcout << "reference size == " << 28 << "\n";
        return false;
      }

      stdcout << "done testing Scan45Star4\n";
      return true;
    }

    template <typename stream_type>
    static inline bool testScan45(stream_type& stdcout) {
      if(!testScan45Rect(stdcout)) return false;
      if(!testScan45P1(stdcout)) return false;
      if(!testScan45P2(stdcout)) return false;
      if(!testScan45And(stdcout)) return false;
      if(!testScan45Star1(stdcout)) return false;
      if(!testScan45Star2(stdcout)) return false;
      if(!testScan45Star3(stdcout)) return false;
      if(!testScan45Star4(stdcout)) return false;
      return true;
    }

  };

}

}
#endif

/* boolean_op_45.hpp
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
*/