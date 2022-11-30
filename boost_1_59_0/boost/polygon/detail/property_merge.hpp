/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_PROPERTY_MERGE_HPP
#define BOOST_POLYGON_PROPERTY_MERGE_HPP
namespace boost { namespace polygon{

template <typename coordinate_type>
class property_merge_point {
private:
  coordinate_type x_, y_;
public:
  inline property_merge_point() : x_(), y_() {}
  inline property_merge_point(coordinate_type x, coordinate_type y) : x_(x), y_(y) {}
  //use builtin assign and copy
  inline bool operator==(const property_merge_point& that) const { return x_ == that.x_ && y_ == that.y_; }
  inline bool operator!=(const property_merge_point& that) const { return !((*this) == that); }
  inline bool operator<(const property_merge_point& that) const {
    if(x_ < that.x_) return true;
    if(x_ > that.x_) return false;
    return y_ < that.y_;
  }
  inline coordinate_type x() const { return x_; }
  inline coordinate_type y() const { return y_; }
  inline void x(coordinate_type value) { x_ = value; }
  inline void y(coordinate_type value) { y_ = value; }
};

template <typename coordinate_type>
class property_merge_interval {
private:
  coordinate_type low_, high_;
public:
  inline property_merge_interval() : low_(), high_() {}
  inline property_merge_interval(coordinate_type low, coordinate_type high) : low_(low), high_(high) {}
  //use builtin assign and copy
  inline bool operator==(const property_merge_interval& that) const { return low_ == that.low_ && high_ == that.high_; }
  inline bool operator!=(const property_merge_interval& that) const { return !((*this) == that); }
  inline bool operator<(const property_merge_interval& that) const {
    if(low_ < that.low_) return true;
    if(low_ > that.low_) return false;
    return high_ < that.high_;
  }
  inline coordinate_type low() const { return low_; }
  inline coordinate_type high() const { return high_; }
  inline void low(coordinate_type value) { low_ = value; }
  inline void high(coordinate_type value) { high_ = value; }
};

template <typename coordinate_type, typename property_type, typename polygon_set_type, typename keytype = std::set<property_type> >
class merge_scanline {
public:
  //definitions

  typedef keytype property_set;
  typedef std::vector<std::pair<property_type, int> > property_map;
  typedef std::pair<property_merge_point<coordinate_type>, std::pair<property_type, int> > vertex_property;
  typedef std::pair<property_merge_point<coordinate_type>, property_map> vertex_data;
  typedef std::vector<vertex_property> property_merge_data;
  //typedef std::map<property_set, polygon_set_type> Result;
  typedef std::map<coordinate_type, property_map> scanline_type;
  typedef typename scanline_type::iterator scanline_iterator;
  typedef std::pair<property_merge_interval<coordinate_type>, std::pair<property_set, property_set> > edge_property;
  typedef std::vector<edge_property> edge_property_vector;

  //static public member functions

  template <typename iT, typename orientation_2d_type>
  static inline void
  populate_property_merge_data(property_merge_data& pmd, iT input_begin, iT input_end,
                               const property_type& property, orientation_2d_type orient) {
    for( ; input_begin != input_end; ++input_begin) {
      std::pair<property_merge_point<coordinate_type>, std::pair<property_type, int> > element;
      if(orient == HORIZONTAL)
        element.first = property_merge_point<coordinate_type>((*input_begin).second.first, (*input_begin).first);
      else
        element.first = property_merge_point<coordinate_type>((*input_begin).first, (*input_begin).second.first);
      element.second.first = property;
      element.second.second = (*input_begin).second.second;
      pmd.push_back(element);
    }
  }

  //public member functions

  merge_scanline() : output(), scanline(), currentVertex(), tmpVector(), previousY(), countFromBelow(), scanlinePosition() {}
  merge_scanline(const merge_scanline& that) :
    output(that.output),
    scanline(that.scanline),
    currentVertex(that.currentVertex),
    tmpVector(that.tmpVector),
    previousY(that.previousY),
    countFromBelow(that.countFromBelow),
    scanlinePosition(that.scanlinePosition)
  {}
  merge_scanline& operator=(const merge_scanline& that) {
    output = that.output;
    scanline = that.scanline;
    currentVertex = that.currentVertex;
    tmpVector = that.tmpVector;
    previousY = that.previousY;
    countFromBelow = that.countFromBelow;
    scanlinePosition = that.scanlinePosition;
    return *this;
  }

