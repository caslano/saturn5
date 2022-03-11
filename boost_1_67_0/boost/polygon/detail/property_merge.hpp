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