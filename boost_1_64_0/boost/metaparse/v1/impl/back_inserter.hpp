#ifndef BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP
#define BOOST_METAPARSE_V1_IMPL_BACK_INSERTER_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2015.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/mpl/push_back.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      namespace impl
      {
        struct back_inserter
        {
          typedef back_inserter type;

          template <class T0, class T1>
          struct apply : boost::mpl::push_back<T0, T1> {};
        };
      }
    }
  }
}

#endif


/* back_inserter.hpp
+xZ+jJ9s3ddB3nZo+io9zCq+yMbFmqcqei59u3VN+9v4Z7PVWd4SpawhmlsjJ/KfO/LB+EUr7rQOb062+V6fGM+x5tW25tpNvcQy8pFx8vTMafcmT3FsziMX9I2xWjDDHBTwnO4DYxvH1rj+Cf7iILazeqr52nr2ev5g5orWji/bSxX0H46YE6wJXsxJ5u5Tdgk6OCD4zMLcY346wY9+jY276rj17dPs2AH2wXprzlN8iznGXNp8Y1yMzd15L3+MnEV2Io+3sNfWKYnmvLJt+cFtpdmfMJ5x777I89NW/Lei2oqLN5ovG5sHjGsTdrZKdmNCr/b47AD24SscwjEcwTZ8gJ3Bz8Jp2a9mh5AThXA1yqBCOD038iEWZVEeHdAOibgOg7HsZ2uHH6IC8Wn6p7X+3M32lSVb9GXoYvP5AWeSKwd9mwh+ZyDQhm5ea33zpBjtJbrz8Gj2+Rd9SR+j2PRRs7W1BR+4CpljY/K8x5c9T+8jxQEW8W+/MHcZi7HGtqb++QN7+xl7/WWK5wl0v0+q9d0jwfUqv8/a4PIUfvTr+tx88OJu/tr91u8z2PJm/JkFdC6XtTxZ7Wd+LjdMe8Q27mQ/69bQjsbWOtLX5zJPG+th7F9MirhcYb46nTr+k+d4dLP9neJ1N7IXZHohGRrfQbnzyMbdxrmceS4L+RUD2id2fnCqddw0sbUl/Meq7Eys+ONmPtRT7MlR8jmTvE4UL/rZWvkou35KXK+P58wjrRlmmU8HSTtp/o20JyDKs2P99/016r3EfDzVGDzkXs/x0Y+L/z5rPlWfwGZ2Qbvm5rOupAMtrD1+pLc3T/IsLb8xeNF+yho+NwafmmN6fWi+2s+fedcaytmealPptjn0kYmBK2cvz403V99r7bPGueWC/JkkdUyh1y3UeYp1U/Yo6y56TFez1PGc/n3zQXsyeN48k2KtMVBfGPOkH9n6G9mQ8vTVWC9ZS/e+1Z90sBM6Yvr1xv4IXTb/TVjEDtojm3tVhPgwP7QC/8OznbYP8WVO2L/B9660xtgnsyvmuc1koJo5lpsTeJ0P9qrnXEMOG/+VYgh8k/rxYgvWkqWM0y/rtDcXXZhlnr0sZrOefn7uc/5KHWUffIO8zeRnt1FWDPvEDyzJjhVla3t9ZQ3V1XOPuzx/TKWn6v1FSsAa2pxO7qaN4rdIe6U2G3XBXMjfbqpvZuurHJ6hZmX7qh32vKiY9WPwnPenYjAHXFtGzIeP+Jy2Psh/fZzvtlQ5RV7T5+JjFV/RjovWE1F8a+Oc3fgNMdedj+DDTOcHeZ5X/ZS5ztgOCj7zqGvO4YtseshcdwcffY35Qf17jNOP/Pguxfga+mBN8AzPeDZd3/XXN3OMf4UVnrUb76wB9vYkGc5Ot3Ibo7sir6w7yotLtO1lfcYWfqGO+xD9gn7gUzXZaJ7ne65hu7LUYq/IzAw+6DnryYkL2I/mfF4yV9Q1Z27X9/yWatebm/19y2v8z8ERV85TDVscxU7p77fFNweZyxPYi+jgPg1x+op8Z3K+Wxnj6fFIc9J+7Zn/ozUZW9SRjzlGrOGXzvSrJd1epn10ZyzZfGWDvudH7Wth/Muxo9v4GFe5RwJZ62AuK+h5k7mm6zFrhA+sSfl+7/FV8sh7jP7uMTflLycdhVEQBVAUc/lODeeyBZuM0Vo2rZk+f4fOfSm+LXZ1RxW+zlnP6vVdkcN8xlXsZTnPb5PkZbcOsf0zXrYmFPfL2drcxyYVMfc8qH9efondmcImiz8PjFBv64AccdrPDqQe59vr+3V12dXT2sa/HsT+PcC/7k0X1r1obiZvre2LS/zKONU311YhnyeN203BMqxrMgd/+4UNe5Q=
*/