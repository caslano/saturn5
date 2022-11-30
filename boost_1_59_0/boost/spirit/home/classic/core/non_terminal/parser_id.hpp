/*=============================================================================
    Copyright (c) 2001-2003 Joel de Guzman
    Copyright (c) 2001 Daniel Nuffer
    http://spirit.sourceforge.net/

  Distributed under the Boost Software License, Version 1.0. (See accompanying
  file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#if !defined(BOOST_SPIRIT_PARSER_ID_HPP)
#define BOOST_SPIRIT_PARSER_ID_HPP

#if defined(BOOST_SPIRIT_DEBUG)
#   include <ostream>
#endif
#include <boost/spirit/home/classic/namespace.hpp>

///////////////////////////////////////////////////////////////////////////////
namespace boost { namespace spirit {

BOOST_SPIRIT_CLASSIC_NAMESPACE_BEGIN

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_id class
    //
    ///////////////////////////////////////////////////////////////////////////
    class parser_id
    {
    public:
                    parser_id()                     : p(0) {}
        explicit    parser_id(void const* prule)    : p(prule) {}
                    parser_id(std::size_t l_)       : l(l_) {}

        bool operator==(parser_id const& x) const   { return p == x.p; }
        bool operator!=(parser_id const& x) const   { return !(*this == x); }
        bool operator<(parser_id const& x) const    { return p < x.p; }
        std::size_t to_long() const                 { return l; }

    private:

        union
        {
            void const* p;
            std::size_t l;
        };
    };

    #if defined(BOOST_SPIRIT_DEBUG)
    inline std::ostream&
    operator<<(std::ostream& out, parser_id const& rid)
    {
        out << (unsigned int)rid.to_long();
        return out;
    }
    #endif

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_tag_base class: base class of all parser tags
    //
    ///////////////////////////////////////////////////////////////////////////
    struct parser_tag_base {};
    
    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_address_tag class: tags a parser with its address
    //
    ///////////////////////////////////////////////////////////////////////////
    struct parser_address_tag : parser_tag_base
    {
        parser_id id() const
        { return parser_id(reinterpret_cast<std::size_t>(this)); }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  parser_tag class: tags a parser with an integer ID
    //
    ///////////////////////////////////////////////////////////////////////////
    template <int N>
    struct parser_tag : parser_tag_base
    {
        static parser_id id()
        { return parser_id(std::size_t(N)); }
    };

    ///////////////////////////////////////////////////////////////////////////
    //
    //  dynamic_parser_tag class: tags a parser with a dynamically changeable
    //  integer ID
    //
    ///////////////////////////////////////////////////////////////////////////
    class dynamic_parser_tag : public parser_tag_base
    {
    public:
    
        dynamic_parser_tag() 
        : tag(std::size_t(0)) {}
        
        parser_id 
        id() const
        { 
            return 
                tag.to_long() 
                ? tag 
                : parser_id(reinterpret_cast<std::size_t>(this)); 
        }

        void set_id(parser_id id_) { tag = id_; } 
        
    private:
    
        parser_id tag;
    };

///////////////////////////////////////////////////////////////////////////////
BOOST_SPIRIT_CLASSIC_NAMESPACE_END

}} // namespace BOOST_SPIRIT_CLASSIC_NS

#endif


/* parser_id.hpp
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
*/