#ifndef BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP
#define BOOST_METAPARSE_V1_CPP11_REPEATED_ONE_OF1_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2017.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/one_of.hpp>
#include <boost/metaparse/v1/repeated1.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class... Ps>
      using repeated_one_of1 = repeated1<one_of<Ps...>>;
    }
  }
}

#endif


/* repeated_one_of1.hpp
d4nSlVzPsFOUD6Fu/2mivMgUZxTUCdo3aZnpeV2zJ47Jyk5NO1G59m3Wp9pa38l7ilwzSU7L0i2kpf5+m6XlpJyilJS+T+vSpOXIkJa+oVxX7ZCWlJCW/P22mC9dCio2p4/756RnzRbSs6jkvImn5lfOn+j4SasQyvPZR+vxJp4pPcsT0qOH6vQsR2Be1DbBdqYhqn8Tb7cvvvzloZ/Y/ND2Ih2/3L94fpyUY26hXljH7WyD
*/