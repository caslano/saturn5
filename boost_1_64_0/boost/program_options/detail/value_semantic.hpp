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
C839P8jsKbH5QnL/03Htmpkvzr8CVYbk9g+eQ3pjdTxy+J3Mc7iJeO9Yc7gvLBb7Z9y2vOnKU3ev+XLeoj05S5auan4Ot0fwPuLvgeYExRBRLt3ByygPQj9o4NkAfUsjnw2g5sTGlB78nFgynw0AHxz3OovyUva+DMMwDMMwDMO02vy/dNkIAUjKGoB4xgBqQ+b/x9AYAERBYwCz5Tx1+f5jAIbT5W5+HICO1ZsbBygviDoOcHjNia+S/rt+j69j7031Z9TOmnvRI9O27058nIB8OfWrJku1Rr48Sn7ChTQXDW/eojnolsw/J+K5a+G5G9l3MwzDMAzDMAzzHyP58/8Ol9lK0/9tEPu/5gjO/7eOfPEuB9ZElpm061HcKNNRqsqix22vxv5PyM82leE4Z3LntOclKT/gACf7Z4ZhGIZhGIZhmGSS/Pl/60Sn4XN4DavP5WmbNQAbMAZwLc3/F0asATChnAePXkfz/4YXV2Bgct4IbachIgGKzJbSuHLDNULzkzifn7pE7D+ldsqyvOkD319p3N+/3UbnTYduHKKnbM/2vkM3lKZN/Xb+5n6jB1e+0ynx8QmVy4v6nu7J11p4Lq8MmufPpOcPZtF8/3KnqU3m/BucpqSMV3Rw8XgFwzAMwzAMwzD/bVrP/4v8em3j/7fG4f9XRPf/1M7E/f/hEM9vlT7/uTnThrUf8fb8hTubrvH/cbXp4H3+ihCfXx3h848nn59BPj8zJK6/wmVqdZ8f8PhVLlOLfP5q9vkMwzAMwzAMw/xPSUUpSqr/LzP7xto8HsNq89ks4il0Lc4BIDz+LyEeP0MPPvtNcgxKTR6e5xTm8e1ew++1eYxAe9wem9fm9MX5/LdGaA7KrCXSs+94bOq8JfPnl9Rcd8IbGZVjgp6X6qS2RHjeLPK82fR8sBxoB+hIt0mb7GYfyTAMwzAMwzAMw7Qdyff/frxln/lPxjMAhf/flq0Fn/3eJYb/f+KpSP8vm+JwGHanGAvQEvT+a6T3905M+ainb2jRc8euv21jQXXvoPdHfYl7/07jTVqf8ez9GYZhGIZhGIZhmLYl+fH/FldZmd1nlLmstpAcgHoLvP9fgfz+FHcf8Noa5Yy/BMHklRWa8P4yst/rM3t8frcR0pKEfH+XKhR91Yjjivqnd+03Ot/ZfsU143sEfD/VRW2I9P2dyfcfBxVtQ6Xloo8ns+dnGIZhGIZhGIZhDiGpKM6k+n+rrdjsd/gMhwuL6uHFrXaX4XKLWABvEsYDDpAPQL6+Fs/7i/KyMaS3yheQDZM/hMYTymk8IY/6IxdlOM7/YvhaAqfdZzc77HfbjGYuT/n/4WnC92diofudmfHHGwxNiZU3IPE8AP+ydy1QURVheBZcRF2FBeWhifiIY2UGPgoT84GmJhGZpaWxruwSxLLQslSUCZU9LIvVrDRLtJdmmpRWZmiampZvI0GltNQy0zKPGpY9vpn77+XuyiYkZZ3mO+c/387s3Jm5M3Pn3vn//8498haP/+S+gNsC5kw/dPOM0onzSzeP8rX/gO/9AXYJPYihsFP5ntOrJ/hNOOj3wsX6nb72K/S9b0DBYh7/zMqog/tXtnGNbftUz/j476p97yewXNR/yaljaQXt9fZ+AxdedmjbkdO+91twiHpaEjMPnNhjaz5+xZDBuye1+gzfhBD5T33ohuplkZNdse+Y5jTL6rPd9z4JFaKd9z/TI25kQczOZZGGHauCHkn0vT9Dx/dEe6ZmvvDjisqSjRu3NN+yxpXC2FxRn06JuyOr1j60L/Bk80U/tE1KwugW6QumRm3wX7vW3rnijoXVU4KwIWIPUc+sKTsfNO/v+lvxCWtJ0qGe+PA=
*/