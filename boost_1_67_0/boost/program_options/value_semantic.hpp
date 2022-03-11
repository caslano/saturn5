// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_VALUE_SEMANTIC_HPP_VP_2004_02_24
#define BOOST_VALUE_SEMANTIC_HPP_VP_2004_02_24

#include <boost/program_options/config.hpp>
#include <boost/program_options/errors.hpp>

#include <boost/any.hpp>
#include <boost/function/function1.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <vector>
#include <typeinfo>
#include <limits>

namespace boost { namespace program_options {

    /** Class which specifies how the option's value is to be parsed
        and converted into C++ types.
    */
    class BOOST_PROGRAM_OPTIONS_DECL value_semantic {
    public:
        /** Returns the name of the option. The name is only meaningful
            for automatic help message.
         */
        virtual std::string name() const = 0;

        /** The minimum number of tokens for this option that
            should be present on the command line. */
        virtual unsigned min_tokens() const = 0;

        /** The maximum number of tokens for this option that
            should be present on the command line. */
        virtual unsigned max_tokens() const = 0;

        /** Returns true if values from different sources should be composed.
            Otherwise, value from the first source is used and values from
            other sources are discarded.
        */
        virtual bool is_composing() const = 0;

        /** Returns true if value must be given. Non-optional value

        */
        virtual bool is_required() const = 0;
        
        /** Parses a group of tokens that specify a value of option.
            Stores the result in 'value_store', using whatever representation
            is desired. May be be called several times if value of the same
            option is specified more than once.
        */
        virtual void parse(boost::any& value_store, 
                           const std::vector<std::string>& new_tokens,
                           bool utf8) const 
            = 0;

        /** Called to assign default value to 'value_store'. Returns
            true if default value is assigned, and false if no default
            value exists. */
        virtual bool apply_default(boost::any& value_store) const = 0;
                                   
        /** Called when final value of an option is determined. 
        */
        virtual void notify(const boost::any& value_store) const = 0;
        
        virtual ~value_semantic() {}
    };

    /** Helper class which perform necessary character conversions in the 
        'parse' method and forwards the data further.
    */
    template<class charT>
    class value_semantic_codecvt_helper {
        // Nothing here. Specializations to follow.
    };

    /** Helper conversion class for values that accept ascii
        strings as input.
        Overrides the 'parse' method and defines new 'xparse'
        method taking std::string. Depending on whether input
        to parse is ascii or UTF8, will pass it to xparse unmodified,
        or with UTF8->ascii conversion.
    */
    template<>
    class BOOST_PROGRAM_OPTIONS_DECL 
    value_semantic_codecvt_helper<char> : public value_semantic {
    private: // base overrides
        void parse(boost::any& value_store, 
                   const std::vector<std::string>& new_tokens,
                   bool utf8) const;
    protected: // interface for derived classes.
        virtual void xparse(boost::any& value_store, 
                            const std::vector<std::string>& new_tokens) 
            const = 0;
    };

    /** Helper conversion class for values that accept ascii
        strings as input.
        Overrides the 'parse' method and defines new 'xparse'
        method taking std::wstring. Depending on whether input
        to parse is ascii or UTF8, will recode input to Unicode, or
        pass it unmodified.
    */
    template<>
    class BOOST_PROGRAM_OPTIONS_DECL
    value_semantic_codecvt_helper<wchar_t> : public value_semantic {
    private: // base overrides
        void parse(boost::any& value_store, 
                   const std::vector<std::string>& new_tokens,
                   bool utf8) const;
    protected: // interface for derived classes.
#if !defined(BOOST_NO_STD_WSTRING)
        virtual void xparse(boost::any& value_store, 
                            const std::vector<std::wstring>& new_tokens) 
            const = 0;
#endif
    };

