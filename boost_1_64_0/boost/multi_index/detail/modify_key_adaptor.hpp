/* Copyright 2003-2013 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_MODIFY_KEY_ADAPTOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

namespace boost{

namespace multi_index{

namespace detail{

/* Functional adaptor to resolve modify_key as a call to modify.
 * Preferred over compose_f_gx and stuff cause it eliminates problems
 * with references to references, dealing with function pointers, etc.
 */

template<typename Fun,typename Value,typename KeyFromValue>
struct modify_key_adaptor
{

  modify_key_adaptor(Fun f_,KeyFromValue kfv_):f(f_),kfv(kfv_){}

  void operator()(Value& x)
  {
    f(kfv(x));
  }

private:
  Fun          f;
  KeyFromValue kfv;
};

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif

/* modify_key_adaptor.hpp
jRNlSX9kot2PAZOZGOeq1iqETtKxL0cLfub0CkW9GX7Sd2/RPfdX+oRFa9TVmRoPE69cDC+EG0gucBH+yBttQUVdCHMHkZ6N9lvMk/IJC1e7nf3wYBxKC+FJwuFKjNFwub7T9haoppGhluaOs3zCIdrhcuFlMbHtVIG0bnWV+My+b9VmRb0VKrPJd3SQwiK/0x8swpEmx0omM7HHiiGF8CxhcTVGip60W42i3gY/kU95kHzK5/mERVPCvVggD8snIrcQBhEOePZqt6UbzCQvMbjbuJ9OOkp0+YWDK3daDxNv/xhUyHFyr7Xi5N6BfqQqng/1jwW3OYzbkK6mY+OExcTGIjNtn7jOsk/cCaNWIn/KwWS3c22v0tVMOtoYt3nY88dvBfi+JQ7XY6yvH7e4RLX0LlhG82gZzaOjb/dJJsLudW7kYdn2Xy6AOvKdQr3iuCt/CUiiuJVlczqdFy+mO9qc4hBpr493tTa3uxoiuHzbj/KlAliP5GABapSFdT+pFt4Dy3TcAn032x2u2x9pb+gOdTryCjA52D6EL6YxuNHC4F74zINBjy8YOLuMy+Rgy8ELBXAjYXATepfHv50miUKzWkQY9BAGuXf6gIG72A0mB9t2/VgBHEkY3CxvWTgRlxhIgadonYUethgXt/bbNR3ODVTDuLuVhcHB1pvuS/eFhVZfuB8W5JMGRWvNuX7IQby1yjUEVV4d+t4COI8wuEV8vj+icZKiPsD+tCXUF37yA4OYq5MnFgNbTzq1AI4mDG4Vn+u+8QCdy3wQemh/c0aA4qVXudSTVBUd7m6aDOyYBUcVwCGEwW3oM3XitxQT9iEYQTb7/CFKDuJ3+SAH0Y7mmFsQkIPnTGIB79/cbu3fPAx1nrt8c092uY5SNXTnJWYxsH2KuwpgU8LgDrQqjBn1lqI+ImLmkqV6qJKDpX7IQchVyAKLgX0+N14Am5GefCfOgyvuuUxRH4Xjc/muRnVngMvxINaUjNd3TWgQn45iV5gc7DVTqAAa6AzaXagd9oy5jqzyME/HsxEL7WHybKLDPV2sGf5yGCHZYuH1+di9AH6j/nA32pFahz+sqI/DgXSTRO0Qmhs2cS0LspLJRJdrHJCFZ/+upgByyS5/D95L9d2YaxX1CbhWx9HX96v4g4OzKE8WC+8Z1SkFfB7xXjyBN+FGmh2fhMf0LSsiZQ3EwaXerCvpMGr2n8RdeXzcQxR/kzvZZHdTPdIDLUVR9ApxVdxBERRBSJPdbRNJmpWkaVpFSxHaatASd50NiqKou6UIijiqdcfRKi2qqq2izGS+v9mdX/zRf96PT7abz0zM+73v782bN2/evGeRcNsLud3oVuCg/NF1N3+4XfcuNzG0lIlYqEM8kYdyJm9CFwrGbtyzGw0EBktUJeOni8D5OzRoV5xpO/XJvMEg0sgOAkjE1y7cM2Y3LbXspnepyFVjpoDz3rZ5SD7LySLhnhN9uxl/6ytWDar3qDAAGzoTa8WhnshDiMl46kLByEJ2DINXLZ9zOzXtAbshq1MWJCbDvcCAzeVskXDPCV83yoINuYyIarbct1z3vk/LfbAbUqkzrrblC8Y6z/KxIqH6OvVd0lgbYao+9J9UDBbp3egYyIQyng545W7kAPuAlkACmhJ1LrjFLdcwykTsKRlXTZuI245Kj+nK1y1d+SEVufIftbDqythjMmpLm4g7XnJ9Nh0Fm/INZVsl1CL/zUe0qA+0Rg8i9WvarR7JRbiUawW1ibj33V9l0+HQF+ou1valOVW6dwWN6oYYWp+OHW3kjB01j1kyXuZoYYp7cRFx16z7JJtGYY68qaLKZ1Uinvhjak3BuSVyrc/7m1N3ltSz3bc=
*/