//  Copyright (c) 2008-2009 Ben Hanson
//  Copyright (c) 2008-2011 Hartmut Kaiser
//
//  Distributed under the Boost Software License, Version 1.0. (See accompanying
//  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#if !defined(BOOST_SPIRIT_LEX_LEXERTL_GENERATE_CPP_FEB_10_2008_0855PM)
#define BOOST_SPIRIT_LEX_LEXERTL_GENERATE_CPP_FEB_10_2008_0855PM

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/spirit/home/support/detail/lexer/char_traits.hpp>
#include <boost/spirit/home/support/detail/lexer/consts.hpp>
#include <boost/spirit/home/support/detail/lexer/rules.hpp>
#include <boost/spirit/home/support/detail/lexer/size_t.hpp>
#include <boost/spirit/home/support/detail/lexer/state_machine.hpp>
#include <boost/spirit/home/support/detail/lexer/debug.hpp>
#include <boost/spirit/home/lex/lexer/lexertl/static_version.hpp>
#include <boost/scoped_array.hpp>
#include <cstring>
#include <locale>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit { namespace lex { namespace lexertl
{
    namespace detail
    {

    ///////////////////////////////////////////////////////////////////////////
    template <typename CharT>
    struct string_lit;

    template <>
    struct string_lit<char>
    {
        static char get(char c) { return c; }
        static std::string get(char const* str = "") { return str; }
    };

    template <>
    struct string_lit<wchar_t>
    {
        static wchar_t get(char c)
        {
            typedef std::ctype<wchar_t> ctype_t;
            return std::use_facet<ctype_t>(std::locale()).widen(c);
        }
        static std::basic_string<wchar_t> get(char const* source = "")
        {
            using namespace std;        // some systems have size_t in ns std
            size_t len = strlen(source);
            boost::scoped_array<wchar_t> result (new wchar_t[len+1]);
            result.get()[len] = '\0';

            // working with wide character streams is supported only if the
            // platform provides the std::ctype<wchar_t> facet
            BOOST_ASSERT(std::has_facet<std::ctype<wchar_t> >(std::locale()));

            std::use_facet<std::ctype<wchar_t> >(std::locale())
                .widen(source, source + len, result.get());
            return result.get();
        }
    };

    template <typename Char>
    inline Char L(char c)
    {
        return string_lit<Char>::get(c);
    }

    template <typename Char>
    inline std::basic_string<Char> L(char const* c = "")
    {
        return string_lit<Char>::get(c);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char>
    inline bool
    generate_delimiter(std::basic_ostream<Char> &os_)
    {
        os_ << std::basic_string<Char>(80, '/') << "\n";
        return os_.good();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate a table of the names of the used lexer states, which is a bit
    // tricky, because the table stored with the rules is sorted based on the
    // names, but we need it sorted using the state ids.
    template <typename Char>
    inline bool
    generate_cpp_state_info (boost::lexer::basic_rules<Char> const& rules_
      , std::basic_ostream<Char> &os_, Char const* name_suffix)
    {
        // we need to re-sort the state names in ascending order of the state
        // ids, filling possible gaps in between later
        typedef typename
            boost::lexer::basic_rules<Char>::string_size_t_map::const_iterator
        state_iterator;
        typedef std::map<std::size_t, Char const*> reverse_state_map_type;

        reverse_state_map_type reverse_state_map;
        state_iterator send = rules_.statemap().end();
        for (state_iterator sit = rules_.statemap().begin(); sit != send; ++sit)
        {
            typedef typename reverse_state_map_type::value_type value_type;
            reverse_state_map.insert(value_type((*sit).second, (*sit).first.c_str()));
        }

        generate_delimiter(os_);
        os_ << "// this table defines the names of the lexer states\n";
        os_ << boost::lexer::detail::strings<Char>::char_name()
            << " const* const lexer_state_names"
            << (name_suffix[0] ? "_" : "") << name_suffix
            << "[" << rules_.statemap().size() << "] = \n{\n";

        typedef typename reverse_state_map_type::iterator iterator;
        iterator rend = reverse_state_map.end();
        std::size_t last_id = 0;
        for (iterator rit = reverse_state_map.begin(); rit != rend; ++last_id)
        {
            for (/**/; last_id < (*rit).first; ++last_id)
            {
                os_ << "    0,  // \"<undefined state>\"\n";
            }
            os_ << "    "
                << boost::lexer::detail::strings<Char>::char_prefix()
                << "\"" << (*rit).second << "\"";
            if (++rit != rend)
                os_ << ",\n";
            else
                os_ << "\n";        // don't generate the final comma
        }
        os_ << "};\n\n";

        generate_delimiter(os_);
        os_ << "// this variable defines the number of lexer states\n";
        os_ << "std::size_t const lexer_state_count"
            << (name_suffix[0] ? "_" : "") << name_suffix
            << " = " << rules_.statemap().size() << ";\n\n";
        return os_.good();
    }

    template <typename Char>
    inline bool
    generate_cpp_state_table (std::basic_ostream<Char> &os_
      , Char const* name_suffix, bool bol, bool eol)
    {
        std::basic_string<Char> suffix(L<Char>(name_suffix[0] ? "_" : ""));
        suffix += name_suffix;

        generate_delimiter(os_);
        os_ << "// this defines a generic accessors for the information above\n";
        os_ << "struct lexer" << suffix << "\n{\n";
        os_ << "    // version number and feature-set of compatible static lexer engine\n";
        os_ << "    enum\n";
        os_ << "    {\n        static_version = " << SPIRIT_STATIC_LEXER_VERSION << ",\n";
        os_ << "        supports_bol = " << std::boolalpha << bol << ",\n";
        os_ << "        supports_eol = " << std::boolalpha << eol << "\n";
        os_ << "    };\n\n";
        os_ << "    // return the number of lexer states\n";
        os_ << "    static std::size_t state_count()\n";
        os_ << "    {\n        return lexer_state_count" << suffix << "; \n    }\n\n";
        os_ << "    // return the name of the lexer state as given by 'idx'\n";
        os_ << "    static " << boost::lexer::detail::strings<Char>::char_name()
            << " const* state_name(std::size_t idx)\n";
        os_ << "    {\n        return lexer_state_names" << suffix << "[idx]; \n    }\n\n";
        os_ << "    // return the next matched token\n";
        os_ << "    template<typename Iterator>\n";
        os_ << "    static std::size_t next(std::size_t &start_state_, bool& bol_\n";
        os_ << "      , Iterator &start_token_, Iterator const& end_, std::size_t& unique_id_)\n";
        os_ << "    {\n        return next_token" << suffix
            << "(start_state_, bol_, start_token_, end_, unique_id_);\n    }\n";
        os_ << "};\n\n";
        return os_.good();
    }

    ///////////////////////////////////////////////////////////////////////////
    // generate function body based on traversing the DFA tables
    template <typename Char>
    bool generate_function_body_dfa(std::basic_ostream<Char>& os_
      , boost::lexer::basic_state_machine<Char> const &sm_)
    {
        std::size_t const dfas_ = sm_.data()._dfa->size();
        std::size_t const lookups_ = sm_.data()._lookup->front()->size();

        os_ << "    enum {end_state_index, id_index, unique_id_index, "
               "state_index, bol_index,\n";
        os_ << "        eol_index, dead_state_index, dfa_offset};\n\n";
        os_ << "    static std::size_t const npos = "
               "static_cast<std::size_t>(~0);\n";

        if (dfas_ > 1)
        {
            for (std::size_t state_ = 0; state_ < dfas_; ++state_)
            {
                std::size_t i_ = 0;
                std::size_t j_ = 1;
                std::size_t count_ = lookups_ / 8;
                std::size_t const* lookup_ = &sm_.data()._lookup[state_]->front();
                std::size_t const* dfa_ = &sm_.data()._dfa[state_]->front();

                os_ << "    static std::size_t const lookup" << state_
                    << "_[" << lookups_ << "] = {\n        ";
                for (/**/; i_ < count_; ++i_)
                {
                    std::size_t const index_ = i_ * 8;
                    os_ << lookup_[index_];
                    for (/**/; j_ < 8; ++j_)
                    {
                        os_ << ", " << lookup_[index_ + j_];
                    }
                    if (i_ < count_ - 1)
                    {
                        os_ << ",\n        ";
                    }
                    j_ = 1;
                }
                os_ << " };\n";

                count_ = sm_.data()._dfa[state_]->size ();
                os_ << "    static const std::size_t dfa" << state_ << "_["
                    << count_ << "] = {\n        ";
                count_ /= 8;
                for (i_ = 0; i_ < count_; ++i_)
                {
                    std::size_t const index_ = i_ * 8;
                    os_ << dfa_[index_];
                    for (j_ = 1; j_ < 8; ++j_)
                    {
                        os_ << ", " << dfa_[index_ + j_];
                    }
                    if (i_ < count_ - 1)
                    {
                        os_ << ",\n        ";
                    }
                }

                std::size_t const mod_ = sm_.data()._dfa[state_]->size () % 8;
                if (mod_)
                {
                    std::size_t const index_ = count_ * 8;
                    if (count_)
                    {
                        os_ << ",\n        ";
                    }
                    os_ << dfa_[index_];
                    for (j_ = 1; j_ < mod_; ++j_)
                    {
                        os_ << ", " << dfa_[index_ + j_];
                    }
                }
                os_ << " };\n";
            }

            std::size_t count_ = sm_.data()._dfa_alphabet.size();
            std::size_t i_ = 1;

            os_ << "    static std::size_t const* lookup_arr_[" << count_
                << "] = { lookup0_";
            for (i_ = 1; i_ < count_; ++i_)
            {
                os_ << ", " << "lookup" << i_ << "_";
            }
            os_ << " };\n";

            os_ << "    static std::size_t const dfa_alphabet_arr_["
                << count_ << "] = { ";
            os_ << sm_.data()._dfa_alphabet.front ();
            for (i_ = 1; i_ < count_; ++i_)
            {
                os_ << ", " << sm_.data()._dfa_alphabet[i_];
            }
            os_ << " };\n";

            os_ << "    static std::size_t const* dfa_arr_[" << count_
                << "] = { ";
            os_ << "dfa0_";
            for (i_ = 1; i_ < count_; ++i_)
            {
                os_ << ", " << "dfa" << i_ << "_";
            }
            os_ << " };\n";
        }
        else
        {
            std::size_t const* lookup_ = &sm_.data()._lookup[0]->front();
            std::size_t const* dfa_ = &sm_.data()._dfa[0]->front();
            std::size_t i_ = 0;
            std::size_t j_ = 1;
            std::size_t count_ = lookups_ / 8;

            os_ << "    static std::size_t const lookup_[";
            os_ << sm_.data()._lookup[0]->size() << "] = {\n        ";
            for (/**/; i_ < count_; ++i_)
            {
                const std::size_t index_ = i_ * 8;
                os_ << lookup_[index_];
                for (/**/; j_ < 8; ++j_)
                {
                    os_ << ", " << lookup_[index_ + j_];
                }
                if (i_ < count_ - 1)
                {
                    os_ << ",\n        ";
                }
                j_ = 1;
            }
            os_ << " };\n";

            os_ << "    static std::size_t const dfa_alphabet_ = "
                << sm_.data()._dfa_alphabet.front () << ";\n";
            os_ << "    static std::size_t const dfa_["
                << sm_.data()._dfa[0]->size () << "] = {\n        ";
            count_ = sm_.data()._dfa[0]->size () / 8;
            for (i_ = 0; i_ < count_; ++i_)
            {
                const std::size_t index_ = i_ * 8;
                os_ << dfa_[index_];
                for (j_ = 1; j_ < 8; ++j_)
                {
                    os_ << ", " << dfa_[index_ + j_];
                }
                if (i_ < count_ - 1)
                {
                    os_ << ",\n        ";
                }
            }

            const std::size_t mod_ = sm_.data()._dfa[0]->size () % 8;
            if (mod_)
            {
                const std::size_t index_ = count_ * 8;
                if (count_)
                {
                    os_ << ",\n        ";
                }
                os_ << dfa_[index_];
                for (j_ = 1; j_ < mod_; ++j_)
                {
                    os_ << ", " << dfa_[index_ + j_];
                }
            }
            os_ << " };\n";
        }

        os_ << "\n    if (start_token_ == end_)\n";
        os_ << "    {\n";
        os_ << "        unique_id_ = npos;\n";
        os_ << "        return 0;\n";
        os_ << "    }\n\n";
        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "    bool bol = bol_;\n\n";
        }

        if (dfas_ > 1)
        {
            os_ << "again:\n";
            os_ << "    std::size_t const* lookup_ = lookup_arr_[start_state_];\n";
            os_ << "    std::size_t dfa_alphabet_ = dfa_alphabet_arr_[start_state_];\n";
            os_ << "    std::size_t const*dfa_ = dfa_arr_[start_state_];\n";
        }

        os_ << "    std::size_t const* ptr_ = dfa_ + dfa_alphabet_;\n";
        os_ << "    Iterator curr_ = start_token_;\n";
        os_ << "    bool end_state_ = *ptr_ != 0;\n";
        os_ << "    std::size_t id_ = *(ptr_ + id_index);\n";
        os_ << "    std::size_t uid_ = *(ptr_ + unique_id_index);\n";
        if (dfas_ > 1)
        {
            os_ << "    std::size_t end_start_state_ = start_state_;\n";
        }
        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "    bool end_bol_ = bol_;\n";
        }
        os_ << "    Iterator end_token_ = start_token_;\n\n";

        os_ << "    while (curr_ != end_)\n";
        os_ << "    {\n";

        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        std::size_t const BOL_state_ = ptr_[bol_index];\n\n";
        }

        if (sm_.data()._seen_EOL_assertion)
        {
            os_ << "        std::size_t const EOL_state_ = ptr_[eol_index];\n\n";
        }

        if (sm_.data()._seen_BOL_assertion && sm_.data()._seen_EOL_assertion)
        {
            os_ << "        if (BOL_state_ && bol)\n";
            os_ << "        {\n";
            os_ << "            ptr_ = &dfa_[BOL_state_ * dfa_alphabet_];\n";
            os_ << "        }\n";
            os_ << "        else if (EOL_state_ && *curr_ == '\\n')\n";
            os_ << "        {\n";
            os_ << "            ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];\n";
            os_ << "        }\n";
            os_ << "        else\n";
            os_ << "        {\n";
            if (lookups_ == 256)
            {
                os_ << "            unsigned char index = \n";
                os_ << "                static_cast<unsigned char>(*curr_++);\n";
            }
            else
            {
                os_ << "            std::size_t index = *curr_++\n";
            }
            os_ << "            bol = (index == '\\n') ? true : false;\n";
            os_ << "            std::size_t const state_ = ptr_[\n";
            os_ << "                lookup_[static_cast<std::size_t>(index)]];\n";

            os_ << '\n';
            os_ << "            if (state_ == 0) break;\n";
            os_ << '\n';
            os_ << "            ptr_ = &dfa_[state_ * dfa_alphabet_];\n";
            os_ << "        }\n\n";
        }
        else if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        if (BOL_state_ && bol)\n";
            os_ << "        {\n";
            os_ << "            ptr_ = &dfa_[BOL_state_ * dfa_alphabet_];\n";
            os_ << "        }\n";
            os_ << "        else\n";
            os_ << "        {\n";
            if (lookups_ == 256)
            {
                os_ << "            unsigned char index = \n";
                os_ << "                static_cast<unsigned char>(*curr_++);\n";
            }
            else
            {
                os_ << "            std::size_t index = *curr_++\n";
            }
            os_ << "            bol = (index == '\\n') ? true : false;\n";
            os_ << "            std::size_t const state_ = ptr_[\n";
            os_ << "                lookup_[static_cast<std::size_t>(index)]];\n";

            os_ << '\n';
            os_ << "            if (state_ == 0) break;\n";
            os_ << '\n';
            os_ << "            ptr_ = &dfa_[state_ * dfa_alphabet_];\n";
            os_ << "        }\n\n";
        }
        else if (sm_.data()._seen_EOL_assertion)
        {
            os_ << "        if (EOL_state_ && *curr_ == '\\n')\n";
            os_ << "        {\n";
            os_ << "            ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];\n";
            os_ << "        }\n";
            os_ << "        else\n";
            os_ << "        {\n";
            if (lookups_ == 256)
            {
                os_ << "            unsigned char index = \n";
                os_ << "                static_cast<unsigned char>(*curr_++);\n";
            }
            else
            {
                os_ << "            std::size_t index = *curr_++\n";
            }
            os_ << "            bol = (index == '\\n') ? true : false;\n";
            os_ << "            std::size_t const state_ = ptr_[\n";
            os_ << "                lookup_[static_cast<std::size_t>(index)]];\n";

            os_ << '\n';
            os_ << "            if (state_ == 0) break;\n";
            os_ << '\n';
            os_ << "            ptr_ = &dfa_[state_ * dfa_alphabet_];\n";
            os_ << "        }\n\n";
        }
        else
        {
            os_ << "        std::size_t const state_ =\n";

            if (lookups_ == 256)
            {
                os_ << "            ptr_[lookup_["
                       "static_cast<unsigned char>(*curr_++)]];\n";
            }
            else
            {
                os_ << "            ptr_[lookup_[*curr_++]];\n";
            }

            os_ << '\n';
            os_ << "        if (state_ == 0) break;\n";
            os_ << '\n';
            os_ << "        ptr_ = &dfa_[state_ * dfa_alphabet_];\n\n";
        }

        os_ << "        if (*ptr_)\n";
        os_ << "        {\n";
        os_ << "            end_state_ = true;\n";
        os_ << "            id_ = *(ptr_ + id_index);\n";
        os_ << "            uid_ = *(ptr_ + unique_id_index);\n";
        if (dfas_ > 1)
        {
            os_ << "            end_start_state_ = *(ptr_ + state_index);\n";
        }
        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "            end_bol_ = bol;\n";
        }
        os_ << "            end_token_ = curr_;\n";
        os_ << "        }\n";
        os_ << "    }\n\n";

        if (sm_.data()._seen_EOL_assertion)
        {
            os_ << "    std::size_t const EOL_state_ = ptr_[eol_index];\n\n";

            os_ << "    if (EOL_state_ && curr_ == end_)\n";
            os_ << "    {\n";
            os_ << "        ptr_ = &dfa_[EOL_state_ * dfa_alphabet_];\n\n";

            os_ << "        if (*ptr_)\n";
            os_ << "        {\n";
            os_ << "            end_state_ = true;\n";
            os_ << "            id_ = *(ptr_ + id_index);\n";
            os_ << "            uid_ = *(ptr_ + unique_id_index);\n";
            if (dfas_ > 1)
            {
                os_ << "            end_start_state_ = *(ptr_ + state_index);\n";
            }
            if (sm_.data()._seen_BOL_assertion)
            {
                os_ << "            end_bol_ = bol;\n";
            }
            os_ << "            end_token_ = curr_;\n";
            os_ << "        }\n";
            os_ << "    }\n\n";
        }

        os_ << "    if (end_state_)\n";
        os_ << "    {\n";
        os_ << "        // return longest match\n";
        os_ << "        start_token_ = end_token_;\n";

        if (dfas_ > 1)
        {
            os_ << "        start_state_ = end_start_state_;\n";
            os_ << "        if (id_ == 0)\n";
            os_ << "        {\n";
            if (sm_.data()._seen_BOL_assertion)
            {
                os_ << "            bol = end_bol_;\n";
            }
            os_ << "            goto again;\n";
            os_ << "        }\n";
            if (sm_.data()._seen_BOL_assertion)
            {
                os_ << "        else\n";
                os_ << "        {\n";
                os_ << "            bol_ = end_bol_;\n";
                os_ << "        }\n";
            }
        }
        else if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        bol_ = end_bol_;\n";
        }

        os_ << "    }\n";
        os_ << "    else\n";
        os_ << "    {\n";

        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        bol_ = (*start_token_ == '\\n') ? true : false;\n";
        }

        os_ << "        id_ = npos;\n";
        os_ << "        uid_ = npos;\n";
        os_ << "    }\n\n";

        os_ << "    unique_id_ = uid_;\n";
        os_ << "    return id_;\n";
        return os_.good();
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char>
    inline std::basic_string<Char> get_charlit(Char ch)
    {
        std::basic_string<Char> result;
        boost::lexer::basic_string_token<Char>::escape_char(ch, result);
        return result;
    }

    // check whether state0_0 is referenced from any of the other states
    template <typename Char>
    bool need_label0_0(boost::lexer::basic_state_machine<Char> const &sm_)
    {
        typedef typename boost::lexer::basic_state_machine<Char>::iterator
            iterator_type;
        iterator_type iter_ = sm_.begin();
        std::size_t const states_ = iter_->states;

        for (std::size_t state_ = 0; state_ < states_; ++state_)
        {
            if (0 == iter_->bol_index || 0 == iter_->eol_index)
            {
                return true;
            }

            std::size_t const transitions_ = iter_->transitions;
            for (std::size_t t_ = 0; t_ < transitions_; ++t_)
            {
                if (0 == iter_->goto_state)
                {
                    return true;
                }
                ++iter_;
            }
            if (transitions_ == 0) ++iter_;
        }
        return false;
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Char>
    bool generate_function_body_switch(std::basic_ostream<Char> & os_
      , boost::lexer::basic_state_machine<Char> const &sm_)
    {
        typedef typename boost::lexer::basic_state_machine<Char>::iterator
            iterator_type;

        std::size_t const lookups_ = sm_.data()._lookup->front ()->size ();
        iterator_type iter_ = sm_.begin();
        iterator_type labeliter_ = iter_;
        iterator_type end_ = sm_.end();
        std::size_t const dfas_ = sm_.data()._dfa->size ();

        os_ << "    static std::size_t const npos = "
               "static_cast<std::size_t>(~0);\n";

        os_ << "\n    if (start_token_ == end_)\n";
        os_ << "    {\n";
        os_ << "        unique_id_ = npos;\n";
        os_ << "        return 0;\n";
        os_ << "    }\n\n";

        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "    bool bol = bol_;\n";
        }

        if (dfas_ > 1)
        {
            os_ << "again:\n";
        }

        os_ << "    Iterator curr_ = start_token_;\n";
        os_ << "    bool end_state_ = false;\n";
        os_ << "    std::size_t id_ = npos;\n";
        os_ << "    std::size_t uid_ = npos;\n";

        if (dfas_ > 1)
        {
            os_ << "    std::size_t end_start_state_ = start_state_;\n";
        }

        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "    bool end_bol_ = bol_;\n";
        }

        os_ << "    Iterator end_token_ = start_token_;\n";
        os_ << '\n';

        os_ << "    " << ((lookups_ == 256) ? "char" : "wchar_t")
            << " ch_ = 0;\n\n";

        if (dfas_ > 1)
        {
            os_ << "    switch (start_state_)\n";
            os_ << "    {\n";

            for (std::size_t i_ = 0; i_ < dfas_; ++i_)
            {
                os_ << "    case " << i_ << ":\n";
                os_ << "        goto state" << i_ << "_0;\n";
                os_ << "        break;\n";
            }

            os_ << "    default:\n";
            os_ << "        goto end;\n";
            os_ << "        break;\n";
            os_ << "    }\n";
        }

        bool need_state0_0_label = need_label0_0(sm_);

        for (std::size_t dfa_ = 0; dfa_ < dfas_; ++dfa_)
        {
            std::size_t const states_ = iter_->states;
            for (std::size_t state_ = 0; state_ < states_; ++state_)
            {
                std::size_t const transitions_ = iter_->transitions;
                std::size_t t_ = 0;

                if (dfas_ > 1 || dfa_ != 0 || state_ != 0 || need_state0_0_label)
                {
                    os_ << "\nstate" << dfa_ << '_' << state_ << ":\n";
                }

                if (iter_->end_state)
                {
                    os_ << "    end_state_ = true;\n";
                    os_ << "    id_ = " << iter_->id << ";\n";
                    os_ << "    uid_ = " << iter_->unique_id << ";\n";
                    os_ << "    end_token_ = curr_;\n";

                    if (dfas_ > 1)
                    {
                        os_ << "    end_start_state_ = " << iter_->goto_dfa <<
                            ";\n";
                    }

                    if (sm_.data()._seen_BOL_assertion)
                    {
                        os_ << "    end_bol_ = bol;\n";
                    }

                    if (transitions_) os_ << '\n';
                }

                if (t_ < transitions_ ||
                    iter_->bol_index != boost::lexer::npos ||
                    iter_->eol_index != boost::lexer::npos)
                {
                    os_ << "    if (curr_ == end_) goto end;\n";
                    os_ << "    ch_ = *curr_;\n";
                    if (iter_->bol_index != boost::lexer::npos)
                    {
                        os_ << "\n    if (bol) goto state" << dfa_ << '_'
                            << iter_->bol_index << ";\n";
                    }
                    if (iter_->eol_index != boost::lexer::npos)
                    {
                        os_ << "\n    if (ch_ == '\\n') goto state" << dfa_
                            << '_' << iter_->eol_index << ";\n";
                    }
                    os_ << "    ++curr_;\n";
                }

                for (/**/; t_ < transitions_; ++t_)
                {
                    Char const *ptr_ = iter_->token._charset.c_str();
                    Char const *end2_ = ptr_ + iter_->token._charset.size();
                    Char start_char_ = 0;
                    Char curr_char_ = 0;
                    bool range_ = false;
                    bool first_char_ = true;

                    os_ << "\n    if (";

                    while (ptr_ != end2_)
                    {
                        curr_char_ = *ptr_++;

                        if (*ptr_ == curr_char_ + 1)
                        {
                            if (!range_)
                            {
                                start_char_ = curr_char_;
                            }
                            range_ = true;
                        }
                        else
                        {
                            if (!first_char_)
                            {
                                os_ << ((iter_->token._negated) ? " && " : " || ");
                            }
                            else
                            {
                                first_char_ = false;
                            }
                            if (range_)
                            {
                                if (iter_->token._negated)
                                {
                                    os_ << "!";
                                }
                                os_ << "(ch_ >= '" << get_charlit(start_char_)
                                    << "' && ch_ <= '"
                                    << get_charlit(curr_char_) << "')";
                                range_ = false;
                            }
                            else
                            {
                                os_ << "ch_ "
                                    << ((iter_->token._negated) ? "!=" : "==")
                                    << " '" << get_charlit(curr_char_) << "'";
                            }
                        }
                    }

                    os_ << ") goto state" << dfa_ << '_' << iter_->goto_state
                        << ";\n";
                    ++iter_;
                }

                if (!(dfa_ == dfas_ - 1 && state_ == states_ - 1))
                {
                    os_ << "    goto end;\n";
                }

                if (transitions_ == 0) ++iter_;
            }
        }

        os_ << "\nend:\n";
        os_ << "    if (end_state_)\n";
        os_ << "    {\n";
        os_ << "        // return longest match\n";
        os_ << "        start_token_ = end_token_;\n";

        if (dfas_ > 1)
        {
            os_ << "        start_state_ = end_start_state_;\n";
            os_ << "\n        if (id_ == 0)\n";
            os_ << "        {\n";

            if (sm_.data()._seen_BOL_assertion)
            {
                os_ << "            bol = end_bol_;\n";
            }

            os_ << "            goto again;\n";
            os_ << "        }\n";

            if (sm_.data()._seen_BOL_assertion)
            {
                os_ << "        else\n";
                os_ << "        {\n";
                os_ << "            bol_ = end_bol_;\n";
                os_ << "        }\n";
            }
        }
        else if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        bol_ = end_bol_;\n";
        }

        os_ << "    }\n";
        os_ << "    else\n";
        os_ << "    {\n";

        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "        bol_ = (*start_token_ == '\\n') ? true : false;\n";
        }
        os_ << "        id_ = npos;\n";
        os_ << "        uid_ = npos;\n";
        os_ << "    }\n\n";

        os_ << "    unique_id_ = uid_;\n";
        os_ << "    return id_;\n";
        return os_.good();
    }

    ///////////////////////////////////////////////////////////////////////////
    // Generate a tokenizer for the given state machine.
    template <typename Char, typename F>
    inline bool
    generate_cpp (boost::lexer::basic_state_machine<Char> const& sm_
      , boost::lexer::basic_rules<Char> const& rules_
      , std::basic_ostream<Char> &os_, Char const* name_suffix
      , F generate_function_body)
    {
        if (sm_.data()._lookup->empty())
            return false;

        std::size_t const dfas_ = sm_.data()._dfa->size();
//         std::size_t const lookups_ = sm_.data()._lookup->front()->size();

        os_ << "// Copyright (c) 2008-2009 Ben Hanson\n";
        os_ << "// Copyright (c) 2008-2011 Hartmut Kaiser\n";
        os_ << "//\n";
        os_ << "// Distributed under the Boost Software License, "
            "Version 1.0. (See accompanying\n";
        os_ << "// file licence_1_0.txt or copy at "
            "http://www.boost.org/LICENSE_1_0.txt)\n\n";
        os_ << "// Auto-generated by boost::lexer, do not edit\n\n";

        std::basic_string<Char> guard(name_suffix);
        guard += L<Char>(name_suffix[0] ? "_" : "");
        guard += L<Char>(__DATE__ "_" __TIME__);
        typename std::basic_string<Char>::size_type p = 
            guard.find_first_of(L<Char>(": "));
        while (std::string::npos != p)
        {
            guard.replace(p, 1, L<Char>("_"));
            p = guard.find_first_of(L<Char>(": "), p);
        }
        { // to_upper(guard)
            typedef std::ctype<Char> facet_t;
            facet_t const& facet = std::use_facet<facet_t>(std::locale());
            typedef typename std::basic_string<Char>::iterator iter_t;
            for (iter_t iter = guard.begin(),
                        last = guard.end(); iter != last; ++iter)
                *iter = facet.toupper(*iter);
        }

        os_ << "#if !defined(BOOST_SPIRIT_LEXER_NEXT_TOKEN_" << guard << ")\n";
        os_ << "#define BOOST_SPIRIT_LEXER_NEXT_TOKEN_" << guard << "\n\n";

        os_ << "#include <boost/spirit/home/support/detail/lexer/char_traits.hpp>\n\n";

        generate_delimiter(os_);
        os_ << "// the generated table of state names and the tokenizer have to be\n"
               "// defined in the boost::spirit::lex::lexertl::static_ namespace\n";
        os_ << "namespace boost { namespace spirit { namespace lex { "
            "namespace lexertl { namespace static_ {\n\n";

        // generate the lexer state information variables
        if (!generate_cpp_state_info(rules_, os_, name_suffix))
            return false;

        generate_delimiter(os_);
        os_ << "// this function returns the next matched token\n";
        os_ << "template<typename Iterator>\n";
        os_ << "std::size_t next_token" << (name_suffix[0] ? "_" : "")
            << name_suffix  << " (";

        if (dfas_ > 1)
        {
            os_ << "std::size_t& start_state_, ";
        }
        else
        {
            os_ << "std::size_t& /*start_state_*/, ";
        }
        if (sm_.data()._seen_BOL_assertion)
        {
            os_ << "bool& bol_, ";
        }
        else
        {
            os_ << "bool& /*bol_*/, ";
        }
        os_ << "\n    ";

        os_ << "Iterator &start_token_, Iterator const& end_, ";
        os_ << "std::size_t& unique_id_)\n";
        os_ << "{\n";
        if (!generate_function_body(os_, sm_))
            return false;
        os_ << "}\n\n";

        if (!generate_cpp_state_table<Char>(os_, name_suffix
            , sm_.data()._seen_BOL_assertion, sm_.data()._seen_EOL_assertion))
        {
            return false;
        }

        os_ << "}}}}}  // namespace boost::spirit::lex::lexertl::static_\n\n";

        os_ << "#endif\n";

        return os_.good();
    }

    }   // namespace detail

    ///////////////////////////////////////////////////////////////////////////
    template <typename Lexer, typename F>
    inline bool
    generate_static(Lexer const& lexer
      , std::basic_ostream<typename Lexer::char_type>& os
      , typename Lexer::char_type const* name_suffix, F f)
    {
        if (!lexer.init_dfa(true))    // always minimize DFA for static lexers
            return false;
        return detail::generate_cpp(lexer.state_machine_, lexer.rules_, os
          , name_suffix, f);
    }

    ///////////////////////////////////////////////////////////////////////////
    // deprecated function, will be removed in the future (this has been
    // replaced by the function generate_static_dfa - see below).
    template <typename Lexer>
    inline bool
    generate_static(Lexer const& lexer
      , std::basic_ostream<typename Lexer::char_type>& os
      , typename Lexer::char_type const* name_suffix =
          detail::L<typename Lexer::char_type>())
    {
        return generate_static(lexer, os, name_suffix
          , &detail::generate_function_body_dfa<typename Lexer::char_type>);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Lexer>
    inline bool
    generate_static_dfa(Lexer const& lexer
      , std::basic_ostream<typename Lexer::char_type>& os
      , typename Lexer::char_type const* name_suffix =
          detail::L<typename Lexer::char_type>())
    {
        return generate_static(lexer, os, name_suffix
          , &detail::generate_function_body_dfa<typename Lexer::char_type>);
    }

    ///////////////////////////////////////////////////////////////////////////
    template <typename Lexer>
    inline bool
    generate_static_switch(Lexer const& lexer
      , std::basic_ostream<typename Lexer::char_type>& os
      , typename Lexer::char_type const* name_suffix =
          detail::L<typename Lexer::char_type>())
    {
        return generate_static(lexer, os, name_suffix
          , &detail::generate_function_body_switch<typename Lexer::char_type>);
    }

///////////////////////////////////////////////////////////////////////////////
}}}}

#endif

/* generate_static.hpp
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
*/