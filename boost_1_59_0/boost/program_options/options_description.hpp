// Copyright Vladimir Prus 2002-2004.
// Copyright Bertolt Mildner 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_OPTION_DESCRIPTION_VP_2003_05_19
#define BOOST_OPTION_DESCRIPTION_VP_2003_05_19

#include <boost/program_options/config.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/value_semantic.hpp>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/workaround.hpp>
#include <boost/any.hpp>

#include <string>
#include <vector>
#include <set>
#include <map>
#include <stdexcept>
#include <utility>

#include <iosfwd>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // class 'boost::shared_ptr<T>' needs to have dll-interface to be used by clients of class 'boost::program_options::option_description'
#endif


/** Boost namespace */
namespace boost { 
/** Namespace for the library. */
namespace program_options {

    /** Describes one possible command line/config file option. There are two
        kinds of properties of an option. First describe it syntactically and
        are used only to validate input. Second affect interpretation of the
        option, for example default value for it or function that should be
        called  when the value is finally known. Routines which perform parsing
        never use second kind of properties \-- they are side effect free.
        @sa options_description
    */
    class BOOST_PROGRAM_OPTIONS_DECL option_description {
    public:

        option_description();

        /** Initializes the object with the passed data.

            Note: it would be nice to make the second parameter auto_ptr,
            to explicitly pass ownership. Unfortunately, it's often needed to
            create objects of types derived from 'value_semantic':
               options_description d;
               d.add_options()("a", parameter<int>("n")->default_value(1));
            Here, the static type returned by 'parameter' should be derived
            from value_semantic.

            Alas, derived->base conversion for auto_ptr does not really work,
            see
            http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2000/n1232.pdf
            http://www.open-std.org/jtc1/sc22/wg21/docs/cwg_defects.html#84

            So, we have to use plain old pointers. Besides, users are not
            expected to use the constructor directly.

            
            The 'name' parameter is interpreted by the following rules:
            - if there's no "," character in 'name', it specifies long name
            - otherwise, the part before "," specifies long name and the part
            after \-- short name.
        */
        option_description(const char* name,
                           const value_semantic* s);

        /** Initializes the class with the passed data. 
         */
        option_description(const char* name,
                           const value_semantic* s,
                           const char* description);

        virtual ~option_description();

        enum match_result { no_match, full_match, approximate_match };

        /** Given 'option', specified in the input source,
            returns 'true' if 'option' specifies *this.
        */
        match_result match(const std::string& option, bool approx,
                           bool long_ignore_case, bool short_ignore_case) const;

        /** Returns the key that should identify the option, in
            particular in the variables_map class.
            The 'option' parameter is the option spelling from the
            input source.
            If option name contains '*', returns 'option'.
            If long name was specified, it's the long name, otherwise
            it's a short name with prepended '-'.
        */
        const std::string& key(const std::string& option) const;


        /** Returns the canonical name for the option description to enable the user to
            recognised a matching option.
            1) For short options ('-', '/'), returns the short name prefixed.
            2) For long options ('--' / '-') returns the first long name prefixed
            3) All other cases, returns the first long name (if present) or the short
               name, unprefixed.
        */
        std::string canonical_display_name(int canonical_option_style = 0) const;

        const std::string& long_name() const;

        const std::pair<const std::string*, std::size_t> long_names() const;

        /// Explanation of this option
        const std::string& description() const;

        /// Semantic of option's value
        shared_ptr<const value_semantic> semantic() const;
        
        /// Returns the option name, formatted suitably for usage message. 
        std::string format_name() const;

        /** Returns the parameter name and properties, formatted suitably for
            usage message. */
        std::string format_parameter() const;

    private:
    
        option_description& set_names(const char* name);

        /**
         * a one-character "switch" name - with its prefix,
         * so that this is either empty or has length 2 (e.g. "-c"
         */
        std::string m_short_name;

        /**
         *  one or more names by which this option may be specified
         *  on a command-line or in a config file, which are not
         *  a single-letter switch. The names here are _without_
         * any prefix.
         */
        std::vector<std::string> m_long_names;

        std::string m_description;

        // shared_ptr is needed to simplify memory management in
        // copy ctor and destructor.
        shared_ptr<const value_semantic> m_value_semantic;
    };

    class options_description;

