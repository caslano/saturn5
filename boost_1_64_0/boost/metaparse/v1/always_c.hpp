#ifndef BOOST_METAPARSE_V1_ALWAYS_C_HPP
#define BOOST_METAPARSE_V1_ALWAYS_C_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/always.hpp>
#include <boost/metaparse/v1/lit_c.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <char C, class Result>
      struct always_c : always<lit_c<C>, Result> {};
    }
  }
}

#endif


/* always_c.hpp
X/wap39L9k/cj19aon/MjH/Oxc8Tvhw38wMX4sOENw3b+YEP4kMcl++n+CNVwcsV5fNPD8QX4DL/tLk//ojPE37xb/b9fjI+13EZP34qfp/rMn58SVWwVinfOny+Ur5/4RmlfK/ic5TyvY7fq5Qv/k/6R0p8fwYVync8/qUZv3bq370K5avBPxaeww834+d43rhT/+5W+OsG/BHHZf079WRVUKOsX3YDfqJw4iMKSnw+zuk6zjYJ+zZ5Bd8hPIeb0qzDfxHe7Rin/+mpquAsLb84PsR1+XzhS5X1ERfh00R+81/Ptv2nj+JThE/cw1mfAj9FeA4vxrcs4/ukfN9W4Ecq+YdexfdX5v9Fl4vxf7F+Xif8osK1xQv5yez35QB8pPDFuPm+9MNPEr4DD5n4cnyA4zI/WT3+H+f9IudPvIm/UzDj9B8WlHsV3yx8VZ09/w/wnPCWw+3V2I7PFn41XvzrWeovSnx0Y3w/Jf/XLnhHx2X7LoEfFbIux79Ox/fC48ZF/9lQvJnjsv+sDq9yXPafbcS5P6zL8a/nqoKDlfnP6/FS+R/M+/MNvIMSvx19nvF/Z/6D7J9th++CR42L/uMYHjgu+4/3x38OrMv+44Pwbx2X/cfJeuo/zvtH9r9Pw0cVrqbxzp1t/WIGPkL4yL/a8Z978fOEL8WL8Zcr6J8u8f7tY+4PvG8Ic5znt5h/YgQeF95qjr0+l+H7C78QN8e/DW8IdvaFuzvt41XEz5Qo38Hm/YK3wvdzfGOVze92MB4V3iJs3581+LpgZx+Bm/INxF8Wvhovth9e4PxLlM/M2XoO37XE9dvf9F/iIeGL8VihfJvxr8T12YFHCuX7AH/Pcfn+i73E/L4S5TNr4pyGN8YPdPzoiL1+Z+K/Bzv7eNxcv+vwZ4Wvw831G48vF36o8/vWr2b8rJEtn8wf+T7eER/gOONPBaVevIb+sQrjdvzJlK8nvtZxOf7UB1/luBx/anilSl2fbDveU6lf167j+Wb/UTc/0FrePxz/f/NrX9PjbzL4/lr7Gh9RuL+L+RGahoL2Zv/r9fmrWfwUZXz8SbxGiU+LbeD7q9QvOuDHK+3no/AuSv6oXvhBrsv5IfgwJb7uBvwsJX/WNHyA43J+wl34cdbl/EAKQ/tAi+/EZ2jz1/Crle9XPf6jFp+2ifhE5/su14eowvcIYY4vvtHWH8J4RPgXuPnrbHx5sLMfuZt9vs/BnxY+Ey9+3zZXqeszTcCrlfrnJLylUv/M4oMdl+f/NF4q/14jEx+J91fiB9/Amzsu4yNjW5g/WOL4uxeOfwged1zW37riXZX++SS+tza/AW+nzU/FD9HyF77B/HQl/047fGWhbWN8bjP7+0zBTxQ+pIn9PtyBnyD8Ibx4/d4kvsqpH8v6eR6/3SmfzI+4Db/VcZkf8X18suMyPuYD/LCgfP9h+q0qNf9kBr+/RPswUvB5+L0l2ofhwt7+gV+vrT/1Nu0T5/0j818Nx98SzvkX41vOwzcLX46b8cfz8Q0l+meihfO/An9e6Z9JvUP/Y0jJL4O/qrz/P8MXKM9f/l3G55Tr/zk+Qfn+foNfrcxvS2/l+104drjU/Ydrz8cX+ErR/vzmGnu0se/RfhN+9a72+bga31v4Gtz81YC7+Qfl+oK/4NMD/rZO+8X2HwR54vcdl+3XLvh5jsv2az2e0PK3bKN/Xvn9B+A/K+OTJ+I/OS7zK56E/yC8adj+dTK+XZl/kH7fPJ+l13dfiY8Q539oc6f+9gHvV239FfwIxXN4e8dlfOAmvLWW3/RD6ufa+9vjMVyNP8fV9Qs8XuvxOk/5kh5Pefaf9myf8XgWb63Vr/H9FA8+Ij5c6b8=
*/