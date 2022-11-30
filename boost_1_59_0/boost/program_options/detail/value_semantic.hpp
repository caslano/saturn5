// Copyright Vladimir Prus 2004.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

// This file defines template functions that are declared in
// ../value_semantic.hpp.

#include <boost/throw_exception.hpp>

// forward declaration
namespace boost { template<class T> class optional; }

namespace boost { namespace program_options { 

    extern BOOST_PROGRAM_OPTIONS_DECL std::string arg;
    
    template<class T, class charT>
    std::string
    typed_value<T, charT>::name() const
    {
        std::string const& var = (m_value_name.empty() ? arg : m_value_name);
        if (!m_implicit_value.empty() && !m_implicit_value_as_text.empty()) {
            std::string msg = "[=" + var + "(=" + m_implicit_value_as_text + ")]";
            if (!m_default_value.empty() && !m_default_value_as_text.empty())
                msg += " (=" + m_default_value_as_text + ")";
            return msg;
        }
        else if (!m_default_value.empty() && !m_default_value_as_text.empty()) {
            return var + " (=" + m_default_value_as_text + ")";
        } else {
            return var;
        }
    }

    template<class T, class charT>
    void 
    typed_value<T, charT>::notify(const boost::any& value_store) const
    {
        const T* value = boost::any_cast<T>(&value_store);
        if (m_store_to) {
            *m_store_to = *value;
        }
        if (m_notifier) {
            m_notifier(*value);
        }
    }

    namespace validators {
        /* If v.size() > 1, throw validation_error. 
           If v.size() == 1, return v.front()
           Otherwise, returns a reference to a statically allocated
           empty string if 'allow_empty' and throws validation_error
           otherwise. */
        template<class charT>
        const std::basic_string<charT>& get_single_string(
            const std::vector<std::basic_string<charT> >& v, 
            bool allow_empty = false)
        {
            static std::basic_string<charT> empty;
            if (v.size() > 1)
                boost::throw_exception(validation_error(validation_error::multiple_values_not_allowed));
            else if (v.size() == 1)
                return v.front();
            else if (!allow_empty)
                boost::throw_exception(validation_error(validation_error::at_least_one_value_required));
            return empty;
        }

        /* Throws multiple_occurrences if 'value' is not empty. */
        BOOST_PROGRAM_OPTIONS_DECL void 
        check_first_occurrence(const boost::any& value);
    }

    using namespace validators;

    /** Validates 's' and updates 'v'.
        @pre 'v' is either empty or in the state assigned by the previous
        invocation of 'validate'.
        The target type is specified via a parameter which has the type of 
        pointer to the desired type. This is workaround for compilers without
        partial template ordering, just like the last 'long/int' parameter.
    */
    template<class T, class charT>
    void validate(boost::any& v, 
                  const std::vector< std::basic_string<charT> >& xs, 
                  T*, long)
    {
        validators::check_first_occurrence(v);
        std::basic_string<charT> s(validators::get_single_string(xs));
        try {
            v = any(lexical_cast<T>(s));
        }
        catch(const bad_lexical_cast&) {
            boost::throw_exception(invalid_option_value(s));
        }
    }

    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::string>& xs, 
                       bool*,
                       int);

#if !defined(BOOST_NO_STD_WSTRING)
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::wstring>& xs, 
                       bool*,
                       int);
#endif
    // For some reason, this declaration, which is require by the standard,
    // cause msvc 7.1 to not generate code to specialization defined in
    // value_semantic.cpp
#if ! ( BOOST_WORKAROUND(BOOST_MSVC, == 1310) )
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::string>& xs,
                       std::string*,
                       int);

#if !defined(BOOST_NO_STD_WSTRING)
    BOOST_PROGRAM_OPTIONS_DECL void validate(boost::any& v, 
                       const std::vector<std::wstring>& xs,
                       std::string*,
                       int);
#endif
#endif

    /** Validates sequences. Allows multiple values per option occurrence
       and multiple occurrences. */
    template<class T, class charT>
    void validate(boost::any& v, 
                  const std::vector<std::basic_string<charT> >& s, 
                  std::vector<T>*,
                  int)
    {
        if (v.empty()) {
            v = boost::any(std::vector<T>());
        }
        std::vector<T>* tv = boost::any_cast< std::vector<T> >(&v);
        assert(NULL != tv);
        for (unsigned i = 0; i < s.size(); ++i)
        {
            try {
                /* We call validate so that if user provided
                   a validator for class T, we use it even
                   when parsing vector<T>.  */
                boost::any a;
                std::vector<std::basic_string<charT> > cv;
                cv.push_back(s[i]);
                validate(a, cv, (T*)0, 0);                
                tv->push_back(boost::any_cast<T>(a));
            }
            catch(const bad_lexical_cast& /*e*/) {
                boost::throw_exception(invalid_option_value(s[i]));
            }
        }
    }

    /** Validates optional arguments. */
    template<class T, class charT>
    void validate(boost::any& v,
                  const std::vector<std::basic_string<charT> >& s,
                  boost::optional<T>*,
                  int)
    {
        validators::check_first_occurrence(v);
        validators::get_single_string(s);
        boost::any a;
        validate(a, s, (T*)0, 0);
        v = boost::any(boost::optional<T>(boost::any_cast<T>(a)));
    }

    template<class T, class charT>
    void 
    typed_value<T, charT>::
    xparse(boost::any& value_store, 
           const std::vector<std::basic_string<charT> >& new_tokens) const
    {
        // If no tokens were given, and the option accepts an implicit
        // value, then assign the implicit value as the stored value;
        // otherwise, validate the user-provided token(s).
        if (new_tokens.empty() && !m_implicit_value.empty())
            value_store = m_implicit_value;
        else
            validate(value_store, new_tokens, (T*)0, 0);
    }

    template<class T>
    typed_value<T>*
    value()
    {
        // Explicit qualification is vc6 workaround.
        return boost::program_options::value<T>(0);
    }

    template<class T>
    typed_value<T>*
    value(T* v)
    {
        typed_value<T>* r = new typed_value<T>(v);

        return r;        
    }

    template<class T>
    typed_value<T, wchar_t>*
    wvalue()
    {
        return wvalue<T>(0);
    }

    template<class T>
    typed_value<T, wchar_t>*
    wvalue(T* v)
    {
        typed_value<T, wchar_t>* r = new typed_value<T, wchar_t>(v);

        return r;        
    }



}}

/* value_semantic.hpp
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
*/