    /** Class which specifies a simple handling of a value: the value will
        have string type and only one token is allowed. */    
    class BOOST_PROGRAM_OPTIONS_DECL 
    untyped_value : public value_semantic_codecvt_helper<char>  {
    public:
        untyped_value(bool zero_tokens = false)
        : m_zero_tokens(zero_tokens)
        {}

        std::string name() const;

        unsigned min_tokens() const;
        unsigned max_tokens() const;

        bool is_composing() const { return false; }

        bool is_required() const { return false; }
        
        /** If 'value_store' is already initialized, or new_tokens
            has more than one elements, throws. Otherwise, assigns
            the first string from 'new_tokens' to 'value_store', without
            any modifications.
         */
        void xparse(boost::any& value_store,
                    const std::vector<std::string>& new_tokens) const;

        /** Does nothing. */
        bool apply_default(boost::any&) const { return false; }

        /** Does nothing. */
        void notify(const boost::any&) const {}        
    private:
        bool m_zero_tokens;
    };

#ifndef BOOST_NO_RTTI
    /** Base class for all option that have a fixed type, and are
        willing to announce this type to the outside world.
        Any 'value_semantics' for which you want to find out the
        type can be dynamic_cast-ed to typed_value_base. If conversion
        succeeds, the 'type' method can be called.
    */
    class typed_value_base 
    {
    public:
        // Returns the type of the value described by this
        // object.
        virtual const std::type_info& value_type() const = 0;
        // Not really needed, since deletion from this
        // class is silly, but just in case.
        virtual ~typed_value_base() {}
    };
#endif


