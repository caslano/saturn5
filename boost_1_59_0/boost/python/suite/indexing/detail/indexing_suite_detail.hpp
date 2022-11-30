//  (C) Copyright Joel de Guzman 2003.
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

#ifndef INDEXING_SUITE_DETAIL_JDG20036_HPP
# define INDEXING_SUITE_DETAIL_JDG20036_HPP

# include <boost/python/extract.hpp>
# include <boost/scoped_ptr.hpp>
# include <boost/get_pointer.hpp>
# include <boost/detail/binary_search.hpp>
# include <boost/numeric/conversion/cast.hpp>
# include <boost/python/detail/type_traits.hpp>
# include <vector>
# include <map>
#include <iostream>

namespace boost { namespace python { namespace detail {

#if defined(NDEBUG)
#define BOOST_PYTHON_INDEXING_CHECK_INVARIANT
#else
#define BOOST_PYTHON_INDEXING_CHECK_INVARIANT check_invariant()
#endif
    
    template <class Proxy>
    struct compare_proxy_index
    {
        //  This functor compares a proxy and an index.
        //  This is used by proxy_group::first_proxy to
        //  get first proxy with index i.
                
        template <class Index>
        bool operator()(PyObject* prox, Index i) const
        {
            typedef typename Proxy::policies_type policies_type;
            Proxy& proxy = extract<Proxy&>(prox)();
            return policies_type::
                compare_index(proxy.get_container(), proxy.get_index(), i);
        }
    };        
 
    //  The proxy_group class holds a vector of container element
    //  proxies. First, what is a container element proxy? A container 
    //  element proxy acts like a smart pointer holding a reference to 
    //  a container and an index (see container_element, for details). 
    //
    //  The proxies are held in a vector always sorted by its index.
    //  Various functions manage the addition, removal and searching
    //  of proxies from the vector.
    //
    template <class Proxy>
    class proxy_group
    {
    public:
    
        typedef typename std::vector<PyObject*>::const_iterator const_iterator;
        typedef typename std::vector<PyObject*>::iterator iterator;
        typedef typename Proxy::index_type index_type;
        typedef typename Proxy::policies_type policies_type;
        
        iterator
        first_proxy(index_type i)
        {
            // Return the first proxy with index <= i
            return boost::detail::lower_bound(
                proxies.begin(), proxies.end(), 
                i, compare_proxy_index<Proxy>());
        }

