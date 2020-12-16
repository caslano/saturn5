/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_RECTANGLE_DATA_HPP
#define BOOST_POLYGON_RECTANGLE_DATA_HPP

#include "isotropy.hpp"
//interval
#include "interval_data.hpp"

namespace boost { namespace polygon{

template <typename T>
class rectangle_data {
public:
  typedef T coordinate_type;
  typedef interval_data<T> interval_type;
  inline rectangle_data():ranges_() {}
  inline rectangle_data(T xl, T yl, T xh, T yh):ranges_() {
    if(xl > xh) std::swap(xl, xh);
    if(yl > yh) std::swap(yl, yh);
    ranges_[HORIZONTAL] = interval_data<T>(xl, xh);
    ranges_[VERTICAL] = interval_data<T>(yl, yh);
  }
  template <typename interval_type_1, typename interval_type_2>
  inline rectangle_data(const interval_type_1& hrange,
                        const interval_type_2& vrange):ranges_() {
    set(HORIZONTAL, hrange); set(VERTICAL, vrange); }

  inline rectangle_data(const rectangle_data& that):ranges_() { (*this) = that; }
  inline rectangle_data& operator=(const rectangle_data& that) {
    ranges_[0] = that.ranges_[0]; ranges_[1] = that.ranges_[1]; return *this;
  }
  template <typename T2>
  inline rectangle_data& operator=(const T2& rvalue);

  template <typename T2>
  inline bool operator==(const T2& rvalue) const;
  template <typename T2>
  inline bool operator!=(const T2& rvalue) const { return !((*this) == rvalue); }

  inline interval_data<coordinate_type> get(orientation_2d orient) const {
    return ranges_[orient.to_int()]; }
  inline coordinate_type get(direction_2d dir) const {
    return ranges_[orientation_2d(dir).to_int()].get(direction_1d(dir));
  }
  inline void set(direction_2d dir, coordinate_type value) {
    return ranges_[orientation_2d(dir).to_int()].set(direction_1d(dir), value);
  }
  template <typename interval_type_1>
  inline void set(orientation_2d orient, const interval_type_1& interval);
private:
  interval_data<coordinate_type> ranges_[2];
};


}
}
#endif

/* rectangle_data.hpp
ykZKOuU85TbFYQ1zC1MCKImUrZRMyiWK9kcemlK8KOGUFEoG5SLFJoV/o3hRwinLKPsp5yi5FAd+EKITJZCSuM46HsG6WBfrYl2si3WxLtbFulgX62JdrMvvs/x++f/hfBEdn1gac/5r8x6erJ8fbzkb7UpVUbFx02NVmvi4STwjgb9rxwjccGCOF5mXPrBMwXxm5SjNKSOYPCZnfN537X59vYf2D1CFJk1iTrjIxKK+Z3c1mAtrgKP2/m2iwdz0rCXvsXYFSZRodWx+HojEcl5iaS+xtKWMJRbXIGUsk+Lip4fEh9uUPBZp22B+fr+y8v2TtN2OMoh6wQZtT1Ynqjwsbremrl3FvIXK7c4203ZqobZjKR1Krf3e0n6E5N53kfY7UcZrXwOF2uc3ClSakLAoJowrQf/nxSGPWZP2T0W+Hq5JXK0lricow6nrPkEZl3YeOpWHJfH4PqZfukv70ZJ330/a95L2NYXaz98xpRmDbt/Yli/82ghh32QXikGxc35DHMXdNxqJy07iqkwZRV2Hicq44tUxIZGxnKQsjkeZF8z/5i3O0pYTpZcTNfPb8vf3VXkHBKoS2Ack9jAloiopQZ13Un18XpCuXXtaCkucoZ/T8wS19KdN2ScDJJ45Ek81iceeMlo7h6Y+nvyDRR2tDktUh+dFojsHFydvzPj3SJS5arnS9pPStj9lDG0HG7atbDLht7Y5p2Lh/h/Bf7L1bf62vpc2Tfa98THZU3Lbp8i8jZMo49j+3PxYtBO56rZbFTpTFRsSo37s3JHOEofGVt+utqLBnLOBtKHRJDJdW6HjQj+XZhsiZLN57FmjrSr/uzZvJ8NzfYbE7yZ96UIJcMz/gQbizz9+S/kaN0Da9qksuRnSdi1KENuVnt92QpTKf1SAn8pv1IiA/t4Bg0cM1/7vgMG+/fPmxy1+LK1oLSHKRh+Ltl/oOoNYsioXnrM1oR6vqcfHwhy4lseibXuItO1uIp9/gvY19Ni2mddVFZsUHf349pXberBK4W0NoT2b4Me2lxRjwWtAVV+2taBtcpRN73PXx7atSUqIKH7bxdnnp0zEEqY9bz42lmkh0UnqYsdCPxjEkkiJDJ9hcA7PlFx9DQdpVYzG0dr3exJLQrQqJDxcUmQj1NHRcfoTm4qzXF4sDhac26op54pWnEMSbfOP05o8dpRYY0Jm8KeC35zS9m1YdGxiwby9Mo8s/1H+5lSknK9ydecizmXG165oyc3/VfbBfYp2u91DldstqbGFt9vic3pJtlv5/idccueDZD8F4iTtuThMHy+XbVVMSJS60PXOscg4y9d4KTzvHK2Oj5drgNG1R5WQGM97F/02hNNuXFKivs+5XjCXb3T+PpHHvObzHt9QXA/qKPajPka5TmTmbQfbX0fOUbKfdkpO/Bey3VcwULuf1Prt1oTEs2fMvUKlD5qWYF/JtcRgX4VE52/HDXmtyRsMNS8wfX8kKV6TD4xek1/Kv8dERap018xr8rfI8PznXOLxqzX17z8NXssJ8mJWHBPEMI09Z9hvafLq3Cb9tkn6LWWyYb+ZfYVb8Ptrxe03mfu50HGc+5g+u214HMvrSt+PRn1ozV235q7/9+euz83LXZ/ikt6gn11oi+nBvZ+/tdgmp+jcddKQ5H4Vz6NojObnHSq5bcPQHoejA/qhE45ENxyFzdFfP8+u3HvC9hSN0Ty7aZJTvQ8d8Vl0wv3YEp/HtvgC6tYXLOtzN7G+GxLnd1gXb2J9zMUn8Ba2wx8V8aUWsb7tsr4dsr6dsr6nZX2psr7divXlyPq6KNdnYn7l+pgs8xwvwPa4CDvhYv365F4Ntjaxvquyvs+xFn4hcX6FTfE=
*/