    /** Class which handles value of a specific type. */
    template<class T, class charT = char>
    class typed_value : public value_semantic_codecvt_helper<charT>
#ifndef BOOST_NO_RTTI
                      , public typed_value_base
#endif
    {
    public:
        /** Ctor. The 'store_to' parameter tells where to store
            the value when it's known. The parameter can be NULL. */
        typed_value(T* store_to) 
        : m_store_to(store_to), m_composing(false),
          m_implicit(false), m_multitoken(false),
          m_zero_tokens(false), m_required(false)
        {} 

        /** Specifies default value, which will be used
            if none is explicitly specified. The type 'T' should
            provide operator<< for ostream.
        */
        typed_value* default_value(const T& v)
        {
            m_default_value = boost::any(v);
            m_default_value_as_text = boost::lexical_cast<std::string>(v);
            return this;
        }

        /** Specifies default value, which will be used
            if none is explicitly specified. Unlike the above overload,
            the type 'T' need not provide operator<< for ostream,
            but textual representation of default value must be provided
            by the user.
        */
        typed_value* default_value(const T& v, const std::string& textual)
        {
            m_default_value = boost::any(v);
            m_default_value_as_text = textual;
            return this;
        }

        /** Specifies an implicit value, which will be used
            if the option is given, but without an adjacent value.
            Using this implies that an explicit value is optional,
        */
        typed_value* implicit_value(const T &v)
        {
            m_implicit_value = boost::any(v);
            m_implicit_value_as_text =
                boost::lexical_cast<std::string>(v);
            return this;
        }

        /** Specifies the name used to to the value in help message.  */
        typed_value* value_name(const std::string& name)
        {
            m_value_name = name;
            return this;
        }

        /** Specifies an implicit value, which will be used
            if the option is given, but without an adjacent value.
            Using this implies that an explicit value is optional, but if
            given, must be strictly adjacent to the option, i.e.: '-ovalue'
            or '--option=value'.  Giving '-o' or '--option' will cause the
            implicit value to be applied.
            Unlike the above overload, the type 'T' need not provide
            operator<< for ostream, but textual representation of default
            value must be provided by the user.
        */
        typed_value* implicit_value(const T &v, const std::string& textual)
        {
            m_implicit_value = boost::any(v);
            m_implicit_value_as_text = textual;
            return this;
        }

        /** Specifies a function to be called when the final value
            is determined. */
        typed_value* notifier(function1<void, const T&> f)
        {
            m_notifier = f;
            return this;
        }

        /** Specifies that the value is composing. See the 'is_composing' 
            method for explanation. 
        */
        typed_value* composing()
        {
            m_composing = true;
            return this;
        }

        /** Specifies that the value can span multiple tokens. 
        */
        typed_value* multitoken()
        {
            m_multitoken = true;
            return this;
        }

        /** Specifies that no tokens may be provided as the value of
            this option, which means that only presense of the option
            is significant. For such option to be useful, either the
            'validate' function should be specialized, or the 
            'implicit_value' method should be also used. In most
            cases, you can use the 'bool_switch' function instead of
            using this method. */
        typed_value* zero_tokens() 
        {
            m_zero_tokens = true;
            return this;
        }
            
        /** Specifies that the value must occur. */
        typed_value* required()
        {
            m_required = true;
            return this;
        }

    public: // value semantic overrides

        std::string name() const;

        bool is_composing() const { return m_composing; }

        unsigned min_tokens() const
        {
            if (m_zero_tokens || !m_implicit_value.empty()) {
                return 0;
            } else {
                return 1;
            }
        }

        unsigned max_tokens() const {
            if (m_multitoken) {
                return std::numeric_limits<unsigned>::max BOOST_PREVENT_MACRO_SUBSTITUTION();
            } else if (m_zero_tokens) {
                return 0;
            } else {
                return 1;
            }
        }

        bool is_required() const { return m_required; }

        /** Creates an instance of the 'validator' class and calls
            its operator() to perform the actual conversion. */
        void xparse(boost::any& value_store, 
                    const std::vector< std::basic_string<charT> >& new_tokens) 
            const;

        /** If default value was specified via previous call to 
            'default_value', stores that value into 'value_store'.
            Returns true if default value was stored.
        */
        virtual bool apply_default(boost::any& value_store) const
        {
            if (m_default_value.empty()) {
                return false;
            } else {
                value_store = m_default_value;
                return true;
            }
        }

        /** If an address of variable to store value was specified
            when creating *this, stores the value there. Otherwise,
            does nothing. */
        void notify(const boost::any& value_store) const;

    public: // typed_value_base overrides
        
#ifndef BOOST_NO_RTTI
        const std::type_info& value_type() const
        {
            return typeid(T);
        }
#endif
        

    private:
        T* m_store_to;
        
        // Default value is stored as boost::any and not
        // as boost::optional to avoid unnecessary instantiations.
        std::string m_value_name;
        boost::any m_default_value;
        std::string m_default_value_as_text;
        boost::any m_implicit_value;
        std::string m_implicit_value_as_text;
        bool m_composing, m_implicit, m_multitoken, m_zero_tokens, m_required;
        boost::function1<void, const T&> m_notifier;
    };


    /** Creates a typed_value<T> instance. This function is the primary
        method to create value_semantic instance for a specific type, which
        can later be passed to 'option_description' constructor.
        The second overload is used when it's additionally desired to store the 
        value of option into program variable.
    */
    template<class T>
    typed_value<T>*
    value();

    /** @overload 
    */
    template<class T>
    typed_value<T>*
    value(T* v);

    /** Creates a typed_value<T> instance. This function is the primary
        method to create value_semantic instance for a specific type, which
        can later be passed to 'option_description' constructor.
    */
    template<class T>
    typed_value<T, wchar_t>*
    wvalue();

    /** @overload   
    */
    template<class T>
    typed_value<T, wchar_t>*
    wvalue(T* v);

    /** Works the same way as the 'value<bool>' function, but the created
        value_semantic won't accept any explicit value. So, if the option 
        is present on the command line, the value will be 'true'.
    */
    BOOST_PROGRAM_OPTIONS_DECL typed_value<bool>*
    bool_switch();

    /** @overload
    */
    BOOST_PROGRAM_OPTIONS_DECL typed_value<bool>*    
    bool_switch(bool* v);

}}

#include "boost/program_options/detail/value_semantic.hpp"

#endif


/* value_semantic.hpp
++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
*/