        void
        remove(Proxy& proxy)
        {
            // Remove a proxy
            for (iterator iter = first_proxy(proxy.get_index());
                iter != proxies.end(); ++iter)
            {
                if (&extract<Proxy&>(*iter)() == &proxy)
                {
                    proxies.erase(iter);
                    break;
                }
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        void
        add(PyObject* prox)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Add a proxy
            proxies.insert(
                first_proxy(extract<Proxy&>(prox)().get_index()), prox);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        void
        erase(index_type i, mpl::false_)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase the proxy with index i 
            replace(i, i+1, 0);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        void
        erase(index_type i, mpl::true_)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase the proxy with index i 
            
            iterator iter = first_proxy(i);
            extract<Proxy&> p(*iter);
            
            if (iter != proxies.end() && p().get_index() == i)
            {
                extract<Proxy&> p(*iter);
                p().detach();
                proxies.erase(iter);
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        void
        erase(index_type from, index_type to)
        {
            // note: this cannot be called when container is not sliceable
            
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase all proxies with indexes from..to 
            replace(from, to, 0);
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }

        void
        replace(
            index_type from, 
            index_type to, 
            typename std::vector<PyObject*>::size_type len)
        {
            // note: this cannot be called when container is not sliceable

            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Erase all proxies with indexes from..to.
            // Adjust the displaced indexes such that the
            // final effect is that we have inserted *len*
            // number of proxies in the vacated region. This
            // procedure involves adjusting the indexes of 
            // the proxies.
            
            iterator left = first_proxy(from);
            iterator right = proxies.end(); // we'll adjust this later
            
            for (iterator iter = left; iter != right; ++iter)
            {
                if (extract<Proxy&>(*iter)().get_index() > to)
                {
                    right = iter; // adjust right
                    break;
                }
                extract<Proxy&> p(*iter);
                p().detach();
            }
            
            typename std::vector<PyObject*>::size_type 
                offset = left-proxies.begin();
            proxies.erase(left, right);
            right = proxies.begin()+offset;

            while (right != proxies.end())
            {
                typedef typename Proxy::container_type::difference_type difference_type;
                extract<Proxy&> p(*right);
                p().set_index(
                    extract<Proxy&>(*right)().get_index() 
                    - (difference_type(to) - from - len)
                );
                    
                ++right;
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
        }
        
        PyObject*
        find(index_type i)
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // Find the proxy with *exact* index i.
            // Return 0 (null) if no proxy with the 
            // given index is found.
            iterator iter = first_proxy(i);
            if (iter != proxies.end()
                && extract<Proxy&>(*iter)().get_index() == i)
            {
                BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
                return *iter;
            }
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            return 0;
        }

        typename std::vector<PyObject*>::size_type 
        size() const
        {
            BOOST_PYTHON_INDEXING_CHECK_INVARIANT;
            // How many proxies are there so far?
            return proxies.size();
        } 

    private:

#if !defined(NDEBUG)
        void
        check_invariant() const
        {
            for (const_iterator i = proxies.begin(); i != proxies.end(); ++i)
            {
                if ((*i)->ob_refcnt <= 0)
                {
                    PyErr_SetString(PyExc_RuntimeError, 
                        "Invariant: Proxy vector in an inconsistent state");
                    throw_error_already_set();
                }
                
                if (i+1 != proxies.end())
                {
                    if (extract<Proxy&>(*(i+1))().get_index() ==
                        extract<Proxy&>(*(i))().get_index())
                    {
                        PyErr_SetString(PyExc_RuntimeError, 
                            "Invariant: Proxy vector in an inconsistent state (duplicate proxy)");
                        throw_error_already_set();
                    }
                }
            }
        }
#endif
        
        std::vector<PyObject*> proxies;
    };
            
    // proxy_links holds a map of Container pointers (keys)
    // with proxy_group(s) (data). Various functions manage 
    // the addition, removal and searching of proxies from 
    // the map.
    //
    template <class Proxy, class Container>
    class proxy_links
    {
    public:
    
        typedef std::map<Container*, proxy_group<Proxy> > links_t;
        typedef typename Proxy::index_type index_type;

        void
        remove(Proxy& proxy)
        {
            // Remove a proxy.
            typename links_t::iterator r = links.find(&proxy.get_container());
            if (r != links.end())
            {
                r->second.remove(proxy);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }
        
        void
        add(PyObject* prox, Container& container)
        {
            // Add a proxy
            links[&container].add(prox);
        }
        
        template <class NoSlice>
        void erase(Container& container, index_type i, NoSlice no_slice)
        {
            // Erase the proxy with index i 
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.erase(i, no_slice);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }
        
        void
        erase(Container& container, index_type from, index_type to)
        {
            // Erase all proxies with indexes from..to 
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.erase(from, to);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }

        void
        replace(
            Container& container, 
            index_type from, index_type to, index_type len)
        {
            // Erase all proxies with indexes from..to.
            // Adjust the displaced indexes such that the
            // final effect is that we have inserted *len*
            // number of proxies in the vacated region. This
            // procedure involves adjusting the indexes of 
            // the proxies.

            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
            {
                r->second.replace(from, to, len);
                if (r->second.size() == 0)
                    links.erase(r);
            }
        }
        
        PyObject*
        find(Container& container, index_type i)
        {
            // Find the proxy with *exact* index i.
            // Return 0 (null) if no proxy with the given 
            // index is found.
            typename links_t::iterator r = links.find(&container);
            if (r != links.end())
                return r->second.find(i);
            return 0;
        }

    private:
    
        links_t links;
    };
    
    // container_element is our container proxy class.
    // This class acts like a smart pointer to a container
    // element. The class holds an index and a reference to
    // a container. Dereferencing the smart pointer will
    // retrieve the nth (index) element from the container.
    //
    // A container_element can also be detached from the
    // container. In such a detached state, the container_element
    // holds a copy of the nth (index) element, which it 
    // returns when dereferenced.
    //
    template <class Container, class Index, class Policies>
    class container_element
    {
    public:
    
        typedef Index index_type;
        typedef Container container_type;
        typedef typename Policies::data_type element_type;
        typedef Policies policies_type;
        typedef container_element<Container, Index, Policies> self_t;
        typedef proxy_group<self_t> links_type;
        
        container_element(object container, Index index)
            : ptr()
            , container(container)
            , index(index)
        {
        }
            
        container_element(container_element const& ce)
          : ptr(ce.ptr.get() == 0 ? 0 : new element_type(*ce.ptr.get()))
          , container(ce.container)
          , index(ce.index)
        {
        }

        ~container_element()
        {
            if (!is_detached())
                get_links().remove(*this);
        }
                      
        element_type& operator*() const
        {
            if (is_detached())
                return *get_pointer(ptr);
            return Policies::get_item(get_container(), index);
        }
        
        element_type* get() const
        {
            if (is_detached())
                return get_pointer(ptr);
            return &Policies::get_item(get_container(), index);
        }
        
        void
        detach()
        {
            if (!is_detached())
            {
                ptr.reset(
                    new element_type(
                        Policies::get_item(get_container(), index)));
                container = object(); // free container. reset it to None
            }
        }
        
        bool
        is_detached() const
        {
            return get_pointer(ptr) != 0;
        }

        Container& 
        get_container() const
        {
            return extract<Container&>(container)();
        }
        
        Index 
        get_index() const
        {
            return index;
        }

        void 
        set_index(Index i)
        {
            index = i;
        }
 
        static proxy_links<self_t, Container>&
        get_links()
        {
            // All container_element(s) maintain links to
            // its container in a global map (see proxy_links).
            // This global "links" map is a singleton.
            
            static proxy_links<self_t, Container> links;
            return links; // singleton
        }

    private:
            
        container_element& operator=(container_element const& ce);

        scoped_ptr<element_type> ptr;
        object container;
        Index index;
    };

    template <
          class Container
        , class DerivedPolicies
        , class ContainerElement
        , class Index
    >
    struct no_proxy_helper
    {                
        static void
        register_container_element()
        { 
        }

        template <class DataType> 
        static object
        base_get_item_helper(DataType const& p, detail::true_)
        { 
            return object(ptr(p));
        }

        template <class DataType> 
        static object
        base_get_item_helper(DataType const& x, detail::false_)
        { 
            return object(x);
        }

        static object
        base_get_item_(back_reference<Container&> const& container, PyObject* i)
        { 
            return base_get_item_helper(
                DerivedPolicies::get_item(
                    container.get(), DerivedPolicies::
                        convert_index(container.get(), i))
              , is_pointer<BOOST_DEDUCED_TYPENAME Container::value_type>()
            );
        }

        static void
        base_replace_indexes(
            Container& /*container*/, Index /*from*/, 
            Index /*to*/, Index /*n*/)
        {
        }

        template <class NoSlice>
        static void
        base_erase_index(
            Container& /*container*/, Index /*i*/, NoSlice /*no_slice*/)
        {
        }
        
        static void
        base_erase_indexes(Container& /*container*/, Index /*from*/, Index /*to*/)
        {
        }
    };            
          
    template <
          class Container
        , class DerivedPolicies
        , class ContainerElement
        , class Index
    >
    struct proxy_helper
    {        
        static void
        register_container_element()
        { 
            register_ptr_to_python<ContainerElement>();
        }

        static object
        base_get_item_(back_reference<Container&> const& container, PyObject* i)
        { 
            // Proxy
            Index idx = DerivedPolicies::convert_index(container.get(), i);

            if (PyObject* shared = 
                ContainerElement::get_links().find(container.get(), idx))
            {
                handle<> h(python::borrowed(shared));
                return object(h);
            }
            else
            {
                object prox(ContainerElement(container.source(), idx));
                ContainerElement::
                    get_links().add(prox.ptr(), container.get());
                return prox;
            }
        }

        static void
        base_replace_indexes(
            Container& container, Index from, 
            Index to, Index n)
        {
            ContainerElement::get_links().replace(container, from, to, n);
        }
        
        template <class NoSlice>
        static void
        base_erase_index(
            Container& container, Index i, NoSlice no_slice)
        {
            ContainerElement::get_links().erase(container, i, no_slice);
        }
        
        static void
        base_erase_indexes(
            Container& container, Index from, Index to)
        {
            ContainerElement::get_links().erase(container, from, to);
        }
    };        
    
    template <
          class Container
        , class DerivedPolicies
        , class ProxyHandler
        , class Data
        , class Index
    >
    struct slice_helper
    {        
        static object 
        base_get_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            return DerivedPolicies::get_slice(container, from, to);
        }

        static void
        base_get_slice_data(
            Container& container, PySliceObject* slice, Index& from_, Index& to_)
        {
            if (Py_None != slice->step) {
                PyErr_SetString( PyExc_IndexError, "slice step size not supported.");
                throw_error_already_set();
            }

            Index min_index = DerivedPolicies::get_min_index(container);
            Index max_index = DerivedPolicies::get_max_index(container);
            
            if (Py_None == slice->start) {
                from_ = min_index;
            }
            else {
                long from = extract<long>( slice->start);
                if (from < 0) // Negative slice index
                    from += max_index;
                if (from < 0) // Clip lower bounds to zero
                    from = 0;
                from_ = boost::numeric_cast<Index>(from);
                if (from_ > max_index) // Clip upper bounds to max_index.
                    from_ = max_index;
            }

            if (Py_None == slice->stop) {
                to_ = max_index;
            }
            else {
                long to = extract<long>( slice->stop);
                if (to < 0)
                    to += max_index;
                if (to < 0)
                    to = 0;
                to_ = boost::numeric_cast<Index>(to);
                if (to_ > max_index)
                    to_ = max_index;
            }
        }        
   
        static void 
        base_set_slice(Container& container, PySliceObject* slice, PyObject* v)
        {
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            
            extract<Data&> elem(v);
            // try if elem is an exact Data
            if (elem.check())
            {
                ProxyHandler::base_replace_indexes(container, from, to, 1);
                DerivedPolicies::set_slice(container, from, to, elem());
            }
            else
            {
                //  try to convert elem to Data
                extract<Data> elem(v);
                if (elem.check())
                {
                    ProxyHandler::base_replace_indexes(container, from, to, 1);
                    DerivedPolicies::set_slice(container, from, to, elem());
                }
                else
                {
                    //  Otherwise, it must be a list or some container
                    handle<> l_(python::borrowed(v));
                    object l(l_);
    
                    std::vector<Data> temp;
                    for (int i = 0; i < l.attr("__len__")(); i++)
                    {
                        object elem(l[i]);
                        extract<Data const&> x(elem);
                        //  try if elem is an exact Data type
                        if (x.check())
                        {
                            temp.push_back(x());
                        }
                        else
                        {
                            //  try to convert elem to Data type
                            extract<Data> x(elem);
                            if (x.check())
                            {
                                temp.push_back(x());
                            }
                            else
                            {
                                PyErr_SetString(PyExc_TypeError, 
                                    "Invalid sequence element");
                                throw_error_already_set();
                            }
                        }
                    }          
                  
                    ProxyHandler::base_replace_indexes(container, from, to, 
                        temp.end()-temp.begin());
                    DerivedPolicies::set_slice(container, from, to, 
                        temp.begin(), temp.end());
                }
            }            
        }
        
        static void 
        base_delete_slice(Container& container, PySliceObject* slice)
        { 
            Index from, to;
            base_get_slice_data(container, slice, from, to);
            ProxyHandler::base_erase_indexes(container, from, to);
            DerivedPolicies::delete_slice(container, from, to);
        }  
    };
    
    template <
          class Container
        , class DerivedPolicies
        , class ProxyHandler
        , class Data
        , class Index
    >
    struct no_slice_helper
    {        
        static void
        slicing_not_suported()
        {
            PyErr_SetString(PyExc_RuntimeError, "Slicing not supported");
            throw_error_already_set();
        }
        
        static object 
        base_get_slice(Container& /*container*/, PySliceObject* /*slice*/)
        { 
            slicing_not_suported();
            return object();
        }
   
        static void 
        base_set_slice(Container& /*container*/, PySliceObject* /*slice*/, PyObject* /*v*/)
        {
            slicing_not_suported();
        }
        
        static void 
        base_delete_slice(Container& /*container*/, PySliceObject* /*slice*/)
        { 
            slicing_not_suported();
        }  
    };

#ifdef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
}} // namespace python::detail
#endif

    template <class Container, class Index, class Policies>
    inline typename Policies::data_type* 
    get_pointer(
        python::detail::container_element<Container, Index, Policies> const& p)
    {
        // Get the pointer of a container_element smart pointer
        return p.get();
    }

#ifndef BOOST_NO_ARGUMENT_DEPENDENT_LOOKUP
    // Don't hide these other get_pointer overloads
    using boost::python::get_pointer;
    using boost::get_pointer;
}} // namespace python::detail
#endif

} // namespace boost

#endif // INDEXING_SUITE_DETAIL_JDG20036_HPP

/* indexing_suite_detail.hpp
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
*/