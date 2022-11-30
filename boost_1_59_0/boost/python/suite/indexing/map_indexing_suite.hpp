//  (C) Copyright Joel de Guzman 2003.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef MAP_INDEXING_SUITE_JDG20038_HPP
# define MAP_INDEXING_SUITE_JDG20038_HPP

# include <boost/python/suite/indexing/indexing_suite.hpp>
# include <boost/python/iterator.hpp>
# include <boost/python/call_method.hpp>
# include <boost/python/tuple.hpp>

namespace boost { namespace python {

    // Forward declaration
    template <class Container, bool NoProxy, class DerivedPolicies>
    class map_indexing_suite;

    namespace detail
    {
        template <class Container, bool NoProxy>
        class final_map_derived_policies
            : public map_indexing_suite<Container,
                NoProxy, final_map_derived_policies<Container, NoProxy> > {};
    }

    // The map_indexing_suite class is a predefined indexing_suite derived
    // class for wrapping std::map (and std::map like) classes. It provides
    // all the policies required by the indexing_suite (see indexing_suite).
    // Example usage:
    //
    //  class X {...};
    //
    //  ...
    //
    //      class_<std::map<std::string, X> >("XMap")
    //          .def(map_indexing_suite<std::map<std::string, X> >())
    //      ;
    //
    // By default indexed elements are returned by proxy. This can be
    // disabled by supplying *true* in the NoProxy template parameter.
    //
    template <
        class Container,
        bool NoProxy = false,
        class DerivedPolicies
            = detail::final_map_derived_policies<Container, NoProxy> >
    class map_indexing_suite
        : public indexing_suite<
            Container
          , DerivedPolicies
          , NoProxy
          , true
          , typename Container::value_type::second_type
          , typename Container::key_type
          , typename Container::key_type
        >
    {
    public:

        typedef typename Container::value_type value_type;
        typedef typename Container::value_type::second_type data_type;
        typedef typename Container::key_type key_type;
        typedef typename Container::key_type index_type;
        typedef typename Container::size_type size_type;
        typedef typename Container::difference_type difference_type;

        template <class Class>
        static void
        extension_def(Class& cl)
        {
            //  Wrap the map's element (value_type)
            std::string elem_name = "map_indexing_suite_";
            object class_name(cl.attr("__name__"));
            extract<std::string> class_name_extractor(class_name);
            elem_name += class_name_extractor();
            elem_name += "_entry";

            typedef typename mpl::if_<
                mpl::and_<is_class<data_type>, mpl::bool_<!NoProxy> >
              , return_internal_reference<>
              , default_call_policies
            >::type get_data_return_policy;

            class_<value_type>(elem_name.c_str())
                .def("__repr__", &DerivedPolicies::print_elem)
                .def("data", &DerivedPolicies::get_data, get_data_return_policy())
                .def("key", &DerivedPolicies::get_key)
            ;
        }

        static object
        print_elem(typename Container::value_type const& e)
        {
            return "(%s, %s)" % python::make_tuple(e.first, e.second);
        }

        static
        typename mpl::if_<
            mpl::and_<is_class<data_type>, mpl::bool_<!NoProxy> >
          , data_type&
          , data_type
        >::type
        get_data(typename Container::value_type& e)
        {
            return e.second;
        }

        static typename Container::key_type
        get_key(typename Container::value_type& e)
        {
            return e.first;
        }

        static data_type&
        get_item(Container& container, index_type i_)
        {
            typename Container::iterator i = container.find(i_);
            if (i == container.end())
            {
                PyErr_SetString(PyExc_KeyError, "Invalid key");
                throw_error_already_set();
            }
            return i->second;
        }

        static void
        set_item(Container& container, index_type i, data_type const& v)
        {
            container[i] = v;
        }

        static void
        delete_item(Container& container, index_type i)
        {
            container.erase(i);
        }

        static size_t
        size(Container& container)
        {
            return container.size();
        }

        static bool
        contains(Container& container, key_type const& key)
        {
            return container.find(key) != container.end();
        }

        static bool
        compare_index(Container& container, index_type a, index_type b)
        {
            return container.key_comp()(a, b);
        }

        static index_type
        convert_index(Container& /*container*/, PyObject* i_)
        {
            extract<key_type const&> i(i_);
            if (i.check())
            {
                return i();
            }
            else
            {
                extract<key_type> i(i_);
                if (i.check())
                    return i();
            }

            PyErr_SetString(PyExc_TypeError, "Invalid index type");
            throw_error_already_set();
            return index_type();
        }
    };

}} // namespace boost::python

#endif // MAP_INDEXING_SUITE_JDG20038_HPP

/* map_indexing_suite.hpp
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
*/