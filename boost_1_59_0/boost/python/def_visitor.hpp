// Copyright David Abrahams 2003.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef DEF_VISITOR_DWA2003810_HPP
# define DEF_VISITOR_DWA2003810_HPP

# include <boost/python/detail/prefix.hpp>
# include <boost/detail/workaround.hpp>

namespace boost { namespace python { 

template <class DerivedVisitor> class def_visitor;
template <class T, class X1, class X2, class X3> class class_;

class def_visitor_access
{
# if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)                  \
    || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
    // Tasteless as this may seem, making all members public allows member templates
    // to work in the absence of member template friends.
 public:
# else      
    template <class Derived> friend class def_visitor;
# endif
    
    // unnamed visit, c.f. init<...>, container suites
    template <class V, class classT>
    static void visit(V const& v, classT& c)
    {
        v.derived_visitor().visit(c);
    }

    // named visit, c.f. object, pure_virtual
    template <class V, class classT, class OptionalArgs>
    static void visit(
        V const& v
      , classT& c
      , char const* name
      , OptionalArgs const& options
    ) 
    {
        v.derived_visitor().visit(c, name, options);
    }
    
};


template <class DerivedVisitor>
class def_visitor
{
    friend class def_visitor_access;
    
# if defined(BOOST_NO_MEMBER_TEMPLATE_FRIENDS)                  \
    || BOOST_WORKAROUND(BOOST_BORLANDC, BOOST_TESTED_AT(0x551))
    // Tasteless as this may seem, making all members public allows member templates
    // to work in the absence of member template friends.
 public:
# else      
    template <class T, class X1, class X2, class X3> friend class class_;
# endif
    
    // unnamed visit, c.f. init<...>, container suites
    template <class classT>
    void visit(classT& c) const
    {
        def_visitor_access::visit(*this, c);
    }

    // named visit, c.f. object, pure_virtual
    template <class classT, class OptionalArgs>
    void visit(classT& c, char const* name, OptionalArgs const& options) const
    {
        def_visitor_access::visit(*this, c, name, options);
    }
    
 protected:
    DerivedVisitor const& derived_visitor() const
    {
        return static_cast<DerivedVisitor const&>(*this);
    }
};

}} // namespace boost::python

#endif // DEF_VISITOR_DWA2003810_HPP

/* def_visitor.hpp
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
*/