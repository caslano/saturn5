#ifndef BOOST_METAPARSE_V1_EXCEPT_HPP
#define BOOST_METAPARSE_V1_EXCEPT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2009 - 2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/is_error.hpp>
#include <boost/metaparse/v1/accept.hpp>
#include <boost/metaparse/v1/reject.hpp>

#include <boost/mpl/if.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Result, class ErrorMsg>
      struct except
      {
        typedef except type;
        
        template <class S, class Pos>
        struct apply :
          boost::mpl::if_<
            is_error<typename P::template apply<S, Pos> >,
            accept<Result, S, Pos>,
            reject<ErrorMsg, Pos>
          >
        {};
      };
    }
  }
}

#endif


/* except.hpp
8TM9E8RPiPYRfrrrdn1sfKJYvyfdKxHc77jNbzcczzlu89sdgC9x3MaHjsDvrhLrU/ZOBMuDysefiN8fVD7+JDwXVD7+ZPxesT5mpg/bi/U5x+Lu9nb+/Dh8ies2P8+uUf2wfP/mnvjqFpXzK+yLv+O4Pb/98Dcct+eX7sfztZVYXwh/3HH7fJyNX+S4nR//dG0i2Mf2Dz/ifL8GJcz8WfP9wpe6br9f+GKxvsBkfI5YX+Bs/BQxPzscnAiGV4n5U0MSOj8RLvMT7Zmg/1fkT8DTjtv+re54d+P1A5z4R/xqsf+J+JUiP+/l+JSg8u/bgE9y3OY/SO2VkP0bGTzfonL+gan4Q7id3xOV7wr8l8Z/eDAu3y348cZHLYvLtwA/zvg9eHN8/z66/OG+CfKfxuW38f198U0831nHez4U518chH9lfBIe9Z8MxovGH8RbR/M78I+Nd3k4Ln/65+y/TP9J51L5Dsc/4J9h7LRP4vGTDP5e5E77ZLto/Sn8dePrH4iv7xL8AuPjHnS+X+kE65/F5bPxc7Pwfvi2jrftE7//ZuN9jT9/Szy+MxfvZbzLgrh8y/HPgi39fLz5bXkA7esy5Quj+Ei8PV4dO/0L8fspxKsdt/FVR+HPBlt6tTM+fDT+jPHpePP1G0H7QPWP4S/zz37m/m1d8vyBCfo4Kq9P+w5+YBVHi9yMf7+LH+C4Hf/ufxD3bxC7Hf8egH/puh3/PjQR3CPaN+3wxaJ9swN+m2jfDMVni/bNJPwo0b4p4v8S8f8b8O9F/H/t6EQwVMV34xeI85+LzxHnfxF+tuN2/vk9+OFi/DM1JhGsUfMb8NVq/cvDEsGC0vt9SJn1+UbjDXh17Dw/8fy3Mfhlxk/Bo/lvh+F/NP4IHq0/eyR+oeO2f64hkwjWifH3G/H3ysw/jO7/m/B3HLfrS9+LP2z8Gjy6vpvxk4z/tNTpnxubCI5oG39fbfz4C/iBbbHIzfpGL+L7GD8Fj+LHX8KHGH8EbxXFt+N3VMdur192ki7fLFyVbzauyjcHV+Wbh6vypc6kfto6rn/Z/rnd8dNwO/816p/rh0903K4v3B8/1HG7vvAA/BC80vzXTD3fF/H+rsf7ivGDJnwX1f+F9xb7T81NyPldQ3E1v+tQXM3vyuM/F/MLX8WHifmFb+JDxPzCt/A+rtv2428TOr8jLvM74mp+YR5X8wtfxdX8wjdxNb9wDa7mF7a8MCHnFxbwPtv/f/l2LJVvPd4RP9Lxr8fH/ftFvL3xs+6N+/c34KHxlXg0v+47fDvju97n3P8LEsFfnfLb9Y+n4zcHHNPxe++Jr99Z+LXGv8Sj65dpTOj1P/Fj1P2BH6XmT+AqP3EBV+f3E67Ob6uF+vwK+KoW8fnZ/pHV+OuO2/6RD/EX8UrP1xr8ebzS85W9XV+/Gbi6fgVcPV/BIv18VeHq+doaV89XB1w9X4Nx9XyFdySCT8LYbXzxQfhN+J2O1wyJz/9Q/Frjs5fE5ZuAX2j8FTz663h8nvE973Hmhzxmxj/M+P44nGczeNfx3yyOn//j8NHGH8Sb7z9c5kfF71LxVY97nh9clb/FE7r8rXFV/gb8glaVn5/5+By80vNzBT4Tr/T8XImf1Uo8Pyv19ck8q5+PLP5umetTHT1/+D8ct/GjM/FXRP64s/GXRP642fhfRf64hr/Sv7Z17Db/SA7fF9+2Zewt746vxjN4d+Mj8OhqvIhvb/waPPrrJbyD8R/xqHyNr9C/Jd4vi/ATgsr5S5/Chzpu21epPOMrYn3S3fFNpv7ftk9cP+6Hf2d8DB79Pv3xb43fjEe/zyB8veO2/pl9NRHMd/o3bP14Fj6vTP9Gy6j+jp8=
*/