//
// Boost.Pointer Container
//
//  Copyright Thorsten Ottosen 2008. Use, modification and
//  distribution is subject to the Boost Software License, Version
//  1.0. (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
// For more information, see http://www.boost.org/libs/ptr_container/
//

#ifndef BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP
#define BOOST_PTR_CONTAINER_SERIALIZE_UNORDERED_PTR_MAP_HPP

#include <boost/ptr_container/detail/serialize_ptr_map_adapter.hpp>
#include <boost/ptr_container/ptr_unordered_map.hpp>

namespace boost 
{

namespace serialization 
{

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_map<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

template<class Archive, class Key, class T, class Hash, class Pred, class CloneAllocator, class Allocator>
void serialize(Archive& ar, ptr_unordered_multimap<Key, T, Hash, Pred, CloneAllocator, Allocator>& c, const unsigned int version)
{
   split_free(ar, c, version);
}

} // namespace serialization
} // namespace boost

#endif

/* serialize_ptr_unordered_map.hpp
RsbVqt24PmrmZl+B0RXE3GOmPO7IiAx9nXmZMVBLidPccZfRJRN2ibn3mvYyJ+XW3Rg8kXPvN23oNzn/lGfk05SrZ/tkncNM/+aCfrKenMMRpp8Edt5kZ017550NzM+K+9TuxSMpZ4xH5SXrxCX9aEVvrqKFigQcWf9Nnus5KHgi53yCq1zk+dyxosFPdqzolJ9o1q0v/pqAUY5xsih3vTEp2cep1roM3OjkDcZqNI94H4a5r2QER8rx6UYXQ6uUYUnNsf7WPbYuTV1bpXtxIr46i/Zsc9x07nG970QvQ+7D6jyTHzL1k8+5Q3fMQFyvU/qHc/Oc58mkvLzDLYnk5kifIvMY1o458Sl9gTi12kd6yS+I2F3xyYqNsVnhxABpx9beDs1nd+xtrlI6duqCFN+acJLrwtcnMWKeHCth2OHE6Je7+lJ3PeXduckijtWnfWYM6nCYprp18N4Voi9xfqhtnzFt/q6Q8Udp8guJrjg7oxyntrrJNax1+hUPvzkye7VYYyBoHgWUd5Apt3iY+gzo9aad3m+NXeOeYlN2k2stQmYYo085zrjyi63Crt7qahPoivYYR5KCeVptGQt2mqU4ea/bFeZZkKo76/NEjgVPI/Msbj7CPKNCeie11yq1Y1z3miLWaXW3Okx2NtZsviNvd7vaReMrzRhO5Wnp56LqIo6gAyXjnan3+u91+hU5ImfcDaI8va9y6t7vqttGXiMcSqoG/HfqPpS2rniPlLCZj4i6Ln/qvGdQ4j/X3b/HUsrQIOFDn3CvLxZldOXNHJ16Nk0dhSwVkEqnpy+Y+lq+TFKxokzLQVLvXnL16VTTqT1Hb3Rezmy1sHcH5iUxaEJisdccv24aabjn3G0XftkdT74l2so1yrz5O6I9dcwYRoWUnxQ+SufwDDKxwUvyrka2yD2hBulywuY9QmmxUFC9tlqUvSfmJZ6hd+E3NYyGGx6Zn1Mb06MOZTi2TcEn45xYjiSKPtSVd0GgW43siELe3WM+fv8SX1lVZXXcF0rIfj+iLBbo1zbZjKrK5NopS6LjQflP5KGT2/OEBStDst+NhgdSj/MEVlSzFEHPoLgorJ5HUFX4Ge80Z+Giji7URt5JE9vln5g16TyOWpRytvKMzskB6W11Y49vLOwlQhXyOKL8W3e5yeHY6/tOyK4dKE3edAxkUsSOnpl3hMADHnw2ebXvabfKa33vcYShZYy3zuUiWzq0rPFWvRdFvS3HW3nEiwVtuKlXm+HQtja0+zwOLdvQXhK0HNPfBaK/SXZb1d9m5v20nUmbv16Rs6n8dSykHbOKyXsiwgYtN++kNAVuGXby+0IOpo1PeUZafUqmWHkku3z38Tov4sq/OPMpGm/pcrC3O6pvtou2c8drGXFeh4AIybH3cZdrERL32axyn/tdkhUOfdB7ICvHp4nnzVORdh2vqOO28+nj8ASLA2QY+Ze2qC2h1DTUo+CCjDuqnDEKrYnEeT7PwSfzTbn9Qg464gTTZAtFrL6Aemah4aA+JjK3Vpz38jnPWZi67mcFF5k96tEvTtMmQZ8R5KUvxww6WLmWMosHBgrwwRrnHUSu93218rirwH5149PkQ7gVEzM5mB+qRw4h0KNrifclmnp8OL7ByZyYvXflNSTQZGOsb+IY/Vya5ejsv9g7D+g6iisMz+6SELrBBeMiyTbFFBtL7iYGrGJbtiw7klwReag8y7JlSehJboTQS+img+m9JPTeIfQeei+B0EsIvYV8Ozv79r55KyGTc1LOwSebJ/650+7cufdOn2ewp4z+SO/j3SwYQ+HeNthn/4f2D8Z76Hz/RuBozyR48LoJc11mjtQeyxmBs8dy7Es0+dU0tsk=
*/