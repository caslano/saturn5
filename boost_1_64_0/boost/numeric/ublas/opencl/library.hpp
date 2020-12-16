// Boost.uBLAS
//
// Copyright (c) 2018 Fady Essam
// Copyright (c) 2018 Stefan Seefeld
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or
// copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef boost_numeric_ublas_opencl_library_hpp_
#define boost_numeric_ublas_opencl_library_hpp_

#include <clBLAS.h>
#include <type_traits>
#include <complex>

namespace boost { namespace numeric { namespace ublas { namespace opencl {

class library
{
public:
  library() { clblasSetup();}
  ~library() { clblasTeardown();}
};

template <typename T>
struct is_numeric
{
  static bool const value =
    std::is_same<T, float>::value |
    std::is_same<T, double>::value |
    std::is_same<T, std::complex<float>>::value |
    std::is_same<T, std::complex<double>>::value;
};
	
}}}}

#endif

/* library.hpp
gbkLOmaDHsZCWCX4J4L/4NHQiU52HnTOh57dsF8JqobMU9Dx0ijsS8DcCLchwD4P2a+Cd8po/IK3A/Qe+LsL9D2Yt8J9LXR/GuF8Fby7R4Dgz69HIU6w/wG6H8fvlZA7Ngr/8HsEZGbh98vgd8L9QWD3gncMeF/B7zX4PR5x2gxzG3SfDdx9wzE2OAbpB8xD0D8VYWyAOQN/fgC5CxC+DbBvAr8Gv5ceCwzkX4bupUcBMwJpCNlauM+Cnz/D77fgx6+OY+wB2FeDfgvzLtDrcPvrKMQJ4fgH6IPw2weNgXwK7nPg1xLwX4B5nI80gex+hPM6yPTAr63wsw7uY8H/NsJ+JsJTj/CcDvufIHcS6EKYP4ww/R46/wG/Pw/MFODr8DsL9JXRkEU4HgX+fPgzAjqmw30V5O/i6QaZ7aCrIFcDP2dCVy3c7gRmL/z6Lvx4J8yHjkQeQv8CmIeOQloeBxnIjYR5MPDzoOs2yP9yONygpwO4i6BzIzBfAibFywlkB8H9KcgNhr6b4LYIOq7H7xVwG4U02AI9X4e+CyG3cwTyAv4kjoAZGB/58Ax4O+D2aWDS4G3H7zfg3yHQ88oY5Ad+nwBtg8z3wb8U8nU+9AH7a9DlkH8WvzmuF/QidDweRRmF+byRSA/QSGAvho7b8ZuD359EPI6Dnsu4nbdW0FsBHSOiiBv8/A3PX4T5SdA3Ifd+YNfgdzj8ugeyl8CPxXD7M8y7QCug5w3obQa2Cv4Oha4XwP85ZLrA/xz4y2HeA/4YpN0ZMA8Bvwf0Dci/CbIHQ/9V0Hs4ZJ6D/MmQOWkY8FGkK8x/GIn0GQ0ewvJtyL8Xv3thHw3312EehbD9FNhTgf0FdE0Ar3UUyhp4d8GPL0PureDfOxrhhr+v8TID/cePQbx81DHQWbzNgH0TyIPcWui4H7gO/OZh/xR0PQzzVNCMMfALv5fBj8OOQ/gOR7wQxhNAb8D+yDDwga2ETHIE4sPDj98jRiM+MDcgDiuBvQLhuA+/Z4H3R/BuPRp+4ve3oDboWAe386C7EXIfAm88dFeAd/QoyED/1yDz4mjkyxEIE/x6AHpqIHMz5FdApgXY7+H3XqTtB/F7JtwOGYMwwb4N9pfh39P4XTAG6QT97cD/Gtj1cG+B2z7Ifw5+jIN5HfgfQByqIDcRer8K+3SkyWPAXAP7kfB/DPQ8Dvce4H6F32dHIUw8vxHWO+A2Avx3Qm6wj3wHL4Zw+5D5IXR9Eb8v4Xcc9C2EeT38msvrCOJ3A8yXQ8/VwG4CvXcY8huy+RFIF55HsN8GuccgcxR4PwYdhv5lNGgKaBZoCagD9C7QRtBm0D2g74IeAz0LqqioYlHQsaDJoPmg5aAu0LWgj4G+BNoFegL0PGhQZRU7GjQVtBgUB60GXQ+6HfQF0E9AT4MGRxAm0KmghaBW0GWgDRHoBn0R9H3QU6C/g6qrqthRoEmgc0ErQFnQRtBnQQ+A9oJeAlUfVMWOBI0HzQA1gdpA7wbdBPoU6Bugh0H7Qa+DooOqWA1oHuhi0DtAGwZBFvQd0DMgVo0wgE4DLaiGTtB7QLeAPgN6qBrhBb0KGjW4ip0BmgNaPhj6QNeBtoK+BtoDeh7EhiAdQGeCzgM1g94FuhF0J+gh0K9Ar4GOPBg6QUtBWdBNoPtAPwH9CXTU0Cp2DujiodAB+jjoc6BHQc+Aqg6pYieB6kGrQdeD7gY9DHoC9Cpo1KHIb1AjKAW6AfRJ0DdBew+FDMg/rIpNOwx6QO2gdaAPgT4NegD0I9DToEgUsqAZoOWgHtDGKNIK9AjoWdDBh1exE0DngBaD2kBXgj4G+jzoYdDvQG+Ahg1DnoIWgXKg9aAtoC8=
*/