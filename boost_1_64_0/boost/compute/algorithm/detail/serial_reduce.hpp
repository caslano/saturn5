//---------------------------------------------------------------------------//
// Copyright (c) 2013 Kyle Lutz <kyle.r.lutz@gmail.com>
//
// Distributed under the Boost Software License, Version 1.0
// See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt
//
// See http://boostorg.github.com/compute for more information.
//---------------------------------------------------------------------------//

#ifndef BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP
#define BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP

#include <boost/compute/command_queue.hpp>
#include <boost/compute/detail/meta_kernel.hpp>
#include <boost/compute/detail/iterator_range_size.hpp>
#include <boost/compute/type_traits/result_of.hpp>

namespace boost {
namespace compute {
namespace detail {

// Space complexity: O(1)
template<class InputIterator, class OutputIterator, class BinaryFunction>
inline void serial_reduce(InputIterator first,
                          InputIterator last,
                          OutputIterator result,
                          BinaryFunction function,
                          command_queue &queue)
{
    typedef typename
        std::iterator_traits<InputIterator>::value_type T;
    typedef typename
        ::boost::compute::result_of<BinaryFunction(T, T)>::type result_type;

    const context &context = queue.get_context();
    size_t count = detail::iterator_range_size(first, last);
    if(count == 0){
        return;
    }

    meta_kernel k("serial_reduce");
    size_t count_arg = k.add_arg<cl_uint>("count");

    k <<
        k.decl<result_type>("result") << " = " << first[0] << ";\n" <<
        "for(uint i = 1; i < count; i++)\n" <<
        "    result = " << function(k.var<T>("result"),
                                    first[k.var<uint_>("i")]) << ";\n" <<
        result[0] << " = result;\n";

    kernel kernel = k.compile(context);

    kernel.set_arg(count_arg, static_cast<uint_>(count));

    queue.enqueue_task(kernel);
}

} // end detail namespace
} // end compute namespace
} // end boost namespace

#endif // BOOST_COMPUTE_ALGORITHM_DETAIL_SERIAL_REDUCE_HPP

/* serial_reduce.hpp
hugBZ9wPFaeL5OfNeO3e4L1GD8D7X8YbG+D4FmeoJUUE89CJH96FX20L/m5cF3Hg6uD3dee3g1+C+0ZuNX6X8MvucPbf8q75S94THcznKGeejmwXfK+BXe72fHHsCv6vihePXvZ3A5yFOBCfGetsrrHizSniv3wyNRrOcf2ZpxjnF531CoenFMINwxKCzwRntVWxp2Nig/G4zFnLzzhD7HBxBY5P6e1stczgvovugzOHBp85f8Dz0fD2cexoHPwVFXyuvFB+PCgheO7bYoP3XeNsukH4e7b3PMb7fwKn0oHiOsFld8gD+XjVlmAcRw4Nrt8ov68ohP+vk3cq5Y3X6USnwdv8frp8Pv1T/ok39D8Crr4t+LtieCpZ3knaBHftC96nLZ0eEiu+DQrmtah3O7jDdX7hD8eLW/xn1rP4/wK4mp/VyUdli8TPVmeuipcN70QF9+vrzDj20wwXFi7EJ46Tl3tGBZ/v8tPezoo73Jmf99Ir6/GURXjFUPirB/1uAT30ameZPuD6A+i2/xWPf6JDVQfP09re/fvgBXhi8+HBfdIW8Lvu4tan/Go//7090jgG18vFsyLZeXHH4PpVr+Apn8LlY51FmgXPwHkNR/j+On4yzhnld4sHTxiPEXBjd3lAPCoay/7f9j5T4YfO0fgw/4EviuW/ujsjgnkvx9M3ee9kvOl5Z9iuktf3yIf8Lu9C/D9afBK/ap9whuaO4DlWlcHfx9Mjb8O722LxGWc3mo/kPHj6Jv4eD68e7MzY+XgRnj+T38XQN2sfk3fdL6VavtjlDEr6y9q+3uNpZxdntqO7BtdbiRfkvCGu4I2D1AcyF9DFUugn5wb3Lb8PPh8A54kzpavw/xT2eCX8updO9DfdpDK433q6z+yeroPnN30c3Kc2F26eKu9cC88nmW84vIVutfJL410WfOZewO6my3+fOyvTfbL+LQ98CS+cDp+vg0cb6UntgnFbcpI4iXdmXMyfhjhbkf49kl/kw3VTU/z/AF3LeG8/nB6RzZ5neP4SfOaFqOC5+oiX78oHW2OD52enBXPonnF43BXi90nsfhydsz2/uMnzFKvT3MyvtsUG87xE/BgJT8h3qQ/Ko+fEB+NzRfC9uMS44D0OdtbpHGeFVstTN9M114szhwV/lz1TPv0K7hqp/nFD8P9Zt6hLZalHbYAjYoLf58MH1dNi8T73mdvRffFw752XiUfe5WzRicaFzlAdBW8fHfx83Ft4+ST4aAt7XBpnnvBN8aptYPD/7FHB7/MG4bPqEzNP8vdJ+Huys0FfDp6/fEd8cP/fgs/I7/lPe2dhj2aH4nlRq3xqPFeso9P3FcfnBfffuozuN9iZn2vwDPi7ogWf+pBdjOkIL3gO81QerQ6Sxl6vCe6XZdzq+NmUyfSTGPhkdPD3SQMTAv/BLzKq4c/OcFfXhOA6s+Go9s4a34XvXCjOlsLLQ5yJf5s8+zXeMDgB3w++32uA5xnijOkxcEQPceik4O8af3b2/EXOBj6Tn66Dd44Ofp44ge66VjxdLM+cEB9cTzxMXiRfFvIzeSP9D9/b7jpH4SV0xTb6SRt8O3uDvDDP+MfKj3vEgdPh9MPZ8X/gsB+Cvy8x/snhmc7REeqqwc9bmjzvEXjJRD9fTTfrLf/dat6+Y/dp8Mfz/GSiOBCvTsju897G80bQ8/ub1w7e/21nnn+tDpnpLN5eEepJeP+j8qWztdO6+L/4sPVh+TqCjnwI3JCAP7/nLP7n8bQP8bsGdWp+3ApvJy6Fj+6ODb53eFif83dP4rMt7AauLW8Tf+k8jenGbU3wvf7jg+tk5sErP4pbxqOSzhd5GH0yAZ6eHR38Xa78mk53uUs=
*/