// Copyright Vladimir Prus 2002-2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)


#ifndef BOOST_VARIABLES_MAP_VP_2003_05_19
#define BOOST_VARIABLES_MAP_VP_2003_05_19

#include <boost/program_options/config.hpp>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <map>
#include <set>

#if defined(BOOST_MSVC)
#   pragma warning (push)
#   pragma warning (disable:4251) // 'boost::program_options::variable_value::v' : class 'boost::any' needs to have dll-interface to be used by clients of class 'boost::program_options::variable_value
#endif

namespace boost { namespace program_options {

    template<class charT>
    class basic_parsed_options;

    class value_semantic;
    class variables_map;

    // forward declaration

    /** Stores in 'm' all options that are defined in 'options'.
        If 'm' already has a non-defaulted value of an option, that value
        is not changed, even if 'options' specify some value.
    */
    BOOST_PROGRAM_OPTIONS_DECL
    void store(const basic_parsed_options<char>& options, variables_map& m,
                    bool utf8 = false);

    /** Stores in 'm' all options that are defined in 'options'.
        If 'm' already has a non-defaulted value of an option, that value
        is not changed, even if 'options' specify some value.
        This is wide character variant.
    */
    BOOST_PROGRAM_OPTIONS_DECL
    void store(const basic_parsed_options<wchar_t>& options,
                    variables_map& m);


    /** Runs all 'notify' function for options in 'm'. */
    BOOST_PROGRAM_OPTIONS_DECL void notify(variables_map& m);

    /** Class holding value of option. Contains details about how the
        value is set and allows to conveniently obtain the value.
    */
    class BOOST_PROGRAM_OPTIONS_DECL variable_value {
    public:
        variable_value() : m_defaulted(false) {}
        variable_value(const boost::any& xv, bool xdefaulted)
        : v(xv), m_defaulted(xdefaulted)
        {}

        /** If stored value if of type T, returns that value. Otherwise,
            throws boost::bad_any_cast exception. */
       template<class T>
       const T& as() const {
           return boost::any_cast<const T&>(v);
       }
       /** @overload */
       template<class T>
       T& as() {
           return boost::any_cast<T&>(v);
       }

        /// Returns true if no value is stored.
        bool empty() const;
        /** Returns true if the value was not explicitly
            given, but has default value. */
        bool defaulted() const;
        /** Returns the contained value. */
        const boost::any& value() const;

        /** Returns the contained value. */
        boost::any& value();
    private:
        boost::any v;
        bool m_defaulted;
        // Internal reference to value semantic. We need to run
        // notifications when *final* values of options are known, and
        // they are known only after all sources are stored. By that
        // time options_description for the first source might not
        // be easily accessible, so we need to store semantic here.
        shared_ptr<const value_semantic> m_value_semantic;

        friend BOOST_PROGRAM_OPTIONS_DECL
        void store(const basic_parsed_options<char>& options,
              variables_map& m, bool);

        friend class BOOST_PROGRAM_OPTIONS_DECL variables_map;
    };

    /** Implements string->string mapping with convenient value casting
        facilities. */
    class BOOST_PROGRAM_OPTIONS_DECL abstract_variables_map {
    public:
        abstract_variables_map();
        abstract_variables_map(const abstract_variables_map* next);

        virtual ~abstract_variables_map() {}

        /** Obtains the value of variable 'name', from *this and
            possibly from the chain of variable maps.

            - if there's no value in *this.
                - if there's next variable map, returns value from it
                - otherwise, returns empty value

            - if there's defaulted value
                - if there's next variable map, which has a non-defaulted
                  value, return that
                - otherwise, return value from *this

            - if there's a non-defaulted value, returns it.
        */
        const variable_value& operator[](const std::string& name) const;

        /** Sets next variable map, which will be used to find
           variables not found in *this. */
        void next(abstract_variables_map* next);

    private:
        /** Returns value of variable 'name' stored in *this, or
            empty value otherwise. */
        virtual const variable_value& get(const std::string& name) const = 0;

        const abstract_variables_map* m_next;
    };

    /** Concrete variables map which store variables in real map.

        This class is derived from std::map<std::string, variable_value>,
        so you can use all map operators to examine its content.
    */
    class BOOST_PROGRAM_OPTIONS_DECL variables_map : public abstract_variables_map,
                               public std::map<std::string, variable_value>
    {
    public:
        variables_map();
        variables_map(const abstract_variables_map* next);

        // Resolve conflict between inherited operators.
        const variable_value& operator[](const std::string& name) const
        { return abstract_variables_map::operator[](name); }

        // Override to clear some extra fields.
        void clear();

        void notify();

    private:
        /** Implementation of abstract_variables_map::get
            which does 'find' in *this. */
        const variable_value& get(const std::string& name) const;

        /** Names of option with 'final' values \-- which should not
            be changed by subsequence assignments. */
        std::set<std::string> m_final;

        friend BOOST_PROGRAM_OPTIONS_DECL
        void store(const basic_parsed_options<char>& options,
                          variables_map& xm,
                          bool utf8);

        /** Names of required options, filled by parser which has
            access to options_description.
            The map values are the "canonical" names for each corresponding option.
            This is useful in creating diagnostic messages when the option is absent. */
        std::map<std::string, std::string> m_required;
    };


    /*
     * Templates/inlines
     */

    inline bool
    variable_value::empty() const
    {
        return v.empty();
    }

    inline bool
    variable_value::defaulted() const
    {
        return m_defaulted;
    }

    inline
    const boost::any&
    variable_value::value() const
    {
        return v;
    }

    inline
    boost::any&
    variable_value::value()
    {
        return v;
    }

}}

#if defined(BOOST_MSVC)
#   pragma warning (pop)
#endif

#endif

/* variables_map.hpp
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
*/