/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
#define BOOST_POLYGON_ITERATOR_COMPACT_TO_POINTS_HPP
namespace boost { namespace polygon{
template <typename iterator_type, typename point_type>
class iterator_compact_to_points {
private:
  iterator_type iter_;
  iterator_type iter_end_;
  point_type pt_;
  typename point_traits<point_type>::coordinate_type firstX_;
  orientation_2d orient_;
public:
  typedef std::forward_iterator_tag iterator_category;
  typedef point_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const point_type* pointer; //immutable
  typedef const point_type& reference; //immutable

  inline iterator_compact_to_points() : iter_(), iter_end_(), pt_(), firstX_(), orient_() {}
  inline iterator_compact_to_points(iterator_type iter, iterator_type iter_end) :
    iter_(iter), iter_end_(iter_end), pt_(), firstX_(), orient_(HORIZONTAL) {
    if(iter_ != iter_end_) {
      firstX_ = *iter_;
      x(pt_, firstX_);
      ++iter_;
      if(iter_ != iter_end_) {
        y(pt_, *iter_);
      }
    }
  }
  //use bitwise copy and assign provided by the compiler
  inline iterator_compact_to_points& operator++() {
    iterator_type prev_iter = iter_;
    ++iter_;
    if(iter_ == iter_end_) {
      if(x(pt_) != firstX_) {
        iter_ = prev_iter;
        x(pt_, firstX_);
      }
    } else {
      set(pt_, orient_, *iter_);
      orient_.turn_90();
    }
    return *this;
  }
  inline const iterator_compact_to_points operator++(int) {
    iterator_compact_to_points tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ == that.iter_;
    }
    return (iter_ == that.iter_) && (x(pt_) == x(that.pt_));
  }
  inline bool operator!=(const iterator_compact_to_points& that) const {
    if (iter_ == iter_end_) {
      return iter_ != that.iter_;
    }
    return (iter_ != that.iter_) || (x(pt_) != x(that.pt_));
  }
  inline reference operator*() const { return pt_; }
};
}
}
#endif

/* iterator_compact_to_points.hpp
KVKkSJEiRYoUKVKk/EURov8HmwL/E/0fLY3U/3v6WQPgZ2sA9C9p/v4dcdYAnLKRNQD36WsAkj/76tknu4898oRBi+rmmCv/nF7fjeL/HWsAcoCDgLnAzYBjgMnAscCtgOOA2wLHA7cHHgRMARYAdwBOBg4GFgKHAouAw4DFwF2AhwHTgKXAdOB0YBIw+VOp70qRIkWKFClSpEiRIkXKr+ydC1gUVRTHhwWNFA1MCQsNFeldpFZaWhha2kdFYopljsvuAhvrsu4jwSQptSwrScvoKZaV2ovSXkZGhT3J0ig0NSlJDdEQQbEw+s/M2WUXd4WN0V7n/333+zF3Z+beOTvMzrnnPtSU+v4/Jv+32TP+q/7/FKNNB+/fdZ00BYDL/893re1PJP+/cJLi/ytHKfH7EiVPZ7swVt4uc24PiHX5/bFI9bLf//qS80oP941Kqs58Z0+OPvI+n34/zf3nKtNVF9fcf+SfC+SHS/uMJv/+GvAE8HrwRDAR7Aw64/dJ5OePJb9+PBgOJpNfPwE8DXTvv98LnAieDjr770+i/vsp4FmgjuL4evL/49j/Z7FYLBaLxWKxWCxVpb7/n2ajhfXOR9YxX/9vMmou+ck1gv/rz3lfb8//dfv8Xa9OrfX23haUte5mw1d2rnfnWgeP1r7DmnOqrn3nXPeueIzHene01l3b17djsVgsFovFYrFYLNbx1THx/60GS6bV3m7/v68QEhYHXzkWA7MDhauTxJFZOgP2yzSPMegysXAe1Bv7XIZ9cp37xGei5ll22kM+xwh8vuo59KX3OEdiplG6RpvQpnaGqbDQ5RTjr6YY/1lIgUhnICWgjBq5P/2JomjVGm0G0WbQOaxGe3aq1mhyWA1SOd1CBe/KHSBfS+ewYPAanMvgrKZocdWzqzAkrJ767F8fqWw30fZo2u6kVbZvoO0w2h4bqYwluJSuwULh9UB8eCLYhHSjZGutcg30HYppNmf1lfpH44KPVDDqj/JQ/y2NTU3jcR79NIxnwHZDU1PTBGwrTUJKHa6kOmykOoSQHTtRHXJTPOtg1ZrTDLp0gy7DWZfWbYlyXN9XOtV5g6Bc6zqkm1BOnlzOaGc5Lb8wuYzIo1zvqfR99UWiY9D0pTcIZItKly08r3tikCCrP9m+DzgR+xXo6Lq912dkFl131F+sk/RZCH1m0Vq1Uwy4r/Cpw2wXwvGZZNAvTnH7zKZcR0XzdWC/wDATyk/GNUjzLczVo850vditSTq3kezv7MOSHuB/m5qvtrlb5fN8VL7ilfnzxBFTty2+uqyx906MQ5HzKxcNunB8dsym1T1DvvvgpHviUT/5PBkPbZqlrTz/j/n1hsUJVReNxPiWflL+PeNuffbJiK1Dq4r7COcNenOYem1z/rZFvi3nL5iT1LC65/15sW+KSzpnDNvgf9ui1PcnTqBnET2j8pA6IDnXAJ1OY3pyqW/PnWAPmpPyDJqTshY8M4CeB/ScyKN7J5KefyXUR2gt9QX6hPr+VIBR4I+07udPNDfndvrfrKQ5OH+mOTd3gCPBnTS3xi4wCfyF5tCoorkyd4PpYDVoBPeAmeA+miujFpwG7geng3XgTLAevAs8AN4DHgIfABvBR8HD4BLwxAAh90WwE/gG2Bl8HwwB14Oh4HYwDKwHe4BNYDiIstFXy/nswjFk90CkaLJ7T41i91PBTuBpYK18XnoW0TMqj8ZkBZGd3w1Q7FwEdgfXgD3BTWBv8HtQKmMzeDa4BYwFt4IXgz+AQ8FtYDxYAV4D/gjeAP4EJoPbQRGsBFPBn8E0cAc4BawCLeBu0AFWg1ngHjAH3Avmgr+Cc8BacB5YDz4iQLjexUAAuBwMBFc=
*/