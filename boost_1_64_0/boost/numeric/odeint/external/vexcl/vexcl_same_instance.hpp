/*
 [auto_generated]
 boost/numeric/odeint/external/vexcl/vexcl_same_instance.hpp

 [begin_description]
 Check if two VexCL containers are the same instance.
 [end_description]

 Copyright 2009-2011 Karsten Ahnert
 Copyright 2009-2011 Mario Mulansky

 Distributed under the Boost Software License, Version 1.0.
 (See accompanying file LICENSE_1_0.txt or
 copy at http://www.boost.org/LICENSE_1_0.txt)
 */


#ifndef BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED
#define BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED

#include <vexcl/vector.hpp>
#include <vexcl/multivector.hpp>

#include <boost/numeric/odeint/util/same_instance.hpp>

namespace boost {
namespace numeric {
namespace odeint {

template <typename T>
struct same_instance_impl< vex::vector<T> , vex::vector<T> >
{
    static bool same_instance( const vex::vector<T> &x1 , const vex::vector<T> &x2 )
    {
        return
            static_cast<const vex::vector<T>*>(&x1) ==
            static_cast<const vex::vector<T>*>(&x2);
    }
};

template <typename T, size_t N>
struct same_instance_impl< vex::multivector<T, N> , vex::multivector<T, N> >
{
    static bool same_instance( const vex::multivector<T, N> &x1 , const vex::multivector<T, N> &x2 )
    {
        return
            static_cast<const vex::multivector<T, N>*>(&x1) ==
            static_cast<const vex::multivector<T, N>*>(&x2);
    }
};

} // namespace odeint
} // namespace numeric
} // namespace boost



#endif // BOOST_NUMERIC_ODEINT_EXTERNAL_VEXCL_VEXCL_SAME_INSTANCE_HPP_INCLUDED

/* vexcl_same_instance.hpp
OjrWD3cuCzeB3VWn0UzBZdu5geys67ZdegcF1nnEJSM25Htr4g37wO9rhD9UCwXkaXsOWYKE50Qh5rs81iu2eMeI+LqtbIUO45Wap06Mxk3d7W9ZtuljIXeZfBBstrP0ZwiIz95H+jc4fViZus67BypdsOtfWx/icWvsggn4Legjmk3DT8pnN90L7416DfskcHi3twzBWrwH0YTPo0LzT5FAv39Oeocwu8GGRjq0oqwM2XLJSVklQXj/BxpmJXDOTEtSzJljW6qx2qIskTKqEJKgByjWks865ufvQFqu9TejTsml0MTEXX0K7JEzGlxg4dBr9TDMV6+8gnyWynaqrb3PpCzSaCRZs8HytEDEGjjaSNeDwTWuPg4EzOXZ7+nlQjMRDdp6O5zS2DqxIF+h2JVaDAXL1oU6ngb2dKsh4Zs5JaVqAAVPUNoGWKf8xsokmbY4j3VLcCPqxx9LK1ch23gHQfIc/RmqSyibCvvKUI3IVruqjqroVqBPbg39T8htPhL89Hnc0V5ryPX6zdt6qelSejSZiDmYgSUcz/uccYfWkhYn9F8rLOMcvg==
*/