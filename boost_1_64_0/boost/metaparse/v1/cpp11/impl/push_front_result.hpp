#ifndef BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP
#define BOOST_METAPARSE_V1_CPP11_IMPL_PUSH_FRONT_RESULT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/get_result.hpp>

#include <boost/mpl/push_front.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        template <class Value>
        struct push_front_result
        {
          typedef push_front_result type;

          template <class Seq>
          struct apply :
            boost::mpl::push_front<Seq, typename get_result<Value>::type>
          {};
        };
      }
    }
  }
}

#endif

/* push_front_result.hpp
68588JJz9Rxt/eZJOsj66Wj4cUht+Dp73nCULemZXq4zT1yuYJ9eX8TxDO7Jp9v5astpNUtQF6tT+/TFobRJJbpkJs78dC4tuRPmy9mOL+Mw3NBsovnC/8W02yDz6zRM/QkTGz7AnnRJz3WRjDXL9WI1eZt+A5y44xbHHdR7Uf89BRMzw7aD8T2f1i1ue1bO6dcPc/2b4cIeGBjnlxYt9VrEx2T5X3CS86n5er8I0h6xFjUdx7BV4jXq6Tvg1HoYci2f3hfL6LO25OuTY/iwhnWq3eST3kLkdblOpxV03Nt/gLviZ+D78OUtuoBu2txHXaku2N5evljLqFuZ/9i/3lgYW5Q2vxq3HcD3wfrUPHhP230eU5vrN/dLp5ngaKAPt8HcKW+LqZXGLY5flgeNd7FXW3WvtYcOpfn2jLxJdL4T9upk9n6EBFg03jqU9aBL6JSi48RXRXs+YfbYZPh8C60mxt5fbQ6OrwVb3pxpLHnlRlXHdoflxn57kvWt3dbn88GGD4J7BKxPxetmGjd/oj7Pe3wL4+rPoEnkxv7ZNH0x1/gYlu+hvXHDjxPNHab8pqe6Q65dL4dPwOYPUqwXw5Em6fT/y/C/YvzBFnjkgL0V+CjxajVoX+vrelzX3K5fbT7lm6q7h9OW39NI+Pv3r8PsFdbw5erTcHq2az6jx9lpkuvQtxXr4FN4dB3NuovNx6xRb/NtmULGW92437O2PI4tacGVL+MZOX5ntaj4cC1x+an4OLhI/Y3brlfHFFzp72qtkWPgmZy9LAF3q6cegHPNq8XHp14x9k7FrXWlxfGX7oLlP5jj1jH4zjVug8tH6KX2l+iviN3mMGguLEqj78uOsFbUzrrCd/LrtBpT3Fd5CI+z/x2brA+wQ//r6eEl+mvr470P777HPaMz6ZXQKXWL6CFM5R9Ysu0yuTnEGpG8PztQf+lammSA/SzWlhrywY5M1ke38lUv4yr6y7uU6vrONc+y2Rs44R2151vxnqXxfB5ff9brhRXFfoK5m+m952i479TW8nJKC9rH5/cuFutH6DI6vlkVtikXzbDZBmvlw2rD8M74Ot4bfR5HwuKtW/DWSPX2OfiwU+7kgfv7ccI+PsPBN91K/ywVi2LuUboyibbO9A590t559f3705NZasq1yWqpfbhpsz4WX5++if7picPvhz/x+9ZHqTmLyFW2/4pPD9FLK8qyVUuaqyue2m0vFrstyU3v26cT04dq11XsfkNrPuX3wdZRStE5b4vX5uKhk/UsvYvptGXYQ6O/BefTgvPTVea/uyztIV/euDyO2+ItlV3updWmipkO1hgbqFlx9tvWXY5tpg9gy46vxbQ5ZFOr5XgDjtdl4zT9Snjct4M+qr1kA6padz3EX/A35RCO6GesA/WgalvDvVGe/1ENRFd0hx03603M+ko+4stvN6kPp9EZNMPa1WobmjKJll6un9aPjulHcyxkk5vb2MNknuP7WHuoQgttgMGX6QXG72PTNxqc7Dv4LZf1iHZ8fG1x/YFE+l7eFB+My/i2JHttgCcvNfulb3ujMb/yezi9gEatbh/BI/pmJfVt6+kjyodn5HfDmPm/CYNqqSFS9FIqweQD9EQddc297PsyrQtTllpPTiymlisqPxbTDDA/mhkuPaXnbpynrCH13gg74U1aY5w1lb6V78+3pCnm0wzsM/8w/t0hT9vH9ZRa0Brn5gZ6QfF9QUVomm/Z7EM6xbXeluPzrWU2f0+smkeRhWJvbIBj1iE7i7li8X0mesxqtf4JsYxaeFUP+38H6DNklxvf8wdsHwkzDiThBzGWmwZao7bIt0d92hxfwawqtNcHa2kCOVrqgzi20ORt8Oc=
*/