/*
  Copyright 2008 Intel Corporation
 
  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
#define BOOST_POLYGON_ITERATOR_POINTS_TO_COMPACT_HPP
namespace boost { namespace polygon{
template <typename iT, typename point_type>
class iterator_points_to_compact {
private:
  iT iter_, iterEnd_;
  orientation_2d orient_;
  mutable typename point_traits<point_type>::coordinate_type coord_;
public:
  typedef typename point_traits<point_type>::coordinate_type coordinate_type;
  typedef std::forward_iterator_tag iterator_category;
  typedef coordinate_type value_type;
  typedef std::ptrdiff_t difference_type;
  typedef const coordinate_type* pointer; //immutable
  typedef const coordinate_type& reference; //immutable

  inline iterator_points_to_compact() : iter_(), iterEnd_(), orient_(), coord_() {}
  inline iterator_points_to_compact(iT iter, iT iterEnd) : 
    iter_(iter), iterEnd_(iterEnd), orient_(HORIZONTAL), coord_() {}
  inline iterator_points_to_compact(const iterator_points_to_compact& that) : 
    iter_(that.iter_), iterEnd_(that.iterEnd_), orient_(that.orient_), coord_(that.coord_) {}
  //use bitwise copy and assign provided by the compiler
  inline iterator_points_to_compact& operator++() {
    //iT tmp = iter_;
    ++iter_;
    //iT tmp2 = iter_;
    orient_.turn_90();
    //while(tmp2 != iterEnd_ && get(*tmp2, orient_) == get(*tmp, orient_)) {
    //  iter_ = tmp2;
    //  ++tmp2;
    //}
    return *this;
  }
  inline const iterator_points_to_compact operator++(int) {
    iT tmp(*this);
    ++(*this);
    return tmp;
  }
  inline bool operator==(const iterator_points_to_compact& that) const {
    return (iter_ == that.iter_);
  }
  inline bool operator!=(const iterator_points_to_compact& that) const {
    return (iter_ != that.iter_);
  }
  inline reference operator*() const { coord_ = get(*iter_, orient_); 
    return coord_;
  }
};
}
}
#endif


/* iterator_points_to_compact.hpp
WH+fgpDMqvr/ekOq1mGyi6ZMdKqHP643ZoqZ8lL2NqUzQLvaBFoZDyB/Hok2AS8fi+MGKuMFytz6Eszw0qawEMcXmJQ1Azwuw2LFUvypzqs5SrtCFK3nHxLWT9qMl84tXq8clmTPtGrTDILn/IFBGu/1KPRWD5tOa26uRpvrEXqUeoyjeuRSPeJo/cShtH5iscmjbwXGTBi1JuN0g3iUr9vZ3yK4DW0vySj3gdOltpeShDuG7L3s0usOrOzTuzis0zL/x1n4Gqdwi3z+z3M6pnVckl814bHC2SsK1yWjX39/KT9kZnTZtsaP7tDcsUvz1NkdNvkeB/GtvH+/0rnv9Xr4hg/XiXfFd/zRfK3/4zJ+keuzqLj3rsri0/Im91p40eDBuxt8j9eIlsvVxxt/rt9m6jJjzairN9/b41tBOE8+z6pDtbrsPh3McSNevqBq/Z5G3+M7vK/B4HttCe/jUHyvOREZJeWPj5q3UT+z7r3bHx598pbefxzyPf7ld7nNLXZo4gtFCxLKYlY/EzIzvCcWavxDvt7zJhmf2rdm4+LS0q+6fFWSh/EcE+T86PjNPbesnbM9+ECXV3/tlZCAsSQxUn72gt5fBK5daz6zfOrLDQ+dtNFtfIqpue0uTuPZdpdIbXdjqM0uCXQeV3iU4ybQcTfTcRPpuMEC/c/Q/1IWPWvPpeNCaW3KMLAP2A0cSuNkSlqZc7LiF80R42Lcx8RUt3VczC+aVufrCKb1H7tXeR8bE4189/Ex+Q1YkxuppoHbO1ksFovFYrH+iVI//p9qsqOvvV4FX1/y1beG0XvzIX6fZLFYLBaLxWKxWCwW669Kff/fbtaZDFqzw9Lu/v9qxPpDuzXH+pMp1h9KMfauFNue7Cu2bc+2GLCdmtn6GIKuwpCwdIr3mXspce2rqNwSKrcblRtK5eZ6lOswey3Zj/ELoRrfMVnvsVdfsXLfse9zzpDy86+JyLImHjzwdaI544PD2Q/5in2rF9P3Hrv3P/atVizee0zcV+zbd8xdGyPHsg0FGacnfhnz8qRPNnR5fvMwQaiX8wdPrHlg+QXWExJjOs6ouGK2xneM/lY5/6PyFa/MnyeOmLpt8dVljb13OmPfdI/TvTe5xbiVUIphh4FdKRZNx9E9ijwvx0XQcT3BUPBUsBqM+03jNX5dtFPTagxbj2M953YEkXe0OHYj6B7LLqR4dnCSZ0w7YpdGjmsX4HxSbLsMaZV0buSX/abxK87dKF3j79wmyWKxWCwWi8X6d+kYzP+P+faQpmiNZhX6AEh91+04R/WVct91EaXqRK3drsUi+npBUKWNYFA3qY4nyTZoIF99BlJH4p2S72aQfXW6MFGeWNBos2jtuvRW+7h3xTXI55TOIW93CEtT/o5OuO4SefsW1/bF8vblru2L5O1zXduDMLdg5zCpvBzUy2jGjAdmnUFuX0B+CHgH8q0GrS3TLMj7Sr7ZTDnPZrDeBrM5xx7QNVsClcrqUUAsOAachf0Lj7hm2fwGm42+AWqbIH/Q1bYy+DXp/HHSteN7vjSstKmpKVyqH65jaarzOi68SKC8Z5vzLvaSN9CZt6g5b5CXvEu85ElV8G4vyg9paRuy407UWbJFqtZoku8j5FUgbzb2PWLVCDrXDnw+RyrDJpoNNrtBT+1Ce+T64LhIT7vPpYkoy8nXXot0D463pPm0u97gZvfIFnZPbmH3Mje7h6e7bHKh00490j3t1NUjb4i8T2DzPlIVW+YNpOPc8gYLp5K9yRbSg8SIZwb+rxU77WxpJ7ofLya7vNRBuaY5OKFUgA2ci/1z093t4vn/F9XCFlktbPG1my22GY+8335ozhviJc91b6105Q0=
*/