    /** Class which provides convenient creation syntax to option_description. 
     */        
    class BOOST_PROGRAM_OPTIONS_DECL options_description_easy_init {
    public:
        options_description_easy_init(options_description* owner);

        options_description_easy_init&
        operator()(const char* name,
                   const char* description);

        options_description_easy_init&
        operator()(const char* name,
                   const value_semantic* s);
        
        options_description_easy_init&
        operator()(const char* name,
                   const value_semantic* s,
                   const char* description);
       
    private:
        options_description* owner;
    };


    /** A set of option descriptions. This provides convenient interface for
        adding new option (the add_options) method, and facilities to search
        for options by name.
        
        See @ref a_adding_options "here" for option adding interface discussion.
        @sa option_description
    */
    class BOOST_PROGRAM_OPTIONS_DECL options_description {
    public:
        static const unsigned m_default_line_length;
        
        /** Creates the instance. */
        options_description(unsigned line_length = m_default_line_length,
                            unsigned min_description_length = m_default_line_length / 2);
        /** Creates the instance. The 'caption' parameter gives the name of
            this 'options_description' instance. Primarily useful for output.
            The 'description_length' specifies the number of columns that
            should be reserved for the description text; if the option text
            encroaches into this, then the description will start on the next
            line.
        */
        options_description(const std::string& caption,
                            unsigned line_length = m_default_line_length,
                            unsigned min_description_length = m_default_line_length / 2);
        /** Adds new variable description. Throws duplicate_variable_error if
            either short or long name matches that of already present one. 
        */
        void add(shared_ptr<option_description> desc);
        /** Adds a group of option description. This has the same
            effect as adding all option_descriptions in 'desc' 
            individually, except that output operator will show
            a separate group.
            Returns *this.
        */
        options_description& add(const options_description& desc);

        /** Find the maximum width of the option column, including options 
            in groups. */
        unsigned get_option_column_width() const;

    public:
        /** Returns an object of implementation-defined type suitable for adding
            options to options_description. The returned object will
            have overloaded operator() with parameter type matching 
            'option_description' constructors. Calling the operator will create
            new option_description instance and add it.
        */
        options_description_easy_init add_options();

        const option_description& find(const std::string& name, 
                                       bool approx, 
                                       bool long_ignore_case = false,
                                       bool short_ignore_case = false) const;

        const option_description* find_nothrow(const std::string& name, 
                                               bool approx,
                                               bool long_ignore_case = false,
                                               bool short_ignore_case = false) const;


        const std::vector< shared_ptr<option_description> >& options() const;

        /** Produces a human readable output of 'desc', listing options,
            their descriptions and allowed parameters. Other options_description
            instances previously passed to add will be output separately. */
        friend BOOST_PROGRAM_OPTIONS_DECL std::ostream& operator<<(std::ostream& os, 
                                             const options_description& desc);

        /** Outputs 'desc' to the specified stream, calling 'f' to output each
            option_description element. */
        void print(std::ostream& os, unsigned width = 0) const;

    private:
#if BOOST_WORKAROUND(BOOST_MSVC, BOOST_TESTED_AT(1800))
        // prevent warning C4512: assignment operator could not be generated
        options_description& operator=(const options_description&);
#endif

        typedef std::map<std::string, int>::const_iterator name2index_iterator;
        typedef std::pair<name2index_iterator, name2index_iterator> 
            approximation_range;

        //approximation_range find_approximation(const std::string& prefix) const;

        std::string m_caption;
        const unsigned m_line_length;
        const unsigned m_min_description_length;
        
        // Data organization is chosen because:
        // - there could be two names for one option
        // - option_add_proxy needs to know the last added option
        std::vector< shared_ptr<option_description> > m_options;

        // Whether the option comes from one of declared groups.
#if BOOST_WORKAROUND(BOOST_DINKUMWARE_STDLIB, BOOST_TESTED_AT(313))
        // vector<bool> is buggy there, see
        // http://support.microsoft.com/default.aspx?scid=kb;en-us;837698
        std::vector<char> belong_to_group;
#else
        std::vector<bool> belong_to_group;
#endif

        std::vector< shared_ptr<options_description> > groups;

    };

    /** Class thrown when duplicate option description is found. */
    class BOOST_PROGRAM_OPTIONS_DECL duplicate_option_error : public error {
    public:
        duplicate_option_error(const std::string& xwhat) : error(xwhat) {}
    };
}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif

/* options_description.hpp
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
*/