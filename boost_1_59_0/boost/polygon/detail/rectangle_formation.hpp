/*
    Copyright 2008 Intel Corporation

    Use, modification and distribution are subject to the Boost Software License,
    Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
    http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_FORMATION_HPP
#define BOOST_POLYGON_RECTANGLE_FORMATION_HPP
namespace boost { namespace polygon{

namespace rectangle_formation {
  template <class T>
  class ScanLineToRects {
  public:
    typedef T rectangle_type;
    typedef typename rectangle_traits<T>::coordinate_type coordinate_type;
    typedef rectangle_data<coordinate_type> scan_rect_type;
  private:

    typedef std::set<scan_rect_type, less_rectangle_concept<scan_rect_type, scan_rect_type> > ScanData;
    ScanData scanData_;
    bool haveCurrentRect_;
    scan_rect_type currentRect_;
    orientation_2d orient_;
    typename rectangle_traits<T>::coordinate_type currentCoordinate_;
  public:
    inline ScanLineToRects() : scanData_(), haveCurrentRect_(), currentRect_(), orient_(), currentCoordinate_() {}

    inline ScanLineToRects(orientation_2d orient, rectangle_type model) :
      scanData_(orientation_2d(orient.to_int() ? VERTICAL : HORIZONTAL)),
      haveCurrentRect_(false), currentRect_(), orient_(orient), currentCoordinate_() {
      assign(currentRect_, model);
      currentCoordinate_ = (std::numeric_limits<coordinate_type>::max)();
    }

    template <typename CT>
    inline ScanLineToRects& processEdge(CT& rectangles, const interval_data<coordinate_type>& edge);

    inline ScanLineToRects& nextMajorCoordinate(coordinate_type currentCoordinate) {
      if(haveCurrentRect_) {
        scanData_.insert(scanData_.end(), currentRect_);
        haveCurrentRect_ = false;
      }
      currentCoordinate_ = currentCoordinate;
      return *this;
    }

  };

  template <class CT, class ST, class rectangle_type, typename interval_type, typename coordinate_type> inline CT&
  processEdge_(CT& rectangles, ST& scanData, const interval_type& edge,
               bool& haveCurrentRect, rectangle_type& currentRect, coordinate_type currentCoordinate, orientation_2d orient)
  {
    typedef typename CT::value_type result_type;
    bool edgeProcessed = false;
    if(!scanData.empty()) {

      //process all rectangles in the scanData that touch the edge
      typename ST::iterator dataIter = scanData.lower_bound(rectangle_type(edge, edge));
      //decrement beginIter until its low is less than edge's low
      while((dataIter == scanData.end() || (*dataIter).get(orient).get(LOW) > edge.get(LOW)) &&
            dataIter != scanData.begin())
        {
          --dataIter;
        }
      //process each rectangle until the low end of the rectangle
      //is greater than the high end of the edge
      while(dataIter != scanData.end() &&
            (*dataIter).get(orient).get(LOW) <= edge.get(HIGH))
        {
          const rectangle_type& rect = *dataIter;
          //if the rectangle data intersects the edge at all
          if(rect.get(orient).get(HIGH) >= edge.get(LOW)) {
            if(contains(rect.get(orient), edge, true)) {
              //this is a closing edge
              //we need to write out the intersecting rectangle and
              //insert between 0 and 2 rectangles into the scanData
              //write out rectangle
              rectangle_type tmpRect = rect;

              if(rect.get(orient.get_perpendicular()).get(LOW) < currentCoordinate) {
                //set the high coordinate perpedicular to slicing orientation
                //to the current coordinate of the scan event
                tmpRect.set(orient.get_perpendicular().get_direction(HIGH),
                            currentCoordinate);
                result_type result;
                assign(result, tmpRect);
                rectangles.insert(rectangles.end(), result);
              }
              //erase the rectangle from the scan data
              typename ST::iterator nextIter = dataIter;
              ++nextIter;
              scanData.erase(dataIter);
              if(tmpRect.get(orient).get(LOW) < edge.get(LOW)) {
                //insert a rectangle for the overhang of the bottom
                //of the rectangle back into scan data
                rectangle_type lowRect(tmpRect);
                lowRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                currentCoordinate));
                lowRect.set(orient.get_direction(HIGH), edge.get(LOW));
                scanData.insert(nextIter, lowRect);
              }
              if(tmpRect.get(orient).get(HIGH) > edge.get(HIGH)) {
                //insert a rectangle for the overhang of the top
                //of the rectangle back into scan data
                rectangle_type highRect(tmpRect);
                highRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                 currentCoordinate));
                highRect.set(orient.get_direction(LOW), edge.get(HIGH));
                scanData.insert(nextIter, highRect);
              }
              //we are done with this edge
              edgeProcessed = true;
              break;
            } else {
              //it must be an opening edge
              //assert that rect does not overlap the edge but only touches
              //write out rectangle
              rectangle_type tmpRect = rect;
              //set the high coordinate perpedicular to slicing orientation
              //to the current coordinate of the scan event
              if(tmpRect.get(orient.get_perpendicular().get_direction(LOW)) < currentCoordinate) {
                tmpRect.set(orient.get_perpendicular().get_direction(HIGH),
                            currentCoordinate);
                result_type result;
                assign(result, tmpRect);
                rectangles.insert(rectangles.end(), result);
              }
              //erase the rectangle from the scan data
              typename ST::iterator nextIter = dataIter;
              ++nextIter;
              scanData.erase(dataIter);
              dataIter = nextIter;
              if(haveCurrentRect) {
                if(currentRect.get(orient).get(HIGH) >= edge.get(LOW)){
                  if(!edgeProcessed && currentRect.get(orient.get_direction(HIGH)) > edge.get(LOW)){
                    rectangle_type tmpRect2(currentRect);
                    tmpRect2.set(orient.get_direction(HIGH), edge.get(LOW));
                    scanData.insert(nextIter, tmpRect2);
                    if(currentRect.get(orient.get_direction(HIGH)) > edge.get(HIGH)) {
                      currentRect.set(orient, interval_data<coordinate_type>(edge.get(HIGH), currentRect.get(orient.get_direction(HIGH))));
                    } else {
                      haveCurrentRect = false;
                    }
                  } else {
                    //extend the top of current rect
                    currentRect.set(orient.get_direction(HIGH),
                                    (std::max)(edge.get(HIGH),
                                               tmpRect.get(orient.get_direction(HIGH))));
                  }
                } else {
                  //insert current rect into the scanData
                  scanData.insert(nextIter, currentRect);
                  //create a new current rect
                  currentRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                      currentCoordinate));
                  currentRect.set(orient, interval_data<coordinate_type>((std::min)(tmpRect.get(orient).get(LOW),
                                                       edge.get(LOW)),
                                                                         (std::max)(tmpRect.get(orient).get(HIGH),
                                                       edge.get(HIGH))));
                }
              } else {
                haveCurrentRect = true;
                currentRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                                    currentCoordinate));
                currentRect.set(orient, interval_data<coordinate_type>((std::min)(tmpRect.get(orient).get(LOW),
                                                     edge.get(LOW)),
                                                                       (std::max)(tmpRect.get(orient).get(HIGH),
                                                     edge.get(HIGH))));
              }
              //skip to nextIter position
              edgeProcessed = true;
              continue;
            }
            //edgeProcessed = true;
          }
          ++dataIter;
        } //end while edge intersects rectangle data

    }
    if(!edgeProcessed) {
      if(haveCurrentRect) {
        if(currentRect.get(orient.get_perpendicular().get_direction(HIGH))
           == currentCoordinate &&
           currentRect.get(orient.get_direction(HIGH)) >= edge.get(LOW))
          {
            if(currentRect.get(orient.get_direction(HIGH)) > edge.get(LOW)){
              rectangle_type tmpRect(currentRect);
              tmpRect.set(orient.get_direction(HIGH), edge.get(LOW));
              scanData.insert(scanData.end(), tmpRect);
              if(currentRect.get(orient.get_direction(HIGH)) > edge.get(HIGH)) {
                currentRect.set(orient,
                                interval_data<coordinate_type>(edge.get(HIGH),
                                         currentRect.get(orient.get_direction(HIGH))));
                return rectangles;
              } else {
                haveCurrentRect = false;
                return rectangles;
              }
            }
            //extend current rect
            currentRect.set(orient.get_direction(HIGH), edge.get(HIGH));
            return rectangles;
          }
        scanData.insert(scanData.end(), currentRect);
        haveCurrentRect = false;
      }
      rectangle_type tmpRect(currentRect);
      tmpRect.set(orient.get_perpendicular(), interval_data<coordinate_type>(currentCoordinate,
                                                      currentCoordinate));
      tmpRect.set(orient, edge);
      scanData.insert(tmpRect);
      return rectangles;
    }
    return rectangles;

  }

  template <class T>
  template <class CT>
  inline
  ScanLineToRects<T>& ScanLineToRects<T>::processEdge(CT& rectangles, const interval_data<coordinate_type>& edge)
  {
    processEdge_(rectangles, scanData_, edge, haveCurrentRect_, currentRect_, currentCoordinate_, orient_);
    return *this;
  }


} //namespace rectangle_formation

  template <typename T, typename T2>
  struct get_coordinate_type_for_rectangles {
    typedef typename polygon_traits<T>::coordinate_type type;
  };
  template <typename T>
  struct get_coordinate_type_for_rectangles<T, rectangle_concept> {
    typedef typename rectangle_traits<T>::coordinate_type type;
  };

  template <typename output_container, typename iterator_type, typename rectangle_concept>
  void form_rectangles(output_container& output, iterator_type begin, iterator_type end,
                       orientation_2d orient, rectangle_concept ) {
    typedef typename output_container::value_type rectangle_type;
    typedef typename get_coordinate_type_for_rectangles<rectangle_type, typename geometry_concept<rectangle_type>::type>::type Unit;
    rectangle_data<Unit> model;
    Unit prevPos = (std::numeric_limits<Unit>::max)();
    rectangle_formation::ScanLineToRects<rectangle_data<Unit> > scanlineToRects(orient, model);
    for(iterator_type itr = begin;
        itr != end; ++ itr) {
      Unit pos = (*itr).first;
      if(pos != prevPos) {
        scanlineToRects.nextMajorCoordinate(pos);
        prevPos = pos;
      }
      Unit lowy = (*itr).second.first;
      iterator_type tmp_itr = itr;
      ++itr;
      Unit highy = (*itr).second.first;
      scanlineToRects.processEdge(output, interval_data<Unit>(lowy, highy));
      if(std::abs((*itr).second.second) > 1) itr = tmp_itr; //next edge begins from this vertex
    }
  }
}
}
#endif

/* rectangle_formation.hpp
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
*/