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
kB+btehy4zK02URCPqxf2EX+pZLijvN9Rg229bhIRSTkAxoy4CLPRELQr7p8i0G2+w6WeyF7pbpHz6y9Q3YMbMmgJq3GHHKjWSWYoI/9ScPZY5mOMFdrR8Nb5IBPzaiW2kx09Gy5Co36d7kuL+x2kxe1FJwP5WSbnGl0HozDvusmD0U/on8MyJKf5iaCmh1Mco4BvaNHS4KDPF4qZLfIYfnjjP4xxWyIk+PxzTEAfSojPOZj6N9zCzzE50OxX1/gwSQxMFdsOiDFiycU7dtruPcfRjPrH8Mo0Yehy34Mwbf5qCQwpDFpaZyGwUS8loiNJLLSRGNpIlZNZBWbCLyoiazw9UZM1Ow7Xp5RZaCmU5xWGCEJ6BBRt9gkua26xanA+C0EUus7XnWuHCKt+R4i+RfqErZ4E9RoshNj+gJVx2uCOEYhjRgYryy2SE5Tk9OchF37bQ/+keBoZsjiCf6q+7PXpFT3p62J53bUn2gs10N0KEoCRdE4L7Zt27Zt27ZtGz+2bdu2bdtOZ9CDvWpcNah1j128lnXAxexo7ltBP2odTlyFVIRbMxOuXWBFmcuLX23wsTakRz2DpN0uZjWFhQmn9NeqTGxNpgJcpKXJsvZbOu4SdQV4sYWTQutMfYaWI0HUJ4pC8/zCA9aU6QUa6sFQlQDUVkWpq5FpiEV2SrT5UKwu8S9+vfGFObZwtt7iNWlj9TRW68APAZzUtgGJfetErikkaWzGGdDKIJfYrjqIm09hllnA7EvilLTvChBXlZUIROEYkSRx408ZbtqT9H5mdGF8zJofDZ/ild4M3Ki71c0DbdyRfgi2aNgUs3t9apOCH3JS6FGX8psnT8XUOt9BaSSf7mDpfDhS9+qWLJElhBKtZHiAFQ2/bDzZUoLErRLrTrTXpcIJRQdUsGymw53lVu25hTKWyPu7bn/GOfqeWGItnPznXMRREvDYNAwA3dK/IoIGvhlT5qhcp4+9tCCJ/oIZIWGFgnyIhDkd+Mj7fGG4FtQNMkBXRnK8RbYNuiqTa4Ob/Oo5LKuPclIhS+Ekg6JRGt/BCD2nFygqVciRmZtp6MVV4eF+mv4Z9nuo7rXZVB0X17DEHg4bNrPUzJ2ROMPS/CnilsvnackOuxHamaqiz9LBUxn7XdDaTNQBE5avnMDdYCOsg0tEVnYXF44OmBn2sRZacHbj7jVhJj7E6S0/JqQYKaNz/zhRUIzw51PzKhlL7HqEwzxCUO/qqGkj5i3oOyz/Bq+9VdBe2LfsgF2Jt3EovOt4VN4VQDcgN6BX2ja3/m6sm2372wAvuK1Be7hBH4AbYN8gPLaf5+0PexAsSFVP1i/UATuKUPY1FCo4VmvBf0a5yxtWBACH8NEAnIQO318uwD8PU4DVMAvgm/jvpY1cYHlbbrtDjp+ywCW3HkkrbAuk35aZxvqZIK6LrP1jmZp77eC+5XcN/eW59lW0YnDaEKbfPMM7WAwaRNaaWf0tH7CGC6plURHtFKS4wpjWjbdPB6//GF/jsUSH5rrUBm14vir21cLS+24x3mxCdnd3imySINtkQzpRblTbtPZsAwAELPvTOjFu3rZB3JC2NNoa7dn6tumbbJSxcQIuJd5c+ui+TKU32Z8BXKS15l7zr+GxWIuuz/J2KsnPbPoVE8/12zfE7In6ZNSodYQ5ArnudB4Mo/56TF08f+vDi2SsBkty6bp7jsZL5XQ1zXuanRgS7zuKE+fWoU7ki/l9nuiiQgRN8hENdutk+R1qfVP7/Wh/eeMCh+gBrA12ihb2UDHfbOylvYN4LI4nBh2ygQ/1SARzTBakXQD4ffjfWHBg1i9qoHagF5rFDvsUDw/q0eWxmBYhvhyQvcF4kJqqzlvbGPjrL5P/LiKU+5Tu48uguTWWSwppPNtOlKyr2NR/a1aw7UxRMt5WT+pBi2O3mXqGO/kWuk1AEWgtyfmlyDKvIrIUiRIGzI9zuXScBeH8llDGmA4CpNJgwZCF4ylBd1MsVp29w84f1+Q3Wb8kLtn8gGnY699zVywsRDgnlvNL/60NO/rp5Nj2yaxGLPdJmqkMKmrsyc7K0CXAnCN4yfyonFfJr73vHUI3SkjN6v3OFrG4ynpjSzH5GEqQtQIOk5VlRUqe/ZCcgz0sKkE7bTbGx7ulLE3J1EYeHsrpTcs2pcnpub80vqD9sKtOXXhiB7zIBDXZxQnZ5B8tJ4mlc9UGvrZUIjFc9C+emh/dkZXK6f3z4ccNkhYy0lVCjkX4IUgtbYyG/yhqvr5IdY7yoGOMmpfm87QULykCZezmGejLhLRXr8YptEnJDyQU++miO4E34bXELZAQPyPjzoAmpNHLuw9XtVy9R9iigwD+rbhD/Sy1msIw2+7D9VXl1yct/NSXCVJqXWs2DsfQrDWg0HhqLxB3e3ZXUtGT5ZGUvLx0HxhYrvCCICvn6+7tA/LkpM2jck3t+br+p+5Q2UJ2FfNVtLAc1EK254OMaSlmlEUzxtdYR6hZ+V9IHZ/YPV1u6VOztPnx4VPuOwyb4mNI9Y9LZE9B5+0SSD7ZYVV37ZVlbcDLLtDTTlXOs3aAt3e5QCnYgx10BoaI2ZibTYztaffvbRsj5oTfj6SPmT76L1XKKSz5vpu84GmIZwoLxsbu4c9z7sVt1i36nQzBCbUaRIJUGwWFFmCMvV2oXluw1iJjYXAldLK9VDTgx/5oKuLNUP7q3B1RL7kUYEtnV0Ewlxf5pecZmYoEyVa5yHmonPx9Q3Cn6LvSx6aOJ8gYdT7QmUQ9LhyV+hsGMTrRQtJTeLhoHL/9C3zylubAMvhhI7K4Fi8DFEp3hSshdCZAqJ+9VKZR5PvQGlCAvOb3WvYdPNz8iG1BXo5mjUjE8Oym3G/SWwLtgNwr3T4ZzTvh17+oJUjzNwZtTD6/X7m7xzCyH6avM+WnX1ERnmE5ruHZB/WvrJ/YgxHouXNJdjYffmyGcSH74FS1J/P9+s3VqI18MObmeIBDC55oMrbmUJ3gFinH8n1UJQuoCZgpSHJIB92S9BXtbmUHGgpCuzJfy7m33ORVwMbLqaXwbz6RM3yOW9Ep23hvdP0hCbMICVPLKjAWg3FoTMWKUOn5GaXlRAVeMr+II03CU7oUbaljb6GeI8Z4OVF+0d64jUdyfhInLSyVp29DO+cfdHRRNLt8Sbb3cCzm2zfInF1n4POLYz8pXOyAz4jXtnGgpqEzejSU9m4wt/KG3EHQLOX2IajLrWLJCUFPRWoVTP+9dG7JCUt/BJe+0cq9Al33VVr8uB5W3nz/cABhBFQcMrZq/kX8hJ+x3dfZKbpHrt8f5akt5tdciUkXW4GP303oqPbGs/WxpDYRLYpftpNJmtkfv1w6nFnR00kqvG73nq++X6nHYsd5bw4Aht2eaFmbZXa9l086Dj1Ker2ap9+N94eU/PTE6rgDb4z8Vsq51w86sA1MQEx4/YNHlr6YIhOiwTxKu2b6n6e4eUZUfQxRzRFSEO5NOSMXNYhFZXiyCvxYKBwCLvywuRQhgtxwjgcuOp2AWjbY8Szvk7j0O420u23cz/0Hk5cjVPMOFlBHenTWCb5wvbjX2edmofgs+C/OHrd956DYXJKZ7Jq7xWFqII3L4HqMMI/HaW6vRvqGvk0kQ6iuU8EPILqpkfPOvEey8BJ3UPVQ5AZLtlhe5jqpm/UYVuHQtX8ChY37UIEpbXuZaSPx6fNnymsTaOqzGzH/dNZRjDNQzYb0UzHu/RN+4zODvkXXj8Tih1/u+13900HT+OJhrBmagaKLJH3FBOi6HZFUG+AoIVwWZ/Oel4aG/IF1+yGZuiOIbQg0S6hw+14npVqBqu+4ZPgDtJeqUDw/r+SzrIXBLDlzeFDd7owsdg7YDoN2hybBMhr99q2l/4tC7p8XQAWEhmlhBQCGfD8oKXPRTV61FJ0rfPaXfEO7oL8e6B2eSBM4pwjeZGn7tVuSB51yr6rnvhdSZm+Kj+0VKdT1fycrp2iqW7VAfF+3DQRj2HZM+zICv9HilfLZ1W0PmmFTHrkVInFOv5IWIUBDk9iEGKOTMIkcQkQK6sIWqXr3AzSs9cPKxnXm91IKgLF18gc6x6FuX8lb2DYm58yUK9EAYD0RGABjS6/XafQ8Jm27x7BKw/i0PSuKHi1n2SxcKxi5nc81dno+9dTScvHLiv/GhKIZM5uQXSGanfz3mTxhgftfZldcGBut4YYIeFm3xB6+js2egKz1r4RjhiDEgaFShru6RsQMiRR0NHKcrr8hPIQ49gnpWDNKSI0LEnNLwBWxJH/oyCuHDDnxkNaW8Tuo8G7vdYD7kiNjQzBVGfuR89D8Xat+QLE4Co7iMEaaA9BjvZ8K9JonSf42LxMAzMy7QrDLZqVW/iK6q+nMidqYtB1rUzJWhcOmFHvARuwuMQrsHHmDQWmW1QVM5FdzekgV/YCIb1T8fjIP7PAT7WyVPqiUHX3sqfaR5nVSHt4Je1CstLz5LEZFc/9BU7Zp6dTaOemkOQEMwhbRPhKVunqO211dCZ8QbhBHFaB/boYMTcv5mPsUmyDcrm064OI4cN9suZyOnDnqgWVHCUBQo89LkvsEC3AtxeI9pyumrplsv5Uqp7YUa0nbGY0HQXeMTCGbEWW3TNPC5jJqG89rGsOrBDPsjHWu1G3o9br9K9faddTd9mqsanO0y1JyWux6KF7rrA9QNZBc2CU9MJI548wcdIzCjtZDs2CizfbTPXQGqnQ6ULC1F4twYIbni/nUrIR6UrKsnGiSG04fQLgGegDC3dNgqIMkgx3J8TYb+aBhCDVYjIS1XoOHsnF0hTjGBcMKUY5avNrbiww2HFcdbLRbwu4qg/+oIu3Dy+ZZIWaQivl3z/nSUJJEiPpD82DlEV/Q6nS1u88Psa5b657LLkJbqvUWdgmbH1o3z660XQ/wUwsRv93vD+1WjtfUaoxkKWwQ3yz+u9dee0Rq2L8Ub5DebW78d647glnidwRajlloAuTUGnLY7mhsVYTTUv1O5aV9BaQ7M9LqhVNXoWIiMqme6ovxxM3KTT5M+IuXkfkEaBcXOIEa0y+59HZjp+hpQZ/6BVyr6SjMMKGd+Aw813bxJMs0qzHI697OXquan+NvnZO74lc3mrAz3YL3uo7eT+QuW8mwKCjfr3y99t6o9N/Vz070y/9e3Zq5P/Km/j+xcQJ2Ad+6oXp1wn5KX9woWJGrmlB8z+8yfd5+h39unMQKPjujYr8Ofm5WBptk6B9Ksu+8EX2Bw36jvrdPY782vnUybvmaeyuPrwM3Fd+2AXsV36pDdz3fVAZvx4l+lT47KWN/gFZ17rgAeleIfpM+O23jqtHCjFaonFv/DaswxUgZ3NXgwBF1Yo/U/hoA2RiqAT/TT09ss7vgKHrEmpMqpJcqHGdgFOvlqg2KeFhwdPeyNQSRSA9eD+ula92ZtYuYz0jppOVDYh6Z/zRz3EQ9qEkluLH3IMV0J8akY2YGT80acot2u27ixN9dH9vnq/68I6RX0cvMsIj3srSN+fiJKlVawRzRevOfkDI2kimGhGaTp+8ieuI16HJimT3lf6owVpkciZxb6/HgyDkdt3Fw7mcMAfBZzGRzGhgS1nUKGOYw8cm2YQOJTbUr0aUN5wlUsRG7/hs12QPDYo2BwLZCA+4I7fHMMve4DGWv1wVf9yYCc4k/k9bj4Xw+0KNNUJjB4sUOmROd+vUZ88tFj4Za3q+KsuXFTE5W3gsmOimdM72c+m8eQmiiqTf/E5RZuhmmm3GvC+ET4pUpmGFiauEMOaBGqOmfavQcerqoeSPM84X/DJdFy5hmjCMFk9qoN3JSOVa4DZ3Vbthgk/GIj79xhtepVeNcrMW5p7UI0hR/8eUuXj7GZIiotSMtHaisILUBRmYikYpm0cRyDFxh1nLgSJgdYDSNuWOqqh4otDijxxVY9X1Kc7EkJBSGMKYT7tBrxpgPWxk2yQaq2w5wElUnjI1/f2PDC64jPl6PqGKR/uPqL4oaoSRsH+C6l6lC6oww6uxC9J3nkg308jwoNaK8q55Ffps29jpbO16pt8uu8Qxd+1CdZ0A1nBIC5TIZmOdQ/IFQn7JfHU6M/LOghBm+d/EGtK1iSKeYOuwlS9KVn1JZZiIY/6GqMJFtdcVk9Ab9TRHnYn48CFr5yJTxKfNztbRPZn5PteLuSYWd7TONls+kyi5qhZ3TUqv2s03GRws3VCYE8Ig+QJ4UGxUjMpWUD6QfqHK+tg6GIwtkC3ruHsFuN0gCEftrWfUSt5IN+AV93gOuOFe/0I6zQB5PVIZ14xK5aVfmEBaGM5JhlE2bg7LkicXUf0OAuPbUcydepmA2LO6sCTFMBZdF4WZJWmU9Q8bVi5NM5/4coC7YGBbMGzpy+eBwrqCU4l9dFEQL9/M9vNDqii5f+NePQ642S7noopjgZYLaQVo5EVwPxVKAEbjHyueEXXZ6IR65lNMldMUXk9YfglI8JKYG0KI5ESTWowKjcYiN9ITAUGNVXmfAGXdyu6HL+RrWg/WrxkPBqz5j/RtARjZq4NQLsdeYV9o28QKX42kjIeF7lg400hVuAKlmho4epM8izpIxhYCVhMLAqiQgmHVN0A99z0sI67dH1MIa582j/gl57RR4FDSbRMzGBsZP2qt4ODyLYbE5cWdjGEFEZr/vUWKwuGzE8XxZYkc16hgpqM6fOJ3xjWCsm5nXMlr7pKMDaUuuc7jI6k2bkwL1PzJtNN04bOhF6W3VhrV6TFLQ6MNbj5ISSi0DxJLtnu7os8Sspr9gutYu7asTTOcjkvibt5x6i+I4vNmUn3l9SonpryxqXFmRHAhe8ZUizdTrlGDQdXnzbFejaYlE1r9N3LI/zE7UqGoOr1449kL/xl0MZD6Y9Iq4uC1+ODMI+3G1nbLBktzDcsp7jLyb3cNiFPaDrDQJAdxoiJwAEn/IAUz4VF21rRnLRJJ7kSP/O0+SuW9WSc3vVgFD6MWmyfDUj6g3ULeTHz19BtMggJBP7YiixWw4y4Hf7sfYQi+IKHZfZ6gLKHfC9G1BGloumDceHo+MrSMQc4Bem/2Pz9IqadYQFdnGXFxlP6nu6u1iOPRiDjhGVggG8+31hRaG5ANN/lTRcA/7aP2HExZXQeEt059x6lHYoFEhQMMC15N0QLtBaHAuJh4Qdz23f0gO2F0wAr2aAvd8BOi+K2dTPVI1wyITuDskcE7wOTIIpi1uPurph8dlEG5hVhELKGOf7WeZtB6xOczfQOOJraN+Nc1mqPZnmOflpIEuGUv8C6ouLQP6qW5cvrCpF5bmbmUCBcZQFW2DHy3a+IKmbZoZSYfPw7qNIkTLPztOKOTE9L4Dmy07MvLLu8tWyNuG/23FauweXqp2IkpCA5q6DhArbBkbUpCVzQMbUXl2kvKBbvlezdMFFOSaiV8b5EfULSDqyjvE9hXAZQyw7Mms8pRBsFGQCT/nFHAr4m0MYElGNFjdJUexCXpP1dQw4IgTEwrvfERFzPhY/UPoKJwADzUStMVfSzL+lwAtI8M5TaIk6DgsXwkW3CpedIC+LMet2D+1AgfYrzPRi3IvOG9Om6TfLcvMgADJLUnZfIM+1qux/5j49yeS8pxNUSJPVA/JQKObQNch7cJZtgLfrMbmsFZslWHAavl00d3o+d1gIMqcs/yeNCSnl5+lfUMWwEjoa4t5h94tDf4WOlsH+yPR11zh1WkupkAIdK7qzNoGyhpcyGHmffkx9fH73zUxOvaA+0X+yJHbRYWZHgX60Y18A42+VZAlP0ke7ChnwHfXlamm+9ZDZp4geAheHe1coDdBSAIovG06V/TsffO9xtaPPxShHP60nypVehcBbkWpqqwEepUFefrVXMHZPrA3JTMHlwNLMC075iH6EDopvRusGktdebNmd9oIeUfZVVOErY1Z7DDtP567Ze3Q/NGWz1VgDxe0pRiaUkpvkNB+VmdZ0mlmIalNrDeQsk3ryrz/ggHb7QFCxKAgv1B4iBGmEzjiU8SgrNhq3mki1Z6orGwTB/vtDr7AZnCpM48J/8stJt72Te2VlKrp3XMwAgP3izSO7+wGx0mdhuaLfdgh6O7AwwXuwNoG3gNMrF79oWjG6awhXhzJLA+cciao2u7kcVzR5U536mTC3BodWK8BatVyfCLHI5i2OTLrHAv1m9teAnTPvHClEkSfXSZIfUCIhkbqOPq8/h1AH+APSFwIMRG8xS7hgePc3vQ6Ch7uwqPLkergysPF3/aSM6xK+tWgfiK0EAW/kpSES/W/+MwM2lTIVYRlFUamGryTyBLvXhf+UtlykjWBUHFbezg4diSgAudJN9UHBSL91cqUTygqv/rMwPeBrGEoQ9VMiEnSqbpld1FygwXvixPtJ97pLwgLmYHFzFPyoc4DCe46gLW4x6nzH2Bpu5U5Wl+IOpo4PqiQTkUIKsnwner9umWkt6tswDVJ86evGm+HZLMVStHIJLw9Y2Zw1ls5THjV9NZLeDY+wkFxEIxq/Epw43aAmp70pH74oe/RS3oWPvIB7omb3MAp7T4M5GHmtkLrIev7LGQHr9Y5Nkk5FFE8rpAHUqXH01Pdqo9+qQ0vQ7xYL1SWYZwoSERjng4tAyeun6x6p1LU0UVx39H6cnnhuuV/IffLuLLaC3tuth7VWZjTqb+AHvCH6c6hDfkxv1RtR+la7Qlwq+hLZuT/VIubnre5bHmFgPi0C8kSMt3VUN6Xw00YpO93dVJsFZ5ues1ONDWkYGD97pyylfHrep11hui7jnNLkHauwOihMnZ0tBuodOBq0BcZgHsyupheon31FKBjHVGwcbo40F8LfYMZvAjlYoOujdqF36Lf0vCSZ+80dN3Jy1qcnfQ+m01es9Y3ye98wc8l5JNp7LAeNHGCvYdYx1IfO9wCY8XqmYYkUXndHc6s+MRJoNudpGlfbix95JuIq4BHtq6bafdOz5vcjk/zUcIRPY8xH4QN2Htykz/DuDS77gY/+Z0Xn6YRxqLKrRCozMz6Olae+77+rw6v8BYzQsRiVRuYU05f5+jkOsPGTdUwAExnIO3VKsiXaIt+CZl7se0CRWTctf3Zx/bhvLVC3rGKfr1CfRid5ex7DV/Ghxfljqw18QqHfNCKj0ZbQluLMPDbza/yogkmw81WuCApfbSGJzvdrIIZaM49kRAsVKBVhy26SH+BSggmZ91D1Tc=
*/