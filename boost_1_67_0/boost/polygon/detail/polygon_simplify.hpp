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