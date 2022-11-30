// Copyright David Abrahams 2001.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef CLASS_DWA20011214_HPP
# define CLASS_DWA20011214_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/type_id.hpp>
# include <cstddef>

namespace boost { namespace python {

namespace objects { 

struct BOOST_PYTHON_DECL class_base : python::api::object
{
    // constructor
    class_base(
        char const* name              // The name of the class
        
        , std::size_t num_types         // A list of class_ids. The first is the type
        , type_info const*const types    // this is wrapping. The rest are the types of
                                        // any bases.
        
        , char const* doc = 0           // Docstring, if any.
        );


    // Implementation detail. Hiding this in the private section would
    // require use of template friend declarations.
    void enable_pickling_(bool getstate_manages_dict);

 protected:
    void add_property(
        char const* name, object const& fget, char const* docstr);
    void add_property(char const* name, 
        object const& fget, object const& fset, char const* docstr);

    void add_static_property(char const* name, object const& fget);
    void add_static_property(char const* name, object const& fget, object const& fset);
    
    // Retrieve the underlying object
    void setattr(char const* name, object const&);

    // Set a special attribute in the class which tells Boost.Python
    // to allocate extra bytes for embedded C++ objects in Python
    // instances.
    void set_instance_size(std::size_t bytes);

    // Set an __init__ function which throws an appropriate exception
    // for abstract classes.
    void def_no_init();

    // Effects:
    //  setattr(self, staticmethod(getattr(self, method_name)))
    void make_method_static(const char *method_name);
};

}}} // namespace boost::python::objects

#endif // CLASS_DWA20011214_HPP

/* class.hpp
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
*/