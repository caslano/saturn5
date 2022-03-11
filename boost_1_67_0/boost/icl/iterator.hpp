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