#ifndef BOOST_METAPARSE_V1_REJECT_HPP
#define BOOST_METAPARSE_V1_REJECT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2014.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/reject.hpp>
#include <boost/metaparse/v1/fail_tag.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class Msg, class Pos>
      struct reject
      {
        typedef fail_tag tag;

        typedef reject<Msg, typename Pos::type> type;
        
        typedef Pos source_position;
        typedef Msg message;
      };
    }
  }
}

#endif


/* reject.hpp
N2j1Mf/A0/z3sy3Et5pcvcgInFuL49/XXV/B6/5JBVb+/JPr/o26DMl2+2U+z+0hfnNjMR7LvDJNw+vxUZ8JXvti4tudyHigFY/3RfTXF3AX/zD011sFUZp5WlHI99flOd6poLE/n/mjDk2zkNNqL2G/757JciIdyYV/uUKXt+PtHAO34+08lo23P/jf3kW4wMimjGWDtD5TtXEZLq7w33/mFfjvP2tHjejNeeU3YzxWLDi7x72sQts953tSL/RnLs5MLxeycXn2rdorK3TfHVMgzhyA+9UKD7tG0HJ5cw2tryu45YXisnobTLzz2cx1Zh27Oabc9RW6nQX5uTGGbhR9PFf4Fto7kzcZeVQbXbk5Wmvwe03q7Yz5BXruOMbo/nwhv81Gtt9HmupUZQcDTXs8pxWv9Ubed0CeGyawPH9k9OIuSte7dzqxT9s4Ae/OC5n+uJhsKcF3B86txfgmEMkU/pmDefEy/bmR6W4TNJ/3qP6zd1kRD8PIfW6+pjnXvOv5YIXQEf1tDjpi3skyPFK+ovewgQ8a+KPclyYdX368Kf+4GRubTHueELKeCBlj3lX76ycrRD+ab593GX17RtRZH6M/f4C9+gAx+KiLt8XvTV0MdXlmKdLYmz4HvVs8vL1zBTNdA+GN9f4OaewsDHSfrxjurFwXYe5MLmhtAa3zcZ75p4qQBrXD+7O9UOEknKFiAwG/ZeA+I/j0nytC32ki3YZY+GFcN4cg4tENdrcNHC18Q7s7pN8n3UeM0qHMk/Alje5qbq2QdzWHfxPEjf0twpa+WMHn3H81dvWlCvczflVYQ78MXNBQZ8OvoMyfMQf8A2VeBd5qyDIZ0hwcaKMzYKQJeyDdlU6RUx78TcNau6O7srS21zH1BoPwjTY6SJZ3Qd3pbrDtQNwpeE3IJ/9D9b9vD7VD7RdfR3veEDJITUQsCrTtLVcn9SPd7mS+KU3Es20dS+nuto3Zfh0n+pXQR7+t+B5+PGG9TGsZfT47qL5f7xi8y3YVuLnrx/d5LQ845WINVG3ujP2b7QX8EqQPDeVW6vpcvq1vdKWJKVjKNN142lRo/LmAnypgfH7/hNOXmfRck15SqtOdpfH07sV+u93AW016pUk3cVq912LjNhWiPYeb8stNOm3Sa0y6mdN+XkB9i/FWzW3mTtkelUIO8r0E5hM/XS5Rqdtzh5mXKgz8c6UanjRwO09XG/htBl5r4CkD39PA7bw+ifUN8pdxkePjZO1taFabuXof0MxYmozP8ztoTjM0m4ycpht4s4HPqNTvnI83b9vPrNRx+Ut0fF/ij8tQ2vtNVUIH+H1zg+d14JOi7lXQLVn3pyoZ36VLJmq64wOmLenOqfT2lOA0L/GcMq9Sr3PrKxlGvCnYAtBoqORvu8+LOW9hmM/lF1XqNdBilgH0K34cLOFy0DttN+6E3UixHVE+afcXq1jbRJ91ORXdQ1e2jmLnKRr0NkOxPltLm35YofTQ12PrWGnauwo/+17iZyp5XrBysXeJD1f1xs8zR1bmflOsNjhH5fJPP43TbnBSMXV1sL5SfzP8z/iusZrhmBfNORjDiX7uPvZzDKc1tXnfguBdlfI8ge1xtdGpnqi/J0Z7GtZTylN6us7oxp5RHULm5xUJPzfUkRF4KbEGsN9L1wu5Xj0+vg83inaPK3I/41/FNLA+yKVxbIQDfpLgRb47eHwlx17AGTHkYuYXgn0BuGQTgcs8urnqCjNfnFzJ53Ss/yw74oXK6XO6U+VYAC7h4e02PRZO97Yq//YCtkFnGBt0prFBZ0VyBYzy1Xess5U++Z9rr43xfq7kE+3KeD553gaf51dqX2Z7VnWhgduz1osM3J4=
*/