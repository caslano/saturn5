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