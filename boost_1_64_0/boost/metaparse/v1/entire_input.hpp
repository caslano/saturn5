#ifndef BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP
#define BOOST_METAPARSE_V1_ENTIRE_INPUT_HPP

// Copyright Abel Sinkovics (abel@sinkovics.hu)  2011.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include <boost/metaparse/v1/first_of.hpp>
#include <boost/metaparse/v1/empty.hpp>
#include <boost/metaparse/v1/change_error_message.hpp>

namespace boost
{
  namespace metaparse
  {
    namespace v1
    {
      template <class P, class Msg = error::end_of_input_expected>
      struct entire_input :
        first_of<P, change_error_message<empty<void>, Msg> >
      {};

      template <class P>
      struct entire_input<P, error::end_of_input_expected> :
        first_of<P, empty<void> >
      {};
    }
  }
}

#endif


/* entire_input.hpp
JPzLeru3p/B5jXb23ivs1Xoanys8gxfbX1v1+l8WP0Drv8f31+bf4GcESvwePlibP/CeXr6k4y1LeNrjWY/nPN6Az3b6H+T8wV/wtFj/+69DbPu1SZ72ofB/4eavvfHRwtufaX/fffCLhU/Ei2+79+lf1eav4xuc96OsH/XCVwXy/W7rR33wZ4VfhJvSnItPF/40bsqf+IDrF5RvPxyDzwzKtx/64fcp/avH4jOU/tXj8OlK+zz6oSf+A2+vjd/hl1aW/37ejp9TiVmn/mmf/yn4MOGr6pz6DV4p/MPH7fVdh1cIP+EJ5/w+5/2uvf/wjcrz3+2/hN0HlFTVHcfxtyAWWGYeRQVps4igCLgUNSqYQSwIGAesiGWpmkRlUIMF0IUYNTHRxd5ZNGIBdTCKBcuiYox1LKiJbRBLFJTBghok5nuSefsu/8z8bs5JzJ6P77373rxyy//+L/6a6j9bq+cn1OMqf34D3kO1r/X+eVnS/lbj13hrdf64Kl8ab6PuD3xIVeXrNxYf5Li9fm/gS8T6OIUvmL+k5sd82TY4R6x/2Q6fWeb5ahPNH8Wnl3m+WkfxgfgvHbfxP13xyeL5yuFHifyOS/EjjM8BW0f5N/GRjtv43+X4AWJ+a2o971cxPlSDu+dnj98bP1HEH++OHyvij3N4axUfh8vxX7xa9S/hB6jvL67mR6SLev8ZvJ96fvHfqvYjPle9PzYwPq/yD+J9xPb1uHy/4NsIb/Rsn/N4k8fzHi94vOjx4CvtocdTHq/1eNrjGY/X4aeI+3ciPk3cv0W8nar/f038n8qPhx/puI1POQTv5rpdHxxXx2/0eJPHCx4PvtGe8nja43Uer/d4o8ebPF7wePAt3xc1PwU/wq3f2/Xf8LGO2/6fmfhox23/zw14b8dt/08BV/nBw43a0x7PerwRV/FrOY834TJ+ED/JmR9g82t/ju+LHx87+QPi8fX1+BDjNY/F4+v/wnc1fiYeXd+dvmsbbAy29Lfx5vbv93H7tVO588PPb2ny8+KDo+8nPg6f4vg5Q6k3RfPr8DHGH8bbRvEL+MHG2wwLUMrPf77GhxmfgTfHf2yOv49dyz2f+PAy62NkS16Pd9iKMjmeeZz/lsp/Jf5Tyy29AR9WKv8ifK3xNXjfKH4IbzJ+6BPO+qotEkEn9XzjHdX3rWVC1p9CvIOoP9V6PIPf6c5/sfkL8Evw6thpHzv5C/CLjNM+jvMX4Bc6btvHG/HPqxy3+T+3ThD/XLl8y/Fd8E6xM/4Tl+8xfGfjS/CofI/jNcY341H5PsTfbRG7Hf9pap0IXneun42vewGvM+ff++J4/P1F/ETjFz0aj7+/jh9t/C08Kt/0Ngn6t7f0fZc74y+JRFDrXD/b/zEBD1tikZv4v+PxhOM2/u8EvNpxG/93It7acRv/l2mfCP7mxifZ8uGP4qb/IC4f/rDjdvzqBHyZ43b86kT8Adft/IAdOX9VP8RV/+FAXPUf1uEyvyk+Ssx/nIGPFP3/8/E+Yv52Hu8s6g9F/EIR/7MBnyfWj92Iz1brx3ZKxO3TMvtfiP/ScVs/WYRPdtzWT17D93Lc1k9qOyeCm8XxB+I3iuPvhV/puJ1/eTx+quN2/uU8/CAVP7NTIuhWVbl+0xHfVuT3ynZJBJfjld6fs/B6s37Pknnx+3M2Psv4Wjx6f87BzzU+9Lfx+d2IjzW+AG+OX+imv48NeDcxP+dqfEc1PwxX39cC3l3NP7Pls/nVu+vvcwpX39+0x+vwA1X9FF8h2ncr8CdF+bfrkQhOM97/ESd/Hu4e316flfj+4v2WSiWCvHP/2fl5NfjLjtv44t74c47b/u8++LOO2/7vXfFnXLc=
*/