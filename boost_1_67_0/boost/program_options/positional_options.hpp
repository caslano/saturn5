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