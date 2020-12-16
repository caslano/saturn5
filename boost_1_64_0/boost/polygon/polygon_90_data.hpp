/*
  Copyright 2008 Intel Corporation

  Use, modification and distribution are subject to the Boost Software License,
  Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
  http://www.boost.org/LICENSE_1_0.txt).
*/
#ifndef BOOST_POLYGON_POLYGON_90_DATA_HPP
#define BOOST_POLYGON_POLYGON_90_DATA_HPP
namespace boost { namespace polygon{
struct polygon_90_concept;
template <typename T>
class polygon_90_data {
public:
  typedef polygon_90_concept geometry_type;
  typedef T coordinate_type;
  typedef typename std::vector<coordinate_type>::const_iterator compact_iterator_type;
  typedef iterator_compact_to_points<compact_iterator_type, point_data<coordinate_type> > iterator_type;
  typedef typename coordinate_traits<T>::area_type area_type;

  inline polygon_90_data() : coords_() {} //do nothing default constructor

  // initialize a polygon from x,y values, it is assumed that the first is an x
  // and that the input is a well behaved polygon
  template<class iT>
  inline polygon_90_data& set(iT begin_point, iT end_point) {
    return set_compact(iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(begin_point, end_point),
                       iterator_points_to_compact<iT, typename std::iterator_traits<iT>::value_type>(end_point, end_point));
  }

  template<class iT>
  inline polygon_90_data& set_compact(iT input_begin, iT input_end) {
    coords_.clear();  //just in case there was some old data there
    while(input_begin != input_end) {
       coords_.insert(coords_.end(), *input_begin);
       ++input_begin;
    }
    return *this;
  }

  // copy constructor (since we have dynamic memory)
  inline polygon_90_data(const polygon_90_data& that) : coords_(that.coords_) {}

  // assignment operator (since we have dynamic memory do a deep copy)
  inline polygon_90_data& operator=(const polygon_90_data& that) {
    coords_ = that.coords_;
    return *this;
  }

  template <typename T2>
  inline polygon_90_data& operator=(const T2& rvalue);

  // assignment operator (since we have dynamic memory do a deep copy)
  inline bool operator==(const polygon_90_data& that) const {
    return coords_ == that.coords_;
  }

  // get begin iterator, returns a pointer to a const Unit
  inline iterator_type begin() const { return iterator_type(coords_.begin(), coords_.end()); }

  // get end iterator, returns a pointer to a const Unit
  inline iterator_type end() const { return iterator_type(coords_.end(), coords_.end()); }

  // get begin iterator, returns a pointer to a const Unit
  inline compact_iterator_type begin_compact() const { return coords_.begin(); }

  // get end iterator, returns a pointer to a const Unit
  inline compact_iterator_type end_compact() const { return coords_.end(); }

  inline std::size_t size() const { return coords_.size(); }

private:
  std::vector<coordinate_type> coords_;
};


}
}
#endif

/* polygon_90_data.hpp
4wyWS7supvzKuH41TXWljroY04YfGseZITN590tIXX9hWhJoqlTZXGc535uWw9HiGkNyzWuvITiQmvq7Sn+yhPdX+2vejyR15WRAf82ym0/kkmNe259FZDaS/9yivzIbU+wKjZ9xrEK7wkr/bUPibnw2zb9VhV9j2z+e2qV4RjEJWY8lsB0Dk/UYD9uxKBnH5NiOUfnPi7HJap7xrOYTtx0rknGsju2YmYxiSzKOvdleQuk/osvyAQfdezrV8+5z+sat8kWznjc8q7E0GcXqGPMByG8p6ExxtcoH8Dc77lXiNHTC6WgcT34HweI2xpsl483GYjhHHY8i47nYGG+ojBeHxXGYZjy/35jfKBlvtMxvjGY8nYxXysZ442S88VgSJ2jGS5DxytsYb5CMF44eGKEZL0nGK2pjvFAZrx8Wwf6oroffWL5lMt5yWb4V6njy/RjdbYy3SsZbjW64RsZzzS3fX+V7rS4ny8u/HeQ7+BSGc8UZWB5nYlVciHVwMTbFJdgGP8NRMj/7HMwHXXAtlsEv8A1MRG/8ChviOmyN6/Ed3IBdcBOG4mYMxy04BL/GsbgVp+A2nI47cAnuxM9wF67D3bgN9+I+/BYP4T68gPvxZzyAqfg9PsVDaE+bHMb8eATdMQkr4FGshsewLiZjMzyB7fEkdscfsQf+hAPxNA7GMzgCz+JEPI/T8QLOxxRcihdxOV7DrXgdd+MNPIg38Rj+ivlY0bexGd7BoXgX38d7+Fe8jwuR3Ntjv8NCeAKd8CY6oxPnrbLojp5YCd/ABlgNO6E3BmNdHIXN8AtsjruwBSZja7yMbfAOvoP2bGMd0R07YRf0wzDsjDOxC36F3fAA9sBk9Mdb2BNf4XvoxDH3L1gRe2Ft7I11sQ92wAAMwL4YjYE4EYNwDobiEuyHazEat6Ie9+AQPIFD8QbGoZKPchh64XBsgyNwBI7EZTgKP8MxuB3H4hl8H+/hOKyQj+MPtsPJ2Bun4yCMx+HSPRNn4lqchd/jbHyMc/AlfoQOnH/mYlmch144H33x79gDF+IY/Bg/x6V4GFfiVVyLeQqwf6IbbsAu+DWG4jc4ELfh+7gd5+FO3IW78DHuxue4F/MWZP9DR/wOi+M+rIv7sSEewJZ4EHvhEdyCSbgdj+IePI63MBkdHNjPsCOeQj88jTo8g2PwLE7BczgfL2ACXsQv8BJ+iZclNsLPTr47YojEYuRFee7AEKNSCHthCeyNbtgH38NQ7IP9sS+GoUxXvhcq21L66VaT6VbHYlgDB6AX7sKa6MZ43hiDPij58uS7neE7H9O1zJdXR6ZbV6ZbD8dgfbyNb2MfRm6AP2BDiclphGq+z+pMH9fbiGlqKtNvJtNviTWwFa7C1piIbdTpyfcoZB9IN712Mr32Mr2OMr1OOIzh/XA0dkZjvjT5roPLpX7afGm3JXYmFaviXfTBe9heYmT7Y16MxXw4HovgYiyKp3JlLibEZvxHhrEfEvfxB2M+Gkbk/KfjPl5nzMfrivfIaqzHVMpeG/EdHWgfyxiP1xPb0Ssi5z8d3/G6Yju0cR0ePagDdaunjemwjud4jbEc6eM4/rUxHKb4jQks8zLKfsp1ikMk+YkofhQdZTZlK+UKxTmK9qH0ooylLIv6/4jpsKdE/in3/42/qir/9JFfWF9HLIAbz3nddmN7dFV+62LixhsDNZms+rduln/z5k+GGIKzjszb9D5wuY/fW34b60lJZdxELt45Y3Tt2sEnoEurFp26tDQ8chudld/w3Dk5RWMJ+T3MdG+AVuAWQrrf7NTf9fitT565snqvnWyKPaSuXaWuXset68osqGxMpnIe/LG6an9f3Cz1cpPvl64=
*/