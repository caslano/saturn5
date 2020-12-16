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
xf7yFHLZiVwOjUBPhuNPRiGPG4lfQ1iPPcz5KXF/J3axeTT+DjmdYT6XYj8BuezjI/DvL7Pv5L6TtLv4C6xLiOMB9GviU+xriZdu6lmeYeTnvN/M65h49m2cax/C/66911wvZ31R9jX0LM7kB2cxX+j1bOKk044/xLNxlCthvxr7HPKh3slzWG/cin95jnOG91kXYk+J2ayXspkH/P2Rp/CznCvEt3Bu/RH76uc5t1lNO/THv5z1ifTWz5r/G+j3TNa5P2Sdm8M8ya5usfLRmyFLqO9j9B05b32IeJWJ/iCP7U/R3gTs5G3mcwhyug/54S98g2jnAPJfhNz8iHO0v/hj/u6BvoQhl8THiAf4fecd6r/VP86X+jcRl7Kwx/uZR77vr6Gfz6J/8p8+lnyZj2kJpr6RSex3GM8L25EH/mcI9nBmN/Z3M37TRXyOZx2D3E/cSX2RlOtk/YRcj6RgT9cjn/HoP3LaSTxy1TAu+r+cuFNSgR8ZxPzZ5/T2eWcNf6/JYH3xNPGU9uO5HpyGX3iP/Tjrs81O/Ms44hjz4cQuY+fQ/2T0Igu/8wT2upX2Gcfqx5BnGvLhPDj2T+x3OMc6cj/7D+o/ZsevezRuq58PqC+W/Jm/86yfxrAO3n6W+x+gX6mc17M+8XoQ+0OPN6m+W6z+zeAcl3WYy163eLGuGoGe5uG3dji4H30fjT+NVT+tfORUjj6PC2Pcs71Y77M+eR/7TOBctYLzsifxU8zrSFsf5yKXEOLbTayDnKx/sLcy/PTscPKv4u8EH3Ef67sU/OvIoegp9TnRx1j0dHMKckYOI1/GTuvN/QGc562wzhetFPlMXMTf8fC7Gz7jHAX9PR9r5H8in/0V+z9f4kfwTNYJHfgN1pFn8Lv+zNNC+7wkkv69S/5b6KEdT1axP7XXsexPZ3H/MtZHTuJ1IvW94GT+7f1nFfuvl5mXFcSdGs4Xmedg7OFUJ/L6Fvs75jc+G/2YTv9Yx5cTT1wBnNtWIkf84OQn8AvL6Tf6F8D+z/8v+KtT1M98bMAuAziHdqK/p9CXs4PZp2E3uxZzDvIKfmYW9sO+3Zfvk4fQ/zu5nofe3YAc7HXhXfjLGZyzZFCO/YoLf5BIe1tziHv8vcSrnHm9z3w/TBxOXI5+VNH/CuS0AvnY62PvPib9nPgg/3erlbI+2upi3pmnjDbOOYibsbNodw5yY1++GL9RxrzHr8aPJ5v7ghnnsfNKrfy19Id+DatC74j/rhb89Wr8xFXsfxOwi7uRcyPxMRj/g7/PQC92tSM/xjEugf0q8Twfv93/ffS6iTjFfYutc0IrHcq+Er/rq/WGj/Xd9ufLmLct+PM/YGfsuzM4x3BPo3+5zC/5R/azzn8A+byKf8DvL7fPETnXyMd+DtjxHjktZJ+xdIaR+0S+D+ccYzN648V9zpcZpx1vV7GOxk5S5uOPyqxUeamc2xI/nFWUL6N+1j3LTzGvmfz9lv3A5NH4uXn4FeZzZAd/L5rBucjnrIc4pyph/k/in8pcyH0p53zo0VLbvuejN6Wse6rJn0f8rqG/2E2KarHq2US8989k3pNVt9INgzmXy+G8jDh3aA7nTc9iL+wXN5egV/ZzFfY5BfF32b3W/Fh/Z8VfrmSdnMR5DPO28Dj9Gck8Uc6Zx74+k3LIf9wK5gm/EIafTPwb/cylnhOsnx5E7x/Gnpuwu6dYD4Whj/OoB31ZcTfywU5KsEMX/sX1OXJV/6+0+mefn3yBdX8G82fvJ3Uu4GO1u5j5bMMekOtuy69aKfHTHz2LfZt4ojjjbdU7kzj+EOXaOT85w/hZd+1kHR6P/i5+Hbv/OfbTQjqY+fgm+oJctjL+pXw=
*/