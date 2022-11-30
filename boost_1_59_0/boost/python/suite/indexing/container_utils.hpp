
//  (C) Copyright Joel de Guzman 2003.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef PY_CONTAINER_UTILS_JDG20038_HPP
# define PY_CONTAINER_UTILS_JDG20038_HPP

# include <utility>
# include <boost/foreach.hpp>
# include <boost/python/object.hpp>
# include <boost/python/handle.hpp>
# include <boost/python/extract.hpp>
# include <boost/python/stl_iterator.hpp>

namespace boost { namespace python { namespace container_utils {
        
    template <typename Container>
    void
    extend_container(Container& container, object l)
    {
        typedef typename Container::value_type data_type;
        
        //  l must be iterable
        BOOST_FOREACH(object elem,
            std::make_pair(
              boost::python::stl_input_iterator<object>(l),
              boost::python::stl_input_iterator<object>()
              ))
        {
            extract<data_type const&> x(elem);
            //  try if elem is an exact data_type type
            if (x.check())
            {
                container.push_back(x());
            }
            else
            {
                //  try to convert elem to data_type type
                extract<data_type> x(elem);
                if (x.check())
                {
                    container.push_back(x());
                }
                else
                {
                    PyErr_SetString(PyExc_TypeError, "Incompatible Data Type");
                    throw_error_already_set();
                }
            }
        }          
    }

}}} // namespace boost::python::container_utils

#endif

/* container_utils.hpp
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
*/