//  (C) Copyright Joel de Guzman 2003.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef VECTOR_INDEXING_SUITE_JDG20036_HPP
# define VECTOR_INDEXING_SUITE_JDG20036_HPP

# include <boost/python/suite/indexing/indexing_suite.hpp>
# include <boost/python/suite/indexing/container_utils.hpp>
# include <boost/python/iterator.hpp>

namespace boost { namespace python {
            
    // Forward declaration
    template <class Container, bool NoProxy, class DerivedPolicies>
    class vector_indexing_suite;
    
    namespace detail
    {
        template <class Container, bool NoProxy>
        class final_vector_derived_policies 
            : public vector_indexing_suite<Container, 
                NoProxy, final_vector_derived_policies<Container, NoProxy> > {};
    }

    // The vector_indexing_suite class is a predefined indexing_suite derived 
    // class for wrapping std::vector (and std::vector like) classes. It provides
    // all the policies required by the indexing_suite (see indexing_suite).
    // Example usage:
    //
    //  class X {...};
    //
    //  ...
    //
    //      class_<std::vector<X> >("XVec")
    //          .def(vector_indexing_suite<std::vector<X> >())
    //      ;
    //
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    //
    template <
        class Container, 
        bool NoProxy = false,
        class DerivedPolicies 
            = detail::final_vector_derived_policies<Container, NoProxy> >
    class vector_indexing_suite 
        : public indexing_suite<Container, DerivedPolicies, NoProxy>
    {
    public:
    
        typedef typename Container::value_type data_type;
        typedef typename Container::value_type key_type;
        typedef typename Container::size_type index_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::difference_type difference_type;
        
        template <class Class>
        static void 
        extension_def(Class& cl)
        {
            cl
                .def("append", &base_append)
                .def("extend", &base_extend)
            ;
        }
        
        static 
        typename mpl::if_<
            is_class<data_type>
          , data_type&
          , data_type
        >::type
        get_item(Container& container, index_type i)
        { 
            return container[i];
        }

        static object 
        get_slice(Container& container, index_type from, index_type to)
        { 
            if (from > to)
                return object(Container());
            return object(Container(container.begin()+from, container.begin()+to));
        }

        static void 
        set_item(Container& container, index_type i, data_type const& v)
        { 
            container[i] = v;
        }

        static void 
        set_slice(Container& container, index_type from, 
            index_type to, data_type const& v)
        { 
            if (from > to) {
                return;
            }
            else {
                container.erase(container.begin()+from, container.begin()+to);
                container.insert(container.begin()+from, v);
            }
        }

        template <class Iter>
        static void 
        set_slice(Container& container, index_type from, 
            index_type to, Iter first, Iter last)
        { 
            if (from > to) {
                container.insert(container.begin()+from, first, last);
            }
            else {
                container.erase(container.begin()+from, container.begin()+to);
                container.insert(container.begin()+from, first, last);
            }
        }

        static void 
        delete_item(Container& container, index_type i)
        { 
            container.erase(container.begin()+i);
        }
        
        static void 
        delete_slice(Container& container, index_type from, index_type to)
        { 
            if (from > to) {
                // A null-op.
                return;
            }
            container.erase(container.begin()+from, container.begin()+to);
        }
        
        static size_t
        size(Container& container)
        {
            return container.size();
        }
        
        static bool
        contains(Container& container, key_type const& key)
        {
            return std::find(container.begin(), container.end(), key)
                != container.end();
        }
        
        static index_type
        get_min_index(Container& /*container*/)
        { 
            return 0;
        }

        static index_type
        get_max_index(Container& container)
        { 
            return container.size();
        }
      
        static bool 
        compare_index(Container& /*container*/, index_type a, index_type b)
        {
            return a < b;
        }
        
        static index_type
        convert_index(Container& container, PyObject* i_)
        { 
            extract<long> i(i_);
            if (i.check())
            {
                long index = i();
                if (index < 0)
                    index += DerivedPolicies::size(container);
                if (index >= long(container.size()) || index < 0)
                {
                    PyErr_SetString(PyExc_IndexError, "Index out of range");
                    throw_error_already_set();
                }
                return index;
            }
            
            PyErr_SetString(PyExc_TypeError, "Invalid index type");
            throw_error_already_set();
            return index_type();
        }
      
        static void 
        append(Container& container, data_type const& v)
        { 
            container.push_back(v);
        }
        
        template <class Iter>
        static void 
        extend(Container& container, Iter first, Iter last)
        { 
            container.insert(container.end(), first, last);
        }
        
    private:
    
        static void
        base_append(Container& container, object v)
        {
            extract<data_type&> elem(v);
            // try if elem is an exact Data
            if (elem.check())
            {
                DerivedPolicies::append(container, elem());
            }
            else
            {
                //  try to convert elem to data_type
                extract<data_type> elem(v);
                if (elem.check())
                {
                    DerivedPolicies::append(container, elem());
                }
                else
                {
                    PyErr_SetString(PyExc_TypeError, 
                        "Attempting to append an invalid type");
                    throw_error_already_set();
                }
            }
        }
        
        static void
        base_extend(Container& container, object v)
        {
            std::vector<data_type> temp;
            container_utils::extend_container(temp, v);
            DerivedPolicies::extend(container, temp.begin(), temp.end());
        }
    };
       
}} // namespace boost::python 

#endif // VECTOR_INDEXING_SUITE_JDG20036_HPP

/* vector_indexing_suite.hpp
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
*/