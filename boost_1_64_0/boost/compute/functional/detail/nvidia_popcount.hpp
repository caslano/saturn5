//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP
#define BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

#include <boost/compute/function.hpp>

namespace boost {
namespace compute {
namespace detail {

template<class T>
class nvidia_popcount : public function<T(T)>
{
public:
    nvidia_popcount()
        : function<T(T)>("nvidia_popcount")
    {
        this->set_source(
            "inline uint nvidia_popcount(const uint x)\n"
            "{\n"
            "    uint count;\n"
            "    asm(\"popc.b32 %0, %1;\" : \"=r\"(count) : \"r\"(x));\n"
            "    return count;\n"
            "}\n"
        );
    }
};

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_FUNCTIONAL_DETAIL_NVIDIA_POPCOUNT_HPP

/* nvidia_popcount.hpp
TlTJW4KMOfQHrgSJxOjz9h8FZil7yEOlJUEgfX2utrtsrMzVq8EeeoyqD+zNGDoddbVsTaTdB10bQ7Cp74U+NNdCNehHpC3swzwEuuyuRYxpy164D8oo7NOc/9CcpC2V2vQ+8ga9YNOftzDlNv0Fqxywoc+dIA/QC3br/EIBo4oB5qJZTjcLolwEFZtrwlMfNjF5p6MhWh4ea5SFPtc6fl/zMnONcaEEY/bL+RddTtI7dI9iQjaY91Clv71/XFvRHkLWEtLMW9+5ffNQ2NWweZc7bG2+shSQCBv35Zr0dqfejdt8j8XcgzmagZF1Q/3nbleOM+uXmxiydNgnzG0OTea/DJl16TpfGuAWrZOb/ebSRMbLaKMCnTImOvZ8Nd16993s12MTQyakBGRomzuU0GUFMf+7GOhXY50EHaff8mOf8R7pGSlf4m6qDHL3PTnejQeEzfsoL5bQO0QHbw8w89Xvx5h7IWOrbPbci9aH+/smDe/BaJ/84206VV3rqpZNW0qMfYECTbQ89ODdXDpvdNDzAt3WHePcoutJwhxDMzAdo23mHmFixGIR+tSh4Y5oU4a3TQyUzxLmol2TzkdWBJkp0Ow2OrDbACMPbWzR1cjT9FOJScebJHr/41embPHtjxZso99YNDq7p2n+3a18iSdNO2/ROD8tyOozrkQ0cu3zECfp3Z+I986wj873LwcLvXJfA3Ta+eolFc7du09hP2tMub9n4xKg671yTT9sIL3lD4Ju27wap6/BZ6Nt2CPQXFtA83cRmHK/y5Fsi40ZbQE5ugNwpX6XA9BL/S7aLi/FTXQMzpcvCXq534WBgJnpd5kHZrbfZRWYUr9LB/EQpTiUCXm5ANxsv8tFYBy/C/YZQS/4XY76lwCtzO+SI+1sv8s+MLP9LoczMDIr1PcYuNl+l7mvAlPqd/FBL/G7IIYR9S74XcZID7+LHueglfpVtEwCV+5X8b4G+ky/yjwwpX4VtNnRJSwcDUWmo/q9HepHHeukx4gcZ4jF9l4EWrnvBftv13JwRd/LwYLKa7Zf5WBZYU72q/jfv6zEzfarjN8DzIl+lfMfBK7gVzm2aWg+663xCXie6Xs5fvblJaboe5l7DmgF38sq+nm27+U8MOW+l33wV+57OQS9xPeCcQweS9dpxzRHunR3nTZ32sUU12mHKKfc97K6jTxKfS8+ypjtexk7GHdddAweDN8L9AtoBd+L/4crSFrR93IA2mzfy8EfgSn1vXh/Ar3c94J6zfa9HAEz2/cyvwNMwffi3QO0Ut/LvEVH02r6s5WslfteztO6RNDLfS8XQJ/te7kIzGzfy6l98HGi72UV/Jb7Xs6X0rVePPVN1R6zfS85MLN9L/vAzPa9HAIz2/dyjLF+su8lT6VOme170XX8jYst+l5yYMp9L0fQ+0Xfy0Xaoxe0Et8L+hOYUt9LDvps38s+MOW+l0PQy30vx6CX+17mngZ6qe/FB32272UMTLnv5QD0ct/LEejlvhfv6aDP9L3MAzPb97IKzGzfy3lgZvteLmB8FX0v8w9VMlX0vZxaMmiCpMc00pX7XvanV5P0ou/lELRy38sx6LN9L3N7wMz0vZz6DDClvpcx6EXfy+qXQLN8L+fxvdz3cgH0ct/LRdBn+15OfdnFFH0vOTAzfS/6HnQHS5q6xvoDOg/02b6ZY2DKfTNzRy696JvxgTnZN7OK+Q++GW0DXHfOocGahC146KTfHGvfiHdP0Gy/DLN7pYAo7PgkLOVqrb/ugrqV+YXGmDPnLZxrPoxxPnEmjg56Onx6dz0B6/B5sIFxW+ZvQvnHqHsJzil/7l4nYGX5sO+ALfqbxqAV/U35J6UOm+1vopE=
*/