  template <typename result_type>
  inline void perform_merge(result_type& result, property_merge_data& data) {
    if(data.empty()) return;
    //sort
    polygon_sort(data.begin(), data.end(), less_vertex_data<vertex_property>());
    //scanline
    bool firstIteration = true;
    scanlinePosition = scanline.end();
    for(std::size_t i = 0; i < data.size(); ++i) {
      if(firstIteration) {
        mergeProperty(currentVertex.second, data[i].second);
        currentVertex.first = data[i].first;
        firstIteration = false;
      } else {
        if(data[i].first != currentVertex.first) {
          if(data[i].first.x() != currentVertex.first.x()) {
            processVertex(output);
            //std::cout << scanline.size() << " ";
            countFromBelow.clear(); //should already be clear
            writeOutput(currentVertex.first.x(), result, output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
            //std::cout << assertRedundant(scanline) << "/" << scanline.size() << " ";
          } else {
            processVertex(output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          }
        } else {
          mergeProperty(currentVertex.second, data[i].second);
        }
      }
    }
    processVertex(output);
    writeOutput(currentVertex.first.x(), result, output);
    //std::cout << assertRedundant(scanline) << "/" << scanline.size() << "\n";
    //std::cout << scanline.size() << "\n";
  }

private:
  //private supporting types

  template <class T>
  class less_vertex_data {
  public:
    less_vertex_data() {}
    bool operator()(const T& lvalue, const T& rvalue) const {
      if(lvalue.first.x() < rvalue.first.x()) return true;
      if(lvalue.first.x() > rvalue.first.x()) return false;
      if(lvalue.first.y() < rvalue.first.y()) return true;
      return false;
    }
  };

  template <typename T>
  struct lessPropertyCount {
    lessPropertyCount() {}
    bool operator()(const T& a, const T& b) {
      return a.first < b.first;
    }
  };

  //private static member functions

  static inline void mergeProperty(property_map& lvalue, std::pair<property_type, int>& rvalue) {
    typename property_map::iterator itr = std::lower_bound(lvalue.begin(), lvalue.end(), rvalue,
                                                          lessPropertyCount<std::pair<property_type, int> >());
    if(itr == lvalue.end() ||
       (*itr).first != rvalue.first) {
      lvalue.insert(itr, rvalue);
    } else {
      (*itr).second += rvalue.second;
      if((*itr).second == 0)
        lvalue.erase(itr);
    }
//     if(assertSorted(lvalue)) {
//       std::cout << "in mergeProperty\n";
//       exit(0);
//     }
  }

//   static inline bool assertSorted(property_map& pset) {
//     bool result = false;
//     for(std::size_t i = 1; i < pset.size(); ++i) {
//       if(pset[i] < pset[i-1]) {
//         std::cout << "Out of Order Error ";
//         result = true;
//       }
//       if(pset[i].first == pset[i-1].first) {
//         std::cout << "Duplicate Property Error ";
//         result = true;
//       }
//       if(pset[0].second == 0 || pset[1].second == 0) {
//         std::cout << "Empty Property Error ";
//         result = true;
//       }
//     }
//     return result;
//   }

  static inline void setProperty(property_set& pset, property_map& pmap) {
    for(typename property_map::iterator itr = pmap.begin(); itr != pmap.end(); ++itr) {
      if((*itr).second > 0) {
        pset.insert(pset.end(), (*itr).first);
      }
    }
  }

  //private data members

  edge_property_vector output;
  scanline_type scanline;
  vertex_data currentVertex;
  property_map tmpVector;
  coordinate_type previousY;
  property_map countFromBelow;
  scanline_iterator scanlinePosition;

  //private member functions

  inline void mergeCount(property_map& lvalue, property_map& rvalue) {
    typename property_map::iterator litr = lvalue.begin();
    typename property_map::iterator ritr = rvalue.begin();
    tmpVector.clear();
    while(litr != lvalue.end() && ritr != rvalue.end()) {
      if((*litr).first <= (*ritr).first) {
        if(!tmpVector.empty() &&
           (*litr).first == tmpVector.back().first) {
          tmpVector.back().second += (*litr).second;
        } else {
          tmpVector.push_back(*litr);
        }
        ++litr;
      } else if((*ritr).first <= (*litr).first) {
        if(!tmpVector.empty() &&
           (*ritr).first == tmpVector.back().first) {
          tmpVector.back().second += (*ritr).second;
        } else {
          tmpVector.push_back(*ritr);
        }
        ++ritr;
      }
    }
    while(litr != lvalue.end()) {
      if(!tmpVector.empty() &&
         (*litr).first == tmpVector.back().first) {
        tmpVector.back().second += (*litr).second;
      } else {
        tmpVector.push_back(*litr);
      }
      ++litr;
    }
    while(ritr != rvalue.end()) {
      if(!tmpVector.empty() &&
         (*ritr).first == tmpVector.back().first) {
        tmpVector.back().second += (*ritr).second;
      } else {
        tmpVector.push_back(*ritr);
      }
      ++ritr;
    }
    lvalue.clear();
    for(std::size_t i = 0; i < tmpVector.size(); ++i) {
      if(tmpVector[i].second != 0) {
        lvalue.push_back(tmpVector[i]);
      }
    }
//     if(assertSorted(lvalue)) {
//       std::cout << "in mergeCount\n";
//       exit(0);
//     }
  }

  inline void processVertex(edge_property_vector& output) {
    if(!countFromBelow.empty()) {
      //we are processing an interval of change in scanline state between
      //previous vertex position and current vertex position where
      //count from below represents the change on the interval
      //foreach scanline element from previous to current we
      //write the interval on the scanline that is changing
      //the old value and the new value to output
      property_merge_interval<coordinate_type> currentInterval(previousY, currentVertex.first.y());
      coordinate_type currentY = currentInterval.low();
      if(scanlinePosition == scanline.end() ||
         (*scanlinePosition).first != previousY) {
        scanlinePosition = scanline.lower_bound(previousY);
      }
      scanline_iterator previousScanlinePosition = scanlinePosition;
      ++scanlinePosition;
      while(scanlinePosition != scanline.end()) {
        coordinate_type elementY = (*scanlinePosition).first;
        if(elementY <= currentInterval.high()) {
          property_map& countOnLeft = (*previousScanlinePosition).second;
          edge_property element;
          output.push_back(element);
          output.back().first = property_merge_interval<coordinate_type>((*previousScanlinePosition).first, elementY);
          setProperty(output.back().second.first, countOnLeft);
          mergeCount(countOnLeft, countFromBelow);
          setProperty(output.back().second.second, countOnLeft);
          if(output.back().second.first == output.back().second.second) {
            output.pop_back(); //it was an internal vertical edge, not to be output
          }
          else if(output.size() > 1) {
            edge_property& secondToLast = output[output.size()-2];
            if(secondToLast.first.high() == output.back().first.low() &&
               secondToLast.second.first == output.back().second.first &&
               secondToLast.second.second == output.back().second.second) {
              //merge output onto previous output because properties are
              //identical on both sides implying an internal horizontal edge
              secondToLast.first.high(output.back().first.high());
              output.pop_back();
            }
          }
          if(previousScanlinePosition == scanline.begin()) {
            if(countOnLeft.empty()) {
              scanline.erase(previousScanlinePosition);
            }
          } else {
            scanline_iterator tmpitr = previousScanlinePosition;
            --tmpitr;
            if((*tmpitr).second == (*previousScanlinePosition).second)
              scanline.erase(previousScanlinePosition);
          }

        } else if(currentY < currentInterval.high()){
          //elementY > currentInterval.high()
          //split the interval between previous and current scanline elements
          std::pair<coordinate_type, property_map> elementScan;
          elementScan.first = currentInterval.high();
          elementScan.second = (*previousScanlinePosition).second;
          scanlinePosition = scanline.insert(scanlinePosition, elementScan);
          continue;
        } else {
          break;
        }
        previousScanlinePosition = scanlinePosition;
        currentY = previousY = elementY;
        ++scanlinePosition;
        if(scanlinePosition == scanline.end() &&
           currentY < currentInterval.high()) {
          //insert a new element for top of range
          std::pair<coordinate_type, property_map> elementScan;
          elementScan.first = currentInterval.high();
          scanlinePosition = scanline.insert(scanline.end(), elementScan);
        }
      }
      if(scanlinePosition == scanline.end() &&
         currentY < currentInterval.high()) {
        //handle case where we iterated to end of the scanline
        //we need to insert an element into the scanline at currentY
        //with property value coming from below
        //and another one at currentInterval.high() with empty property value
        mergeCount(scanline[currentY], countFromBelow);
        std::pair<coordinate_type, property_map> elementScan;
        elementScan.first = currentInterval.high();
        scanline.insert(scanline.end(), elementScan);

        edge_property element;
        output.push_back(element);
        output.back().first = property_merge_interval<coordinate_type>(currentY, currentInterval.high());
        setProperty(output.back().second.second, countFromBelow);
        mergeCount(countFromBelow, currentVertex.second);
      } else {
        mergeCount(countFromBelow, currentVertex.second);
        if(countFromBelow.empty()) {
          if(previousScanlinePosition == scanline.begin()) {
            if((*previousScanlinePosition).second.empty()) {
              scanline.erase(previousScanlinePosition);
              //previousScanlinePosition = scanline.end();
              //std::cout << "ERASE_A ";
            }
          } else {
            scanline_iterator tmpitr = previousScanlinePosition;
            --tmpitr;
            if((*tmpitr).second == (*previousScanlinePosition).second) {
              scanline.erase(previousScanlinePosition);
              //previousScanlinePosition = scanline.end();
              //std::cout << "ERASE_B ";
            }
          }
        }
      }
    } else {
      //count from below is empty, we are starting a new interval of change
      countFromBelow = currentVertex.second;
      scanlinePosition = scanline.lower_bound(currentVertex.first.y());
      if(scanlinePosition != scanline.end()) {
        if((*scanlinePosition).first != currentVertex.first.y()) {
          if(scanlinePosition != scanline.begin()) {
            //decrement to get the lower position of the first interval this vertex intersects
            --scanlinePosition;
            //insert a new element into the scanline for the incoming vertex
            property_map& countOnLeft = (*scanlinePosition).second;
            std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
            scanlinePosition = scanline.insert(scanlinePosition, element);
          } else {
            property_map countOnLeft;
            std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
            scanlinePosition = scanline.insert(scanlinePosition, element);
          }
        }
      } else {
        property_map countOnLeft;
        std::pair<coordinate_type, property_map> element(currentVertex.first.y(), countOnLeft);
        scanlinePosition = scanline.insert(scanlinePosition, element);
      }
    }
    previousY = currentVertex.first.y();
  }

  template <typename T>
  inline int assertRedundant(T& t) {
    if(t.empty()) return 0;
    int count = 0;
    typename T::iterator itr = t.begin();
    if((*itr).second.empty())
      ++count;
    typename T::iterator itr2 = itr;
    ++itr2;
    while(itr2 != t.end()) {
      if((*itr).second == (*itr2).second)
        ++count;
      itr = itr2;
      ++itr2;
    }
    return count;
  }

  template <typename T>
  inline void performExtract(T& result, property_merge_data& data) {
    if(data.empty()) return;
    //sort
    polygon_sort(data.begin(), data.end(), less_vertex_data<vertex_property>());

    //scanline
    bool firstIteration = true;
    scanlinePosition = scanline.end();
    for(std::size_t i = 0; i < data.size(); ++i) {
      if(firstIteration) {
        mergeProperty(currentVertex.second, data[i].second);
        currentVertex.first = data[i].first;
        firstIteration = false;
      } else {
        if(data[i].first != currentVertex.first) {
          if(data[i].first.x() != currentVertex.first.x()) {
            processVertex(output);
            //std::cout << scanline.size() << " ";
            countFromBelow.clear(); //should already be clear
            writeGraph(result, output, scanline);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          } else {
            processVertex(output);
            currentVertex.second.clear();
            mergeProperty(currentVertex.second, data[i].second);
            currentVertex.first = data[i].first;
          }
        } else {
          mergeProperty(currentVertex.second, data[i].second);
        }
      }
    }
    processVertex(output);
    writeGraph(result, output, scanline);
    //std::cout << scanline.size() << "\n";
  }

  template <typename T>
  inline void insertEdges(T& graph, property_set& p1, property_set& p2) {
    for(typename property_set::iterator itr = p1.begin(); itr != p1.end(); ++itr) {
      for(typename property_set::iterator itr2 = p2.begin(); itr2 != p2.end(); ++itr2) {
        if(*itr != *itr2) {
          graph[*itr].insert(*itr2);
          graph[*itr2].insert(*itr);
        }
      }
    }
  }

  template <typename T>
  inline void propertySetAbove(coordinate_type y, property_set& ps, T& scanline) {
    ps.clear();
    typename T::iterator itr = scanline.find(y);
    if(itr != scanline.end())
      setProperty(ps, (*itr).second);
  }

  template <typename T>
  inline void propertySetBelow(coordinate_type y, property_set& ps, T& scanline) {
    ps.clear();
    typename T::iterator itr = scanline.find(y);
    if(itr != scanline.begin()) {
      --itr;
      setProperty(ps, (*itr).second);
    }
  }

  template <typename T, typename T2>
  inline void writeGraph(T& graph, edge_property_vector& output, T2& scanline) {
    if(output.empty()) return;
    edge_property* previousEdgeP = &(output[0]);
    bool firstIteration = true;
    property_set ps;
    for(std::size_t i = 0; i < output.size(); ++i) {
      edge_property& previousEdge = *previousEdgeP;
      edge_property& edge = output[i];
      if(previousEdge.first.high() == edge.first.low()) {
        //horizontal edge
        insertEdges(graph, edge.second.first, previousEdge.second.first);
        //corner 1
        insertEdges(graph, edge.second.first, previousEdge.second.second);
        //other horizontal edge
        insertEdges(graph, edge.second.second, previousEdge.second.second);
        //corner 2
        insertEdges(graph, edge.second.second, previousEdge.second.first);
      } else {
        if(!firstIteration){
          //look up regions above previous edge
          propertySetAbove(previousEdge.first.high(), ps, scanline);
          insertEdges(graph, ps, previousEdge.second.first);
          insertEdges(graph, ps, previousEdge.second.second);
        }
        //look up regions below current edge in the scanline
        propertySetBelow(edge.first.high(), ps, scanline);
        insertEdges(graph, ps, edge.second.first);
        insertEdges(graph, ps, edge.second.second);
      }
      firstIteration = false;
      //vertical edge
      insertEdges(graph, edge.second.second, edge.second.first);
      //shared region to left
      insertEdges(graph, edge.second.second, edge.second.second);
      //shared region to right
      insertEdges(graph, edge.second.first, edge.second.first);
      previousEdgeP = &(output[i]);
    }
    edge_property& previousEdge = *previousEdgeP;
    propertySetAbove(previousEdge.first.high(), ps, scanline);
    insertEdges(graph, ps, previousEdge.second.first);
    insertEdges(graph, ps, previousEdge.second.second);
    output.clear();
  }

  template <typename Result>
  inline void writeOutput(coordinate_type x, Result& result, edge_property_vector& output) {
    for(std::size_t i = 0; i < output.size(); ++i) {
      edge_property& edge = output[i];
      //edge.second.first is the property set on the left of the edge
      if(!edge.second.first.empty()) {
        typename Result::iterator itr = result.find(edge.second.first);
        if(itr == result.end()) {
          std::pair<property_set, polygon_set_type> element(edge.second.first, polygon_set_type(VERTICAL));
          itr = result.insert(result.end(), element);
        }
        std::pair<interval_data<coordinate_type>, int> element2(interval_data<coordinate_type>(edge.first.low(), edge.first.high()), -1); //right edge of figure
        (*itr).second.insert(x, element2);
      }
      if(!edge.second.second.empty()) {
        //edge.second.second is the property set on the right of the edge
        typename Result::iterator itr = result.find(edge.second.second);
        if(itr == result.end()) {
          std::pair<property_set, polygon_set_type> element(edge.second.second, polygon_set_type(VERTICAL));
          itr = result.insert(result.end(), element);
        }
        std::pair<interval_data<coordinate_type>, int> element3(interval_data<coordinate_type>(edge.first.low(), edge.first.high()), 1); //left edge of figure
        (*itr).second.insert(x, element3);
      }
    }
    output.clear();
  }
};

}
}
#endif

/* property_merge.hpp
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
*/