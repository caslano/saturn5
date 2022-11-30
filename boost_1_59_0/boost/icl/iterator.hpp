/*-----------------------------------------------------------------------------+
Copyright (c) 2009-2009: Joachim Faulhaber
+------------------------------------------------------------------------------+
   Distributed under the Boost Software License, Version 1.0.
      (See accompanying file LICENCE.txt or copy at
           http://www.boost.org/LICENSE_1_0.txt)
+-----------------------------------------------------------------------------*/
#ifndef BOOST_ICL_ITERATOR_HPP_JOFA_091003
#define BOOST_ICL_ITERATOR_HPP_JOFA_091003

#include <iterator>
#include <boost/config/warning_disable.hpp>

namespace boost{namespace icl
{

/** \brief Performes an addition using a container's memberfunction add, when operator= is called. */
template<class ContainerT> class add_iterator
{
public:
    /// The container's type.
    typedef ContainerT container_type;
    typedef std::output_iterator_tag iterator_category; 
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    /** An add_iterator is constructed with a container and a position 
        that has to be maintained. */
    add_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    /** This assignment operator adds the \c value before the current position.
        It maintains it's position by incrementing after addition.    */
    add_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = icl::add(*_cont, _iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }

    add_iterator& operator*()    { return *this; }
    add_iterator& operator++()   { return *this; }
    add_iterator& operator++(int){ return *this; }

private:
    ContainerT*                   _cont;
    typename ContainerT::iterator _iter;
};


/** Function adder creates and initializes an add_iterator */
template<class ContainerT, typename IteratorT>
inline add_iterator<ContainerT> adder(ContainerT& cont, IteratorT iter_)
{
    return add_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

/** \brief Performes an insertion using a container's memberfunction add, when operator= is called. */
template<class ContainerT> class insert_iterator
{
public:
    /// The container's type.
    typedef ContainerT container_type;
    typedef std::output_iterator_tag iterator_category; 
    typedef void value_type;
    typedef void difference_type;
    typedef void pointer;
    typedef void reference;

    /** An insert_iterator is constructed with a container and a position 
        that has to be maintained. */
    insert_iterator(ContainerT& cont, typename ContainerT::iterator iter)
    : _cont(&cont), _iter(iter) {}

    /** This assignment operator adds the \c value before the current position.
        It maintains it's position by incrementing after addition.    */
    insert_iterator& operator=(typename ContainerT::const_reference value)
    {
        _iter = _cont->insert(_iter, value);
        if(_iter != _cont->end())
            ++_iter;
        return *this;
    }

    insert_iterator& operator*()    { return *this; }
    insert_iterator& operator++()   { return *this; }
    insert_iterator& operator++(int){ return *this; }

private:
    ContainerT*                   _cont;
    typename ContainerT::iterator _iter;
};


/** Function inserter creates and initializes an insert_iterator */
template<class ContainerT, typename IteratorT>
inline insert_iterator<ContainerT> inserter(ContainerT& cont, IteratorT iter_)
{
    return insert_iterator<ContainerT>(cont, typename ContainerT::iterator(iter_));
}

}} // namespace icl boost

#endif // BOOST_ICL_ITERATOR_HPP_JOFA_091003



/* iterator.hpp
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
*/