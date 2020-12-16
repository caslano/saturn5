#ifndef BOOST_METAPARSE_V1_ACCEPT_TAG_HPP
#define BOOST_METAPARSE_V1_ACCEPT_TAG_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/fwd/get_remaining.hpp>
#include <boost/metaparse/v1/fwd/get_position.hpp>
#include <boost/metaparse/v1/fwd/get_result.hpp>


namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      struct accept_tag { typedef accept_tag type; };

      template <>
      struct get_position_impl<accept_tag>
      {
        template <class A>
        struct apply : A::source_position {};
      };

      template <>
      struct get_remaining_impl<accept_tag>
      {
        template <class A>
        struct apply : A::remaining {};
      };

      template <>
      struct get_result_impl<accept_tag>
      {
        template <class A>
        struct apply { typedef typename A::result type; };
      };
    }
  }
}

#endif


/* accept_tag.hpp
/71fXL8bD0trT3yV8UQ/Z//2axh/K6cvVWV9xJl4R/xEx399LprfPR9va/wvfWOV/v1cfHPjsd2j9HW4lvmlZhv6cXilf399tP61fbX3Fz415rg9vwM/GN8odLN/3sv4RMft/nm33RAP/hhEbvfPK9wYr+yf635/l/JnbsZ/4PqHOj5vUjT/egv+vfFGPJyfuxVfZ7zTkdH86534F8Yvwivvh1uY/1Xzi3hWeHAr86+i/xDD06L/kMEHB7XH70fg/VT9gu+g2pf4GPf5tfGJ+GjXbXwiPlz0T1K38fvU+B7+pvj+Kfjr4vun4cvF9+dvjwdnivp5Jj5b9f/uYH5FnY+O91Hn0+JyfgnfXXgR30V4UE//UHgG7ya8gKv4y0Z8X9V/xvdR+0/NN+8/G9+IDxKfL+DDxefn4EPF50v4QBX/he+p0r+A8R9Vfj1eh7dQ71e8nfBG/KrA+WfzH7/CRfv832nWT9nzXfBJjtv40uRd+vNtcPX5Olx+Py6//27iW9T4E95FPV/4UPfz9vnHhzhu828evr3xG/vEovh5z/VXeK6/Tl+f8/d5vsT1e+PDxPUn4ur6dbhK/zxcpX+x5/pNuBqfz9yrx89z+DZq/AVX77cGfF/HbfzgUnyAsz7Oro9N3kf8sxpfwDuq+W38N3V+F75O7L9Th3/quG1f/Yb/UexPXLxfj+834gPU+r+FtL9F/ufwRJX+5bZlPwH/LeB/R87vi9q/efwn4w14y3B/OPxH40H7qP02G//Gcbt+p2GRTn8TPq1K+3ePsscf4PnAswHujE+0C89nxXczzvhEZf1LCu/uuB2f2Anv4rgdn2j4M/HLYn+Rl/AR+ETHvz8sOl/iNXyI8VP/Eq2PfAMfYPx5PIzvfRPvb7zbg8784YPUT276bPsd38GsH9yu5LTf8Q7GZ/wW3f8FeFvH7fnYd+JbOm7HR1KL45XzpbeqFh+P/yTmJ0/G5zpu25e5h4hPEu2LKXhOtU/wtaJ/sAb/UvQP+jzM+kuxPij5iE5fG1ylrw6fFBPvB/zwyM3n+c9H2R9RtM+zj+n7Mw5X9+cOXN2fusf175+Hq9+ffILxN5G+NvhHIn2T8NNE+tJ/ZX2aah/jR4r0NeBT1PzkEs/1cXl9/Bvx+xfja8Xv/x0/S/z+0lKdvjW4Sl/uSU//Cu+m5ufx1sKL+F2ifbQMX+C4bb/+Bx/mul2f9ZT+/fNw9fuTT1O+1PkN+HR1fgM+TezP2oC/IH7/Yvzv4vf/hB8ufn/D3/TvX4yr358uxoOt1fwI3lW1H/Ev3PPVbfwL/pHr9vlYRnyDWB+xGF8t1nc+hr8t6u/GZ5jfUP1vvNFxm/9tn2X+13Gb/yV8tHr+8JEi/zPPeeLXPJ7zeN7jBY/X4QcHtdcP3YKPDvjfjh/WObraEry78WnrnNL2PO0PNf7t8UzotdrXuKqf8h4v4Lur+Rd8pIpf/DvxWyq+6B//218nX2N/kTpczS8UcTm/jav44OQL2tP4Dip/PV7n8aLHm3CZ/hf15zMez3u83uON2ulgaE97PIf3UvFZeGvhDR4v4ur5KUnn33LtKY9ncJW+rOfzeY/XebzB440eb/J48mXtaby98BzeN+a4Hd/He+O11g9Ow3dx3K5vOAdvYzw9KfrrFbxo0jdlt6h/XXrFE9/8qvYUvrHwdOi1xuc9n896Pp/zfD6Pf9msvFValf0xzsNX4e0dn9ohWh9cwN903ZyfPAd/3XF7fvL5+ArH7fnJqZXMPzaP0mvnT4fi/fGzHf+YArFJuD86vofxHXeN5k/3xdPG/4iH6RuJ9zL+T7wyv/sW7TPAtq/7l///N+DX8j/edvzgntH88yarWL8=
*/