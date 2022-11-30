// Copyright 2011, Andrew Ross
//
// Use, modification and distribution are subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt).
#ifndef BOOST_POLYGON_DETAIL_SIMPLIFY_HPP
#define BOOST_POLYGON_DETAIL_SIMPLIFY_HPP
#include <vector>

namespace boost { namespace polygon { namespace detail { namespace simplify_detail {

  // Does a simplification/optimization pass on the polygon.  If a given
  // vertex lies within "len" of the line segment joining its neighbor
  // vertices, it is removed.
  template <typename T> //T is a model of point concept
  std::size_t simplify(std::vector<T>& dst, const std::vector<T>& src,
                       typename coordinate_traits<
                       typename point_traits<T>::coordinate_type
                       >::coordinate_distance len)
  {
    using namespace boost::polygon;
    typedef typename point_traits<T>::coordinate_type coordinate_type;
    typedef typename coordinate_traits<coordinate_type>::area_type ftype;
    typedef typename std::vector<T>::const_iterator iter;

    std::vector<T> out;
    out.reserve(src.size());
    dst = src;
    std::size_t final_result = 0;
    std::size_t orig_size = src.size();

    //I can't use == if T doesn't provide it, so use generic point concept compare
    bool closed = equivalence(src.front(), src.back());

    //we need to keep smoothing until we don't find points to remove
    //because removing points in the first iteration through the
    //polygon may leave it in a state where more removal is possible
    bool not_done = true;
    while(not_done) {
      if(dst.size() < 3) {
        dst.clear();
        return orig_size;
      }

      // Start with the second, test for the last point
      // explicitly, and exit after looping back around to the first.
      ftype len2 = ftype(len) * ftype(len);
      for(iter prev=dst.begin(), i=prev+1, next; /**/; i = next) {
        next = i+1;
        if(next == dst.end())
          next = dst.begin();

        // points A, B, C
        ftype ax = x(*prev), ay = y(*prev);
        ftype bx = x(*i), by = y(*i);
        ftype cx = x(*next), cy = y(*next);

        // vectors AB, BC and AC:
        ftype abx = bx-ax, aby = by-ay;
        ftype bcx = cx-bx, bcy = cy-by;
        ftype acx = cx-ax, acy = cy-ay;

        // dot products
        ftype ab_ab = abx*abx + aby*aby;
        ftype bc_bc = bcx*bcx + bcy*bcy;
        ftype ac_ac = acx*acx + acy*acy;
        ftype ab_ac = abx*acx + aby*acy;

        // projection of AB along AC
        ftype projf = ab_ac / ac_ac;
        ftype projx = acx * projf, projy = acy * projf;

        // perpendicular vector from the line AC to point B (i.e. AB - proj)
        ftype perpx = abx - projx, perpy = aby - projy;

        // Squared fractional distance of projection. FIXME: can
        // remove this division, the decisions below can be made with
        // just the sign of the quotient and a check to see if
        // abs(numerator) is greater than abs(divisor).
        ftype f2 = (projx*acx + projy*acx) / ac_ac;

        // Square of the relevant distance from point B:
        ftype dist2;
        if     (f2 < 0) dist2 = ab_ab;
        else if(f2 > 1) dist2 = bc_bc;
        else            dist2 = perpx*perpx + perpy*perpy;

        if(dist2 > len2) {
          prev = i; // bump prev, we didn't remove the segment
          out.push_back(*i);
        }

        if(i == dst.begin())
          break;
      }
      std::size_t result = dst.size() - out.size();
      if(result == 0) {
        not_done = false;
      } else {
        final_result += result;
        dst = out;
        out.clear();
      }
    } //end of while loop
    if(closed) {
      //if the input was closed we want the output to be closed
      --final_result;
      dst.push_back(dst.front());
    }
    return final_result;
  }


}}}}

#endif

/* polygon_simplify.hpp
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
*/