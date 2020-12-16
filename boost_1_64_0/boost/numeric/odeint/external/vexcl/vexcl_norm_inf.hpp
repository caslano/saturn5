/*
  [auto_generated]
  boost/numeric/odeint/external/vexcl/vexcl_norm_inf.hpp

  [begin_description]
  vector_space_norm_inf specialization for vexcl
  [end_description]

  Copyright 2009-2013 Karsten Ahnert
  Copyright 2009-2013 Mario Mulansky

  Distributed under the Boost Software License, Version 1.0.
  (See accompanying file LICENSE_1_0.txt or
  copy at http://www.boost.org/LICENSE_1_0.txt)
*/


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED

#include <map>
#include <algorithm>

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>
#include <vexcl/reductor.hpp>

#include <boost/numeric/odeint/algebra/vector_space_algebra.hpp>

namespace boost {
namespace numeric {
namespace odeint {

// specialization for vexcl vector
template <typename T>
struct vector_space_norm_inf< vex::vector<T> > {
    typedef T result_type;

    T operator()( const vex::vector<T> &x ) const {
        const auto &max = vex::get_reductor<T, vex::MAX>(x.queue_list());

        return max( fabs(x) );
    }
};

// specialization for vexcl multivector
template <typename T, size_t N>
struct vector_space_norm_inf< vex::multivector<T, N> > {
    typedef T result_type;

    T operator()( const vex::multivector<T, N> &x ) const {
        const auto &max = vex::get_reductor<T, vex::MAX>(x.queue_list());

        // Reducing a multivector results in std::array<T, N>:
        auto m = max( fabs(x) );

        // We will need to reduce it even further:
        return *std::max_element(m.begin(), m.end());
    }
};


} // namespace odeint
} // namespace numeric
} // namespace boost


#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_NORM_INF_HPP_DEFINED

/* vexcl_norm_inf.hpp
VQ6amOc8pPO/A48w8BgVmy+rfR3LNb/ND/Lnz2+2KuffxwgedNpz/nLOCadl2YaW9mCpT9cXwjjxBoDwiKrPucqOoX9gaQPmHtk84PRdqWKeAV9VHF47zQcOMiLv6HFlAehyhynA6z5xIfMpKgry+RDy0eE9ZN5CezE+ZyeKLNA530GgPowsSwUL/QyMXU77++hEllfy4BpP/IPodIeZPAbCrpbxAHJEr3kON/3Yyv3DekY4eL/e9E/5cEexXNNZj7o/uAhxa0EfqP/9FOicAyCP8NrmWNCYl11nAhvw13UfBz7fd5wb3B6w/60o5R3BPeA24GUPeHkinWqLJxMxH9S5rrPN3UtN4Kw5zpa7dj0gAm1c6/Vf5eHy3kI/Agnq66395JvpesTZsbkjPJYCQx+zpv7eM/k8yzF3I3CR/q7+D+V0530nivw9EfL3Gvl7KH/SyP8FNe7pM9x9BrfLPsQZ3w9pg9tjfBh3DvltNrgzjN5+XRLgthi7z1ePJxhcvvo60eDy1ddJBpdPfycbXD79nWJw+fS3zeDy6e9Ug8unv9Mm8jxiuexZn444e//zy6bfPsPMWaDnQeduZzKvU8ZIXmdF5HW2yeschDV9L3Nv9WtGlmfLB5fl64Znj8nzm4bnG0Mo3/mG5z7G78qFQked5Or026H52dB0erHhaXV3qaFb3V0WynNourvC8LS6uzLEc2i6u9rwtLq7VtExj0Q7V+0b9OsNHe1W2ivoNxg62pdqVzi7BHr0t9TetlTS9awxd/tPbrXlxrOv3U6bPoFj22y3hvChh2bvE94ETDC+rXapGc/vw+mOztTh9F+p/cr04CpSOL4JEhd5KVyq60o0b8Hjsf732pT35mLelfqRGjNLg7IE4FhfIpUENKHLY2muTNl71ZWub+lMpfoTfVk/0ci/wPd57L9Fiza9mGP1j/VYzXwTfZt935QE63wtzeVrvkX3Zf1ctnR2h/RSoGirEvFUL3x3L6Qct+bK4YM3wvd+p/LLaAjil3EdZZiax0fQOL++qJPlOKCyCAgnG2njSIP7SUfKxNd5KHJnvGt5f3er/517Dn0E3abkna1sr7NdRNVxkDL6Pub7KKvz0Unbzeg+7dY463t72+m728nH1EgjmP6ejT29x/cgDmd5EOuNvGvi8M7yWH+wd0+UszxNrM97dH0Os23ODdkTziod3tcVtiPEoULCbRFxzuDgp5vnG+5VMowOZADIVBGjxMe36gugv03zIZ0nbbiAbXiVP21LpaUpA5Mp+325Ze/tQWMNkqjMbTwkqNVtGHeiYavShhgHG82+k/TAB6y7n6u6y7TFX+TIz44GD3gY7RkCdRhl50PUv3tLb+IA5wTfZx/l/CqQ78JQX+G/IQDb60tIh6HtSuheZr0zmuudzFm9h5S+iigfE9lem7G084H6g022L9CRA9yTHUb+zqcsdZI5r/iIK0u6NUUDz+jiUcSjbEm/78Y76lmdzKHNPJYzfkXau7b1wd6JXTF/9crYiuXNq5oPcwyiCFmbeYLlaB3gXNTDY3xbpwi9bhhwdfok0hZm4vEEvG7voxFvW3rGT9xTut6HUW/Lh1Du1YcuP2QpSrh6JcseTcyW/xmZy+Qt/wEVQfnZYjHJ0XOWZF9ve39bor0xW+e/dXWemWOkvIxOSrNxSilIs5BzmWeVXsZRL0zgnmwQ5VjKEMbJYfDJ2MJzYtMBZgHfjWAfMG6QPqAyog+oYR+wmLbwvCpzXSBraxyHaCOnb5ZEu4js794nL+dn2ewfvDhR7kRXmfvGL4EW2W8PsS07nxgmv50D5PcK92swzup1pbO5P5l1yp9lTcAyhOmvqTX0l0oFY/N8Xfg=
*/