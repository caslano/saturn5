//  (C) Copyright Joel de Guzman 2003.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef INDEXING_SUITE_JDG20036_HPP
# define INDEXING_SUITE_JDG20036_HPP

# include <boost/python/class.hpp>
# include <boost/python/def_visitor.hpp>
# include <boost/python/register_ptr_to_python.hpp>
# include <boost/python/suite/indexing/detail/indexing_suite_detail.hpp>
# include <boost/python/return_internal_reference.hpp>
# include <boost/python/iterator.hpp>
# include <boost/mpl/or.hpp>
# include <boost/mpl/not.hpp>
# include <boost/python/detail/type_traits.hpp>

namespace boost { namespace python {

    // indexing_suite class. This class is the facade class for
    // the management of C++ containers intended to be integrated
    // to Python. The objective is make a C++ container look and
    // feel and behave exactly as we'd expect a Python container.
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    //
    // Derived classes provide the hooks needed by the indexing_suite
    // to do its job:
    //
    //      static data_type&
    //      get_item(Container& container, index_type i);
    //
    //      static object
    //      get_slice(Container& container, index_type from, index_type to);
    //
    //      static void
    //      set_item(Container& container, index_type i, data_type const& v);
    //
    //      static void
    //      set_slice(
    //         Container& container, index_type from,
    //         index_type to, data_type const& v
    //      );
    //
    //      template <class Iter>
    //      static void
    //      set_slice(Container& container, index_type from,
    //          index_type to, Iter first, Iter last
    //      );
    //
    //      static void
    //      delete_item(Container& container, index_type i);
    //
    //      static void
    //      delete_slice(Container& container, index_type from, index_type to);
    //
    //      static size_t
    //      size(Container& container);
    //
    //      template <class T>
    //      static bool
    //      contains(Container& container, T const& val);
    //
    //      static index_type
    //      convert_index(Container& container, PyObject* i);
    //
    //      static index_type
    //      adjust_index(index_type current, index_type from,
    //          index_type to, size_type len
    //      );
    //
    // Most of these policies are self explanatory. convert_index and
    // adjust_index, however, deserves some explanation.
    //
    // convert_index converts an Python index into a C++ index that the
    // container can handle. For instance, negative indexes in Python, by
    // convention, indexes from the right (e.g. C[-1] indexes the rightmost
    // element in C). convert_index should handle the necessary conversion
    // for the C++ container (e.g. convert -1 to C.size()-1). convert_index
    // should also be able to convert the type of the index (A dynamic Python
    // type) to the actual type that the C++ container expects.
    //
    // When a container expands or contracts, held indexes to its elements
    // must be adjusted to follow the movement of data. For instance, if
    // we erase 3 elements, starting from index 0 from a 5 element vector,
    // what used to be at index 4 will now be at index 1:
    //
    //      [a][b][c][d][e] ---> [d][e]
    //                   ^           ^
    //                   4           1
    //
    // adjust_index takes care of the adjustment. Given a current index,
    // the function should return the adjusted index when data in the
    // container at index from..to is replaced by *len* elements.
    //

