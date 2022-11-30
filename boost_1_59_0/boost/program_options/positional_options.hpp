// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02
#define BOOST_PROGRAM_OPTIONS_POSITIONAL_OPTIONS_VP_2004_03_02

#include <boost/program_options/config.hpp>

#include <vector>
#include <string>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'std::vector<_Ty>' needs to have dll-interface to be used by clients of class 'boost::program_options::positional_options_description'
#endif

namespace boost { namespace program_options {

    /** Describes positional options. 

        The class allows to guess option names for positional options, which
        are specified on the command line and are identified by the position.
        The class uses the information provided by the user to associate a name
        with every positional option, or tell that no name is known. 

        The primary assumption is that only the relative order of the
        positional options themselves matters, and that any interleaving
        ordinary options don't affect interpretation of positional options.
        
        The user initializes the class by specifying that first N positional 
        options should be given the name X1, following M options should be given 
        the name X2 and so on. 
    */
    class BOOST_PROGRAM_OPTIONS_DECL positional_options_description {
    public:
        positional_options_description();

        /** Species that up to 'max_count' next positional options
            should be given the 'name'. The value of '-1' means 'unlimited'. 
            No calls to 'add' can be made after call with 'max_value' equal to 
            '-1'.            
        */
        positional_options_description&
        add(const char* name, int max_count);

        /** Returns the maximum number of positional options that can
            be present. Can return (numeric_limits<unsigned>::max)() to
            indicate unlimited number. */
        unsigned max_total_count() const;

        /** Returns the name that should be associated with positional
            options at 'position'. 
            Precondition: position < max_total_count()
        */
        const std::string& name_for_position(unsigned position) const;

    private:
        // List of names corresponding to the positions. If the number of
        // positions is unlimited, then the last name is stored in
        // m_trailing;
        std::vector<std::string> m_names;
        std::string m_trailing;
    };

}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif


/* positional_options.hpp
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
*/