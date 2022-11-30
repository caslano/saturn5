// Copyright David Abrahams 2002.
// Distributed under the Boost Software License, Version 1.0. (See
// accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef PROXY_DWA2002615_HPP
# define PROXY_DWA2002615_HPP
# include <boost/python/detail/prefix.hpp>
# include <boost/python/object_core.hpp>
# include <boost/python/object_operators.hpp>

namespace boost { namespace python { namespace api {

template <class Policies>
class proxy : public object_operators<proxy<Policies> >
{
    typedef typename Policies::key_type key_type;
    
    typedef proxy const& assignment_self;
 public:
    proxy(object const& target, key_type const& key);
    operator object() const;

    // to support a[b] = c[d]
    proxy const& operator=(assignment_self) const;
    
    template <class T>
    inline proxy const& operator=(T const& rhs) const
    {
        Policies::set(m_target, m_key, object(rhs));
        return *this;
    }

 public: // implementation detail
    void del() const;
        
 private:
    object m_target;
    key_type m_key;
};


template <class T>
inline void del(proxy<T> const& x)
{
    x.del();
}

//
// implementation
//

template <class Policies>
inline proxy<Policies>::proxy(object const& target, key_type const& key)
    : m_target(target), m_key(key)
{}

template <class Policies>
inline proxy<Policies>::operator object() const
{
    return Policies::get(m_target, m_key);
}

// to support a[b] = c[d]
template <class Policies>
inline proxy<Policies> const& proxy<Policies>::operator=(typename proxy::assignment_self rhs) const
{
    return *this = python::object(rhs);
}

# define BOOST_PYTHON_PROXY_INPLACE(op)                                         \
template <class Policies, class R>                                              \
proxy<Policies> const& operator op(proxy<Policies> const& lhs, R const& rhs)    \
{                                                                               \
    object old(lhs);                                                            \
    return lhs = (old op rhs);                                                  \
} 
BOOST_PYTHON_PROXY_INPLACE(+=)
BOOST_PYTHON_PROXY_INPLACE(-=)
BOOST_PYTHON_PROXY_INPLACE(*=)
BOOST_PYTHON_PROXY_INPLACE(/=)
BOOST_PYTHON_PROXY_INPLACE(%=)
BOOST_PYTHON_PROXY_INPLACE(<<=)
BOOST_PYTHON_PROXY_INPLACE(>>=)
BOOST_PYTHON_PROXY_INPLACE(&=)
BOOST_PYTHON_PROXY_INPLACE(^=)
BOOST_PYTHON_PROXY_INPLACE(|=)
# undef BOOST_PYTHON_PROXY_INPLACE

template <class Policies>
inline void proxy<Policies>::del() const
{
    Policies::del(m_target, m_key);
}

}}} // namespace boost::python::api

#endif // PROXY_DWA2002615_HPP

/* proxy.hpp
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
*/