    template <
          class Container
        , class DerivedPolicies
        , bool NoProxy = false
        , bool NoSlice = false
        , class Data = typename Container::value_type
        , class Index = typename Container::size_type
        , class Key = typename Container::value_type
    >
    class indexing_suite
        : public def_visitor<
            indexing_suite<
              Container
            , DerivedPolicies
            , NoProxy
            , NoSlice
            , Data
            , Index
            , Key
        > >
    {
    private:

        typedef mpl::or_<
            mpl::bool_<NoProxy>
          , mpl::not_<is_class<Data> >
          , typename mpl::or_<
                detail::is_same<Data, std::string>
              , detail::is_same<Data, std::complex<float> >
              , detail::is_same<Data, std::complex<double> >
              , detail::is_same<Data, std::complex<long double> > >::type>
        no_proxy;

        typedef detail::container_element<Container, Index, DerivedPolicies>
            container_element_t;

        typedef return_internal_reference<> return_policy;

        typedef typename mpl::if_<
            no_proxy
          , iterator<Container>
          , iterator<Container, return_policy> >::type
        def_iterator;

        typedef typename mpl::if_<
            no_proxy
          , detail::no_proxy_helper<
                Container
              , DerivedPolicies
              , container_element_t
              , Index>
          , detail::proxy_helper<
                Container
              , DerivedPolicies
              , container_element_t
              , Index> >::type
        proxy_handler;

        typedef typename mpl::if_<
            mpl::bool_<NoSlice>
          , detail::no_slice_helper<
                Container
              , DerivedPolicies
              , proxy_handler
              , Data
              , Index>
          , detail::slice_helper<
                Container
              , DerivedPolicies
              , proxy_handler
              , Data
              , Index> >::type
        slice_handler;

    public:

        template <class Class>
        void visit(Class& cl) const
        {
            // Hook into the class_ generic visitation .def function
            proxy_handler::register_container_element();

            cl
                .def("__len__", base_size)
                .def("__setitem__", &base_set_item)
                .def("__delitem__", &base_delete_item)
                .def("__getitem__", &base_get_item)
                .def("__contains__", &base_contains)
                .def("__iter__", def_iterator())
            ;

            DerivedPolicies::extension_def(cl);
        }

        template <class Class>
        static void
        extension_def(Class& cl)
        {
            // default.
            // no more extensions
        }

    private:

        static object
        base_get_item(back_reference<Container&> container, PyObject* i)
        {
            if (PySlice_Check(i))
                return slice_handler::base_get_slice(
                    container.get(), static_cast<PySliceObject*>(static_cast<void*>(i)));

            return proxy_handler::base_get_item_(container, i);
        }

        static void
        base_set_item(Container& container, PyObject* i, PyObject* v)
        {
            if (PySlice_Check(i))
            {
                 slice_handler::base_set_slice(container,
                     static_cast<PySliceObject*>(static_cast<void*>(i)), v);
            }
            else
            {
                extract<Data&> elem(v);
                // try if elem is an exact Data
                if (elem.check())
                {
                    DerivedPolicies::
                        set_item(container,
                            DerivedPolicies::
                                convert_index(container, i), elem());
                }
                else
                {
                    //  try to convert elem to Data
                    extract<Data> elem(v);
                    if (elem.check())
                    {
                        DerivedPolicies::
                            set_item(container,
                                DerivedPolicies::
                                    convert_index(container, i), elem());
                    }
                    else
                    {
                        PyErr_SetString(PyExc_TypeError, "Invalid assignment");
                        throw_error_already_set();
                    }
                }
            }
        }

        static void
        base_delete_item(Container& container, PyObject* i)
        {
            if (PySlice_Check(i))
            {
                slice_handler::base_delete_slice(
                    container, static_cast<PySliceObject*>(static_cast<void*>(i)));
                return;
            }

            Index index = DerivedPolicies::convert_index(container, i);
            proxy_handler::base_erase_index(container, index, mpl::bool_<NoSlice>());
            DerivedPolicies::delete_item(container, index);
        }

        static size_t
        base_size(Container& container)
        {
            return DerivedPolicies::size(container);
        }

        static bool
        base_contains(Container& container, PyObject* key)
        {
            extract<Key const&> x(key);
            //  try if key is an exact Key type
            if (x.check())
            {
                return DerivedPolicies::contains(container, x());
            }
            else
            {
                //  try to convert key to Key type
                extract<Key> x(key);
                if (x.check())
                    return DerivedPolicies::contains(container, x());
                else
                    return false;
            }
        }
    };

}} // namespace boost::python

#endif // INDEXING_SUITE_JDG20036_HPP

/* indexing_suite.hpp
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
*/